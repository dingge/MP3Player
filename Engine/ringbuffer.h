#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#define SFIFO_MAX_BUFFER_SIZE 0x7FFFFFFF
#define SFIFO_SIZEMASK(x)   ((x)->size - 1)
#define sfifo_used(x)       (((x)->writepos - (x)->readpos) & SFIFO_SIZEMASK(x))
#define sfifo_space(x)      ((x)->size - 1 - sfifo_used(x))
#define sfifo_size(x)       ((x)->size - 1)

typedef int sfifo_atomic_t;

class SFIFO
{
public:
    SFIFO();
    ~SFIFO();
    char *buffer;
    int size;
    sfifo_atomic_t readpos;
    sfifo_atomic_t writepos;
    int sfifo_init(SFIFO *f, int size);
    void sfifo_close(SFIFO *f);
    void sfifo_flush(SFIFO *f);
    int sfifo_write(SFIFO *f, const void *buf, int len);
    int sfifo_read(SFIFO *f, void *buf, int len);

};

#endif // RINGBUFFER_H
