#ifndef VTALGORITHMS_H
#define VTALGORITHMS_H

#include "vglobal.h"

template<class RandomAccessIterator, class T>
RandomAccessIterator vBinaryFind(RandomAccessIterator begin,
				 RandomAccessIterator end, const T &value)
{
    RandomAccessIterator it;
    forever
    {
	it = begin + int(int(end - begin) / 2);
	if(*it > value)
	    begin = it + 1;
	else if(*it < value)
	    end = it - 1;
	else
	    return it;
	if(begin > end) break;
    }
    return it;
}

template<class Container, class T>
typename Container::const_iterator vBinaryFind(const Container &container, const T &value)
{
    return vBinaryFind(container.begin(), container.end(), value);
}

/*
template<class RandomAccessIterator, class T, class LessThan>
RandomAccessIterator vBinaryFind(RandomAccessIterator begin,
				 RadnomAccessIterator end,
				 const T &value, LessThan lessThan)
{
} */

template<class OutputIterator, class InputIterator>
OutputIterator vCopy(InputIterator begin1, InputIterator end1, OutputIterator begin2)
{
    while(begin1 != end1)
    {
	*begin2 = *begin1;
	++begin1;
	++begin2;
    }
    return begin2;
}

template<class InputIterator, class T, class Size>
void vCount(InputIterator begin, InputIterator end, const T &value, Size &n)
{
    while(begin != end)
    {
	if(*begin == value)
	    ++n;
    }
}

template<class Container, class T, class Size>
void vCount(const Container &container, const T &value, Size &n)
{
    vCount(container.constBegin(), container.constEnd(), value, n);
}

template<class ForwardIterator>
void vDeleteAll(ForwardIterator begin, ForwardIterator end)
{
    while(begin != end)
    {
	delete *begin;
	++begin;
    }
}

template<class Container>
void vDeleteAll(const Container &c)
{
    vDeleteAll(c.constBegin(), c.constEnd());
}

template<class ForwardIterator, class T>
void vFill(ForwardIterator begin, ForwardIterator end, const T &value)
{
    while(begin != end)
    {
	*begin = value;
	++begin;
    }
}

template<class Container, class T>
void vFill(Container &container, const T &value)
{
    vFill(container.begin(), container.end(), value);
}

template<class InputIterator, class T>
InputIterator vFind(InputIterator begin, InputIterator end, const T &value)
{
    while(begin != end)
    {
	if(*begin == value)
	    return begin;
	++begin;
    }
    return end;
}

template<class Container, class T>
typename Container::const_iterator vFind(const Container &container, const T &value)
{
    return vFind(container.begin(), container.end(), value);
}

template<class InputIterator1, class InputIterator2>
bool vEqual(InputIterator1 begin1, InputIterator1 end1, InputIterator2 begin2)
{
    while(begin1 != end1)
    {
	if(*begin1 != *begin2) return false;
	++begin1;
	++begin2;
    }
    return true;
}

template<class T>
class vGreater
{
public:
    inline bool operator()(const T &t1, const T &t2) const
	{ return (t1 > t2); }
};

template<class T>
class vLess
{
public:
    inline bool operator()(const T &t1, const T &t2) const
	{ return (t1 < t2); }
};

template<class RandomAccessIterator, class LessThan>
void vSort(RandomAccessIterator begin, RandomAccessIterator end, LessThan lessThan)
{
    RandomAccessIterator temp;
    RandomAccessIterator it = int(end - begin) / 2;

    do
    {
	while(lessThan(*begin, *it)) ++begin;
	while(lessThan(*end, *it))   --end;

	if(begin <= end)
	{
	    temp = *begin;
	    *begin = *end;
	    *end = temp;

	    ++begin;
	    --end;
	}
    } while(begin <= end);

    if(end > 0) vSort(begin, end);
    if(end > begin) vSort(begin, end-begin);
}

template<class T>
void vSwap(T &t1, T &t2)
{
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}

#endif
