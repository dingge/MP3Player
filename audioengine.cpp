#include "audioengine.h"
#include <QDebug>
#include <QVBoxLayout>

#define BITS 8

AudioEngine::AudioEngine(QObject *parent) :
    m_pullTimer(new QTimer(this))
{
    Q_UNUSED(parent);
    initDecoder("C:/Users/Public/Music/Sample Music/Kalimba.mp3");
    initWindow();
}

AudioEngine::~AudioEngine()
{
}

void AudioEngine::initWindow()
{
    QScopedPointer<QWidget> window(new QWidget);
    QScopedPointer<QVBoxLayout> layout(new QVBoxLayout);

    m_suspendResumeButton = new QPushButton(this);
    m_suspendResumeButton->setText(tr("Pause"));
    connect(m_suspendResumeButton, SIGNAL(clicked()), SLOT(toggleSuspendResume()));
    layout->addWidget(m_suspendResumeButton);

    window->setLayout(layout.data());
    layout.take(); // ownership transferred

    setCentralWidget(window.data());
    QWidget *const windowPtr = window.take(); // ownership transferred
    windowPtr->show();
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
    initOutput(channels, encoding, rate);
}

void AudioEngine::toggleSuspendResume()
{
    if(pull_state == true)
    {
        pull_state = false;
        m_pullTimer->stop();
    }
    else
    {
        pull_state = true;
        m_pullTimer->start(reset);
    }
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
    m_pullTimer->start(reset);
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
        m_pullTimer->stop();
        free(buffer);
        ao_close(dev);
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        ao_shutdown();
    }
}
