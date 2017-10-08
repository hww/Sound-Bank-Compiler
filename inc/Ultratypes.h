#ifndef _ULTRATYPES_H_
#define _ULTRATYPES_H_


/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/


/*************************************************************************
 *
 *  File: ultratypes.h
 *
 *  This file contains various types used in Ultra64 interfaces.
 *
 *  $Header: /mdev2/PR/include/RCS/ultratypes.h,v 1.4 1995/03/29 00:52:13 jeffd Exp $
 *
 */

/**********************************************************************
	Для изменения размерности
 */

#define DSP56
#define MOST_SIGN_ORDER
#define  CTL_PTR_16_BIT
#define  WIDE_CHAR
#define  WORD_ALIGNED

// Запакованые структуры

#pragma pack(1)

#ifdef CTL_PTR_16_BIT
#define PTR(x) (u16)((u32)x & 0xFFFF)
#else
#define PTR(x) x
#endif

typedef unsigned long  pctl;		/* pointer to ctl */
typedef unsigned long  ptbl;		/* pointer to tbl */

#ifdef MOST_SIGN_ORDER	// MOTOROLA FORMAT
#define _S8(x)	x	
#define _S16(x)	(short)short2msb((unsigned short)x)
#define _S32(x)	(long)long2msb((unsigned long)x)
#define _U8(x)	x
#define _U16(x)	short2msb((unsigned short)x)
#define _U32(x)	long2msb((unsigned long)x)
#else
#define _S8(x)	x	
#define _S16(x)	x
#define _S32(x)	x
#define _U8(x)	x
#define _U16(x)	x
#define _U32(x)	x
#endif

#ifdef CTL_PTR_16_BIT
#ifdef WORD_ALIGNED
#define PTCTL(x) _U16(x>>1)
#else
#define PTCTL(x) _U16(x)
#endif
#define MAX_CTL_PTR 0xFFFFL
#else
#define PTCTL(x) _U32(x)
#define MAX_CTL_PTR 0xFFFFFFL
#endif

#ifdef  WIDE_CHAR
#define SC(x)		_S16(x)
#define UC(x)		_U16(x)
#define _VSC(x)		_S16(s16val(x)) 
#define _VUC(x)		_U16(u16val(x)) 
#define _VN(x)		_U16(noteval(x)) 
#else
#define SC(x)		_S8(x)
#define UC(x)		_U8(x)
#define _VSC(x)		s8val(x) 
#define _VUC(x)		u8val(x) 
#define _VN(x)		noteval(x) 
#endif

#define S16(x)		_S16(x) 
#define S32(x)		_S32(x)
#define U16(x)		_U16(x)
#define U32(x)		_U32(x)

#define VN			_VN(val)
#define VSC			_VSC(val) 
#define VUC			_VUC(val) 
#define VS16		S16(s16val(val))
#define VS32		S32(s32val(val))
#define VU16		U16(u16val(val))
#define VU32		U32(u32val(val))
#define VPTCTL(x)   PTCTL(pctlval(x,val))



/**********************************************************************
 * General data types for R4300
 */
#ifdef WIDE_CHAR					// Символ два байта
typedef unsigned short			u8;		/* unsigned  16-bit */
typedef signed short			s8;		/* signed	 16-bit */
typedef volatile unsigned short	vu8;	/* unsigned  16-bit */
typedef volatile signed short	vs8;	/* signed	 16-bit */
#else								// Если символ один байт
typedef unsigned char			u8;		/* unsigned  8-bit */
typedef signed char				s8;		/* signed    8-bit */
typedef volatile unsigned char	vu8;	/* unsigned  8-bit */
typedef volatile signed char	vs8;	/* signed    8-bit */
#endif

typedef unsigned short			u16;	/* unsigned 16-bit */
typedef unsigned long			u32;	/* unsigned 32-bit */
//typedef unsigned long long    u64;	/* unsigned 64-bit */

typedef short					s16;	/* signed 16-bit */
typedef long					s32;	/* signed 32-bit */
//typedef long long				s64;	/* signed 64-bit */

typedef volatile unsigned short	vu16;	/* unsigned 16-bit */
typedef volatile unsigned long	vu32;	/* unsigned 32-bit */
//typedef volatile unsigned long long	vu64;	/* unsigned 64-bit */

typedef volatile short			vs16;	/* signed 16-bit */
typedef volatile long			vs32;	/* signed 32-bit */
//typedef volatile long long	vs64;	/* signed 64-bit */

typedef float					f32;	/* single prec floating point */
typedef double					f64;	/* double prec floating point */


/*************************************************************************
 * Common definitions
 */
#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef NULL
#define NULL    0
#endif

#endif  /* _ULTRATYPES_H_ */

