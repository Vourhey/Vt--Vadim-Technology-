#ifndef VPOINT_H
#define VPOINT_H

#include "vglobal.h"

class VPoint
{
public:
    inline VPoint() : _x(0), _y(0) {}
    inline VPoint(int x, int y) : _x(x), _y(y) {}

    bool isNull() const;    
    int manhattanLength() const;

    inline int &rx() { return _x; }
    inline int &ry() { return _y; }
    inline void setX(int x) { _x = x; }
    inline void setY(int y) { _y = y; }
    inline int x() const { return _x; }
    inline int y() const { return _y; }

    VPoint &operator*=(vreal factor);
    VPoint &operator+=(const VPoint &point);
    VPoint &operator-=(const VPoint &point);
    VPoint &operator/=(vreal divisor);

    friend bool operator==(const VPoint &p1, const VPoint &p2);
    friend bool operator!=(const VPoint &p1, const VPoint &p2)
	{ return !operator==(p1, p2); }
    friend const VPoint operator*(const VPoint &point, vreal factor)
	{ return (VPoint(point) *= factor); }
    friend const VPoint operator*(vreal factor, const VPoint &point)
	{ return (VPoint(point) *= factor); }
    friend const VPoint operator+(const VPoint &p1, const VPoint &p2)
	{ return (VPoint(p1) += p2); }
    friend const VPoint operator-(const VPoint &p1, const VPoint &p2)
	{ return (VPoint(p1) -= p2); }
    friend const VPoint operator-(const VPoint &point)
	{ return VPoint(-point._x, -point._y); }
    friend VPoint operator/(const VPoint &point, vreal divisor)
	{ return (VPoint(point) /= divisor); }

private:
    int _x;
    int _y;
};

class VPointF
{
public:
    inline VPointF() : _x(0), _y(0) {}
    inline VPointF(const VPoint &point) : _x(point.x()), _y(point.y()) {}
    inline VPointF(vreal x, vreal y) : _x(x), _y(y) {}

    bool isNull() const;
    vreal manhattanLength() const;

    inline vreal &rx() { return _x; }
    inline vreal &ry() { return _y; }
    inline void setX(vreal x) { _x = x; }
    inline void setY(vreal y) { _y = y; }
    inline VPoint toPoint() const 
        { return VPoint(vRound(_x), vRound(_y)); }
    inline vreal x() const { return _x; }
    inline vreal y() const { return _y; }

    VPointF &operator*=(vreal factor);
    VPointF &operator+=(const VPointF &point);
    VPointF &operator-=(const VPointF &point);
    VPointF &operator/=(vreal divisor);

    friend bool operator==(const VPointF &p1, const VPointF &p2);
    friend bool operator!=(const VPointF &p1, const VPointF &p2)
	{ return !operator==(p1, p2); }
    friend const VPointF operator*(const VPointF &point, vreal factor)
	{ return (VPointF(point) /= factor); }
    friend const VPointF operator*(vreal factor, const VPointF &point)
	{ return (VPointF(point) /= factor); }
    friend const VPointF operator+(const VPointF &p1, const VPointF &p2)
	{ return (VPointF(p1) += p2); }
    friend const VPointF operator-(const VPointF &p1, const VPointF &p2)
	{ return (VPointF(p1) -= p2); }
    friend const VPointF operator-(const VPointF &point)
	{ return VPointF(-point._x, -point._y); }
    friend const VPointF operator/(const VPointF &point, vreal divisor)
	{ return (VPointF(point) /= divisor); }

private:
    vreal _x;
    vreal _y;
};

#include <iostream>
inline std::ostream &operator<<(std::ostream &os, const VPoint &p)
{
    os << "VPoint(" << p.x() << "," << p.y() << ")";
    return os;
}
inline std::ostream &operator<<(std::ostream &os, const VPointF &p)
{
    os << "VPoint(" << p.x() << "," << p.y() << ")";
    return os;
}

#endif
