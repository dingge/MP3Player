#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QWidget>
#include "audioengine.h"
#include <QButtonGroup>
#include <QSlider>
#include <QLabel>

class AudioPlayer : public QWidget
{
    Q_OBJECT

public:
    AudioPlayer(QObject * parent);
    ~AudioPlayer();

private:
    void createWidgets();

    AudioEngine m_audioEngine;
    QAbstractButton *m_playButton;
    QSlider *m_positionSlider;
    QLabel *m_positionLabel;
    QLabel *m_infoLabel;
    //VolumeButton *volumeButton;

public slots:
    void togglePlayback();
};

#endif // AUDIOPLAYER_H
