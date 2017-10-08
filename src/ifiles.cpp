/**********************************************************

	Sound Bank Compiller

 **********************************************************/

#include <stdio.h>
#include <string.h>

#include "ultratypes.h"
#include "main.h"

tfilelist *flist;
unsigned long fidx;								// ��������� �� ����

/**********************************************************

	������� ���� � ��������� ��� � ����

 **********************************************************/

int push_file( char *name )
{

FILE *f;

	if(fidx>=MAX_FILES)
	{
		printf("Too more number of files\n");
		return 0;
	}

	if((f = fopen( name , "r")) != NULL  )
	{
		printf("%s\n", name);
		
		fidx++;
		strcpy( flist[fidx].name, name);	// ��� ���
		flist[fidx].lnum=0;						// ����� ������ 0
		flist[fidx].f = f;
		
		return 1;								// �� ��
	}
	else return 0;								// �� �����
}

/**********************************************************

	������� ���� � ������� ��� �� �����

 **********************************************************/

int pop_file( )
{
	
	if(fidx == 0) return 0;						// ��� ������
	fclose( flist[fidx--].f );					// ���� � ������� ���
	if(fidx == 0) return 0;						// ��� ������
	return 1;
}