#ifndef WINDOWTITLEBAR_H
#define WINDOWTITLEBAR_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>
#include "windowbutton.h"

class WindowTitleBar : public QWidget
{
    Q_OBJECT

public:
    WindowTitleBar(QWidget * Parent = 0);
    ~WindowTitleBar();

protected:
    void resizeEvent(QResizeEvent * event);
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QGridLayout m_SubLayout;
    QPixmap * m_Cache;
    QLabel m_Title;
    WindowButton m_Minimize;
    WindowButton m_Maximize;
    WindowButton m_Close;
    QPoint m_Diff;

public slots:
    void updateWindowTitle();
    void Minimized();
    void Maximized();
    void Quit();
};

#endif // WINDOWTITLEBAR_H
