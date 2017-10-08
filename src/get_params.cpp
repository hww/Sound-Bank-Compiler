/**********************************************************

	Sound Bank Compiller

 **********************************************************/

#include <stdio.h>
#include <string.h>

#include "ultratypes.h"
#include "main.h"

/**********************************************************
	Взять одну строку с параметрами
 **********************************************************/

int get_params( char *par1, char  *par2 , char *par3)
{

int parnum;						// Количество параметров в строке
char oneln[MAX_LINE_LENGH+3];		// Строка для ввода из файла


loop:
		if( fgets( oneln, MAX_LINE_LENGH, flist[fidx].f ) != NULL)
		{
			flist[fidx].lnum++;								// Номер строки увеличим
			char *si = _strlwr( _strdup( oneln  ) );
			parnum = sscanf( si, "%s %s %s", par1, par2, par3 );
			if (parnum < 0) goto loop;					// Пустая строка

			switch(parnum)
			{
			case 0:
				goto loop;								// Пустая строка
				break;
			case 1:
				if ( *par1 == 0x27 ) goto loop;			// коментарии
				break;
			case 2:
				if ( *par1 == 0x27 ) goto loop;				// коментарии
				if ( *par2 == 0x27 ) parnum = 1;			// коментарии
				break;
			case 3:
				if ( *par1 == 0x27 ) goto loop;				// коментарии
				if ( *par3 == 0x27 ) parnum = 2;			// коментарии
				if ( *par2 == 0x27 ) parnum = 1;			// коментарии
				break;
			}
		
			if(parnum==1) 
			{
				if( strcmp( par1, "end")==0) return 1;
				if( strcmp( par1, "wave")==0) return 1;
				print_e( par1,"Only one parameter found" );
			}
			
			if(parnum==3) 
			{
				if( strcmp( par1, "p")==0) return 1;
				if( strcmp( par1, "sustain")==0) return 1;
				if( strcmp( par1, "loop")==0) return 1;
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

			return 1;									// Нормальное завершение файла
		}
		else
		{
			if(pop_file()) goto loop;					// Если файл закрылся удачно то сканируем предыдущий
			else return 0;								// Если нет то выход с ошибкой
		}
}