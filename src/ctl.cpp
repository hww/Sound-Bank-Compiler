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

void write_ctl(void)
{
    FILE *f;
    if(pos)
    {
        if((f=fopen("tone.ctl","wb")) == NULL)
        {
            printf("Can't create CTL file\n");
            return;
        }
        if(fwrite( ctl,pos,1,f) == 0) printf("Can't write CTL file\n");
        fclose(f);
    }
    else printf("CTL size is 0 bytes\n");
}
