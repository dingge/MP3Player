#include <QWidget>
#include "playlist.h"


PlayList::PlayList(QWidget *parent) :
    QWidget(parent),
    m_SongList(0),
    m_PlayLayout(0)
{
    resize(100,100);
    addSongs(&m_SongList);
    m_PlayLayout.addWidget(&m_SongList,0,0,1,1);
    setLayout(&m_PlayLayout);
}

PlayList::~PlayList()
{

}

void PlayList::addSongs(QListWidget *songs)
{
    for(int i = 0; i < 9; i++)
    {
        songs->addItem(QString::number(i));
    }
}
