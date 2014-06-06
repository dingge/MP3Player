#include "customwindow.h"
#include "musicplayer.h"
#include "playlist.h"
#include <QDesktopWidget>

CustomWindow::CustomWindow(QWidget * parent): QWidget (parent), m_MusicPlayer(0), m_TabWindow(0)
{
    PlayList *playlist = new PlayList(this);
    QWidget *equalizer = new QWidget();
    connect(this, SIGNAL(windowTitleChanged()), &m_TitleBar, SLOT(updateWindowTitle()));
    resize(512, 256);
    setWindowTitle(tr("Nobis MP3 Player"));
    setWindowFlags(Qt::FramelessWindowHint);
    m_MainLayout.setMargin(0);
    m_MainLayout.setSpacing(0);
    m_MainLayout.addWidget(&m_TitleBar, 0, 0, 1, 1);
    m_TabWindow.addTab(playlist, "PlayList");
    m_TabWindow.addTab(equalizer, "Equalizer");
    m_MainLayout.addWidget(&m_TabWindow,2,0,1,1);
    m_MainLayout.addWidget(&m_MusicPlayer,3,0,1,1);
    m_MainLayout.setRowStretch(1, 1);
    setLayout(&m_MainLayout);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
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

    QPixmap pixmap(size());
    QPainter painter(&pixmap);
    QColor gradientStart(0, 0, 0, 0);
    QColor gradientEnd(0,0,0,220);
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
    linearGrad.setColorAt(1, gradientStart);
    linearGrad.setColorAt(0, gradientEnd);

    QLine left(QPoint(0, 50),QPoint(width(), 50));

    painter.fillRect(pixmap.rect(), Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRoundRect(pixmap.rect(), 6, 6);
    painter.setPen(QPen(Qt::black, 3.0));
    painter.drawLine(left);
    setMask(pixmap.createMaskFromColor(Qt::white));
}

void CustomWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    CenterOnScreen();
}

void CustomWindow::CenterOnScreen()
{
    QDesktopWidget screen;
    QRect screenGeom = screen.screenGeometry(this);

    int screenCenterX = screenGeom.width()-this->width();
    int screenCenterY = screenGeom.height()-this->height();

    move(screenCenterX/2, screenCenterY/2);
}
