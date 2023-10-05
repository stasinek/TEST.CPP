/*
   chlopaki_nie_pi_io.c
   2019-07-03 // sstasinek 2023-10-5
   Public Domain
   gcc -o minimal_pi_io_ minimal_pi_io_.c
   sudo ./minimal_pi_io_
*/
// inne biblioteki https://github.com/Milliways2/pi-gpio
// https://github.com/search?q=gpio&type=repositories&s=stars&o=desc
// nie testowane, mo¿e byæ baza do w³asnej prostej biblioteki sterowania portami
// a mo¿e byæ tylko strata czasu :>
// przerobi³em na kolanie, 
// ¿eby pokazaæ co jest za kotar¹ czarownika z Oz 
// nawet nie mam Raspberry kiedyœ kupiê ¿eby sprawdziæ czy poprawnie mapowane s¹ piny
//----------------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
//----------------------------------------------------------------------------
#ifdef __linux__
	#include <sys/mman.h>
    // linux funkcja mmap mapuje plik /dev/gpiochip0 lub interfejs dostêpu pamiêci fizycznej /dev/mem
	// do adresów pamiêci virtualnej procesu, tak jakby by³o stworzone przez malloc
	// i mo¿emy udawaæ ¿e bawimy siê pamiêci¹ - pinami bezpoœrednio
	#include <sys/stat.h>
	#include <sys/types.h>
#elif __FreeBSD__
	// BSD
#elif __APPLE__
	// MacOS X
#elif _WIN32
    // W windows odpowiednikiem Linuxowego mmap jest MapViewOfFile niestety nie zadzia³a w userlandzie
    // nawet gdyby to by³o Raspberry na Windows, bo dostêp do pamiêci fizycznej ma tylko sterownik, a Windows nie mapuje pamiêci do plików,
	// tak jak linux /dev/mem 
	// Ale teoretycznie mo¿na napisaæ pseudo sterownik dowolnego urz¹dzenia IO 
	// Podpiêtego w dowolny sposób do komputera, 
	// mo¿e to byæ COM do dowolnego albo nawet stare poczciwe LPT
	// Mo¿na te¿ zapisywaæ dane do pliku wspó³dzieliæ miêdzy
    // dwoma procesami, jeden proces faktycznie mapuje dowolne IO do formatu zgodnego z GPIO z Raspberry
    // Mo¿e to byæ inny program symulacyjny albo czytaj¹cy z dowolnego portu, 
    // A nasz process po prostu odczytuje plik z dysku, mapuje go do pamiêci procesu
	// to udajemy pod Windowsem jakby to by³ Linux i jakbyœmy mieli Raspbery Pi pod rêk¹
	// i robimy sobie symulator Raspberry ;) 
	// musia³bym mieæ ¿eby sprawdziæ czy to siê kupy trzyma nie mam, nie staæ mnie
	
	// Jeœli zapiszesz ten program jako main.cpp
	// domyslnie ustawi³em tak linia 325 ¿e program otworzy "main.cpp" wyœwietli zawatoœæ 
	// ustaw COM1, LPT1 przerób pokombinuj rób co chcesz albo kup Raspberry i nie marudŸ 
	// https://www.elektroda.pl/rtvforum/topic1884119.html
	// skompiluje siê pod Linuxem i MinGW te¿!
    #include <windows.h>
#endif
//----------------------------------------------------------------------------
// dla Raspbery 2 i wzwy¿ adres bazowy jest bez zmian
#define BCM2708_PERI_BASE 0x20000000
static volatile uint32_t pi_io_BASE = BCM2708_PERI_BASE;
static volatile int pi_is_2711 = 0; // Pi 4
//----------------------------------------------------------------------------
// Wszystkie pisane wielkimi literami to definicje niezmienialne
// pio_io_BASE jest modyfikowane zale¿nie od tego czy s¹ uprawienia roota do /dev/mem
// czy ewentualnie /dev/gpiochip, ró¿nica taka ¿e /dev/mem przechowuje adres bezwzglêdny wiêc potrzebny BASE,
// musisz œciœle wiedzieæ jaka jest platforma jaki ma adres GPIO
// /dev/gpio jest tworzone przez specyficzny sterownik w pamiêci kernela, które ju¿ wie gdzie mapowany jest IO
// ten interfejs zadzia³a na Orand¿e pi i na innych podróbach  
#define SYST_BASE  (pi_io_BASE + 0x003000)
#define DMA_BASE   (pi_io_BASE + 0x007000)
#define CLK_BASE   (pi_io_BASE + 0x101000)
#define GPIO_BASE  (pi_io_BASE + 0x200000)
#define UART0_BASE (pi_io_BASE + 0x201000)
#define PCM_BASE   (pi_io_BASE + 0x203000)
#define SPI0_BASE  (pi_io_BASE + 0x204000)
#define I2C0_BASE  (pi_io_BASE + 0x205000)
#define PWM_BASE   (pi_io_BASE + 0x20C000)
#define BSCS_BASE  (pi_io_BASE + 0x214000)
#define UART1_BASE (pi_io_BASE + 0x215000)
#define I2C1_BASE  (pi_io_BASE + 0x804000)
#define I2C2_BASE  (pi_io_BASE + 0x805000)
#define DMA15_BASE (pi_io_BASE + 0xE05000)
//----------------------------------------------------------------------------
// iloœæ pinów, buforów itd.
#define DMA_LEN   0x1000  /* allow access to all channels */
#define CLK_LEN   0xA8
#define GPIO_LEN  0xF4
#define SYST_LEN  0x1C
#define PCM_LEN   0x24
#define PWM_LEN   0x28
#define I2C_LEN   0x1C
#define BSCS_LEN  0x40
//----------------------------------------------------------------------------
#define GPSET0 7
#define GPSET1 8
//
#define GPCLR0 10
#define GPCLR1 11
//
#define GPLEV0 13
#define GPLEV1 14
// Zegary i dzielnik?
#define GPPUD     37
#define GPPUDCLK0 38
#define GPPUDCLK1 39
//----------------------------------------------------------------------------
// BCM2711 z Raspbery Pi 4 ma inne definicje
// definicje do rejestru kontrolnego
#define GPPUPPDN0 57
#define GPPUPPDN1 58
#define GPPUPPDN2 59
#define GPPUPPDN3 60
// Licznik 
#define SYST_CS  0
#define SYST_CLO 1
#define SYST_CHI 2
// W przypadku b³êdu otwarcia, braku uprawnieñ roota zwróci adress 0xFFFFFF..  
#ifndef MAP_FAILED
#define MAP_FAILED ((uint32_t*)-1)
#endif
// Trzy zmienne, piny, infosystemie, rejestry kontrolne,
static volatile uint32_t  *pi_io_PIN_REGISTER = (uint32_t*)MAP_FAILED;
static volatile uint32_t  *pi_io_SYS_REGISTER = (uint32_t*)MAP_FAILED;
static volatile uint32_t  *pi_io_CONTROL_REGISTER = (uint32_t*)MAP_FAILED;
// Makra pomocnicze, 
#define PI_BANK(dbank) (dbank>>5)
#define PI_BIT(dbit)  (1<<(dbit&0x1F))
// Tryby pracy pinów 
#define PI_INPUT  0
#define PI_OUTPUT 1
#define PI_ALT0   4
#define PI_ALT1   5
#define PI_ALT2   6
#define PI_ALT3   7
#define PI_ALT4   3
#define PI_ALT5   2

void pi_io_SetMode(unsigned jaki_pin, unsigned jaki_mode)
{
   int reg, shift;

   reg   =  jaki_pin/10;
   shift = (jaki_pin%10) * 3;

   pi_io_PIN_REGISTER[reg] = (pi_io_PIN_REGISTER[reg] & ~(7<<shift)) | (jaki_mode<<shift);
}

int pi_io_GetMode(unsigned jaki_pin)
{
   int reg, shift;

   reg   =  jaki_pin/10;
   shift = (jaki_pin%10) * 3;

   return (*(pi_io_PIN_REGISTER + reg) >> shift) & 7;
}

//----------------------------------------------------------------------------
// Wartoœci dla rezystorów podci¹gaj¹cych domyslnie w górê w dó³
// lub wisz¹ce luŸno OFF

#define PI_PUD_OFF  0
#define PI_PUD_DOWN 1
#define PI_PUD_UP   2

void pi_io_SetPullUpDown(unsigned jaki_pin, unsigned jaki_pud)
{
   int shift = (jaki_pin & 0xf) << 1;
   uint32_t bits;
   uint32_t pull;

   if (pi_is_2711)
   {
      switch (jaki_pud)
      {
         case PI_PUD_OFF:  pull = 0; break;
         case PI_PUD_UP:   pull = 1; break;
         case PI_PUD_DOWN: pull = 2; break;
      }

      bits = *(pi_io_PIN_REGISTER + GPPUPPDN0 + (jaki_pin>>4));
      bits &= ~(3 << shift);
      bits |= (pull << shift);
      *(pi_io_PIN_REGISTER + GPPUPPDN0 + (jaki_pin>>4)) = bits;
   }
   else
   {
      *(pi_io_PIN_REGISTER + GPPUD) = jaki_pud;

      usleep(20);

      *(pi_io_PIN_REGISTER + GPPUDCLK0 + PI_BANK(jaki_pin)) = PI_BIT(jaki_pin);

      usleep(20);
  
      *(pi_io_PIN_REGISTER + GPPUD) = 0;

      *(pi_io_PIN_REGISTER + GPPUDCLK0 + PI_BANK(jaki_pin)) = 0;
   }
}
//----------------------------------------------------------------------------
// ODCZYT PORTU, podajesz tylko numer pinu
//----------------------------------------------------------------------------

int pi_io_Read(unsigned jaki_pin)
{
   if ((*(pi_io_PIN_REGISTER + GPLEV0 + PI_BANK(jaki_pin)) & PI_BIT(jaki_pin)) != 0) return 1;
   else                                         return 0;
}
//----------------------------------------------------------------------------
// Zapis pinów, podajesz tylko numer pinu, jaki stan chcesz zapisaæ
//----------------------------------------------------------------------------

void pi_io_Write(unsigned jaki_pin, unsigned jaki_level)
{
   if (jaki_level == 0) *(pi_io_PIN_REGISTER + GPCLR0 + PI_BANK(jaki_pin)) = PI_BIT(jaki_pin);
   else            *(pi_io_PIN_REGISTER + GPSET0 + PI_BANK(jaki_pin)) = PI_BIT(jaki_pin);
}
//----------------------------------------------------------------------------
// Zmieñ stan na chwilê, podajesz numer pinu, czas w mikrosekundach, level 1 oznacza pozytywne zbocze, 
//----------------------------------------------------------------------------

void pi_io_Trigger(unsigned jaki_pin, unsigned jaki_pulse_len, unsigned jaki_level)
{
   if (jaki_level == 0) *(pi_io_PIN_REGISTER + GPCLR0 + PI_BANK(jaki_pin)) = PI_BIT(jaki_pin);
   else            *(pi_io_PIN_REGISTER + GPSET0 + PI_BANK(jaki_pin)) = PI_BIT(jaki_pin);

   usleep(jaki_pulse_len);

   if (jaki_level != 0) *(pi_io_PIN_REGISTER + GPCLR0 + PI_BANK(jaki_pin)) = PI_BIT(jaki_pin);
   else            *(pi_io_PIN_REGISTER + GPSET0 + PI_BANK(jaki_pin)) = PI_BIT(jaki_pin);
}

//----------------------------------------------------------------------------
// Czytaj ca³y port
/* Bit (1<<x) will be set if pi_io x is high. */
//----------------------------------------------------------------------------

uint32_t pi_io_ReadBank1(void) { return (*(pi_io_PIN_REGISTER + GPLEV0)); }
uint32_t pi_io_ReadBank2(void) { return (*(pi_io_PIN_REGISTER + GPLEV1)); }

//----------------------------------------------------------------------------
// Wyczyœæ ca³y port
/* To clear pi_io x bit or in (1<<x). */
//----------------------------------------------------------------------------

void pi_io_ClearBank1(uint32_t bits) { *(pi_io_PIN_REGISTER + GPCLR0) = bits; }
void pi_io_ClearBank2(uint32_t bits) { *(pi_io_PIN_REGISTER + GPCLR1) = bits; }

//----------------------------------------------------------------------------
// Ustaw ca³y port np. 0x00000110
/* To set pi_io x bit or in (1<<x). */
//----------------------------------------------------------------------------

void pi_io_SetBank1(uint32_t bits) { *(pi_io_PIN_REGISTER + GPSET0) = bits; }
void pi_io_SetBank2(uint32_t bits) { *(pi_io_PIN_REGISTER + GPSET1) = bits; }

//----------------------------------------------------------------------------
// Funkcja pomocnicza, informacje o systemie
//----------------------------------------------------------------------------

unsigned pi_io_HardwareRevision(void)
{
   static unsigned rev = 0;

   FILE *filp;
   char buf[512];
   char term;
   int chars=4; /* number of chars in revision string */

   filp = fopen ("/proc/cpuinfo", "r");

   if (filp != NULL)
   {
      while (fgets(buf, sizeof(buf), filp) != NULL)
      {
         if (!strncasecmp("revision", buf, 8))
         {
            if (sscanf(buf+strlen(buf)-(chars+1),
               "%x%c", &rev, &term) == 2)
            {
               if (term != '\n') rev = 0;
               else rev &= 0xFFFFFF; /* mask out warranty bit */
            }
         }
      }

      fclose(filp);
   }

   if (filp = fopen("/proc/device-tree/soc/ranges" , "rb"))
   {
      if (fread(buf, 1, sizeof(buf), filp) >= 8)
      {
         pi_io_BASE = buf[4]<<24 | buf[5]<<16 | buf[6]<<8 | buf[7];
         if (!pi_io_BASE)
            pi_io_BASE = buf[8]<<24 | buf[9]<<16 | buf[10]<<8 | buf[11];

         if (pi_io_BASE == 0xFE00000) pi_is_2711 = 1;
      }
      fclose(filp);
   }

   return rev;
}

//----------------------------------------------------------------------------
/* Zwróci czas od uruchomienia systemu, zapêtli siê po 11 dniach */
//----------------------------------------------------------------------------

uint32_t pi_io_Tick(void) { return pi_io_SYS_REGISTER[SYST_CLO]; }

//----------------------------------------------------------------------------
// Funkcja pomocnicza mapowania rejestrów do zmiennych np. pi_io_PIN_REGISTER
//----------------------------------------------------------------------------

static uint32_t * pi_io_initMapMem(int ja_file, uint32_t ja_addr, uint32_t ja_len)
{
#ifdef _WIN32 // udajemy ¿e to Linux
    uint32_t *bufor = MAP_FAILED; 
    HANDLE hFile = (HANDLE)_get_osfhandle(ja_file); 
	// konwersja Linuxowego file descriptor na Windowsowy uchwyt do pliku
	HANDLE hMapFile = CreateFileMapping(hFile,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write
                 0,                       // maximum object size (high-order DWORD)
                 ja_len,                	  // maximum object size (low-order DWORD)
                 "CHLOPAKI_NIE_PI_IO");   // name of mapping object
   if (hMapFile != NULL) bufor = (uint32_t *) MapViewOfFile(hMapFile,   // handle to map object
                        FILE_MAP_ALL_ACCESS, // read/write permission
                        0,
                        0,
                        ja_len);
	return bufor;
#else // Linux
                    
#ifndef PROT_READ
#define PROT_READ		0x1			/* Page can be read.  */
#define PROT_WRITE		0x2			/* Page can be written.  */
#define PROT_EXEC		0x4			/* Page can be executed.  */
#define PROT_NONE		0x0			/* Page can not be accessed.  */
#define MAP_SHARED		0x01		/* Share changes.  */
#define MAP_PRIVATE		0x02		/* Changes are private.  */
#define MAP_TYPE		0x0f		/* Mask for type of mapping.  */
#define MAP_LOCKED		0x02000
#endif
										    
    return (uint32_t *) mmap(0, ja_len,
       PROT_READ|PROT_WRITE|PROT_EXEC,
       MAP_SHARED|MAP_LOCKED,
       ja_file, ja_addr);
#endif
}
//----------------------------------------------------------------------------
// Inicjalizacja systemu, sprawdzenie uprawnieñ, otwarcie portów
//----------------------------------------------------------------------------
int pi_io_Initialise(void)
{
   int ja_file;
   pi_io_HardwareRevision(); /* sets rev and peripherals base address */
	#ifndef O_SYNC // Windows
	#define O_SYNC 0x01000
	// "C:\\jaki_plik_zechcesz.txt" zpisuj go jednym processem symulatora, testera tak jakby to by³o Raspbery /dev/gpgpio 
	// a tym procesem komunikuj siê ze swoim pajtonem, php, innym programem
	// jak ju¿ kupisz prawdziwe Raspberry skompiluj na Raspbery Pi tak jak powinno byæ
	#define MY_PIJAJO_DEVICE_MEMORY_FILE "main.cpp"
	// #define MY_PIJAJO_DEVICE_MEMORY_FILE "LPT1" 
//LPT otwiera siê jak plik rozmiarze 1 bajt https://www.elektroda.pl/rtvforum/topic1884119.html
	// #define MY_PIJAJO_DEVICE_MEMORY_FILE "COM1"  dawno siê nie bawi³em COM wiêc nie wiem... 
	#else
	#define MY_PIJAJO_DEVICE_MEMORY_FILE "/dev/mem"
	#endif 

   ja_file = open(MY_PIJAJO_DEVICE_MEMORY_FILE, O_RDWR | O_SYNC) ;

   if (ja_file < 0)
   {
      fprintf(stderr,
         "This program needs root privileges.  Try using sudo\n");
      return -1;
   }

   pi_io_PIN_REGISTER  = pi_io_initMapMem(ja_file, GPIO_BASE,  GPIO_LEN);
   pi_io_SYS_REGISTER  = pi_io_initMapMem(ja_file, SYST_BASE,  SYST_LEN);
   pi_io_CONTROL_REGISTER  = pi_io_initMapMem(ja_file, BSCS_BASE,  BSCS_LEN);

   close(ja_file);

   if ((pi_io_PIN_REGISTER == MAP_FAILED) ||
       (pi_io_SYS_REGISTER == MAP_FAILED) ||
       (pi_io_CONTROL_REGISTER == MAP_FAILED))
   {
      fprintf(stderr,
         "Bad, mmap failed\n");
      return -1;
   }
   return 0;
}
//----------------------------------------------------------------------------
// G³ówny interfejs programu definiujesz tutaj
//----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
   int i;

   if (pi_io_Initialise() < 0) return 1;

   for (i=0; i<54; i++)
   {
      printf("jaki_pin=%d tick=%u mode=%d level=%d\n",
         i, pi_io_Tick(), pi_io_GetMode(i), pi_io_Read(i));
   }

   for (i=0; i<16; i++)
   {
      printf("reg=%d val=%8X\n",
         i, pi_io_CONTROL_REGISTER[i]);
   }

   return 0;
}
