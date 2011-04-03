#ifndef VQUEUE_H
#define VQUEUE_H

#include "vlist.h"

template<class T>
class VQueue : public VList<T>
{
public:
    inline VQueue() {}
    inline ~VQueue() {}

    T dequeue() { return takeFirst(); }
    void enqueue(const T &t) { append(t); }
    T &head() { return first(); }
    const T &head() const { return first(); }
};

#endif
