#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H
#include <QtWidgets>
#include <QTabWidget>
#include <QGridLayout>
#include "windowtitlebar.h"
#include "musicplayer.h"

class CustomWindow : public QWidget
{
    Q_OBJECT

public:
        CustomWindow(QWidget * parent = 0);
        ~CustomWindow();
        void setWindowTitle(const QString &title);

protected:
        void showEvent(QShowEvent *event);
        void paintEvent(QPaintEvent *event);

private:
        void CenterOnScreen();
        QGridLayout m_MainLayout;
        WindowTitleBar m_TitleBar;
        MusicPlayer m_MusicPlayer;
        QTabWidget m_TabWindow;
        QPixmap m_Cache;

signals:
        void windowTitleChanged();
};

#endif
