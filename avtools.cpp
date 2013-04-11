#include "avtools.h"

using namespace std;

AvTools::AvTools()
{
    detectSources();
}

AvTools::~AvTools(){
    for(unsigned int i(0); i<sources.size(); i++){
        delete sources[i];
        sources[i] = 0;
    }
}

vector<Source*> AvTools::getSources() const{
    return this->sources;
}


Source *AvTools::peekVideoSource() const{
    unsigned int i(0);
    bool found(false);

    while(i<sources.size() && !found){
        i++;
        if (sources[i-1]->getType() == "video")
            found = true;

    }

    return sources[i-1];
}

Source *AvTools::peekAudioSource() const{
    unsigned int i(0);
    bool found(false);

    while(i<sources.size() && !found){
        i++;
        if (sources[i-1]->getType() == "audio")
            found = true;
    }
    return sources[i-1];
}

string AvTools::getDevicesCommand() const{
    return this->devicesCommand;
}

void AvTools::setSources(vector<Source*> sources){
    this->sources = sources;
}

void AvTools::setDevicesCommand(string videoDevice){
#ifdef _WIN32
    this->devicesCommand = "video=" + videoDevice;
#elif __linux__ // else if it's linux
    this->devicesCommand = videoDevice ;
#else //else, error
#error
#endif
}

void AvTools::setDevicesCommand(string videoDevice, string audioDevice){
#ifdef _WIN32
    this->devicesCommand = "video=" + videoDevice + ":audio="+ audioDevice;
#elif __linux__ // else if it's linux
    this->devicesCommand = videoDevice + " -f alsa -i " + audioDevice ;
#else //else, error
#error
#endif
}

void AvTools::pushSource(Source *source){
    sources.push_back(source);
}

void AvTools::detectSources(){

#ifdef _WIN32 //if the OS is Windows 32 AND 64 bits

    cout << "Windows avtools detecting sources feature is working..." << endl;

    QProcess *process = new QProcess();

    QString path("ffmpeg\\bin\\ffmpeg.exe");

    string data, video, audio;
    int posVideo(0), posAudio(0), posEnd(0);

    QStringList arguments;
    arguments << "-list_devices" << "true" << "-f" << "dshow" << "-i" << "dummy";

    process->setProcessChannelMode(QProcess::MergedChannels); // get all channels for the output
    process->start(path,arguments,QIODevice::ReadWrite);

    // If the process started
    if(process->waitForStarted()){
        while(process->waitForReadyRead())
            data.append(process->readAll());

        if ((data.find("DirectShow video devices") != string::npos) && (data.find("DirectShow audio devices") != string::npos) && (data.find("dummy: Immediate exit requested") != string::npos))
        {
            //We get positions of important parts of the string

            posVideo = data.find("DirectShow video devices");
            posAudio = data.find("DirectShow audio devices");
            posEnd = data.find("dummy: Immediate exit requested");

            //and then we split the string in two parts

            video = data.substr(posVideo,posAudio - posVideo);
            audio = data.substr(posAudio,posEnd - posAudio);

            //now we create "Source" objects for all inputs, and add it into the global vector corresponding

            // one input line will look like "USB2.0 HD UVC WebCam" (including quotes)
            // therefore, we look for all inputs in the section "video devices" (this means before posAudio)
            while((posVideo < posAudio) && (video.find("\"") != string::npos)){

                posVideo = video.find("\"") + 1; //We get the position just after the first quote
                video = video.substr(posVideo , video.size() - posVideo); // we remove all until this position

                posVideo = video.find("\""); // the position of the next quote

                //we add the source found in the global vector of sources
                this->pushSource(new Camera(this,video.substr(0, posVideo),"video",video.substr(0, posVideo)));

                video = video.substr(++posVideo, video.size() - posVideo);
                // we save the remaining string and remove the first character to not keep the quote for the next iteration

            }

            // one input line will look like "Microphone (Realtek High Definition Audio)" (including quotes)
            // therefore, we look for all inputs in the section "audio devices" (this means before posEnd)
            while((posAudio < posEnd) && (audio.find("\"") != string::npos)){

                posAudio = audio.find("\"") + 1; //We get the position just after the first quote
                audio = audio.substr(posAudio , audio.size() - posAudio); // we remove all until this position

                posAudio = audio.find("\""); // the position of the next quote

                //we add the source found in the global vector of sources
                this->pushSource(new Microphone(this,audio.substr(0, posAudio),"audio",audio.substr(0, posAudio)));

                audio = audio.substr(++posAudio, audio.size() - posAudio);
                // we save the remaining string and remove the first character to not keep the quote for the next iteration
            }
        }
        else
            cout << "Error while reading FFmpeg dshow list output" << endl; //REPLACE BY EXCEPTION
    }
    else
        cout << "Error while starting FFmpeg dshow devices list command" << endl; //REPLACE BY EXCEPTION

    process->kill();

#elif __linux__ // else if it's linux
    cout << "Linux avtools detecting sources feature is working..." << endl;

    QProcess *process = new QProcess();
    QString path("v4l2-ctl"), data, videoName, videoSysName, audioName, audioSysName;
    int i = 0;

    QStringList arguments;
    arguments << "--list-devices";

    process->setProcessChannelMode(QProcess::MergedChannels); // get all channels for the output
    process->start(path,arguments,QIODevice::ReadWrite);

    // If the process started
    if(process->waitForStarted()){
        while(process->waitForReadyRead())
            data.append(process->readAll());

        //adding video souces to the souces vector
        while(data.indexOf("\n") != -1){ //if there is at least one line

            videoName=data.left(data.indexOf(" ("));

            data = data.mid(data.indexOf("\n")+1, data.size()); //Removing the first line
            data = data.mid(data.indexOf("\n")+1, data.size());// And the second line
            data = data.mid(data.indexOf("\n")+1, data.size());// And the third line

            videoSysName = "/dev/video";
            videoSysName += QString::number(i);
            this->pushSource(new Camera(this,videoName.toStdString(),"video",videoSysName.toStdString()));
            videoName.clear();
            i++;
        }
    }

    process->kill();
    path.clear();
    arguments.clear();
    data.clear();
    i=0;

    path = QString::fromStdString("cat");
    arguments << "/proc/asound/cards";

    process->start(path,arguments,QIODevice::ReadWrite);

    // If the process have started
    if(process->waitForStarted()){
        while(process->waitForReadyRead())
            data.append(process->readAll());

        //adding video souces to the souces vector
        while(data.indexOf("\n") != -1){ //if there is at least one line

            audioName = data.mid(data.indexOf(" - ")+3,data.indexOf("\n") - (data.indexOf(" - ")+3)); //Taking the audio device name into the first line
            data = data.mid(data.indexOf("\n")+1, data.size());// Removing the first line
            data = data.mid(data.indexOf("\n")+1, data.size());// And the second line

            audioSysName = "hw:";
            audioSysName += QString::number(i);
            this->pushSource(new Microphone(this,audioName.toStdString(),"audio",audioSysName.toStdString()));
            audioName.clear();
            i++;
        }
    }

#else //else, error
#error
#endif
}




