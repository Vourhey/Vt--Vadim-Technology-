#include "vstack.h"

/*!
 * \class VStack
 * \brief Класс реализует структуру данных стек
 *
 * VStack<T> один из классов-контейнеров библиотеки Vt. 
 * Он реализует структуру данных стек для определенного типа.
 *
 * Стек - это стуктура данных, работающая по принципу последний
 * вошел, первый вышел (LIFO). Элементы добавляются на вершину 
 * стека, используя push(), и извлекаются с помощью pop().
 * Функция top() возвращает вершину стека, не удаляя элемент.
 *
 * Пример:
 * \code
 * VStack<int> stack;
 * stack.push(1);
 * stack.push(2);
 * stack.push(3);
 * while(!stack.isEmpty())
 *     cout << stack.pop() << endl;
 * \endcode
 * На экран будет выведено 3, 2, 1.
 *
 * Так как VStack наследуется от VVector, то весь функционал
 * этого класса также доступен в VStack. Например, вы можете
 * использовать isEmpty(), чтобы проверить пуст ли стек.
 * Ещё вы можете исползовать итератор VVectorIterator, но
 * тогда теряется смысл структуры стек (первый вошел, последний
 * вышел). Лучше использовать push(), pop() и top().
 *
 * Тип данных для VStack должен быть назначаемым. Это большинство
 * стандартных типов данных, в том числе и указатели.
 * \see VVector и VQueue
 */

/*!
 * \fn VStack::VStack()
 * Создает пустой стек
 */

/*!
 * \fn VStack::~VStack()
 * Деструктор
 */

/*!
 * \fn T VStack::pop()
 * Удаляет элемент из вершины стека и возвращает его.
 * Предполагается, что стек не пустой
 * \see top(), push() и isEmpty()
 */

/*!
 * \fn void VStack::push(const T &t)
 * Добавляет элемент \a t на вершину стека.
 * Это равносильно VVector::append()
 * \see pop() и top()
 */

/*!
 * \fn T &VStack::top()
 * Возвращает ссылку на вершину стека.
 * Предполагается, что стек не пустой.
 * Это равносильно VVector::last()
 * \see pop(), push() и isEmpty()
 */

/*!
 * \fn const T &VStack::top() const
 * \overload
 */

/*!
 * \class VVector
 * \brief Шаблонный класс, реализующий динамический массив
 *
 * VVector<T> один из классов-контейнеров библиотека Vt. Он хранит
 * элементы в соседних элементах памяти и обеспечивает быстрый доступ
 * с помощью индексов.
 * 
 * TODO
 * TODO
 * TODO
 */

/*!
 * \typedef VVector::ConstIterator
 * Синоним для VVector::const_iterator в стиле Vt
 */
/*!
 * \typedef VVector::Iterator
 * Синоним для VVector::iterator в стиле Vt
 */
/*!
 * \typedef VVector::const_iterator
 * Синоним в стиле STL для константного итератора для VVecotr и VStakc.
 * VVector в равной степени поддерживает STL интераторы и Java 
 * итераторы. В случае STL итераторов константный итератор всего лишь
 * синоним для "const T *"
 * \see VVector::constBegin(), VVector::constEnd() и VVector::iterator
 */
/*!
 * \typedef VVecotr::const_pointer
 * Синоним для const T *. Нужно для совместимости с STL
 */
/*!
 * \typedef VVector::const_reference
 * Синоним для T &. Нужно для совместимости с STL
 */
/*!
 * \typedef VVector::iterator
 * Синоним для не константного STL итератора.
 * В общем смысле это синоним для "T *"
 * \see VVecotr::begin(), VVector::end(), VVecotr::const_iterator
 */
/*!
 * \typedef VVector::pointer
 * Синоним для T *
 */
/*!
 * \typedef VVector::reference
 * Синоним для T &
 */
/*!
 * \typedef VVector::size_type
 * Синоним для int. Нужен для совместимости с STL
 */
/*!
 * \typedef VVector::value_type
 * Синоним для T. Нужен для совместимости с STL
 */

/*!
 * \fn VVector::VVector()
 * Создает пустой динамический массив
 * \see resize()
 */
/*!
 * \fn VVector::VVector(int size)
 * Создает вектор размером \a size.
 * Все элементы инициализируются значениями по умолчанию.
 * \see resize()
 */
/*!
 * \fn VVector::VVector(int size, const T &value)
 * Создает вектор размером \a size. Каждый элемент инициализируется
 * значением \a value.
 * \see resize(), fill()
 */
/*!
 * \fn VVector::VVector(const VVector<T> &other)
 * Конструктор копий
 */
/*!
 * \fn VVector::~VVector()
 * Деструктор
 */

/*!
 * \fn void VVector::append(const T &value)
 * Вставляет \a value в конец вектора.
 * 
 * Пример:
 * \code
 * VVector<double> vector(0);
 * vector.append(1.0);
 * vector.append(2.0);
 * vector.append(3.0);
 * // vector: [1.0, 2.0, 3.0]
 * \endcode 
 * Каждый вызов append() увеличивает размер на 1 и вставляет
 * новый элемент в последнюю позицию
 * \see operator<<(), prepend() и insert()
 */

/*!
 * \fn const T &VVector::at(int i) const
 * Возвращает элемент с позиции \a i в векторе.
 * \a i должнен быть в пределах вектора (т.е. 0 <= \a i < size())
 * \see value() и operator[]()
 */

/*!
 * \fn reference VVector::back()
 * Эта функция нужна для STL совместимости. Равносильно last()
 */
/*!
 * \fn const_reference VVector::back() const
 * \overload
 */
/*!
 * \fn iterator VVector::begin()
 * Возвращает STL итератор, указывающий на начало вектора
 * \see constBegin() и end()
 */
/*!
 * \fn const_iterator VVector::begin() const
 * \overload
 */

/*!
 * \fn int VVector::capacity() const 
 * Возвращает максимальное количество элементов, которые могут
 * быть сохранены в векторе без перевыделения памяти.
 * В общем, вам редко придется использовать эту функцию. Разве что 
 * вы захотите очень точно управлять памятью.
 * \see reserve()
 */

/*!
 * \fn void VVector::clear()
 * Удаляет все элементы из вектора и очищает память
 */

/*!
 * \fn const_iterator VVector::constBegin() const
 * Возвращает константный STL итератор, указывающий на первый элемент
 * вектора.
 * \see begin() и constEnd()
 */

/*!
 * \fn const T *VVector::constData() const
 * Возвращает константный указатель на исходный массив.
 * Посредством указателя можно получить доступ ко всем элементам
 * массива. Указатель действителен, пока существует вектор
 * \see data() и operator[]()
 */

/*!
 * \fn const_iterator VVector::constEnd() const
 * Возвращает константный STL итератор, указывающий на последний
 * элемент вектора.
 * \see constBegin() и end()
 */

/*!
 * \fn bool VVector::contains(const T &value) const
 * Возвращает \c true, если вектор содержит элемент \a value.
 * Иначе \c false. Функция требует, чтобы тип данных поддерживал
 * функцию operator==()
 * \see indexOf() и count() 
 */

/*!
 * \fn int VVector::count(const T &value) const
 * Возвращает число вхождений элемента \a value в вектор.
 * Функция требует, чтобы тип данных поддерживал оператор operator==()
 * \see contains() и indexOf()
 */

/*!
 * \fn int VVector::count() const
 * \overload\n Равносильно size().
 */
/*!
 * \fn T *VVector::data()
 * Возвращает указатель на данные, хранящиеся в векторе.
 * Посредством указателя можно получать доступ к данным и изменять
 * содержимое массива.
 *
 * Пример:
 * \code
 * VVector<int> vector(10);
 * int *data = vector.data();
 * for(int i=0; i<10; i++)
 *     data[i] = 2 * i;
 * \endcode
 * Указатель действителен столько, сколько существует вектор или
 * пока вектор не перевыделит память.
 * \see constData() и operator[]()
 */
/*!
 * \fn const T *VVector::data() const
 * \overload
 */
/*!
 * \fn bool VVector::empty() const
 * Эта функция существует для STL совместимости. Равносильно isEmpty()
 */
/*!
 * \fn iterator VVector::end()
 * Возвращает STL итератор, указывающий на последний элемент вектора.
 * \see begin() и constEnd()
 */
/*!
 * \fn const_iterator VVector::end() const
 * \overload
 */
/*!
 * \fn bool VVector::endsWith(const T &value) const
 * Возвращает \c true, если последний элемент вектора равен \a value.
 * Иначе \c false
 * \see isEmpty() и last()
 */
/*!
 * \fn iterator VVector::erase(iterator pos)
 * Удаляет элемент, на который указывает \a pos и возвращает итератор
 * на следующий элемент (который может быть end())
 * \see insert() и remove()
 */
/*!
 * \fn iterator VVector::erase(iterator begin, iterator end)
 * \overload\n
 * Удаляет все элемент, начиная с \a begin и заканчивая \a end (но
 * не включая его). Возвращает итератор на элемент, на который
 * указывал \a end до вызова.
 */
/*!
 * \fn VVector<T> &VVector::fill(const T &value, int size = -1)
 * Назначает всем элементам значение \a value. Если \a size
 * отличен от -1 (по умолчанию -1), то вектор изменяет свой размер
 * до \a size.
 *
 * Пример:
 * \code
 * VVector<int> vector(3);
 * vector.fill(9);
 * // vector: [9, 9, 9]
 *
 * vector.fill(7, 5);
 * // vector: [7, 7, 7, 7, 7]
 * \endcode
 * \see resize()
 */

/*!
 * \fn T &VVector::first()
 * Возвращает ссылку на первый элемент вектора. Предполагается, что
 * вектор не пустой.
 * \see last() и isEmpty()
 */
/*!
 * \fn const T &VVector::first() const
 * \overload
 */
/*!
 * \fn T &VVector::front()
 * Нужна для STL совместимости. Равносильно first()
 */
/*!
 * \fn const_reference VVector::front() const
 * \overload
 */

/*!
 * \fn int VVector::indexOf(const T &value, int from = 0) const
 * Возвращает позицию первого вхождения \a value в вектор. Поиск
 * производится начиная с \a from и до конца. Если элемент не
 * найден, то возвращается -1.
 *
 * Пример:
 * \code
 * VVector<char> vector;
 * vector << 'a' << 'b' << 'c' << 'b' << 'a';
 * vector.indexOf('b');            // returns 1
 * vector.indexOf('b', 1);         // returns 1
 * vector.indexOf('b', 2);         // returns 3
 * vector.indexOf('x');            // returns -1
 * \endcode
 * Эта функция требует, чтобы тип данных поддерживал оператор
 * operator==()
 * \see lastIndexOf() и contains()
 */

/*!
 * \fn void VVector::insert(int i, const T &value)
 * Вставляет \a value в пизицию \a i. 
 *
 * Пример:
 * \code
 * VVector<char> vector;
 * vector << 'a' << 'c' << 'd';
 * vector.insert(1, 'b');
 * // vector: ['a', 'b', 'c', 'd']
 * \endcode
 * Для больших массивов эта операция может быть очень медленной, так
 * как придется переместить все элементы после \a i на одну позицию дальше.
 * Если вам нужно часто вставлять и удалять элементы, то лучше использовать
 * VLinkedList.
 * \see append(), prepend() и remove()
 */
/*!
 * \fn iterator VVector::insert(iterator before, int count, const T &value)
 * Вставляет \a count элементов \a value до элемента на который указывает
 * итератор \a before. Возвращает итератор, который указывает на первой
 * вставленный элемент.
 */
/*!
 * \fn void VVector::insert(int i, int count, const T &value)
 * \overload \n
 * Вставляет \a count копий \a value в позицию \a i в вектор.
 * Пример:
 * \code
 * VVector<double> vector;
 * vector << 2.718 << 1.442 << 0.4342;
 * vector.insert(1, 3, 9.9);
 * // vector: [2.718, 9.9, 9.9, 9.9, 1.442, 0.4342]
 * \endcode
 */
/*!
 * \fn iterator VVector::insert(iterator before, const T &value)
 * \overload \n
 * Вставляет \a value перед элементом, на который указывает \a before.
 * Возвращает итератор указывающий на вставленный элемент.
 */

/*!
 * \fn bool VVector::isEmpty() const
 * Возвращает \a true, если вектор пустой (т.е. размер равен 0).
 * Иначе \a false.
 * \see size() и resize()
 */

/*!
 * \fn T &VVector::last()
 * Возвращает ссылку на последний элемент в векторе.
 * Предполагается, что вектор не пустой.
 * \see first() и isEmpty()
 */
/*!
 * \fn const T &VVector::last() const
 * \overload
 */
/*!
 * \fn int VVector::lastIndexOf(const T &value, int from = -1) const
 * Возвращает позицию последнего вхождения элемента \a value в векторе.
 * Поиск проводится в обратном поряде от \a from. Если \a from равно -1
 * (по умолчанию), то поиск происходит с конца. Возвращается -1 если
 * элемент не найден.
 *
 * Пример:
 * \code
 * VVector<char> vector;
 * vector << 'a' << 'b' << 'c' << 'b' << 'a';
 * vector.lastIndexOf('b');        // returns 3
 * vector.lastIndexOf('b', 3);     // returns 3
 * vector.lastIndexOf('b', 2);     // returns 1
 * vector.lastIndexOf('x');        // returns -1
 * \endcode
 * Тип данных должен поддерживать оператор operator==()
 * \see indexOf()
 */
/*!
 * \fn VVector<T> VVector::mid(int pos, int length = -1) const
 * Возвращает вектор, содержащий копии элементов из текущего вектора начиная
 * с \a pos. Если \a length равна -1 (по умолчанию), копируются все 
 * элемент после \a pos. Иначе копируются \a length элементов.
 */
/*!
 * \fn void VVector::pop_back()
 * Эта функция нужна для совместимости с STL. Равносильно erase(end()-1).
 */
/*!
 * \fn void VVector::pop_front()
 * Эта функция нажна для совместимости с STL. Равносильно erase(begin())
 */
/*!
 * \fn void VVector::prepend(const T &value)
 * Вставляет \a value в начало вектора.
 *
 * Пример:
 * \code
 * VVector<int> vector;
 * vector.prepend(1);
 * vector.prepend(2);
 * vector.prepend(3);
 * // vector: [3, 2, 1]
 * \endcode
 * Равносильно vector.insert(0, \a value).
 *
 * Эта функция может быть очень медленная для больших векторов.
 * Если вам нужно часто вставлять и удалять элементы в/из середины
 * лучше использовать VList и VLinkedList.
 * \see append() и insert()
 */
/*!
 * \fn void VVector::push_back(const T &value)
 * Эта функция нужна для совместимости с STL. Равносильно append(\a value).
 */
/*!
 * \fn void VVector::push_front(const T &value)
 * Эта функция нужна для совместимости с STL. Равносильно prepend(\a value).
 */
/*!
 * \fn void VVector::remove(int i)
 * \overload \n
 * Удаляет элемент из позиции \a i.
 * \see insert(), replace() и fill()
 */
/*!
 * \fn void VVector::remove(int i, int count)
 * \overload \n
 * Удаляет \a count элементов начиная с позиции \a i.
 * \see insert(), replace() и fill()
 */
/*!
 * \fn void VVector::replace(int i, const T &value)
 * Заменяет элемент в позиции \a i на значение \a value.
 * \a i должна быть пределах вектора (т.е. 0 <= \a i < size()).
 * \see operator[]() и remove()
 */
/*!
 * \fn void VVector::reserve(int size)
 * Выделяет память для \a size элементво. Эта функция может быть
 * полезна, если вы знаете, сколько элементов будет в векторе.
 * \see capacity()
 */
/*!
 * \fn void VVector::resize(int size)
 * \overload
 * \see size()
 */
/*!
 * \fn int VVector::size() const
 * Возвращает число элементов в векторе.
 * \see isEmpty() и resize()
 */
/*!
 * \fn bool VVector::startsWith(const T &value) const
 * Возвращает \c true, если вектор начинается со значения
 * \a value. Иначе \c false.
 * \see isEmpty() и first()
 */
/*!
 * \fn T VVector::value(int i) const
 * Возвращает элемент с позиции \a i.
 * \see at() и operator[]()
 */
/*!
 * \fn T VVector::value(int i, const T &defaultValue) const
 * \overload \n
 * Если \a i вне границ вектор, возвращается \a defaultValue.
 */
/*!
 * \fn bool VVector::operator!=(const VVector<T> &other) const
 * Возвращает \c true если векторы не равны. Иначе \c false.
 * Эта функция требует, чтобы тип поддерживал операцию operator==()
 * \see operator==()
 */
/*!
 * \fn VVector<T> VVector::operator+(const VVector<T> &other) const
 * Возвращает вектор, содержащий все элементы из этого вектора
 * и \a other.
 * \see operator+=()
 */
/*!
 * \fn VVector<T> &VVector::operator+=(const VVector<T> &other)
 * Добавляет вектор \a other в конец текущего
 * \see operator+() и append()
 */
/*!
 * \fn VVector<T> &VVector::operator+=(const T &value)
 * \overload \n
 * Добавляет \a value в конец вектора.
 * \see append() и operator<<()
 */
/*!
 * \fn VVector<T> &VVector::operator<<(const T &value)
 * Добавляет \a value в конец вектора и возвращает ссылку на него.
 * \see appned() и operator+=()
 */
/*!
 * \fn VVector<T> &VVector::operator<<(const VVector<T> &other)
 * \overload
 */
/*!
 * \fn bool VVector::operator==(const VVector<T> &other) const
 * Возвращает \c true, если векторы равны. Иначе \c false.
 * Эта функция требует, чтобы тип поддерживал оператор operator==()
 * \see operator!=()
 */
/*!
 * \fn T &VVector::operator[](int i)
 * Возвращает элемент из позиции \a i. Элемент можно изменять.
 * \see at() и value()
 */
/*!
 * \fn const T &VVector::operator[](int i) const
 * \overload
 * \n Равносильно at(\a i).
 */
