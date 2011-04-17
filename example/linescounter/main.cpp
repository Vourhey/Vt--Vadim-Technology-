/*!
 * Программа считает строчки в файле и выводит на экран
 */
#include <Vt>
#include <cstdio>

int main(int argc, char **argv)
{
    int c = 0;
    FILE *f;

    if(argc == 1)
    	vFatal("lc: нет входных файлов");
    
    while(argc != 1)
    {
	f = fopen(argv[argc-1], "r");
	if(f == NULL)
	{
	    vCritical("Файл %s не найден", argv[argc-1]);
	    --argc;
	    continue;
	}

	while(!feof(f))
	{
	    if(fgetc(f) == (int)'\n')
		++c;
	}

	printf("%s: %d\n", argv[argc-1], c);
	c = 0;
	--argc;
    }

    return 0;
}
