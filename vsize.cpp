#include "vsize.h"

/*!
 * \class VSize
 * \brief Определяет размер на двумерной поверхнисти, используя целые числа.
 *
 * Размер определяется width() и height(). Ширину и высоту можно установить
 * через setWidth() и setHeight(). Получить прямой доступ к полям
 * высоты и ширины можно через rwidth() и rheight(). Наконец,
 * высоту и ширину можно поменять местами, используя transpose().
 *
 * Функция isValid() определяет, действителен ли размер (т.е. высота
 * и ширина должны быть больше 0). isEmpty() вовзвращает \c true,
 * если оба параметра установленны в 0 или меньше него. 
 * isNull() возвращает \c true только в том случае, когда
 * высота и ширина равны нулю.
 *
 * expandedTo() возвращает объект с максимальными значениями высоты
 * и ширины, а boundedTo() с минимальными.
 *
 * VSize можно сравнивать и передавать в качестве параметра.
 * \see VSizeF, VPoint 
 */

VSize VSize::boundedTo(const VSize &otherSize) const
{
    return VSize(vMin(_w, otherSize._w), vMin(_h, otherSize._h));
}

VSize VSize::expandedTo(const VSize &otherSize) const
{
    return VSize(vMax(_w, otherSize._w), vMax(_h, otherSize._h));
}

VSize &VSize::operator*=(vreal factor)
{
    _h = vRound(_h * factor);
    _w = vRound(_w * factor);
    return *this;
}

VSize &VSize::operator+=(const VSize &size)
{
    _h += size._h;
    _w += size._w;
    return *this;
}

VSize &VSize::operator-=(const VSize &size)
{
    _h -= size._h;
    _w -= size._w;
    return *this;
}

VSize &VSize::operator/=(vreal divisor)
{
    if(!divisor) return *this;
    _h = vRound(_h / divisor);
    _w = vRound(_w / divisor);
    return *this;
}

VSizeF VSizeF::boundedTo(const VSizeF &otherSize) const
{
    return VSizeF(vMin(_w, otherSize._w), vMin(_h, otherSize._h));
}

VSizeF VSizeF::expandedTo(const VSizeF &otherSize) const
{
    return VSizeF(vMax(_w, otherSize._w), vMax(_h, otherSize._h));
}

VSizeF &VSizeF::operator*=(vreal factor)
{
    _h *= factor;
    _w *= factor;
    return *this;
}

VSizeF &VSizeF::operator+=(const VSizeF &size)
{
    _h += size._h;
    _w += size._w;
    return *this;
}

VSizeF &VSizeF::operator-=(const VSizeF &size)
{
    _h -= size._h;
    _w -= size._w;
    return *this;
}

VSizeF &VSizeF::operator/=(vreal divisor)
{
    if(!divisor) return *this;

    _h /= divisor;
    _w /= divisor;
    return *this;
}
