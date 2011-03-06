#ifndef VVECTOR_H
#define VVECTOR_H

#include <iostream>
#include "vglobal.h"
#include "viterator.h"

template<class T>
class VVector
{
public:
    // for STL compatibility
    typedef const T* const_pointer;
    typedef const T& const_reference;
    typedef T*       pointer;
    typedef T&       reference;
    typedef int      size_type;
    typedef T        value_type;
    typedef const T* const_iterator;
    typedef T*       iterator;
    // and Vt...
    typedef const_iterator ConstIterator;
    typedef iterator       Iterator;

    VVector();
    VVector(int size);
    VVector(int size, const T &value);
    VVector(const VVector<T> &other);
    ~VVector();

    void append(const T &value);
    const T &at(int i) const
    {
	if(i>0 && i<d->size) return d->data[i];
	return T(); // возвращаем значение по-умолчанию
    }
    void clear()
    {
	free(d);
	d = 0;
    }

    bool contains(const T &value) const;
    int count(const T &value) const;
    int count() const { return d->size; }
    const T *constData() const { return d->data; }
    int capacity() const { return d->alloc; }

    T *data() { return d->data; }
    const T *data() const { return d->data; }

    bool empty() const { return !d->size; }
    bool endsWith(const T &value) const
        { return (d->data[d->size-1] == value); }

    VVector<T> &fill(const T &value, int size = -1);
    T &first() { return d->data[0]; }
    const T &first() const { return at(0); }

    int indexOf(const T &value, int from = 0) const;
    void insert(int i, const T &value);
    void insert(int i, int count, const T &value);
    bool isEmpty() const { return !d->size; }

    T &last() { return d->data[d->size-1]; }
    const T &last() const { return at(d->size-1); }
    int lastIndexOf(const T &value, int from = -1) const;

    VVector<T> mid(int pos, int length = -1) const;
    void prepend(const T &value);

    void remove(int i);
    void remove(int i, int count);
    void replace(int i, const T &value)
	{ d->data[i] = value; }
    void reserve(int size)
	{ reallocData(size); }
    void resize(int size)
	{ reallocData(size); }

    int size() const { return d->size; }
    bool startsWith(const T &value) const
	{ return (d->data[0] == value); }

    T value(int i) const { return value(i, T()); }
    T value(int i, const T &defaultValue) const
	{ if(i>-1 && i<d->size) return d->data[i]; return defaultValue;}

    // for STL
    reference back() { return d->data[d->size-1]; }
    const_reference back() const { return at(d->size-1); }

    iterator begin() { return d->data; }
    const_iterator begin() const { return d->data; }

    const_iterator constBegin() const { return d->data; }
    const_iterator constEnd() const   { return d->data+d->size; }

    iterator end() { return d->data+d->size; }
    const_iterator end() const { return d->data+d->size; }

    iterator erase(iterator pos) { return erase(pos, pos+1); }
    iterator erase(iterator begin, iterator end);

    T &front() { return d->data[0]; }
    const_reference front() const { return at(0); }

    iterator insert(iterator before, const T &value) 
	{ return insert(before, 1, value); }
    iterator insert(iterator before, int count, const T &value);

    void pop_back() { erase(d->data+d->size-1); }
    void pop_front() { erase(d->data); }
    void push_back(const T &value) { append(value); }
    void push_front(const T &value) { prepend(value); }

    // operators
    bool operator!=(const VVector<T> &other) const
	{ return !operator==(other); }
    bool operator==(const VVector<T> &other) const;
    T &operator[](int i) { return value(i, T()); }
    const T &operator[](int i) const { return at(i); }
    VVector<T> operator+(const VVector<T> &other) const
	{ VVector<T> ret = *this; ret += other; return ret; }
    VVector<T> &operator+=(const VVector<T> &other);
    VVector<T> &operator+=(const T &value)
	{ append(value); return *this; }
    VVector<T> &operator<<(const T &value)
	{ append(value); return *this; }
    VVector<T> &operator<<(const VVector<T> &other)
	{ return operator+=(other); }
    friend std::ostream &operator<<(std::ostream &os, const VVector<T> &vec)
    {
	for(int i=0; i<vec.d->size; i++)
	    os << vec.d->data[i] << ' ';
	return os;
    }

private:
    void reallocData(int nsize);
    struct VVectorData
    {
	int size;
	int alloc;
	T *data;
	T array[1];
    };
    typedef VVectorData Data;
    Data *d;
};

template<class T>
void VVector<T>::reallocData(int nsize)
{
    if(!d) // ещё не выделяли память
    {
	d = (Data*)malloc(sizeof(Data)+nsize*sizeof(T));
	d->data = d->array;
	d->size = d->alloc = nsize;
    }
    else if(nsize <= d->alloc)
    {
	d->size = nsize;
    }
    else // nsize > d->alloc; нужно больше памяти
    {
	Data *x = (Data*)malloc(sizeof(Data)+nsize*sizeof(T));
	x->data = x->array;
	x->size = x->alloc = nsize;

	::memcpy(x->data, d->data, d->size*sizeof(T));
	free(d);
	d = x;
    }
}

template<class T>
VVector<T>::VVector()
{
    d = 0;
    reallocData(0);
}

template<class T>
VVector<T>::VVector(int size)
{
    if(size < 0) size = 0;
    d = 0;
    reallocData(size);

    for(int i=0; i<size; i++) 
	d->data[i] = T(); // default-value
}

template<class T>
VVector<T>::VVector(int size, const T &value)
{
    if(size < 0) size = 0;
    d = 0;
    reallocData(size);

    for(int i=0; i<size; i++)
	d->data[i] = value;
}

template<class T>
VVector<T>::VVector(const VVector<T> &other)
{
    d = 0;
    reallocData(other.d->size);

    // copy
    for(int i=0; i<d->size; i++)
	d->data[i] = other.d->data[i];
}

template<class T>
VVector<T>::~VVector()
{
    free(d);
    d = 0;
}

template<class T>
void VVector<T>::append(const T &value)
{
    reallocData(d->size+1);
    d->data[d->size-1] = value;
}

template<class T>
bool VVector<T>::contains(const T &value) const
{
    for(int i=0; i<d->size; i++)
	if(d->data[i] == value)
	    return true;
    return false;
}

template<class T>
int VVector<T>::count(const T &value) const
{
    int c = 0;
    for(int i=0; i<d->size; i++)
	if(d->data[i] == value)
	    c++;
    return c;
}

template<class T>
VVector<T> &VVector<T>::fill(const T &value, int size)
{
    if(size == -1) size = d->size;
    reallocData(size);

    for(int i=0; i<size; i++)
	d->data[i] = value;

    return *this;
}

template<class T>
int VVector<T>::indexOf(const T &value, int from) const
{
    for(int i = from; i<d->size; i++)
	if(d->data[i] == value)
	    return i;
    return -1;
}

template<class T>
void VVector<T>::insert(int i, const T &value)
{
    reallocData(d->size+1);
    ::memmove(d->data+i, d->data+i-1, (d->size - i)*sizeof(T));
    d->data[i-1] = value;
}

template<class T>
void VVector<T>::insert(int i, int count, const T &value)
{
    if(count < 1) count = 1;
    reallocData(d->size+count);
    ::memmove(d->data+i+count-1, d->data+i-1, (d->size-i)*sizeof(T));
    
    int j = i-1;
    while(count--) d->data[j++] = value;
}

template<class T>
int VVector<T>::lastIndexOf(const T &value, int from) const
{
    if(from == -1) from = d->size - 1;
    for(int i=from; i>=0; i--)
	if(d->data[i] == value)
	    return i;
    return -1;
}

template<class T>
VVector<T> VVector<T>::mid(int pos, int length) const
{
    int len = length == -1 ? d->size - pos : length;
    VVector<T> ret(len);

    for(int i=0; i<length && pos<d->size; i++)
	ret.d->data[i] = d->data[pos];

    return ret;
}

template<class T>
void VVector<T>::prepend(const T &value)
{
    reallocData(d->size+1);
    ::memmove(d->data+1, d->data, sizeof(T));
    d->data[0] = value;
}

template<class T>
void VVector<T>::remove(int i)
{
    ::memmove(d->data+i, d->data+i+1, sizeof(T));
    reallocData(d->size-1);
}

template<class T>
void VVector<T>::remove(int i, int count)
{
    ::memmove(d->data+i, d->data+i+count, sizeof(T)*count);
    reallocData(d->size-count);
}

template<class T>
bool VVector<T>::operator==(const VVector<T> &other) const
{
    for(int i=0; i<d->size; i++)
	if(d->data[i] != other.d->data[i])
	    return false;
    return true;
}

template<class T>
VVector<T> &VVector<T>::operator+=(const VVector<T> &other)
{
    reserve(d->size+other.d->size); // optimization
    for(int i=0; i<other.d->size; i++)
	append(other.d->data[i]);
    return *this;
}

template<class T>
typename VVector<T>::iterator VVector<T>::erase(iterator begin, iterator end)
{
    int b = int(begin - d->data);
    int e = int(end - d->data);
    int n = e - b;

    ::memmove(d->data+b, d->data+e, sizeof(T)*(d->size - e));
    reallocData(d->size - n);
    return d->data+b;
}

template<class T>
typename VVector<T>::iterator VVector<T>::insert(iterator before, int count, const T &value)
{
    int b = int(before - d->data);
    insert(b, count, value);
    return d->data+b;
}

DEFINE_READONLY_ITERATOR_FOR_C(Vector)
DEFINE_MUTABLE_ITERATOR_FOR_C(Vector)

#endif
