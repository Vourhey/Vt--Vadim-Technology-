#ifndef VLIST_H
#define VLIST_H

#include <list>
#include "vglobal.h"
#include "viterator.h"
#include "vvector.h"

template<class T>
class VList
{
    struct Node;
public:
    typedef const T * const_pointer;
    typedef const T & const_reference;
    typedef vptrdiff  difference_type;
    typedef T *       pointer;
    typedef T &       reference;
    typedef int       size_type;
    typedef T         value_type;

    VList();
    VList(const VList<T> &other);
    inline ~VList() { free(d); }

    void append(const T &value);
    void append(const VList<T> &value);
    void prepend(const T &value);

    const T &at(int i) const { return *d->data[i].v; }
    void clear() { free(d); d = 0; }

    bool contains(const T &value) const;
    int count(const T &value) const;

    int count() const  { return d->size; }
    int length() const { return d->size; }
    int size() const   { return d->size; }

    bool endsWith(const T &value) const;
    bool startsWith(const T &value) const;

    T &first() { return *d->data->v; }
    const T &first() const { return *d->data->v; }
    T &last() { return *d->data[d->size-1].v; }
    const T &last() const { return *d->data[d->size-1].v; }

    bool isEmpty() const { return d->size == 0; }
    int indexOf(const T &value, int from = 0) const;
    int lastIndexOf(const T &value, int from = -1) const;

    VList<T> mid(int pos, int length = -1) const;
    void insert(int i, const T &value);

    int removeAll(const T &value);
    void removeAt(int i);
    void removeFirst() { removeAt(0); }
    void removeLast()  { removeAt(d->size-1); }
    bool removeOne(const T &value);

    T takeAt(int i);
    T takeFirst() { return takeAt(0); }
    T takeLast()  { return takeAt(d->size-1); }

    T value(int i, const T &defaultValue) const 
    {
	if(i < 0 || i >= d->size) return defaultValue; 
	return *d->data[i].v; 
    }
    T value(int i) const { return value(i, T()); }

    void reserve(int alloc);

    void move(int from, int to);
    void replace(int i, const T &value);
    void swap(int i, int j);

    class iterator;
    class const_iterator
    {
    public:
	typedef std::random_access_iterator_tag iterator_category;

	Node *i;
	const_iterator() : i(0) {}
	const_iterator(const const_iterator &other) : i(other.i) {}
	const_iterator(const iterator &other) : i(other.i) {}
	const_iterator(Node *n) : i(n) {}

	bool operator!=(const const_iterator &other) const { return i != other.i; }
	const T &operator*() const { return *i->v; }
	const_iterator operator+(int j) const { return i + j; }
	const_iterator &operator++() { ++i; return *this; }
	const_iterator operator++(int) { Node *n = i; ++i; return n; }
	const_iterator &operator+=(int j) { i += j; return *this; }
	const_iterator operator-(int j) const { return i - j; }
	int operator-(const_iterator other) const { return int(i - other.i); }
	const_iterator &operator--() { --i; return *this; }
	const_iterator operator--(int) { Node *n = i; --i; return n; }
	const_iterator &operator-=(int j) { i -= j; return *this; }
	const T *operator->() const { return i.v; }
	bool operator<(const const_iterator &other) const  { return i < other.i; }
	bool operator<=(const const_iterator &other) const { return i <= other.i; }
	bool operator==(const const_iterator &other) const { return i == other.i; }
	bool operator>(const const_iterator &other) const  { return i > other.i; }
	bool operator>=(const const_iterator &other) const { return i >= other.i; }
	const T &operator[](int j) const { return *i[j].v; }
    };

    class iterator
    {
    public:
	typedef std::random_access_iterator_tag iterator_category;
	Node *i;

	iterator() : i(0) {}
	iterator(const iterator &other) : i(other.i) {}
	iterator(Node *n) : i(n) {}
	bool operator!=(const iterator &other) const { return i != other.i; }
	bool operator!=(const const_iterator &other) const { return i != other.i; }
	T &operator*() const { return *i->v; }
	iterator operator+(int j) const { return i + j; }
	iterator &operator++() { ++i; return *this; }
	iterator operator++(int) { Node *n = i; i++; return n; }
	iterator &operator+=(int j) { i += j; return *this; }
	iterator operator-(int j) const { return i - j; }
	int operator-(iterator other) const { return int(i - other.i); }
	iterator &operator--() { --i; return *this; }
	iterator operator--(int) { Node *n = i; --i; return n; }
	iterator &operator-=(int j) { i -= j; return *this; }
	T *operator->() const { return i.v; }
	bool operator<(const iterator &other) const { return i < other.i; }
	bool operator<(const const_iterator &other) const { return i < other.i; }
	bool operator<=(const iterator &other) const { return i <= other.i; }
	bool operator<=(const const_iterator &other) const { return i < other.i; }
	bool operator==(const iterator &other) const { return i == other.i; }
	bool operator==(const const_iterator &other) const { return i == other.i; }
	bool operator>(const iterator &other) const { return i > other.i; }
	bool operator>(const const_iterator &other) const { return i > other.i; }
	bool operator>=(const iterator &other) const { return i >= other.i; }
	bool operator>=(const const_iterator &other) const { return i >= other.i; }
	T &operator[](int j) const { return *i[j].v; }
    };

    typedef const_iterator ConstIterator;
    typedef iterator       Iterator;

    iterator begin() { return d->data; }
    const_iterator begin() const { return d->data; }
    const_iterator constBegin() const { return d->data; }
    const_iterator constEnd() const { return d->data; }
    iterator end() { return d->data+d->size; }
    const_iterator end() const { return d->data+d->size; }

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

    VVector<T> toVector() const
    {
	VVector<T> vec;
	vec.reserve(size());

	for(iterator it = begin(); it!=end(); ++it)
	    vec.append(*it);

	return vec;
    }

    static VList<T> fromStdList(const std::list<T> &list)
    {
	VList<T> l;
	l.reserve(list.size());

	typename std::list<T>::iterator it = list.begin();
	for(; it!=list.end(); ++it)
	    l.append(*it);
	return l;
    }

    static VList<T> fromVector(const VVector<T> &vector)
    {
	VList<T> l;
	l.reserve(vector.size());

	for(int i=0; i<vector.size(); i++)
	    l.append(vecotr[i]);

	return l;
    }

    // STL comfort
    inline T &back() { return last(); }
    inline const T &back() const { return last(); }
    inline T &front() { return first(); }
    inline const T &front() const { return first(); }

    inline bool empty() const { return d->size == 0; }

    inline void pop_back() { removeLast(); }
    inline void pop_front() { removeFirst(); }
    inline void push_back(const T &value) { append(value); }
    inline void push_front(const T &value) { prepend(value); }

    iterator insert(iterator before, const T &value);
    iterator erase(iterator pos) { return erase(pos, pos+1); }
    iterator erase(iterator begin, iterator end);

    // operators 
    VList<T> operator+(const VList<T> &other) const
    {
	VList<T> ret;
	ret.reserve(d->size+other.d->size);
	ret.append(*this);
	ret.append(other);
	return ret;
    }
    VList<T> &operator+=(const VList<T> &other) { append(other); return *this; }
    VList<T> &operator+=(const T &value) { append(value); return *this; }
    VList<T> &operator<<(const VList<T> &other) { append(other); return *this; }
    VList<T> &operator<<(const T &value) { append(value); return *this; }
    bool operator==(const VList<T> &other) const;
    bool operator!=(const VList<T> &other) const
	{ return !operator==(other); }

    T &operator[](int i) { return *d->data[i].v; }
    const T &operator[](int i) const { return at(i); }

    VList<T> &operator=(const VList<T> &other)
    {
	free(d);
	d = (VListData*)malloc(sizeof(VListData)+other.size()*sizeof(T));
	d->data = d->array;
	
	for(int i=0; i<other.size(); ++i)
	    d->data[i] = other.d->data[i];
	return *this;
    }

private:
    struct Node
    {
	Node(const T &value) : v(new T(value)) {}
	T *v;
    };
    struct VListData
    {
	int size;
	int alloc;
	Node *data;
	Node array[1];
    };
    VListData *d;
    void reallocData(int _s);
};

template<class T>
void VList<T>::reallocData(int _s)
{
    if(!d)
    {
	d = (VListData*)malloc(sizeof(VListData) + _s*sizeof(T*));
	d->size = 0;
	d->alloc = _s;
	d->data = d->array;
    }
    else if(_s > d->alloc)
    {
	VListData *x = (VListData*)malloc(sizeof(VListData)+ _s*sizeof(T*));
	x->alloc = _s;
	x->size = d->size;
	x->data = x->array;
	memcpy(x->data, d->data, d->size*sizeof(Node));
	free(d);
	d = x;
    }
}

template<class T>
VList<T>::VList()
{
    d = (VListData*)malloc(sizeof(VListData));
    d->size = d->alloc = 0;
    d->data = d->array;
}

template<class T>
VList<T>::VList(const VList<T> &other)
{
    d = (VListData*)malloc(sizeof(VListData)+other.d->size*sizeof(T*));
    d->data = d->array;
    d->alloc = other.d->size;
    d->size = other.d->size;
    memcpy(d->data, other.d->data, sizeof(Node)*d->size);
}

template<class T>
void VList<T>::append(const T &value)
{
    reallocData(d->size+1);
    d->size++;
    Node *n = new Node(value);
    d->data[d->size-1] = *n;
}

template<class T>
void VList<T>::append(const VList<T> &value)
{
    reserve(value.d->size + d->size);
    for(int i = 0; i<value.d->size; i++)
	(d->data+d->size+i).v = new T(*value.d->data[i].v);
    d->size += value.d->size;
}

template<class T>
void VList<T>::reserve(int alloc)
{
    reallocData(alloc);
}

template<class T>
bool VList<T>::contains(const T &value) const
{
    for(int i = 0; i<d->size; i++)
	if(*d->data[i].v == value)
	    return true;
    return false;
}

template<class T>
int VList<T>::count(const T &value) const
{
    int c = 0;
    for(int i=0; i<d->size; i++)
	if(*d->data[i].v == value)
	    ++c;
    return c;
}

template<class T>
bool VList<T>::endsWith(const T &value) const
{
    return (*d->data[d->size-1].v == value);
}

template<class T>
bool VList<T>::startsWith(const T &value) const
{
    return (*d->data->v == value);
}

template<class T>
int VList<T>::indexOf(const T &value, int from) const
{
    for(int i = from; i<d->size; i++)
	if(*d->data[i].v == value)
	    return i;
    return -1;
}

template<class T>
int VList<T>::lastIndexOf(const T &value, int from ) const
{
    if(from == -1) from = d->size-1;

    while(from-- > 0)
	if(*d->data[from].v == value)
	    return from;
    return -1;
}

template<class T>
VList<T> VList<T>::mid(int pos, int length) const
{
    if(length == -1) length = d->size - pos;

    VList<T> ret;
    ret.reserve(length);

    Node *t = d->data+pos;
    for(int i =0; i<length; i++)
	ret.append(*t[0].v);
    return ret;
}

template<class T>
void VList<T>::prepend(const T &value)
{
    reallocData(d->size + 1);
    Node *n = new Node(value);

    memmove(d->data+1, d->data, d->size*sizeof(Node));
    d->data[0] = *n;
    d->size++;
}

template<class T>
int VList<T>::removeAll(const T &value)
{
    int c = 0;
    for(int i = 0; i<d->size; i++)
	if(*d->data[i].v == value)
	{
	    removeAt(i);
	    ++c;
	}
    return c;
}

template<class T>
void VList<T>::removeAt(int i)
{
    if(i == d->size-1) 
    {
	d->size--; 
	return; 
    }
    memmove(d->data+i, d->data+i+1, sizeof(Node));
    d->size--;
}

template<class T>
bool VList<T>::removeOne(const T &value)
{
    for(int i = 0; i<d->size; i++)
	if(*d->data[i].v == value)
	{
	    removeAt(i);
	    return true;
	}
    return false;
}

template<class T>
T VList<T>::takeAt(int i)
{
    T t = at(i);
    removeAt(i);
    return t;
}

template<class T>
typename VList<T>::iterator VList<T>::erase(iterator begin, iterator end )
{
    int e = end - this->begin();
    int b = begin - this->begin();
    int n = e - b;

    memmove(d->data+b, d->data+e, n*sizeof(Node));
    d->size -= n;

    return d->data + b;
}

template<class T>
void VList<T>::insert(int i, const T &value)
{
    reallocData(d->size + 1);
    memmove(d->data+i+1, d->data+i, sizeof(Node)*(d->size-i));
    d->data[i] = *new Node(value);
    d->size++;
}

template<class T>
typename VList<T>::iterator VList<T>::insert(iterator before, const T &value)
{
    int i = before - d->data;
    insert(i, value);
    return d->data+i;
}

template<class T>
bool VList<T>::operator==(const VList<T> &other) const
{
    if(d->size != other.d->size) return false;

    for(int i=0; i<d->size; i++)
	if(*d->data[i].v != *other.d->data[i].v)
	    return false;
    return true;
}

template<class T>
void VList<T>::move(int from, int to)
{
    if(from<0 || from>d->size) return;
    if(to<0   || to>d->size)   return;

    Node tmp = d->data[from];
    memmove(d->data+from, d->data+from+1, (to-from)*sizeof(Node));
    d->data[to] = tmp;
}

template<class T>
void VList<T>::replace(int i, const T &value)
{
    if(i<0 || i>d->size) return;
    d->data[i].v = new T(value);
}

template<class T>
void VList<T>::swap(int i, int j)
{
    if(i<0 || i>d->size) return;
    if(j<0 || j>d->size) return;

    Node tmp = d->data[i];
    d->data[i] = d->data[j];
    d->data[j] = tmp;
}

DEFINE_READONLY_ITERATOR_FOR_C(List)
DEFINE_MUTABLE_ITERATOR_FOR_C(List)

#endif
