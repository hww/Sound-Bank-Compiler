/*****************************************************************************
 * @project SndSynt
 * @info Sound synthesizer library and MIDI file player.
 * @platform DSP
 * @autor Valery P. (https://github.com/hww)
 *****************************************************************************/
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

#ifndef __LIBAUDIO_H
#define __LIBAUDIO_H

#include "ultratypes.h"

/* ADPCM State */
#define ADPCMVSIZE  8
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
#define AL_DEFAULT_FXMIX    0
#define AL_SUSTAIN      63

/*****************************************************************************
* Waveform flags
*****************************************************************************/

#define AL_SF_LOOP      0x0001  // ha sloop
#define AL_SF_ACTIVE    0x0010  // is active

/*****************************************************************************
* Sound's flags
*****************************************************************************/

#define AL_ENV_SUSTANE  0x0100  // has sustain
#define AL_ENV_LOOP     0x0200  // has loop
#define AL_ENV_VOL      0x0400  // has volume envelope
#define AL_ENV_PAN      0x0800  // has pan envelope
#define AL_ENV_VOL_OLD  0x1000  // version of envelope
#define AL_INDEXED      0x8000  // indexing for memory relocation

/*****************************************************************************
 * data structures for sound banks
 *****************************************************************************/

#define AL_BANK_VERSION    'B2'

/* Possible wave table types */
enum    {AL_BRR_WAVE = 0,
         AL_RAW_WAVE,
};

typedef struct {
    s16         type;
    s16         sustaneStart;
    s16         sustaneEnd;
    s16         loopStart;
    s16         loopEnd;
    s16         pointCount;
    struct
    {   s16     val;
        s16     time;
    }           pointArray[1];
} ALEnvelopeTable;

typedef struct {
    u8          velocityMin;
    u8          velocityMax;
    u8          keyMin;
    u8          keyMax;
    u8          keyBase;
    s8          detune;
} ALKeyMap;

typedef struct ALWaveTable_s {
    u32         base;           /* ptr to start of wave data    */
    u32         len;            /* length of data in bytes      */
    u16         type;           /* compression type             */
    u16         flags;          /* offset/address flags         */
    u16         rate;
    u16         ltype;
    u32         start;
    u32         end;
    u32         count;
} ALWaveTable;

typedef struct ALSound_s {
    u16         venvelope;
    u16         penvelope;
    u16         keyMap;
    u16         wavetable;     /* offset to wavetable struct           */
    ALPan       samplePan;
    u8          sampleVolume;
    s16         sampleFadeout;
    u8          flags;
} ALSound;

typedef struct {
    u8          volume;         /* overall volume for this instrument   */
    ALPan       pan;            /* 0 = hard left, 127 = hard right      */
    u8          priority;       /* voice priority for this instrument   */
    u8          flags;
//    u8          tremType;       /* the type of tremelo osc. to use      */
//    u8          tremRate;       /* the rate of the tremelo osc.         */
//    u8          tremDepth;      /* the depth of the tremelo osc         */
//    u8          tremDelay;      /* the delay for the tremelo osc        */
    u8          vibType;        /* the type of tremelo osc. to use      */
    u8          vibRate;        /* the rate of the tremelo osc.         */
    u8          vibDepth;       /* the depth of the tremelo osc         */
    u8          vibDelay;       /* the delay for the tremelo osc        */
    s16         bendRange;      /* pitch bend range in cents            */
    s16         soundCount;     /* number of sounds in this array       */
    u16         soundArray[1];
} ALInstrument;

typedef struct ALBank_s {
    s16         instCount;      /* number of programs in this bank */
    u16         flags;
    u16         percussion;     /* default percussion for GM       */
    u16         instArray[1];   /* ARRAY of instruments            */
} ALBank;

typedef struct {                /* Note: sizeof won't be correct */
    u32         ctl_size;
    u32         tbl_size;
    s16         revision;       /* format revision of this file         */
    s16         bankCount;      /* number of banks                      */
    u16         bankArray[1];   /* ARRAY of bank offsets                */
} ALBankFile;

#endif // __LIBAUDIO_H



