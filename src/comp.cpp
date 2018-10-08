/*****************************************************************************
 * @project SndSynt
 * @info Sound Bank Compiler
 * @platform DSP
 * @autor Valery P. (https://github.com/hww)
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "tdefs.h"
#include "ultratypes.h"
#include "main.h"
#include "libaudio.h"
#include "wav.h"

char var[VAR_NAME_SIZE];
char val[VAR_NAME_SIZE];
char val1[VAR_NAME_SIZE];
char *ctl;
_int32 pos;

#define CURPTR ((unsigned long)ctl + pos)
#define NEXT(x) pos+=x; \
        if((pos & 3) !=0) pos = (pos | 3)+1;

short bankCount;  // quantity of banks
int   envdiv;     // divider of time in MKS to have ticks of envelope

/*****************************************************************************
 * BANK_FILE
 *****************************************************************************/

void add_bankfile(void)
{
    ALBankFile *p;
    p = (ALBankFile*) CURPTR;
#ifdef DSP56
    p->ctl_size     = U32((unsigned long)0);
    p->tbl_size     = U32((unsigned long)0);
#endif
    p->revision     = S16((unsigned short)(('B'<<8) + '2'));
    p->bankCount    = S16(1);
    NEXT(sizeof(ALBankFile));
}

/*****************************************************************************
 * ENVELOPE NEW TYPE, TABLE WITH VARIABLE LEN
 *****************************************************************************/

void add_envelope_table(char *val )
{
    ALEnvelopeTable *p;
    int pointnum = 0;
    p = (ALEnvelopeTable*) CURPTR;
    add_2_list( ENVELOPE, val, pos);
    NEXT(sizeof(ALEnvelopeTable));

    p->type         =   S16(0);
    p->sustaneStart =   S16(0);
    p->sustaneEnd   =   S16(0);
    p->loopStart    =   S16(0);
    p->loopEnd      =   S16(0);
    p->pointCount   =   S16(0);
loop:
    if(get_params(var,val,val1) == 0)
        return;

    if  (IS("sustain")) {
        p->type |= U16(AL_ENV_SUSTANE);
        p->sustaneStart = VU16;
        p->sustaneEnd   = VU161;
    }
    else if (IS("loop")) {
        p->type |= U16(AL_ENV_LOOP);
        p->loopStart    = VU16;
        p->loopEnd      = VU161;
    }
    else if (IS("p")) {
        p->pointArray[pointnum].val  = VUC;
        p->pointArray[pointnum].time = VS161;
        pointnum++;
        NEXT(sizeof(s32));
    }
    else if (IS("end")) {
        p->pointCount   =   U16(pointnum);
        return;
    }
    else {
        print_e( var,"not valid parameter for this object");
    }
    goto loop;
}

/*****************************************************************************
 * KEYMAP
 *****************************************************************************/

void add_keymap(char *val )
{
    ALKeyMap *p;
    p = (ALKeyMap*) CURPTR;
    add_2_list( KEYMAP, val, pos );
    NEXT(sizeof(ALKeyMap));

    p->velocityMin  =   UC(1);
    p->velocityMax  =   UC(127);
    p->keyMin       =   UC(0);
    p->keyMax       =   UC(127);
    p->keyBase      =   UC(60);
    p->detune       =   SC(0);
loop:
    if(get_params(var,val,val1) == 0) return;

    if (IS("velminmax")) {
        p->velocityMin = VUC;
         p->velocityMax = VUC1;
    }
    else if (IS("region")) {
        p->keyMin = VN;
        p->keyMax = VN1;
    }
    else if (IS("keybase"))     p->keyBase      = VN;
    else if (IS("detune"))      p->detune       = VSC;
    else if (IS("end"))         return;
    else print_e( var,"not valid parameter for this object");
    goto loop;
}

/*****************************************************************************
 * Add wave object
 *****************************************************************************/

void add_wave(char *val )
{
    ALWaveTable *p;
    loop:

    if(get_params(var,val,val1) == 0) return;

    if (IS("end")) {
        return;
    }
    else if(IS("wave")) {
        p = (ALWaveTable*) CURPTR;
        add_2_list( WAVE, val, pos );
        NEXT(sizeof(ALWaveTable));

        if(LoadWav(val1))
        {   p->base = U32(tblpos);                  /* ptr to start of wave data    */
            if(write_tbl( wh.handle, wh.dSize)) {
            deleteWav();
                p->len      = S32(wh.dSize);        /* length of data in bytes      */
                p->type     = UC(AL_RAW_WAVE);      /* compression type             */
                p->rate     = U16(wh.nSamplesPerSec);
                if(wh.cSampleLoops > 0)
                {   p->ltype = U16(AL_SF_LOOP);
                    p->start = U32(wh.Loops[0].dwStart);
                    p->end   = U32(wh.Loops[0].dwEnd);
                    p->count = U32(wh.Loops[0].dwPlayCount);
                }
                else
                {   p->ltype = U16(0);
                    p->start = U32(0);
                    p->end   = U32(0);
                    p->count = U32(0);
                }
            }
            else {
                print_e( val, "Can't write DATA to tbl file");
            }
        }
    }
    else {
        print_e( var,"not valid parameter for SOUND object");
    }
    goto loop;
}

/*****************************************************************************
 * Add sound object
 *****************************************************************************/

void add_sound(char *val )
{
    ALSound *p;
    char name[VAR_NAME_SIZE];
    strcpy( name, val );
    p = (ALSound*) CURPTR;
    add_2_list( SOUND, val, pos );
    NEXT(sizeof(ALSound));
    p->samplePan    = SC(AL_PAN_CENTER);
    p->sampleVolume = UC(AL_VOL_FULL);
    p->venvelope    = 0;
    p->penvelope    = 0;
    p->flags        = UC(0);
    p->sampleFadeout= S16(0);
loop:
    if(get_params(var,val,val1) == 0) 
        return;

    if (IS("venvelope")) {
        p->flags       |= UC(AL_ENV_VOL);
        p->venvelope    = PTR((ALEnvelopeTable *)VPTCTL(ENVELOPE));
    }
    else if (IS("penvelope")) {
        p->flags       |= UC(AL_ENV_PAN);
        p->penvelope    = PTR((ALEnvelopeTable *)VPTCTL(ENVELOPE));
    }
    else if (IS("keymap")) {
        p->keyMap       = PTR((ALKeyMap*)   VPTCTL(KEYMAP));
    }
    else if (IS("use")) {
        p->wavetable    = PTR((ALWaveTable*)VPTCTL(WAVE));
    }
    else if (IS("pan")) {
        p->samplePan    = VPAN;
    }
    else if (IS("volume")) {
        p->sampleVolume = VUC;
    }
    else if (IS("fadeout")) {
        p->sampleFadeout= VS16;
    }
    else if (IS("end")) {
        if(p->keyMap    == 0)   print_e(name,"Object have no keyMap");
        if(p->wavetable == 0)   print_e(name,"Object have no WaveTable");
        return;
    }
    else {
        print_e( var,"not valid parameter for SOUND object");
    }
    goto loop;
}

/*****************************************************************************
 * Add instrument object
 *****************************************************************************/

void add_instrument(char *val )
{
    ALInstrument *p;
    short sndnum =0 ;
    char name[VAR_NAME_SIZE];

    strcpy( name, val );
    p = (ALInstrument*) CURPTR;
    add_2_list( INSTRUMENT, val, pos);
    NEXT(sizeof(ALInstrument));

    p->volume   =UC(AL_VOL_FULL);   /* overall volume for this instrument   */
    p->pan      =SC(AL_PAN_CENTER); /* 0 = hard left, 127 = hard right      */
    p->priority =SC(5);             /* voice priority for this instrument   */
    p->flags    =0;
    p->soundCount=0;                /* number of sounds in this array       */
    p->bendRange=S16(200);          /* pitch bend range in cents            */
//    p->tremType   =0;               /* the type of tremelo osc. to use      */
//    p->tremRate   =0;               /* the rate of the tremelo osc.         */
//    p->tremDepth=0;                 /* the depth of the tremelo osc         */
//    p->tremDelay=0;                 /* the delay for the tremelo osc        */
    p->vibType  =0;                 /* the type of tremelo osc. to use      */
    p->vibRate  =0;                 /* the rate of the tremelo osc.         */
    p->vibDepth =0;                 /* the depth of the tremelo osc         */
    p->vibDelay =0;                 /* the delay for the tremelo osc        */
loop:
    if(get_params(var,val,val1) == 0) 
        return;

         if (IS("volume"))      p->volume       =VUC;
    else if (IS("pan"))         p->pan          =VPAN;
    else if (IS("priority"))    p->priority     =VUC;
//  else if (IS("tremtype"))    p->tremType     =VUC;
//  else if (IS("tremrate"))    p->tremRate     =VUC;
//  else if (IS("tremdepth"))   p->tremDepth    =VUC;
//  else if (IS("tremdelay"))   p->tremDelay    =VUC;
    else if (IS("vibtype"))     p->vibType      =VUC;
    else if (IS("vibrate"))     p->vibRate      =VUC;
    else if (IS("vibdepth"))    p->vibDepth     =VUC;
    else if (IS("vibdelay"))    p->vibDelay     =VUC;
    else if (IS("bendrange"))   p->bendRange    =VUC;
    else if (IS("sound")) {
        p->soundArray[sndnum++] = PTR((ALSound*)VPTCTL(SOUND));
        NEXT(sizeof(pctl));
    }
    else if (IS("end")) {
        p->soundCount = S16(sndnum);
        if(p->soundCount == 0)  print_e(name,"Object have no Sound");
        return;
    }
    else    print_e( var,"not valid parameter for INSTRUMENT object");

    goto loop;
}

/*****************************************************************************
 * Add sound bank object
 *****************************************************************************/

void add_bank(char *val )
{
    ALBank *p;
    ALBankFile *bf;
    int maxins = 0;
    int ins;

    bf = (ALBankFile*)ctl;
    bf->bankArray[0] = PTR((ALBank*)PTCTL(pos));

    p = (ALBank*)CURPTR;
    add_2_list( BANK, val, pos );
    NEXT(sizeof(ALBank));

    p->instCount = 0;       /* number of programs in this bank */
    p->flags = 0;

loop:

    if(get_params(var,val,val1) == 0)
        return;

    if  (IS("percussion")) {
        p->percussion = PTR((ALInstrument*)VPTCTL(INSTRUMENT));
    }
    else if (IS("instrument")) {
        ins = s16val(val);
        if(maxins < ins)
        {
            NEXT((ins-maxins) * sizeof(pctl));
            for(;maxins<ins;maxins++)
                p->instArray[ins] = 0;
        }
        p->instArray[ins] = PTR((ALInstrument*)VPTCTL1(INSTRUMENT));
    }
    else if (IS("end")) {
        p->instCount = S16(maxins+1);
        return;
    }
    else {
        print_e( var,"not valid parameter for BANK object");
    }
    goto loop;
}

/*****************************************************************************
 * Compile file
 *****************************************************************************/

void compille_file( void )
{
    ALBankFile *bf;
    pos = 0; // start of ctl
    bankCount = 0;
    add_bankfile();
loop:
    if( get_params( var, val, val1 ) == 0) {
#ifdef DSP56
        bf = (ALBankFile*)ctl;
        bf->ctl_size = U32(pos-8);
        bf->tbl_size = U32(tblpos);
#endif
        return;
    }
         if ( IS("bank")       )    add_bank(val);
    else if ( IS("waves")       )   add_wave(val);
    else if ( IS("instrument") )    add_instrument(val);
    else if ( IS("sound")      )    add_sound(val);
    else if ( IS("keymap")     )    add_keymap(val);
    else if ( IS("envelope")   )    add_envelope_table(val);
    else print_e( var,"found keyword but not found begin of object");
    goto loop;
}