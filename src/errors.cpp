/**********************************************************

	Sound Bank Compiller

 **********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "ultratypes.h"
#include "main.h"

long numErrors, numWarnings;

/**********************************************************
 * Сообщение об ошибке
 **********************************************************/


void print_e( char *sym, char *message)
{
	printf("%s(%d) : error : ' %s ' : %s\n",flist[fidx].name,flist[fidx].lnum,sym,message);
	numErrors++;
	if(numErrors > MAX_NUM_OF_ERRORS)
	{
		while( pop_file() );
		prit_end();
		exit(1);
	}
}

void print_w( char *sym, char *message)
{
	printf("%s(%d) : warning : ' %s ' : %s\n",flist[fidx].name,flist[fidx].lnum,sym,message);
	numWarnings++;
}

void prit_end( void )
{
	printf( "\nEnd  compilling -  %d error(s), %d warning(s)\n",  numErrors,numWarnings  );
}