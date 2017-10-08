/**********************************************************

	Sound Bank Compiller

 **********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <LIMITS.H>

#include "ultratypes.h"
#include "main.h"


 /**********************************************************
	Преобразование велечин НОТ
 **********************************************************/

u16 noteval( char *v )
{
u16 num;
u16 o;

	switch( *v )
	{
	case 'c': num = 0; 	break;
	case 'd': num = 2;	break;
	case 'e': num = 4;  break;
	case 'f': num = 5; 	break;
	case 'g': num = 7;	break;
	case 'a': num = 9;	break;
	case 'b': num = 11;	break;
	default:
		return u8val( v );	// просто цифры
		break;
	}
	v++;
	switch( *v )
	{
	case '#': 
	case 'd': num += 1;	break;
	case 'b': num -= 1; break;
	case '-': break;
	default:  v--;		break;
	}

	v++;
	o = u8val( v );		// октава
	return o*12+num;
}

 /**********************************************************
	Преобразование велечин S8
 **********************************************************/

char s8val( char *v)
{
long i;
char *tc;
	
	i = strtol( v, &tc, 10 );
	if(v == tc)
	{	print_e( v,"Parameter is Bad");
		return 0;
	}

	if((i > CHAR_MAX) && ( i < CHAR_MIN))
	{
		print_e( var,"Out of range as CHAR");
		return 0;
	}
	else return  (char)i;
}

/**********************************************************
	Преобразование велечин S16
 **********************************************************/

short s16val( char *v)
{
long i;
	
char *tc;
	
	i = strtol( v, &tc, 10 );
	if(v == tc)
	{	print_e( v,"Parameter is Bad");
		return 0;
	}
	if((i > SHRT_MAX) && ( i < SHRT_MIN))
	{
		print_e( var,"Out of range as SHORT");
		return 0;
	}
	else return (short)i;
}

/**********************************************************
	Преобразование велечин S32
 **********************************************************/

long s32val( char *v)
{

long i; 
char *tc;
	
	i = strtol( v, &tc, 10 );
	if(v == tc)
	{	print_e( v,"Parameter is Bad");
		return 0;
	}
	if((i>LONG_MAX) && (i<LONG_MIN))
	{
		print_e( var,"Out of range as LONG");
		return 0;
	}
	else return i;
}

/**********************************************************
	Преобразование велечин U8
 **********************************************************/

unsigned char u8val( char *v)
{

long i;
char *tc;
	
	i = strtol( v, &tc, 10 );
	if(v == tc)
	{	print_e( v,"Parameter is Bad");
		return 0;
	}
	if(i > UCHAR_MAX)
	{
		print_e( var,"Out of range as UCHAR");
		return 0;
	}
	else return  (unsigned char)i;
}

/**********************************************************
	Преобразование велечин S16
 **********************************************************/

unsigned short u16val( char *v)
{

long i;
char *tc;
	
	i = strtol( v, &tc, 10 );
	if(v == tc)
	{	print_e( v,"Parameter is Bad");
		return 0;
	}	
	if(i > USHRT_MAX)
	{
		print_e( var,"Out of range as USHORT");
		return 0;
	}
	else return (unsigned short)i;
}

/**********************************************************
	Преобразование велечин S32
 **********************************************************/

unsigned long u32val( char *v)
{

long i;
	
char *tc;
	
	i = strtol( v, &tc, 10 );
	if(v == tc)
	{	print_e( v,"Parameter is Bad");
		return 0;
	}
	if(i > ULONG_MAX)
	{
		print_e( var,"Out of range as ULONG");
		return 0;
	}
		else return (unsigned long)i;
}

/**********************************************************
	Преобразование велечин POINTER TO CTL
 **********************************************************/

unsigned long pctlval( char objtype, char *name )
{

tlist *t;

	t = find_in_list( objtype, name );
	if( t == 0) 
	{
		print_e(name, "OBJECT not found");
		return 0;
	}
	else
	{
		if(t->obj == objtype)
		{
			if(t->ptr > MAX_CTL_PTR)
			{
				print_e( name, "Value overflow type Pointer to CTL");
				return 0;
			}
			else return t->ptr;
		}
		else
		{
			print_e( name, "Used not valid object type for this reference");
			return 0;
		}
	}
}

/**********************************************************
	Преобразование велечин в MSB
 **********************************************************/
#ifdef DSP56

unsigned long long2msb( unsigned long x )
{
unsigned long result;
	result  = ((x>>8)  & 0x00FF00FFL);
	result |= ((x<<8)  & 0xFF00FF00L);
	return result;
}

unsigned short short2msb( unsigned short x )
{
unsigned short result;
	result  = ((x>>8 ) & 0x00FF);
	result |= ((x<<8)  & 0xFF00);
	return result;
}

#else
unsigned long long2msb( unsigned long x )
{
unsigned long result;
	result  = ((x>>24) & 0xFFL);
	result |= ((x>>8)  & 0xFF00L);
	result |= ((x<<8)  & 0xFF0000L);
	result |= ((x<<24) & 0xFF000000L);
	return result;
}

unsigned short short2msb( unsigned short x )
{
unsigned short result;
	result  = ((x>>8 ) & 0x00FF);
	result |= ((x<<8)  & 0xFF00);
	return result;
}
#endif
