#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QListWidget>
#include <QGridLayout>

class PlayList: public QWidget
{
    Q_OBJECT

public:
    PlayList(QWidget *parent);
    ~PlayList();
    void addSongs(QListWidget *songs);

private:
    QListWidget m_SongList;
    QGridLayout m_PlayLayout;

protected:

};

#endif // TABWINDOW_H
