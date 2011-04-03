#ifndef VSTACK_H
#define VSTACK_H

#include "vvector.h"

template<class T>
class VStack : public VVector<T>
{
public:
    VStack() {}
    ~VStack() {}
    T pop() 
    { 
	T ret = VVector<T>::last(); 
	VVector<T>::remove(VVector<T>::size()-1); 
	return ret; 
    }
    void push(const T &t) { VVector<T>::append(t); }
    T &top() { return VVector<T>::last(); }
    const T &top() const { return VVector<T>::last(); }
};

#endif
