#include "customwindow.h"
#include "musicplayer.h"
#include "playlist.h"
#include <QDesktopWidget>
#include <QAudioDecoder>


CustomWindow::CustomWindow(QWidget * parent):
    QWidget (parent),
    m_PlayList(this),
    m_MusicPlayer(this),
    m_TabWindow(0),
    m_SizeGrip(this)
{  
    connect(this, SIGNAL(windowTitleChanged()), &m_TitleBar, SLOT(updateWindowTitle()));
    connect(&m_PlayList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), SLOT(updateSong(QTreeWidgetItem*)));
    connect(&m_PlayList, SIGNAL(itemSelectionChanged()), SLOT(updateBuffer()));
    formatWidget();
    setLayout(&m_MainLayout);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
}

void CustomWindow::formatWidget()
{
    QWidget *equalizer = new QWidget();
    resize(512, 256);
    setWindowTitle(tr("Nobis MP3 Player"));
    setWindowFlags(Qt::FramelessWindowHint);
    m_MainLayout.setMargin(0);
    m_MainLayout.setHorizontalSpacing(5);
    m_TabWindow.addTab(&m_PlayList, "Library");
    m_TabWindow.addTab(equalizer, "Equalizer");
    m_MainLayout.addWidget(&m_TitleBar, 0, 0, 1, 3);
    m_MainLayout.addWidget(&m_TabWindow,1,1,1,1);
    m_MainLayout.addWidget(&m_MusicPlayer,2,0,1,3);
    m_MainLayout.setRowStretch(2, 1);

}

CustomWindow::~CustomWindow()
{
}

void CustomWindow::setWindowTitle(const QString &title)
{
    QWidget::setWindowTitle(title);
    emit windowTitleChanged();
}

void CustomWindow::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QBrush background(QColor(120,120,120));

    painter.setBrush(background);
    painter.setPen(Qt::NoPen);

    painter.drawRect(0,0,width(),height());
    painter.setPen(QPen(Qt::black, 2.0));
    painter.drawRect(0,0,width(),height());
}

void CustomWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    CenterOnScreen();
}

void CustomWindow::updateSong(QTreeWidgetItem* item)
{
    QString song = item->data(0, 4).toString();
    qDebug() << song;
    m_MusicPlayer.playFile(song);
}

void CustomWindow::updateBuffer()
{
    QTreeWidgetItem *item = m_PlayList.selectedItems().first();
    QString song = item->data(0,4).toString();
    m_MusicPlayer.bufferFile(song);
}

void CustomWindow::CenterOnScreen()
{
    QDesktopWidget screen;
    QRect screenGeom = screen.screenGeometry(this);

    int screenCenterX = screenGeom.width()-this->width();
    int screenCenterY = screenGeom.height()-this->height();

    move(screenCenterX/2, screenCenterY/2);
}
