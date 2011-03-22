#include "vpoint.h"

bool VPoint::isNull() const
{
    return (_x == 0) && (_y == 0);
}

int VPoint::manhattanLength() const
{
    return vAbs(_x) + vAbs(_y);
}

VPoint &VPoint::operator*=(vreal factor)
{
    _x = vRound(_x * factor);
    _y = vRound(_y * factor);
    return *this;
}

VPoint &VPoint::operator+=(const VPoint &point)
{
    _x += point._x;
    _y += point._y;
    return *this;
}

VPoint &VPoint::operator-=(const VPoint &point)
{
    _x -= point._x;
    _y -= point._y;
    return *this;
}

VPoint &VPoint::operator/=(vreal divisor)
{
    if(!divisor) return *this; // делить на ноль нельзя

    _x = vRound(_x / divisor);
    _y = vRound(_y / divisor);
    return *this;
}

bool operator==(const VPoint &p1, const VPoint &p2)
{
    return (p1._x == p2._x) && (p1._y == p2._y);
}

bool VPointF::isNull() const
{
    return (_x == 0.0) && (_y == 0.0);
}

vreal VPointF::manhattanLength() const
{
    return vAbs(_x) + vAbs(_y);
}

VPointF &VPointF::operator*=(vreal factor)
{
    _x *= factor;
    _y *= factor;
    return *this;
}

VPointF &VPointF::operator+=(const VPointF &point)
{
    _x += point._x;
    _y += point._y;
    return *this;
}

VPointF &VPointF::operator-=(const VPointF &point)
{
    _x -= point._x;
    _y -= point._y;
    return *this;
}

VPointF &VPointF::operator/=(vreal divisor)
{
    if(!divisor) return *this; // делить на ноль нельзя

    _x /= divisor;
    _y /= divisor;
    return *this;
}

bool operator==(const VPointF &p1, const VPointF &p2)
{
    return (p1._x == p2._x) && (p1._y == p2._y);
}
