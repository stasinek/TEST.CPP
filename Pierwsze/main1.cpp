#if defined(QT_VERSION)
#include <QCoreApplication>
#endif

#include <math.h>
#include <memory.h>
#include <stdio.h>

void pierwiastki(int *a_tablica_sqrt, int a_count) {
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
#if defined(QT_VERSION)
    use namespace std;
#endif

int main(int argc, char *argv[])
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
#if defined(QT_VERSION)
    QCoreApplication a(argc, argv);
    return a.exec();
#endif

return 0;
}
