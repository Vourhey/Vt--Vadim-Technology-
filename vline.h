#ifndef VLINE_H
#define VLINE_H

#include "vglobal.h"
#include "vpoint.h"

class VLine
{
public:
    inline VLine();
    inline VLine(const VPoint &p1, const VPoint &p2) : _p1(p1), _p2(p2) {}
    inline VLine(int x1, int y1, int x2, int y2) : _p1(x1, y1), _p2(x2, y2) {}

    inline VPoint p1() const { return _p1; }
    inline VPoint p2() const { return _p2; }

    inline int x1() const { return _p1.x(); }
    inline int x2() const { return _p2.x(); }
    inline int y1() const { return _p1.y(); }
    inline int y2() const { return _p2.y(); }

    inline int dx() const { return _p2.x() - _p1.x(); }
    inline int dy() const { return _p2.y() - _p2.y(); }

    inline bool isNull() const { return _p1.isNull() && _p2.isNull(); }

    inline void setP1(const VPoint &p1) { _p1 = p1; }
    inline void setP2(const VPoint &p2) { _p2 = p2; }

    inline void setLine(int x1, int y1, int x2, int y2)
	{ _p1 = VPoint(x1, y1); _p2 = VPoint(x2, y2); }
    inline void setPoints(const VPoint &p1, const VPoint &p2)
	{ _p1 = p1; _p2 = p2; }

    inline void translate(const VPoint &offset)
	{ _p1 += offset; _p2 += offset; }
    inline void translate(int dx, int dy)
	{ translate(VPoint(dx, dy)); }

    inline VLine translated(const VPoint &offset) const
	{ VLine l(_p1, _p2); l.translate(offset); return l; }
    inline VLine translated(int dx, int dy) const
	{ VLine l(_p1, _p2); l.translate(VPoint(dx, dy)); return l; }

    inline bool operator==(const VLine &line) const
	{ return (_p1 == line._p1) && (_p2 == line._p2); }
    inline bool operator!=(const VLine &line) const
	{ return !operator==(line); }

private:
    VPoint _p1;
    VPoint _p2;
};



class VLineF
{
public:
    inline VLineF() {}
    inline VLineF(const VPointF &p1, const VPointF &p2)
	: _p1(p1), _p2(p2) {}
    inline VLineF(vreal x1, vreal y1, vreal x2, vreal y2)
	: _p1(x1, y1), _p2(x2, y2) {}
    inline VLineF(const VLine &line)
	: _p1(line.p1()), _p2(line.p2()) {}

    inline VPointF p1() const { return _p1; }
    inline VPointF p2() const { return _p2; }

    inline vreal x1() const { return _p1.x(); }
    inline vreal x2() const { return _p2.x(); }
    inline vreal y1() const { return _p1.y(); }
    inline vreal y2() const { return _p2.y(); }

    inline vreal dx() const { return _p2.x() - _p1.x(); }
    inline vreal dy() const { return _p2.y() - _p1.y(); }

    vreal length() const;

    inline bool isNull() const { return _p1.isNull() && _p2.isNull(); }

    inline void setP1(const VPointF &p1) { _p1 = p1; }
    inline void setP2(const VPointF &p2) { _p2 = p2; }
    void setLine(vreal x1, vreal y1, vreal x2, vreal y2);
    void setPoints(const VPointF &p1, const VPointF &p2);

    inline VLine toLine() const { return VLine(_p1.toPoint(), _p2.toPoint()); }

    VPointF pointAt(vreal t) const;
    VLineF normalVector() const;

    inline void translate(const VPointF &offset)
	{ _p1 += offset; _p2 += offset; }
    inline void translate(vreal dx, vreal dy)
	{ translate(VPointF(dx, dy)); }

    inline VLineF translated(const VPointF &offset) const
	{ return VLineF(_p1 + offset, _p2 + offset); }
    inline VLineF translated(vreal dx, vreal dy) const
	{ return translated(VPointF(dx, dy)); }

    inline bool operator==(const VLineF &line) const
	{ return (_p1 == line._p1) && (_p2 == line._p2); }
    inline bool operator!=(const VLineF &line) const
	{ return !operator==(line); }

private:
    VPointF _p1;
    VPointF _p2;
};

#endif
