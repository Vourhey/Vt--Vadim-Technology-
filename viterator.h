#ifndef VITERATOR_H
#define VITERATOR_H

#define DEFINE_READONLY_ITERATOR_FOR_C(C) \
	\
template<class T> \
class V##C##Iterator \
{ \
typedef typename V##C<T>::const_iterator const_it; \
V##C<T> c; \
const_it i; \
public: \
inline V##C##Iterator(const V##C<T> &cl) \
    : c(cl), i(c.constBegin()) {} \
inline bool findNext(const T &value) \
    { while(i!=c.constEnd()) if(*i++ == value) return true; return false;} \
inline bool findPrevious(const T &value) \
    { while(i!=c.constBegin()) if(*--i == value) return true; return false; } \
inline bool hasNext() const { return i != c.constEnd(); } \
inline bool hasPrevious() const { return i != c.constBegin(); } \
inline const T &next() { return *i++; } \
inline const T &peekNext() const { return *i; } \
inline const T &peekPrevious() const { return *(i-1); } \
inline const T &previous() { return *--i; } \
inline void  toBack() { i = c.constEnd(); } \
inline void  toFront() { i = c.constBegin(); } \
inline V##C##Iterator &operator=(const V##C<T> &cl) \
    { c = cl; i = c.constBegin(); return *this; } \
};

#define DEFINE_MUTABLE_ITERATOR_FOR_C(C) \
	\
template<class T> \
class VMutable##C##Iterator \
{ \
typedef typename V##C<T>::iterator iterator; \
V##C<T> *c; \
iterator i, n; \
public:	\
inline VMutable##C##Iterator(V##C<T> &cl) \
    : c(&cl), i(c->begin()), n(c->end()) {} \
inline bool findNext(const T &value) \
    { while((n = i)!=c->end()) if(*i++ == value) return true; return false; } \
inline bool findPrevious(const T &value) \
    { while(i!=c->begin()) if(*(n = --i) == value) return true; return false; } \
inline bool hasNext() const { return i != c->end(); } \
inline bool hasPrevious () const { return i != c->begin(); } \
inline void insert(const T &value) { n = i = c->insert(i, value); ++i; } \
inline T & next() { n = i++; return *n; } \
inline T & peekNext() const { return *i; } \
inline T & peekPrevious() const { return *(i-1); } \
inline T & previous() { n = --i; return *n; } \
inline void remove() { if(i!=c->end()) { i = c->erase(n); n = c->end(); } } \
inline void setValue(const T &value) const { if(n!=c->end()) *n = value; } \
inline void toBack() { i = c->end(); } \
inline void toFront() { i = c->begin(); } \
inline const T &value() const { return *n; }\
inline T & value() { return *n; } \
inline VMutable##C##Iterator &operator=(V##C<T> &cl) \
    { c = &cl; i = c->begin(); n = c->end(); return *this; } \
};

#endif
