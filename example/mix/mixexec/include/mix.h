#ifndef MIX_HEADER
#define MIX_HEADER

#include <Vt>

// класс, представляющий компьютер
class MixExec
{
public:
    inline MixExec() {}
    MixExec(const VByteArray &fn);
    inline void setFileName(VByteArray &fn) { fileName = fn; }

private:
    struct Registr
    {
	inline Registr() : r(0) {}
	inline Registr(uint ir) : r(ir) {}
	bool znak() { return (r >> 30) & 0x1; } // возвращает true если знак "+" иначе false
	uchar byte(uchar b) { return uchar(r >> (6*b)); } // возвращает один байт

	uint r;
    };

    struct RegistrI
    {
	inline RegistrI() : r(0) {}
	inline RegistrI(ushort ir) : r(ir) {}
	bool znak() { return (r >> 12) & 0x1; }
	ushort r;
    };

    struct MixComp
    {
	Registr rA;   // Регистры A и X
	Registr rX;
	RegistrI rI1, rI2, rI3,  // регистры I1 - I6;
		 rI4, rI5, rI6;
	RegistrI rJ;  // Регистр J

	bool overflow; // флаг переполнениея
	char cmp;     // индикатор сравнения. Принимает 0 если равны
		      // -1 если меньше и 1 если больше
	
	Registr memory[4000];  // память на 4000 слов
    };

    void loadFile();

    MixComp comp;
    VByteArray fileName;
};

#endif
