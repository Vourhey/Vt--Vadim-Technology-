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
 * в перменных типа \c int или \c uint. Недостаток такого способа является то,
 * что нет проверки на комбинируемые значения. Любое значение можно пересечь
 * с другим объединением.
 *
 * Если вы хотите использовать VFlags для своих объединений, то используйте
 * V_DECLARE_FLAGS() и V_DECLARE_OPERATORS_FOR_FLAGS(). Пример:
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
 * Вы можете использовать MyCLass::Options для хранения значений MyClass::Option.
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
 * Коснтруктор копийю
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
 * \def V_DECLARE_FLAGS(Flags, Enum)
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
 * \def V_DECLARE_OPERATORS_FOR_FLAGS(Flags)
 * \relates VFlags
 * Объявляет глобальные операторы operator|() для \a Flags.
 * \see V_DECLARE_FLAGS()
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

void vWarning(const char *msg, ... )
{
    va_list format;
    va_start(format, msg);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, msg, format);
    fprintf(stderr, "\n");
    va_end(format);
}

void vDebug(const char *msg, ... )
{
    va_list format;
    va_start(format, msg);
    fprintf(stderr, "Debug: ");
    vfprintf(stderr, msg, format);
    fprintf(stderr, "\n");
    va_end(format);
}
