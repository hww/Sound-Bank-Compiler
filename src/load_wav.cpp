/**********************************************************

	Sound Bank Compiller

 **********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ultratypes.h"
#include "tdefs.h"
#include "mmio.h"
#include "main.h"
#include "wav.h"
 
/**********************************************************

 Name:  LOAD_WAV.C

 Description:
 WAV Streaming Audio Loader / Player

 Portability:
 All compilers -- All systems (hopefully)

 **********************************************************/

WAV wh;

/**********************************************************
	Загрузка Семпла
 **********************************************************/

int LoadWavFP(FILE *fp)
{
	/* read wav header */

						_mm_read_str(wh.rID,4,fp);	//RIFF
	wh.rLen=			_mm_read_I_ULONG(fp);		//Size of  FILE
						_mm_read_str(wh.wID,4,fp);	//WAVE

	if( feof(fp) || memcmp(wh.rID,"RIFF",4) || memcmp(wh.wID,"WAVE",4))
	{
		print_e(" ", "Not a WAV file");
		return NULL;
	}

frmt_search:
						_mm_read_str(wh.fID,4,fp);	//frmt
	wh.fLen=			_mm_read_I_ULONG(fp);		//size of 'frmt'

	if(feof(fp))
	{
		return NULL;
		print_e(" ", "Wave file EOF was found but FRMT not !");
	}

	if(memcmp(wh.fID,"fmt ",4))
	{
		_mm_fseek(fp,wh.fLen,SEEK_CUR);
		goto frmt_search;
	}
	
	wh.wFormatTag=		_mm_read_I_UWORD(fp);		//0 1
	wh.nChannels=		_mm_read_I_UWORD(fp);		//2 3
	wh.nSamplesPerSec=	_mm_read_I_ULONG(fp);		//4 5 6  7
	wh.nAvgBytesPerSec=	_mm_read_I_ULONG(fp);		//8 9 10 11
	wh.nBlockAlign=		_mm_read_I_UWORD(fp);		//12 13
	wh.nFormatSpecific=	_mm_read_I_UWORD(fp);		//14 15

	/* skip other crap */

	_mm_fseek(fp,wh.fLen-16,SEEK_CUR);

	if(wh.nChannels>1)
	{
		print_e(" ","Only mono WAV's are supported");
		return NULL;
	}

data_search:

	if(feof(fp))
	{
		return NULL;
		print_e(" ", "Wave file EOF was found but FRMT not !");
	}

    _mm_read_str(wh.dID,4,fp);							// 'data'
	wh.dSize=_mm_read_I_ULONG(fp);						// size of 'data'

	if( memcmp(wh.dID,"data",4) ){
		_mm_fseek(fp,wh.dSize,SEEK_CUR);
		goto data_search;
	}

    if((wh.handle = (char*)calloc(1,wh.dSize))==NULL){
		printf("Can't alocate memory for sample\n");
		return NULL;
	};
	
	if( fread( wh.handle, wh.dSize, 1, fp) == 0){		// Прочитали данные
		free(wh.handle);
		printf("File EOF found, but DATA was not readed !\n");
		return 0;
	}

loop:

	if( feof(fp) ){
		free(wh.handle);
		printf("File EOF found, but SMPL chunk was not!\n");
		return NULL;
	}

				 _mm_read_str(wh.sID,4,fp);			// Имя чанка
	wh.sSize	=_mm_read_I_ULONG(fp);				// размер

	if( memcmp(wh.sID,"smpl",4) ){
		/* skip other crap */

		_mm_fseek(fp,wh.sSize,SEEK_CUR);
		goto loop;
	}

	// There is we found sample chunk

	wh.dwManufacturer			=_mm_read_I_ULONG(fp);
	wh.dwProduct				=_mm_read_I_ULONG(fp);
	wh.dwSamplePeriod			=_mm_read_I_ULONG(fp);
	wh.dwMIDIUnityNote			=_mm_read_I_ULONG(fp);
	wh.dwMIDIPitchFraction		=_mm_read_I_ULONG(fp);
	wh.dwSMPTEFormat			=_mm_read_I_ULONG(fp);
	wh.dwSMPTEOffset			=_mm_read_I_ULONG(fp);
	wh.cSampleLoops				=_mm_read_I_ULONG(fp);
	wh.cbSamplerData			=_mm_read_I_ULONG(fp);

	for( unsigned char n=0; n<wh.cSampleLoops; n++)
	{
		wh.Loops[n].dwIdentifier	=_mm_read_I_ULONG(fp);
		wh.Loops[n].dwType			=_mm_read_I_ULONG(fp);
		wh.Loops[n].dwStart			=_mm_read_I_ULONG(fp);
		wh.Loops[n].dwEnd			=_mm_read_I_ULONG(fp);
		wh.Loops[n].dwFraction		=_mm_read_I_ULONG(fp);
		wh.Loops[n].dwPlayCount		=_mm_read_I_ULONG(fp);
	}

	// There is all wave will be loaded

	return 1;
}

/**********************************************************
	Загрузка семпла семпла
 **********************************************************/

int LoadWav(char *filename)
{
	FILE *fp;

	if((fp=fopen(filename,"rb"))==NULL){
		printf("Couldn't open wav file\n");
		return NULL;
	}

	if(LoadWavFP(fp))
	{

		fclose(fp);
		return 1;
	}
	else
	{
		fclose(fp);
		return 0;
	}
}

int deleteWav()
{
	delete( wh.handle);
	return 1;
}