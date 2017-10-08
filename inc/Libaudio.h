/*====================================================================
 * libaudio.h
 *
 * Copyright 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/


#include "ultratypes.h"

/*
 * ADPCM State
 */
#define ADPCMVSIZE	8
#define ADPCMFSIZE      16
typedef short ADPCM_STATE[ADPCMFSIZE];

typedef s32     ALMicroTime;
typedef u8      ALPan;    

#define AL_FX_BUFFER_SIZE       8192
#define AL_FRAME_INIT           -1
#define AL_USEC_PER_FRAME       16000
#define AL_MAX_PRIORITY         127
#define AL_GAIN_CHANGE_TIME     1000    
    
#define AL_PAN_CENTER   64
#define AL_PAN_LEFT     0
#define AL_PAN_RIGHT    127
#define AL_VOL_FULL     127
#define AL_KEY_MIN      0
#define AL_KEY_MAX      127
#define AL_DEFAULT_FXMIX	0
#define AL_SUSTAIN      63

/***********************************************************************
 * � ���������� ����� ����� ���� �����
 ***********************************************************************/

// ����� �����

#define AL_SF_LOOP      0x0001	// ����� ����� �����
#define AL_SF_ACTIVE    0x0010	// ��������� � �������� ���������

// ����� ������

#define AL_ENV_SUSTANE 	0x0100	// ��������� � ���������
#define AL_ENV_LOOP    	0x0200	// ��������� � �����
#define AL_ENV_VOL		0x0400	// ���� ��������� ���������
#define AL_ENV_PAN		0x0800	// ���� ��������� ��������
#define AL_ENV_VOL_OLD  0x1000  // ��������� ������� ����
#define AL_INDEXED	    0x8000	// ������  ����������������


/***********************************************************************
 * data structures for sound banks
 ***********************************************************************/


#define AL_BANK_VERSION    'B1'

/* Possible wavetable types */
enum    {AL_ADPCM_WAVE = 0,
         AL_RAW_WAVE,
};

typedef struct {
    s32 order;
    s32 npredictors;
    s16 book[1];        /* Actually variable size. Must be 8-byte aligned */
} ALADPCMBook;

typedef struct {
    u32         start;
    u32         end;
    u32         count;
    ADPCM_STATE state;
} ALADPCMloop;

typedef struct {
    u32         start;
    u32         end;
    u32         count;
} ALRawLoop;

typedef struct {
    ALMicroTime attackTime;
    ALMicroTime decayTime;
    ALMicroTime releaseTime;
    u8          attackVolume;
    u8          decayVolume;
} ALEnvelope;


typedef struct {
	s16			type;
	s16			sustaneStart;
	s16			sustaneEnd;
	s16			loopStart;
	s16			loopEnd;
	s16			pointCount;
	struct 
	{
		s16		val;
		s16		time;
	}			pointArray[1];
} ALEnvelopeTable;

typedef struct {
    u8          velocityMin;
    u8          velocityMax;
    u8          keyMin;
    u8          keyMax;
    u8          keyBase;
    s8          detune;
} ALKeyMap;

typedef struct {
#ifdef CTL_PTR_16_BIT
    u16			loop;
    u16			book;
#else
    ALADPCMloop *loop;
    ALADPCMBook *book;
#endif
} ALADPCMWaveInfo;

typedef struct {
#ifdef CTL_PTR_16_BIT
    u16		   loop;
#else
    ALRawLoop *loop;
#endif
} ALRAWWaveInfo;

typedef struct ALWaveTable_s {
    u32         base;           /* ptr to start of wave data    */
    s32         len;            /* length of data in bytes      */
    u8          type;           /* compression type             */
    u8          flags;          /* offset/address flags         */
    s16			pad;
	union {
        ALADPCMWaveInfo adpcmWave;
        ALRAWWaveInfo   rawWave;
    } waveInfo;
} ALWaveTable;

typedef struct ALSound_s {
#ifdef CTL_PTR_16_BIT
    u16			venvelope;
    u16			penvelope;
    u16			keyMap;
    u16			wavetable;     /* offset to wavetable struct           */
#else
    ALEnvelope  *envelope;
    ALKeyMap    *keyMap;
    ALWaveTable *wavetable;     /* offset to wavetable struct           */
#endif
    ALPan       samplePan;
    u8          sampleVolume;
	s16			sampleFadeout;
    u8          flags;
} ALSound;

typedef struct ALSound_s_ {
#ifdef CTL_PTR_16_BIT
    u16			envelope;
    u16			keyMap;
    u16			wavetable;     /* offset to wavetable struct           */
#else
    ALEnvelope  *envelope;
    ALKeyMap    *keyMap;
    ALWaveTable *wavetable;     /* offset to wavetable struct           */
#endif
    ALPan       samplePan;
    u8          sampleVolume;
    u8          flags;
} ALSound_;

typedef struct {
    u8          volume;         /* overall volume for this instrument   */
    ALPan       pan;            /* 0 = hard left, 127 = hard right      */
    u8          priority;       /* voice priority for this instrument   */
    u8          flags;
    u8          tremType;       /* the type of tremelo osc. to use      */
    u8          tremRate;       /* the rate of the tremelo osc.         */
    u8          tremDepth;      /* the depth of the tremelo osc         */
    u8          tremDelay;      /* the delay for the tremelo osc        */
    u8          vibType;        /* the type of tremelo osc. to use      */
    u8          vibRate;        /* the rate of the tremelo osc.         */
    u8          vibDepth;       /* the depth of the tremelo osc         */
    u8          vibDelay;       /* the delay for the tremelo osc        */
    s16         bendRange;      /* pitch bend range in cents            */
    s16         soundCount;     /* number of sounds in this array       */
#ifdef CTL_PTR_16_BIT
    u16			soundArray[1];
#else
    ALSound     *soundArray[1];
#endif
} ALInstrument;

typedef struct ALBank_s {
    s16                 instCount;      /* number of programs in this bank */
    u8                  flags;
#ifndef DSP56
    u8                  pad;
#endif
    s32                 sampleRate;     /* e.g. 44100, 22050, etc...       */
#ifdef CTL_PTR_16_BIT
    u16					percussion;    /* default percussion for GM       */
    u16					instArray[1];  /* ARRAY of instruments            */
#else
    ALInstrument        *percussion;    /* default percussion for GM       */
    ALInstrument        *instArray[1];  /* ARRAY of instruments            */
#endif
} ALBank;

typedef struct {                /* Note: sizeof won't be correct */
#ifdef DSP56
	u32			ctl_size;
	u32			tbl_size;
#endif
    s16         revision;       /* format revision of this file         */
    s16         bankCount;      /* number of banks                      */
#ifdef CTL_PTR_16_BIT
    u16			 bankArray[1];  /* ARRAY of bank offsets                */
#else
    ALBank      *bankArray[1];  /* ARRAY of bank offsets                */
#endif
} ALBankFile;





