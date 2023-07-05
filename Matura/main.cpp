#include <iostream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
__int32 dostawasiana(__int32 dzien){
	if (dzien==7) return 15000;
	if (dzien >7 && dzien%7==0) return 15000;
	else return 0;
}

__int32 dostawaz(__int32 dzien) {
	if (dzien==4) return 4000;
	if ((dzien-4)>=7 && (dzien-4)%7==0) return 4000;
	else return 0;
}
int main(int argc, char** argv) {
	__int32 zubrow = 90, siana = 100000, zoledzi = 5000;
	__int32 tylko_sianem = 0, tylko_zoledziami = 0, dostaw_s = 0, dostaw_z = 0;
	__int32 d, d_pierwszyraz_z = 0, dni = 90;
	
	for (d = 1; d<=90; d++) {
		if (siana >= 50000) {
			tylko_sianem++;
			siana -= zubrow * 40;
		}
		else {
			if (!d_pierwszyraz_z) d_pierwszyraz_z = d;
			tylko_zoledziami++;
			zoledzi-= zubrow * 20;
					}
		if (dostawasiana(d)) { dostaw_s++; siana+=dostawasiana(d); }
		if (dostawaz(d)) { dostaw_z++; zoledzi+=dostawaz(d); }
	}
	printf("siana %d\nzoledzi %d\ntylko sianem %d\ntylko zoledziami %d\n pierwszy dzien zoledziami %d\n dostaw siana %d \n dostaw zoledzi %d", 
			siana,zoledzi, tylko_sianem,tylko_zoledziami, d_pierwszyraz_z, dostaw_s, dostaw_z);
	FILE *plik = fopen("wyniki4.txt","w");
	fprintf(plik, "a siana %d zoledzi %d\n b %d\n c tylko sianem %d tylko zoledziami %d\n ", 
			siana,zoledzi, d_pierwszyraz_z, tylko_sianem ,tylko_zoledziami, d_pierwszyraz_z);
	fclose(plik);	
	return 0;
}
