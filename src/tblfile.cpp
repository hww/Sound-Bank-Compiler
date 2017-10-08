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

	������� ���� � ��������� ��� � ����

 **********************************************************/

int opent_tbl( )
{
	
	tblpos=0;					// � ������ �����

	if((ftbl = fopen( "tone.tbl" , "wb")) == NULL  )
	{
		printf("Can't create TBL file\n"); 
		return 0;								// �� �����
	}
	return 1;									// �� ��
}

/**********************************************************

	�������� � �������� ���� �����

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

	������� ���� � ������� ��� �� �����

 **********************************************************/

int close_tbl( )
{

	fclose( ftbl);								// ������� ���
	
	return 1;
}