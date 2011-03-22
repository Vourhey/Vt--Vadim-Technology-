#include <cmath>
#include "vline.h"

vreal VLineF::length() const
{
   int x = dx();
   int y = dy();
   return sqrt(x*x + y*y);
}

void VLineF::setLine(vreal x1, vreal y1, vreal x2, vreal y2)
{
    _p1 = VPointF(x1, y1);
    _p2 = VPointF(x2, y2);
}

// можно inline
VPointF VLineF::pointAt(vreal t) const
{
    return VPointF(_p1.x() + dx()*t, _p2.y() + dy*t);
}

VLineF VLineF::normalVector() const
{
    return VLineF(_p1, _p1 + VPointF(-dy(), dx()));
}

// можно и inline
void VLineF::setPoints(const VPointF &p1, const VPointF &p2)
{
    _p1 = p1;
    _p2 = p2;
}
