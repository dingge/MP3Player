#include "audioplayer.h"
#include <QToolButton>
#include <QSlider>
#include <QStyle>
#include <QBoxLayout>

AudioPlayer::AudioPlayer(QObject *parent) :
    m_audioEngine(0),
    m_playButton(0),
    m_positionSlider(0),
    m_positionLabel(0),
    m_infoLabel(0)
{
    Q_UNUSED(parent);
    createWidgets();
}

AudioPlayer::~AudioPlayer()
{

}

void AudioPlayer::togglePlayback()
{
    if(m_audioEngine.currentState() == m_audioEngine.PAUSED)
    {
        m_audioEngine.play();
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else if(m_audioEngine.currentState() == m_audioEngine.PLAYING)
    {
        m_audioEngine.pause();
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void AudioPlayer::createWidgets()
{
    m_playButton = new QToolButton(this);
    m_playButton->setEnabled(true);
    m_playButton->setToolTip(tr("Play"));
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(m_playButton, SIGNAL(clicked()), this, SLOT(togglePlayback()));
    //connect(playButton, SIGNAL(clicked()), this->parent(), SLOT(updateBuffer()));

    /*
    QAbstractButton *openButton = new QToolButton(this);
    openButton->setText(tr("..."));
    openButton->setToolTip(tr("Open a file..."));
    openButton->setFixedSize(playButton->sizeHint());
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));
    */


    m_positionSlider = new QSlider(Qt::Horizontal, this);
    m_positionSlider->setEnabled(false);
    m_positionSlider->setToolTip(tr("Seek"));
    //connect(positionSlider, SIGNAL(valueChanged(int)), this, SLOT(setPosition(int)));

    m_infoLabel = new QLabel(this);
    m_positionLabel = new QLabel(tr("00:00"), this);
    m_positionLabel->setMinimumWidth(m_positionLabel->sizeHint().width());

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    //controlLayout->addWidget(openButton);
    controlLayout->addWidget(m_playButton);
    controlLayout->addWidget(m_positionSlider);
    controlLayout->addWidget(m_positionLabel);
    //controlLayout->addWidget(volumeButton);

    QBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_infoLabel);
    mainLayout->addLayout(controlLayout);
}
