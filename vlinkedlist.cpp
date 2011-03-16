#include "vlinkedlist.h"

/*!
 * \class VLinkedList::const_iterator
 * \brief Реализует константный STL итератор для VLinkedList
 *
 * VLinkedList в равной степени поддерживает STL и Java итераторы.
 * STL итераторы более низкоуровневы, но более громоздкие для использования.
 * С другой стороны они могут быть быстрее Java итераторов.
 * Для разработчиков, знакомых с STL, они будут более приемлемы.
 *
 * VLinkedList<T>::const_iterator позволяет вам перебрать контейнер VLinkedList<T>.
 * В общем случае, использовать константный итератор для неконстантного 
 * VLinkedList хорошая практика, пока вы изменяете контейнер. Константный
 * итератор может оказаться быстрее и улучшить безопасность вашего кода.
 *
 * По умолчанию VLinkedList::const_iterator не инициализируется. Вы должны
 * задать итератор, используя VLinkedList::constBegin(), VLinkedList::constEnd()
 * или VLinkedList::insert() до того, как начнете перебирать элементы.
 * Дальше показан типичный цикл перебора всех элементов списка:
 * \code
 * VLinkedList<int> list;
 * list << 1 << 2 << 4 << 7 << 9;
 * ...
 * VLinkedList<int>::const_iterator i;
 * for(i = list.constBegin(); i != list.constEnd(); ++i)
 *     cout << *i << endl;
 * \endcode
 *
 * // TODO:::TODO Дописать про функции-алгоритмы
 *
 * Можно использовать несколько итераторов на один и тот же список.
 * Если вы добавляете элементы в список, существующие будут оставаться
 * в силе. Если элемент был удален, то итератор, указывающий на него,
 * будет недействителен.
 * \see VLinkedList::iterator и VLinkedListIterator
 */

/*!
 * \fn VLinkedList::const_iterator::const_iterator()
 * Создает неинициализированный итератор.\n
 * Функции operator*() и operator++() нельзя вызывать до инициализации. Используйте
 * operator=() чтобы назначить итератору контейнер.
 * \see VLinkedList::constBegin() и VLinkedList::constEnd()
 */
/*!
 * \fn VLinkedList::const_iterator::const_iterator(const const_iterator &other)
 * Создает копию \a other.
 */
/*!
 * \fn VLinkedList::const_iterator::const_iterator(iterator other)
 * Создает копию \a other.
 */
/*!
 * \fn bool VLinkedList::const_iterator::operator!=(const const_iterator &other) const
 * Возвращает \c true если \a other и этот итератор указывают на разные элементы.
 * Иначе \c false.
 * \see operator==()
 */
/*!
 * \fn const T &VLinkedList::const_iterator::operator*() const
 * Возвращает ссылку на текущий элемент.
 * \see operator->()
 */
/*!
 * \fn const_iterator VLinkedList::const_iterator::operator+(int j) const
 * Возвращает итератор на элемент, находящийся на \a j позиций
 * дальше текущего. (если \a j отрицательная, то на \a j
 * позиций в обратную сторону.)
 * \see operator-()
 */
/*!
 * \fn const_iterator &VLinkedList::const_iterator::operator++()
 * Префиксная форма оператора инкремента (т.е. ++it).
 * Перемещает итератор на следующий элемент и возвращает его.
 * \n Если вызвать эту функцию для VLinkedList::constEnd(), то
 * результат неопределен.
 * \see operator--()
 */
/*!
 * \fn const_iterator VLinkedList::const_iterator::operator++(int)
 * \overload \n
 * Постфиксная форма оператора инкремента (it++). Сначала возвращает
 * элемент, а потом перемещает на следующую позицию.
 */
/*!
 * \fn const_iterator &VLinkedList::const_iterator::operator+=(int j)
 * Перемещает итератор на \a j позици. Для больших значений
 * эта функция может быть медленной.
 * \see operator-=() и operator+()
 */
/*!
 * \fn const_iterator VLinkedList::const_iterator::operator-(int j) const
 * Возвращает итератор, смещенный на \a j позиций назад (или вперед, если
 * \a j отрицательна).
 * \see operator+()
 */
/*!
 * \fn const_iterator &VLinkedList::const_iterator::operator--()
 * Префиксная форма декремента (--it). Смещает итератор на одну позицию
 * назад и возвращает элемент.
 * \n Результат неопределен для VLinkedList::begin()
 * \see operator++()
 */
/*!
 * \fn const_iterator VLinkedList::const_iterator::operator--(int)
 * \overload \n
 * Постфиксная форма декремента (it--). Сначала возвращает текущий
 * элемент, а потом уменьшает итератор.
 */
/*!
 * \fn const_iterator &VLinkedList::const_iterator::operator-=(int j)
 * Смещает итератор на \a j позиций назад (или вперед если \a j
 * отрицательна).
 * \see operator+=() и operator-()
 */
/*!
 * \fn const T *VLinkedList::const_iterator::operator->() const
 * Возвращает указатель на текущий элемент.
 * \see operator*()
 */
/*!
 * \fn const_iterator &VLinkedList::const_iterator::operator=(const const_iterator &other)
 * Назначает \a other этому итератору.
 */
/*!
 * \fn bool VLinkedList::const_iterator::operator==(const const_iterator &other) const
 * Возвращает \c true, если \a other и этот итератор указывают на один и тот же
 * элемент. Иначе \c false.
 * \see operator!=()
 */
