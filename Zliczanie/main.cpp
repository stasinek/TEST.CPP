#include <iostream>
#include <cstring>
#include <cstdio>
#include <conio>
#include <windows>
using namespace std;

 int EnterChars(char*, const int);
void CountChars(const char*, const int, unsigned int[256]);
void PrintCharsAndCounts(const char*, const int, const unsigned int[256]);

#define MAX_LENGTH 256
int main()
{
setlocale(LC_ALL,"pl_PL.ISO-8859-2");
system("chcp 1250");
printf("------------------------------------------------------------------\n");
printf("Program do obliczania statystyk wystepowania znaków w tekœcie v1.0\n");
char Chars[MAX_LENGTH];
 unsigned int CharsCounts[254];
 int CharsLen = EnterChars(Chars,MAX_LENGTH);
 if (CharsLen < 0  || CharsLen > MAX_LENGTH) return -1;
CountChars(Chars,CharsLen, CharsCounts);
PrintCharsAndCounts(Chars,CharsLen, CharsCounts);
printf("Naduœ Any klawisz aby kontynuowaæ . . .\n");
getch();
system("pause");
return 0;
}

//--------------------------------------------------
// Wprowadzenie tekstu
//--------------------------------------------------

int EnterChars(char *a_chars, const int a_max_len)
{
printf("WprowadŸ tekst do analizy i naciœnij ENTER\n");
printf("------------------------------------------------------------------\n");
std::scanf("%s",a_chars);
return std::strlen(a_chars);
}
//--------------------------------------------------
// Zliczanie liczebnoœci znaków
//--------------------------------------------------

void CountChars(const char *a_chars, const int a_chars_len, unsigned int a_chars_counts[])
{
int i;

    for(i = 0; i < 256; i++)
		{
		a_chars_counts[i] = 0;
		}
    for(i = 0; i < a_chars_len; i++)
    	{
		a_chars_counts[(unsigned char)a_chars[i]]++;
    	}
}

//--------------------------------------------------
// Drukowanie znaków i liczebnoœci
//--------------------------------------------------

void PrintCharsAndCounts(const char *a_chars, const int a_chars_len, const unsigned int a_chars_counts[])
{
printf("------------------------------------------------------------------\n");
std::printf("Liczebnoœæ znakow w tekœcie:\n");
 int l_unique_chars_count = 0;
bool l_char_printed[256];
int i;

for (i = 0; i < 256; i++)
	{
    l_char_printed[i] = false;
    }
for (i = 0; i < a_chars_len; i++)
	{
     if (l_char_printed[(unsigned char)a_chars[i]]==false)
        {
        std::printf("%c - %d\n", a_chars[i], a_chars_counts[(unsigned char)a_chars[i]]);
        l_char_printed[(unsigned char)a_chars[i]] = true;
        l_unique_chars_count++;
        }
	}
std::printf("Iloœæ wszystkich znakow: %d\n",a_chars_len);
std::printf("Iloœæ ró¿nych znakow: %d\n", l_unique_chars_count);
std::printf("Koniec!\n");
}

