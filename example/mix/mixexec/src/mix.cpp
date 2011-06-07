#include <fstream>
#include "mix.h"

MixExec(const VByteArray &fn)
{
    fileName = fn;
}

// загружает файл в память
void MixExec::loadFile()
{
    ifstream in(fileName.data());

    int i = 0;
    uint mem = 0;
    while(in.good())
    {
	uint tmp;
	in >> tmp;  // считываем знак
	mem = tmp << 30;
	in >> tmp;  // первый байт
	mem |= tmp << 24;
	in >> tmp;  // второй байт
	mem |= tmp << 18;
	in >> tmp;  // третий байт
	mem |= tmp << 12;
	in >> tmp;  // четвертый
	mem |= tmp << 6;
	in >> tmp;  // последний
	mem |= tmp;
	comp.memory[i++] = Registr(mem);
    }
}
