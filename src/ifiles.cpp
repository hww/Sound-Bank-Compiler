/**********************************************************

	Sound Bank Compiller

 **********************************************************/

#include <stdio.h>
#include <string.h>

#include "ultratypes.h"
#include "main.h"

tfilelist *flist;
unsigned long fidx;								// Указатели на файл

/**********************************************************

	Открыть файл и поместить его в стек

 **********************************************************/

int push_file( char *name )
{

FILE *f;

	if(fidx>=MAX_FILES)
	{
		printf("Too more number of files\n");
		return 0;
	}

	if((f = fopen( name , "r")) != NULL  )
	{
		printf("%s\n", name);
		
		fidx++;
		strcpy( flist[fidx].name, name);	// Его имя
		flist[fidx].lnum=0;						// Номер строки 0
		flist[fidx].f = f;
		
		return 1;								// Всё ОК
	}
	else return 0;								// Всё ПЛОХО
}

/**********************************************************

	Закрыть файл и достать его из стека

 **********************************************************/

int pop_file( )
{
	
	if(fidx == 0) return 0;						// Нет файлов
	fclose( flist[fidx--].f );					// Есть и закрыть его
	if(fidx == 0) return 0;						// Нет файлов
	return 1;
}