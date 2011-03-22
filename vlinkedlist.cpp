#include "vlinkedlist.h"

/*!
 * \class VLinkedList
 * \brief Шаблонный класс, реализующий связный список.
 *
 * VLinkedList<T> один из классов-контейнеров библиотеки Vt.
 * Он реализует список элементов, доступ к которым осуществляется
 * посредством итераторов, вставка и удаление элементов всегда
 * требуют константного времени.
 *
 * * TODO:::TODO * дописать про различия между контейнерами.
 *
 * В следующем примере создается список для VTime и для целых чисел:
 * \code
 * VLinkedList<int> integerList;
 * VLinkedList<VTime> timeList;
 * \endcode
 * VLinkedList хранит список элементов. По умолчанию создается пустой
 * список. Для вставки элементов можно использовать operator<<():
 * \code
 * VLinkedList<int> list;
 * list << 1 << 2 << 3;
 * // list: [1, 2, 3]
 * \endcode
 *
 * Для получения первого или последнего элемента используйте first()
 * или last(). Если хотите удалить первый или последний - removeFirst()
 * или removeLast(). Для удаления всех вхождений одного элемента
 * используйте removeAll().
 *
 * Обычно требуется удалить первый или последний элемент из списка
 * и сделать что-нибудь с ним. Для этого существуют функции
 * takeFirst() и takeLast(). В следующем примере одновременно
 * удаляются элементы из списка и удаляются объекты:
 * \code
 * VLinkedList<VTime *> list;
 * ...
 * while(!list.isEmpty())
 *     delete list.takeFirst();
 * \endcode
 *
 * Тип данных для VLinkedList должен быть назначаемым. Это все стандартные
 * типы и указатели. Некоторые функции требуют оператора сравнения operator==().
 *
 * Если вы хотите вставлять, изменять или удалять элементы вы должны 
 * использовать итератор. VLinkedList поддерживает Java (VLinkedListIterator и 
 * VMutableLinkedListIterator) и STL итераторы (VLinkedList::const_iterator и
 * VLinkedList::iterator). Смотрите отдельно документацию по каждому из них.
 * \see VList и VVector
 */

/*!
 * \typedef VLinkedList::ConstIterator
 * Синоним для VLinkedList::const_iterator в стиле Vt. 
 */
/*!
 * \typedef VLinkedList::Iterator
 * Синоним для VLinkedList::iterator в стиле Vt.
 */
/*!
 * \typedef VLinkedList::const_pointer
 * Синоним для const T *. Для STL совместимости.
 */
/*!
 * \typedef VLinkedList::const_reference
 * Синоним для const T &. Для STL совместимости.
 */
/*!
 * \typedef VLinkedList::pointer
 * Синоним для T *. Для STL совместимости.
 */
/*!
 * \typedef VLinkedList::reference
 * Синоним для T &. Для STL совместимости.
 */
/*!
 * \typedef VLinkedList::size_type
 * Синоним для int. Для STL совместимости.
 */
/*!
 * \typedef VLinkedList::value_type
 * Синоним для T. Для STL совместимости.
 */

/*!
 * \fn VLinkedList::VLinkedList()
 * Создает пустой список.
 */
/*!
 * \fn VLinkedList::VLinkedList(const VLinkedList<T> &other)
 * Конструктор копий.
 * \see operator=().
 */
/*!
 * \fn VLinkedList::~VLinkedList()
 * Деструктор. Все итераторы становяться недействительными.
 */
/*!
 * \fn void VLinkedList::append(const T &value)
 * Вставляет \a value в конец списка.
 *
 * Пример:
 * \code
 * VLinkedList<int> list;
 * list.append(1);
 * list.append(2);
 * list.append(3);
 * // list: [1, 2, 3]
 * \endcode
 * Это равносильно list.insert(end(), \a value).
 * \see operator<<(), prepend() и insert()
 */
/*!
 * \fn T &VLinkedList::back()
 * Эта функция нужна для совместимости с STL. Равносильно last().
 */
/*!
 * \fn const T &VLinkedList::back() const
 * \overload
 */
/*!
 * \fn iterator VLinkedList::begin()
 * Возвращает STL итератор, указывающий на первый элемент.
 * \see constBegin() и end()
 */
/*!
 * \fn const_iterator VLinkedList::begin() const
 * \overload
 */
/*!
 * \fn void VLinkedList::clear()
 * Удаляет все элементы списка.
 * \see removeAll()
 */
/*!
 * \fn const_iterator VLinkedList::constBegin() const
 * Возвращает STL итератор, указывающий на первый элемент списка.
 * \see begin() и constEnd()
 */
/*!
 * \fn const_iterator VLinkedList::constEnd() const
 * Возвращает STL итератор, указывающий на воображаемый
 * элемент после последнего.
 * \see constBegin() и end()
 */
/*!
 * \fn bool VLinkedList::contains(const T &value) const
 * Возвращает \c true если список содержит хотя бы один элемент
 * \a value. Иначе \c false. \n
 * Эта функция требует, чтобы тип данных поддерживал operator==().
 * \see VLinkedListIterator::findNext() и VLinkedListIterator::findPrevious()
 */
/*!
 * \fn int VLinkedList::count(const T &value) const
 * Возвращает число вхождений \a value в список.\n
 * Функция требует, чтобы тип данных поддерживал operator==().
 * \see contains()
 */
/*!
 * \fn int VLinkedList::count() const
 * Равносильно size().
 */
/*!
 * \fn bool VLinkedList::empty() const
 * Для совместимости с STL. Равносильно isEmpty().
 */
/*!
 * \fn iterator VLinkedList::end()
 * Возвращает STL итератор, указывающий на воображаемый элемент
 * после последнего.
 * \see begin() и constEnd()
 */
/*!
 * \fn const_iterator VLinkedList::end() const
 * \overload
 */
/*!
 * \fn bool VLinkedList::endsWith(const T &value) const
 * Возвращает \c true, если последний элемент списка равен \a value.
 * Иначе \c false.
 * \see isEmpty() и last()
 */
/*!
 * \fn iterator VLinkedList::erase(iterator pos)
 * Удаляет элемент, на который указывает \a pos и возвращает итератор
 * на следующий в списке (который может оказаться end()).
 * \see insert()
 */
/*!
 * \fn iterator VLinkedList::erase(iterator begin, iterator end)
 * \overload \n
 * Удаляет все элементы начиная с \a begin и до \a end (на не включая его).
 */
/*!
 * \fn T &VLinkedList::first()
 * Возвращает ссылку на первый элемент в списке. Предполагается, что
 * список не пустой.
 * \see last() и isEmpty()
 */
/*!
 * \fn const T &VLinkedList::first() const
 * \overload
 */
/*!
 * \fn T &VLinkedList::front()
 * Для STL совместимости. Равносильно first()
 */
/*!
 * \fn const T &VLinkedList::front() const
 * \overload
 */
/*!
 * \fn iterator VLinkedList::insert(iterator before, const T &value)
 * Вставляет \a value до элемента, на который указывает \a before.
 * Возвращает итератор, указывающий на вставленный элемент.
 * \see erase()
 */
/*!
 * \fn bool VLinkedList::isEmpty() const
 * Возвращает \c true, если список не содержит элементов.
 * Иначе \c false.
 * \see size()
 */
/*!
 * \fn T &VLinkedList::last()
 * Возвращает ссылку на последний элемент в списке. Предполагается
 * что список не пустой.
 * \see first() и isEmpty()
 */
/*!
 * \fn const T &VLinkedList::last() const
 * \overload
 */
/*!
 * \fn void VLinkedList::pop_back()
 * Для STL совместимости. Равносильно removeLast()
 */
/*!
 * \fn void VLinkedList::pop_front()
 * Для STL совместимости. Равносильно removeFirst()
 */
/*!
 * \fn void VLinkedList::prepend(const T &value)
 * Вставляет \a value в начало списка.\n
 * Пример:
 * \code
 * VLinkedList<int> list;
 * list.prepend(1);
 * list.prepend(2);
 * list.prepend(3);
 * // list: [3, 2, 1]
 * \endcode
 * Это равносильно list.insert(begin(), \a value).
 * \see append() и insert()
 */
/*!
 * \fn void VLinkedList::push_back(const T &value)
 * Для STL совместимости. Равносильно append(\a value).
 */
/*!
 * \fn void VLinkedList::push_front(const T &value)
 * Для STL совместимости. Равносильно prepend(\a value).
 */
/*!
 * \fn int VLinkedList::removeAll(const T &value)
 * Удаляет все вхождения \a value в список.
 * \nПример:
 * \code
 * VLinkedList<int> list;
 * list << 1 << 2 << 1 << 3 << 5;
 * list.removeAll(1);
 * // list: [2, 3, 5]
 * \endcode
 * Функция требует, чтобы тип данных поддерживал operator==()
 * \see insert()
 */
/*!
 * \fn void VLinkedList::removeFirst()
 * Удаляет первый элемент из списка.\n
 * Равносильно erase(begin()).
 * \see removeLast()
 */
/*!
 * \fn void VLinkedList::removeLast()
 * Удаляет последний элемент из списка.
 * \see removeFirst() и erase()
 */
/*!
 * \fn bool VLinkedList::removeOne(const T &value)
 * Удаляет первое вхождение \a value в списке. Возвращает
 * \c true в случае удачи. Иначе \c false.\n
 * Пример:
 * \code
 * VLinkedList<int> list;
 * list << 1 << 2 << 1 << 3 << 5;
 * list.removeOne(1);
 * // list: [2, 1, 3, 5]
 * \endcode
 * Функция требует, чтобы тип данных поддерживал оператор operator==().
 * \see insert()
 */
/*!
 * \fn int VLinkedList::size() const
 * Возвращает количество элемнтов в списке.
 * \see isEmpty() и count()
 */
/*!
 * \fn bool VLinkedList::startsWith(const T &value) const
 * Возвращает \c true, если первый элемент списка равен \a value.
 * Иначе \c false.
 * \see isEmpty() и first()
 */
/*!
 * \fn T VLinkedList::takeFirst()
 * Удаляет первый элемент из списка и возвращает его.\n
 * Если вы не используете полученный элемент, removeFirst() -
 * более эффективная функция.
 * \see takeLast() и removeFirst() 
 */
/*!
 * \fn T VLinkedList::takeLast()
 * Удалает последний элемент из списка и возвращает его.\т
 * Если вы не используете полученный элемент, removeLast() -
 * более эффективная функция.
 * \see takeFirst() и removeLast()
 */
/*!
 * \fn bool VLinkedList::operator!=(const VLinkedList<T> &other) const
 * Возвращает \c true, если \a other не равен этому списку. Иначе \c false.\n
 * Два списка считаются равными если они содержат одинаковые элементы, в
 * том же порядке.\n
 * Функция требует, чтобы тип поддерживал оператор operator==().
 * \see operator==()
 */
/*!
 * \fn VLinkedList<T> VLinkedList::operator+(const VLinkedList<T> &other) const
 * Возвращает список, содержащий все элементы из этого списка и \a other.
 * \see operator+=()
 */
/*!
 * \fn VLinkedList<T> &VLinkedList::operator+=(const VLinkedList<T> &other)
 * Добавляет в конец все элементы списка \a other и возвращает ссылку на текущий
 * список.
 * \see operator+() и append()
 */
/*!
 * \fn VLinkedList<T> &VLinkedList::operator+=(const T &value)
 * \overload \n
 * Добавляет \a value в конец списка.
 */
/*!
 * \fn VLinkedList<T> &VLinkedList::operator<<(const VLinkedList<T> &other)
 * Добавляет все элементы \a other в конец этого списка и возвращает
 * ссылку на него.
 * \see operator+=() и append()
 */
/*!
 * \fn VLinkedList<T> &VLinkedList::operator<<(const T &value)
 * \overload \n
 * Добавляет \a value в конец списка.
 */
/*!
 * \fn VLinkedList<T> &VLinkedList::operator=(const VLinkedList<T> &other)
 * Назначает этому списку список \a other и возвращает ссылку.
 */
/*!
 * \fn bool VLinkedList::operator==(const VLinkedList<T> &other) const
 * Возвращает \c true, если этот список равен \a other. Иначе \c false.\n
 * Два списка считаются равными, если они содержат одинаковые элементы
 * и в таком же порядке.\n
 * Функция требует, чтобы тип поддерживал оператор operator==().
 * \see operator!=()
 */

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
 * * TODO:::TODO Дописать про функции-алгоритмы *
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

/*!
 * \class VLinkedList::iterator
 * \brief Реализует неконстантный STL итератор для VLinkedList
 *
 * VLinkedList в равной степени поддерживает STL и Java итераторы. STL итераторы
 * более низкоуровненвы, но более громоздки в использовании. С другой стороны,
 * они могут оказаться быстрее и более приемлемыми для разработчиков, знакомых
 * с STL.
 *
 * VLinkedList<T>::iterator позволяет вам перебрать VLinkedList<T> и изменять
 * список элементов. Если вы хотите только перебрать контейнер, используйте
 * VLinkedList::const_iterator. В общем случае, использование 
 * VLinkedList::const_iterator для неконстантного VLinkedList хорошая практика.
 * Константные итераторы быстрее и делаеют ваш код безопасней.
 *
 * По умолчанию VLinkedList::iterator создает неинициализированный итератор.
 * Вы должны назначить контейнер для этого итератора, используя
 * VLinkedList::begin(), VLinkedList::end() или VLinkedList::insert().
 * Дальше показан типичный цикл прохода всех элементов списка:
 * \code
 * VLinkedList<int> list;
 * list << 1 << 2 << 3 << 4 << 5;
 * ...
 *
 * VLinkedList<int>::iterator i;
 * for(i = list.begin(); i != list.end(); ++i)
 *     cout << *i << endl;
 * \endcode
 *
 * /* TODO:::TODO написать про алгоритмы
 *
 * Следующий пример можно реализовать только с помощью VLinkedList::iterator.
 * Здесь каждое значение увеличивается на 2:
 * \code
 * VLikedList<int>::iterator i;
 * for(i = list.begin(); i != list.end(); ++i)
 *     *i += 2;
 * \endcode
 * В следующем примере удаляются все четные числа:
 * \code
 * VLinkedList<int> list;
 * // заполняем контейнер случайными числами
 * ...
 * VLinkedList<int>::iterator i = list.begin();
 * while(i != list.end())
 * {
 *     if( !(*i % 2) )
 *         i = list.erase(i);
 *     else
 *         ++i;
 * }
 * \endcode
 * Вызов VLinkedList::erase() удаляет элемент, на который указывает итератор
 * и возвращает итератор на следущий элемент. Вот ещё один путь решения
 * этой же задачи:
 * \code
 * VLinkedList<int>::iterator i = list.begin();
 * while(i != list.end())
 * {
 *     VLinkedList<int>::iterator previous = i;
 *     ++i;
 *     if( !(*previous % 2) )
 *         list.erase(previous);
 * }
 * \endcode
 * Однако не пишите вот такой код:
 * \code
 * // WRONG
 * while(i != list.end())
 * {
 *     if( !(*i % 2) )
 *         list.erase(i);
 *     ++i;
 * }
 * \endcode
 * Это привидет к потери \c i после вызова erase() и, в дальнейшем, к ошибке.
 *
 * Несколько итераторов могут использоваться для одного и того же списка.
 * Если вы вставляете элементы, то существующие итераторы останутся
 * действительными. Если вы удаляете элементы, то итераторы, указывающие
 * на удаленные элементы, более не будут действительными.
 * \see VLinkedList::const_iterator и VMutableLinkedListIterator
 */

/*!
 * \fn VLinkedList::iterator::iterator()
 * Создает неинициализированный итератор.\n
 * Фукнции operator*() и operator++() не должны вызываться для неназначенного
 * итератора. Используйте operator=() что присвоить этому итератору контейнер.
 * \see VLinkedList::begin() и VLinkedList::end()
 */
/*!
 * \fn VLinkedList::iterator::iterator(const iterator &other)
 * Конструктор копий.
 */
/*!
 * \fn bool VLinkedList::iterator::operator!=(const iterator &other) const
 * Возвращает \c true если \a other и этот итератор указывают на 
 * разные элементы. Иначе \c false.
 * \see operator==()
 */
/*!
 * \fn bool VLinkedList::iterator::operator!=(const const_iterator &other) const
 * \overload
 */
/*!
 * \fn T &VLinkedList::iterator::operator*() const
 * Возвращает ссылку на текущий элемент.\n
 * Вы можете менять значение элемента, ставя итератор слева от равно:
 * \code
 * if( *it == 2 )
 *     *it = 4;
 * \endcode
 * \see operator->()
 */
/*!
 * \fn iterator VLinkedList::iterator::operator+(int j) const
 * Возвращает итератор на элемент через \a j позиций от текущего.
 * (если \a j отрицательна, то в обратном направлении.)
 * \see operator-()
 */
/*!
 * \fn iterator &VLinkedList::iterator::operator++()
 * Префиксная форма инкремента (++it). Сначала перемещает итератор на
 * следующий элемент, а потом возвращает его.\n
 * Для VLinkedList::end() результат не определен.
 * \see operator--()
 */
/*!
 * \fn iterator VLinkedList::iterator::operator++(int)
 * \overload \n
 * Постфиксная форма инкремента (it++). Возвращает текущий итератор,
 * а потом увеличивает его. 
 */
/*!
 * \fn iterator &VLinkedList::iterator::operator+=(int j)
 * Смещает итератор на \a j позиций (если \a j отрицательна, то
 * в обратную сторону)
 * \see operator-=() и operator+()
 */
/*!
 * \fn iterator VLinkedList::iterator::operator-(int j) const
 * Возвращает итератор на \a j позиций до текущего элемента
 * (или после, если \a j отрицательна).
 * \see operator+()
 */
/*!
 * \fn iterator &VLinkedList::iterator::operator--()
 * Префиксная форма декремента (--it). Уменьшает итератор, а потом
 * возвращает результат.
 * \n Для VLinkedList::begin() результат не определен.
 * \see operator++()
 */
/*!
 * \fn iterator VLinkedList::iterator::operator--(int)
 * \overload \n
 * Постфиксная форма декремента (it--). Возвращает текущий итератор,
 * а потом уменьшает его.
 */
/*!
 * \fn iterator &VLinkedList::iterator::operator-=(int j)
 * Смещает итератор на \a j позиций назад (или вперед, если
 * \a j отрицательна)
 * \see operator+=() и operator-()
 */
/*!
 * \fn T *VLinkedList::iterator::operator->() const
 * Возвращает указатель на текущий элемент.
 * \see operator*()
 */
/*!
 * \fn iterator &VLinkedList::iterator::operator=(const iterator &other)
 * Назначает этому итератору \a other
 */
/*!
 * \fn bool VLinkedList::iterator::operator==(const iterator &other) const
 * Возвращает \c true, если \a other и этот итератор указывают
 * на один и тот же элемент.
 * \see operator!=()
 */
/*!
 * \fn bool VLinkedList::iterator::operator==(const const_iterator &other) const
 * \overload
 * \see operator!=()
 */
