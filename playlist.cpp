#include <QWidget>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QMenu>
#include <QModelIndex>
#include "playlist.h"
#include "tag.h"
#include "fileref.h"

#include <QAudioOutput>

PlayList::PlayList(QWidget *parent)
{
    Q_UNUSED(parent);
    QStringList headers;
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint)), SLOT(showContextMenu()));

    headers << "Name" << "Duration" << "Album" << "Artist";
    setHeaderLabels(headers);
    setIndentation(1);
    addSongs("C:/Users/Public/Music/Sample Music/Kalimba.mp3");
    addSongs("C:/Users/Public/Music/Sample Music/Sleep Away.mp3");
    addSongs("C:/Users/Public/Music/Sample Music/Maid with the Flaxen Hair.mp3");
}

PlayList::~PlayList()
{

}

void PlayList::addSongs(QString path)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    TagLib::FileRef f(path.toStdWString().c_str());
    QString duration;

    if(!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        int min = f.audioProperties()->length() / 60;
        int sec = f.audioProperties()->length() - min * 60;
        if(sec < 10)
            duration = QString::number(min) + ":0" + QString::number(sec);
        else
            duration = QString::number(min) + ":" + QString::number(sec);

        item->setTextAlignment(0,Qt::AlignLeft);
        item->setText(0, TStringToQString(tag->title()));
        item->setData(0,4,path);
        item->setText(1, duration);
        item->setText(2, TStringToQString(tag->album()));
        item->setText(3, TStringToQString(tag->artist()));
    }

    addTopLevelItem(item);
}

QString PlayList::getSelectedSong()
{
    QTreeWidgetItem *item = currentItem();
    QString song = item->data(0, 4).toString();
    qDebug() << song;
    return(song);
}

void PlayList::showContextMenu()
{
    QModelIndex index = this->currentIndex();

    QMenu *menu = new QMenu(this);
    menu->addAction(new QAction("Play", this));
    menu->addAction(new QAction("Edit", this));
    menu->addAction(new QAction("Delete", this));
    menu->exec(QCursor::pos());
}
