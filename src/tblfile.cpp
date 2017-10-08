/**********************************************************

	Sound Bank Compiller

 **********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ultratypes.h"
#include "main.h"

FILE *ftbl;
unsigned int tblpos;


/**********************************************************

	Открыть файл и поместить его в стек

 **********************************************************/

int opent_tbl( )
{
	
	tblpos=0;					// В начало файла

	if((ftbl = fopen( "tone.tbl" , "wb")) == NULL  )
	{
		printf("Can't create TBL file\n"); 
		return 0;								// Всё ПЛОХО
	}
	return 1;									// Всё ОК
}

/**********************************************************

	Записать в выходной файл семпл

 **********************************************************/

int write_tbl( char *ptr, unsigned int size)
{
#ifdef	MOST_SIGN_ORDER
	_swab( ptr, ptr, size );
#endif
	if( fwrite( ptr, size, 1, ftbl ) == 0)
	{
		return 0;
	}

	tblpos+=size;
	return 1;
}

/**********************************************************

	Закрыть файл и достать его из стека

 **********************************************************/

int close_tbl( )
{

	fclose( ftbl);								// Закрыть его
	
	return 1;
}