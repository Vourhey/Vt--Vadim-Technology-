#include "viodevice.h"
#include "private/viodevice_p.h"

VIODevicePrivate::VIODevicePrivate(VIODevice *dev)
    : openMode(VIODevice::NotOpen), pos(0), v_ptr(dev)
{
}

VIODevicePrivate::~VIODevicePrivate()
{}

VIODevice::VIODevice()
{
    d = new VIODevicePrivate(this);
}

VIODevice::~VIODevice()
{}

bool VIODevice::atEnd() const
{
    return d->openMode == NotOpen || (d->pos == size());
}

bool VIODevice::canReadLine() const
{
    return d->buffer.canReadLine();
}

bool VIODevice::open(OpenMode mode)
{
    close();
    d->openMode = mode;
    return true;
}

void VIODevice::close()
{
    d->openMode = NotOpen;
    d->buffer.clear();
    d->pos = 0;
    d->errorString.clear();
}

bool VIODevice::getChar(char *c)
{
    if(readData(c, 1) != 1)
	 return false;
    return true;
}

bool VIODevice::putChar(char c)
{
    if(writeData(&c, 1) != 1)
	return false;
    return true;
}

void VIODevice::ungetChar(char c)
{
    d->buffer.ungetChar(c); 
}

bool VIODevice::isOpen() const
{
    return d->openMode != NotOpen;
}

bool VIODevice::isReadable() const
{
    return d->openMode & ReadOnly;
}

bool VIODevice::isTextModeEnabled() const
{
    return d->openMode & Text;
}

bool VIODevice::isWritable() const
{
    return d->openMode & WriteOnly;
}

VIODevice::OpenMode VIODevice::openMode() const
{
    return d->openMode;
}

void VIODevice::setTextModeEnabled(bool enabled)
{
    if(enabled)
	d->openMode |= Text;
    else
	d->openMode &= ~Text;

}

VByteArray VIODevice::errorString() const
{
    return d->errorString;
}

void VIODevice::setErrorString(const VByteArray &str)
{
    d->errorString = str;
}

void VIODevice::setOpenMode(OpenMode openMode)
{
    d->openMode = openMode;
    d->pos = 0;
}

vint64 VIODevice::pos() const
{
    return d->pos;
}

vint64 VIODevice::size() const
{
    return vint64(0);
}

vint64 VIODevice::write(const char *data, vint64 maxSize)
{
    if(!data) return 0;

    vint64 len = vMax(vint64(vstrlen(data)), maxSize);
    vint64 w = writeData(data, len);
    d->pos += w;
    return w;    
}

vint64 VIODevice::read(char *data, vint64 maxSize)
{
    if(!data) return vint64(0);
    
    vint64 r = readData(data, maxSize);
    d->pos -= r;
    return r;
}

VByteArray VIODevice::read(vint64 maxSize)
{
    VByteArray ret;
    ret.reserve(maxSize);
    readData(ret.data(), maxSize);
    return ret;
}

VByteArray VIODevice::readAll()
{
    VByteArray ret;
    ret.reserve(size());
    readData(ret.data(), size());
    return ret;
}

