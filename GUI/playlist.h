#ifndef PLAYLIST_H
#define PLAYLIST_H

//Potentially use QTreeWidget instead of QListWidget

#include <QWidget>
#include <QTableView>
#include <QTreeWidget>

class PlayList: public QTreeWidget
{
    Q_OBJECT

public:
    PlayList(QWidget *parent);
    ~PlayList();
    void addSongs(QString song);
    QString getSelectedSong();

private:
    //void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);

protected:

public slots:
    void showContextMenu();

};

#endif // TABWINDOW_H
