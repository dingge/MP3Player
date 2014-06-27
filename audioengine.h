#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H


#include <QObject>
#include <QTimer>
#include "mpg123.h"
#include "ao/ao.h"
#include <include/portaudio.h>

class AudioEngine : public QObject
{
    Q_OBJECT

public:
    AudioEngine(QObject * parent);
    ~AudioEngine();
    void play();
    void pause();
    int currentState();

    const int PLAYING;
    const int PAUSED;
    const int STOPPED;

private:
    void initDecoder(QString filename);
    void initOutput(int, int, long);
    int patestCallback(const void *inputBuffer, void *outputBuffer,
                       unsigned long framesPerBuffer,
                       const PaStreamCallbackTimeInfo *timeInfo,
                       PaStreamCallbackFlags statusFlags,
                       void *userData);

    int engineState;

    QTimer *m_pullTimer;
    bool pull_state;
    float reset;

    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;
    ao_sample_format format;

private slots:
    void pullTimerExpired();
    //void toggleSuspendResume();

};

#endif
