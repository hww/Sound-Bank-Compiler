/*****************************************************************************
 * @project SndSynt
 * @info Sound Bank Compiler
 * @platform DSP
 * @autor Valery P. (https://github.com/hww)
 *****************************************************************************/

#ifndef __WAVH_H
#define __WAVH_H

int LoadWav(char *filename);
int deleteWav( void );

typedef struct {
    ULONG dwIdentifier;
    ULONG dwType;
    ULONG dwStart;
    ULONG dwEnd;
    ULONG dwFraction;
    ULONG dwPlayCount;
} SampleLoop;

// dwType field of SAMPLE LOOP
#define FORWARD  0  // Loop forward (normal)
#define PINGPONG 1  // Alternating loop (forward/backward)
#define BACKWARD 2  // Loop backward

typedef struct WAV{
    char  rID[4];
    ULONG rLen;
    char  wID[4];
    char  fID[4];
    ULONG fLen;
    UWORD wFormatTag;
    UWORD nChannels;
    ULONG nSamplesPerSec;
    ULONG nAvgBytesPerSec;
    UWORD nBlockAlign;
    UWORD nFormatSpecific;
    char  dID[4];
    ULONG dSize;
    char  *handle;              // pointer to sample in the TBL
    char  sID[4];
    ULONG sSize;
    ULONG dwManufacturer;       // This is Sample Data
    ULONG dwProduct;
    ULONG dwSamplePeriod;
    ULONG dwMIDIUnityNote;
    ULONG dwMIDIPitchFraction;
    ULONG dwSMPTEFormat;
    ULONG dwSMPTEOffset;
    ULONG cSampleLoops;
    ULONG cbSamplerData;
    SampleLoop Loops[2];
} WAV;

extern WAV wh;

#endif