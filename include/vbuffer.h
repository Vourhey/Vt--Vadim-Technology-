#ifndef VBUFFER_H
#define VBUFFER_H

#include "viodevice.h"

class VByteArray;

class VBuffer : public VIODevice
{
public:
    VBuffer();
    VBuffer(VByteArray *byteArray);
    ~VBuffer();

    VByteArray &buffer();
    const VByteArray &buffer() const;
    const VByteArray &data() const;

    void setBuffer(VByteArray *byteArray);
    void setData(const VByteArray &data);
    void setData(const char *data, int size);

    bool atEnd() const;
    bool canReadLine() const;

    void close();
    bool open(OpenMode flags);
    vint64 pos() const;
    bool seek(vint64 pos);
    vint64 size() const;

protected:
    vint64 readData(char *data, vint64 maxSize);
    vint64 writeData(const char *data, vint64 maxSize);
};

#endif
