#include "vbuffer.h"
#include "private/viodevice_p.h"

#define d_f() static_cast<VBufferPrivate*>(d)

class VBufferPrivate : public VIODevicePrivate
{
public:
    VBufferPrivate(VIODevice *dev) : VIODevicePrivate(dev), ba(&defaultBuf) {}

    VByteArray *ba;
    VByteArray defaultBuf;
};

/*!
 * \class VBuffer
 * \brief Реализует VIODevice интерфейс для VByteArray
 *
 * VBuffer позволяет вам записывать/читать VByteArray, используя
 * VIODevice интерфейс. При этом VByteArray выглядит как обычный
 * файл со случайным доступом. Пример:
 * \code
 * VBuffer buffer;
 * char ch;
 *
 * buffer.open(VBuffer::ReadWrite);
 * buffer.write("Vt is great!");
 * buffer.seek(0);
 * buffer.getChar(&ch);  // ch == 'V'
 * buffer.getChar(&ch);  // ch == 't'
 * buffer.getChar(&ch);  // ch == ' '
 * buffer.getChar(&ch);  // ch == 'i'
 * \endcode
 *
 * По умолчанию, создается собственный VByteArray для каждого VBuffer.
 * Вы можете получить его, используя buffer(). Но вы можете установить
 * собственный VByteArray, используя setBuffer() или при создании VBuffer.
 */

VBuffer::VBuffer()
    : VIODevice(new VBufferPrivate(this))
{
}

VBuffer::VBuffer(VByteArray *byteArray)
    : VIODevice(new VBufferPrivate(this))
{
    if(byteArray)
	d_f()->ba = byteArray;
}

VBuffer::~VBuffer()
{
    delete d;
}

VByteArray &VBuffer::buffer()
{
    return *d_f()->ba;
}

const VByteArray &VBuffer::buffer() const
{
    return *d_f()->ba;
}

const VByteArray &VBuffer::data() const
{
    return *d_f()->ba;
}

void VBuffer::setBuffer(VByteArray *byteArray)
{
    d_f()->ba = byteArray ? byteArray : &d_f()->defaultBuf;
    d_f()->defaultBuf.clear();
    d_f()->pos = 0;
}

void VBuffer::setData(const VByteArray &data)
{
    *d_f()->ba = data;
    d_f()->defaultBuf.clear();
    d_f()->pos = 0;
}

void VBuffer::setData(const char *data, int size)
{
    d_f()->ba = new VByteArray(data, size);
    d_f()->defaultBuf.clear();
    d_f()->pos = 0;
}

bool VBuffer::atEnd() const
{
    return d_f()->ba->isEmpty() || d_f()->pos == d_f()->ba->size();
}

bool VBuffer::canReadLine() const
{
    return d_f()->ba->contains('\n');
}

void VBuffer::close()
{
    VIODevice::close();
}

bool VBuffer::open(OpenMode flags)
{
    if(flags & Append)
	flags |= WriteOnly;

    setOpenMode(flags);
    if(!(isReadable() || isWritable()))
    {
	vWarning("VBuffer: неизвестный способ доступа к файлу");
	return false;
    }

    if(flags & Truncate)
    {
	d_f()->ba->clear();
	d_f()->pos = 0;
    }
    if(flags & Append)
	seek(d_f()->ba->size());
    else
	seek(0);
    return true;
}

vint64 VBuffer::pos() const
{
    return d_f()->pos;
}

bool VBuffer::seek(vint64 pos)
{
    if(pos < 0 || pos > size())
    {
	vWarning("VBuffer: недействительная позиция %d", pos);
	return false;
    }
    d_f()->pos = pos;
    return true;
}

vint64 VBuffer::size() const
{
    return d_f()->ba->size();
}

vint64 VBuffer::readData(char *data, vint64 maxSize)
{
    if(maxSize > size())
	maxSize = size();

    memcpy(data, d_f()->ba->data()+d->pos, maxSize);
//    data[maxSize] = '\0';
    return maxSize;
}

vint64 VBuffer::writeData(const char *data, vint64 maxSize)
{
    d_f()->ba->insert(d->pos, data, maxSize);
    return maxSize;
}

