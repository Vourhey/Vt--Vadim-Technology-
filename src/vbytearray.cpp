#include <cstring>
#include <cctype>
#include <cstdlib>
#include "vbytearray.h"
#include "vlist.h"

int vstrcmp(const char *str1, const char *str2)
{
    return (str1 && str2) ? strcmp(str1, str2) :
	(str1 ? 1 : (str2 ? -1 : 0)); 
}

char *vstrcpy(char *dst, const char *str)
{
    return str ? strcpy(dst, str) : 0;
}

uint vstrlen(const char *str)
{
    return str ? strlen(str) : 0;
}

char *vstrdup(const char *str)
{
    if(!str) return 0;
    char *s = new char[vstrlen(str)+1];
    return vstrcpy(s, str);
}

int vstricmp(const char *str1, const char *str2)
{
    int l1 = vstrlen(str1);
    int l2 = vstrlen(str2);

    if(l1 != l2) return l1 - l2; 

    for(int i = 0; i <= l1; i++)
    {
	char c1 = toupper(str1[i]);
	char c2 = toupper(str2[i]);
	if(c1 != c2)
	    return (c1 - c2);
    }

    return 0; // они равны
}

int vstrncmp(const char *str1, const char *str2, uint len)
{
    return (str1 && str2) ? strncmp(str1, str2, len) :
	(str1 ? 1 : (str2 ? -1 : 0));
}

char *vstrncpy(char *dst, const char *str, uint len)
{
    return str ? strncpy(dst, str, len) : 0;
}

int vstrnicmp(const char *str1, const char *str2, uint len)
{
    for(uint i = 0; i<len; ++i)
    {
	char c1 = toupper(str1[i]);
	char c2 = toupper(str2[i]);
	if(c1 != c2) return c1 - c2;
    }
    return 0; // они равны
}

uint vstrnlen(const char *str, uint maxlen)
{
    uint len = vstrlen(str);
    if(len > maxlen) return maxlen;
    return len;
}

int vsnprintf(char *str, size_t n, const char *fmt, ... )
{
    va_list vl;
    va_start(vl, fmt);
    int r = vvsnprintf(str, n, fmt, vl);
    va_end(vl);
    return r;
}

int vvsnprintf(char *str, size_t n, const char *fmt, va_list ap)
{
    return fmt ? vsnprintf(str, n, fmt, ap) : 0;
}

// табличный (быстрый) расчет стандартного CRC-16
const unsigned short Crc16Table[256] = {
	0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
        0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
	0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
	0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
	0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
	0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
	0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
	0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
	0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
	0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
	0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
	0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
	0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
	0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
	0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
	0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
	0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
	0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
	0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
	0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
	0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
	0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
	0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
	0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
	0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
	0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
	0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
	0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
	0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
	0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
	0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
	0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 
};

vuint16 vChecksum(const char *data, uint len)
{
    unsigned short crc = 0xFFFF;

    while (len--)
	crc = (crc >> 8) ^ Crc16Table[(crc & 0xFF) ^ *data++];

    return crc;
}

void VByteArray::reallocData(int size)
{
    if(!d) // ещё не выделялась память
    {
	d = (Data*)malloc(sizeof(Data) + size);
	d->str = d->array;
	d->size = 0;
	d->alloc = size;
	d->str[size] = '\0';
    }
    else if(size > d->alloc)
    {
	Data *x = (Data*)malloc(sizeof(Data) + size);
	x->str = x->array;
	x->alloc = size;
	memcpy(x->str, d->str, d->size);
	x->size = d->size;
	x->str[size] = '\0';
	free(d);
	d = x;
    }
}

/*!
 * \class VByteArray
 * \brief Массив байтов
 *
 * Этот класс можно использовать как тип данных строка.
 * Т.е. вместо \c char \c *.
 */

/*!
 * \var VT_NO_CAST_FROM_BYTEARRAY
 * \relates VByteArray
 * Отменяет автоматическое преобразование в \c const \c char \c *
 * и \c const \c char \c *.
 */

/*!
 * Конструктор создает пустой массив
 * \see isEmpty()
 */
VByteArray::VByteArray()
{
    d = 0;
    reallocData(0);
    d->size = 0;
}

/*!
 * Создает массив из \a str. Создается точная копия строки.
 */
VByteArray::VByteArray(const char *str)
{
    d = 0;
    int s = vstrlen(str);
    reallocData(s);
    d->size = s;
    memcpy(d->str, str, d->size);
}

/*!
 * Создает массив, содержащий первые \a size байтов из \a data.
 */
VByteArray::VByteArray(const char *data, int size)
{
    d = 0;
    reallocData(size);
    memcpy(d->str, data, size);
    d->size = size;
}

/*!
 * Конструктор копий для \a other.
 */
VByteArray::VByteArray(const VByteArray &other)
{
    d = 0;
    reallocData(other.d->size);
    d->size = other.d->size;
    memcpy(d->str, other.d->str, other.d->size);
}

VByteArray::VByteArray(int size)
{
    d = 0;
    reallocData(size);
    d->size = size;
}

/*!
 * Деструктор
 */
VByteArray::~VByteArray()
{
    free(d);
}

/*!
 * \fn VByteArray &VByteArray::append(const VByteArray &ba)
 * Добавляет в конец массив \a ba.\n Пример:
 * \code
 * VByteArray x("free");
 * VByteArray y("dom");
 * x.append(y);
 * // x == "freedom";
 * \endcode
 * \see operator+=(), prepend() и insert()
 */
/*!
 * \fn VByteArray &VByteArray::append(const char *str)
 * \overload \n
 * Добавляет строку \a str в конец массива.
 */
/*!
 * Добавляет первые \a len байтов строки \a str в конец этого массива. 
 * Предполагается, что \a len не больше длины \a str.
 */
VByteArray &VByteArray::append(const char *str, int len)
{
    reallocData(d->size + len);
    memcpy(d->str+d->size, str, len);
    d->size += len;
    d->str[d->size] = '\0';
    return *this;
}

/*!
 * \overload \n Добавляет символ \a ch в конец массива.
 */
VByteArray &VByteArray::append(char ch)
{
    ++d->size;
    reallocData(d->size);
    d->str[d->size-1] = ch;
    d->str[d->size] = '\0';
    return *this;
}

/*!
 * \fn char VByteArray::at(int i) const
 * Возвращает символ с позиции \a i. \a i должна быть
 * в пределах массива (т.е. 0 <= \a i < size()).
 * \see operator[]()
 */
/*!
 * \fn void VByteArray::chop(int n)
 * Удаляет \a n байтов с конца массива.\n Пример:
 * \code
 * VByteArray ba("STARTTLS\r\n");
 * ba.chop(2);        // ba == "STARTTLS"
 * \endcode
 * \see resize()
 */
/*!
 * \fn void VByteArray::clear()
 * Удаляет все содержимое массива.
 * \see resize() и isEmpty()
 */
/*!
 * \fn const char *VByteArray::constData() const
 * Возвращает указатель на данные, хранящиеся в массиве.
 * Данных ограничены '\0'-символом. Указатель будет действителен
 * пока не будет перевыделения памяти.
 * \see data() и operator[]()
 */
/*!
 * \fn bool VByteArray::contains(const VByteArray &ba) const
 * Возвращает \c true, если массив содержит последовательность
 * байтов \a ba. Иначе \c false.
 * \see indexOf() и count()
 */
/*!
 * \overload \n
 * Возвращает \c true, если массив содержит строку \a str. Иначе \c false.
 */
bool VByteArray::contains(const char *str) const
{
    return (indexOf(str) != -1);
}

/*!
 * \overload \n
 * Возвращает \c true, если массив содержит символ \a ch. Иначе \c false.
 */
bool VByteArray::contains(char ch) const
{
    return (indexOf(ch) != -1);
}

/*!
 * \fn int VByteArray::count(const VByteArray &ba) const
 * Возвращает число вхождений \a ba в массив.
 * \see contains() и indexOf()
 */
/*!
 * \overload \n
 * Возвращает число вхождений строки \a str в массив.
 */
int VByteArray::count(const char *str) const
{
    int c = 0;
    int pos = indexOf(str);

    while(pos != -1)
    {
	++c;
	pos = indexOf(str, pos+1);
    }

    return c;
}

/*!
 * \overload \n
 * Возвращает вхождение символа \a ch в массив.
 */
int VByteArray::count(char ch) const
{
    int c = 0;

    for(int i=0; i<d->size; i++)
	if(d->str[i] == ch)
	    ++c;

    return c;
}
/*!
 * \fn int VByteArray::count() const
 * Равносильно size().
 */
/*!
 * \fn char *VByteArray::data()
 * Возвращает указатель на данные, хранящиеся в массиве.
 * Строка ограничена '\0'-символом. \n Пример:
 * \code
 * VByteArray ba("Hello world");
 * char *data = ba.data();
 * while(*data)
 * {
 *     cout << '[' << *data << ']' << endl;
 *     ++data;
 * }
 * \endcode
 * Если вы не собираетесь изменять содержимое, то лучше 
 * использовать constData().
 * \see constData() и operator[]()
 */
/*!
 * \fn const char *VByteArray::data() const
 * \overload
 */
/*!
 * \fn bool VByteArray::endsWith(const VByteArray &ba) const
 * Возвращает \c true, если массив заканчивается на \a ba. 
 * Иначе \c false. \n Пример:
 * \code
 * VByteArray url("http://anyhost.com/index.html");
 * if(url.endsWith(".html"))
 *     ...
 * \endcode
 * \see startsWith()
 */
/*!
 * \overload \n Возвращает \c true, если массив 
 * заканчивается на строку \a str. Иначе \c false.
 */
bool VByteArray::endsWith(const char *str) const
{
    int l = vstrlen(str);

    if(!vstrncmp(d->str+(d->size-l), str, l))
	return true;

    return false;
}

/*!
 * \overload \n Возвращает \c true, если массив
 * закачивается на символ \c ch. Иначе \c false.
 */
bool VByteArray::endsWith(char ch) const
{
    return (d->str[d->size-1] == ch);	
}

/*!
 * Устанавливает каждый байт в символ \a ch.
 * Если \a size равна -1 (по умолчанию), то массив изменяет
 * размер до \a size.\n Пример:
 * \code
 * VByteArray ba("Istambul");
 * ba.fill('0');
 * // ba == "oooooooo"
 *
 * ba.fill('X', 2);
 * // ba == "XX"
 * \endcode
 * \see resize()
 */
VByteArray &VByteArray::fill(char ch, int size)
{
    if(size == -1) size = d->size;
    reallocData(size);
    d->size = size;

    for(int i = 0; i<d->size; i++)
	d->str[i] = ch;
    d->str[d->size] = '\0';

    return *this;
}

/*!
 * \fn int VByteArray::indexOf(const VByteArray &ba, int from = 0) const
 * Возвращает позицию первого вхождения \a ba в массив. Поиск производится,
 * начиная с \a from и до конца. Возвращается -1, если \a ba не найден.\n Пример:
 * \code
 * VByteArray x("sticky question");
 * VByteArray y("sti");
 * x.indexOf(y);             // return 0
 * x.indexOf(y, 1);          // return 10
 * x.indexOf(y, 10);         // return 10
 * x.indexOf(y, 11);         // return -1
 * \endcode
 * \see lastIndexOf(), contains() и count()
 */

int indexOf_helper(const char *ba, int size, const char *str, int len, int from)
{
    for(int i = from; i<size; i++)
	if(!vstrncmp(ba+i, str, len))
	    return i;
    return -1;
}

/*!
 * \overload \n
 * Возвращает позицию первого вхождения строки \a str в массив, начиная
 * с \a from. Возвращает -1 если строка не найдена.
 */
int VByteArray::indexOf(const char *str, int from) const
{
    return indexOf_helper(d->str, d->size, str, vstrlen(str), from);
}

/*!
 * \overload \n
 * Возвращает позицию первого вхождения символа \a ch в массив.
 * Возвращает -1, если символ не найден.\n Пример:
 * \code
 * VByteArray ba("abcba");
 * ba.indexOf('b');         // return 1
 * ba.indexOf('b', 1);      // return 1
 * ba.indexOf('b', 2);      // return 3
 * ba.indexOf('x');         // return -1
 * \endcode
 * \see lastIndexOf() и contains()
 *
 */
int VByteArray::indexOf(char ch, int from) const
{
    for(int i = from; i<d->size; i++)
	if(d->str[i] == ch)
	    return i;
    return -1;
}

/*!
 * \fn VByteArray &VByteArray::insert(int i, const VByteArray &ba)
 * Вставляет массив байтов \a ba в позцию \a i.\n Пример:
 * \code
 * VByteArray ba("Meal");
 * ba.insert(1, VByteArray("ontr"));
 * // ba == "Montreal"
 * \endcode
 * \see append(), prepend(), replace() и remove()
 */
/*!
 * \fn VByteArray &VByteArray::insert(int i, const char *str)
 * \overload \n
 * Вставляет строку \a str в позцию \a i.
 */
/*!
 * \overload \n
 * Вставляет первые \a len байтов строки \a str в позицию \a i.
 */
VByteArray &VByteArray::insert(int i, const char *str, int len)
{
    int olds = d->size;
    reallocData(d->size + len);
    d->size += len;
    memmove(d->str+i+len, d->str+i, olds-i);
    memcpy(d->str+i, str, len);
    d->str[d->size] = '\0';

    return *this;
}

/*!
 * \overload \n
 * Вставляет символ \a ch в позицию \a i в массив байтов.
 */
VByteArray &VByteArray::insert(int i, char ch)
{
    d->size++;
    reallocData(d->size);

    memmove(d->str+i+1, d->str+i, d->size-i-1);
    d->str[i] = ch;
    d->str[d->size] = '\0';

    return *this;
}

/*!
 * \fn bool VByteArray::isEmpty() const
 * Возвращает \c true, если размер массива байтов равен 0. 
 * Иначе \c false.\n Пример:
 * \code
 * VByteArray().isEmpty();      // return true
 * VByteArray("").isEmpty();    // return true
 * VByteArray("abc").isEmpty(); // return false
 * \endcode
 * \see size()
 */

/*!
 * \fn int VByteArray::lastIndexOf(const VByteArray &ba, int from = -1) const
 * Возвращает позицию последнего вхождения \a ba в массив байто.
 * Поиск производится в обраном порядке, начиная с \a from. Если \a from
 * равна -1 (по умолчанию), то поиск происходит с конца массива.
 * Возвращается -1, если \a ba не найден:
 * \code
 * VByteArray x("crazy azimuts");
 * VByteArray y("az");
 * x.lastIndexOf(y);     // return 6
 * x.lastIndexOf(y, 6);  // return 6
 * x.lastIndexOf(y, 5);  // return 2
 * x.lastIndexOf(y, 1);  // retun -1
 * \endcode
 * \see indexOf(), contains() и count()
 */
/*!
 * \overload \n
 * Возвращает позицию последнего вхождения строки \a str
 * в массив. Если строка не найдена, возвращается -1.
 */
int VByteArray::lastIndexOf(const char *str, int from) const
{
    if(from == -1) from = d->size-1;
    int l = vstrlen(str);

    for(int i = from; i > -1; i--)
	if(!vstrncmp(d->str+i, str, l))
	    return i;

    return -1;
}

/*!
 * \overload \n
 * Возвращается позицию последнего вхождения символа \a ch
 * в массив. Если символ не найден, возвращается -1.\n Пример:
 * \code
 * VByteArray ba("abcba");
 * ba.lastIndexOf('b');        // return 3
 * ba.lastIndexOf('b', 3);     // return 3
 * ba.lastIndexOf('b', 2);     // return 1
 * ba.lastIndexOf('x');        // return -1
 * \endcode
 * \see indexOf() и contains()
 */
int VByteArray::lastIndexOf(char ch, int from) const
{
    if(from == -1) from = d->size - 1;

    for(int i = from; i > -1; i--)
	if(d->str[i] == ch)
	    return i;

    return -1;
}

/*!
 * \fn int VByteArray::length() const
 * Равносильно size().
 */
/*!
 * \fn VByteArray VByteArray::number(int n, int base = 10)
 * Возвращает массив байтов, содержащий строковой эквивалент
 * числа \a n с основанием \a base (10 по умолчанию).
 * \a base может быть от 2 до 36.\n Пример:
 * \code
 * int n = 63;
 * VByteArray::number(n);           // return "63"
 * VByteArray::number(n, 16);       // return "3f"
 * \endcode
 * \see setNum()
 */
/*!
 * \fn VByteArray VByteArray::number(uint n, int base = 10)
 * \overload
 */
/*!
 * \fn VByteArray VByteArray::number(vlonglong n, int base = 10)
 * \overload
 */
/*!
 * \fn VByteArray VByteArray::number(vulonglong n, int base = 10)
 * \overload
 */
/*!
 * \fn VByteArray VByteArray::number(double n, int prec = 6)
 * \overload \n
 * Возвращает строковой эквивалент числа \a n округленного 
 * до \a prec знаков после запятой.
 * \code
 * VByteArray ba = VByteArray::number(12.3456, 3);
 * // ba == "12.345"
 * \endcode
 * \see setNum()
 */

/*!
 * \fn VByteArray &VByteArray::prepend(const VByteArray &ba)
 * Вставляет в начало массива \a ba и возвращает ссылку на этот массив.
 * \n Пример:
 * \code
 * VByteArray x("ship");
 * VByteArray y("air");
 * x.prepend(y);
 * // x == "airship"
 * \endcode
 * Равносильно вызову insert(0, \a ba).
 * \see append() и insert().
 */
/*!
 * \fn VByteArray &VByteArray::prepend(const char *str)
 * \overload \n Вставляет строку \a str в начало массива.
 */
/*!
 * \overload \n Вставляет первые \a len байтов строки \a str
 * в начало массива.
 */
VByteArray &VByteArray::prepend(const char *str, int len)
{
    reallocData(d->size + len);
    d->size += len;
    memmove(d->str+len, d->str, d->size-len);
    memcpy(d->str, str, len);
    d->str[d->size] = '\0';
    return *this;
}

/*!
 * \overload \n Вставляет символ \a ch в начало массива.
 */
VByteArray &VByteArray::prepend(char ch)
{
    d->size++;
    reallocData(d->size);
    memmove(d->str+1, d->str, d->size-1);
    d->str[0] = ch;
    d->str[d->size] = '\0';
    return *this;
}

/*!
 * \fn void VByteArray::push_back(const VByteArray &other)
 * \stl Равносильно append(\a other).
 */
/*!
 * \fn void VByteArray::push_back(const char *str)
 * \overload \n Равносильно append(\a str).
 */
/*!
 * \fn void VByteArray::push_back(char ch)
 * \overload \n Равносильно append(\c ch).
 */
/*!
 * \fn void VByteArray::push_front(const VByteArray &other)
 * \stl Равносильно prepend(\a other).
 */
/*!
 * \fn void VByteArray::push_front(const char *str)
 * \overload \n Равносильно prepend(\a str).
 */
/*!
 * \fn void VByteArray::push_front(char ch)
 * \overload \n Равносильно prepend(\a ch).
 */

// алгоритм перевода в Base64 взят с Wikipedia
/*!
 * Возвращает копию массива, закодированную по алгоритму Base64.
 * \code
 * VByteArray text("Vt is great!");
 * text.toBase64();     // returns "VnQgaXMgZ3JlYXQh"
 * \endcode
 * Про алгоритм <a href="http://ru.wikipedia.org/wiki/Base32">подробнее</a>.
 */
VByteArray VByteArray::toBase64() const
{
    const char *alphabit = "ABCDEFGHI" "JKLMNOPQR" "STUVWXYZa"
	    "bcdefghij" "klmnopqrs" "tuvwxyz" "0123456789+/";
    int pchar = '=';
    int plen = 0;

    VByteArray tmp(d->size+4);
    char *out = tmp.data();

    int i = 0;
    while(i < d->size)
    {
	int charout = 0;
	charout |= int(uchar(d->str[i++])) << 16;
	if(i == d->size) plen = 2;
	else
	{
	    charout |= int(uchar(d->str[i++])) << 8;
	    if(i == d->size) plen = 1;
	    else charout |= int(uchar(d->str[i++]));
	}

	int j = (charout & 0x00fc0000) >> 18; // берем старшие 6 бит
	int l = (charout & 0x0003f000) >> 12; // следующие 6
	int k = (charout & 0x00000fc0) >> 6; 
	int m = (charout & 0x0000003f);

	*out++ = alphabit[j];
	*out++ = alphabit[l];
	if(plen > 1) *out++ = pchar;
	else *out++ = alphabit[k];
	if(plen > 0) *out++ = pchar;
	else *out++ = alphabit[m];
    }

    return tmp;
}

VByteArray VByteArray::fromBase64(const VByteArray &base64)
{
    uint buf = 0;
    int nbits = 0;
    VByteArray tmp;
    tmp.resize(base64.size());
    
    int offset = 0;
    for (int i = 0; i < base64.size(); ++i) 
    {
	int ch = base64.at(i);
	int d;
	
	if (ch >= 'A' && ch <= 'Z')
	    d = ch - 'A';
	else if (ch >= 'a' && ch <= 'z')
	    d = ch - 'a' + 26;
	else if (ch >= '0' && ch <= '9')
	    d = ch - '0' + 52;
	else if (ch == '+')
	    d = 62;
	else if (ch == '/')
	    d = 63;
	else
	    d = -1;

	if (d != -1) 
	{
	    buf = (buf << 6) | d;
	    nbits += 6;
	    if (nbits >= 8) 
	    {
		nbits -= 8;
		tmp[offset++] = buf >> nbits;
		buf &= (1 << nbits) - 1;
	    }
	}
    }
    
    return tmp;
}

/*!
 * \fn bool VByteArray::startsWith(const VByteArray &ba) const
 * Возвращает \c true, если массив начинается с \a ba. 
 * Иначе \c false.\n Пример:
 * \code
 * VByteArray url("ftp://anyhost/");
 * if(url.startsWith("ftp:"))
 *    ...
 * \endcode
 * \see endsWith()
 */
/*!
 * \overload \n Возвращает \c true, если массив начинается
 * со строки \a str. Иначе \c false.
 */
bool VByteArray::startsWith(const char *str) const
{
    return !vstrncmp(d->str, str, vstrlen(str));
}

/*!
 * \overload \n Возвращает \c true, если массив начинается
 * с символа \a ch. Иначе \c false.
 */
bool VByteArray::startsWith(char ch) const
{
    return d->str[0] == ch;
}

/*!
 * Удаляет \a len байтов с позиции \a pos.\n Пример:
 * \code
 * VByteArray ba("Montreal");
 * ba.remove(1, 4);
 * // ba == "Meal"
 * \endcode
 * \see insert() и replace()
 */
VByteArray &VByteArray::remove(int pos, int len)
{
    memmove(d->str+pos, d->str+pos+len, d->size-pos-len);
    reallocData(d->size-len);
    d->size -= len;
    d->str[d->size] = '\0';
    return *this;
}

/*!
 * Возвращает копию этого массива, повторенную \a times раз.
 * \code
 * VByteArray ba("ab");
 * ba.repeated(4);      // retruns "abababab"
 * \endcode
 */
VByteArray VByteArray::repeated(int times) const
{
    VByteArray tmp(times * d->size);

    while(times--)
	tmp.append(d->str);

    tmp.d->str[tmp.d->size] = '\0';
    return tmp;
}

/*!
 * \fn VByteArray &VByteArray::replace(int pos, int len, const VByteArray &after)
 * Заменят \a len байтов с позиции \a pos на массив \a after.\n Пример:
 * \code
 * VByteArray x("Say yes!");
 * VByteArray y("no");
 * x.replace(4, 3, y);
 * // x == "Say no!"
 * \endcode
 * \see insert() и remove()
 */
/*!
 * \fn VByteArray &VByteArray::replace(int pos, int len, const char *after)
 * \overload \n Заменят \a len байтов с позиции \a pos на строку \a after.
 */
/*!
 * \overload \n Заменят \a len байтов с позиции \a pos на первые
 * \a alen байтов строки \a after.
 */
VByteArray &VByteArray::replace(int pos, int len, const char *after, int alen)
{
    int old = d->size;
    d->size = d->size - len + alen;
    reallocData(d->size);

    memmove(d->str+pos+alen, d->str+pos+len, old-pos-len);
    memcpy(d->str+pos, after, alen);
    d->str[d->size] = '\0';
    return *this;
}

/*!
 * \fn VByteArray &VByteArray::replace(const VByteArray &before, const VByteArray &after)
 * \overload \n Заменяет каждое вхождение \a before на массив \a after.\n Пример:
 * \code
 * VByteArray ba("colour behaviour flavour neighbour");
 * ba.replace(VByteArray("ou"), VByteArray("o"));
 * // ba == "color behavior flavor neghbor"
 * \endcode
 */
/*!
 * \fn VByteArray &VByteArray::replace(const char *before, const VByteArray &after)
 * \overload \n Заменят каждое вхождение строки \a before на массив \a after.
 */
/*!
 * \overload \n Заменяет каждое вхождение первых \a bsize байтов строки
 * \a before на первые \a asize байтов строки \a after.
 */
VByteArray &VByteArray::replace(const char *before, int bsize, const char *after, int asize)
{
    int pos = indexOf_helper(d->str, d->size, before, bsize, 0);

    if(pos == -1) return *this;

    return replace(pos, bsize, after, asize);
}

/*!
 * \fn VByteArray &VByteArray::replace(const VByteArray &before, const char *after)
 * \overload \n Заменятет кадое вхождение \a before на \a after.
 */
/*!
 * \fn VByteArray &VByteArray::replace(const char *before, const char *after)
 * \overload \n Заменят каждое вхождение \a before на \a after.
 */
/*!
 * \overload \n Заменяет каждый символ \a before на массив \a after.
 */
VByteArray &VByteArray::replace(char before, const VByteArray &after)
{
    int pos = indexOf(before);
    if(pos == -1) return *this;
    return replace(pos, 1, after.d->str, after.d->size);
}

/*!
 * \overload \n Заменяет каждый символ \a before на строку \a after.
 */
VByteArray &VByteArray::replace(char before, const char *after)
{
    int pos = indexOf(before);

    if(pos == -1) return *this;
    
    return replace(pos, 1, after, vstrlen(after));
}

/*!
 * \overload \n Заменяет каждое вхождение \a before на символ \a after.
 */
VByteArray &VByteArray::replace(char before, char after)
{
    int pos = indexOf(before);
    
    while(pos != -1) 
    {
	 d->str[pos] = after;
	 pos = indexOf(before, pos+1);
    }
    return *this;
}

/*!
 * \fn VByteArray &VByteArray::setNum(int n, int base = 10)
 * Массив становится равным строковому представлению числа \a n
 * по основанию \a base (10 по умолчанию). \a base может быть
 * от 2 до 36.\n Пример:
 * \code
 * VByteArray ba;
 * int n = 63;
 * ba.setNum(n);         // ba == "63"
 * ba.setNum(n, 16);     // ba == "3f"
 * \endcode
 * \see number()
 */
/*!
 * \fn VByteArray &VByteArray::setNum(uint n, int base = 10)
 * \overload
 */
/*!
 * \fn VByteArray &VByteArray::setNum(short n, int base = 10)
 * \overload
 */
/*!
 * \fn VByteArray &VByteArray::setNum(ushort n, int base = 10)
 * \overload
 */
/*!
 * \overload
 */
VByteArray &VByteArray::setNum(vulonglong n, int base)
{
    char buf[65];
    char *p = buf + 65;

    if(base < 2 || base > 36)
    {
	vWarning("VByteArray::setNum(): base не может быть %d", base);
	base = 10;	
    }

    if(base == 10)
    {
	while(n != 0)
	{
	    int c = n % 10;
	    *(--p) = '0' + c;
	    n /= 10;
	}
    }
    else
    {
	while(n != 0)
	{
	    int c = n % base;
	    --p;

	    if(c < 10) *p = c + '0';
	    else *p = c - 10 + 'a';

	    n /= base;
	}
    }

    clear();
    int size = 65 - int(p-buf);
    reallocData(size);
    d->size = size;
    for(int i=0; i<d->size; i++)
	d->str[i] = p[i];

    return *this;
}

/*!
 * \overload
 */
VByteArray &VByteArray::setNum(vlonglong n, int base)
{
    setNum(vulonglong(vAbs(n)), base);
    if(n < 0) prepend('-');
    return *this;
}

/*!
 * \overload \n Массив символов становится равным строковому
 * представлению числа \a n, ограниченного \a prec знаками после запятой.
 */
VByteArray &VByteArray::setNum(double n, int prec)
{
    int decpt;
    int sign;

    char *s = fcvt(n, prec, &decpt, &sign);

    clear();
    int size = vstrlen(s) + 3;
    reallocData(size); // 3 символа на запятую, знак и ноль
    d->size = size;

    int i = 0;
    if(sign > 0) d->str[i++] = '-';
    if(decpt < 0) { d->str[i++] = 0; decpt = 0; }

    memcpy(d->str+i, s, decpt);
    i += decpt;
    d->str[i++] = '.';
    s += decpt;
    while(*s)
	d->str[i++] = *s++;
    d->str[i] = '\0';
    d->size = i;
    return *this;
}
/*!
 * \fn VByteArray &VByteArray::setNum(float n, int prec = 6)
 * \overload
 */

/*!
 * \fn int VByteArray::size() const
 * Возвращает число байтов в массиве.\n Последний символ в
 * массиве имеет позицию size()-1. Это из-за того, что любой
 * массив ограничен '\0'-символом.\n Пример:
 * \code
 * VByteArray ba("Hello");
 * int n = ba.size();       // n == 5
 * ba.data()[0];            // return 'H'
 * ba.data()[4];            // return 'o'
 * ba.data()[5];            // return '\0'
 * \endcode
 * \see isEmpty() и resize()
 */
/*!
 * \fn bool VByteArray::operator!=(const VByteArray &str) const
 * Возвращает \c true, если массив символов не равен \a str.
 * Иначе \c false. Сравнение производится с учетом регистра.
 */
/*!
 * \fn VByteArray &VByteArray::operator+=(const VByteArray &ba)
 * Добавляет в конец этого массива массив \a ba.\n Пример:
 * \code
 * VByteArray x("free");
 * VByteArray y("dom");
 * x += y;
 * // x == "freedom"
 * \endcode
 * \see append() и prepend()
 */
/*!
 * \fn VByteArray &VByteArray::operator+=(const char *str)
 * \overload \n Добавляет в конец массива строку \a str.
 */
/*!
 * \fn VByteArray &VByteArray::operator+=(char ch)
 * \overload \n Добавляет в конец массива символ \a ch.
 */
/*!
 * \fn bool VByteArray::operator<(const VByteArray &str) const
 * Возвращает \c true, если этот массив меньше \a str. Иначе \c false.
 * Сравнение производится с учетом регистра.
 */
/*!
 * \fn bool VByteArray::operator<=(const VByteArray &str) const
 * Возвращает \c true, если массив меньше или равен \a str.
 * Иначе \c false. Сравнение производится с учетом регистра.
 */
/*!
 * \fn bool VByteArray::operator==(const VByteArray &str) const
 * Возвращает \c true, если массив равен \a str. Иначе \c false.
 * Сравнение производится с учетом регистра.
 */
/*!
 * \fn bool VByteArray::operator>(const VByteArray &str) const
 * Возвращает \c true, если массив больше \a str. Иначе \c false.
 * Сравнение производится с учетом регистра.
 */
/*!
 * \fn bool VByteArray::operator>=(const VByteArray &str) const
 * Возвращает \c true, если массив больше или равен \a str.
 * Иначе \c false. Сравнение производится с учетом регистра.
 */
/*!
 * \fn char &VByteArray::operator[](int i)
 * Возвращает ссылку на символ с позиции \a i.\n Пример:
 * \code
 * VByteArray ba;
 * ba.reserve(10);
 * for(int i = 0; i<10; ++i)
 *     ba[i] = 'A' + i;
 * // ba == "ABCDEFGHIJ"
 * \endcode
 * \see at()
 */
/*!
 * \fn char VByteArray::operator[](int i) const
 * \overload \n Равносильно at(\a i).
 */
/*!
 * \fn char &VByteArray::operator[](uint i)
 * \overload
 */
/*!
 * \fn char VByteArray::operator[](uint i) const
 * \overload
 */
/*!
 * \fn void VByteArray::reserve(int size)
 * Выделяет память под \a size символов. Эта функция
 * позволяет напрямую следить за выделением памяти. Так же
 * она полезна, если вы заранее знаете, сколько байтов будет
 * занимать массив. Функция не меняет размер, а только
 * выделенную память.
 * \see resize()
 */
/*!
 * \fn void VByteArray::resize(int size)
 * Изменят размер массива до \a size. Если \a size
 * больше текущего размера, то массив выделяет дополнительную
 * память. Если \a size меньше текущего размера, то последние
 * символы теряются.
 * \see size()
 */
/*!
 * \fn bool operator!=(const VByteArray &a1, const char *a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если \a a1 не равен \a a2. Иначе \c false.
 */
/*!
 * \fn bool operator!=(const char *a1, const VByteArray &a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если строка \a a1 не равна
 * массиву \a a2. Иначе \c false.
 */
/*!
 * \fn const VByteArray operator+(const VByteArray &a1, const char *a2)
 * \relates VByteArray
 * \overload \n Возвращает массив, содержащий соединенные \a a1 и \a a2.
 */
/*!
 * \fn const VByteArray operator+(const VByteArray &a1, char a2)
 * \relates VByteArray
 * \overload \n Возвращает массив, содержащий соединенные \a a1 и \a a2.
 */
/*!
 * \fn const VByteArray operator+(const char *a1, const VByteArray &a2)
 * \relates VByteArray
 * \overload \n Возвращает массив, содержащий соединенные \a a1 и \a a2.
 */
/*!
 * \fn const VByteArray operator+(char a1, const VByteArray &a2)
 * \relates VByteArray
 * \overload \n Возвращает массив, содержащий соединенные \a a1 и \a a2.
 */
/*!
 * \fn const VByteArray operator+(const VByteArray &a1, const VByteArray &a2)
 * \relates VByteArray
 * \overload \n Возвращает массив, содержащий результат соединения \a a1 и \a a2.
 * \see VByteArray::operator+=()
 */
/*!
 * \fn bool operator<(const VByteArray &a1, const char *a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если массив \a a1 меньше
 * строки \a a2. Иначе \c false.
 */
/*!
 * \fn bool operator<(const char *a1, const VByteArray &a2)
 * \relates VByteArray
 * Возвращает \c true, если строка \a a1 меньше массива \a a2.
 * Иначе \c false.
 */
/*!
 * \fn bool operator<=(const VByteArray &a1, const char *a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если массив \a a2 меньше
 * или равен \a a2. Иначе \c false.
 */
/*!
 * \fn bool operator<=(const char *a1, const VByteArray &a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если строка \a a1 меньше
 * или равна массиву \a a2. Иначе \c false.
 */
/*!
 * \fn bool operator==(const VByteArray &a1, const char *a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если массив \a a1
 * равен строке \a a2. Иначе \c false.
 */
/*!
 * \fn bool operator==(const char *a1, const VByteArray &a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если строка \a a1 равна
 * массиву \a a2. Иначе \c false.
 */
/*!
 * \fn bool operator>(const VByteArray &a1, const char *a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если массив \a a1 больше
 * строки \a a2. Иначе \c false.
 */
/*!
 * \fn bool operator>(const char *a1, const VByteArray &a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если строка \a a1
 * больше массива \a a2. Иначе \c false.
 */
/*!
 * \fn bool operator>=(const VByteArray &a1, const char *a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если массив \a a1
 * больше или равен строки \a a2. Иначе \c false.
 */
/*!
 * \fn bool operator>=(const char *a1, const VByteArray &a2)
 * \relates VByteArray
 * \overload \n Возвращает \c true, если строка \a a1
 * больше или равна массива \a a2. Иначе \c false.
 */

/*!
 * Возвращает указатель на данные, хранящиеся в массиве.
 * Данные ограничены '\0'-символом. Указатель действителен так
 * долго, пока не будет перевыделена память.
 *
 * Этот оператор полезен для функций, принимающих <tt>const char *</tt>.
 * Если вы объявете #VT_NO_CAST_FROM_BYTEARRAY, то отключите этот оператор.
 * \see constData()
 */
VByteArray::operator const char *() const
{
    return d->str;
}

/*!
 * Возвращает указатель на данные, хранящиеся в массиве.
 * Данные ограничены '\0'-символом. Указатель действителен
 * так долго, пока не будет перевыделена память.
 *
 * Оператор полезен для функций, принимающих <tt>const char *</tt>
 * или <tt>const void *</tt>.
 * \see constData()
 */
VByteArray::operator const void *() const
{
    return d->str;
}

VByteArray VByteArray::left(int len) const
{
    return VByteArray(d->str, len);
}

VByteArray VByteArray::right(int len) const
{
    return VByteArray(d->str+(d->size-len), len);
}

VByteArray VByteArray::mid(int pos, int len) const
{
    if(len == -1) len = d->size - pos;
    return VByteArray(d->str+pos, len);
}

bool vIsLower(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

bool vIsUpper(char ch)
{
    return ch >= 'A' && ch <= 'Z';
}

char vToLower(char ch)
{
    if(vIsUpper(ch))
	ch -= 'A';
    return ch;
}

char vToUpper(char ch)
{
    if(vIsLower(ch))
	ch += 'A';
    return ch;
}

VByteArray VByteArray::toLower() const
{
    VByteArray ret;
    ret.reserve(d->size);

    for(int i=0; i<d->size; ++i)
	ret[i] = vToLower(d->str[i]);
    return ret;
}

VByteArray VByteArray::toUpper() const
{
    VByteArray ret;
    ret.reserve(d->size);

    for(int i=0; i<d->size; ++i)
	ret[i] = vToUpper(d->str[i]);
    return ret;
}

VByteArray &VByteArray::setRawData(const char *data, uint size)
{
    clear();
    reallocData(0);

    d->str = const_cast<char*>(data);
    d->size = d->alloc = size;
    return *this;
}

VByteArray VByteArray::leftJustified(int width, char fill, bool truncate) const
{
    int p = width - d->size;
    if(p < 0)
    {
	if(truncate)
	    return left(width);
	else
	    return *this;
    }

    VByteArray ret;
    ret.resize(width);

    memcpy(ret.d->str, d->str, d->size);
    memset(ret.d->str+d->size, fill, p);
    return ret;
}

VByteArray VByteArray::rightJustified(int width, char fill, bool truncate) const
{
    int p = width - d->size;
    if(p < 0)
    {
	if(truncate)
	    return right(width);
	else
	    return *this;
    }

    VByteArray ret;
    ret.resize(width);

    memcpy(ret.d->str+p, d->str, d->size);
    memset(ret.d->str, fill, p);
    return ret;
}

bool vIsSpace(char ch)
{
    return ch == ' '  ||
	   ch == '\t' ||
	   ch == '\n' ||
	   ch == '\v' ||
	   ch == '\f' ||
	   ch == '\r';
}

VByteArray VByteArray::simplified() const
{
    if(d->size == 0)
	return *this;

    VByteArray ret;

    ret.reserve(size());
    char *out = ret.data();
    char *in = d->str;
    char *inend = d->str + d->size;
    int pos = 0;

    forever
    {
	while(in != inend && vIsSpace(*in))
	    ++in;
	while(in != inend && !vIsSpace(*in))
	    out[pos++] = *in++;
	if(in != inend)
	    out[pos++] = ' ';
	else
	    break;
    }

    if(pos > 0 && out[pos-1] == ' ')
	--pos;
    ret.resize(pos);

    return ret;
}

VList<VByteArray> VByteArray::split(char sep) const
{
    VList<VByteArray> ret;
    int pos = indexOf(sep);
    int last = 0;

    while(pos != -1)
    {
	ret << VByteArray(d->str+last, pos-last);
	last = pos + 1;
	pos = indexOf(sep, last);
    }

    if(last != d->size)
	ret << VByteArray(d->str+last, d->size - last);

    return ret;
}

void VByteArray::squeeze()
{
    if(d->size == d->alloc)
	return;

    Data *x = (Data*)malloc(sizeof(Data)+d->size);
    x->alloc = x->size = d->size;
    x->str = x->array;
    x->str[d->size] = '\0';
    memcpy(x->str, d->str, d->size);
    free(d);
    d = x;
}

VByteArray VByteArray::toHex() const
{
    VByteArray ret;
    ret.resize(d->size * 2);

    const uchar *in = (const uchar *)d->str;
    char *out = ret.d->str;

    for(int i=0; i<d->size; ++i)
    {
	int c = (in[i] >> 4) & 0xF;
	if(c <= 9)
	    *out++ = c + '0';
	else
	    *out++ = c - 10 + 'a';
	c = in[i] & 0xF;
	if(c <= 9)
	    *out++ = c + '0';
	else
	    *out++ = c - 10 + 'a';
    }

    return ret;
}

VByteArray VByteArray::fromHex(const VByteArray &hexEncoded)
{
    VByteArray ret;
    ret.resize(hexEncoded.d->size / 2 );

    const uchar *hex = (const uchar *)hexEncoded.d->str;
    char *out = ret.d->str;

    for(int i=0; i<hexEncoded.d->size; ++i)
    {
	char c = 0;
	int tmp = hex[i];

	if(tmp >= 'a' && tmp <= 'z')
	    tmp = (tmp - 'a' + 10) << 4;
	else if(tmp >= 'A' && tmp <= 'Z')
	    tmp = (tmp - 'A' + 10) << 4;
	else if(tmp >= '0' && tmp <= '9')
	    tmp = (tmp - '0') << 4;
	c |= tmp;

	tmp = hex[++i];
	if(tmp >= 'a' && tmp <= 'z')
	    tmp = (tmp - 'a' + 10);
	else if(tmp >= 'A' && tmp <= 'Z')
	    tmp = (tmp - 'A' + 10);
	else if(tmp >= '0' && tmp <= '9')
	    tmp = tmp - '0';

	c |= tmp;

	*out++ = c;
    }
    
    return ret;
}

