#include "viterator.h"
#include "vvector.h"
#include "vlinkedlist.h"

/*!
 * \class VVectorIterator
 * \brief Класс реализует итератор в стиле Java для VVector и VStack
 *
 * VVector в равной степени поддерживает итераторы в стиле Java и
 * в стиле STL. Итераторы в стиле Java имеют более высокий уровень
 * и проще в использовании чем STL итераторы. С другой стороны
 * они могут быть менее эфективными.
 *
 * Существует альтернативный метод - использование индекса. Многие
 * функции в VVector требуют в качестве параметра индекс элемента:
 * получение доступа, удаление и вставка.
 *
 * VVectorIterator<T> позволяет только перебрать VVector<T> (или VStack<T>).
 * Если вам нужно изменить содержимое, используйте VMutableVectorIterator<T>.
 *
 * VVectorIterator при создании принимает VVector в качестве параметра.
 * После этого итератор указывает на элемент перед первым.
 * \code
 * VVector<float> vector;
 *  ...
 * VVectorIterator<float> i(vector);
 * while (i.hasNext())
 *     cout << i.next();
 * \endcode
 * Функция next() возвращает следующий элемент и передвигает итератор.
 * В отличии от STL итераторов, Java итераторы указывают на позицию
 * между элементами. Первый вызов next() возвращает первый элемент и
 * указывает на позицию между первым и вторым. Второй вызов
 * возвращает второй элемент и передвигает указатель на позицию
 * между вторым и третьим. И так далее.
 *
 * \image html javaiterators1.png
 *
 * Следующий пример показывает как перебрать контейнер в обратном
 * порядке:
 * \code
 * VVectorIterator<float> i(vector);
 * i.toBack();
 * while (i.hasPrevious())
 *     cout << i.previous();
 * \endcode
 *
 * Если вы хотите найти все вхождения элемента, используйте
 * findNext() и findPrevious() в цикле.
 * \see VMutableVectorIterator и VVector::const_iterator
 */
/*!
 * \class VMutableVectorIterator
 * \brief Класс реализует неконстантный Java итератор для VVector и VStack
 *
 * VVector в равной степени поддерживает Java и STL итераторы. Java
 * итераторы более высокоуровневые и проще в использовании чем STL.
 * С другой стороны, они могут быть менее эфективными.
 *
 * Альтернативный метод заключается в использовании индексов позиции.
 * Многие функции VVector принимают в качестве аргумента индекс
 * элемента: доступ к элементу, вставка, удаление и некоторые другие.
 *
 * VMutableVectorIterator<T> позволяет перебрать VVector<T> и изменять
 * его. Если вам не требуется менять содержимое, то лучше использовать
 * VVectorIterator\<T\>.
 *
 * При создании VMutalbeVectorIterator принимает контейнер в качестве
 * параметра. Итератор устанавливается на начало (т.е. до первого
 * элемента). Пример, как перебрать все элементы:
 * \code
 * VVector<double> vector;
 * ...
 * VMutableVectorIterator<double> i(vector);
 * while(i.hasNext())
 *     cout << i.next();
 * \endcode
 * Функция next() возвращает следующий элемент и перемещает итератор.
 * В отличии от STL итераторов, Java итераторы указывают на позицию
 * между элементами. Первый вызов next() возвращает первый элемент
 * и устанавливает итератор между первым и вторым элементом.
 * Второй вызов возвращает второй элемент и устанавливает итератор
 * между вторым и третьим элементом. И так далее.
 * \image html javaiterators1.png
 * Здесь показано, как пройти контейнер в обратном порядке:
 * \code
 * VMutableVectorIterator<double> i(vector);
 * i.toBack();
 * while(i.hasPrevious())
 *     cout << i.previous();
 * \endcode
 * Если вы хотите найти все вхождения одного элемента, то используйте
 * findNext() или findPrevious() в цикле.
 *
 * Если вам нужно удалить элемент из контейнера, используйте remove().
 * Для изменения значения setValue(). Для вставки нового элемента insert().
 * \nПример:
 * \code
 * VMutableVectorIterator<int> i(vector);
 * while(i.hasNext())
 * {
 *     int val = i.next();
 *     if(val < 0)
 *         i.setValue(-val);
 *     else if(val == 0)
 *         i.remove();
 * }
 * \endcode
 * Только один итератор может быть активным в любое время. Так как
 * получение доступа посредством двух и более итераторов может привести
 * к неопределенному поведению.
 * \see VVectorIterator и VVector::iterator
 */
/*!
 * \class VLinkedListIterator
 * \brief Реализует константный Java итератор для VLinkedList
 *
 * VLinkedList в равной степени поддерживает Java и STL итераторы. Java
 * итераторы более высокоуровневы и проще в использовании. С другой стороны,
 * они могут быть менее эфективными.
 *
 * VLinkedListIterator<T> позволяет вам перебрать VLinkedList<T>. Если вам
 * требуется изменить содержимое контейнера, то используйте
 * VMutableLinkedListIterator<T>.
 *
 * Конструктор требует VLinkedList в качестве аргумента. После создания,
 * итератор устанавливается на начало списка (до первого элемента).
 * Дальше показано как перебрать все элементы:
 * \code
 * VLinkedList<double> list;
 * ...
 * VLinkedListIterator<double> i(list);
 * while(i.hasNext())
 *     cout << i.next();
 * \endcode
 * Функция next() возвращает следующий элемент и перемещает итератор.
 * В отличии от STL итераторов, Java итераторы указывают между реальными
 * элементами. Первый вызов next() возвращает первый элемент и 
 * устанавливает итератор между первым и вторым. Следущий вызов 
 * возвращает второй элемент и устанавливает итератор между вторым и 
 * третьим и так далее.
 * \image html javaiterators1.png
 * Дальше показано как перебрать все элементы в обратном порядке:
 * \code
 * VLinkedListIterator<double> i(list);
 * i.toBack();
 * while(i.hasPrevious())
 *     cout << i.previous();
 * \endcode
 * Если вы хотите найти все вхождения элемента в список, то
 * используйте findNext() или findPrevious() в цикле.\n
 * Несколько итераторов могут быть использованы на один и тот же
 * список. Если изменить список вне итератора, то VLinkedListIterator 
 * будет продолжать перебирать оригинальный список, игнорируя изменения.
 * \see VMutableLinkedListIterator и VLinkedList::const_iterator
 */
/*!
 * \class VMutableLinkedListIterator
 * \brief Реализует неконстантый Java итератор для VLinkedList
 *
 * VLinkedList в равной степени поддерживает Java и STL итераторы.
 * Java итераторы более высокоуровневы и проще в использовании.
 * С другой стороны, они могут быть менее эфективными.
 *
 * VMutableLinkedListIterator<T> позволяет вам перебрать VLinkedList<T>
 * и изменить содержимое. Если вам не нужно менять список (или имеется
 * только константый VLinkedList), используйте более быстрый
 * VLinkedListIterator<T>.
 *
 * Конструктор требует VLinkedList в качестве аргумента. После создания
 * итератор устанавливается на начало списка (до первого элемента).
 * Дальше показано, как перебрать все элементы списка:
 * \code
 * VLinkedList<double> list;
 * ...
 * VMutableLinkedListIterator<double> i(list);
 * while(i.hasNext())
 *     cout << i.next();
 * \endcode
 * Функция next() возвращает следующий элемент и перемещает итератор.
 * В отличии от STL итераторов, Java итераторы указывают на позицию
 * между элементами. Первый вызов next() возвращает первый элемент
 * и устанавливает итератор между первым и вторым. Второй вызов
 * возвращает второй элемент и перемещает итератор на позицию
 * между вторым и третьим. И так далее.
 * \image html javaiterators1.png
 * Дальше показано, как перебрать список в обратном порядке:
 * \code
 * VMutableLinkedListIterator<double> i(list);
 * i.toBack();
 * while(i.hasPrevious())
 *     cout << i.previous();
 * \endcode
 * Если вы хотите найти все вхождения элемента в список, используйте
 * findNext() и findPrevious() в цикле.\n
 * Если вы хотите удалить текущий элемент, используйте remove().
 * Для изменения значения - setValue(). Если хотите вставить элемент,
 * используйте insert().\n
 * Пример:
 * \code
 * VMutableLinkedListIterator<int> i(list);
 * while(i.hasNext())
 * {
 *     int val = i.next();
 *     if(val < 0)
 *         i.setValue(-val);
 *     else if(val == 0)
 *         i.remove();
 * }
 * \endcode
 * В примере все нулевые элементы удаляются, а отрицательные числа
 * заменяются на противоположные.\n
 * Только один изменяемый итератор может быть активным в любое время.
 * Кроме того, нельзя делать измененй списка непосредственно, а не через
 * итератор. Так как это приведет к неопределенному результату.
 * \see VLinkedListIterator и VLinkedList::iterator
 */

/*!
 * \fn VVectorIterator::VVectorIterator(const VVector<T> &vector)
 * Создает итератор для \a vector. Итератор устанавливается на начало вектора
 * (до первого элемента).
 * \see operator=()
 */
/*!
 * \fn bool VVectorIterator::findNext(const T &value)
 * Ищит \a value начиная с текущей позиции и до конца. Возвращает \c true, если
 * \a value найден. Иначе \c false.
 *
 * После вызова, если элемент найден, итератор устанавливается на элемент
 * после найденного. Иначе, на конец вектора.
 * \see findPrevious()
 */
/*!
 * \fn bool VVectorIterator::findPrevious(const T &value)
 * Ищит \a value начиная с текущей позиции в обратном порядке. Возвращаетa \c true
 * если элемент найден. Иначе \c false.
 *
 * После вызова, если элемент найден, итератор устанавливается на элемент до
 * найденного. Иначе на начало контейнера.
 * \see findNext()
 */
/*!
 * \fn bool VVectorIterator::hasNext() const
 * Возвращает \c true, если существует ещё хотя бы один элемент после этого.
 * Иначе \c false.
 * \see hasPrevious() и next()
 */
/*!
 * \fn bool VVectorIterator::hasPrevious() const
 * Возвращает \c true, если существует ещё хотя бы один элемент до этого.
 * Иначе \c false.
 * \see hasNext() и previous()
 */
/*!
 * \fn const T &VVectorIterator::next()
 * Возвращает следующий элемент и передвигает итератор на одну позицию.
 * \see hasNext(), peekNext() и previous()
 */
/*!
 * \fn const T &VVectorIterator::peekNext() const
 * Возвращает следующий элемент, но не перемещает итератор.
 * \see hasNext(), next() и peekPrevious()
 */
/*!
 * \fn const T &VVectorIterator::peekPrevious() const
 * Возвращает предыдущий элемент, но не перемещает итератор.
 * \see hasPrevious(), previous() и peekNext()
 */
/*!
 * \fn const T &VVectorIterator::previous()
 * Возвращает предыдущий элемент и перемещает итератор назад
 * на одну позицию.
 * \see hasPrevious(), peekPrevious() и next()
 */
/*!
 * \fn void VVectorIterator::toBack()
 * Перемещает итератор в конец конетейнера (после последнего)
 * \see toFront() и previous()
 */
/*!
 * \fn void VVectorIterator::toFront()
 * Перемещает итератор в начало контейнера (перед предыдущим)
 * \see toBack() и next()
 */
/*!
 * \fn VVectorIterator &VVectorIterator::operator=(const VVector<T> &vector)
 * Назначает этому итератору контейнер \a vector.
 * \see toFront() и toBack()
 */

/*!
 * \fn VMutableVectorIterator::VMutableVectorIterator(VVector<T> &vector)
 * \copydoc VVectorIterator::VVectorIterator(const VVector<T> &vector)
 */
/*!
 * \fn bool VMutableVectorIterator::findNext(const T &value)
 * Ищит \a value начиная с текущей позии и до конца. Возвращает \c true
 * есил элемент найден. Иначе \c false.
 *
 * После вызова, если \a value найден, итератор устанавливается на 
 * позицию после элемента. Иначе итератор устанавливается на конец
 * контейнера.
 * \see findPrevious().
 */
/*!
 * \fn bool VMutableVectorIterator::findPrevious(const T &value)
 * Ищит \a value начиная с текущей позиции в обратном порядке. Возвращаетa \c true
 * если элемент найден. Иначе \c false.
 * 
 * После вызова, если элемент найден, итератор устанавливается на позицию до
 * найденного. Иначе на начало контейнера.
 * \see findNext()
 */
/*!
 * \fn bool VMutableVectorIterator::hasNext() const
 * \copydoc VVectorIterator::hasNext()
 */
/*!
 * \fn bool VMutableVectorIterator::hasPrevious() const
 * \copydoc VVectorIterator::hasPrevious()
 */
/*!
 * \fn void VMutableVectorIterator::insert(const T &value)
 * Вставляет \a value в текущую позицию. После вызова итератор
 * устанавливается после вставленного элемента.
 * \see remove() и setValue()
 */
/*!
 * \fn T &VMutableVectorIterator::next()
 * \copydoc VVectorIterator::next()
 */
/*!
 * \fn T &VMutableVectorIterator::peekNext() const
 * Возвращает ссылку на следующий элемент, но не перемещает итератор.
 * \see hasNext(), next() и peekPrevious()
 */
/*!
 * \fn T &VMutableVectorIterator::peekPrevious() const
 * Возвращает ссылку на предыдущий элемент, но не перемещает итератор.
 * \see hasPrevious(), previous() и peekNext()
 */
/*!
 * \fn T &VMutableVectorIterator::previous()
 * Возвращает ссылку на предыдущий элемент и перемещает итератор
 * на одну позицию назад.
 * \see hasPrevious(), peekPrevious() и next()
 */
/*!
 * \fn void VMutableVectorIterator::remove()
 * Удаляет последний элемент, который вернула функция обхода
 * (next(), previous(), findNext() или findPrevious()).
 *
 * Пример:
 * \code
 * VMutableVectorIterator<int> i(vector);
 * while(i.hasNext())
 * {
 *     int val = i.next();
 *     if(val < -32768 || val > 32767)
 *         i.remove();
 * }
 * \endcode
 * \see insert() и setValue()
 */
/*!
 * \fn void VMutableVectorIterator::setValue(const T &value) const
 * Заменяет значение последнего элемент, полученного функцией обхода
 * на значение \a value.
 *
 * Пример:
 * \code
 * VMutableVectorIterator<double> i(list);
 * while(i.hasNext())
 * {
 *     double val = i.next();
 *     i.setValue(sqrt(val));
 * }
 * \endcode
 * \see value, remove() и insert()
 */
/*!
 * \fn void VMutableVectorIterator::toBack()
 * \copydoc VVectorIterator::toBack()
 */
/*!
 * \fn void VMutableVectorIterator::toFront()
 * \copydoc VVectorIterator::toFront()
 */
/*!
 * \fn const T &VMutableVectorIterator::value() const
 * Возвращает значение элемента, который был получен после вызова
 * функци обхода (next(), previous(), findNext() или findPrevious()).
 * \see setValue()
 */
/*!
 * \fn T &VMutableVectorIterator::value()
 * \overload
 */
/*!
 * \fn VMutableVectorIterator &VMutableVectorIterator::operator=(VVector<T> &vector)
 * \copydoc VVectorIterator::operator=()
 */
