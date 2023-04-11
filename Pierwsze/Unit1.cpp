//---------------------------------------------------------------------------
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <locale.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <time>
#pragma hdrstop
using namespace std;
//---------------------------------------------------------------------------
#define PRIME_START 0
#define PRIME_END 5000000
//---------------------------------------------------------------------------

int time_ms();
void druk(int*,int,int);
int __fastcall is_prime_A(__int64);
//---------------------------------------------------------------------------
int __stdcall time_ms()
{
    register __int32 s = __int64(1000 * clock())/CLOCKS_PER_SEC;
    return s;
}
//---------------------------------------------------------------------------

void druk(int *a_t_p, int a_base, int a_count)
{
#define KOLUMN 13
for (int x = 0, b = a_base, c = a_count, k = KOLUMN;; x++) {
    if (x==k) {
            printf("\n"); k+=KOLUMN;
        }
     else
     if (x==c) {
            printf("\n"); break;
        }
     if (a_t_p[x]==0) printf("%5d ",b+x);
    }
}
//---------------------------------------------------------------------------

int __fastcall is_prime_A(__int64 i)
{
    if(i <= 1) return 0;
    __int32 sqrt_i = sqrt(i);
    for(__int64 n = 2; n <= sqrt_i; n++){
        if((i % n)  == 0)
           return 0;
    }
return 1;
}
//---------------------------------------------------------------------------

int prime_A() {

    int t = time(NULL);
    fstream plik;
    char nazwa_pliku[255], ts[10];
    strcpy(nazwa_pliku,"C:\\Kandydatki_A_");
    strcat(nazwa_pliku,itoa(t,ts,10));
    strcat(nazwa_pliku,".txt");

    plik.open(nazwa_pliku,ios::out);
    if (plik.is_open()==false) {
        cout<<"Problem z utworzeniem pliku: \""<<nazwa_pliku<<"\""<<endl;
        getch(); return 0;
    }
    plik<<"Ilosc liczb= " <<PRIME_END-PRIME_START<<endl;

    int T1 = time_ms(), T2 = T1;

	__int64 n = 0;
	for(__int64 i = PRIME_START; i <= PRIME_END;i++){

        if((i %  2) == 0) continue;
        if((i %  3) == 0) continue;
        if((i %  5) == 0) continue;
        if((i %  7) == 0) continue;

		if(is_prime_A(i) == 1){
			plik<<"N="<<++n<<", liczba="<<i<<endl;
		}
	}
    T2 = time_ms();
	printf("CZAS: %d ms\n",T2-T1);
    cout<<"KONIEC"<<endl;
    printf("NACISNIJ JAKIS KLAWISZ ABY ZAKONCZYC") ;getch();
    plik.close();
    return 0;
}
//---------------------------------------------------------------------------

void pierwiastki(int *a_tablica_sqrt, int a_count)
{
    int *r_t = a_tablica_sqrt, r_c = a_count; r_t[0] = 0;
    int  r_liczb;

    for (int x = 1; x < r_c; x++)
    {
       r_t[x] = floor(sqrt(x));
    if(r_t[x-1]!=r_t[x]) {
        if ((double)sqrt(r_liczb)==(double)floor(sqrt(r_liczb))) {
                 printf("%d\n",r_liczb); r_liczb = 1;
                 continue;
        }
    }
    else r_liczb++;
    }

}
//---------------------------------------------------------------------------

void sito(int *a_tablica_prime, int a_base, int a_prime_limit, int *a_tablica_s)
{
    int r_sqrt_x, *r_t_p = a_tablica_prime, nie_prime, liczba = 7;
    r_t_p[0] = 1;
    r_t_p[1] = 2;
    r_t_p[2] = 3;
    r_t_p[3] = 5;

    for (int x = 4, b = a_base, c = 4, l = a_prime_limit; x < l; x++) {
        nie_prime = 0;
        r_sqrt_x = sqrt(x);
        for (int a = 0; a < r_sqrt_x; a++) {
            if (x % a) {
                nie_prime = true;
                break;
            }
        }
        if (nie_prime==false) r_t_p[x] = liczba;
        liczba+=2;
    }

}
//---------------------------------------------------------------------------

int prime_B()
{
#define RANGE 1000
#define PRINT_RANGE 200

    int  tablica_sqrt[RANGE];
    pierwiastki(tablica_sqrt, RANGE);
    printf("KONIEC PIERWIASTKOW!\n");
    getchar();

    int tablica_prime[RANGE * RANGE];
    memset(&tablica_sqrt,RANGE,0);
    sito(tablica_prime, 0 ,RANGE * RANGE, tablica_sqrt);
    for (int z = 0; z < RANGE * RANGE; z+= PRINT_RANGE) {
         printf("Zakres od %d do %d:\n\r",z, z + PRINT_RANGE);
         druk(&tablica_prime[z], z, PRINT_RANGE);
         printf("Naciśnij \'x\' jeśli chcesz przerwać."); if (getchar()=='x') break;
    }

    printf("KONIEC!\n");
}
//---------------------------------------------------------------------------

int prime_M()
{
        int t = time(NULL);
        fstream plik;
        char nazwa_pliku[255], ts[10];
        strcpy(nazwa_pliku,"C:\\Kandydatki_M_");
        strcat(nazwa_pliku,itoa(t,ts,10));
        strcat(nazwa_pliku,".txt");

        int dz01[30] = {0,0,0,0,0,0,0,0,0,0, 0,1,2,3,4,5,6,7,8,9, 10,11,12,13,14,15,16,17,18,19};
        int ta20[ 8] = {                       1,2,3,      7,        11,   13,         17,   19};
        int dzXX[10] = { 0,10,20,30,40,50,60,70,80,90};
        int dz02[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,2,0,4,0,6,0,8,0, 10, 0,12, 0,14, 0,16, 0,18, 0};
        int dz03[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,3,0,0,6,0,0,9,  0, 0,12, 0, 0,15, 0, 0,18, 0};
        int dz04[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,4,0,0,0,8,0,  0, 0,12, 0, 0, 0,16, 0, 0, 0};
        int dz05[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,5,0,0,0,0, 10, 0, 0, 0, 0,15, 0, 0, 0, 0};
        int dz06[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,6,0,0,0,  0, 0,12, 0, 0, 0, 0, 0,18, 0};
        int dz07[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,7,0,0,  0, 0, 0, 0,14, 0, 0, 0, 0, 0};
        int dz08[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,8,0,  0, 0, 0, 0, 0, 0,16, 0, 0, 0};
        int dz09[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,9,  0, 0, 0, 0, 0, 0, 0, 0,18, 0};

        int tab1[10] = {11,13,17,19,23,29,31,37};
        int tab2[05] = {3,7,9};

        long long int liczba;
        int n=0;
        int L=1,L2=0;
        int ilosc_liczb;
        int L7=41;

        cout<<"Podaj ilosc liczb:";
        cin>>ilosc_liczb;
        plik.open(nazwa_pliku,ios::out);
        plik<<"Ilosc liczb= " <<ilosc_liczb<<endl;
        do {
             if ( L!=L7 )
                {
                    n =L-(8*int(L/8));
                if (n==0) n =8;
                liczba = int((L-n)/8)*30+tab1[n-1];
                plik<<"L="<<L<<", n="<<n<<", tab="<< tab1[n-1]<<", liczba="<<liczba<<endl;
                L2++;
                }
            else
                { L7+=8*7;
                }
        //cout<<liczba<<endl;
            } while(++L<=ilosc_liczb);

        cout<<"Ostatnia liczba pierwsza="<<L2<<endl;
        cout<<"Czas="<<t-time(NULL)<<endl;
        cout<<"KONIEC"<<endl;
        printf("NACISNIJ JAKIS KLAWISZ ABY ZAKONCZYC") ;getch();
        plik.close(); return 0;
}
//---------------------------------------------------------------------------

#pragma argsused
int prime_X()
{
__int32 X = 2,Y,I = 0,O = 0,N_MAX = 400000000, N2 = N_MAX/2;
char *P = new char[N_MAX];
#define prime 1
printf("N MAX =  %d\n\r",N_MAX) ;
int T1 = time_ms();

for (X = 2; X < N_MAX; X++)
	{
	for (Y = X; Y < N_MAX; Y+=X)
    	{
 		if (P[X]==prime) break;
        else
        	P[Y] =prime;
        }
    }
int T2 = time_ms();
printf("CZAS: %d ms\n\r",T2-T1) ;
cout<<"KONIEC"<<endl;
printf("NACISNIJ JAKIS KLAWISZ ABY ZAKONCZYC") ;getch();
delete P;
return 0;
}
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
prime_A();

return 0;
}
//---------------------------------------------------------------------------
