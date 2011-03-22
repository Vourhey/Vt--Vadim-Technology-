#include "vpair.h"

/*!
 * \class VPair
 * \brief Шаблонный класс для хранения пары элементов.
 *
 * VPair<T1, T2> можно использовать в вашей программе, если класс STL pair
 * недоступен. В классе хранится пара знечений. Одни элемент имеет тип T1,
 * второй - T2. Класс можно использовать как возвращаемое значение функции,
 * если нужно вернуть пару элементов, или как тип данных для контейнеров.
 *
 * Дальше показано, как использовать VPair для хранения const char * и
 * double:
 * \code
 * VPair<const char *, double> pair;
 * \endcode
 * Можно обращатся к элементом непосредственно:
 * \code
 * pair.first = "pi";
 * pair.second = 3.14159265358979323846;
 * \endcode
 * Оби типа данных для VPair должны быть назначаемыми. Для ваших классов
 * лучше использовать указатели.
 */
/*!
 * \typedef T1 VPair::first_type
 * Синоним для типа данных первого элемента (T1).
 * \see first
 */
/*!
 * \typedef T2 VPair::second_type
 * Синоним для типа данных второго элемента (T2).
 * \see second
 */
/*!
 * \fn VPair::VPair()
 * Создает пустую пару. \c first и \c second элементы инициализируются 
 * значениями по умолчанию.
 */
/*!
 * \fn VPair::VPair(const T1 &value1, const T2 &value2)
 * Создает пару элементов из \a valu2 и \a value2.
 * \see vMakePair()
 */
/*!
 * \fn VPair<T1, T2> &VPair::operator=(const VPair<T1, T2> &other)
 * Назначает этой паре значения \a other.
 */
/*!
 * \var T1 VPair::first
 * Первый элемент в паре
 */
/*!
 * \var T2 VPair::second
 * Второй элемент в паре
 */
/*!
 * \fn VPair<T1, T2> vMakePair(const T1 &value1, const T2 &value2)
 * \relates VPair
 * Возвращает VPair<T1, T2> содержащую \a value1 и \a value2. Пример:
 * \code
 * VLinkedList<VPair<int, double> > list;
 * list.append(vMakePair(66, 3.14159));
 * \endcode
 * Это равносильно VPair<T1, T2(\a value1, \a value2), но обычно
 * занимает меньше места в коде.
 */
/*!
 * \fn bool operator!=(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
 * \relates VPair
 * Возвращает \c true, если \a p1 не равна \a p2. Иначе \c false.\n
 * Две пары считаются не равными, если их первые или второые элементы
 * не равны. Функция требует, чтобы типы данных поддерживали operator==().
 */
/*!     
 * \fn bool operator<(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
 * \relates VPair
 * Возвращает \c true, если \a p1 меньше \a p2. Иначе \c false.\n
 * Одна пара меньше другой, если первый и второй элемент первой пары
 * меньше соответствующих элементов второй пары.
 * Функция требует, чтобы типы данных поддерживали operator<().
 */
/*!
 * \fn bool operator<=(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
 * \relates VPair
 * Возвращает \c true, если \a p1 меньше или равно \a p2. Иначе \c false.\n
 * Функция требует, чтобы типы данных поддерживали operator<().
 */
/*!
 * \fn bool operator==(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
 * \relates VPair
 * Возвращает \c true, если \a p1 равна \a p2. Иначе \c false.\n
 * Пары считаются равными, если первые и вторые элементы соответственно
 * равны. Функция требует, чтобы типы данных поддерживали operator==().
 */
/*!
 * \fn bool operator>(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
 * \relates VPair
 * Возвращает \c true, если \a p1 меньше \a p2. Иначе \c false.\n
 * Пара считается больше другой, если первый и второй элемент одной
 * пары больше соответствующих элементов второй. Функция требует, чтобы
 * типы данных поддреживали operator<().
 */
/*!
 * \fn bool operator>=(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
 * \relates VPair
 * Возвращает \c true, если \a p1 больше или равна \a p2. Иначе \c false.\n
 * Функция требует, чтобы типы данных поддерживали operator<().
 */
