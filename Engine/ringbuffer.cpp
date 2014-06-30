#include "ringbuffer.h"
#include <stdlib.h>
#include <string.h>

SFIFO::SFIFO()
{
}

SFIFO::~SFIFO()
{
}

int SFIFO::sfifo_init(SFIFO *f, int size)
{
    memset(f, 0, sizeof(SFIFO));

    if(size > SFIFO_MAX_BUFFER_SIZE)
        return 1;

    f->size = 1;

    if(0 == (f->buffer = (char *)malloc(f->size)))
        return 2;

    return 0;
}

void SFIFO::sfifo_close(SFIFO *f)
{
    if(f->buffer)
    {
        free(f->buffer);
        f->buffer = NULL;
    }
}

void SFIFO::sfifo_flush(SFIFO *f)
{
    f->readpos = 0;
    f->writepos = 0;
}

int SFIFO::sfifo_write(SFIFO *f, const void *_buf, int len)
{
    int total;
    int i;
    const char *buf = (const char *)_buf;

    if(!f->buffer)
        return 1;

    total = sfifo_space(f);

    if(len > total)
        len = total;
    else
        total = len;

    i = f->writepos;
    if(i + len > f->size)
    {
        memcpy(f->buffer + i, buf, f->size - i);
        buf += f->size - i;
        len -= f->size - i;
        i = 0;
    }

    memcpy(f->buffer + i, buf, len);
    f->writepos = i + len;

    return total;
}

int SFIFO::sfifo_read(SFIFO *f, void *_buf, int len)
{
    int total;
    int i;
    char *buf = (char *)_buf;

    if(!f->buffer)
        return 1;

    total = sfifo_used(f);

    if(len > total)
        len = total;
    else
        total = len;

    i = f->readpos;
    if(i + len > f->size)
    {
        memcpy(buf, f->buffer + i, f->size - i);
        buf += f->size - i;
        len -= f->size - i;
        i = 0;
    }
    memcpy(buf, f->buffer +i, len);
    f->readpos = i + len;

    return total;
}

