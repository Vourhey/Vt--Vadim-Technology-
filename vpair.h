#ifndef VPAIR_H
#define VPAIR_H

template<class T1, class T2>
class VPair
{
public:
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;
   
    VPair() : first(T1()), second(T2()) {}
    VPair(const T1 &value1, const T2 &value2)
	: first(value1), second(value2) {}

    VPair<T1, T2> &operator=(const VPair<T1, T2> &other)
	{ first = other.first; second = other.second; return *this; }

    friend VPair<T1, T2> vMakePair(const T1 &value1, const T2 &value2)
	{ return VPair<T1, T2>(value1, value2); }
    friend bool operator==(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
	{ return (p1.first == p2.first) && (p1.second == p2.second); }
    friend bool operator!=(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
	{ return !operator==(p1, p2); }
    friend bool operator<(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
	{ return (p1.first < p2.first) && (p1.second < p2.second); }
    friend bool operator<=(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
	{ return !(p2 < p1); }
    friend bool operator>(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
	{ return p2 < p1; }
    friend bool operator>=(const VPair<T1, T2> &p1, const VPair<T1, T2> &p2)
	{ return !(p1 < p2); }
};

#endif
