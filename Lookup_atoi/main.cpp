#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
*/
// -----------------------------------------------------------------------------

int atoi_reference(const char *astr)
{
// maybe lated :D
// copy paste whatever you want to compare with!
return atoi(astr);
}
// -----------------------------------------------------------------------------
/*
How about NOT using multiplication? But lookup tables?
*/
// -----------------------------------------------------------------------------

int atoi_lookup(const char *astr)
{
// on 32bit platform limit is 1 sign, 2 for hex,bin notation: 0x,0b + 8,10,32 digits = 11-34
// but if you want filter out, trim mush allow higher limit
#define MY_POS_LIMIT 100
// on 32bit platform parameters are send via stack,
//this allow str to be put into register!
const char *str = astr;
// 3 lines of code, decission making purpose, allow to pick table of choice dec,hex,bin
const char base_bin_ascii = '0';
const char last_bin_ascii = '1';
const char base_dec_ascii = '0'; // both for HEX and DEC! 48='0'
const char last_dec_ascii = '9'; // both for HEX and DEC! 58='9'
const char base_hex_ascii = 'A'; // 65='A'
const char last_hex_ascii = 'F'; // 70='F'
//const char base_hex_ascii = 'a'; // 97='a'
//const char last_hex_ascii = 'f'; // 102='f'
// we could mask bit nr 5 (32) to make upper letters so one range is enough!
// also x and b will turn into -> X and B

// every hex, bin notation starts with 0 so before we adapt we assume dec is default

// current position, first valid number char starts here, last valid number char ends here
// first >= last means there is no valid number anywhere in string, even single digit!
int pos = 0, first = 0, last = -1, count = 0, result = 0;

//if negative sign is detected or first bit 2's complement notation is detected
// -1 or 0b1000 to 0x1111 HEX or 0x8000 to FFFF.. BIN
bool negative = false;
enum __format_enum {BIN=0,DEC=1,HEX=2,NON=3} format; // bin,dec,hex;
format = NON; //default important enables detection of dec directly or 0x, 0b format preffix

do
	{ if (str[pos]=='\0')
            {
            break; // totally finished here
            }
	  if (format==NON) // before we determine format, start with NON but as if it was DEC but just trim out first character
	  	    {
  	        if (str[pos] == '-')            // this is for first time, sign negative, format DEC
                {
                 first = pos+1; format = DEC; negative = true;
                }
            else
	  	    if (str[pos] > last_dec_ascii)  // higher than '9'
	  	 	    {
                 first = pos+1;
                }
		    else
	  	    if (str[pos] < base_dec_ascii)  // lower than '0'
	  		    {
                 first = pos+1;
                }
            else                            // number is in range 0-9, change to DEC, so next invalid character out of range will this time cause break
                {
                 first = pos+0; last = pos+0; format = DEC;
                }
                                            // here ^^ first correct digital number was detected "garbage1324whatever" so change format to DEC
                                            // do next time if garbage is in string just cut out rest, keep only that first number to process
		    }
	  else
      if (format==DEC) // if we already determined DEC format, any "123bad" character is cut off, break;
	  	    {
	        if ((str[pos] & 0xDF) == 'X')    // "0X" = HEX, comparison as upper letters
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
            else
	  	    if (str[pos] > last_dec_ascii)  // higher than '9'
	  	 	    {
                 last = pos-1; break;
                }                           // trim invalid char for dec
		    else
	  	    if (str[pos] < base_dec_ascii)  // lower than '0'
	  		    {
                 last = pos-1; break;
                }                           // trim invalid char for dec
            else
                {
                 last = pos;
                }                           // number is within range
		    }
      else
	  if (format==BIN)                      // if we passed already "0B" check out ranges of 0B010101 next characters
	  	    {
	  	    if (str[pos] > last_bin_ascii)  // higher than '1'
	  	 	    {
                 last = pos-1; break;
                }                           // trim invalid char for bin
		    else
	  	    if (str[pos] < base_bin_ascii)  // lower than '0'
	  		    {
                 last = pos-1; break;
                }                           // trim invalid char for bin
            else
                {
                 last = pos;
                }                           // number is within range
		    }
      else
	  if (format==HEX)
	  	    {
	  	    if (str[pos] > last_dec_ascii && str[pos] < base_hex_ascii) // range between 0-9 and A-F
	  		    {
                 last = pos-1; break;
                }                           // trim invalid chars for hex
		    else
		    if (str[pos] < base_dec_ascii)  // lower than '0'
	  		    {
                 last = pos-1; break;
                }                           // trim invalid chars for dec (subpart of hex as well)
	  	    else
		    if (str[pos] > last_hex_ascii)  // higher han 'F'
	  	 	    {
                 last = pos-1; break;
                }                           // trim invalid chars for hex
            else
                {
                 last = pos;
                }                           // number is within range
		    }
	} while (++pos < MY_POS_LIMIT);

 switch (format)
{ 	case DEC:
    break;
	case BIN:
	// determine sign here
		switch (str[first]) {
			case '0':
			negative = false;
            break;
			case '1':
			negative = true;
            break;
			default:
			return 0; // handle ERROR we made some mistake!
		}
    break;
	case HEX:
	//determine sign 0x0000-0x7000 positive, 0x8000-0xF000 is negative
		switch (str[first]) {

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			negative = false;
			break;

			case '8':
			case '9':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			negative = true;
			break;

			default: return 0; // ERROR we made some mistake!
			}
		break;
	default:
	first = last + 1; break; // handle errror we made some mistake!
}
// buffer containing essence of string all letters will be upper case, numbers wont be affected
// we can also rearrange 12345 -> 54321 to make it bit faster compute but wont do that now
count = last - first + 1;
char stripped[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char *stripped_vatch = (char*)stripped;
// check lenght of number, depending on format 11 digits DEC, 32 digits binary, 8 digits HEX is limit 32 bit
// also copy string here to buffer and make it upper case if HEX
if (count > 0)
{
    switch (format)
    {
    case DEC:
		if (count > 10) return 0; // ERROR handler
		else
			{
			for (pos = 0; pos < count; pos++)
				stripped[pos] = str[last-pos];
			}
	break;
	case BIN:
		if (count > 32) return 0; // ERROR handler
		else
			{
			for (pos = 0; pos < count; pos++)
				stripped[pos] = str[last-pos];
            stripped[0]='0'; // negative bit => 0
			}
	break;
	case HEX:
		if (count >  8) return 0; // ERROR handler
		else
			{
			for (pos = 0; pos < count; pos++)
				stripped[pos] = str[last-pos] & 0xDF; // UPPER case, clear bit 5(-32)
            stripped[0]=stripped[0] & 0xDF;
			}
    break;
    default: return 0; // ERROR handler
	}
}
else return 0; // ERROR handler

if (count > 0)
{
    switch (format)
    {
    case DEC:
		if (negative==true)
			{
			for (pos = 0; pos < count; pos++)
				result -= table_dec[pos][ stripped[pos] - base_dec_ascii ];
			}
		else
			{
			for (pos = 0; pos < count; pos++)
				result += table_dec[pos][ stripped[pos] - base_dec_ascii ];
			}
	break;
    case BIN:
		if (negative==true)
			{
			for (pos = 0; pos < count; pos++)
				result -= table_bin[pos][ stripped[pos] - base_bin_ascii ];
			}
		else
			{
			for (pos = 0; pos < count; pos++)
				result += table_bin[pos][ stripped[pos] - base_bin_ascii ];
			}
	break;
    case HEX:
		if (negative==true)
            {
		    for (pos = 0; pos < count; pos++)
                {
			    if (stripped[pos]>=base_hex_ascii)
				    result -= table_hex[pos][ 10 + stripped[pos] - base_hex_ascii ];
			    else
				    result -= table_hex[pos][ stripped[pos] - base_dec_ascii ];
			    }
            }
		else
            {
		    for (pos = 0; pos < count; pos++)
                {
			    if (stripped[pos]>=base_hex_ascii)
				    result += table_hex[pos][ 10 + stripped[pos] - base_hex_ascii ];
			    else
				    result += table_hex[pos][ stripped[pos] - base_dec_ascii ];
                }
			}
    break;
    }
	return result;
}
else return 0; // ERROR handler
//
return result;
}
// -----------------------------------------------------------------------------
/*
Speed test
*/
// -----------------------------------------------------------------------------

int main(int argc, char** argv) {

		int TEST_stdlib_result, TEST_my_result;
		char *TEST_str;

		#define TEST(__ATEST_STR)                                       \
		TEST_str = __ATEST_STR;                                         \
		TEST_my_result = atoi_lookup(TEST_str);                         \
                TEST_stdlib_result = atoi_reference(TEST_str);                  \
		printf("%20s\t%12d\t%12d",TEST_str,TEST_stdlib_result, TEST_my_result); \
		if (TEST_stdlib_result==TEST_my_result) printf(" - OK\n\r");    \
		else printf(" - ERROR\n\r");

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
		TEST("0b001010101010101")
		TEST("2x2134234")
		TEST("-21b00x42")

                char *testy[10] = {"12435567","-121244","0x00233543","0b0101010101010101","0x4134",
                                   "0xFFFFFFFF","99999999","-999999999","1","dsx120x12"};
                int old_time, end_time, runda;
                int i;

                #define TEST_SPEED(TEST_NAME,TEST_FUNC)                         \
                printf("TESTING SPEED %s..\n\r",TEST_NAME);                     \
                old_time = time(NULL);                                          \
                for (runda = 0; runda < 10000000; runda++)                      \
                for (i = 0; i < 10; i++) TEST_FUNC;                             \
                end_time = time(NULL);                                          \
                printf("%s time = %d\n\r",TEST_NAME,end_time-old_time);

                TEST_SPEED("STDLIB",atoi(testy[i]);)
                TEST_SPEED("LOOKUP",atoi_lookup(testy[i]);)
                //TEST_SPEED("REFERENCE",atoi_reference(testy[i]);)
                system("pause");

	return 0;
}
// -----------------------------------------------------------------------------


