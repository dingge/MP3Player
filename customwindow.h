#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H
#include <QtWidgets>
#include <QTabWidget>
#include <QGridLayout>
#include <QList>
#include <QSizeGrip>
#include "windowtitlebar.h"
#include "musicplayer.h"
#include "playlist.h"
#include "audioplayer.h"

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
        void formatWidget();
        QGridLayout m_MainLayout;
        WindowTitleBar m_TitleBar;
        PlayList m_PlayList;
        MusicPlayer m_MusicPlayer;
        QTabWidget m_TabWindow;
        QSizeGrip m_SizeGrip;
        AudioPlayer m_AudioPlayer;

signals:
        void windowTitleChanged();

public slots:
        void updateSong(QTreeWidgetItem*);
        void updateBuffer();
};

#endif
