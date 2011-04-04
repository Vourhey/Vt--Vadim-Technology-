#ifndef VGLOBAL_H
#define VGLOBAL_H

#include <stdlib.h>
#include <cstring>

#define VT_VERSION 0x000001
#define VT_VERSION_STR "0.0.1"

inline const char *vVersion() { return VT_VERSION_STR; }

typedef signed char            vint8;
typedef signed short           vint16;
typedef signed int             vint32;
typedef long long int          vint64;
typedef long long int          vlonglong;
typedef double                 vreal;
typedef unsigned char          vuint8;
typedef unsigned short         vuint16;
typedef unsigned int           vuint32;
typedef unsigned long long int vuint64;
typedef unsigned long long int vulonglong;
typedef unsigned char          uchar;
typedef unsigned int           uint;
typedef unsigned long          ulong;
typedef unsigned short         ushort;

#define V_INT64_C(literal) literal ## LL
#define V_UINT64_C(literal) literat ## UL 

/*! \cond */
// служенбный класс. Размер целого
template<int> struct VIntegerSize {};
template<> struct VIntegerSize<4> { typedef vint32 Signed; typedef vuint32 Unsigned; };
template<> struct VIntegerSize<8> { typedef vint64 Signed; typedef vuint64 Unsigned; };
/*! \endcond */

typedef VIntegerSize<sizeof(void*)>::Signed   vptrdiff;
typedef VIntegerSize<sizeof(void*)>::Unsigned vuintptr;

template<class T> T vAbs(const T &value) { return value<0 ? -value : value; }
template<class T> const T &vMax(const T &value1, const T &value2)
{ if(value1 > value2) return value1; return value2; }
template<class T> const T &vMin(const T &value1, const T &value2)
{ if(value1 < value2) return value1; return value2; }
template<class T> const T &vBound(const T &min, const T &value, const T &max)
{ return vMax(min, vMin(value, max)); }

inline vint64 vRound64(vreal value)
{ if(value<0) return vint64(value-0.5); return vint64(value+0.5); }
inline int vRound(vreal value)
{ if(value<0) return int(value-0.5); return int(value+0.5); }

// класс для OR комбинаций
template<class Enum>
class VFlags
{
    int i;

public:
    typedef Enum enum_type;

    inline VFlags(const VFlags &other) : i(other.i) {}
    inline VFlags(Enum flag) : i(flag) {}
    inline VFlags() : i(0) {}
    inline VFlags(int value) : i(value) {}

    inline bool testFlag(Enum flag) const { return (i & flag); }

    inline operator int() const { return i; }
    inline bool operator!() const { return !i; }
    inline VFlags &operator=(const VFlags &other) { i = other.i; return *this; }

    inline VFlags operator&(int mask) const { return VFlags(i & mask); }
    inline VFlags operator&(uint mask) const { return VFlags(i & mask); }
    inline VFlags operator&(Enum mask) const { return VFlags(i & mask); }

    inline VFlags &operator&=(int mask) { i &= mask; return *this; }
    inline VFlags &operator&=(uint mask) { i &= mask; return *this; }

    inline VFlags operator^(VFlags other) const { return VFlags(i ^ other.i); }
    inline VFlags operator^(Enum flag) const { return VFlags(i ^ flag); }

    inline VFlags &operator^=(VFlags other) { i ^= other.i; return *this; }
    inline VFlags &operator^=(Enum flag) { i ^= flag; return *this; }

    inline VFlags operator|(VFlags other) const { return VFlags(i | other.i); }
    inline VFlags operator|(Enum flag) const { return VFlags(i | flag); }

    inline VFlags &operator|=(VFlags other) { i |= other.i; return *this; }
    inline VFlags &operator|=(Enum flag) { i |= flag; return *this; }

    inline VFlags operator~() const { return VFlags(~i); }
};

#define V_DECLARE_FLAGS(Flags, Enum) typedef VFlags<Enum> Flags;
#define V_DECLARE_OPERATORS_FOR_FLAGS(Flags) \
inline VFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) \
{ return VFlags<Flags::enum_type>(f1) | f2; } \
inline VFlags<Flags::enum_type> operator|(Flags::enum_type f1, VFlags<FLags::enum_type> f2) \
{ return f2 | f1; }

// Debug output
void vCritical(const char *msg, ... );
void vDebug(const char *msg, ... );
void vFatal(const char *msg, ... );
void vWarning(const char *msg, ... );

#define V_ASSERT(test) \
if(!(test)) vFatal("ASSERT: \"%s\" в файле %s, в строке %d", #test, __FILE__, __LINE__)
#define V_ASSERT_X(test, where, what) \
if(!(test)) vFatal("ASSERT в %s: \"%s\", в файле %s, в строке %d", where, what, __FILE__, __LINE__) 
#define V_CHECK_PTR(p) \
if(!(p)) vWarning("В файле %s, в строке %d: Не хватает памяти", __FILE__, __LINE__)

template<class T> inline T *v_check_ptr(T *p) { V_CHECK_PTR(p); return p; }

#define V_UNUSED(name) (void)name;
// работает только на GCC
#define V_FUNC_INFO __PRETTY_FUNCTION__

// новые ключевые слова
#define V_FOREVER for(;;)
#define forever for(;;)

#endif
