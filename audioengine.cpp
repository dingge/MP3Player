#include "audioengine.h"
#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>

#define BITS 8

AudioEngine::AudioEngine(QObject *parent) :
    PLAYING(0),
    PAUSED(1),
    STOPPED(2),
    m_pullTimer(new QTimer(0))
{
    Q_UNUSED(parent);
    initDecoder("C:/Users/Public/Music/Sample Music/Kalimba.mp3");
}

AudioEngine::~AudioEngine()
{
}

int AudioEngine::currentState()
{
    return engineState;
}

void AudioEngine::initDecoder(QString filename)
{

    int channels, encoding;
    long rate;

    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer_size /= 8;
    buffer = (unsigned char *) malloc(sizeof(unsigned char) * buffer_size);
    mpg123_open(mh, filename.toStdString().c_str());
    mpg123_getformat(mh, &rate, &channels, &encoding);
    mpg123_volume_change(mh, 0);
    initOutput(channels, encoding, rate);
}


void AudioEngine::initOutput(int channels, int encoding, long rate)
{
    connect(m_pullTimer, SIGNAL(timeout()), SLOT(pullTimerExpired()));

    ao_initialize();
    driver = ao_default_driver_id();
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    long time = format.bits * format.rate * format.channels;

    qDebug() << time;
    qDebug() << buffer_size;

    reset = (((float)buffer_size*8)/time*1000)-5;
    engineState = PAUSED;
}

void AudioEngine::play()
{
    m_pullTimer->start(reset);
    engineState = PLAYING;
}

void AudioEngine::pause(){
    m_pullTimer->stop();
    engineState = PAUSED;
}

void AudioEngine::pullTimerExpired()
{
    err = mpg123_read(mh, buffer, buffer_size, &done);
    if(err == MPG123_OK)
    {
        ao_play(dev, (char *)buffer, buffer_size);        
    }
    else
    {
        engineState = STOPPED;
        m_pullTimer->stop();
        free(buffer);
        ao_close(dev);
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        ao_shutdown();
    }
}
