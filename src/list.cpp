/**********************************************************

	Sound Bank Compiller

 **********************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "ultratypes.h"
#include "main.h"

tlist *list;
unsigned long listidx;

/**********************************************************
	Добавить запись в лист
 **********************************************************/

void add_2_list( char objtype, char *name, long val )
{
	if( listidx >= MAX_LIST_SIZE )
	{
		print_e(" ","SYM entries too more\n");
		while(pop_file());
		exit(1);
	}

	strcpy( list[listidx].name, name );	// Имя скопировали
	list[listidx].obj = objtype;		// Тип отмечен
	list[listidx].ptr = val;			// Значение установили
	listidx++;							// Следующая запись
}

/**********************************************************
	Найти запись в листе
 **********************************************************/

tlist *find_in_list( char objtype, char *name )
{
unsigned long idx=0;	

	while(idx < listidx)
	{
		if((objtype==list[idx].obj) && ( strcmp( name, list[idx].name)==0)) return &list[idx];
		idx++;
	}

	return 0;
}

/**********************************************************
	Записать лист в файл 
 **********************************************************/
unsigned char snop[]		={ "EMPTY" };
unsigned char sbfile[]		={ "BFILE" };
unsigned char sbank[]		={ "BANK " };
unsigned char sinstr[]		={ "INSTR" };
unsigned char ssound[]		={ "SOUND" };
unsigned char ssound_[]		={ "SOUN_" };
unsigned char skeymap[]		={ "KEYMP" };
unsigned char senvelope_[]	={ "ENVE_" };
unsigned char senvelope[]	={ "ENVEL" };
unsigned char swave[]		={ "WAVE " };

void save_list( void )
{
unsigned long idx=0;	
FILE *f;
unsigned char * type;

 	if(listidx)
	{
		if((f=fopen("tone.sym","wb")) == NULL)
		{
			printf("Can't create SYM file\n");
			return;
		}
		//fprintf( f,"REMIS, Omsk, 2002       \n" );
		fprintf( f,"Sound Bank SYM File    \n\n" );
		fprintf( f,"REMIS lab\n\n");	
		fprintf( f,"использовать только не для коммерческих целей \n\n");
		fprintf( f,"Address   Type   Name   \n" );
		fprintf( f,"---------------------------------------------\n" );
		while(idx < listidx)
		{	
			switch(list[idx].obj)
			{
			case NOP:			type = snop; break;
			case BFILE:			type = sbfile; break;
			case BANK:			type = sbank; break;
			case INSTRUMENT:	type = sinstr; break;
			case SOUND:			type = ssound; break;
			case SOUNDOLD:		type = ssound_; break;
			case KEYMAP:		type = skeymap; break;
			case ENVELOPEOLD:	type = senvelope_; break;
			case ENVELOPE:		type = senvelope; break;
			case WAVE:			type = swave; break;
			}
			if(fprintf( f,"%08Lx  %s  %s\n",list[idx].ptr, type,list[idx].name) < 0)	{ printf("Can't write LST file\n"); return ; }
			
			idx++;
		}
		fclose(f);			
	}
	else printf("LIST size is 0 records\n");

}


