#ifndef VSTRING_H
#define VSTRING_H

#include "vglobal.h"
#include "vchar.h"

class VString;
class VByteArray;

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

    static int compare(const VString &s1, const VString &s2, Vt::CaseSensitivity cs);
    static int compare(const VString &s1, const VString &s2)
	{ return compare(s1, s2, Vt::CaseSensitive); }
    static int compare(const VString &s1, const VLatin1String &s2, Vt::CaseSensitivity cs = Vt::CaseSensitive);
    static int compare(const VLatin1String &s1, const VString &s2, Vt::CaseSensitivity cs = Vt::CaseSensitive);

    int compare(const VString &other) const
        { return compare(*this, other, Vt::CaseSensitive); }
    int compare(const VString &other, Vt::CaseSensitivity cs) const
	{ return compare(*this, other, cs); }

    bool contains(const VString &str, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    bool contains(VChar ch, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;

    int count(const VString &str, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int count(VChar ch, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int count() const { return d->_s; }

    int indexOf(const VString &str, int from = 0, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int indexOf(const VLatin1String &str, int from = 0, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;
    int indexOf(VChar ch, int from = 0, Vt::CaseSensitivity cs = Vt::CaseSensitive) const;

    // operators
    VChar &operator[](int position);
    const VChar operator[](int position) const;
    VChar &operator[](uint position);
    const VChar operator[](uint position) const;

#ifndef VT_NO_CAST_TO_ASCII
    operator const char *() const;
#endif

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
