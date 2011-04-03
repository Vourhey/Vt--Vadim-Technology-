#include "vdatetime.h"
#include <ctime>
#include <sys/time.h>

const int SEC_IN_MINUTE = 60;
const int SEC_IN_HOUR = 3600;
const int MSECS_IN_HOUR = 3600000;
const int SEC_PER_DAY = 86400;
const int MSECS_PER_DAY = 86400000;

/*!
 * \class VTime
 * \brief Обеспечивает функции для работы со временен
 *
 * \note Сейчас существует поддержка только Unix/Linux
 *
 * Класс VTime содержит время, т.е. часы, минуты, секунды и милисекунды
 * начиная с полуночи. Он позволяет получить время с системных часов,
 * замерить промежутки и посчитать разницу. Погрешность состовляет
 * всего несколько милисекунд. Время хранится в формате 24 часа.
 *
 * Обычно для начала работы используется currentTime(), чтобы
 * получить текущее время. По умолчанию создается пустой объект.
 *
 * Получить состовляющие можно через функции: hour(), minute(),
 * second() и msec(). Чтобы засечь промежутки можно использовать
 * start(), restart() и elapsed().  
 */

/*!
 * Создает нулейвой объект. isNull() вернет \c true, isValid() вернет
 * \c false
 * \see isNull()
 */
VTime::VTime()
    : dms(0)
{}

/*!
 * Создает объект, инициализируя полями \a h, \a m, \a s и \a ms.
 * \a h должна быть между 0 и 23, \a m и \a s между 0 и 59,
 * \a ms между 0 и 999
 * \see isValid()
 */
VTime::VTime(int h, int m, int s, int ms)
{
    dms = 0;
    setHMS(h, m, s, ms);
}

/*!
 * Возвращает объект VTime, содержащий время на \a ms
 * больше чем в текущем (или меньше, если \a ms отрицательная)
 *
 * Смотри addSecs() для примера
 * \see msecsTo()
 */
VTime VTime::addMSecs(int ms) const
{
    VTime ret;
    if(ms > 0)
	ret.dms = (dms + ms) % MSECS_PER_DAY;
    else
    {
	int neg = (MSECS_PER_DAY - ms) / MSECS_PER_DAY;
	ret.dms = (dms + ms + neg*MSECS_PER_DAY)%MSECS_PER_DAY;
    }
    return ret;
}

/*!
 * Тоже самое, только добавляет секунды\n
 * Пример:
 * \code
 * VTime n(14, 0, 0);                // n == 14:00:00
 * VTime t;
 * t = n.addSecs(70);                // t == 14:01:10
 * t = n.addSecs(-70);               // t == 13:58:50
 * t = n.addSecs(10 * 60 * 60 + 5);  // t == 00:00:05
 * t = n.addSecs(-15 * 60 * 60);     // t == 23:00:00
 * \endcode
 * \see secsTo()
 */
VTime VTime::addSecs(int s) const
{
    return addMSecs(s * 1000);
}

/*!
 * Возвращает текущее время, которое получаем из
 * системных часов.
 * \note Существует поддержка только Unix/Linux
 */
VTime VTime::currentTime()
{
    // NOTE: Only for Unix/Linux
    VTime ret;
    struct timeval tv;
    struct tm * curtime = 0;
    time_t tt;
    gettimeofday(&tv, 0);
    tt = tv.tv_sec;
    curtime = localtime(&tt);
    ret.dms = 1000*(curtime->tm_sec + curtime->tm_min*SEC_IN_MINUTE +
	      curtime->tm_hour*SEC_IN_HOUR) + tv.tv_usec/1000;
    return ret;
}

/*!
 * Возвращает количество милисекунд, которые
 * прошли с момента вызова start() или restart()
 */
int VTime::elapsed() const
{
    return currentTime().dms - dms;
}

/*!
 * Возвращает число часов
 * \see minute(), second() и msec()
 */
int VTime::hour() const
{
    return dms / MSECS_IN_HOUR;
}

/*!
 * Возвращает \c true, если объект создан
 * конструктором по умолчанию. Иначе \c false.
 * Нулевой объект также является не действительным
 * \see isValid()
 */
bool VTime::isNull() const
{
    return (dms == 0);
}

/*!
 * Возвращает \c true, если время действительное.
 * Иначе \c false. Например, время 23:30:55.746 действительное,
 * но 24:12:30 недействительное.
 * \see isNull()
 */
bool VTime::isValid() const
{
    if(isNull()) return false;
    return isValid(hour(), minute(), second(), msec());
}

/*!
 * Перегруженная функция\n
 * \a h должна быть от 0 до 23, \a m и \a s
 * в промежутке от 0 до 59, а \a ms от 0 до 999
 * \code
 *  VTime::isValid(21, 10, 30); // returns true
 *  VTime::isValid(22, 5,  62); // returns false
 * \endcode
 */
bool VTime::isValid(int h, int m, int s, int ms)
{
    // VTime(0,0,0,0)
    if(h==0 && m==0 && s==0 && ms==0)
	return false;
    if( (h>=0&&h<24) &&
	(m>=0&&m<60) &&
	(s>=0&&s<60) &&
	(ms>=0&&ms<1000) )
	return true;
    return false;
}

/*!
 * Возвращает число минут
 * \see hour(), second() и msec()
 */
int VTime::minute() const
{
    return (dms % MSECS_IN_HOUR) / 60000;
}

/*!
 * Возвращает число милисекунд
 * \see hour(), minute() и second()
 */
int VTime::msec() const
{
    return dms % 1000;
}

/*!
 * Возвращает количество милисекунд от этого врмение 
 * до времени \a t. Результат всегда между -86400000 и 86400000.
 * \see addMSecs()
 */
int VTime::msecsTo(const VTime &t) const
{
    return t.dms - dms;
}

/*!
 * Устанавливает время по системным часам и возвращает
 * число милисекунд, которые прошли с последнего вызова 
 * start() или restart()\n\n
 * Этот медот гарантирует очень точные результаты, т.к.
 * имеет малые погрешности.
 * \see currentTime(), start()
 */
int VTime::restart()
{
    VTime cur = currentTime();
    int ret = cur.dms - dms;
    *this = cur;
    return ret;
}

/*!
 * Возвращает число секунд
 * \see hour(), minute() и msec()
 */
int VTime::second() const
{
    return (dms / 1000) % 60;
}

/*!
 * Делает тоже самое что и msecsTo() только
 * возвращает результат в секундах
 * \see addSecs()
 */
int VTime::secsTo(const VTime &t) const
{
    return (t.dms - dms) / 1000;
}

/*!
 * Устанавливает время\n
 * \a h, \a m, \a s и \a ms должны быть в 
 * действительных пределах
 * \see isValid()
 */
bool VTime::setHMS(int h, int m, int s, int ms)
{
    if(!isValid(h, m, s, ms))
	return false;

    dms = ms + 1000*(s + SEC_IN_MINUTE*m + SEC_IN_HOUR*h);
    return true;
}

/*!
 * Устанавливает время в соостветствии с системными
 * часами. На практике это может быть полезно:
 * \code
 * VTime t;
 * t.start();
 * some_lengthy_task();  // очень большое задание
 * cout << "Time elapsed: " << t.elapsed() << "ms\n"; 
 * \endcode
 * \see elapsed(), restart()
 */
void VTime::start()
{
    *this = currentTime();
}

/*!
 * \fn bool VTime::operator!=(const VTime &t) const
 * Возвращает \c true, если текущее вермя не равно времени \a t.
 * Иначе \c false
 */

/*!
 * \fn bool VTime::operator<(const VTime &t) const
 * Возвращает \c true, если текущее вермя меньше времени \a t.
 * Иначе \c false
 */

/*!
 * \fn bool VTime::operator<=(const VTime &t) const
 * Возвращает \c true, если текущее вермя меньше или 
 * равно времени \a t. Иначе \c false
 */

/*!
 * \fn bool VTime::operator==(const VTime &t) const
 * Возвращает \c true, если текущее вермя равно времени \a t.
 * Иначе \c false
 */

/*!
 * \fn bool VTime::operator>(const VTime &t) const
 * Возвращает \c true, если текущее вермя больше времени \a t.
 * Иначе \c false
 */

/*!
 * \fn bool VTime::operator>=(const VTime &t) const
 * Возвращает \c true, если текущее вермя больше 
 * или равно времени \a t. Иначе \c false
 */
