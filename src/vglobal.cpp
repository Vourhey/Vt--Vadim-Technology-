#include "vglobal.h"
#include <cstdio>
#include <cstdarg>

/*!
 * \class VFlags
 * \brief Реализует безопасный способ управления значениями объединений (enum)
 *
 * VFlags<Enum> - шаблонный класс, где \c Enum - тип объединения. VFlags
 * используется для хранения комбинаций значений перечисления. 
 *
 * При традиционном программировании на C++ значения объединений хранятся
 * в переменных типа \c int или \c uint. Недостаток такого способа является то,
 * что нет проверки на комбинируемые значения. Любое значение можно пересечь
 * с другим объединением.
 *
 * Если вы хотите использовать VFlags для своих объединений, то используйте
 * #V_DECLARE_FLAGS() и #V_DECLARE_OPERATORS_FOR_FLAGS(). Пример:
 * \code
 * class MyClass
 * {
 * public:
 *     enum Option
 *     {
 *         NoOptions = 0x0,
 *         ShowTabs  = 0x1,
 *         ShowAll   = 0x2,
 *         Other     = 0x4
 *     };
 *     V_DECLARE_FLAGS(Options, Option)
 *     ...
 * };
 *
 * V_DECLARE_OPERATORS_FOR_FLAGS(MyClass::Options)
 * \endcode
 * Вы можете использовать MyClass::Options для хранения значений MyClass::Option.
 */
/*!
 * \typedef Enum VFlags::enum_type
 * Синоним для Enum.
 */
/*!
 * \fn VFlags::VFlags()
 * Создает пустой объект.
 */
/*!
 * \fn VFlags::VFlags(const VFlags &other)
 * Конструктор копий
 */
/*!
 * \fn VFlags::VFlags(Enum flag)
 * Создает VFlags и присваивает ему \a flag.
 */
/*!
 * \fn VFlags::VFlags(int value)
 * Создает VFlags и присваивает ему \a value.
 */
/*!
 * \fn bool VFlags::testFlag(Enum flag) const
 * Возвращает \c true, если \a flag установлен.
 * Иначе \c false.
 */
/*!
 * \fn VFlags::operator int() const
 * Возвращает значение объекта, как целое.
 */
/*!
 * \fn bool VFlags::operator!() const
 * Возвращает \c true, если флаг установлен (т.е. если
 * VFlags хранит не нулевое значение). Иначе \c false.
 */
/*!
 * \fn VFlags VFlags::operator&(int mask) const
 * Возвращает VFlags, содержащий результат побитового
 * AND между этим объектом и \a mask.
 * \see operator&=(), operator|(), operator^() и operator~()
 */
/*!
 * \fn VFlags VFlags::operator&(uint mask) const
 * \overload
 */
/*!
 * \fn VFlags VFlags::operator&(Enum mask) const
 * \overload
 */
/*!
 * \fn VFlags &VFlags::operator&=(int mask)
 * Выполняет побитовую операцию AND между этим объектом
 * и \a mask. Результат сохраняется в этом объекте.
 * Функция возвращает ссылку на этот объект.
 * \see operator&(), operator|=() и operator^=()
 */
/*!
 * \fn VFlags &VFlags::operator&=(uint mask)
 * \overload
 */
/*!
 * \fn VFlags &VFlags::operator=(const VFlags &other)
 * Назначает этому объекту значение \a other. 
 * Возвращает ссылку на этот объект.
 */
/*!
 * \fn VFlags VFlags::operator^(VFlags other) const
 * Возвращает VFlags, содержащий результат побитового XOR между
 * этим объектом и \a other.
 * \see operator^=(), operator&(), operator|() и operator~()
 */
/*!
 * \fn VFlags VFlags::operator^(Enum other) const
 * \overload
 */
/*!
 * \fn VFlags &VFlags::operator^=(VFlags other)
 * Выполняет операцию побитового XOR между этим объектом и
 * \a other. Возвращает ссылку на этот объект.
 * \see operator^(), operator&=() и operator|=()
 */
/*!
 * \fn VFlags &VFlags::operator^=(Enum other)
 * \overload
 */
/*!
 * \fn VFlags VFlags::operator|(VFlags other) const
 * Возвращает VFlags, содержащий результат побитового OR
 * между этим объектом и \a other.
 * \see operator|=(), operator^(), operator&() и operator~()
 */
/*!
 * \fn VFlags VFlags::operator|(Enum other) const
 * \overload
 */
/*!
 * \fn VFlags &VFlags::operator|=(VFlags other)
 * Выполняет операцию побитового OR между этим объектом и
 * \a other. Возвращает ссылку на этот объект.
 * \see operator|(), operator&=() и operator^=()
 */
/*!
 * \fn VFlags &VFlags::operator|=(Enum other)
 * \overload
 */
/*!
 * \fn VFlags VFlags::operator~() const
 * Возвращает VFlags, содержащий результат побитового
 * отрицания этого объекта.
 * \see operator&(), operator|() и operator^()
 */
/*!
 * \fn V_DECLARE_FLAGS(Flags,Enum)
 * \relates VFlags
 * Расширяется в
 * \code
 * typedef VFlags<Enum> Flags;
 * \endcode
 * \a Enum - имя существующего типа объединения.
 * \a Flags - синоним для VFlags<Enum>.
 * \see V_DECLARE_OPERATORS_FOR_FLAGS()
 */
/*!
 * \fn V_DECLARE_OPERATORS_FOR_FLAGS(Flags)
 * \relates VFlags
 * Объявляет глобальные операторы operator|() для \a Flags.
 * \see V_DECLARE_FLAGS()
 */

/*!
 * \defgroup global_group Глобальные определения
 * \{
 */

/*!
 * \typedef vint8
 * Синоним для <tt>signed char</tt>.
 */
/*!
 * \typedef vint16
 * Синоним для <tt>signed short</tt>.
 */
/*!
 * \typedef vint32
 * Синоним для <tt>signed int</tt>.
 */
/*!
 * \typedef vint64
 * Синоним для <tt>long long int</tt>. Литерал этого типа
 * можно получить с помощью V_INT64_C():
 * \code
 * vint64 value = V_INT64_C(2147483647);
 * \endcode
 * \see V_INT64_C(), vuint64 и vlonglong
 */
/*!
 * \typedef vlonglong
 * Синоним для <tt>long long int</tt>.
 * \see vulonglong и vint64
 */
/*!
 * \typedef vptrdiff
 * Представляет тип целого. На 32-битных платформах это равносильно
 * vint32. На 64-битных равносильно vint64.
 * \see vuintptr, vint32 и vint64
 */
/*!
 * \typedef vreal
 * Синоним для double.
 */
/*!
 * \typedef vuint8
 * Синоним для <tt>unsigned char</tt>.
 */
/*!
 * \typedef vuint16
 * Синоним для <tt>unsigned short</tt>.
 */
/*!
 * \typedef vuint32
 * Синоним для <tt>unsigned int</tt>.
 */
/*!
 * \typedef vuint64
 * Синоним для <tt>unsigned long long int</tt>. Литерал этого типа
 * можно получить с помощью V_UINT64_C():
 * \code
 * vuint64 value = V_UINT64_C(932838457459459);
 * \endcode
 * \see V_UINT64_C(), vint64 и vulonglong
 */
/*!
 * \typedef vuintptr
 * Синоним для беззнакового целого. На 32-битных платформах
 * это равносильно vuint32. На 64-битных платформа равносильно vuint64.
 * \see vptrdiff, vuint32 и vuint64
 */
/*!
 * \typedef vulonglong
 * Синоним для <tt> unsigned long long int</tt>. Равносильно vuint64.
 * \see vuint64 и vlonglong
 */
/*!
 * \typedef uchar
 * Удобный синоним для <tt>unsigned char</tt>.
 */
/*!
 * \typedef uint
 * Удобный синоним для <tt>unsigned int</tt>.
 */
/*!
 * \typedef ulong
 * Удобный синоним для <tt>unsigned long</tt>.
 */
/*!
 * \typedef ushort
 * Удобный синоним для <tt>unsigned short</tt>.
 */

/*!
 * \def VT_VERSION
 * Макрос, расширяющийся в челочисленное значение вида 0xMMNNPP, равное номеру версии. 
 * Например, для первой версии (v0.1.0) макрсо будет представлять 0x000100.
 * \see vVersion()
 */
/*!
 * \def VT_VERSION_STR
 * Представляет строковую константу, равную номеру версии (например, "0.1.0")
 * \see vVersion() и VT_VERSION
 */
/*!
 * \fn vVersion()
 * Возвращает версию библиотеки в виде строковой константы.
 * \see VT_VERSION_STR
 */
/*!
 * \def V_INT64_C(literal)
 * Возвращает целое 64-х битное со знаком. Напримре:
 * \code
 *  vint64 value = V_INT64_C(932838457459459);
 * \endcode
 * \see vint64 и V_UINT64_C()
 */
/*!
 * \def V_UINT64_C(literal)
 * Возвращает целое 64-х битное беззнаковое число. Например:
 * \code
 *  vuint64 value = V_UINT64_C(932838457459459);
 * \endcode
 * \see vuint64 и V_INT64_C()
 */
/*!
 * \fn T vAbs(const T &value)
 * Сравнивает \a value с нулем и возвращает абсолютное значение. Например:
 * \code
 * int absoluteValue;
 * int myValue = -4;
 *
 * absoluteValue = vAbs(myValue);
 * // absoluteValue == 4
 * \endcode
 */
/*!
 * \fn const T &vMax(const T &value1, const T &value2)
 * Возвращает максимальное из двух значений \a value1 и \a value2. Например:
 * \code
 * int myValue = 6;
 * int yourValue = 4;
 * 
 * int maxValue = vMax(myValue, yourValue);
 * // maxValue == myValue
 * \endcode
 * \see vMin() и vBound()
 */
/*!
 * \fn const T &vMin(const T &value1, const T &value2)
 * Возвращает меньшее из двух значений \a value1 и \a value2. Например:
 * \code
 * int myValue = 6;
 * int yourValue = 4;
 *
 * int minValue = vMin(myValue, yourValue);
 * // minValue == yourValue
 * \endcode
 * \see vMax() и vBound()
 */
/*!
 * \fn const T &vBound(const T &min, const T &value, const T &max)
 * Возвращает среднее из трех значений. Это равносильно vMax(\a min, vMin(\a value, \a max)). Пример:
 * \code
 * int myValue = 10;
 * int minValue = 2;
 * int maxValue = 6;
 *
 * int boundedValue = vBound(minValue, myValue, maxValue);
 * // boundedValue == 6
 * \endcode
 * \see vMin() и vMax()
 */
/*!
 * \fn int vRound(vreal value)
 * Округляет \a value до ближайшего целого. Пример:
 * \code
 * vreal valueA = 2.3;
 * vreal valueB = 2.7;
 *
 * int roundedA = vRound(valueA);
 * // roundedA == 2
 * int roundedB = vRound(valueB);
 * // roundedB == 3
 * \endcode
 */
/*!
 * \fn vint64 vRound64(vreal value)
 * Округляет \a value до ближайщего 64-х битного целого. Пример:
 * \code
 * vreal valueA = 42949672960.3;
 * vreal valueB = 42949672960.7;
 *
 * vint64 roundedValueA = vRound64(valueA);
 * // roundedValueA == 42949672960
 * vint64 roundedValueB = vRound64(valueB);
 * // roundedValueB == 42949672961
 * \endcode
 */

/*!
 * Печатает критическое сообщение об ошибке на стандартный
 * поток ошибок (stderr). Аргументы функции такие же как
 * у стандратной C-функции printf().
 * \code
 * char *filename = "myfile";
 * FILE *file = fopen(filename, "r");
 * if(file == NULL)
 *     vCritical("File %s not open", filename);
 * \endcode
 * \see vDebug(), vWarning() и vFatal()
 */
void vCritical(const char *msg, ... )
{
    va_list format;
    va_start(format, msg);
    fprintf(stderr, "Critical: ");
    vfprintf(stderr, msg, format);
    fprintf(stderr, "\n");
    va_end(format);
}

/*!
 * Печатает сообщение об ошибке на стандратный поток
 * ошибок (stderr) и завершает выполнение программы.
 * Функция принимает аргументы, аналогичные printf().
 * \code
 * int divide(int a, int b)
 * {
 *     if(b == 0)
 *         vFatal("divide: cannot divide by zero");
 *     return a / b;
 * }
 * \endcode
 * \see vDebug(), vCritical() и vWarning()
 */
void vFatal(const char *msg, ... )
{
    va_list format;
    va_start(format, msg);
    fprintf(stderr, "Fatal: ");
    vfprintf(stderr, msg, format);
    fprintf(stderr, "\n");
    va_end(format);
    abort(); // прекращаем выполнение программы
}

/*!
 * Печатает предупреждающее сообщение \a msg на стандартный
 * поток ошибок (stderr). Функция принимает аргументы, аналогичные
 * printf().\n Пример:
 * \code
 * void f(int c)
 * {
 *     if( c > 200 )
 *         vWarning("f: bad argument, c == %d", c);
 * }
 * \endcode
 * \see vDebug(), vCritical() и vFatal()
 */
void vWarning(const char *msg, ... )
{
    va_list format;
    va_start(format, msg);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, msg, format);
    fprintf(stderr, "\n");
    va_end(format);
}

/*!
 * Выводит отладочную информацию \a msg на стандартный
 * поток ошибок (stderr). Функция принимает аргументы,
 * аналогичные printf().
 * \code
 * vDebug("Items in list: %d", myList.size());
 * \endcode
 * \see vWarning(), vCritical() и vFatal()
 */
void vDebug(const char *msg, ... )
{
    va_list format;
    va_start(format, msg);
    fprintf(stderr, "Debug: ");
    vfprintf(stderr, msg, format);
    fprintf(stderr, "\n");
    va_end(format);
}

/*!
 * \def V_ASSERT(test)
 * Печатает предупреждающее сообщение, содержащее \a test, 
 * имя файла и номер строки, если \a test не прошел (равен \c false).
 * \code
 * // File: dev.cpp
 *
 * #include <VtGlobal>
 *
 * int divide(int a, int b)
 * {
 *     V_ASSERT(b != 0);
 *     return a / b;
 * }
 * \endcode
 * Если b равно нулю, то V_ASSERT выведет слудующее сообщение, используя vFatal():
 * \code
 * ASSERT: "b != 0" в файле div.cpp, в строке 7
 * \endcode
 * \see V_ASSERT_X(), vFatal()
 */
/*!
 * \def V_ASSERT_X(test, where, what)
 * Печатает сообщение \a what вместе с расположением \a where, имя файла
 * и номер строки, если \a test равен \c false.
 * \code
 * // File: div.cpp
 *
 * #include <VtGlobal>
 *
 * int divide(int a, int b)
 * {
 *     V_ASSERT_X(b != 0, "divide", "деление на ноль");
 *     return a / b;
 * }
 * \endcode
 * Если b равно нулю, то V_ASSERT_X выведет следующее сообщение с помощью vFatal():
 * \code
 * ASSERT в divide: "деление на ноль", в файле div.cpp, в строке 7
 * \endcode
 * \see V_ASSERT() и vFatal()
 */
/*!
 * \def V_CHECK_PTR(p)
 * Если \a p равен 0, печатает предупреждающее сообщение, содержащее
 * имя исходного файла и номер строки. Пример:
 * \code
 * int *a;
 *
 * V_CHECK_PTR(a = new int[70]); // ошбика!
 * 
 * a = new (nothrow) int[70];    // правильно
 * V_CHECK_PTR(a);
 * \endcode
 * \see vWarning()
 */
/*!
 * \fn T *v_check_ptr(T *p)
 * Встраиваемая версия V_CHECK_PTR. Возвращает \a p.
 */
/*!
 * \def V_UNUSED(name)
 * Указывает компилятору, что параметр \a name не используется в теле функции.
 * Это может быть использовано для подавлений предупреждений компилятора.
 */
/*!
 * \def V_FOREVER
 * Так же как и #forever.
 */
/*!
 * \def forever
 * Макрос расширяется в бесконечный цикл. Пример:
 * \code
 * forever 
 * {
 *    ...
 * }
 * \endcode
 * Это равносильно for(;;).
 * \see V_FOREVER
 */
/*!
 * \def V_CC_BOR
 * Определено если приложение компилируется в Borland C++. 
 */
/*!
 * \def V_CC_COMEAU
 * Определено если приложение компилируется в Comeau C++. 
 */
/*!
 * \def V_CC_EDG
 * Определено если приложение компилируется в Edison Design Group C++. 
 */
/*!
 * \def V_CC_GHS
 * Определено если приложение компилируется в Green Hills Optimizing C++ Compilers.
 */
/*!
 * \def V_CC_GNU
 * Определено если приложение компилируется в GNU C++. 
 */
/*!
 * \def V_CC_HIGHC
 * Определено если приложение компилируется в MetaWare High C++. 
 */
/*!
 * \def V_CC_HPACC
 * Определено если приложение компилируется в HP aC++. 
 */
/*!
 * \def V_CC_INTEL
 * Определено если приложение компилируется в Intel C++. 
 */
/*!
 * \def V_CC_KAI
 * Определено если приложение компилируется в KAI C++. 
 */
/*!
 * \def V_CC_MIPS
 * Определено если приложение компилируется в MIPSpro C++. 
 */
/*!
 * \def V_CC_MSVC
 * Определено если приложение компилируется в Microsoft Visual C++. 
 */
/*!
 * \def V_CC_MWERKS
 * Определено если приложение компилируется в Metrowerks CodeWarrior. 
 */
/*!
 * \def V_CC_PGI
 * Определено если приложение компилируется в Portland Group C++.
 */
/*!
 * \def V_CC_SUN
 * Определено если приложение компилируется в Sun Studio C++. 
 */
/*!
 * \def V_CC_SYM
 * Определено если приложение компилируется в Digital Mars C++. 
 */
/*!
 * \def V_CC_USLC
 * Определено если приложение компилируется в SCO OUDK. 
 */
/*!
 * \def V_CC_WAT
 * Определено если приложение компилируется в Watcom C++. 
 */

/*! \} */

