/*****************************************************************************
 * @project SndSynt
 * @info Sound Bank Compiler
 * @platform DSP
 * @autor Valery P. (https://github.com/hww)
 *****************************************************************************/

#ifndef __MMIO_H
#define __MMIO_H

#define _mm_rewind(x) _mm_fseek(x,0,SEEK_SET)
int  _mm_fseek(FILE *stream,long offset,int whence);
void _mm_setiobase(long iobase);
long _mm_ftell(FILE *stream);

extern SBYTE  _mm_read_SBYTE   (FILE *fp);
extern UBYTE _mm_read_UBYTE  (FILE *fp);

extern SWORD  _mm_read_M_SWORD (FILE *fp);
extern SWORD  _mm_read_I_SWORD (FILE *fp);

extern UWORD _mm_read_M_UWORD(FILE *fp);
extern UWORD _mm_read_I_UWORD(FILE *fp);

extern SLONG  _mm_read_M_SLONG (FILE *fp);
extern SLONG  _mm_read_I_SLONG (FILE *fp);

extern ULONG _mm_read_M_ULONG(FILE *fp);
extern ULONG _mm_read_I_ULONG(FILE *fp);

extern int _mm_read_str(char *str, int size, FILE *fp);

extern int _mm_read_SBYTES    (SBYTE  *buffer, int number, FILE *fp);
extern int _mm_read_UBYTES   (UBYTE *buffer, int number, FILE *fp);

extern int _mm_read_M_SWORDS  (SWORD  *buffer, int number, FILE *fp);
extern int _mm_read_I_SWORDS  (SWORD  *buffer, int number, FILE *fp);

extern int _mm_read_M_UWORDS (UWORD *buffer, int number, FILE *fp);
extern int _mm_read_I_UWORDS (UWORD *buffer, int number, FILE *fp);

extern int _mm_read_M_SLONGS  (SLONG  *buffer, int number, FILE *fp);
extern int _mm_read_I_SLONGS  (SLONG  *buffer, int number, FILE *fp);

extern int _mm_read_M_ULONGS (ULONG *buffer, int number, FILE *fp);
extern int _mm_read_I_ULONGS (ULONG *buffer, int number, FILE *fp);

extern void _mm_write_SBYTE     (SBYTE data,FILE *fp);
extern void _mm_write_UBYTE     (UBYTE data,FILE *fp);

extern void _mm_write_M_SWORD   (SWORD data,FILE *fp);
extern void _mm_write_I_SWORD   (SWORD data,FILE *fp);

extern void _mm_write_M_UWORD   (UWORD data,FILE *fp);
extern void _mm_write_I_UWORD   (UWORD data,FILE *fp);

extern void _mm_write_M_SLONG   (SLONG data,FILE *fp);
extern void _mm_write_I_SLONG   (SLONG data,FILE *fp);

extern void _mm_write_M_ULONG   (ULONG data,FILE *fp);
extern void _mm_write_I_ULONG   (ULONG data,FILE *fp);

extern void _mm_write_SBYTES        (SBYTE *data,  int number,FILE *fp);
extern void _mm_write_UBYTES    (UBYTE *data, int number,FILE *fp);

extern void _mm_write_M_SWORDS  (SWORD *data,  int number,FILE *fp);
extern void _mm_write_I_SWORDS  (SWORD *data,  int number,FILE *fp);

extern void _mm_write_M_UWORDS  (UWORD *data, int number,FILE *fp);
extern void _mm_write_I_UWORDS  (UWORD *data, int number,FILE *fp);

extern void _mm_write_M_SLONGS  (SLONG *data,  int number,FILE *fp);
extern void _mm_write_I_SLONGS  (SLONG *data,  int number,FILE *fp);

extern void _mm_write_M_ULONGS  (ULONG *data, int number,FILE *fp);
extern void _mm_write_I_ULONGS  (ULONG *data, int number,FILE *fp);

#endif // __MMIO_H