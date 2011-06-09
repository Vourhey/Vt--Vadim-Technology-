#include "vstring.h"
#include "vbytearray.h"
#include "vstringlist.h"

/*!
 * \class VLatin1String
 * \brief Класс для удобного представления строки в US-ASCII/Latin-1 кодировки.
 *
 * Многие функции VString используют этот класс для представления <tt>const char *</tt>.
 * Класс включает конструктор копий, функции доступа и операторы сравнения строк.
 * Этот класс оптимизирует создание VString для <tt>const char *</tt> объектов. Например:
 * \code
 * if(str == "auto" || str == "extern" || 
 *    str == "static" || str == "register")
 * {
 *     ... 
 * }
 * \endcode
 * более быстрое чем
 * \code
 * if (str == VString("auto") || str == VString("extern") || 
 *     str == VString("static") || str == VString("register")) 
 * {
 *      ...
 * }
 * \endcode
 * так как не создаются временные объекты VString.
 * \see VString и VLatin1Char
 */

/*!
 * Создает объект VLatin1String для хранения \a str. Помните, что
 * данные из \a str не копируются. При инициализации вы должны гарантировать,
 * что строка не будет удалена или измененна пока VLatin1String существует.
 * \see latin1()
 */
VLatin1String::VLatin1String(const char *str)
{
    data = str;
}

/*!
 * Возвращает строку Latin-1, хранящуюся в этом объекте.
 */
const char *VLatin1String::latin1() const
{
    return data;
}

/*!
 * Конструктор копий для \a other.
 */
VLatin1String &VLatin1String::operator=(const VLatin1String &other)
{
    data = other.data;
    return *this;
}

/*!
 * Возвращает \c true, если строка не равна \a other. Иначе \c false.
 */
bool VLatin1String::operator!=(const VString &other) const
{
    return VString::compare(*this, other);
}

/*! \overload  */
bool VLatin1String::operator!=(const char *other) const
{
    return vstrcmp(data, other);
}

/*!
 * Возвращает \c true, если строка меньше \a other. Иначе \c false.
 */
bool VLatin1String::operator<(const VString &other) const
{
    return VString::compare(*this, other) < 0;
}

/*! \overload */
bool VLatin1String::operator<(const char *other) const
{
     return vstrcmp(data, other) < 0;
}

/*!
 * Возвращает \c true, если строка меньше или равна \a other. Иначе \c false.
 */
bool VLatin1String::operator<=(const VString &other) const
{
    return VString::compare(*this, other) <= 0;
}

/*! \overload */
bool VLatin1String::operator<=(const char *other) const
{
    return vstrcmp(data, other) <= 0;
}

/*!
 * Возвращает \c true, если строка равна \a other. Иначе \c false.
 */
bool VLatin1String::operator==(const VString &other) const
{
    return !VString::compare(*this, other);
}

/*! \overload */
bool VLatin1String::operator==(const char *other) const
{
    return !vstrcmp(data, other);
}

/*!
 * Возвращает \c true, если строка больше \a other. Иначе \c false.
 */
bool VLatin1String::operator>(const VString &other) const
{
    return VString::compare(*this, other) > 0;
}

/*! \overload */
bool VLatin1String::operator>(const char *other) const
{
    return vstrcmp(data, other) > 0;
}

/*!
 * Возвращает \c true, если строка больше или равна \a other. Иначе \c false.
 */
bool VLatin1String::operator>=(const VString &other) const
{
    return VString::compare(*this, other) >= 0;
}

/*! \overload */
bool VLatin1String::operator>=(const char *other) const
{
    return vstrcmp(data, other) >= 0;
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
	d->data[size] = null;
    }
    else if(size > d->_alloc)
    {
	Data *x = (Data*)malloc(sizeof(Data)+size*sizeof(VChar));
	x->_s = d->_s;
	x->_alloc = size;
	x->data = x->array;
	x->data[size] = null;
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
    for(int i =0; i<size; ++i)
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

    for(int i=0; i<d->_s; ++i)
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
    if(d != &shared_null)
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

static int indexOf_helper(const VChar *s1, int size, const VChar *s2, int len, int from, Vt::CaseSensitivity cs)
{
    for(int i=from; i<size; ++i)
    {
	if(cs == Vt::CaseInsensitive)
	{
	    if(!vustrincmp(s1+i, s2, len))
		return i;
	    else
		continue;
	}

	if(!vustrncmp(s1+i, s2, len))
	    return i;
    }
    return -1;
}

int VString::indexOf(const VString &str, int from, Vt::CaseSensitivity cs) const
{
    return indexOf_helper(d->data, d->_s, str.d->data, str.d->_s, from, cs);
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

VString &VString::insert(int position, const VLatin1String &str)
{
    if(position<0 || position>d->_s)
    {
	vWarning("VString::insert(): position is %d\nNo inserted", position);
	return *this;
    }

    int l = vstrlen(str.latin1());
    reallocData(d->_s+l);

    memmove(d->data+position+l, d->data+position, sizeof(VChar)*(d->_s-position));

    for(int i=0; i<l; i++)
    	d->data[position+i] = VChar(str.latin1()[i]);
    
    d->_s += l;
    return *this;
}

VString &VString::insert(int position, const VChar *unicode, int size)
{
    if(position<0 || position>d->_s)
    {
	vWarning("VString::insert(): position is %d\nNo inserted", position);
	return *this;
    }

    reallocData(d->_s + size);

    memmove(d->data+position+size, d->data+position, sizeof(VChar)*size);
    memcpy(d->data+position, unicode, size);
    d->_s += size;

    return *this;
}

VString &VString::insert(int position, VChar ch)
{
    if(position<0 || position>d->_s)
    {
	vWarning("VString::insert(): position is %d\nNo inserted", position);
	return *this;
    }

    reallocData(++d->_s);

    memmove(d->data+position+1, d->data+position, sizeof(VChar));
    d->data[position] = ch;

    return *this;
}

VString &VString::prepend(const VString &str)
{
    reallocData(d->_s + str.d->_s);

    memmove(d->data+str.d->_s, d->data, sizeof(VChar)*d->_s);
    memcpy(d->data, str.d->data, sizeof(VChar)*str.d->_s);

    d->_s += str.d->_s;
    return *this;
}

VString &VString::prepend(const VByteArray &ba)
{
    return prepend(ba.constData());
}

VString &VString::prepend(const VLatin1String &str)
{
    int l = vstrlen(str.latin1());
    reallocData(d->_s + l);
    
    memmove(d->data+l, d->data, sizeof(VChar)*d->_s);
    
    for(int i=0; i<l; ++i)
	d->data[i] = VChar(str.latin1()[i]);

    d->_s += l;


    return *this;
}

VString &VString::prepend(VChar ch)
{
    reallocData(d->_s + 1);
    memmove(d->data+1, d->data, sizeof(VChar));
    d->data[0] = ch;
    ++d->_s;
    return *this;
}

int VString::lastIndexOf(const VString &str, int from, Vt::CaseSensitivity cs) const
{
    if(from == -1) from = d->_s - str.d->_s;

    for(int i=from; i>-1; --i)
    {
	if(cs == Vt::CaseInsensitive)
	{
	    if(!vustrincmp(d->data+i, str.d->data, str.d->_s))
		return i;
	    else
		continue;
	}

	if(!vustrncmp(d->data+i, str.d->data, str.d->_s))
	    return i;
    }
    return -1;
}

int VString::lastIndexOf(const VLatin1String &str, int from, Vt::CaseSensitivity cs) const
{
    int l = vstrlen(str.latin1());
    const char *data = toLatin1().constData();
    if(from == -1) from = d->_s - l;

    for(int i=from; i>-1; --i)
    {
	if(cs == Vt::CaseInsensitive)
	{
	    if(!vstrnicmp(data+i, str.latin1(), l))
		return i;
	    else
		continue;
	}

	if(!vstrncmp(data+i, str.latin1(), l))
	    return i;
    }

    return -1;
}

int VString::lastIndexOf(VChar ch, int from, Vt::CaseSensitivity cs) const
{
    VChar up = ch.toUpper();
    if(from == -1) from = d->_s - 1;

    for(int i=from; i>-1; --i)
    {
	if(cs == Vt::CaseInsensitive)
	{
	    if(d->data[i].toUpper() == up)
		return i;
	    else
		continue;
	}

	if(d->data[i] == ch)
	    return i;
    }
    return -1;
}

VString &VString::remove(int position, int n)
{
    if(position<0 || position>d->_s)
    {
	vWarning("VString::remove(): position is %d\nNo remove", position);
	return *this;
    }

    memmove(d->data+position, d->data+position+n, sizeof(VChar)*(d->_s-position-n));
    d->_s -= n;
    return *this;
}

VString &VString::remove(VChar ch, Vt::CaseSensitivity cs)
{
    int pos = indexOf(ch, 0, cs);

    while(pos != -1)
    {
	remove(pos, 1);
	pos = indexOf(ch, pos+1, cs);
    }

    return *this;
}

VString &VString::remove(const VString &str, Vt::CaseSensitivity cs)
{
    int len = str.size();
    int pos = indexOf(str, 0, cs);

    while(pos != -1)
    {
	remove(pos, len);
	pos = indexOf(str, pos+1, cs);
    }

    return *this;
}

VString VString::repeated(int times) const
{
    VString tmp;
    tmp.reserve(times*d->_s);

    while(times--)
        tmp.append(*this);

    return tmp;
}

VString &VString::replace(int position, int n, const VChar *unicode, int size)
{
    int len = d->_s - n + size;
    reallocData(len);

    memmove(d->data+position+size, d->data+position+n, sizeof(VChar)*(d->_s-position-n));
    memcpy(d->data+position, unicode, sizeof(VChar)*size);
    d->_s = len;
    return *this;
}

VString &VString::replace(const VChar *before, int blen, const VChar *after, int alen, Vt::CaseSensitivity cs)
{
    int pos = indexOf_helper(d->data, d->_s, before, blen, 0, cs);

    while(pos != -1)
    {
	replace(pos, blen, after, alen);
	pos = indexOf_helper(d->data, d->_s, before, blen, pos+1, cs);
    }

    return *this;
}

bool VString::startsWith(const VString &s, Vt::CaseSensitivity cs) const
{
    if(cs == Vt::CaseSensitive)
	return !vustrncmp(unicode(), s.unicode(), s.size());

    return !vustrincmp(unicode(), s.unicode(), s.size());
}

bool VString::startsWith(const VLatin1String &s, Vt::CaseSensitivity cs) const
{
    int len = vstrlen(s.latin1());
    const char *ts = toLatin1().constData();

    if(cs == Vt::CaseSensitive)
	return !vstrncmp(ts, s.latin1(), len);

    return !vstrnicmp(ts, s.latin1(), len);
}

bool VString::startsWith(const VChar &c, Vt::CaseSensitivity cs) const
{
    if(cs == Vt::CaseSensitive)
	return *d->data == c;

    return d->data->toUpper() == c.toUpper();
}

VString VString::left(int n) const
{
    return VString(d->data, n);
}

VString VString::right(int n) const
{
    return VString(d->data+(d->_s-n), n);
}

VString VString::mid(int position, int n) const
{
    if(n == -1) n = d->_s - position;

    return VString(d->data+position, n); 
}

VString &VString::setRawData(const VChar *unicode, int size)
{
    clear();
    reallocData(0);
    d->data = const_cast<VChar*>(unicode);
    d->_s = d->_alloc = size;
    return *this;
}

VString &VString::setUnicode(const VChar *unicode, int size)
{
    clear();
    reallocData(size);
    d->_s = size;

    memcpy(d->data, unicode, sizeof(VChar)*size);
    return *this;
}

VString &VString::setUtf16(const ushort *unicode, int size)
{
    clear();
    reallocData(size);
    d->_s = size;

    for(int i=0; i<size; ++i)
	d->data[i] = VChar(unicode[i]);
    return *this;
}

VString VString::toLower() const
{
    VString ret;
    ret.reserve(d->_s);

    for(int i=0; i<d->_s; ++i)
	ret.d->data[i] = d->data[i].toLower();

    return ret;
}

VString VString::toUpper() const
{
    VString ret;
    ret.reserve(d->_s);

    for(int i=0; i<d->_s; ++i)
	ret.d->data[i] = d->data[i].toUpper();

    return ret;
}

VStringList VString::split(const VString &sep, SplitBehavior bahavior, Vt::CaseSensitivity cs) const
{
    VStringList list;

    int pos = indexOf(sep, 0, cs);
    int last = 0;

    if(pos == -1)
    {
	list << *this;
	return list;
    }

    while(pos != -1)
    {
	VString tmp(d->data+last, pos - last);
	if(bahavior == KeepEmptyParts)
	    list << tmp;
	else if(!tmp.isEmpty())
	    list << tmp;
	last = pos + sep.size();
	pos = indexOf(sep, last, cs);
    }

    if(last != d->_s)
    {
	VString t(d->data+last, d->_s - last);
	if((bahavior == KeepEmptyParts) || !t.isEmpty())
	    list << t;
    }

    return list;
}


std::string VString::toStdString() const
{
    return std::string(toLatin1().data(), size());
}

VStdWString VString::toStdWString() const
{
    VStdWString ret;
    ret.resize(size());

    toWCharArray(&(*ret.begin()));
    return ret;
}

int VString::toWCharArray(wchar_t *array) const
{
    if(sizeof(wchar_t) == sizeof(VChar))
    {
	memcpy(array, utf16(), size()*sizeof(wchar_t));
    }
    return size();
}

VString &VString::operator=(const VString &other)
{
    clear();
    reallocData(other.d->_s);
    d->_s = other.d->_s;

    for(int i=0; i<=d->_s; ++i)
	d->data[i] = other.d->data[i];
    return *this;
}

