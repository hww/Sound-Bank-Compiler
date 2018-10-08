/*****************************************************************************
* @project SndSynt
* @info Sound Bank Compiler
* @platform DSP
* @autor Valery P. (https://github.com/hww)
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "ultratypes.h"
#include "main.h"

// Count total errors and warnings
long numErrors, numWarnings;

// Error message
void print_e( char *sym, char *message)
{
	printf("%s(%d) : error : ' %s ' : %s\n", flist[fidx].name, flist[fidx].lnum, sym, message);
	numErrors++;
	if(numErrors > MAX_NUM_OF_ERRORS)
	{
		while( pop_file() );
		prit_end();
		exit(1);
	}
}

// Warning message
void print_w( char *sym, char *message)
{
	printf("%s(%d) : warning : ' %s ' : %s\n", flist[fidx].name, flist[fidx].lnum, sym, message);
	numWarnings++;
}

// Final message
void prit_end( void )
{
	printf( "\nEnd  compiling -  %d error(s), %d warning(s)\n",  numErrors, numWarnings  );
}