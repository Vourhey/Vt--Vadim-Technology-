#include "vstringlist.h"
#include "valgorithms.h"

/*!
 * \class VStringList
 * \brief Реализует список строк.
 *
 * VStringList наследует VList<VString>. Это значит, что весь функционал
 * VList также доступен и в VStringList. Например, вы можете использовать
 * isEmpty(), чтобы узнать пустой список или нет. Так же вам доступны
 * функции append(), prepend(), insert(), replace(), removeAll(), removeAt(),
 * removeFirst(), removeLast() и removeOne(). В дополнение к ним, VStringList
 * определяет несколько специфичных функций:
 *
 * <H3>Добавление строк</H3>
 * Строки можно вставлять в список, используя append(), operator+=() и operator<<().
 * \code
 * VStringList fonts;
 * fonts << "Arial" << "Helvetica" << "Times" << "Courier";
 * \endcode
 *
 * <H3>Перебор строк</H3>
 * Для перебора списка, вы можете использовать индексирование, а также 
 * Java и STL итераторы.\n\n
 * Индексирование:
 * \code
 * for(int i=0; i<fonts.size(); ++i)
 *     cout << fonts.at(i).toLocal8Bit().constData() << endl;
 * \endcode
 * Java-итератор:
 * \code
 * VStringListIterator javaStyleIterator(fonts);
 * while(javaStyleIterator.hasNext())
 *     cout << javaStyleIterator.next().toLocal8Bit().constData() << endl;
 * \endcode
 * STL-итератор:
 * \code
 * VStringList::const_iterator constIterator;
 * for(constIterator = fonts.constBegin(); constIterator != fonts.constEnd();
 *         ++constIterator)
 *      cout << (*constIterator).toLocal8Bit().constData() << endl;
 * \endcode
 * VStringList в дополнение к VStringListIterator поддерживает VMutableStringListIterator.
 *
 * <H3>Действия над строками</H3>
 * VStringList поддерживает ряд функций, позволяющих вам работать со всеми
 * строками сразу. К примеру, вы можете собрать все строки в одну с
 * помощью join():
 * \code
 * VString str = fonts.join(",");
 * // str == "Arial,Helvetica,Times,Courier"
 * \endcode
 * Чтобы разбить строку, используйте VString::split():
 * \code
 * VStringList list;
 * list = str.split(",");
 * // list: ["Arial", "Helvetica", "Times", "Courier"]
 * \endcode
 * \see VString
 */

/*!
 * \fn VStringList::VStringList()
 * Создает пустой список.
 */
/*!
 * \fn VStringList::VStringList(const VString &str)
 * Создает список с элементом \a str.
 * \see append()
 */
/*!
 * \fn VStringList::VStringList(const VStringList &other)
 * Конструктор копий.
 */

bool VStringList::contains(const VString &str, Vt::CaseSensitivity cs) const
{
    return (indexOf(str, cs) != -1);
}

VStringList VStringList::filter(const VString &str, Vt::CaseSensitivity cs) const
{
    VStringList sl;
    
    for(int i=0; i<size(); ++i)
    {
	if(at(i).contains(str, cs))
	    sl << at(i);
    }

    return sl;
}

int VStringList::indexOf(const VString &value, int from) const
{
    for(int i=from; i<size(); ++i)
	if(!VString::compare(at(i), value))
	    return i;
    return -1;
}

int VStringList::lastIndexOf(const VString &value, int from) const
{
    if(from == -1) from = size() - 1;

    for(int i = from; i>-1; --i)
	if(!VString::compare(at(i), value))
	    return i;
    return -1;
}

VString VStringList::join(const VString &separator) const
{
    int l = size()-1;
    VString ret;
    // немного ускоряем работу
    ret.reserve(l * separator.size());

    for(int i=0; i<l; ++i)
    {
	ret.append(at(i));
	ret.append(separator);
    }

    if(!isEmpty())
	ret.append(at(size()-1));
    return ret;
}

VStringList &VStringList::replaceInStrings(const VString &before, const VString &after, Vt::CaseSensitivity cs)
{
    for(int i=0; i<size(); ++i)
	value(i).replace(before, after, cs);

    return *this;
}

int VStringList::removeDuplicates()
{
    int c = 0;

    /*
    for(int i=0; i<size(); ++i)
    {
	for(int j=i+1; j<size(); ++j)
	    if(!VString::compare(at(i), at(j)))
	    {
		++c;
		removeAt(j);
		--j;
	    }
    } */

    VStringList nlist;

    for(int i=0; i<size(); ++i)
    {
	if(!nlist.contains(at(i)))
	{
	    nlist << at(i);
	    ++c;
	}
    }

    int co = size() - c;

    clear();
    reserve(c);

    for(int i=0; i<nlist.size(); ++i)
	append(nlist.at(i));
    resize(nlist.size());

    return co;
}

/*
void VStringList::sort()
{
    vSort<VList<VString>::iterator, vLess<VString> >(begin(), end(), vLess<VString>());
}
*/
