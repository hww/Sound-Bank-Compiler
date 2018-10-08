/*****************************************************************************
 * @project SndSynt
 * @info Sound Bank Compiler
 * @platform DSP
 * @autor Valery P. (https://github.com/hww)
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "ultratypes.h"
#include "main.h"

// Get single line with arguments
int get_params( char *par1, char  *par2 , char *par3)
{
    int parnum;                     // Number of arguments in line
    char oneln[MAX_LINE_LENGH+3];   // Single input line

loop:
    if( fgets( oneln, MAX_LINE_LENGH, flist[fidx].f ) != NULL)
    {
        flist[fidx].lnum++;  // count line number
        char *si = _strlwr( _strdup( oneln  ) );
        parnum = sscanf( si, "%s %s %s", par1, par2, par3 );
        if (parnum < 0) goto loop;   // empty line

        switch(parnum)
        {
        case 0:
            goto loop;  // empty line
            break;
        case 1:
            if ( *par1 == 0x27 ) goto loop;   
            break;
        case 2:
            if ( *par1 == 0x27 ) goto loop;   
            if ( *par2 == 0x27 ) parnum = 1;  
            break;
        case 3:
            if ( *par1 == 0x27 ) goto loop;   
            if ( *par3 == 0x27 ) parnum = 2;  
            if ( *par2 == 0x27 ) parnum = 1;  
            break;
        }

        if(parnum==1)
        {
            if( strcmp( par1, "end")==0) return 1;
            if( strcmp( par1, "waves")==0) return 1;
            print_e( par1,"Only one parameter found" );
        }

        if(parnum==3)
        {
            if( strcmp( par1, "p")==0) return 1;
            if( strcmp( par1, "sustain")==0) return 1;
            if( strcmp( par1, "loop")==0) return 1;
            if( strcmp( par1, "velminmax")==0) return 1;
            if( strcmp( par1, "region")==0) return 1;
            if( strcmp( par1, "wave")==0) return 1;
            if( strcmp( par1, "instrument")==0) return 1;
            print_e( par1,"Too more parameter found" );
        }

        if( strcmp( par1, "#include" ) == 0 )
        {
            if( push_file(par2) ) goto loop;
            else
            {
                print_e( par2,"Can't include file" );
                goto loop;
            }
        }

        return 1; // success
    }
    else
    {
        if(pop_file()) goto loop; // success then scan next file
        else return 0; // terminate with error
    }
}