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

/*! \} */

