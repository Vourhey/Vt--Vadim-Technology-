#include <cmath>
#include "vline.h"

/*!
 * \class VLine
 * \brief Представляет двумерный объект отрезок с целыми точками.
 *
 * VLine описывает конечную длину отрезка на двумерной поверхности
 * используя целое представление. Если вам нужны представление
 * с плавающей точкой, то используйте VLineF.\n
 * <table><tr><td>
 * \image html vline-coordinates.png
 * </td><td>
 * \image html vline-point.png
 * </td></tr></table> \n
 * Позиции начала и конца отрезка можно получить с помощью
 * p1(), x1(), y1(), p2(), x2(), y2(). dx() и dy() возвращают
 * длину по горизонтали и по вертикали соответственно.
 * Используйте isNull(), чтобы определить состояние VLine.
 *
 * Так же можно смещать отрезок, используя translate().
 * \see VLineF
 */
/*!
 * \fn VLine::VLine()
 * Создает пустую линию.
 */
/*!
 * \fn VLine::VLine(const VPoint &p1, const VPoint &p2)
 * Создает линию, используя \a p1 и \a p2 в качестве начала
 * и конца.
 */
/*!
 * \fn VLine::VLine(int x1, int y1, int x2, int y2)
 * Создает отрезок между точками (\a x1, \a y1) и (\a x2, \a y2).
 */
/*!
 * \fn VPoint VLine::p1() const
 * Возвращает точку начала.
 * \see setP1(), x1(), y1() и p2()
 */
/*!
 * \fn VPoint VLine::p2() const
 * Возвращает точку конца.
 * \see setP2(), x2(), y2() и p1()
 */
/*!
 * \fn int VLine::x1() const
 * Возвращает x-координату начала отрезка.
 * \see p1()
 */
/*!
 * \fn int VLine::x2() const
 * Возвращает x-координату конца строки.
 * \see p2()
 */
/*!
 * \fn int VLine::y1() const
 * Возвращает y-координату начала отрезка.
 * \see p1()
 */
/*!
 * \fn int VLine::y2() const
 * Возвращает y-координату конца отрезка.
 * \see p2()
 */
/*!
 * \fn int VLine::dx() const
 * Возвращает длину по горизонтали.
 * \see dy()
 */
/*!
 * \fn VLine::dy() const
 * Возвращает длину по вертикали.
 * \see dy()
 */
/*!
 * \fn bool VLine::isNull() const
 * Возвращает \c true, если отрезок имеет действительные
 * значение начальной и конечной точки. Иначе \c false.
 */
/*!
 * \fn void VLine::setP1(const VPoint &p1)
 * Устанавливает начальную точку в \a p1.
 * \see setP2() и p1()
 */
/*!
 * \fn void VLine::setP2(const VPoint &p2)
 * Устанавливает конечную точку в \a p2.
 * \see setP1() и p2()
 */
/*!
 * \fn void VLine::setLine(int x1, int y1, int x2, int y2)
 * Устанавливает начальную точку в (\a x1, \a y1) и 
 * конечную в (\a x2, \a y2).
 * \see setP1(), setP2(), p1() и p2()
 */
/*!
 * \fn void VLine::setPoints(const VPoint &p1, const VPoint &p2)
 * Устанавливает начальную точку в \a p1 и конечную \a p2.
 * \see setP1(), setP2(), p1() и p2()
 */
/*!
 * \fn void VLine::translate(const VPoint &offset)
 * Смещает отрезок на \a offset.
 */
/*!
 * \fn void VLine::translate(int dx, int dy)
 * \overload \n
 * Смещает отрезок на \a dx по горизонтали и 
 * \a dy по вертикали.
 */
/*!
 * \fn VLine VLine::translated(const VPoint &offset) const
 * Возвращает отрезок, смещенный на \a offset.
 */
/*!
 * \fn VLine VLine::translated(int dx, int dy) const
 * \overload \n
 * Возвращает строку, смещенную на \a dx по горизонтали
 * и на \a dy по вертикали.
 */
/*!
 * \fn bool VLine::operator!=(const VLine &line) const
 * Возвращает \c true, если \a line не равен этому отрезку.
 * Отрезки считаются разными, если их начальные или конечные
 * (или обе сразу) точки не совпадают.
 */
/*!
 * \fn bool VLine::operator==(const VLine &line) const
 * Возвращает \c true, если \a line равен этому отрезку.
 * Отрезки считаются равными, если их начальные и конечные
 * точки совпадают.
 */

/*!
 * \class VLineF
 * \brief Представляет отрезок, используя значения с плавающей точкой.
 *
 * VLineF представляет отрезок на двумерной поверхности, используя
 * значения с плавающей точкой для представления начальной и конечной
 * координаты. Для получения аналога, выраженного целыми числами,
 * используйте toLine().
 * <br><table><tr><td>
 * \image html vline-coordinates.png
 * </td><td>
 * \image html vline-point.png
 * </td></tr></table><br>
 * Для получения начальной и конечно точки можно использовать
 * p1(), x1(), y1(), p2(), x2(), y2(). Для получения горизонтальной и
 * вертикальной составляющей dx() и dy() соответственно.
 *
 * Длину отрезка можно узнать, используя length(). Действителен ли
 * отрезок - isNull(). Получить отрезок, перпендикулярный этому - normalVector().
 *
 * Отрезок можно сместить, используя translate().
 * \see VLine
 */
/*!
 * \fn VLineF::VLineF()
 * Создает нулевой отрезок.
 */
/*!
 * \fn VLineF::VLineF(const VPointF &p1, const VPointF &p2)
 * Создает отрезок с начальной \a p1 и конечной \a p2 точками.
 */
/*!
 * \fn VLineF::VLineF(vreal x1, vreal y1, vreal x2, vreal y2)
 * Создает отрезок между (\a x1, \a y1) и (\a x2, \a y2).
 */
/*!
 * \fn VLineF::VLineF(const VLine &line)
 * Создает VLineF объект из отрезка с целыми точками \a line.
 * \see toLine()
 */
/*!
 * \fn VPointF VLineF::p1() const
 * Возвращает начальную точку.
 * \see setP1(), x1(), y1() и p2()
 */
/*!
 * \fn VPointF VLineF::p2() const
 * Возвращает конечную точку.
 * \see setP2(), x2(), y2() и p1()
 */
/*!
 * \fn vreal VLineF::x1() const
 * Возвращает x-координату начальной точки.
 * \see p1()
 */
/*!
 * \fn vreal VLineF::x2() const
 * Возвращает x-координату конечной точки.
 * \see p2()
 */
/*!
 * \fn vreal VLineF::y1() const
 * Возвращает y-координату начальной точки.
 * \see p1()
 */
/*!
 * \fn vreal VLineF::y2() const
 * Возвращает y-координату конечной точки.
 * \see p2()
 */
/*!
 * \fn vreal VLineF::dx() const
 * Возвращает длину по горизонтали.
 * \see dy() и pointAt()
 */
/*!
 * \fn vreal VLineF::dy() const 
 * Возвращает длину по вертикали.
 * \see dx() и pointAt()
 */
/*!
 * \fn bool VLineF::isNull() const
 * Возвращает \c true, если отрезок нулевой. Иначе \c false.
 */
/*!
 * \fn void VLineF::setP1(const VPointF &p1)
 * Устанавливает начальную точку в \a p1.
 * \see setP2() и p1()
 */
/*!
 * \fn void VLineF::setP2(const VPointF &p2)
 * Устанавливает конечную точку в \a p2.
 * \see setP1() и p2()
 */
/*!
 * \fn VLine VLineF::toLine() const
 * Возвращает целочисленную копию отрезка.
 * Начальные и конечные точки округляются до целых.
 * \see VLineF()
 */
/*!
 * \fn void VLineF::translate(const VPointF &offset)
 * Смещает отрезок на \a offset.
 */
/*!
 * \fn void VLineF::translate(vreal dx, vreal dy)
 * \overload \n
 * Смещает отрезок на \a dx по горизонтали и на \a dy
 * по вертикали.
 */
/*!
 * \fn VLineF VLineF::translated(const VPointF &offset) const
 * Возвращает отрезок, смещенные на \a offset.
 */
/*!
 * \fn VLineF VLineF::translated(vreal dx, vreal dy) const
 * \overload \n
 * Возвращает отрезок, смещенный на \a dx и \a dy
 * по горизонтали и вертикали соответственно.
 */
/*!
 * \fn bool VLineF::operator!=(const VLineF &line) const
 * Возвращает \c true, если этот отрезок не равен \a line.
 * Отрезки считаются не равными, если их начальные или конечные
 * (или обе сразу) точки не совпадают.
 */
/*!
 * \fn bool VLineF::operator==(const VLineF &line) const
 * Возвращает \c true, если этот отрезок равен \a line.
 * Отрезки считаются равными, если их начальные и конечные
 * точки совпадают.
 */

/*!
 * Возвращает длину отрезка.
 */
vreal VLineF::length() const
{
   int x = dx();
   int y = dy();
   return sqrt(x*x + y*y);
}

/*!
 * Устанавливает начальную точку в (\a x1, \a y1)
 * и конечную в (\a x2, \a y2).
 * \see setP1(), setP2(), p1() и p2()
 */
void VLineF::setLine(vreal x1, vreal y1, vreal x2, vreal y2)
{
    _p1 = VPointF(x1, y1);
    _p2 = VPointF(x2, y2);
}

// можно inline
/*!
 * Возвращает точку на отрезке. Функция возвращает начальную
 * точку, если \a t = 0, конечную, если \a t = 1.
 * \see dx() и dy()
 */
VPointF VLineF::pointAt(vreal t) const
{
    return VPointF(_p1.x() + dx()*t, _p2.y() + dy()*t);
}

/*!
 * Возвращает отрезок, перпендикулярный этому.
 * \image html vlinef-normalvector.png
 */
VLineF VLineF::normalVector() const
{
    return VLineF(_p1, _p1 + VPointF(-dy(), dx()));
}

// можно и inline
/*!
 * Устанавливает начальную точку в \a p1 и конечную в \a p2.
 * \see setP1(), setP2(), p1() и p2()
 */
void VLineF::setPoints(const VPointF &p1, const VPointF &p2)
{
    _p1 = p1;
    _p2 = p2;
}
