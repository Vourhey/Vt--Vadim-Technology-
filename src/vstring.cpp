#include "vstring.h"
#include "vbytearray.h"

VLatin1String::VLatin1String(const char *str)
{
    data = str;
}

const char *VLatin1String::latin1() const
{
    return data;
}

VLatin1String &VLatin1String::operator=(const VLatin1String &other)
{
    data = other.data;
    return *this;
}

#define null VChar(VChar::Null)

int vustrlen(const VChar *u)
{
    int l = 0;
    while(*u++ != null)
	++l;
    return l;
}

int vustrcmp(const VChar *s1, int len1, const VChar *s2, int len2)
{
    if(len1 != len2) return len1 - len2;

    while(*s1 != null)
    {
	if(*s1 != *s2) return (*s1).unicode() - (*s2).unicode();
	++s1;
	++s2;
    }

    return 0;
}

int vustricmp(const VChar *s1, int len1, const VChar *s2, int len2)
{
    if(len1 != len2) return len1 - len2;

    VChar ch1 = *s1;
    VChar ch2 = *s2;

    while(ch1 != null)
    {
	if(ch1.toUpper() != ch2.toUpper())
	    return ch1.unicode() - ch2.unicode();
	ch1 = *++s1;
	ch2 = *++s2;
    }

    return 0;
}

int vustrncmp(const VChar *s1, const VChar *s2, int n)
{
    VChar ch1 = *s1;
    VChar ch2 = *s2;
    while(n-- > 0)
    {
	if(ch1 != ch2)
	   return ch1.unicode() - ch2.unicode();
	ch1 = *++s1;
	ch2 = *++s2;
    }
    return 0;
}

int vustrincmp(const VChar *s1, const VChar *s2, int n)
{
    VChar ch1 = *s1;
    VChar ch2 = *s2;

    while(n-- > 0)
    {
	if(ch1.toUpper() != ch2.toUpper())
	    return ch1.unicode() - ch2.unicode();
	ch1 = *++s1;
	ch2 = *++s2;
    }

    return 0;
}

VString::Data VString::shared_null = {0, 0, shared_null.array, {0}};

void VString::reallocData(int size)
{
    if(!d || d == &shared_null)
    {
	d = (Data*)malloc(sizeof(Data)+size*sizeof(VChar));
	d->_s = 0;
	d->_alloc = size;
	d->data = d->array;
    }
    else if(size > d->_alloc)
    {
	Data *x = (Data*)malloc(sizeof(Data)+size*sizeof(VChar));
	x->_s = d->_s;
	x->_alloc = size;
	x->data = x->array;
	memcpy(x->data, d->data, sizeof(VChar)*d->_s);

	free(d);
	d = x;
    }
}

VString::VString()
    : d(&shared_null)
{
}

VString::VString(const VChar *unicode, int size)
{
    d = 0;
    reallocData(size);
    d->_s = size;
    for(int i =0; i<=size; ++i)
	d->data[i] = unicode[i];
}

VString::VString(const VChar *unicode)
{
    d = 0;
    int len = vustrlen(unicode);
    reallocData(len);
    d->_s = len;
    memcpy(d->data, unicode, sizeof(VChar)*len);
}

VString::VString(VChar ch)
{
    d = 0;
    reallocData(1);
    d->_s = 1;
    d->data[0] = ch;
}

VString::VString(int size, VChar ch)
{
    d = 0;
    reallocData(size);
    d->_s = size;

    while(size != 0) d->data[size--] = ch;
}

VString::VString(const VLatin1String &str)
{
    d = 0;
    int len = vstrlen(str.latin1());
    reallocData(len);
    d->_s = len;
    
    for(int i=0; i<=len; ++i)
	d->data[i] = VChar(str.latin1()[i]);
}

VString::VString(const VString &other)
{
    d = 0;
    reallocData(other.d->_s);
    d->_s = other.d->_s;

    for(int i = 0; i<=d->_s; ++i)
	d->data[i] = other.d->data[i];
}

VString::VString(const char *str)
{
    d = 0;
    reallocData(vstrlen(str));
    d->_s = vstrlen(str);

    for(int i = 0; i<=d->_s; ++i)
	d->data[i] = VChar(str[i]);
}

VString::VString(const VByteArray &ba)
{
    d = 0;
    reallocData(ba.size());
    d->_s = ba.size();

    for(int i = 0; i<=d->_s; ++i)
	d->data[i] = VChar(ba[i]);
}

VString::~VString()
{
    clear();
}

VString &VString::append(const VString &str)
{
    int old = d->_s;
    reallocData(d->_s + str.d->_s);
    d->_s += str.d->_s;

    memcpy(d->data+old, str.d->data, sizeof(VChar)*str.d->_s);
    return *this;
}

VString &VString::append(const VLatin1String &str)
{
    uint old = d->_s;
    reallocData(d->_s + vstrlen(str.latin1()));
    d->_s += vstrlen(str.latin1());

    for(uint i = 0; i<=vstrlen(str.latin1()); ++i)
	d->data[i+old] = VChar(str.latin1()[i]);
    return *this;
}

VString &VString::append(const VByteArray &ba)
{
    int old = d->_s;

    reallocData(old + ba.size());
    d->_s += ba.size();

    for(int i = 0; i<=ba.size(); ++i)
	d->data[i+old] = VChar(ba[i]);
    return *this;
}

VString &VString::append(VChar ch)
{
    reallocData(++d->_s);

    d->data[d->_s-1] = ch;
    d->data[d->_s] = null;
    return *this;
}

VByteArray VString::toLatin1() const
{
    VByteArray ba;
    ba.reserve(d->_s);

    for(int i=0; i<=d->_s; ++i)
	ba[i] = d->data[i].toLatin1();
    return ba;
}

VByteArray VString::toAscii() const
{
    return toLatin1();
}

VByteArray VString::toLocal8Bit() const
{
    return toLatin1();
}

const VChar VString::at(int position) const
{
    if(position < 0 || position > d->_s)
    {
	vWarning("VString::at(): position за пределами строки %d", position);
	return VChar();
    }
    return d->data[position];
}

void VString::chop(int n)
{
    if(n < 0 || n > d->_s)
    {
	vWarning("VString::chop(): n равна %d", n);
	n = d->_s;
    }
    d->_s -= n;
}

void VString::clear()
{
    free(d);
    d = &shared_null;
}

int VString::compare(const VString &s1, const VString &s2, Vt::CaseSensitivity cs)
{
    if(cs == Vt::CaseInsensitive)
	return vustricmp(s1.d->data, s1.d->_s, s2.d->data, s2.d->_s);
    
    return vustrcmp(s1.d->data, s1.d->_s, s2.d->data, s2.d->_s);
}

int VString::compare(const VString &s1, const VLatin1String &s2, Vt::CaseSensitivity cs)
{
    VByteArray ba = s1.toLatin1();

    if(cs == Vt::CaseInsensitive)
	return vstricmp(ba.constData(), s2.latin1());

    return vstrcmp(ba.constData(), s2.latin1());
}

int VString::compare(const VLatin1String &s1, const VString &s2, Vt::CaseSensitivity cs)
{
    VByteArray ba = s2.toLatin1();

    if(cs == Vt::CaseInsensitive)
	return vstricmp(s1.latin1(), ba.constData());

    return vstrcmp(s1.latin1(), ba.constData());
}

int VString::indexOf(const VString &str, int from, Vt::CaseSensitivity cs) const
{
    for(int i = from; i<=d->_s; ++i)
    {
	if(cs == Vt::CaseInsensitive)
	    if(!vustrincmp(d->data+i, str.d->data, str.d->_s))
		return i;
	if(!vustrncmp(d->data+i, str.d->data, str.d->_s))
	    return i;
    }
    return -1;
}

int VString::indexOf(const VLatin1String &str, int from, Vt::CaseSensitivity cs) const
{
    const char *t1 = toLatin1().data();
    const char *t2 = str.latin1();
    int len = vstrlen(t2);

    for(int i = from; i<=d->_s; ++i)
    {
	if(cs == Vt::CaseInsensitive)
	    if(!vstrnicmp(t1+i, t2, len))
		return i;
	if(!vstrncmp(t1+i, t2, len))
	    return i;
    }
    return -1;
}

int VString::indexOf(VChar ch, int from, Vt::CaseSensitivity cs) const
{
    for(int i=from; i<=d->_s; ++i)
    {
	if(cs == Vt::CaseInsensitive)
	    if(d->data[i].toUpper() == ch.toUpper())
		return i;
	if(d->data[i] == ch)
	    return i;
    }
    return -1;
}

VString &VString::fill(VChar ch, int size)
{
    if(size == -1) size = d->_s;
    reallocData(size);
    d->_s = size;

    while(size--) d->data[size] = ch;
    return *this;
}

bool VString::contains(const VString &str, Vt::CaseSensitivity cs) const
{
    return indexOf(str, 0, cs) != -1;
}

bool VString::contains(VChar ch, Vt::CaseSensitivity cs) const
{
    return indexOf(ch, 0, cs) != -1;
}

int VString::count(const VString &str, Vt::CaseSensitivity cs) const
{
    int c = 0;
    int pos = indexOf(str, 0, cs);

    while(pos != -1)
    {
	++c;
	pos = indexOf(str, pos+1, cs);
    }

    return c;
}

int VString::count(VChar ch, Vt::CaseSensitivity cs) const
{
    int c = 0;
    int pos = indexOf(ch, 0, cs);

    while(pos != -1)
    {
	++c;
	pos = indexOf(ch, pos + 1, cs);
    }

    return c;
}

VChar &VString::operator[](int position)
{
    V_ASSERT(position>0||position<=d->_s);

    return d->data[position];
}

VChar &VString::operator[](uint position)
{
    V_ASSERT(position<=static_cast<uint>(d->_s));

    return d->data[position];
}

const VChar VString::operator[](int position) const
{
    if(position<0 || position>d->_s)
    {
	vWarning("VString::operator[]: position вне строки %d", position);
	return VChar();
    }

    return d->data[position];
}

const VChar VString::operator[](uint position) const
{
    if(position>static_cast<uint>(d->_s))
    {
	vWarning("VString::operator[]: position вне строки %d", position);
	return VChar();
    }

    return d->data[position];
}

VString::operator const char *() const
{
    return toLatin1().constData();
}

bool VString::endsWith(const VString &s, Vt::CaseSensitivity cs) const
{
    int p = d->_s - s.d->_s;

    if(cs == Vt::CaseInsensitive)
	return (!vustricmp(d->data+p, s.d->_s, s.d->data, s.d->_s));

    return !vustrcmp(d->data+p, s.d->_s, s.d->data, s.d->_s);
}

bool VString::endsWith(const VLatin1String &s, Vt::CaseSensitivity cs) const
{
    int p = d->_s - vstrlen(s.latin1());

    if(cs == Vt::CaseInsensitive)
	return !vstricmp(*this+p, s.latin1());

    return !vstrcmp(*this+p, s.latin1());
}

bool VString::endsWith(const VChar &c, Vt::CaseSensitivity cs) const
{
    if(cs == Vt::CaseSensitive)
	return d->data[d->_s].toUpper() == c.toUpper();

    return d->data[d->_s] == c;
}
