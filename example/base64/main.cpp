/* VtLib Example *
 *
 * base64 v1.0
 *
 * Простой Base64 кодировщик 
 * На вход нужно подать список файлов */
#include <VByteArray>
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int i = 1;
    VByteArray base;
    base.resize(3);

    while(i < argc)
    {
	cout << "File " << argv[i] << ":\n";
	
	ifstream in(argv[i]);

	while(!in.eof())
	{
	    // читаем по три байта
	    // ровно столько нужно Base64 парсеру для
	    // одного прохода
	    in.read(base.data(), 3);
	    base.resize(in.gcount());
	    cout << base.toBase64().constData();
	}

	cout << "\n\n";
	++i;
    }

    return 0;
}

