#ifndef VSIZE_H
#define VSIZE_H

#include "vglobal.h"

class VSize
{
public:
    inline VSize() : _w(-1), _h(-1) {}
    inline VSize(int width, int height) : _w(width), _h(height) {}

    VSize boundedTo(const VSize &otherSize) const;
    VSize expandedTo(const VSize &otherSize) const;

    inline int height() const { return _h; }
    inline int width() const  { return _w; }
    inline int &rheight() { return _h; }
    inline int &rwidth()  { return _w; }

    inline bool isEmpty() const { return _h <= 0 && _w <= 0; }
    inline bool isNull() const  { return _h == 0 && _w == 0; }
    inline bool isValid() const { return _h >= 0 && _w >= 0; }

    inline void setHeight(int height) { _h = height; }
    inline void setWidth(int width)   { _w = width; }

    void transpose() { int t = _w; _w = _h; _h = t; }

    VSize &operator*=(vreal factor);
    VSize &operator+=(const VSize &size);
    VSize &operator-=(const VSize &size);
    VSize &operator/=(vreal divisor);

    friend bool operator==(const VSize &s1, const VSize &s2)
	{ return s1._h == s2._h && s1._w == s2._w; }
    friend bool operator!=(const VSize &s1, const VSize &s2)
	{ return !operator==(s1, s2); }
    friend const VSize operator*(vreal factor, const VSize &size)
	{ VSize s(size); s *= factor; return s; }
    friend const VSize operator*(const VSize &size, vreal factor)
	{ return operator*(factor, size); }
    friend const VSize operator+(const VSize &s1, const VSize &s2)
	{ VSize s(s1); s += s2; return s; }
    friend const VSize operator-(const VSize &s1, const VSize &s2)
	{ VSize s(s1); s -= s2; return s; }
    friend const VSize operator/(const VSize &size, vreal divisor)
	{ VSize s(size); s /= divisor; return s; }

private:
    int _w;
    int _h;
};

class VSizeF
{
public:
    inline VSizeF() : _w(-1), _h(-1) {}
    inline VSizeF(const VSize &size) : _w(size.width()), _h(size.height()) {}
    inline VSizeF(vreal width, vreal height) : _w(width), _h(height) {}

    VSizeF boundedTo(const VSizeF &otherSize) const;
    VSizeF expandedTo(const VSizeF &otherSize) const;

    inline vreal height() const { return _h; }
    inline vreal width() const  { return _w; }
    inline vreal &rheight() { return _h; }
    inline vreal &rwidth()  { return _w; }

    inline void setHeight(vreal height) { _h = height; }
    inline void setWidth(vreal width)   { _w = width; }

    inline bool isEmpty() const { return _h <= 0 && _w <= 0; }
    inline bool isNull() const  { return _h == 0 && _w == 0; }
    inline bool isValid() const { return _h >= 0 && _w >= 0; }

    inline VSize toSize() const { return VSize(vRound(_w), vRound(_h)); }
    inline void transpose() { vreal t = _h; _h = _w; _w = t; }

    VSizeF &operator*=(vreal factor);
    VSizeF &operator+=(const VSizeF &size);
    VSizeF &operator-=(const VSizeF &size);
    VSizeF &operator/=(vreal divisor);

    friend bool operator==(const VSizeF &s1, const VSizeF &s2)
	{ return s1._h == s2._h && s1._w == s2._w; }
    friend bool operator!=(const VSizeF &s1, const VSizeF &s2)
	{ return !operator==(s1, s2); }
    friend const VSizeF operator*(const VSizeF &size, vreal factor)
	{ VSizeF s(size); s *= factor; return s; }
    friend const VSizeF operator*(vreal factor, const VSizeF &size)
	{ return operator*(size, factor); }
    friend const VSizeF operator+(const VSizeF &s1, const VSizeF &s2)
	{ VSizeF s(s1); s += s2; return s; }
    friend const VSizeF operator-(const VSizeF &s1, const VSizeF &s2)
	{ VSizeF s(s1); s -= s2; return s; }
    friend const VSizeF operator/(const VSizeF &size, vreal divisor)
	{ VSizeF s(size); s /= divisor; return s; }

private:
    vreal _w;
    vreal _h;
};

#endif
