#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <memory.h>
//#include <sys/cdefs.h>
// -----------------------------------------------------------------------------

	const int table_bin[32][2] = {
		{0,1},
		{0,2},
		{0,4},
		{0,8},
		{0,16},
		{0,32},
		{0,64},
		{0,128},
		{0,256},
		{0,512},
		{0,1024},
		{0,2048},
		{0,4096},
		{0,8192},
		{0,16384},
		{0,32768},
		{0,65536},
		{0,131072},
		{0,262144},
		{0,524288},
		{0,1048576},
		{0,2097152},
		{0,4194304},
		{0,8388608},
		{0,16777216},
		{0,33554432},
		{0,67108864},
		{0,134217728},
		{0,268435456},
		{0,536870912},
		{0,1073741824},
		{0,0/*2147483648*/}};
// -----------------------------------------------------------------------------

	const int table_dec[10][10] = {
		{0,1,2,3,4,5,6,7,8,9},
		{0,10,20,30,40,50,60,70,80,90},
		{0,100,200,300,400,500,600,700,800,900},
		{0,1000,2000,3000,4000,5000,6000,7000,8000,9000},
		{0,10000,20000,30000,40000,50000,60000,70000,80000,90000},
		{0,100000,200000,300000,400000,500000,600000,700000,800000,900000},
		{0,1000000,2000000,3000000,4000000,5000000,6000000,7000000,8000000,9000000},
		{0,10000000,20000000,30000000,40000000,50000000,60000000,70000000,80000000,90000000},
		{0,100000000,200000000,300000000,400000000,500000000,600000000,700000000,800000000,900000000},
		{0,1000000000,2000000000,3000000000,4000000000,5000000000,6000000000,7000000000,8000000000,9000000000}};
// -----------------------------------------------------------------------------

	const int table_hex[8][16] = {
		{0,0x00000001,0x00000002,0x00000003,0x00000004,0x00000005,0x00000006,0x00000007,0x00000008,0x00000009,0x0000000A,0x0000000B,0x0000000C,0x0000000D,0x0000000E,0x0000000F},
		{0,0x00000010,0x00000020,0x00000030,0x00000040,0x00000050,0x00000060,0x00000070,0x00000080,0x00000090,0x000000A0,0x000000B0,0x000000C0,0x000000D0,0x000000E0,0x000000F0},
		{0,0x00000100,0x00000200,0x00000300,0x00000400,0x00000500,0x00000600,0x00000700,0x00000800,0x00000900,0x00000A00,0x00000B00,0x00000C00,0x00000D00,0x00000E00,0x00000F00},
		{0,0x00001000,0x00002000,0x00003000,0x00004000,0x00005000,0x00006000,0x00007000,0x00008000,0x00009000,0x0000A000,0x0000B000,0x0000C000,0x0000D000,0x0000E000,0x0000F000},
		{0,0x00010000,0x00020000,0x00030000,0x00040000,0x00050000,0x00060000,0x00070000,0x00080000,0x00090000,0x000A0000,0x000B0000,0x000C0000,0x000D0000,0x000E0000,0x000F0000},
		{0,0x00100000,0x00200000,0x00300000,0x00400000,0x00500000,0x00600000,0x00700000,0x00800000,0x00900000,0x00A00000,0x00B00000,0x00C00000,0x00D00000,0x00E00000,0x00F00000},
		{0,0x01000000,0x02000000,0x03000000,0x04000000,0x05000000,0x06000000,0x07000000,0x08000000,0x09000000,0x0A000000,0x0B000000,0x0C000000,0x0D000000,0x0E000000,0x0F000000},
		{0,0x10000000,0x20000000,0x30000000,0x40000000,0x50000000,0x60000000,0x70000000,0x80000000,0x90000000,0xA0000000,0xB0000000,0xC0000000,0xD0000000,0xE0000000,0xF0000000},
	};
// -----------------------------------------------------------------------------
/*
How about basic idea?
copy paste whatever you want to compare with!
*/
// -----------------------------------------------------------------------------

int atoi_reference(const char *astr)
{
/*-
    FreeBSD - strtol (str to long int)

 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)strtol.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */
//__FBSDID("$FreeBSD: src/lib/libc/stdlib/strtol.c,v 1.20 2007/01/09 00:28:10 imp Exp $");
/*
 * Convert a string to a long integer.
 *
 * Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
#ifdef __BORLANDC__
#define __restrict
#define isspace_l(c,l) c == ' '  // filter out white characters, could be SPACE alone or any charter other than 0-9,A-F
#else
locale_t loc;
	NORMALIZE_LOCALE(loc);
#endif

    const char * __restrict nptr = astr;
    char ** __restrict endptr = NULL;        // return ERROR - atoi does not support that
    int base = 10;

	register const char *s;
	register char c;
	unsigned long acc;
	unsigned long cutoff;
	int neg, any;

	/*
	 * Skip white space and pick up leading +/- sign if any.
	 * If base is 0, allow 0x for hex and 0 for octal, else
	 * assume decimal; if base is already 16, allow 0x.
	 */
	s = nptr;
	do {
		c = *s++;
	} while (isspace_l((unsigned char)c, loc));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else {
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X') &&
	    ((s[1] >= '0' && s[1] <= '9') ||
	    (s[1] >= 'A' && s[1] <= 'F') ||
	    (s[1] >= 'a' && s[1] <= 'f'))) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	acc = any = 0;
	if (base < 2 || base > 36)
		goto noconv;

	/*
	 * Compute the cutoff value between legal numbers and illegal
	 * numbers.  That is the largest legal value, divided by the
	 * base.  An input number that is greater than this value, if
	 * followed by a legal input character, is too big.  One that
	 * is equal to this value may be valid or not; the limit
	 * between valid and invalid numbers is then based on the last
	 * digit.  For instance, if the range for longs is
	 * [-2147483648..2147483647] and the input base is 10,
	 * cutoff will be set to 214748364 and cutlim to either
	 * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
	 * a value > 214748364, or equal but the next digit is > 7 (or 8),
	 * the number is too big, and we will return a range error.
	 *
	 * Set 'any' if any `digits' consumed; make it negative to indicate
	 * overflow.
	 */
    int cutlim;
	cutoff = neg ? (unsigned long)-(LONG_MIN + LONG_MAX) + LONG_MAX
	    : LONG_MAX;
	cutlim = cutoff % base;
	cutoff /= base;
	for ( ; ; c = *s++) {
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'A' && c <= 'Z')
			c -= 'A' - 10;
		else if (c >= 'a' && c <= 'z')
			c -= 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = neg ? LONG_MIN : LONG_MAX;
		errno = ERANGE;
	} else if (!any) {
noconv:
		errno = EINVAL;
	} else if (neg)
		acc = -acc;
	if (endptr != NULL)
		*endptr = (char *)(any ? s - 1 : nptr);
	return (acc);
}
// -----------------------------------------------------------------------------
/*
How about NOT using multiplication? But lookup tables?
*/
// -----------------------------------------------------------------------------

int atoi_lookup(const char *astr)
{
#define MY_POS_LIMIT 100
/* on 32bit platform limit is: 1 byte for sign, 2 bytes for hex,bin notation: 0x,0b 
   and + HEX 8 or DEC 10 or BIN 32 digits = 11-34 bytes string 
 if you want filter out more, trim mush allow higher limit or even no limits */

// determine valid ranges of characters 0-9, A-F
const char base_bin_ascii = '0';
const char last_bin_ascii = '1';
const char base_dec_ascii = '0'; // valid both for HEX and DEC! 48='0'
const char last_dec_ascii = '9'; // valid both for HEX and DEC! 58='9'
const char base_hex_ascii = 'A'; // 65 = 'A'
const char last_hex_ascii = 'F'; // 70 = 'F'
/*
 const char base_hex_ascii = 'a'; // 97 = 'a'
 const char last_hex_ascii = 'f'; // 102 = 'f'
*/
// we could mask bit nr 5 (32) to make upper letters so one range is enough!
// also x and b will turn into -> X and B

// every hex, bin notation starts with 0 so before we adapt we assume dec is default

// current position, first valid number char starts here, last valid number char ends here
// first >= last means there is no valid number anywhere in string, even single digit!
// on 32bit platform parameters are send via stack,
// this allow str to be put into register
register const char *str = astr;
register int pos = 0, first = 0, last = -1;
int result = 0;
bool negative = false;
//if negative sign is detected or first bit 2's complement notation is detected
// -1 or 0b1000 to 0x1111 HEX or 0x8000 to FFFF.. BIN
register enum __format_enum {BIN=0,DEC=1,HEX=2,NON=3} format; // bin,dec,hex;
format = NON; //default important enables detection of dec directly or 0x, 0b format preffix

do
	{ if (str[pos]=='\0')
            {
            break; // totally finished here
            }
      if (format==DEC) // if we already determined DEC format, any "123bad" character is cut off, break;
	  	    {
            if (str[pos] >= base_dec_ascii ? str[pos] <= last_dec_ascii : false)
                {
                 last = pos;
                }                           // OK number is within range
            else                            // EXCEPTIONS AS FOLLOWS
	        if ((str[pos] & 0xDF) == 'X')   // "0X" = HEX, comparison as upper letters
	  	        {
		        if (str[first]=='0')        // 0X scenario, HEX, ignore '-' sign will be deterimed by compliment bits
		            {
		   	        negative = false;
			        format   = HEX;
                    first    = pos+1;
                    last     = pos+1;       // first "0x"=2bytes doesn't represent value, start at next byte
		            }
	            else                        // 121x823 scenario, we found "X" but not 0X rather 1234X so format is DEC ends here
		            {
   		            last = pos-1;
			        break;
		            }
		        }
            else
	        if ((str[pos] & 0xDF) == 'B')    // "0B" = BIN, comparison as upper letters
                {
	            if (str[first]=='0')
		            {
		            negative = false;
		            format   = BIN;
                    first    = pos+1;
                    last     = pos+1;       // first "0b"=2bytes doesn't represent value, start at next byte
		            }
	            else                        // 123b01010 scenario, we found "B" but not "0B" rather 1234B so format is DEC, ends here
		            {
		            last = pos-1;
                    break;
		            }
		        }
            else // END OF EXCEPTIONS LIST, higher than '9' nor lower than '0', it's not X, not B, therefore it's invalid character
	  	 	    {
                 last = pos-1; break;
                }                           // trim invalid char for dec
		    }
      else
	  if (format==HEX)
	  	    {
	  	    if ((str[pos]) >= base_dec_ascii ? (str[pos]) <= last_dec_ascii : false)  // within range of '0' - '9'
                {
                 last = pos;
                }                           // number is within range
            else
	  	    if ((str[pos] & 0xDF) >= base_hex_ascii ? (str[pos] & 0xDF) <= last_hex_ascii : false)  // within range of 'A' - 'F'
                {
                 last = pos;
                }                           // number is within range
            else
   	  		    {
                 last = pos-1; break;
                }                           // trim invalid chars
            }
	  else
      if (format==BIN)                      // if we passed already "0B" check out ranges of 0B010101 next characters
	  	    {
	  	    if (str[pos] >= base_bin_ascii ? str[pos] <= last_bin_ascii : false)  // either '0' or '1'
                {
                 last = pos;
                }                           // number is within range
		    else
	  		    {
                 last = pos-1; break;
                }                           // trim invalid char for bin
		    }
      else
	  if (format==NON) // before we determine format, start with NON but as if it was DEC but just trim out first character
	  	    {
	  	    if (str[pos] >= base_dec_ascii ? str[pos] <= last_dec_ascii : false)  // within range of '0' - '9'
               {
                 first = pos+0; last = pos+0; format = DEC;
               }
            else
  	        if (str[pos] == '-')            //  '-' for first time, sign negative, switch format DEC
                {
                 first = pos+1; format = DEC; negative = true;
                }
            else  // there was no good characters yet, invalid, just skip first characters as long necessary
	  	 	    {
                 first = pos+1;
                }
            // here ^^ first correct digital number was detected "garbage1324whatever" so change format to DEC
            // do next time if garbage is in string just cut out rest, keep only that first number to process
		    }

	} while (++pos < MY_POS_LIMIT);

if (format==DEC); else if (format==HEX) negative = str[first] > '7'; else if (format==BIN) negative =  str[first] > '0'; else if (format==NON) return 0;
register int count = last - first + 1, index;
// check lenght of number, depending on format 11 digits DEC, 32 digits binary, 8 digits HEX is limit 32 bit
if (count <= 0) return 0; // ERROR handler
else
{
    switch (format)
    {
    case DEC:
		if (count > 10) return 0; // ERROR handler
        if (negative==true)
			{
            // reverse order higher index higher base number, but we start from left pos=first(1)  12345 to finish last 5,
            // we must start highest index number in the table, highest index bigger the base, last 5 is lowest value to add, lowest index = 0;
			for (index = 0; index < count;  index++)
				{
                 result -= table_dec[index][ str[last-index] - base_dec_ascii ];
                }
			}
		else
			{
			for (index = 0; index < count;  index++)
				{
				 result += table_dec[index][ str[last-index] - base_dec_ascii ];
                }
			}
	break;
    case HEX:
		if (count >  8) return 0; // ERROR handler
        if (negative==true)
            {
			for (index = 0; index < count;  index++)
				{
			    if (str[last-index] >= base_dec_ascii) result -= table_hex[index][ 10 + (str[last-index] & 0xDF) - base_hex_ascii ];
			    else
				    result -= table_hex[index][ str[last-index] - base_dec_ascii ];
			    }
            }
		else
            {
			for (index = 0; index < count;  index++)
                {
			    if (str[last-index] >= base_dec_ascii) result += table_hex[index][ 10 + (str[last-index] & 0xDF) - base_hex_ascii ];
			    else
				    result += table_hex[index][ str[last-index] - base_dec_ascii ];
                }
			}
    break;
    case BIN:
		if (count > 32) return 0; // ERROR handler
        if (negative==true)
			{
			for (index = 0; index < count;  index++)
				{
				 result -= table_bin[index][ str[last-index] - base_bin_ascii ];
                }
			}
		else
			{
			for (index = 0; index < count;  index++)
				{
				 result += table_bin[index][ str[last-index] - base_bin_ascii ];
                }
			}
	break;
    default: return 0; // ERROR!
    }

}
return result;
}
// -----------------------------------------------------------------------------
/*
Speed test
*/
// -----------------------------------------------------------------------------

int main(int argc, char** argv) {

		int TEST_stdlib_result, TEST_reference_result, TEST_my_result;
		char *TEST_str,TEST_itoabuff[20];
        char TEST_br[81];
        memset(TEST_br, '-', 78);
        TEST_br[78] = '\n';
        TEST_br[79] = '\r';
        TEST_br[80] = '\0';


		printf("TEXT\t\t\tATOI\t\tREF(DEC)\tMY(DEC)\t\tMY(HEX)\n\r");

		#define TEST(__ATEST_STR)                                               \
		TEST_str = __ATEST_STR;                                                 \
		TEST_my_result = atoi_lookup(TEST_str);                                 \
        TEST_reference_result = atoi_reference(TEST_str);                       \
        TEST_stdlib_result = atoi(TEST_str);                                    \
        printf("%s",TEST_br);                                                   \
        printf("%12s\t%11d\t%11d\t%11d\t0x%08x\n\r",                            \
                TEST_str, TEST_stdlib_result, TEST_reference_result, TEST_my_result, TEST_my_result);       \
		if (TEST_stdlib_result==TEST_my_result) printf("^^ OK: CORRECT 100%%\n\r");                         \
        else if (TEST_stdlib_result==0) printf("^^ WARNING: NOT SUPPORTED BY ATOI, CHECK MANUALLY\n\r");    \
		        else printf("^^ ERROR: ABSOLUTELY! \n\r");

		TEST("0x24549ABC")
		TEST("0b10")
		TEST("4294967295")
		TEST("21")
		TEST("124")
		TEST("-1212")
		TEST("-323-1")
		TEST("abc-323-1")
		TEST("0x24549ABC")
		TEST("0b12134234")
		TEST("0b0010101010101")
		TEST("2x2134234")
		TEST("-21b00x42")

                char *testy[10] = {"12435567","-121244","0x00233543","0b0101010101010101","0x4134",
                                   "0xFFFFFFFF","99999999","-999999999","1","dsx120x12"};
                int old_time, end_time, runda;
                int i;

                #define TEST_SPEED(TEST_NAME,TEST_FUNC)                         \
                printf("\n\r");                                                 \
                printf("TESTING SPEED %s.. ",TEST_NAME);                     \
                old_time = time(NULL);                                          \
                for (runda = 0; runda < 10000000; runda++)                      \
                for (i = 0; i < 10; i++) TEST_FUNC;                             \
                end_time = time(NULL);                                          \
                printf("%s time = %d\n\r",TEST_NAME,end_time-old_time);

                TEST_SPEED("Compiler STDLIB",atoi(testy[i]);)
                    int stdlib_time = end_time-old_time;
                TEST_SPEED("Apple FreeBSD",atoi_reference(testy[i]);)
                    int reference_time = end_time-old_time;
                TEST_SPEED("LOOKUP",atoi_lookup(testy[i]);)
                    int my_time = end_time-old_time;

                printf("Relative speed, lower is faster, STDLIB=100%% APPLE=%d%% LOOKUP=%d%%",
                            (reference_time*100)/stdlib_time,(my_time*100)/stdlib_time);
                printf("\n\r");
                
                system("pause");

	return 0;
}
// -----------------------------------------------------------------------------


