#include <valgorithms.h>

/*!
 * \defgroup algorithms_group Алгоритмы
 * \{
 */

/*!
 * Функция возвращает наибольший общий делитель для чисел
 * \a first и \a second.
 */
uint vNodEvklid(uint first, uint second)
{
    if(first < second) vSwap(first, second);

    int nod = first % second;

    while(nod != 0)
    {
	first = second;
	second = nod;
	nod = first % second;
    }

    return second;
}

/*! \}  */

