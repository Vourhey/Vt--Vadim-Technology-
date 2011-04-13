#ifndef VLINKEDLIST_H
#define VLINKEDLIST_H

#include <list>
#include "viterator.h"

template<class T>
class VLinkedList
{
    struct Node;
public:
    typedef const T *      const_pointer;
    typedef const T &      const_reference;
    typedef vptrdiff       difference_type;
    typedef T *            pointer;
    typedef T &            reference;
    typedef int            size_type;
    typedef T              value_type;

    inline VLinkedList();
    VLinkedList(const VLinkedList<T> &other);
    inline ~VLinkedList() { clear(); }

    void append(const T &value);
    void clear();
    bool contains(const T &value) const;
    int count(const T &value) const;
    int count() const { return _size; }

    bool endsWith(const T &value) const
	{ return _end->value == value; }

    T &first() { return _end->nextNode->value; }
    const T &first() const { return _end->nextNode->value; }

    bool isEmpty() const { return _size == 0; }

    T &last() { return _end->value; }
    const T &last() const { return _end->value; }

    void prepend(const T &value);

    int removeAll(const T &value);
    void removeFirst();
    void removeLast();
    bool removeOne(const T &value);

    int size() const { return _size; }
    bool startsWith(const T &value) const
	{ return _end->nextNode->value == value; }

    T takeFirst();
    T takeLast();

    // for STL
    class iterator;
    class const_iterator
    {
    public:
	Node *i;
	const_iterator() : i(0) {}
	const_iterator(Node *n) : i(n) {}
	const_iterator(const const_iterator &other) : i(other.i) {}
	const_iterator(iterator other) : i(other.i) {}
	bool operator!=(const const_iterator &other) const
	    { return i != other.i; }
	const T &operator*()const { return i->value; }
	const_iterator operator+(int j) const
	{
	   Node *n = i; 
	   if(j > 0) while(j-- != 0) n=n->nextNode; 
	   else while(j++ != 0)      n=n->prevNode; 
	   return n; 
	}
	const_iterator &operator++() { i = i->nextNode; return *this; }
	const_iterator operator++(int)
	    { Node *n = i; i = i->nextNode; return n; }
	const_iterator &operator+=(int j)
	    { i = operator+(j); return *this; }
	const_iterator operator-(int j) const
	    { return operator+(-j); }
	const_iterator &operator--() { i = i->prevNode; return *this; }
	const_iterator operator--(int)
	    { Node *n = i; i->prevNode; return n; }
	const_iterator &operator-=(int j)
	    { i = operator+(-j); return *this; }
	const T *operator->() const { return &i->value; }
	const_iterator &operator=(const const_iterator &other)
	    { i = other.i; return *this; }
	bool operator==(const const_iterator &other) const
	    { return i == other.i; }
    };
    friend class const_iterator;

    class iterator
    {
    public:
	Node *i;
	iterator() : i(0) {}
	iterator(Node *n) : i(n) {}
	iterator(const iterator &other) : i(other.i) {}
	bool operator!=(const iterator &other) const
	    { return i != other.i; }
	bool operator!=(const const_iterator &other) const
	    { return i != other.i; }
	T &operator*() const { return i->value; }
	iterator operator+(int j) const
	{
	    Node *n = i;
	    if(j > 0) while(j-- != 0) n = n->nextNode;
	    else while(j++ != 0)      n = n->prevNode;
	    return n;
	}
	iterator &operator++() { i = i->nextNode; return i; }
	iterator operator++(int)
	    { Node *n = i; i = i->nextNode; return n; }
	iterator &operator+= (int j) 
	    { i = operator+(j); return *this; }
	iterator operator-(int j) const
	    { return operator+(-j); }
	iterator &operator--() { i = i->prevNode; return i; }
	iterator operator--(int)
	    { Node *n = i; i = i->prevNode; return n; }
	iterator &operator-=(int j) { return operator+=(-j); }
	T *operator->() const { return &i->value; }
	iterator &operator=(const iterator &other)
	    { i = other.i; return *this; }
	bool operator==(const iterator &other) const
	    { return i == other.i; }
	bool operator==(const const_iterator &other) const
	    { return i == other.i; }
    };
    friend class iterator;
    typedef const_iterator ConstIterator;
    typedef iterator       Iterator;

    iterator begin() { return _end->nextNode; }
    const_iterator begin() const { return _end->nextNode; }

    iterator end() { return _end; }
    const_iterator end() const { return _end; }

    const_iterator constBegin() const { return _end->nextNode; }
    const_iterator constEnd() const { return _end; }

    iterator erase(iterator pos);
    iterator erase(iterator begin, iterator end);
    iterator insert(iterator before, const T &value);

    std::list<T> toStdList() const
    {
	std::list<T> ls;
	ls.resize(size());

	iterator it = begin();
	while(it != end())
	{
	    ls.push_back(*it);
	    ++it;
	}
	return ls;
    }

    static VLinkedList<T> fromStdList(const std::list<T> &list)
    {
	VLinkedList<T> ll;

	typename std::list<T>::const_iterator it = list.begin();
	for(; it != list.end(); ++it)
	    ll.append(*it);

	return ll;
    }

    // STL comfort
    T &back() { return _end->value; }
    const T &back() const { return _end->value; }

    bool empty() const { return _size == 0; }

    T &front() { return _end->nextNode->value; }
    const T &front() const { return _end->nextNode->value; }

    void pop_back() { removeLast(); }
    void pop_front() { removeFirst(); }
    void push_back(const T &value) { append(value); }
    void push_front(const T &value) { prepend(value); }

    // operators
    bool operator!=(const VLinkedList<T> &other) const
	{ return !operator==(other); }
    bool operator==(const VLinkedList<T> &other) const;
    VLinkedList<T> operator+(const VLinkedList<T> &other) const
	{ VLinkedList<T> ret; ret << *this << other; return ret; }
    VLinkedList<T> &operator+=(const VLinkedList<T> &other);
    VLinkedList<T> &operator+=(const T &value) 
        { append(value); return *this; }
    VLinkedList<T> &operator<<(const VLinkedList<T> &other)
	{ return operator+=(other); }
    VLinkedList<T> &operator<<(const T &value)
	{ return operator+=(value); }
    VLinkedList<T> &operator=(const VLinkedList<T> &other)
	{ clear(); operator+=(other); return *this; }

private:
    struct Node
    {
	Node *prevNode;
	Node *nextNode;
	T value;
    };
    Node *_end;
    int _size;
};

template<class T>
VLinkedList<T>::VLinkedList()
{
    _end = new Node;
    _end->prevNode = _end;
    _end->nextNode = _end;
    _size = 0;
}

template<class T>
VLinkedList<T>::VLinkedList(const VLinkedList<T> &other)
{
    operator+=(other);
}

template<class T>
void VLinkedList<T>::append(const T &value)
{
    Node *n = new Node;
    n->value = value;
    n->prevNode = _end->prevNode;
    n->nextNode = _end;
    n->prevNode->nextNode = n;
    _end->prevNode = n;
    ++_size;
}

template<class T>
void VLinkedList<T>::clear()
{
    while(_size--)
    {
	Node *tmp = _end;
	_end = _end->nextNode;
	delete tmp;
    }
}

template<class T>
bool VLinkedList<T>::contains(const T &value) const
{
    Node *n = _end->nextNode;
    while(n != _end)
    {
	if(n->value == value)
	    return true;
	n = n->nextNode;
    }
    return false;
}

template<class T>
int VLinkedList<T>::count(const T &value) const
{
    int c = 0;
    Node *n = _end->nextNode;
    while(n != _end)
    {
	if(n->value == value)
	    ++c;
	n = n->nextNode;
    }
    return c;
}

template<class T>
void VLinkedList<T>::prepend(const T &value)
{
    Node *n = new Node;
    n->value = value;
    n->prevNode = _end;
    n->nextNode = _end->nextNode;
    n->nextNode->prevNode = n;
    _end->nextNode = n;
    _size++;
}

template<class T>
int VLinkedList<T>::removeAll(const T &value)
{
    Node *n = _end->nextNode;
    int c = 0;
    while(n != _end)
    {
	if(n->value == value)
	{
	    Node *tmp = n->nextNode;
	    n->prevNode->nextNode = tmp;
	    tmp->prevNode = n->prevNode;
	    delete n;
	    n = tmp;
	    ++c;
	}
	else
	    n = n->nextNode;
    }
    _size -= c;
    return c;
}

template<class T>
void VLinkedList<T>::removeFirst()
{
    Node *n = _end->nextNode;
    _end->next = n->nextNode;
    n->nextNode->prevNode = _end;
    --_size;
    delete n;
}

template<class T>
void VLinkedList<T>::removeLast()
{
    Node *n = _end->prevNode;
    _end->prevNode = n->prevNode;
    n->nextNode = _end;
    --_size;
    delete n;
}

template<class T>
bool VLinkedList<T>::removeOne(const T &value)
{
    Node *n = _end->nextNode;
    while(n != _end)
    {
	if(n->value == value)
	{
	    Node *tmp = n->nextNode;
	    n->prevNode->nextNode = tmp;
	    tmp->prevNode = n->prevNode;
	    delete n;
	    --_size;
	    return true;
	}
	else
	    n = n->nextNode;
    }
    return false;
}

template<class T>
T VLinkedList<T>::takeFirst()
{
    T t = _end->nextNode->value;
    removeFirst();
    return t;
}

template<class T>
T VLinkedList<T>::takeLast()
{
    T t = _end->prevNode->value;
    removeLast();
    return t;
}

template<class T>
bool VLinkedList<T>::operator==(const VLinkedList<T> &other) const
{
    if(_size != other._size)
	return false;

    Node *n = _end->nextNode;
    Node *no = other._end->nextNode;
    while(n != _end)
    {
	if(n->value != no->value)
	    return false;
	n = n->nextNode;
	no = no->nextNode;
    }

    return true;
}

template<class T>
VLinkedList<T> &VLinkedList<T>::operator+=(const VLinkedList<T> &other)
{
    Node *n = other._end->nextNode;
    while(n != other._end)
    {
	append(n->value);
	n = n->nextNode;
    }
    return *this;
}

template<class T>
typename VLinkedList<T>::iterator VLinkedList<T>::erase(iterator pos)
{
    return erase(pos, pos+1);
}

template<class T>
typename VLinkedList<T>::iterator VLinkedList<T>::erase(iterator begin, iterator end)
{
    Node *n = begin.i;
    while(n != end.i)
    {
	Node *tmp = n->nextNode;
	tmp->prevNode = n->prevNode;
	n->prevNode->nextNode = tmp;
	delete n;
	n = tmp;
	--_size;
    }
    return end;
}

template<class T>
typename VLinkedList<T>::iterator VLinkedList<T>::insert(typename VLinkedList<T>::iterator before, const T &value)
{
    Node *n = new Node;
    Node *i = before.i;
    n->value = value;
    n->nextNode = i;
    n->prevNode = i->prevNode;
    n->prevNode->nextNode = n;
    i->prevNode = n;
    return n;
}

// Java iterators
DEFINE_READONLY_ITERATOR_FOR_C(LinkedList)
DEFINE_MUTABLE_ITERATOR_FOR_C(LinkedList)

#endif
