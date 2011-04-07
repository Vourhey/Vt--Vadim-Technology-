#include "vlist.h"
#include "vqueue.h"

/*!
 * \class VQueue
 * \brief Контейнер, реализующий очередь.
 *
 * VQueue<T> один из классов-контейнеров библиотеки Vt. Он позволяет
 * хранить данные любого типа.
 *
 * Очередь работает по принципу первый вошел, первый вышел (FIFO).
 * Элементы добавляются в конец очереди, использую enqueue(),
 * и удаляются с головы, используя dequeue(). Функция head()
 * возвращает головной элемент без удаления.
 *
 * Пример:
 * \code
 * VQueue<int> queue;
 * queue.enqueue(1);
 * queue.enqueue(2);
 * queue.enqueue(3);
 * while(!queue.isEmpty())
 *     cout << queue.dequeue() << endl;
 * \endcode
 * На экране появятся 1, 2, 3 в этом же порядке.
 *
 * VQueue наследуется от VList. Поэтому все открытые члены VList
 * так же доступны и в VQueue. Например, вы можете использовать isEmpty()
 * и использовать итераторы (VListIterator, VMutableListIterator). Но
 * для управления очередью лучше использовать заявленные функции, так
 * как в ином случае смысл класса теряется.
 *
 * Требования к типу данных такие же как и в VList.
 * \see VList и VStack
 */

/*!
 * \fn VQueue::VQueue()
 * Создает пустую очередь
 */
/*!
 * \fn VQueue::~VQueue()
 * Удаляет очередь. Все итераторы становятся недействительными.
 */
/*!
 * \fn T VQueue::dequeue()
 * Удаляет элемент с головы очереди и возвращает его.
 * Предполагается, что очередь не пустая.\n
 * Равносильно VList::takeFirst().
 * \see head(), enqueue() и isEmpty()
 */
/*!
 * \fn void VQueue::enqueue(const T &t)
 * Добавляет \a t в конец очереди.\n
 * Равносильно VList::append().
 * \see dequeue() и head()
 */
/*!
 * \fn T &VQueue::head()
 * Возвращает ссылку на первый элемент, но не удаляет его.
 * Предполагается, что очередь не пуста.\n
 * Равносильно VList::first().
 * \see dequeue(), enqueue() и isEmpty()
 */
/*!
 * \fn const T &VQueue::head() const
 * \overload
 */

/*!
 * \class VList
 * \brief Шаблонный класс, реализующий список.
 * \see VListIterator, VMutableListIterator, VLinkedList, VVector
 */

/*!
 * \typedef VList::ConstIterator
 * Синоним для VList::const_iterator в стиле Vt.
 */
/*!
 * \typedef VList::Iterator
 * Синоним для VList::iterator в стиле Vt.
 */
/*!
 * \typedef VList::const_pointer
 * Синоним для cosnt T *. \stl
 */
/*!
 * \typedef VList::const_reference
 * Синоним для const T &. \stl
 */
/*!
 * \typedef VList::difference_type
 * Синоним для vptrdiff. \stl
 */
/*!
 * \typedef VList::pointer
 * Синоним для T *. \stl
 */
/*!
 * \typedef VList::reference
 * Синоним для T &. \stl
 */
/*!
 * \typedef VList::size_type
 * Синоним для int. \stl
 */
/*!
 * \typedef VList::value_type
 * Синоним для T. \stl
 */
/*!
 * \fn VList::VList()
 * Создает пустой список.
 */
/*!
 * \fn VList::VList(const VList<T> &other)
 * Конструктор копий для \a other.
 * \see operator=()
 */
/*!
 * \fn VList::~VList()
 * Деструктор. Все итераторы становятся недействительными.
 */
/*!
 * \fn void VList::append(const T &value)
 * Вставляет \a value в конец списка.\n
 * Пример:
 * \code
 * VList<int> list;
 * list.append(1);
 * list.append(2);
 * list.append(3);
 * // list: [1, 2, 3]
 * \endcode
 * \see operator<<(), prepend() и insert()
 */
/*!
 * \fn void VList::append(const VList<T> &value)
 * \overload \n
 * Добавляет все элементы \a value в конец этого списка.
 * \see operator<<() и operator+=()
 */
/*!
 * \fn const T &VList::at(int i) const
 * Возвращает элемент с позиции \a i. \a i должна быть в пределах списка
 * (т.е. 0 <= \a i < size()).
 * \see value() и operator[]().
 */
/*!
 * \fn T &VList::back()
 * \stl Равносильно last(). Список не должен быть пустым.
 * \see isEmpty()
 */
/*!
 * \fn const T &VList::back() const
 * \overload
 */
/*!
 * \fn iterator VList::begin()
 * Возвращает STL итератор, указывающий на первый элемент списка.
 * \see constBegin() и end()
 */
/*!
 * \fn const_iterator VList::begin() const
 * \overload
 */
/*!
 * \fn void VList::clear()
 * Удаляет все элементы в списке.
 * \see removeAll().
 */
/*!
 * \fn const_iterator VList::constBegin() const
 * Возвращает STL итератор, указывающий на первый элемент в списке.
 * \see begin() и constEnd()
 */
/*!
 * \fn const_iterator VList::constEnd() const
 * Возвращает STL итератор, указывающий на последний элемент в списке.
 * \see constBegin() и end()
 */
/*!
 * \fn bool VList::contains(const T &value) const
 * Возвращает \c true, если список содержит \a value. Иначе \c false.
 * Функция требует, чтобы тип данных поддерживал операцию operator==().
 * \see indexOf() и count() 
 */
/*!
 * \fn int VList::count(const T &value) const
 * Возвращает число вхождений \a value в список.
 * Функция требует, чтобы тип данных поддерживал оператор operator==().
 * \see contains() и indexOf()
 */
/*!
 * \fn int VList::count() const
 * Возвращает число элементов в списке. Равносильно size().
 */
/*!
 * \fn bool VList::empty() const
 * \stl Равносильно isEmpty().
 */
/*!
 * \fn iterator VList::end()
 * Возвращает STL итератор, указывающий на последний элемент в списке.
 * \see begin() и constEnd()
 */
/*!
 * \fn const_iterator VList::end() const
 * \overload
 */
/*!
 * \fn bool VList::endsWith(const T &value) const
 * Возвращает \c true, если список не пустой и заканчивается на \a value.
 * Иначе \c false.
 * \see isEmpty() и contains()
 */
/*!
 * \fn iterator VList::erase(iterator pos)
 * Удаляет элемент, на который указывает \a pos и возвращает 
 * итератор на следующий элемент (который может быть end()).
 * \see insert() и removeAt()
 */
/*!
 * \fn iterator VList::erase(iterator begin, iterator end)
 * \overload \n
 * Удаляет все элемент начиная с \a begin и до \a end (но не включая его).
 * Возвращает итератор на элемент после последнего удаленного.
 */
/*!
 * \fn T &VList::first()
 * Возвращает ссылку на первый элемент в списке. Список не должен быть пустым.
 * \see last() и isEmpty()
 */
/*!
 * \fn const T &VList::first() const
 * \overload
 */
/*!
 * \fn T &VList::front()
 * \stl Равносильно first().
 */
/*!
 * \fn const T &VList::front() const
 * \overload
 */
/*!
 * \fn int VList::indexOf(const T &value, int from = 0) const
 * Возвращает позицию первого вхождения \a value в список.
 * Поиск производится начиная с \a from. Возвращает -1 если
 * элемент не найден.\n
 * Пример:
 * \code
 * VList<char> list;
 * list << 'a' << 'b' << 'c' << 'b' << 'a';
 * list.indexOf('b');    // return 1
 * list.indexOf('b', 1); // return 1
 * list.indexOf('b', 2); // return 3
 * list.indexOf('x');    // return -1
 * \endcode
 * Тип данных должен поддерживать оператор operator==().
 * \see lastIndexOf() и contains()
 */
/*!
 * \fn void VList::insert(int i, const T &value)
 * Вставляет \a value в позицию \a i. \n Пример:
 * \code
 * VList<VByteArray> list;
 * list << "alpha" << "beta" << "delta";
 * list.insert(2, "gamma");
 * // list: ["alpha", "beta", "gamma", "delta"]
 * \endcode
 * \see append(), prepend(), replace() и removeAt()
 */
/*!
 * \fn iterator VList::insert(iterator before, const T &value)
 * \overload \n
 * Вставляет \a value до элемента на который указывает \a before.
 * Возвращает итератор на вставленный элемент.
 */
/*!
 * \fn bool VList::isEmpty() const
 * Возвращает \c true, если список пуст. Иначе \c false.
 * \see size()
 */
/*!
 * \fn T &VList::last()
 * Возвращает ссылку на последний элемент. Список не должен быть пустым.
 * \see first() и isEmpty()
 */
/*!
 * \fn const T &VList::last() const
 * \overload
 */
/*!
 * \fn int VList::lastIndexOf(const T &value, int from = -1) const
 * Возвращает позицию последнего вхождения \a value в список.
 * Поиск производится в обратном порядке начиная с \a from. Если
 * \a from равна -1 (по умолчанию), то поиск производится с конца.\n
 * Пример:
 * \code
 * VList<char> list;
 * list << 'a' << 'b' << 'c' << 'b' << 'a';
 * list.lastIndexOf('b');      // returns 3
 * list.lastIndexOf('b', 3);   // returns 3
 * list.lastIndexOf('b', 2);   // returns 1
 * list.lastIndexOf('x');      // returns -1
 * \endcode
 * Функция требует, чтобы тип данных поддерживал operator==().
 * \see indexOf()
 */
/*!
 * \fn int VList::length() const
 * Равносильно count() и size().
 * \see count().
 */
/*!
 * \fn VList<T> VList::mid(int pos, int length = -1) const
 * Возвращает список, который содержит элементы из этого списка
 * начиная с \a pos. Если \a length равна -1 (по умолчанию), то
 * все элементы после \a pos копируются в новый список.
 * Иначе только \a length элементов будут добавлены в конечный список.
 */
/*!
 * \fn void VList::pop_back()
 * \stl Равносильно removeLast().
 */
/*!
 * \fn void VList::pop_front()
 * \stl Равносильно removeFirst().
 */
/*!
 * \fn void VList::prepend(const T &value)
 * Вставляет \a value в начало списка.\n Пример:
 * \code
 * VList<VByteArray> list;
 * list.prepend("one");
 * list.prepend("two");
 * list.prepend("three");
 * // list: ["three", "two", "one"]
 * \endcode
 * Того же эфекта можно добиться через list.insert(0, \a value).
 * \see append() и insert().
 */
/*!
 * \fn void VList::push_back(const T &value)
 * \stl Равносильно append(\a value).
 */
/*!
 * \fn void VList::push_front(const T &value)
 * \stl Равносильно prepend(\a value).
 */
/*!
 * \fn int VList::removeAll(const T &value)
 * Удаляет все вхождения \a value в список и возвращает 
 * число удаленных.\n Пример:
 * \code
 * VList<VByteArray> list;
 * list << "sun" << "cloud" << "sun" << "rain";
 * list.removeAll("sun");   // return 2
 * // list: ["cloud", "rain"]
 * \endcode
 * Функция требует, чтобы тип данных поддерживал operator==().
 * \see removeOne(), removeAt(), takeAt()
 */
/*!
 * \fn void VList::removeAt(int i)
 * Удаляет элемент с позиции \a i. \a i должна быть в пределах списка
 * (т.е. 0 <= \a i < size()).
 * \see takeAt(), removeFirst(), removeLast() и removeOne().
 */
/*!
 * \fn void VList::removeFirst()
 * Удаляет первый элемент из списка. Это равносильно вызову removeAt(0).
 * \see removeAt() и takeFirst()
 */
/*!
 * \fn void VList::removeLast()
 * Удаляет последний элемент из списка. Равносильно вызову removeAt(size()-1).
 * \see removeAt() и takeLast().
 */
/*!
 * \fn bool VList::removeOne(const T &value)
 * Удаляет первое вхождение \a value и возвращает \c true в случае успеха.
 * Иначе \c false. \n Пример:
 * \code
 * VList<VByteArray> list;
 * list << "sun" << "cloud" << "sun" << "rain";
 * list.removeOne("sun");
 * // list: ["cloud", "sun", "rain"]
 * \endcode
 * Функция требует, чтобы тип данных поддерживал operator==().
 * \see removeAll(), removeAt() и takeAt().
 */
/*!
 * \fn void VList::reserve(int alloc)
 * Резервирует память под \a alloc элементов.\n
 * Функция нужна для точного контроля над памятью. Так же это может
 * быть полезно, если вы заранее знаете сколько элементов будет в списке.
 */
/*!
 * \fn int VList::size() const
 * Возвращает число элементов в списке.
 * \see isEmpty() и count()
 */
/*!
 * \fn bool VList::startsWith(const T &value) const
 * Возвращает \c true, если список начинается на \a value.
 * Иначе \c false.
 * \see isEmpty() и contains().
 */
/*!
 * \fn T VList::takeAt(int i)
 * Удаляет элемент с позиции \a i и возвращает его.
 * Если вам дальше не понадобится этот элемент, removeAt()
 * будет более эффективна.
 * \see removeAt(), takeFirst() и takeLast()
 */
/*!
 * \fn T VList::takeFirst()
 * Удаляет первый элемент и возвращает его. Равносильно takeAt(0).
 * Если вы не используете полученный элемент, removeFirst() более
 * эффективная функция.
 * \see takeLast(), takeAt() и removeFirst()
 */
/*!
 * \fn T VList::takeLast()
 * Удаляет последний элемент и возвращает его. Равносильно takeAt(size()-1).
 * Если вы не используете полученный элемент, removeLast() более
 * эффективная функция.
 * \see takeFirst(), takeAt() и removeLast()
 */
/*!
 * \fn T VList::value(int i) const
 * Возвращает элемент с позиции \a i.
 * Если \a i находится вне списка, то возвращает значение по умолчанию.
 * \see at() и operator[]()
 */
/*!
 * \fn T VList::value(int i, const T &defaultValue) const
 * \overload \n
 * Если \a i вне списка, возвращается \a defaultValue.
 */
/*!
 * \fn bool VList::operator!=(const VList<T> &other) const
 * Возвращает \c true, если этот список не равен \a other.
 * Иначе \c false. Два списка считаются не равными, если
 * имеют разные элементы или в другом порядке.
 * \see operator==()
 */
/*!
 * \fn VList<T> VList::operator+(const VList<T> &other) const 
 * Возвращает список содержащий все элементы из этого списка и из \c other.
 * \see operator+=()
 */
/*!
 * \fn VList<T> &VList::operator+=(const VList<T> &other)
 * Добавляет в конец этого списка все элементы из \a other.
 * \see operator+() и append()
 */
/*!
 * \fn VList<T> &VList::operator+=(const T &value)
 * \overload \n
 * Добавляет в конец списка \a value.
 * \see append() и operator<<()
 */
/*!
 * \fn VList<T> &VList::operator<<(const VList<T> &other)
 * Добавляет в конец этого списка все элементы из \a other.
 * \see operator+=() и append()
 */
/*!
 * \fn VList<T> &VList::operator<<(const T &value)
 * \overload \n
 * Добавляет в конец списка \a value.
 */
/*!
 * \fn bool VList::operator==(const VList<T> &other) const
 * Возвращает \c true, если этот список равен \a other.
 * Иначе \c false. Два списка считаются равными, если имеют
 * одинаковые элементы и в таком же порядке.
 * \see operator!=()
 */
/*!
 * \fn T &VList::operator[](int i)
 * Возвращает элемент с позиции \a i, доступный для изменений.
 * \a i должна быть в пределах списка (т.е. 0 <= \a i < size()).
 * \see at() и value()
 */
/*!
 * \fn const T &VList::operator[](int i) const
 * \overload \n Равносильно at().
 */

/*!
 * \class VList::const_iterator
 * \brief Реализует константный STL итератор для VList и VQueue
 *
 * VList в равной степени поддерживает STL и Java итераторы. STL итераторы
 * более низкоуровневые и менее интуитивны в использовании. С другой
 * стороны они могут оказаться быстрее и более подходящими для
 * разработчиков, знакомых с STL.
 *
 * VList<T>::const_iterator позволяет вам перебрать VList<T> (или VQueue<T>).
 * Если вам нужно изменить список, то используйте VList::iterator. В общем,
 * хорошая практика использовать VList::const_iterator для не константного
 * VList, если вы собираетесь только получить значения элементов.
 * Константный итератор так же делает ваш код более безопасным.
 *
 * По умолчанию конструктор VList::const_iterator создает не инициализированный
 * итератор. Вы должны назначить контейнер этому итератор, используя
 * VList::constBegin(), VList::constEnd() или VList::insert() до того, как
 * начнете перебирать элементы. Дальше показан обычный проход всего контейнера:
 * \code
 * VList<int> list;
 * list.append(1);
 * list.append(3);
 * list.append(5);
 * ...
 * list.append(19);
 *
 * VList<int>::const_iterator i;
 * for(i = list.constBegin(); i != list.constEnd(); ++i)
 *     cout << *i << ' ';
 * \endcode
 *
 * Большинство функций VList позволяют использовать индексы вместо итераторов.
 * Одно место, где STL итераторы незаменимы - это общие алгоритмы (добавить ссылку).
 * \code
 * VList<char *> list;
 * ...
 * vDeleteAll(list.constBegin(), list.constEnd());
 * \endcode
 * Сразу несколько константных итераторов могут указывать на один и тот же контейнер.
 * Однако, только один изменяемый итератор можно использовать в одно время.
 * Если вам нужно перебирать элементы долгий период времени, рекомендуем
 * воспользоваться VLinkedList.
 * \see VList::iterator и VListIterator
 */

/*!
 * \typedef VList::const_iterator::iterator_category
 * Синоним для \c std::random_access_iterator_tag.
 * Это говорит о том, что итератор является итератором случайного доступа.
 */
/*!
 * \fn VList::const_iterator::const_iterator()
 * Создает не инициализированный итератор.\n
 * Функции operator*() и operator++() нельзя вызывать для такого итератора.
 * Используйте \c operator=() чтобы назначить контейнер.
 * \see VList::constBegin() и VList::constEnd()
 */
/*!
 * \fn VList::const_iterator::const_iterator(const const_iterator &other)
 * Конструктор копий для \a other.
 */
/*!
 * \fn VList::const_iterator::const_iterator(const iterator &other)
 * Конструктор копий для \a other.
 */
/*!
 * \fn bool VList::const_iterator::operator!=(const const_iterator &other) const
 * Возвращает \c true, если \a other не указывает на тот же элемент, что и этот
 * итератор. Иначе \c false.
 * \see operator==()
 */
/*!
 * \fn const T &VList::const_iterator::operator*() const
 * Возвращает текущий элемент.
 * \see operator->()
 */
/*!
 * \fn const_iterator VList::const_iterator::operator+(int j) const
 * Возвращает итератор, указывающий на элемент через \a j позиций от текущего.
 * \see operator-() и operator+=()
 */
/*!
 * \fn const_iterator &VList::const_iterator::operator++()
 * Префиксная форма инкремента (++it). Передвигает итератор на следующий
 * элемент и возвращает итератор на новый элемент.\n
 * Для VList::end() результат не определен.
 * \see operator--()
 */
/*!
 * \fn const_iterator VList::const_iterator::operator++(int)
 * \overload \n
 * Постфиксная форма инкремента (it++). Возвращает текущий итератор и 
 * передвигает на следующий элемент.
 */
/*!
 * \fn const_iterator &VList::const_iterator::operator+=(int j)
 * Смещает итератор на \a j позиций вперед (или назад, если \a j отрицательна)
 * \see operator-=() и operator+()
 */
/*!
 * \fn const_iterator VList::const_iterator::operator-(int j) const
 * Возвращает итератор, указывающий на элемент, находящийся на \a j позиций
 * до текущего (или впереди, если \a j отрицательна)
 * \see operator+() и operator-=()
 */
/*!
 * \fn int VList::const_iterator::operator-(const_iterator other) const
 * Возвращает число элементов между текущим и \a other.
 */
/*!
 * \fn const_iterator &VList::const_iterator::operator--()
 * Префиксная форма декремента (--it). Смещает итератор на одну позицию
 * назад и возвращает его.\n
 * Для VList::begin() результат не определен.
 * \see operator++()
 */
/*!
 * \fn const_iterator VList::const_iterator::operator--(int)
 * \overload \n
 * Постфиксная форма декремента (it--). Возвращает текущий итератор
 * и смещает его на одну позицию назад.
 */
/*!
 * \fn const_iterator &VList::const_iterator::operator-=(int j)
 * Смещает итератор на \a j позиций назад (или вперед, если \a j отрицательна).
 * \see operator+=() и operator-()
 */
/*!
 * \fn const T *VList::const_iterator::operator->() const
 * Возвращает указатель на текущий элемент.
 * \see operator*()
 */
/*!
 * \fn bool VList::const_iterator::operator<(const const_iterator &other) const
 * Возвращает \c true, если текущий элемент находится до \a other.
 */
/*!
 * \fn bool VList::const_iterator::operator<=(const const_iterator &other) const
 * Возвращает \c true, если текущий элемент находится до или является \a other.
 */
/*!
 * \fn bool VList::const_iterator::operator==(const const_iterator &other) const
 * Возвращает \c true, если этот итератор и \a other указывают на один и тот же элемент.
 * Иначе \c false.
 * \see operator!=()
 */
/*!
 * \fn bool VList::const_iterator::operator>(const const_iterator &other) const
 * Возвращает \c true, если текущий элемент находится после \a other.
 */
/*!
 * \fn bool VList::const_iterator::operator>=(const const_iterator &other) const
 * Возвращает \c true, если текущий элемент находится после или равен \a other.
 */
/*!
 * \fn const T &VList::const_iterator::operator[](int j) const
 * Возвращает элемент с позиции *this + \a j.
 * \see operator+()
 */

/*!
 * \class VList::iterator
 * \brief STL итератор для VList и VQueue.
 *
 * VList в равной степени поддерживает STL и Java итераторы. 
 * Итераторы STL более низкого уровня и более громоздки в использовании.
 * С другой стороны, они могут быть быстрее и более удобными для
 * разработчиков, знакомых с STL.
 *
 * VList<T>::iterator позволяет вам перебрать VList<T> (или VQueue<T>) 
 * и изменить содержимое списка. Если вам нужно только получить элементы
 * или у вас имеется константный список, то лучше использовать
 * VList::const_iterator. В общем случае, хорошая практика использовать
 * VList::const_iterator и для не константного списка. Это сделает ваш
 * код безопаснее.
 *
 * По умолчанию VList::iterator создает не инициализированный итератор.
 * Вы должны назначить контейнер ему, используя VList::begin(),
 * VList::end() или VList::insert() до того, как начнете перебирать.
 * Дальше показан типичный цикл перебора всех элементов:
 * \code
 * VList<VByteArray> list;
 * list.append("Январь");
 * list.append("Февраль");
 * ...
 * list.append("Декабрь");
 *
 * VList<VByteArray>::iterator i;
 * for(i = list.begin(); i != list.end(); ++i)
 *     cout << *i << endl;
 * \endcode
 * Это можно сделать и с VList::const_iterator. Дальше показан пример,
 * который можно сделать только с VList::iterator:
 * \code
 * VList<int>::iterator i;
 * for(i=list.begin(); i!=list.end(); ++i)
 *     *i += 2;
 * \endcode
 * Здесь каждый элемент увеличивается на 2. 
 *
 * Большинство функций VList требуют целое число в качестве индекса.
 * Поэтому зачастую можно обойтись и обычным циклом (без итератора).
 * Однако итераторы нужны для всех общих алгоритмов (дописать ссылку).
 * \code
 * VList<char *> list;
 * ...
 * vDeleteAll(list.begin(), list.end());
 * \endcode
 * \see VList::const_iterator и VMutableListIterator
 */

/*!
 * \typedef VList::iterator::iterator_category
 * Синоним для \c std::random_access_iterator_tag, показывающий, что
 * итератор является итератором случайного доступа.
 */
/*!
 * \fn VList::iterator::iterator()
 * Создает не инициализированный итератор.\n
 * Итератору нужно назначить контейнер до вызова таких функций, как
 * operator*() или operator++().
 * \see VList::begin() и VList::end()
 */
/*!
 * \fn VList::iterator::iterator(const iterator &other)
 * Конструктор копий для \a other.
 */
/*!
 * \fn bool VList::iterator::operator!=(const iterator &other) const
 * Возвращает \c true, если этот итератор указывает не на тот же
 * элемент, что и \a other. Иначе \c false.
 * \see operator==()
 */
/*!
 * \fn bool VList::iterator::operator!=(const const_iterator &other) const
 * \overload
 */
/*!
 * \fn T &VList::iterator::operator*() const
 * Возвращает ссылку на текущий элемент.\n
 * Вы можете менять полученный элемент, например:
 * \code
 * if( *it == "Hello" )
 *     *it = "Bonjour";
 * \endcode
 * \see operator->()
 */
/*!
 * \fn iterator VList::iterator::operator+(int j) const
 * Возвращает итератор, указывающий на элемент через \a j позиций.
 * \see operator-() и operator+=()
 */
/*!
 * \fn iterator &VList::iterator::operator++()
 * Префиксная форма инкремента (++it). Увеличивает итератор и возвращает
 * его.\n Для VList::end() результат не определен.
 * \see operator--()
 */
/*!
 * \fn iterator VList::iterator::operator++(int)
 * \overload \n
 * Постфиксная форма инкремента (it++).
 */
/*!
 * \fn iterator &VList::iterator::operator+=(int j)
 * Перемещает итератор на \a j позиций вперед (или назад, если \a j отрицательна).
 * \see operator-=() и operator+()
 */
/*!
 * \fn iterator VList::iterator::operator-(int j) const
 * Возвращает итератор на элемент через \a j позиций назад
 * (или вперед, если \a j отрицательна).
 * \see operator+() и operator-=()
 */
/*!
 * \fn int VList::iterator::operator-(iterator other) const
 * Возвращает число элементов между этим итератором и \a other.
 */
/*!
 * \fn iterator &VList::iterator::operator--()
 * Префиксная форма декремента (--it). Уменьшает итератор и возвращает его.\n
 * Для VList::begin() результат не определен.
 * \see operator++()
 */
/*!
 * \fn iterator VList::iterator::operator--(int)
 * \overload \n
 * Постфиксная форма декремента (it--). Возвращает текущий итератор и уменьшает его.
 */
/*!
 * \fn iterator &VList::iterator::operator-=(int j)
 * Смещает итератор на \a j позиций назад (или вперед, если \a j отрицательна).
 * \see operator+=() и operator-()
 */
/*!
 * \fn T *VList::iterator::operator->() const
 * Возвращает указатель на текущий элемент.
 * \see operator*()
 */
/*!
 * \fn bool VList::iterator::operator<(const iterator &other) const
 * Возвращает \c true, если текущий элемент находится до \a other.
 */
/*!
 * \fn bool VList::iterator::operator<(const const_iterator &other) const
 * \copydoc VList::iterator::operator<()
 */
/*!
 * \fn bool VList::iterator::operator<=(const iterator &other) const
 * Возвращает \c true, если текущий элемент находится до или равен \a other.
 */
/*!
 * \fn bool VList::iterator::operator<=(const const_iterator &other) const
 * \copydoc VList::iterator::operator<=()
 */
/*!
 * \fn bool VList::iterator::operator==(const iterator &other) const
 * Возвращает \c true, если текущий элемент равен \a other. Иначе \c false.
 * \see operator!=()
 */
/*!
 * \fn bool VList::iterator::operator==(const const_iterator &other) const
 * \copydoc VList::iterator::operator==()
 */
/*!
 * \fn bool VList::iterator::operator>(const iterator &other) const
 * Возвращает \c true, если текущий элемент находится после \a other.
 */
/*!
 * \fn bool VList::iterator::operator>(const const_iterator &other) const
 * \copydoc VList::iterator::operator>()
 */
/*!
 * \fn bool VList::iterator::operator>=(const iterator &other) const
 * Возвращает \c true, если текущий элемент находится после или равен \a other.
 */
/*!
 * \fn bool VList::iterator::operator>=(const const_iterator &other) const
 * \copydoc VList::iterator::operator>=()
 */
/*!
 * \fn T &VList::iterator::operator[](int j) const
 * Возвращает ссылку на элемент с позиции *this + \a j.
 * Элемент можно изменять.
 * \see operator+()
 */
