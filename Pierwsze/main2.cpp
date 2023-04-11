#include <Windows.h>

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
using namespace std;

int main(int argc, char** argv)
{
        int t = time(NULL);
        srand(t);
        fstream sik;
        char nazwa_siku[255], ts[10];
        strcpy(nazwa_siku,"C:\\Kandydatki_");
        strcat(nazwa_siku,_itoa(t,ts,10));
        strcat(nazwa_siku,".txt");

        int dz01[30] = {0,0,0,0,0,0,0,0,0,0, 0,1,2,3,4,5,6,7,8,9, 10,11,12,13,14,15,16,17,18,19};
        int ta20[ 8] = {                       1,2,3,      7,        11,   13,         17,   19};
        int dzXX[10] = {00,10,20,30,40,50,60,70,80,90};
        int dz02[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,2,0,4,0,6,0,8,0, 10,00,12,00,14,00,16,00,18,00};
        int dz03[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,3,0,0,6,0,0,9, 00,00,12,00,00,15,00,00,18,00};
        int dz04[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,4,0,0,0,8,0, 00,00,12,00,00,00,16,00,00,00};
        int dz05[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,5,0,0,0,0, 10,00,00,00,00,15,00,00,00,00};
        int dz06[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,6,0,0,0, 00,00,12,00,00,00,00,00,18,00};
        int dz07[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,7,0,0, 00,00,00,00,14,00,00,00,00,00};
        int dz08[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,8,0, 00,00,00,00,00,00,16,00,00,00};
        int dz09[30] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,9, 00,00,00,00,00,00,00,00,18,00};

        int tab1[10] = {11,13,17,19,23,29,31,37};
        int tab2[05] = {3,7,9};

        long long int liczba;
        int n=0;
        int L=1,L2=0;
        int ilosc_liczb;
        int L7=41;

        cout<<"Podaj ilosc liczb:";
        cin>>ilosc_liczb;
        sik.open(nazwa_siku,ios::app);
        sik<<"Ilosc liczb= " <<ilosc_liczb<<endl;
        do {
             if ( L!=L7 )
                {
                    n =L-(8*int(L/8));
                if (n==0) n =8;
                liczba = int((L-n)/8)*30+tab1[n-1];
                sik<<"L="<<L<<", n="<<n<<", tab="<< tab1[n-1]<<", liczba="<<liczba<<endl;
                L2++;
                }
            else
                { L7+=8*7;
                }
        //cout<<liczba<<endl;
            } while(++L<=ilosc_liczb);
        sik.close();
        cout<<"Ostatnia liczba pierwsza="<<L2<<endl;
        cout<<"Czas="<<t-time(NULL)<<endl;
        cout<<"KONIEC"<<endl;
        getch(); return 0;
}

