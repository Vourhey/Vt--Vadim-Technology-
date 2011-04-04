#include "vpoint.h"

/*!
 * \class VPoint
 * \brief Определяет точку на плоскости, используя целые числа
 *
 * Точка определяется двумя координатами (\c x, \c y), которые можно
 * получить через x() и y(). Функция isNull() определяет, установлены
 * ли обе координаты в 0 и возвращает \c true в случае успеха. 
 * Установить координаты можно, используя функции setX() и setY().
 * Или, используя альтернативный подход, rx() и ry(). Последние
 * две функции возвращает ссылку на координаты для непосредственного
 * изменения.
 *
 * Задать точку можно следующим образом:
 * \code
 * VPoint p;
 *
 * p.setX(p.x() + 1);
 * p += VPoint(1, 0);
 * p.rx()++;
 * // p: [3, 0]
 * \endcode
 *
 * Объекты VPoint можно складывать и вычитать: будут
 * складываться/вычитаться соответствующие координаты. Так же можно
 * делать и умножать координаты точки на \c int или \c vreal.
 *
 * Плюс, VPoint определяет функцию manhattanLength(), которая дает
 * длину, если бы точка интерпретировалась как отрезок. Результат
 * пренебрежительно округлен до истины. Наконец, VPoint можно 
 * сравнивать и передавать в функции.
 * \see VPointF
 */
/*!
 * \fn VPoint::VPoint()
 * Создает нулевую точку, т.е. координаты устанавливаются в 0.
 * \see isNull()
 */
/*!
 * \fn VPoint::VPoint(int x, int y)
 * Создает точку с координатами (\a x, \a y).
 * \see setX() и setY()
 */
/*!
 * \fn int &VPoint::rx()
 * Возвращает ссылку на x-координату.\n
 * Используя ссылку можно напрямую менять x, например:
 * \code
 * VPoint p(1, 2);
 * p.rx()--; // p станет (0, 2)
 * \endcode
 * \see x() и setX()
 */
/*!
 * \fn int &VPoint::ry()
 * Возвращает ссылку на y-координату.\n
 * Используя ссылку можно напрямую менять y, например:
 * \code
 * VPoint p(1, 2);
 * p.ry()++; // p станет (1, 3)
 * \endcode
 * \see y() и setY()
 */
/*!
 * \fn void VPoint::setX(int x)
 * Устанавливает x-координату в \a x.
 * \see x() и setY()
 */
/*!
 * \fn void VPoint::setY(int y)
 * Устанавливает y-координату в \a y.
 * \see y() и setX()
 */
/*!
 * \fn int VPoint::x() const
 * Возвращает x-координату.
 * \see setX() и rx()
 */
/*!
 * \fn int VPoint::y() const
 * Возвращает y-координату.
 * \see setY() и ry()
 */
/*!
 * \fn bool operator!=(const VPoint &p1, const VPoint &p2)
 * \relates VPoint
 * Возвращает \c true, если \a p1 равна \a p2. Иначе \c false.
 */
/*!
 * \fn const VPoint operator*(const VPoint &point, vreal facotr)
 * \relates VPoint
 * Возвращает копию точки \a point, умноженную на \a factor.
 * \n Для получения не приближенного результата используйте VPointF.
 * \see VPoint::operator*=()
 */
/*!
 * \fn const VPoint operator*(vreal factor, const VPoint &point)
 * \relates VPoint
 * \overload
 */
/*!
 * \fn const VPoint operator+(const VPoint &p1, const VPoint &p2)
 * \relates VPoint
 * Возвращает VPoint, являющийся результатом сложения \a p1 и \a p2.
 * \see VPoint::operator+=()
 */
/*!
 * \fn const VPoint operator-(const VPoint &p1, const VPoint &p2)
 * \relates VPoint
 * Возвращает объект, являющийся результатом вычитания \a p2 из \a p1.
 * \see VPoint::operator-=()
 */
/*!
 * \fn const VPoint operator-(const VPoint &point)
 * \relates VPoint
 * Возвращает объект с противоположными координатами \a point.
 * Равносильно \c VPoint(0,0) \c - \c point.
 */
/*!
 * \fn const VPoint operator/(const VPoint &point, vreal divisor)
 * \relates VPoint
 * Возвращает объект, содержащий результат деления \a point на \a divisor.
 * Если вам не нужны приближенные результаты, используйте VPointF.
 */

/*!
 * Возвращает \c true, если x и y установлены в 0. Иначе \c false.
 */
bool VPoint::isNull() const
{
    return (_x == 0) && (_y == 0);
}

/*!
 * Возвращает сумму абсолютных значений x и y. Обычно эту величину
 * называют "Manhattan length".
 */
int VPoint::manhattanLength() const
{
    return vAbs(_x) + vAbs(_y);
}

/*!
 * Умножает каждую координату на \a factor и возвращает ссылку на эту
 * точку. Например:
 * \code
 * VPoint p(-1, 4);
 * p *= 2.5;  // p станет (-3, 10)
 * \endcode
 * Помните, что результат округляется до целого. 
 * Если вы хотите большую точность, используйте VPointF.
 * \see operator/=()
 */
VPoint &VPoint::operator*=(vreal factor)
{
    _x = vRound(_x * factor);
    _y = vRound(_y * factor);
    return *this;
}

/*!
 * Складывает соответствующие координаты этой точки
 * с точкой \a point. Например:
 * \code
 * VPoint p(3, 7);
 * VPoint q(-1, 4);
 * p += q; // p станет (2, 11)
 * \endcode
 * \see operator-=()
 */
VPoint &VPoint::operator+=(const VPoint &point)
{
    _x += point._x;
    _y += point._y;
    return *this;
}

/*!
 * Вычитает из соответствующих координат этой точки
 * координаты \a point. Например:
 * \code
 * VPoint p(3, 7);
 * VPoint q(-1, 4);
 * p -= q; // p станет (4, 3)
 * \endcode
 * \see operator+=()
 */
VPoint &VPoint::operator-=(const VPoint &point)
{
    _x -= point._x;
    _y -= point._y;
    return *this;
}

/*!
 * Делит каждую координату на \a divisor и возвращает
 * ссылку на эту точку. Например:
 * \code
 * VPoint p(-3, 10);
 * p /= 2.5; // p станет (-1, 4)
 * \endcode
 * Помните, что результат округляется до целого. Если вам
 * нужна большая точность, используйте VPointF.
 * \see operator*=()
 */
VPoint &VPoint::operator/=(vreal divisor)
{
    if(!divisor) return *this; // делить на ноль нельзя

    _x = vRound(_x / divisor);
    _y = vRound(_y / divisor);
    return *this;
}

/*!
 * \relates VPoint
 * Возвращает \c true, если \a p1 и \a p2 равны. Иначе \c false.
 */
bool operator==(const VPoint &p1, const VPoint &p2)
{
    return (p1._x == p2._x) && (p1._y == p2._y);
}

/*!
 * \class VPointF
 * \brief Определяет точку на плоскости, используя вещественные числа.
 *
 * Точка определяется двумя координатами \c x и \c y, которые можно получить
 * через функции x() и y(). Координаты выражаются в вещественных числах.
 * Функция isNull() возвращает \c true, если обе координаты установлены в 0.
 * Задать координаты можно функциями setX(), setY() или rx() и ry(). Последние
 * возвращает ссылку.
 *
 * Задать точку можно следующим образом:
 * \code
 * VPointF p;
 *
 * p.setX(p.x() + 1.0);
 * p += VPointF(1.0, 0.0);
 * p.rx()++;
 * \endcode
 *
 * Точки можно складывать и вычитать (координаты 
 * складываются/вычитаются соответственно). Можно умножать или делать на
 * целое (\c int) или дробное (\c vreal) число.
 *
 * Из VPointF можно получить целочисленную копию VPoint, вызвав toPoint().
 * Каждая координата округляется. Наконец, VPointF можно сравнивать
 * и передавать в функции.
 * \see VPoint
 */
/*!
 * \fn VPointF::VPointF()
 * Создает нулевую точку, т.е. с координатами (0.0, 0.0).
 * \see isNull()
 */
/*!
 * \fn VPointF::VPointF(const VPoint &point)
 * Создает копию из \a point.
 * \see toPoint()
 */
/*!
 * \fn VPointF::VPointF(vreal x, vreal y)
 * Создает точку с координатами (\a x, \a y).
 * \see setX() и setY()
 */
/*!
 * \fn vreal &VPointF::rx()
 * Возвращает ссылку на координату \c x.\n
 * Использовании ссылки позволяет напрямую менять \c x:
 * \code
 * VPointF p(1.1, 2.5);
 * p.rx()--; // p станет (0.1, 2.5)
 * \endcode
 * \see x() и setX()
 */
/*!
 * \fn vreal &VPointF::ry()
 * Возвращает ссылку на координату \c y.\n
 * Использовании ссылки позволяет напрямую менять \c y:
 * \code
 * VPointF p(1.1, 2.5);
 * p.ry()++; // p станет (1.1, 3.5)
 * \endcode
 * \see y() и setY()
 */
/*!
 * \fn void VPointF::setX(vreal x)
 * Устанавливает координату \c x в \a x.
 * \see x() и setY()
 */
/*!
 * \fn void VPointF::setY(vreal y)
 * Устанавливает координату \c y в \a y.
 * \see y() и setX()
 */
/*!
 * \fn VPoint VPointF::toPoint() const
 * Округляет координаты до целого и возвращает результат как VPoint.
 * \see VPointF()
 */
/*!
 * \fn vreal VPointF::x() const
 * Возвращает \c x координату.
 * \see setX() и rx()
 */
/*!
 * \fn vreal VPointF::y() const
 * Возвращает \c y координату.
 * \see setY() и ry()
 */

/*!
 * Возвращает \c true, если обе координаты установлены в 0.
 * Иначе \c false.
 */
bool VPointF::isNull() const
{
    return (_x == 0.0) && (_y == 0.0);
}

/*!
 * Возвращает сумму абсолютных значений \c x и \c y.
 * \see VPoint::manhattanLength()
 */
vreal VPointF::manhattanLength() const
{
    return vAbs(_x) + vAbs(_y);
}

/*!
 * Умножает координаты точки на \a factor и возвращает ссылку:
 * \code
 * VPointF p(-1.1, 4.1);
 * p *= 2.5;   // p станет (-2.75, 10.25)
 * \endcode
 * \see operator/=()
 */
VPointF &VPointF::operator*=(vreal factor)
{
    _x *= factor;
    _y *= factor;
    return *this;
}

/*!
 * Складывает соответствующие координаты этой точки с точкой \a point:
 * \code
 * VPointF p(3.1, 7.1);
 * VPointF q(-1.0, 4.1);
 * p += q; // p станет (2.1, 11.2)
 * \endcode
 * \see operator-=()
 */
VPointF &VPointF::operator+=(const VPointF &point)
{
    _x += point._x;
    _y += point._y;
    return *this;
}

/*!
 * Вычитает из координат этой точки координаты \a point:
 * \code
 * VPointF p(3.1, 7.1);
 * VPointF q(-1.0, 4.1);
 * p -= q; // p станет (4.1, 3.0)
 * \endcode
 * \see operator+=()
 */
VPointF &VPointF::operator-=(const VPointF &point)
{
    _x -= point._x;
    _y -= point._y;
    return *this;
}

/*!
 * Делит координаты этой точки на \a divisor и возвращает ссылку:
 * \code
 * VPointF p(-2.75, 10.25);
 * p /= 2.5;   // p станет (-1.1, 4.1)
 * \endcode
 * \see operator*=()
 */
VPointF &VPointF::operator/=(vreal divisor)
{
    if(!divisor) return *this; // делить на ноль нельзя

    _x /= divisor;
    _y /= divisor;
    return *this;
}

/*!
 * \fn bool operator!=(const VPointF &p1, const VPointF &p2)
 * \relates VPointF
 * Возвращает \c true, если \a p1 не равна \a p2. Иначе \c false.
 */
/*!
 * \fn const VPointF operator*(const VPointF &point, vreal factor)
 * \relates VPointF
 * Возвращает копию \a point, умноженную на \a factor.
 * \see VPointF::operator*=()
 */
/*!
 * \fn const VPointF operator*(vreal factor, const VPointF &point)
 * \relates VPointF
 * \overload
 */
/*!
 * \fn const VPointF operator+(const VPointF &p1, const VPointF &p2)
 * \relates VPointF
 * Возвращает сумму \a p1 и \a p2.
 * \see VPointF::operator+=()
 */
/*!
 * \fn const VPointF operator-(const VPointF &p1, const VPointF &p2)
 * \relates VPointF
 * Возвращает разность между \a p1 и \a p2.
 * \see VPointF::operator-=()
 */
/*!
 * \fn const VPointF operator-(const VPointF &point)
 * \relates VPointF
 * Возвращает копию \a point с противоположными значениями координат.
 */
/*!
 * \fn const VPointF operator/(const VPointF &point, vreal divisor)
 * \relates VPointF
 * Возвращает копию \a point, координаты которой поделены на \a divisor.
 * \see VPointF::operator/=()
 */

/*!
 * \relates VPointF
 * Возвращает \c true, если \a p1 равна \a p2. Иначе \c false.
 */
bool operator==(const VPointF &p1, const VPointF &p2)
{
    return (p1._x == p2._x) && (p1._y == p2._y);
}
