#ifndef VSTRING_H
#define VSTRING_H

#include "vglobal.h"
#include "vchar.h"
#include <string>

class VString;
class VByteArray;
class VStringList;
class string;
typedef std::basic_string<wchar_t> VStdWString;

class VLatin1String
{
public:
    VLatin1String(const char *str);
    const char *latin1() const;
    bool operator!=(const VString &other) const;
    bool operator!=(const char *other) const;
    bool operator<(const VString &other) const;
    bool operator<(const char *other) const;
    bool operator<=(const VString &other) const;
    bool operator<=(const char *other) const;
    VLatin1String &operator=(const VLatin1String &other);
    bool operator==(const VString &other) const;
    bool operator==(const char *other) const;
    bool operator>(const VString &other) const;
    bool operator>(const char *other) const;
    bool operator>=(const VString &other) const;
    bool operator>=(const char *other) const;

private:
    const char *data;
};

class VString
{
public:
    VString();
    VString(const VChar *unicode, int size);
    VString(const VChar *unicode);
    VString(VChar ch);
    VString(int size, VChar ch);
    VString(const VLatin1String &str);
    VString(const VString &other);

#ifndef VT_NO_CAST_FROM_ASCII
    VString(const char *str);
    VString(const VByteArray &ba);
#endif

    ~VString();

    void clear();

    VString &append(const VString &str);
    VString &append(const VLatin1String &str);
#ifndef VT_NO_CAST_FROM_ASCII
    VString &append(const VByteArray &ba);
    VString &append(const char *str) { return append(VLatin1String(str)); }
#endif
    VString &append(VChar ch);

    VString &prepend(const VString &str);
    VString &prepend(const VLatin1String &str);
#ifndef VT_NO_CAST_FROM_ACSII
    VString &prepend(const VByteArray &ba);
    VString &prepend(const char *str) { return prepend(VLatin1String(str)); }
#endif
    VString &prepend(VChar ch);

    const VChar at(int position) const;
    const VChar *constData() const { return d->data; }
    VChar *data() { return d->data; }
    const VChar *data() const { return d->data; }

    VByteArray toAscii() const;
    VByteArray toLatin1() const;
    VByteArray toLocal8Bit() const;

    class Null {};
    static const Null null;
    inline VString(const Null &n) : d(&shared_null) {}
    inline bool isNull() const { return d == &shared_null; }

    void chop(int n);
    VString &fill(VChar ch, int size = -1);

    bool endsWith(const VString &s, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    bool endsWith(const VLatin1String &s, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    bool endsWith(const VChar &c, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    bool startsWith(const VString &s, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    bool startsWith(const VLatin1String &s, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    bool startsWith(const VChar &c, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;

    static int compare(const VString &s1, const VString &s2, Vt::CaseSensitivity cs);
    static int compare(const VString &s1, const VString &s2)
	{ return compare(s1, s2, Vt::CaseSensitive); }
    static int compare(const VString &s1, const VLatin1String &s2, Vt::CaseSensitivity cs = Vt::CaseSensitive);
    static int compare(const VLatin1String &s1, const VString &s2, Vt::CaseSensitivity cs = Vt::CaseSensitive);

    int compare(const VString &other) const
        { return compare(*this, other, Vt::CaseSensitive); }
    int compare(const VString &other, Vt::CaseSensitivity cs) const
	{ return compare(*this, other, cs); }
    int compare(const VLatin1String &other, Vt::CaseSensitivity cs = Vt::CaseSensitive) const
	{ return compare(*this, other, cs); }

    bool contains(const VString &str, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    bool contains(VChar ch, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;

    int count(const VString &str, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int count(VChar ch, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int count() const { return d->_s; }
    int length() const { return d->_s; }
    int size() const { return d->_s; }

    int indexOf(const VString &str, int from = 0, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int indexOf(const VLatin1String &str, int from = 0, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int indexOf(VChar ch, int from = 0, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;

    int lastIndexOf(const VString &str, int from = -1, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int lastIndexOf(const VLatin1String &str, int from = -1, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int lastIndexOf(VChar ch, int from = -1, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;

    VString &insert(int position, const VString &str)
	{ return insert(position, str.d->data, str.d->_s); }
    VString &insert(int position, const VChar *unicode, int size);
    VString &insert(int position, const VLatin1String &str);
    VString &insert(int position, VChar ch);

    VString &remove(int position, int n);
    VString &remove(VChar ch, Vt::CaseSensitivity cs = Vt::CaseSensitive);
    VString &remove(const VString &str, Vt::CaseSensitivity cs = Vt::CaseSensitive);

    VString repeated(int times) const;

    VString &replace(int position, int n, const VString &after)
	{ return replace(position, n, after.d->data, after.d->_s); }
    VString &replace(int position, int n, const VChar *unicode, int size);
    VString &replace(int position, int n, VChar after)
	{ return replace(position, n, &after, 1); }
    VString &replace(const VChar *before, int blen, const VChar *after, int alen, Vt::CaseSensitivity cs = Vt::CaseSensitive);
    VString &replace(const VString &before, const VString &after, Vt::CaseSensitivity cs = Vt::CaseSensitive)
	{ return replace(before.unicode(), before.size(), after.unicode(), after.size(), cs); }
    VString &replace(VChar before, const VString &after, Vt::CaseSensitivity cs = Vt::CaseSensitive)
	{ return replace(&before, 1, after.unicode(), after.size(), cs); }
    VString &replace(VChar before, VChar after, Vt::CaseSensitivity cs = Vt::CaseSensitive)
	{ return replace(&before, 1, &after, 1, cs); }

    VString &setRawData(const VChar *unicode, int size);
    VString &setUnicode(const VChar *unicode, int size);
    VString &setUtf16(const ushort *unicdoe, int size);

    inline bool isEmpty() const { return d->_s == 0; }
    inline void reserve(int size) { reallocData(size); }
    inline void resize(int size) { reallocData(size); d->_s = size; }

    VString left(int n) const;
    VString right(int n) const;
    VString mid(int position, int n = -1) const;

    enum SplitBehavior
    {
	KeepEmptyParts = 0,
	SkipEmptyParts = 1
    };

    VStringList split(const VString &sep, SplitBehavior behavior = KeepEmptyParts, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;

    VString toLower() const;
    VString toUpper() const;

    std::string toStdString() const;
    VStdWString toStdWString() const;
    int toWCharArray (wchar_t *array) const;

    // operators
    VChar &operator[](int position);
    const VChar operator[](int position) const;
    VChar &operator[](uint position);
    const VChar operator[](uint position) const;

    VString &operator=(const VString &other);

    // for STL
    void push_back(const VString &other) { append(other); }
    void push_back(VChar ch)             { append(ch); }
    void push_front(const VString &other) { prepend(other); }
    void push_front(VChar ch)             { prepend(ch); }

#ifndef VT_NO_CAST_TO_ASCII
    operator const char *() const;
#endif
    const VChar *unicode() const { return reinterpret_cast<const VChar*>(d->data); }
    const ushort *utf16() const { return reinterpret_cast<const ushort*>(d->data); }

private:
    void reallocData(int size);

    struct VStringData
    {
	int _s;
	int _alloc;
	VChar *data;
	VChar array[1];
    };
    typedef VStringData Data;
    static Data shared_null;
    Data *d;
};

#endif
