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
/*!
 * \fn VSize::VSize()
 * Создает недействительный объект размера (т.е. isValid() вернет \c false).
 * \see isValid()
 */
/*!
 * \fn VSize::VSize(int width, int height)
 * Создает размер с шириной \a width и высотой \a height.
 * \see setWidth() и setHeight()
 */
/*!
 * \fn int VSize::height() const
 * Возвращает высоту.
 * \see width() и setHeight()
 */
/*!
 * \fn bool VSize::isEmpty() const
 * Возвращает \c true, если высота и ширина меньше
 * или равны нулю. Иначе \c false.
 * \see isNull() и isValid()
 */
/*!
 * \fn bool VSize::isNull() const
 * Возвращает \c true, если высота и ширина равны нулю. Иначе \c false.
 * \see isEmpty() и isValid()
 */
/*!
 * \fn bool VSize::isValid() const
 * Возвращает \c true, если высота и ширина больше или равны 0.
 * Иначе \c false.
 * \see isNull() и isEmpty()
 */
/*!
 * \fn int &VSize::rheight()
 * Возвращает ссылку на высоту.\n
 * Использовании ссылки позволяет напрямую изменять высоту:
 * \code
 * VSize size(100, 10);
 * size.rheight() += 5;
 *
 * // size станет (100, 15)
 * \endcode
 * \see rwidth() и setHeight()
 */
/*!
 * \fn int &VSize::rwidth()
 * Возвращает ссылку на ширину.\n
 * Использовании ссылки позволяет напрямую изменять ширину:
 * \code
 * VSize size(100, 10);
 * size.rwidth() += 20;
 *
 * // size станет (120, 10)
 * \endcode
 * \see rheight() и setWidth()
 */
/*!
 * \fn void VSize::setHeight(int height)
 * Устанавливает высоту в \a height.
 * \see rheight(), height() и setWidth()
 */
/*!
 * \fn void VSize::setWidth(int width)
 * Устанавливает ширину в \a width.
 * \see rwidth(), width() и setHeight()
 */
/*!
 * \fn void VSize::transpose()
 * Меняет местами значения высоты и ширины.
 * \see setWidth() и setHeight()
 */
/*!
 * \fn int VSize::width() const
 * Возвращает высоту.
 * \see height() и setWidth()
 */

/*!
 * Возвращает размер, содержащий минимальные значения высоты
 * и ширины этого объекта и \a otherSize.
 * \see expandedTo()
 */
VSize VSize::boundedTo(const VSize &otherSize) const
{
    return VSize(vMin(_w, otherSize._w), vMin(_h, otherSize._h));
}

/*!
 * Возвращает размер, содержащий максимальные значения высоты
 * и ширины этого объекта и \a otherSize.
 * \see boundedTo()
 */
VSize VSize::expandedTo(const VSize &otherSize) const
{
    return VSize(vMax(_w, otherSize._w), vMax(_h, otherSize._h));
}

/*!
 * Умножает высоту и ширину на \a factor.\n
 * Помните, что результат округляется до целого.
 */
VSize &VSize::operator*=(vreal factor)
{
    _h = vRound(_h * factor);
    _w = vRound(_w * factor);
    return *this;
}

/*!
 * Складывает высоту и ширину этого объекта с
 * соответсвующими высотой и шириной \a size:
 * \code
 * VSize s(3, 7);
 * VSize r(-1, 4);
 * s += r;
 *
 * // s станет (2, 11)
 * \endcode
 */
VSize &VSize::operator+=(const VSize &size)
{
    _h += size._h;
    _w += size._w;
    return *this;
}

/*!
 * Вычитает из высоты и ширины этого объекта
 * высоту и ширину \a size:
 * \code
 * VSize s(3, 7);
 * VSize r(-1, 4);
 * s -= r;
 *
 * // s станет (4,3)
 * \endcode
 */
VSize &VSize::operator-=(const VSize &size)
{
    _h -= size._h;
    _w -= size._w;
    return *this;
}

/*!
 * Делит высоту и ширину на \a divisor.\n
 * Помните, что результат округляется до целого.
 */
VSize &VSize::operator/=(vreal divisor)
{
    if(!divisor) return *this;
    _h = vRound(_h / divisor);
    _w = vRound(_w / divisor);
    return *this;
}

/*!
 * \fn bool operator!=(const VSize &s1, const VSize &s2)
 * \relates VSize
 * Возвращает \c true, если \a s1 не равен \a s2. Иначе \c false.
 */
/*!
 * \fn const VSize operator*(vreal factor, const VSize &size)
 * \relates VSize
 * Умножает \a size на \a factor.
 */
/*!
 * \fn const VSize operator*(const VSize &size, vreal factor)
 * \relates VSize
 * \overload
 */
/*!
 * \fn const VSize operator+(const VSize &s1, const VSize &s2)
 * \relates VSize
 * Складывает \a s1 и \a s2 и возвращает копию.
 */
/*!
 * \fn const VSize operator-(const VSize &s1, const VSize &s2)
 * \relates VSize
 * Вычитает из \a s1 объект \a s2 и возвращает копию.
 */
/*!
 * \fn const VSize operator/(const VSize &size, vreal divisor)
 * \relates VSize
 * Делит \a size на \a divisor и возвращает округленный результат.
 */
/*!
 * \fn bool operator==(const VSize &s1, const VSize &s2)
 * \relates VSize
 * Возвращает \c true, если \a s1 равен \a s2. Иначе \c false.
 */

/*!
 * \class VSizeF
 * \brief Определяет размер на двумерной плоскости, используя вещественные числа.
 *
 * Размер определяется шириной (width()) и высотой (height()). Задать их можно
 * через функции setWidth(), setHeight() или используя арифметические операции.
 * Получить прямой доступ к высоте и ширине можно через rheight() и rwidth().
 * Наконец, можно поменять местами высоту и ширину с помощью transpose().
 *
 * Функция isValid() определяет, является ли размер действительным.
 * isEmpty() возвращает \c true, если высота и ширина меньше или равны 0.
 * isNull() возвращает \c true, если высота и ширина равны 0.
 *
 * Функция expandedTo() возвращает объект, содержащий максимальные значения
 * высоты и ширины. Напротив, boundedTo() возвращает объект, содержащий
 * минимальные значения высоты и ширины.
 *
 * Из VSizeF можно получить VSize, используя toSize(). Высота и ширина
 * округляются до целого.
 *
 * VSizeF можно сравнивать и передавать в функции.
 * \see VSize, VPointF
 */
/*!
 * \fn VSizeF::VSizeF()
 * Создает недействительный объект.
 * \see isValid()
 */
/*!
 * \fn VSizeF::VSizeF(const VSize &size)
 * Создает копию \a size в вещественных числах.
 * \see toSize()
 */
/*!
 * \fn VSizeF::VSizeF(vreal width, vreal height)
 * Создает размер с высотой (\a height) и шириной (\a width).
 */
/*!
 * \fn vreal VSizeF::height() const
 * Возвращает высоту.
 * \see width() и setHeight()
 */
/*!
 * \fn bool VSizeF::isEmpty() const
 * Возвращает \c true, если высота и ширина меньше или
 * равны 0. Иначе \c false.
 * \see isNull() и isValid()
 */
/*!
 * \fn bool VSizeF::isNull() const
 * Возвращает \c true, если высота и ширина равны 0.
 * Иначе \c false.
 * \see isValid() и isEmpty()
 */
/*!
 * \fn bool VSizeF::isValid() const
 * Возвращает \c true, если высота и ширина больше или
 * равны 0. Иначе \c false.
 * \see isNull() и isEmpty()
 */
/*!
 * \fn vreal &VSizeF::rheight()
 * Возвращает ссылку на высоту.\n
 * Используя ссылки, можно напрямую изменять высоту:
 * \code
 * VSizeF size(100, 10.2);
 * size.rheight() += 5.5;
 * // size станет (100, 15.7)
 * \endcode
 * \see rwidth() и setHeight()
 */
/*!
 * \fn vreal &VSizeF::rwidth()
 * Возвращает ссылку на ширину.\n
 * Использование ссылки позволяет напрямую изменять ширину:
 * \code
 * VSizeF size(100.3, 10);
 * size.rwidth() += 20.5;
 * // size станет (120.8, 10)
 * \endcode
 * \see rheight() и setWidth()
 */
/*!
 * \fn void VSizeF::setHeight(vreal height)
 * Устанавливает высоту в \a height.
 * \see height(), rheight() и setWidth()
 */
/*!
 * \fn void VSizeF::setWidth(vreal width)
 * Устанавливает ширину в \a width.
 * \see width(), rwidth() и setHeight()
 */
/*!
 * \fn VSize VSizeF::toSize() const
 * Возвращает целочисленную копию этого размера.\n
 * Ширина и высота округляются до целого.
 * \see VSizeF()
 */
/*!
 * \fn void VSizeF::transpose()
 * Меняет местами высоту и ширину.
 * \see setWidth() и setHeight()
 */
/*!
 * \fn vreal VSizeF::width() const
 * Возвращает ширину.
 * \see height() и setWidth()
 */

/*!
 * Возвращает размер, содержащий минимальные значения высоты
 * и ширины этого объекта и \a otherSize.
 * \see expandedTo()
 */
VSizeF VSizeF::boundedTo(const VSizeF &otherSize) const
{
    return VSizeF(vMin(_w, otherSize._w), vMin(_h, otherSize._h));
}

/*!
 * Возвращает размер, содержащий максимальные значения высоты
 * и ширины этого объекта и \a otherSize.
 */
VSizeF VSizeF::expandedTo(const VSizeF &otherSize) const
{
    return VSizeF(vMax(_w, otherSize._w), vMax(_h, otherSize._h));
}

/*!
 * Умножает высоту и ширину на \a factor и возвращает ссылку.
 */
VSizeF &VSizeF::operator*=(vreal factor)
{
    _h *= factor;
    _w *= factor;
    return *this;
}

/*!
 * Складывает высоту и ширину этого объект и \a size:
 * \code
 * VSizeF s(3, 7);
 * VSizeF r(-1, 4);
 * s += r;
 * // s станет (2, 11)
 * \endcode
 */
VSizeF &VSizeF::operator+=(const VSizeF &size)
{
    _h += size._h;
    _w += size._w;
    return *this;
}

/*!
 * Вычитает из высоты и ширины этого объекта
 * высоту и ширину \a size.
 * \code
 * VSizeF s(3, 7);
 * VSizeF r(-1, 4);
 * s -= r;
 * // s станет (4, 3)
 * \endcode
 */
VSizeF &VSizeF::operator-=(const VSizeF &size)
{
    _h -= size._h;
    _w -= size._w;
    return *this;
}

/*!
 * Делит высоту и ширину на \a divisor и возвращает ссылку.
 */
VSizeF &VSizeF::operator/=(vreal divisor)
{
    if(!divisor) return *this;

    _h /= divisor;
    _w /= divisor;
    return *this;
}

/*!
 * \fn bool operator!=(const VSizeF &s1, const VSizeF &s2)
 * \relates VSizeF
 * Возвращает \c true, если \a s1 не равен \a s2. Иначе \c false.
 */
/*!
 * \fn const VSizeF operator*(const VSizeF &size, vreal factor)
 * \relates VSizeF
 * Умножает \a size на \a factor и возвращает копию.
 */
/*!
 * \fn const VSizeF operator*(vreal factor, const VSizeF &size)
 * \relates VSizeF
 * \overload
 */
/*!
 * \fn const VSizeF operator+(const VSizeF &s1, const VSizeF &s2)
 * \relates VSizeF
 * Возвращает сумму \a s1 и \a s2.
 */
/*!
 * \fn const VSizeF operator-(const VSizeF &s1, const VSizeF &s2)
 * \relates VSizeF
 * Вычитает из \a s1 объект \a s2 и возвращает результат.
 */
/*!
 * \fn const VSizeF operator/(const VSizeF &size, vreal divisor)
 * \relates VSizeF
 * Делит высоту и ширниу \a size на \a divisor и возвращает результат.
 */
/*!
 * \fn bool operator==(const VSizeF &s1, const VSizeF &s2)
 * \relates VSizeF
 * Возвращает \c true, если \a s1 равен \a s2. Иначе \c false.
 */

