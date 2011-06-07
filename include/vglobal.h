#ifndef VGLOBAL_H
#define VGLOBAL_H

#include <stdlib.h>
#include <cstring>

#define VT_VERSION 0x000100
#define VT_VERSION_STR "0.1.0"

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
#define V_UINT64_C(literal) literat ## ULL 

// Compilers
#if defined(__BORLANDC__) || defined(__CODEGEARC__)
# define V_CC_BOR
#elif defined(__COMO__)
# define V_CC_COMEAU
#elif defined(__EDG__)
# define V_CC_EDG
#elif defined(__ghs__)
# define V_CC_GHS
#elif defined(__GNUC__)
# define V_CC_GNU
#elif defined(__HIGHC__)
# define V_CC_HIGHC
#elif defined(__HP_aCC)
# define V_CC_HPACC
#elif defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ECC) || defined(__ICL)
# define V_CC_INTEL
#elif defined(__KCC)
# define V_CC_KAI
#elif defined(__sgi) || defined(sgi)
# define V_CC_MIPS
#elif defined(_MSC_VER)
# define V_CC_MSVC
#elif defined(__MWERKS__)
# define V_CC_MWERKS
#elif defined(__PGI)
# define V_CC_PGI
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
# define V_CC_SUN
#elif defined(__DMC__) || defined(__SC__) || defined(__ZTC__)
# define V_CC_SYM
#elif defined(_SCO_DS)
# define V_CC_USLC
#elif defined(__WATCOMC__)
# define V_CC_WAT
#endif

// Operation Systems
#if defined(_AIX)
# define V_OS_AIX
#elif defined(__bsdi__)
# define V_OS_BSDI
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
# define V_OS_DARWIN
# define V_OS_MAC
#elif defined(DGUX) || defined(__DGUX__) || defined(__dgux__)
# define V_OS_DGUX
#elif defined(_SEQUENT_) || defined(sequent)
# define V_OS_DYNIX
#elif defined(__FreeBSD__)
# define V_OS_FREEBSD
#elif defined(_hpux) || defined(hpux) || defined(__hpux)
# define V_OS_HPUX
#elif defined(__GNU__)
# define V_OS_HURD
#elif defined(sgi) || defined(__sgi)
# define V_OS_IRIX
#elif defined(linux) || defined(__linux)
# define V_OS_LINUX
#elif defined(__Lynx__)
# define V_OS_LYNX
#elif defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
# define V_OS_MSDOS
#elif defined(__NetBSD__)
# define V_OS_NETBSD
#elif defined(OS2) || defined(_OS2) || defined(__OS2__) || defined(__TOS_OS2__)
# define V_OS_OS2
#elif defined(__OpenBSD__)
# define V_OS_OPENBSD
#elif defined(__osf__) || defined(__osf)
# define V_OS_OSF
#elif defined(__QNX__) || defined(__QNXNTO__)
# define V_OS_QNX
#elif defined(sinux)
# define V_OS_RELIANT
#elif defined(M_I386) || defined(M_XENIX) || defined(_SCO_DS)
# define V_OS_SCO
#elif defined(sun) || defined(__sun)
# define V_OS_SOLARIS
#elif defined(__SYMBIAN32__)
# define V_OS_SYMBIAN
#elif defined(__unix__) || defined(__unix)
# define V_OS_UNIX
#elif defined(sco) || defined(_UNIXWARE7)
# define V_OS_UNIXWARE
#elif defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
# define V_OS_WIN32
# if defined(_WIN64)
#  define V_OS_WIN64
# endif
#elif defined(_WIN32_WCE)
# define V_OS_WINCE
#endif

// Window systems
#if defined(V_OS_WIN32)
# define V_WS_WIN
#elif defined(V_OS_MAC)
# define V_WS_MAC
#else
# define V_WS_X11
#endif

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
{ if(value<0.0) return vint64(value-0.5); return vint64(value+0.5); }
inline int vRound(vreal value)
{ if(value<0.0) return int(value-0.5); return int(value+0.5); }

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

#define V_DECLARE_FLAGS(Flags,Enum) typedef VFlags<Enum> Flags;
#define V_DECLARE_OPERATORS_FOR_FLAGS(Flags) \
inline VFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) \
{ return VFlags<Flags::enum_type>(f1) | f2; } \
inline VFlags<Flags::enum_type> operator|(Flags::enum_type f1, VFlags<Flags::enum_type> f2) \
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
if(!(p)) vWarning("В файле %s, в строке %d: Недействительный указатель", __FILE__, __LINE__)

template<class T> inline T *v_check_ptr(T *p) { V_CHECK_PTR(p); return p; }

#define V_UNUSED(name) (void)name;
// работает только на GCC
#define V_FUNC_INFO __PRETTY_FUNCTION__

// новые ключевые слова
#define V_FOREVER for(;;)
#define forever for(;;)

#include "namespace.h"

#endif
