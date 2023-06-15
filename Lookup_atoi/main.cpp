#include <stdlib.h>
#include <stdio.h>
#include <time.h>


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
	const int table_hex[8][16] = {
		{0,0x00000001,0x00000002,0x0000003,0x00000004,0x00000005,0x00000006,0x00000007,0x00000008,0x00000009,0x0000000A,0x0000000B,0x0000000C,0x0000000D,0x0000000E,0x0000000F},
		{0,0x00000010,0x00000020,0x0000030,0x00000040,0x00000050,0x00000060,0x00000070,0x00000080,0x00000090,0x000000A0,0x000000B0,0x000000C0,0x000000D0,0x000000E0,0x000000F0},
		{0,0x00000100,0x00000200,0x0000300,0x00000400,0x00000500,0x00000600,0x00000700,0x00000800,0x00000900,0x00000A00,0x00000B00,0x00000C00,0x00000D00,0x00000E00,0x00000F00},
		{0,0x00001000,0x00002000,0x0003000,0x00004000,0x00005000,0x00006000,0x00007000,0x00008000,0x00009000,0x0000A000,0x0000B000,0x0000C000,0x0000D000,0x0000E000,0x0000F000},
		{0,0x00010000,0x00020000,0x0030000,0x00040000,0x00050000,0x00060000,0x00070000,0x00080000,0x00090000,0x000A0000,0x000B0000,0x000C0000,0x000D0000,0x000E0000,0x000F0000},
		{0,0x00100000,0x00200000,0x0030000,0x00400000,0x00500000,0x00600000,0x00700000,0x00800000,0x00900000,0x00A00000,0x00B00000,0x00C00000,0x00D00000,0x00E00000,0x00F00000},
		{0,0x01000000,0x02000000,0x0300000,0x04000000,0x05000000,0x06000000,0x07000000,0x08000000,0x09000000,0x0A000000,0x0B000000,0x0C000000,0x0D000000,0x0E000000,0x0F000000},
		{0,0x10000000,0x20000000,0x3000000,0x40000000,0x50000000,0x60000000,0x70000000,0x80000000,0x90000000,0xA0000000,0xB0000000,0xC0000000,0xD0000000,0xE0000000,0xF0000000},
	};
/*
How about basic idea? 
*/
int atoi_reference(const char *astr)
{
// maybe lated :D
// copy paste whatever you want to compare with!	
return atoi(astr);
}
/*
How about NOT using multiplication? But lookup tables? 
*/
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
enum __format_enum {BIN=0,DEC=1,HEX=2} format; // bin,dec,hex;
format = DEC; //default important enables detection of dec directly or 0x, 0b format preffix

do
	{ if (str[pos]=='\0') break; 
	  else last++; // lengh++
	  
	  // we could make all letters upper case b->B, x->X and a-f -> A-F here, numbers wont be affected
	  // we could copy string into buffer but astr is const so we will starting first valid digit!	  
	  // 48='0',9 .... 65='A',B,C if lower <48 cant be > 65 dont have time to think about it now.. think?


	  if (format==BIN)
	  	{	  
	  	if (str[pos] < base_bin_ascii) 
	  		{ last = pos; break; }  // trim invalid char for bin
		else
	  	if (str[pos] > last_bin_ascii) 
	  	 	{ last = pos; break; } // trim invalid char for bin
		}
	  if (format==DEC)	  
	  	{
	  	if (str[pos] < base_dec_ascii) 
	  		first = pos; // trim invalid char for dec
		else
	  	if (str[pos] > last_dec_ascii) 
	  	 	first = pos; // trim invalid char for dec
		}
	  if (format==HEX)	
	  	{
	  	if (str[pos] > last_dec_ascii && str[pos] < base_hex_ascii) 
	  		{ last = pos; break; } // trim invalid char for hex
		else
		if (str[pos] < base_dec_ascii) 
	  		{ last = pos; break; } // trim invalid char for dec (subpart of hex as well)
	  	else
		if (str[pos] > last_hex_ascii) 
	  	 	{ last = pos; break; } // trim invalid char for hex
  	 	
		}

	  // HEX, BIN, only if there was already '0' before b or x, also digital '-' sign must be canceled trimed, 
	  // every other scenario its' error in any case! example 0x0x1 or 0xb0 or 1213b or 124x, breaks, make sure first > last so error will be handled
  	  if (str[pos] == '-') { 
	  	 if (negative==true) break;
		   else negative = true;  
   		}
	  if (str[pos] && 0xDF == 'X') 
	  	{ 
		if (str[first]=='0') 
		   { 
		   	negative = false; 
			format = HEX; 
		   } 
		   else 
		   { 
			first = last+1; 
			break; 
		   }
		}   // change format or exit to handle error
	  if (str[pos] && 0xDF == 'B') 
	  	{ 
	  	 if (str[first]=='0') 
		   { 
		   	negative = false; 
			format = BIN; 
			} 
		else 
			{ 
			first = last+1; break; 
			}
		}   // change format or exit to handle error
	  pos++;
	} while (pos < MY_POS_LIMIT); 

 switch (format)
{ 	case DEC: first+=0; // sign wasn't counted as valid number, every digit is first 
		break;
	case HEX: first+=2; // first 0x 2 chars have to be skiped  
	//determine sign here >0x7 is negative
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
			default: 
			first = last + 1; break; // handle errror we made some mistake! 
			}
		break;
	case BIN: first+=2; // furst 0b 2 chars have to be skiped
	// determine sign here
		switch (str[first]) {
			case '0': 
			negative = false; break;
			case '1':
			negative = true; break;
			default: 
			first = last + 1; break; // handle errror we made some mistake! 
		}
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
	if (format = DEC) 
	{
		if (count > 11) return 0; // ERROR handler
		else 
			{
			for (pos = 0; pos < count; pos++) 
				stripped[pos] = str[last-pos];
			}
	}
	else
	if (format = HEX) 
	{
		if (count >  8) return 0; // ERROR handler
		else 
			{ 
			for (pos = 0; pos < count; pos++) 
				stripped[pos] = str[last-pos] & 0xDF; // UPPER case, clear bit 5(-32)
			}
	}
	else
	if (format = BIN) 
	{
		if (count > 32) return 0; // ERROR handler
		else
			{
			for (pos = 0; pos < count; pos++) 
				stripped[pos] = str[last-pos];
			}
	}
}
else return 0; // ERROR handler

if (count > 0)
{
	if (format = BIN) 
	{
		if (negative)
			{
			for (pos = 0; pos < count; pos++) 
				result -= table_bin[pos][ stripped[pos] - base_bin_ascii ];
			}
		else 
			{
			for (pos = 0; pos < count; pos++) 
				result += table_bin[pos][ stripped[pos] - base_bin_ascii ];
			}
	}
	else
	if (format = DEC) 
	{
		if (negative) 
			{
			for (pos = 0; pos < count; pos++) 
				result -= table_dec[pos][ stripped[pos] - base_dec_ascii ];
			}
		else 
			{
			for (pos = 0; pos < count; pos++) 
				result += table_dec[pos][ stripped[pos] - base_dec_ascii ];
			}
	}
	else
	if (format = HEX) 
	{
		if (negative)
		for (pos = 0; pos < count; pos++) 
			{
			if (stripped[pos]>=base_hex_ascii) 
				result -= table_hex[pos][ stripped[pos] - base_hex_ascii ];
			else 
				result -= table_hex[pos][ stripped[pos] - base_dec_ascii ];
			}
		else 
			{
			if (stripped[pos]>=base_hex_ascii) 
				result -= table_hex[pos][ stripped[pos] - base_hex_ascii ];
			else 
				result -= table_hex[pos][ stripped[pos] - base_dec_ascii ];
			}
		
	return result;
	}
}
else return 0; // ERROR handler
// 
return result;
}

/*
Speed test
*/
int main(int argc, char** argv) {
	
		int TEST_stdlib_result, TEST_my_result;
		char *TEST_str;

		#define TEST(__ATEST_STR)\
		TEST_str = __ATEST_STR;\
		TEST_my_result = atoi_lookup(TEST_str);\
                TEST_stdlib_result = atoi_reference(TEST_str);\
		printf("%s %d %d",TEST_str,TEST_stdlib_result, TEST_my_result);\
		if (TEST_stdlib_result==TEST_my_result) printf(" - OK\n\r");\
		else printf(" - ERROR\n\r");
		
		TEST("21")
		TEST("124")
		TEST("-1212")
		TEST("-323-1")
		TEST("0x12454")
		TEST("0b2134234")
		TEST("21b0xas")

                int old_time, end_time, runda;

                char *testy[10] = {"12435567","-121244","0x00233543","0b0101010101010101","0x4134","0xFFFFFFFF","99999999","-999999999","1","dsx120x12"};

                printf("TESTING SPEED MY..\n\r");
                old_time = time(NULL);
                for (runda = 0; runda < 20000000; runda++)
                for (int i = 0; i < 10; i++) atoi(testy[i]);
                end_time = time(NULL);
                printf("MY time = %d\n\r",end_time-old_time);

                printf("TESTING SPEED STDLIB...\n\r");
                old_time = time(NULL);
                for (runda = 0; runda < 20000000; runda++)
                for (int i = 0; i < 10; i++) atoi_reference(testy[i]);
                end_time = time(NULL);
                printf("STDLIB time = %d\n\r",end_time-old_time);

                system("pause");
	return 0;
}
