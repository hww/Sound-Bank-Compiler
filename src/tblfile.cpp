/*****************************************************************************
 * @project SndSynt
 * @info Sound Bank Compiler
 * @platform DSP
 * @autor Valery P. (https://github.com/hww)
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ultratypes.h"
#include "main.h"

FILE *ftbl;
unsigned int tblpos;

// Open file and push it to the stack
int opent_tbl( )
{
    tblpos=0;
    if((ftbl = fopen( "tone.tbl" , "wb")) == NULL  )
    {
        printf("Can't create TBL file\n");
        return 0;
    }
    return 1;
}

 // Save wave to the output file
int write_tbl( char *ptr, unsigned int size)
{
#ifdef  MOST_SIGN_ORDER
    _swab( ptr, ptr, size );
#endif
    if( fwrite( ptr, size, 1, ftbl ) == 0)
    {
        return 0;
    }
    tblpos+=size;
    return 1;
}

 // Close file and pop it from stack
int close_tbl( )
{
    fclose( ftbl);
    return 1;
}