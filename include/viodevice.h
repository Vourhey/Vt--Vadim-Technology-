#ifndef VIODEVICE_H
#define VIODEVICE_H

#include "vglobal.h"
#include "vbytearray.h"

class VIODevicePrivate;

class VIODevice
{
public:
    enum OpenModeFlag
    {
	NotOpen = 0x0000,
	ReadOnly = 0x0001,
	WriteOnly = 0x0002,
	ReadWrite = ReadOnly | WriteOnly,
	Append = 0x0004,
	Truncate = 0x0008,
	Text = 0x0010
    };
    V_DECLARE_FLAGS(OpenMode, OpenModeFlag)

    VIODevice();
    virtual ~VIODevice();

    virtual bool atEnd() const;
    virtual bool canReadLine() const;

    virtual void close();

    virtual bool open(OpenMode mode);

    VByteArray errorString() const;

    bool isOpen() const;
    bool isReadable() const;
    bool isTextModeEnabled() const;
    bool isWritable() const;

    OpenMode openMode() const;
    void setTextModeEnabled(bool enabled);

    virtual vint64 pos() const;
    virtual vint64 size() const;

    bool getChar(char *c);
    bool putChar(char c);
    void ungetChar(char c);

    vint64 read(char *data, vint64 maxSize);
    VByteArray read(vint64 maxSize);
    VByteArray readAll();

    vint64 write(const char *data, vint64 maxSize);
    inline vint64 write(const char *data) 
        { return write(data, vstrlen(data)); }
    inline vint64 write(const VByteArray &byteArray) 
        { return write(byteArray.constData(), byteArray.size()); }

protected:
    VIODevice(VIODevicePrivate *dd) : d(dd) {}
    VIODevicePrivate *d;

    virtual vint64 readData(char *data, vint64 maxSize) = 0;
    virtual vint64 writeData(const char *data, vint64 maxSize) = 0;

    void setErrorString(const VByteArray &str);
    void setOpenMode(OpenMode openMode);
};

V_DECLARE_OPERATORS_FOR_FLAGS(VIODevice::OpenMode)

#endif
