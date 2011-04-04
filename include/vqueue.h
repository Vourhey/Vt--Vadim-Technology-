#ifndef VQUEUE_H
#define VQUEUE_H

#include "vlist.h"

template<class T>
class VQueue : public VList<T>
{
public:
    inline VQueue() {}
    inline ~VQueue() {}

    T dequeue() { return VList<T>::takeFirst(); }
    void enqueue(const T &t) { VList<T>::append(t); }
    T &head() { return VList<T>::first(); }
    const T &head() const { return VList<T>::first(); }
};

#endif
