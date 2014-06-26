#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <QAudioFormat>
#include <QIODevice>
#include <QMutex>

class AudioBuffer : public QIODevice
{
    Q_OBJECT
public:
    struct block
    {
        char * ptr;
        qint64 len;
        int    index;
    };
//----------------------------------------------------------------------------------------------------------------------------------
    AudioBuffer(/*const QAudioFormat &format,*/ QObject *parent = NULL) :   QIODevice(parent)
    {
//         const char * someData = "12MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWQuhaSSSSSSSSSSSSSSSSSSSSSSSSSSss";
//         writeData(someData,sizeof(someData));
    }
//----------------------------------------------------------------------------------------------------------------------------------
    ~AudioBuffer()
    {
        clear();
    }
//----------------------------------------------------------------------------------------------------------------------------------
    void start()
    {
        if(!isOpen())
            open(QIODevice::ReadWrite);
    }
//----------------------------------------------------------------------------------------------------------------------------------
    void stop()
    {
        close();
    }
//----------------------------------------------------------------------------------------------------------------------------------
    qint64 readData(char * data, qint64 maxlen)
    {
        QMutexLocker mutexLocker(&m_mutex);

        start();

        if(m_buffer.isEmpty())
            return 0;

        int length = maxlen;

        int size = 0;

        while (m_buffer.isEmpty() == false) {
            block bl = m_buffer.at(0);

            if (bl.len <= length) {
                memcpy(data+size, bl.ptr, bl.len);
                m_buffer.removeAt(0);
                delete [] bl.ptr;
                length -= bl.len;
                size += bl.len;
                continue;
            }

            memcpy(data+size, bl.ptr, length);
            bl.len -= length;
            m_buffer[0] = bl;
            memcpy(bl.ptr, bl.ptr+length, bl.len);
            size += length;
            length = 0;
            break;
        }
        if (length > 0)
            memset(data + (maxlen - length), 0xCC, length);

        return maxlen;
    }
//----------------------------------------------------------------------------------------------------------------------------------
    qint64 writeData(const char *data, qint64 len)
    {

        QMutexLocker mutexLocker(&m_mutex);

        start();

        char * ptr = new char[len];
        memcpy(ptr,data,len);
        block bl;
        bl.ptr = ptr;
        bl.len = len;
        m_buffer.append(bl);

        return len;
    }
//----------------------------------------------------------------------------------------------------------------------------------
    void clear(){
        QMutexLocker mutexLocker(&m_mutex);

        for(int i = 0; i<m_buffer.count(); i++)
        {
            block bl = m_buffer.at(i);

            delete [] bl.ptr;
        }

        m_buffer.clear();
    }
//----------------------------------------------------------------------------------------------------------------------------------
private:
    QList<block> m_buffer;
    QMutex  m_mutex;
};

#endif//AUDIOBUFFER_H
