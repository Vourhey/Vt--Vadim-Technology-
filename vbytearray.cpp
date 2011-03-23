#include <cstring>
#include <cctype>
#include "vbytearray.h"

int vstrcmp(const char *str1, const char *str2)
{
    return (str1 && str2) ? strcmp(str1, str2) :
	(str1 ? 1 : (str2 ? -1 : 0)); 
}

char *vstrcpy(char *dst, const char *str)
{
    return str ? strcpy(dst, str) : 0;
}

uint vstrlen(const char *str)
{
    return str ? strlen(str) : 0;
}

char *vstrdup(const char *str)
{
    if(!str) return 0;
    char *s = new char[vstrlen(str)+1];
    return vstrcpy(s, str);
}

int vstricmp(const char *str1, const char *str2)
{
    int l1 = vstrlen(str1);
    int l2 = vstrlen(str2);

    if(l1 != l2) return l1 - l2; 

    for(int i = 0; i <= l1; i++)
    {
	char c1 = toupper(str1[i]);
	char c2 = toupper(str2[i]);
	if(c1 != c2)
	    return (c1 - c2);
    }

    return 0; // они равны
}

int vstrncmp(const char *str1, const char *str2, uint len)
{
    return (str1 && str2) ? strncmp(str1, str2, len) :
	(str1 ? 1 : (str2 ? -1 : 0));
}

char *vstrncpy(char *dst, const char *str, uint len)
{
    return str ? strncpy(dst, str, len) : 0;
}

int vstrnicmp(const char *str1, const char *str2, uint len)
{
    int l1 = vstrlen(str1);
    int l2 = vstrlen(str2);

    if(l1 != l2) return l1 - l2;

    for(int i = 0; i<len; i++)
    {
	char c1 = toupper(str1[i]);
	char c2 = toupper(str2[i]);
	if(c1 != c2) return c1 - c2;
    }
    return 0; // они равны
}

uint vstrnlen(const char *str, uint maxlen)
{
    int len = vstrlen(str);
    if(len > maxlen) return maxlen;
    return len;
}

int vsnprintf(char *str, size_t n, const char *fmt, ... )
{
    va_list vl;
    va_start(vl, fmt);
    int r = vvsnprintf(str, n, fmt, vl);
    va_end(vl);
    return r;
}

int vvsnprintf(char *str, size_t n, const char *fmt, va_list ap)
{
    return fmt ? vsnprintf(str, n, fmt, ap) : 0;
}

// табличный (быстрый) расчет стандартного CRC-16
const unsigned short Crc16Table[256] = {
	0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
        0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
	0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
	0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
	0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
	0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
	0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
	0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
	0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
	0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
	0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
	0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
	0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
	0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
	0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
	0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
	0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
	0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
	0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
	0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
	0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
	0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
	0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
	0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
	0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
	0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
	0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
	0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
	0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
	0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
	0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
	0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 
};

vuint16 vChecksum(const char *data, uint len)
{
    unsigned short crc = 0xFFFF;

    while (len--)
	crc = (crc >> 8) ^ Crc16Table[(crc & 0xFF) ^ *data++];

    return crc;
}

void VByteArray::reallocData(int size)
{
    if(!d) // ещё не выделялась память
    {
	d = (Data*)malloc(sizeof(Data) + size);
	d->str = d->array;
	d->size = 0;
	d->alloc = size;
	d->str[0] = '\0';
    }
    else if(size > d->alloc)
    {
	Data *x = (Data*)malloc(sizeof(Data) + size);
	x->str = x->array;
	x->alloc = size;
	memcpy(x->str, d->str, d->size);
	x->size = d->size;
	free(d);
	d = x;
    }
    else
	d->size = size;
}

/*!
 * \class VByteArray
 */

/*!
 * \def VT_NO_CAST_FROM_BYTEARRAY
 * \relates VByteArray
 * Отменяет автоматическое преобразование в \c const \c char \c *
 * и \c const \c char \c *.
 */

VByteArray::VByteArray()
{
    d = 0;
    reallocData(0);
    d->isNull = true;
}

VByteArray::VByteArray(const char *str)
{
    d = 0;
    reallocData(vstrlen(str));
    d->size = vstrlen(str);
    memcpy(d->str, str, d->size);
    d->str[d->size] = '\0';
    d->isNull = false;
}

VByteArray::VByteArray(const char *data, int size)
{
    d = 0;
    reallocData(size + 1);
    memcpy(d->str, data, size);
    d->size = size+1;
    d->str[d->size] = '\0';
    d->isNull = false;
}

VByteArray::VByteArray(const VByteArray &other)
{
    d = 0;
    reallocData(other.d->size+1);
    d->size = other.d->size + 1;
    memcpy(d->str, other.d->str, other.d->size);
    d->str[d->size] = '\0';
    d->isNull = false;
}

VByteArray::VByteArray(int size, char _f)
{
    d = 0;
    fill(_f, size);
    d->isNull = false;
}

VByteArray::~VByteArray()
{
    free(d);
}

VByteArray &VByteArray::append(const char *str, int len)
{
    int olds = d->size;
    reallocData(d->size + len);
    memcpy(d->str+olds, str, len);
    d->str[d->size] = '\0';
    return *this;
}

VByteArray &VByteArray::append(char ch)
{
    reallocData(d->size + 1);
    d->str[d->size-1] = ch;
    d->str[d->size] = '\0';
    return *this;
}

bool VByteArray::contains(const char *str) const
{
    return (indexOf(str) != -1);
}

bool VByteArray::contains(char ch) const
{
    return (indexOf(ch) != -1);
}

int VByteArray::count(const char *str) const
{
    int c = 0;
    int pos = indexOf(str);

    while(pos != -1)
    {
	++c;
	pos = indexOf(str, pos+1);
    }

    return c;
}

int VByteArray::count(char ch) const
{
    int c = 0;

    for(int i=0; i<d->size; i++)
	if(d->str[i] == ch)
	    ++c;

    return c;
}

bool VByteArray::endsWith(const char *str) const
{
    int l = vstrlen(str);

    if(!vstrncmp(d->str+(d->size-l), str, l))
	return true;

    return false;
}

bool VByteArray::endsWith(char ch) const
{
    return (d->str[d->size-1] == ch);	
}

VByteArray &VByteArray::fill(char ch, int size)
{
    if(size == -1) size = d->size;
    reallocData(size);
    d->size = size;

    for(int i = 0; i<d->size; i++)
	d->str[i] = ch;
    d->str[d->size] = '\0';

    return *this;
}

int VByteArray::indexOf(const char *str, int from) const
{
    int l = vstrlen(str);

    for(int i = from; i < d->size; i++)
	if(!vstrncmp(d->str+i, str, l))
	    return i;

    return -1;
}

int VByteArray::indexOf(char ch, int from) const
{
    for(int i = from; i<d->size; i++)
	if(d->str[i] == ch)
	    return i;
    return -1;
}

VByteArray &VByteArray::insert(int i, const char *str, int len)
{
    int olds = d->size;
    reallocData(d->size + len);

    memmove(d->str+i+len, d->str+i, olds-i);
    memcpy(d->str+i, str, len);
    d->str[d->size] = '\0';

    return *this;
}

VByteArray &VByteArray::insert(int i, char ch)
{
    reallocData(d->size + 1);

    memmove(d->str+i+1, d->str+i, d->size-i-1);
    d->str[i] = ch;
    d->str[d->size] = '\0';

    return *this;
}

int VByteArray::lastIndexOf(const char *str, int from) const
{
    if(from == -1) from = d->size-1;
    int l = vstrlen(str);

    for(int i = from; i > -1; i--)
	if(!vstrncmp(d->str+i, str, l))
	    return i;

    return -1;
}

int VByteArray::lastIndexOf(char ch, int from) const
{
    if(from == -1) from = d->size - 1;

    for(int i = from; i > -1; i--)
	if(d->str[i] == ch)
	    return i;

    return -1;
}

VByteArray &VByteArray::prepend(const char *str, int len)
{
    reallocData(d->size + len);
    memmove(d->str+len, d->str, d->size-len);
    memcpy(d->str, str, len);
    d->str[d->size] = '\0';
    return *this;
}

VByteArray &VByteArray::prepend(char ch)
{
    reallocData(d->size + 1);
    memmove(d->str+1, d->str, d->size-1);
    d->str[0] = ch;
    d->str[d->size] = '\0';
    return *this;
}

// алгоритм перевода в Base64 взят с Wikipedia
VByteArray VByteArray::toBase64() const
{
    const char *alphabit = "ABCDEFGHI" "JKLMNOPQR" "STUVWXYZa"
	    "bcdefghij" "klmnopqrs" "tuvwxyz" "0123456789+/";
    int pchar = '=';
    int plen = 0;

    VByteArray tmp(d->size+4);
    char *out = tmp.data();

    int i = 0;
    while(i < d->size)
    {
	int charout = 0;
	charout |= int(uchar(d->str[i++])) << 16;
	if(i == d->size) plen = 2;
	else
	{
	    charout |= int(uchar(d->str[i++])) << 8;
	    if(i == d->size) plen = 1;
	    else charout |= int(uchar(d->str[i++]));
	}

	int j = (charout & 0x00fc0000) >> 18; // берем старшие 6 бит
	int l = (charout & 0x0003f000) >> 12; // следующие 6
	int k = (charout & 0x00000fc0) >> 6; 
	int m = (charout & 0x0000003f);

	*out++ = alphabit[j];
	*out++ = alphabit[l];
	if(plen > 1) *out++ = pchar;
	else *out++ = alphabit[k];
	if(plen > 0) *out++ = pchar;
	else *out++ = alphabit[m];
    }

    return tmp;
}

bool VByteArray::startsWith(const char *str) const
{
    return !vstrncmp(d->str, str, vstrlen(str));
}

bool VByteArray::startsWith(char ch) const
{
    return d->str[0] == ch;
}

VByteArray &VByteArray::remove(int pos, int len)
{
    memmove(d->str+pos, d->str+pos+len, d->size-pos-len);
    reallocData(d->size-len);
    d->str[d->size] = '\0';
    return *this;
}

VByteArray VByteArray::repeated(int times) const
{
    VByteArray tmp(times * d->size);

    while(times--)
	tmp.append(d->str);

    tmp.d->str[tmp.d->size] = '\0';
    return tmp;
}
