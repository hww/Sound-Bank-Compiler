/*****************************************************************************
 * @project SndSynt
 * @info Sound Bank Compiler
 * @platform DSP
 * @autor Valery P. (https://github.com/hww)
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "ultratypes.h"
#include "main.h"

void main( int argc, char *argv[ ], char *envp[ ]  )
{
    printf("----------------------------------\n\n");
    printf("\nCompiller Instruments Bank Files\n");
    printf("REMIS lab\n");
    printf("Valery P. (https://github.com/hww)\n");
    printf("----------------------------------\n\n");
/*
#ifdef MOST_SIGN_ORDER
    printf("       MOST SIGNIFICATE ORDER                  \n");
#else
    printf("       LAST SIGNIFICATE ORDER                  \n");
#endif

#ifdef  CTL_PTR_16_BIT
    printf("       CTL POINTERS 16 BITS                    \n");
#else
    printf("       CTL POINTERS 32 BITS                    \n");
#endif

#ifdef  WIDE_CHAR
    printf("       WIDE CHAR MODE ON                       \n");
#else
    printf("       8 BITS CHAR MODE ON                     \n");
#endif

#ifdef  WORD_ALIGNED
    printf("       WORD ALIGNED ON                         \n\n");
#else
    printf("       BYTE ALIGNED                            \n\n");
#endif
*/
    if(argc<2)
    {   printf("No name of file INS\n");
        exit(1);
    }
 
    // Create file list
    flist = (tfilelist*) malloc( MAX_FILES * sizeof(tfilelist));
    fidx = 0;

    if( flist == NULL )
    {
        printf("Cant allocate %d memory for filenames\n", MAX_FILES * sizeof(tfilelist) );
        exit(1);
    }
    else memset( flist, 0, MAX_FILES * sizeof(tfilelist) );

    // Crate CTL file
    ctl = (char *)malloc( MAX_CTL_SIZE );
    if( ctl == NULL ) {
        printf("Cant allocate %d memory for .CTL file\n", MAX_CTL_SIZE );
        exit(1);
    }
    else {
        memset( ctl, 0, MAX_CTL_SIZE );
    }
    
    // Create symbol list file
    listidx=0;
    list = (tlist*)malloc( MAX_LIST_SIZE * sizeof(tlist) );

    if( list == NULL ) {
        printf("Cant allocate %d memory for .CTL file\n", MAX_LIST_SIZE * sizeof(tlist) );
        exit(1);
    }
    else {
        memset( list, 0, MAX_LIST_SIZE * sizeof(tlist) );
    }
    
    printf("Compilling...\n\n");

    if(push_file( argv[1] ) == 0 ) {
        printf("Can't open file: tone.ins\n");
        exit(1);
    }
    opent_tbl();
    compille_file();
    close_tbl( );
    write_ctl();
    save_list();
    prit_end( );
    exit(1);
}

