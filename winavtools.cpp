#include "winavtools.h"

using namespace std;

WinAvTools::WinAvTools()
{
    detectSources();
}

WinAvTools::~WinAvTools(){
    for(unsigned int i(0); i<sources.size(); i++){
        delete sources[i];
        sources[i] = 0;
    }
}

vector<Source*> WinAvTools::getSources() const{
    return this->sources;
}


Source *WinAvTools::peekVideoSource() const{
    unsigned int i(0);
    bool found(false);

    while(i<sources.size() && !found){
        i++;
        if (sources[i-1]->getType() == "video")
            found = true;

    }

    return sources[i-1];
}

Source *WinAvTools::peekAudioSource() const{
    unsigned int i(0);
    bool found(false);

    while(i<sources.size() && !found){
        i++;
        if (sources[i-1]->getType() == "audio")
            found = true;
    }
    return sources[i-1];
}

string WinAvTools::getDevicesCommand() const{
    return this->devicesCommand;
}

void WinAvTools::setSources(vector<Source*> sources){
    this->sources = sources;
}

void WinAvTools::setDevicesCommand(string videoDevice){
    this->devicesCommand = "video=" + videoDevice;
}

void WinAvTools::setDevicesCommand(string videoDevice, string audioDevice){
    this->devicesCommand = "video=" + videoDevice + ":audio="+ audioDevice;
}

void WinAvTools::pushSource(Source *source){
    sources.push_back(source);
}

void WinAvTools::detectSources(){

    QProcess *process = new QProcess();

    QString path("..\\StreaMe\\ffmpeg\\bin\\ffmpeg.exe");
    // Path working, but we have to come back to the previous folder to choose the "StreaMe" directory.
    //This is because Qt creator uses a debug folder.
    //Maybe pay attention later...

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
                this->pushSource(new Camera(this,video.substr(0, posVideo),"video"));

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
                this->pushSource(new Microphone(this,audio.substr(0, posAudio),"audio"));

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
}




