#ifndef VIODEVICE_P_H
#define VIODEVICE_P_H

#include "vbytearray.h"
#include "viodevice.h"

class VIODeviceBuffer
{
public:
    VIODeviceBuffer() : len(0), first(0), buf(0), capacity(0) {}
    ~VIODeviceBuffer() { delete [] buf; }

    void clear() { delete [] buf; len = 0; }
    int size() const { return len; }
    bool isEmpty() const { return len == 0; }

    void skip(int n)
    {
	if( n >= len )
	    clear();
	else
	{
	    len -= n;
	    first += n;
	}
    }

    int read(char *target, int size)
    {
	memcpy(target, first, size);
	len -= size;
	first += size;
	return size;
    }

    bool canReadLine() const
    {
	return memchr(first, '\n', len);
    }

    int getChar()
    {
	if(len == 0)
	    return -1;
	int ch = *first;
	first ++;
	len -- ;
	return ch;
    }

    char *reserve(int size)
    {
	reallocData(size);
	return first;
    }

    void ungetChar(char c)
    {
	*(--first) = c;
	len++;
    }

private:
    void reallocData(size_t req)
    {
	if(req > capacity)
	{
	    char *nbuf = new char[req];
	    memcpy(nbuf, buf, len);
	    delete [] buf;
	    buf = nbuf;
	    first = buf;
	    capacity = req;
	}
	else
	    first = buf + (req - len);
    }

    int len;
    char *first;
    char *buf;
    size_t capacity;
};

class VIODevicePrivate
{
public:
    VIODevicePrivate(VIODevice *dev);
    virtual ~VIODevicePrivate();

    VIODeviceBuffer buffer;
    VByteArray errorString;

    VIODevice::OpenMode openMode;

    vint64 pos;

    VIODevice *v_ptr;
};

#endif
