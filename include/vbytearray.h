#ifndef VBYTEARRAY_H
#define VBYTEARRAY_H

#include "vglobal.h"
#include <cstdarg>

int vstrcmp(const char *str1, const char *str2);
char *vstrcpy(char *dst, const char *str);
char *vstrdup(const char *str);
uint vstrlen(const char *str);
int vstricmp(const char *str1, const char *str2);
int vstrncmp(const char *str1, const char *str2, uint len);
char *vstrncpy(char *dst, const char *str, uint len);
int vstrnicmp(const char *str1, const char *str2, uint len);
uint vstrnlen(const char *str, uint maxlen);
int vsnprintf(char *str, size_t n, const char *fmt, ... );
int vvsnprintf(char *str, size_t n, const char *fmt, va_list ap);

vuint16 vChecksum(const char *data, uint len);

// NR: реализовать более грамотное управление памятью
// см. документацию по QString (Qt)
class VByteArray
{
public:
    VByteArray();
    VByteArray(const char *str);
    VByteArray(const char *data, int size);
    VByteArray(const VByteArray &other);
    ~VByteArray();

    VByteArray &append(const VByteArray &ba)
	{ return append(ba.d->str, ba.d->size); }
    VByteArray &append(const char *str)
	{ return append(str, vstrlen(str)); }
    VByteArray &append(const char *str, int len);
    VByteArray &append(char ch);

    VByteArray &prepend(const VByteArray &ba)
	{ return prepend(ba.d->str, ba.d->size); }
    VByteArray &prepend(const char *str)
	{ return prepend(str, vstrlen(str)); }
    VByteArray &prepend(const char *str, int len);
    VByteArray &prepend(char ch);

    // NR: добавить проверку на выход за границы
    inline char at(int i) const { return d->str[i]; }
    // NR: добавить исключение, если n > size
    void chop(int n) { d->size -= n; }

    inline void clear() { free(d); d = 0; }
    inline const char *constData() const { return d->str; }

    bool contains(const VByteArray &ba) const
	{ return contains(ba.d->str); }
    bool contains(const char *str) const;
    bool contains(char ch) const; 

    int count(const VByteArray &ba) const
	{ return count(ba.d->str); }
    int count(const char *str) const;
    int count(char ch) const;
    int count() const { return d->size; }

    char *data() { return d->str; }
    const char *data() const { return d->str; }

    bool endsWith(const VByteArray &ba) const
	{ return endsWith(ba.d->str); }
    bool endsWith(const char *str) const;
    bool endsWith(char ch) const;

    bool startsWith(const VByteArray &ba) const
	{ return startsWith(ba.d->str); }
    bool startsWith(const char *str) const;
    bool startsWith(char ch) const;

    VByteArray &fill(char ch, int size = -1);

    int indexOf(const VByteArray &ba, int from = 0) const
	{ return indexOf(ba.d->str, from); }
    int indexOf(const char *str, int from = 0) const;
    int indexOf(char ch, int from = 0) const;

    VByteArray &insert(int i, const VByteArray &ba)
	{ return insert(i, ba.d->str, ba.d->size); }
    VByteArray &insert(int i, const char *str)
	{ return insert(i, str, vstrlen(str)); }
    VByteArray &insert(int i, const char *str, int len);
    VByteArray &insert(int i, char ch);

    bool isEmpty() const { return d->size == 0; }

    int lastIndexOf(const VByteArray &ba, int from = -1) const
	{ return lastIndexOf(ba.d->str, from); }
    int lastIndexOf(const char *str, int from = -1) const;
    int lastIndexOf(char ch, int from = -1) const;

    int length() const { return d->size; }
    int size() const   { return d->size; }

#ifndef VT_NO_CAST_FROM_BYTEARRAY
    operator const char *() const;
    operator const void *() const;
#endif

    VByteArray toBase64() const;

    VByteArray &remove(int pos, int len);
    VByteArray repeated(int times) const;

    VByteArray &replace(int pos, int len, const VByteArray &after)
	{ return replace(pos, len, after.d->str, after.d->size); }
    VByteArray &replace(int pos, int len, const char *after)
	{ return replace(pos, len, after, vstrlen(after)); }
    VByteArray &replace(int pos, int len, const char *after, int alen);
    VByteArray &replace(const VByteArray &before, const VByteArray &after)
	{ return replace(before.d->str, before.d->size, after.d->str, after.d->size); }
    VByteArray &replace(const char *before, const VByteArray &after)
	{ return replace(before, vstrlen(before), after.d->str, after.d->size); }
    VByteArray &replace(const VByteArray &before, const char *after)
	{ return replace(before.d->str, before.d->size, after, vstrlen(after)); }
    VByteArray &replace(const char *before, const char *after)
	{ return replace(before, vstrlen(before), after, vstrlen(after)); }
    VByteArray &replace(const char *before, int bsize, const char *after, int asize);
    VByteArray &replace(char before, const VByteArray &after);
    VByteArray &replace(char before, const char *after);
    VByteArray &replace(char before, char after);

    void reserve(int size) { reallocData(size); }
    void resize(int size)  { if(size>d->size)reallocData(size); d->size = size; }

    VByteArray &setNum(int n, int base = 10)
	{ return setNum(vlonglong(n), base); }
    VByteArray &setNum(uint n, int base = 10)
	{ return setNum(vulonglong(n), base); }
    VByteArray &setNum(short n, int base = 10)
	{ return setNum(vlonglong(n), base); }
    VByteArray &setNum(ushort n, int base = 10)
	{ return setNum(vulonglong(n), base); }
    VByteArray &setNum(vlonglong n, int base = 10);
    VByteArray &setNum(vulonglong n, int base = 10);
    VByteArray &setNum(double n, int prec = 6);
    VByteArray &setNum(float n, int prec = 6)
	{ return setNum(double(n), prec); }

    // STL
    // NR: дописать inline
    void push_back(const VByteArray &other)  { append(other); }
    void push_back(const char *str)          { append(str); }
    void push_back(char ch)                  { append(ch); }
    void push_front(const VByteArray &other) { prepend(other); }
    void push_front(const char *str)         { prepend(str); }
    void push_front(char ch)                 { prepend(ch); }
    // END STL
    
    // operators
    bool operator!=(const VByteArray &str) const
	{ return vstrcmp(str.d->str, d->str); }
    bool operator==(const VByteArray &str) const
	{ return !vstrcmp(str.d->str, d->str); }
    bool operator<(const VByteArray &str) const
	{ return vstrcmp(str.d->str, d->str) < 0; }
    bool operator<=(const VByteArray &str) const
	{ return vstrcmp(str.d->str, d->str) <= 0; }
    bool operator>(const VByteArray &str) const
	{ return vstrcmp(str.d->str, d->str) > 0; }
    bool operator>=(const VByteArray &str) const
	{ return vstrcmp(str.d->str, d->str) >= 0; }

    // NR: добавить проверку на выход за границы
    // Написать класс VByteRef представляющий собой
    // вспомагательный класс для представления char&.
    char &operator[](int i) { return d->str[i]; }
    char operator[](int i) const { return d->str[i]; }
    char &operator[](uint i) { return d->str[i]; }
    char operator[](uint i) const { return d->str[i]; }

    VByteArray &operator+=(const VByteArray &ba) { return append(ba); }
    VByteArray &operator+=(const char *str) { return append(str); }
    VByteArray &operator+=(char ch) { return append(ch); }

    friend bool operator!=(const VByteArray &a1, const char *a2)
	{ return vstrcmp(a1.d->str, a2); }
    friend bool operator!=(const char *a1, const VByteArray &a2)
	{ return vstrcmp(a1, a2.d->str); }
    friend bool operator==(const VByteArray &a1, const char *a2)
	{ return !vstrcmp(a1.d->str, a2); }
    friend bool operator==(const char *a1, const VByteArray &a2)
	{ return !vstrcmp(a1, a2.d->str); }
    friend bool operator<(const VByteArray &a1, const char *a2)
	{ return vstrcmp(a1.d->str, a2) < 0; }
    friend bool operator<(const char *a1, const VByteArray &a2)
	{ return vstrcmp(a1, a2.d->str) < 0; }
    friend bool operator<=(const VByteArray &a1, const char *a2)
	{ return vstrcmp(a1.d->str, a2) <= 0; }
    friend bool operator<=(const char *a1, const VByteArray &a2)
	{ return vstrcmp(a1, a2.d->str) <= 0; }
    friend bool operator>(const VByteArray &a1, const char *a2)
	{ return vstrcmp(a1.d->str, a2) > 0; }
    friend bool operator>(const char *a1, const VByteArray &a2)
	{ return vstrcmp(a1, a2.d->str) > 0; }
    friend bool operator>=(const VByteArray &a1, const char *a2)
	{ return vstrcmp(a1.d->str, a2) >= 0; }
    friend bool operator>=(const char *a1, const VByteArray &a2)
	{ return vstrcmp(a1, a2.d->str) >= 0; }

    friend const VByteArray operator+(const VByteArray &a1, const VByteArray &a2)
    {
	VByteArray ret; ret.reserve(a1.d->size + a2.d->size);
	ret.append(a1); ret.append(a2);
	return ret;
    }
    friend const VByteArray operator+(const VByteArray &a1, const char *a2)
    {
	VByteArray ret; ret.reserve(a1.d->size+vstrlen(a2));
	ret.append(a1); ret.append(a2);
	return ret;
    }
    friend const VByteArray operator+(const char *a1, const VByteArray &a2)
    {
	VByteArray ret; ret.reserve(vstrlen(a1)+a2.d->size);
	ret.append(a1); ret.append(a2);
	return ret;
    }
    friend const VByteArray operator+(const VByteArray &a1, char a2)
    {
	VByteArray ret; ret.reserve(a1.d->size+1);
	ret.append(a1); ret.append(a2);
	return ret;
    }
    friend const VByteArray operator+(char a1, const VByteArray &a2)
    {
	VByteArray ret; ret.reserve(1+a2.d->size);
	ret.append(a1); ret.append(a2);
	return ret;
    }

    // static
    static VByteArray number(int n, int base = 10)
	{ return VByteArray().setNum(n, base); }
    static VByteArray number(uint n, int base = 10)
	{ return VByteArray().setNum(n, base); }
    static VByteArray number(vlonglong n, int base = 10)
	{ return VByteArray().setNum(n, base); }
    static VByteArray number(vulonglong n, int base = 10)
	{ return VByteArray().setNum(n, base); }
    static VByteArray number(double n, int prec = 6)
        { return VByteArray().setNum(n, prec); }

private:
    VByteArray(int size);

    struct Data
    {
	int size;
	int alloc;
	char *str;
	char array[1];
    };
    Data *d;

    void reallocData(int size);
};

#endif
