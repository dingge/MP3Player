#include "windowtitlebar.h"
#include "qpainter.h"

WindowTitleBar::WindowTitleBar(QWidget * parent): QWidget(parent),
    m_Cache(NULL),
    m_Title(this),
    m_Minimize(WindowButton::BUTTON_MINIMIZE),
    m_Maximize(WindowButton::BUTTON_MAXIMIZE),
    m_Close(WindowButton::BUTTON_CLOSE)
{
    setFixedHeight(26);
    m_Title.setStyleSheet("color: white; font: bold 12px");
    updateWindowTitle();
    connect(&m_Minimize, SIGNAL(clicked()), this, SLOT(Minimized()));
    connect(&m_Maximize, SIGNAL(clicked()), this, SLOT(Maximized()));
    connect(&m_Close, SIGNAL(clicked()), this, SLOT(Quit()));
    m_SubLayout.setContentsMargins(5,5,2,5);
    m_SubLayout.setSpacing(0);
    m_SubLayout.addWidget(&m_Minimize, 0, 1, 1, 1);
    m_SubLayout.addWidget(&m_Maximize, 0, 2, 1, 1);
    m_SubLayout.addWidget(&m_Close, 0, 3, 1, 1);
    m_SubLayout.setColumnStretch(0, 1);
    m_SubLayout.setRowStretch(1,1);
    setLayout(&m_SubLayout);
}

WindowTitleBar::~WindowTitleBar()
{
}

void  WindowTitleBar::resizeEvent(QResizeEvent  * event)
 {

    Q_UNUSED (event);

    delete m_Cache;

    m_Cache = new QPixmap(size());

    m_Cache->fill(Qt::transparent);

    QPainter painter(m_Cache);

    QPolygon border;
    QLine separate(QPoint(0, height()), QPoint(width(), height()));

    border  <<  QPoint(width(), 0)
            <<  QPoint(width(), height())
            <<  QPoint(0, height())
            <<  QPoint(0,0);

    QBrush background(QColor(80,80,80));

    painter.setPen(Qt::transparent);
    painter.setBrush(background);
    painter.drawPolygon(border);
    painter.setPen(QPen(Qt::black, 2.0));
    painter.drawLine(separate);

    m_Title.move(width()/2-43, -1);
}

void  WindowTitleBar::paintEvent ( QPaintEvent  * event)
 {

  Q_UNUSED (event);

  if(m_Cache != NULL)
   {
    QPainter painter(this);

    painter.drawPixmap(0, 0, * m_Cache);
   }
}

void WindowTitleBar::updateWindowTitle()
{
    m_Title.setText("MP3 PLAYER");
}

void WindowTitleBar::Minimized()
{
    window()->showMinimized();
}

void WindowTitleBar::Maximized()
{
    if(window()->windowState() == Qt::WindowMaximized)
        window()->showNormal();
    else
        window()->showMaximized();
}

void WindowTitleBar::Quit()
{
    exit(0);
}

void WindowTitleBar::mousePressEvent(QMouseEvent *event)
{
    m_Diff = event->pos();

}

void WindowTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    setCursor(QCursor(Qt::ArrowCursor));
}

void WindowTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->globalPos();

    window()->move(p-m_Diff);
}
