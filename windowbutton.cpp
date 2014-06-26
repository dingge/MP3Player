#include "windowbutton.h"
#include "qpainter.h"

WindowButton::WindowButton(ButtonType type, QWidget *parent) :
    QAbstractButton(parent),
    m_Type(type),
    m_State(STATE_NORMAL),
    m_Normal(NULL),
    m_Hovered(NULL),
    m_Clicked(NULL)
{
    setFixedHeight(24);
    setFixedWidth(20);
    InitPixmaps();
}

WindowButton::~WindowButton()
{
    delete m_Normal;
    delete m_Hovered;
    delete m_Clicked;
}

void WindowButton::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    InitPixmaps();
}

void WindowButton::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    if(isEnabled())
    {
        switch(m_State)
        {
            case STATE_NORMAL:
                if(m_Normal != NULL)
                    painter.drawPixmap(0,0,*m_Normal);
                break;
            case STATE_HOVERED:
                if(m_Hovered != NULL)
                    painter.drawPixmap(0,0,*m_Hovered);
                break;
            case STATE_CLICKED:
                if(m_Clicked != NULL)
                    painter.drawPixmap(0,0,*m_Clicked);
                break;
        }
    }
    else
    {
        if(m_Normal != NULL)
            painter.drawPixmap(0,0,*m_Normal);
    }
}

void WindowButton::InitPixmaps()
{
    InitPixmap(&m_Normal);
    InitPixmap(&m_Hovered);
    InitPixmap(&m_Clicked);

    switch(m_Type)
    {
        case BUTTON_MINIMIZE:
            InitMinimize();
            break;
        case BUTTON_MAXIMIZE:
            InitMaximize();
            break;
        case BUTTON_CLOSE:
            InitClose();
            break;
    }
}

void WindowButton::InitPixmap(QPixmap * *pixmap)
{
    delete *pixmap;
    *pixmap = new QPixmap(size());
    (*pixmap)->fill(Qt::transparent);
}

void WindowButton::InitMinimize()
{
    QPainterPath circle_path;
    circle_path.addEllipse(QPointF(10,8), 8, 8);

    QLine symbol1(QPoint(width()-7, 8), QPoint(6, 8));

    QColor gradientStart(0, 0, 0, 0);
    QColor gradientEnd(0,0,0,220);

    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
    linearGrad.setColorAt(0, gradientStart);
    linearGrad.setColorAt(1, gradientEnd);

    QLinearGradient invertlinearGrad(QPointF(0,0), QPointF(0, height()));
    invertlinearGrad.setColorAt(0, gradientEnd);
    invertlinearGrad.setColorAt(1, gradientStart);

    QPainter painter;

    //Mode Normal
    painter.begin(m_Normal);

    painter.setPen(QPen(Qt::black, 0.5));
    painter.setBrush(QBrush(linearGrad));
    painter.drawPath(circle_path);

    painter.setPen(QPen(Qt::black, 1.0));
    painter.drawLine(symbol1);

    painter.end();

    //Mode Hovered
    painter.begin(m_Hovered);

    painter.setPen(QPen(Qt::blue, 1.0));
    painter.setBrush(QBrush(linearGrad));
    painter.drawPath(circle_path);

    painter.setPen(QPen(Qt::black, 1.0));
    painter.drawLine(symbol1);

    painter.end();

    //Mode Clicked
    painter.begin(m_Clicked);

    painter.setPen(QPen(Qt::black, 0.3));
    painter.setBrush(QBrush(invertlinearGrad));
    painter.drawPath(circle_path);

    painter.setPen(QPen(Qt::black, 1.0));
    painter.drawLine(symbol1);

    painter.end();

}

void WindowButton::InitMaximize()
{
    QPainterPath circle_path;
    circle_path.addEllipse(QPointF(10,8), 8, 8);

    QPolygon square;

    square << QPoint(width() - 7, 4 )
           << QPoint(width() - 7, 11)
           << QPoint(6, 11)
           << QPoint(6, 4);


    QColor gradientStart(0, 0, 0, 0);
    QColor gradientEnd(0,0,0,220);

    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
    linearGrad.setColorAt(0, gradientStart);
    linearGrad.setColorAt(1, gradientEnd);

    QLinearGradient invertlinearGrad(QPointF(0,0), QPointF(0,height()));
    invertlinearGrad.setColorAt(0, gradientEnd);
    invertlinearGrad.setColorAt(1, gradientStart);

    QPainter painter;

    //Normal Mode
    painter.begin(m_Normal);

    painter.setPen(QPen(Qt::black, 0.3));
    painter.setBrush(QBrush(linearGrad));
    painter.drawPath(circle_path);

    painter.setPen(QPen(Qt::black, 1.0));
    painter.drawPolygon(square);

    painter.end();

    //Hovered Mode
    painter.begin(m_Hovered);

    painter.setPen(QPen(Qt::blue, 1.0));
    painter.setBrush(QBrush(linearGrad));
    painter.drawPath(circle_path);

    painter.setPen(QPen(Qt::black, 1.0));
    painter.drawPolygon(square);

    painter.end();

    //Clicked Mode
    painter.begin(m_Clicked);

    painter.setPen(QPen(Qt::black, 0.3));
    painter.setBrush(QBrush(invertlinearGrad));
    painter.drawPath(circle_path);

    painter.setPen(QPen(Qt::black, 1.0));
    painter.drawPolygon(square);

    painter.end();
}

void WindowButton::InitClose()
{
    QPainterPath circle_path;
    circle_path.addEllipse(QPointF(10,8), 8, 8);

    QColor gradientEnd(196,28,28);
    QColor gradientStart(0,0,0);

    QLinearGradient linearGrad(QPointF(0,0), QPointF(0,height()));
    linearGrad.setColorAt(1, gradientStart);
    linearGrad.setColorAt(0, gradientEnd);

    QLinearGradient invertlinearGrad(QPointF(0,0), QPointF(0,height()));
    invertlinearGrad.setColorAt(1, gradientEnd);
    invertlinearGrad.setColorAt(0, gradientStart);

    QPainter painter;

    //Normal Mode
    painter.begin(m_Normal);

    painter.setPen(QPen(Qt::black, 0.3));
    painter.setBrush(QBrush(linearGrad));
    painter.drawPath(circle_path);

    painter.setPen(QPen(QBrush(Qt::black),2.0));
    painter.drawPoint(10,8);

    painter.end();
    //Hovered Mode

    painter.begin(m_Hovered);

    painter.setPen(QPen(Qt::blue, 1.0));
    painter.setBrush(QBrush(linearGrad));
    painter.drawPath(circle_path);

    painter.setPen(QPen(QBrush(Qt::black),2.0));
    painter.drawPoint(10,8);

    painter.end();

    //Clicked Mode
    painter.begin(m_Clicked);

    painter.setPen(QPen(Qt::black, 0.3));
    painter.setBrush(QBrush(invertlinearGrad));
    painter.drawPath(circle_path);

    painter.setPen(QPen(QBrush(Qt::black),2.0));
    painter.drawPoint(10,8);

    painter.end();
}

void WindowButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_State = STATE_HOVERED;
    update();
}

void WindowButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_State = STATE_NORMAL;
    update();
}

void WindowButton::mousePressEvent(QMouseEvent *event)
{
    QAbstractButton::mousePressEvent(event);
    m_State = STATE_CLICKED;
    update();
}

void WindowButton::mouseReleaseEvent(QMouseEvent *event)
{
    QAbstractButton::mouseReleaseEvent(event);
    if(underMouse())
        m_State = STATE_HOVERED;
    else
        m_State = STATE_NORMAL;
    update();
}


