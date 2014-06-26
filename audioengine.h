#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H


#include <QWidget>
#include <QTimer>
#include <QMainWindow>
#include <QPushButton>
#include "mpg123.h"
#include "ao/ao.h"

class AudioEngine : public QMainWindow
{
    Q_OBJECT

public:
    AudioEngine(QObject * parent);
    ~AudioEngine();

private:
    void initDecoder(QString filename);
    void initOutput(int, int, long);
    void initWindow();

    QPushButton *m_suspendResumeButton;
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
    void toggleSuspendResume();

};

#endif
