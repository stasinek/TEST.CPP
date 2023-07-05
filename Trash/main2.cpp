#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PATTERN_COUNT 5
#define PATTERN_LENGHT 11
int patterns[PATTERN_COUNT][PATTERN_LENGHT] = {

{0,1,2,9,3,0,1,2,9,3,1},
{3,1,4,9,3,9,1,2,9,1,9},
{6,1,1,1,8,9,3,9,9,1,9},
{0,1,9,9,9,9,1,1,9,2,1},
{1,8,6,1,9,7,1,2,9,9,1}

};
int *array = NULL;

void make_array(int asize)
{
if (array) array = (int*)realloc(array,asize);
else array = (int*)malloc(asize*sizeof(int));
for (int i = 0, r = 0; i < asize;)
	{
	// initialize random seed
	if (i%(PATTERN_COUNT*PATTERN_COUNT/2)==0) srand (time(NULL));
	r = rand() % PATTERN_COUNT; 
	// copy paste one of randomly chosen pattern defined to array
	for (int p = 0; p < PATTERN_LENGHT && i < asize; p++) 
		array[i++] = patterns[r][p]; 	
	}
}

void delete_array()
{
free(array); array = NULL;
}

int check_brute(int *n);
int check_smart(int *n);

int main(void)
{
 int status ;
 int n = 0, nmax = 256000000; // max ~ 2GB RAM on 64bit OS
 printf("Set number of ints example. 100000000 = 100mln ~ 400MB of RAM, \n\rMax is 2GB on 64bit OS, input whatever if you want max: ");
 scanf("%d",&n);
 if (n > nmax)  n = nmax;
 make_array(n);

 printf("Our random ARRAY small preview (up to 100 rows, made of %d element chunks):\n\r",PATTERN_LENGHT);
 for (int ipreview; ipreview < n; ipreview+=n/100+PATTERN_LENGHT) {
 	for (int ichunk = 0; ichunk < n && ichunk < PATTERN_LENGHT; ichunk++) 
			 printf("%d,",array[ipreview+ichunk]);
 	printf("\n\r");
	}

 int t1,t2,tdiff; // for benchmarking

#define CHECK(A_FUNCTION_NAME)		\
 printf ("\n\rTESTING " #A_FUNCTION_NAME "(%d) : 3..2..1.. GO\n\r",n);\
 t1 = time(NULL); 					\
 status = A_FUNCTION_NAME(&n);		\
 t2 = time(NULL);					\
 tdiff = t2-t1;						\
 printf ("time of execution, of " #A_FUNCTION_NAME "() for %d elements = %ds\n\r",n,tdiff);

CHECK(check_brute) //check brute force one
CHECK(check_smart) //check queue approch
 
 // doesn't test check anything right not, i just kept as much code as it was, 
 // dont have time for that crap 
 if(status == 1)
 printf("every one is followerd by 9");
 else
 printf("not all 1 is follow 9");
 
 delete_array();
 system("pause");
}

int check_smart(int *pin)
{

}

int check_brute(int *pin)
{
 int * p = 0;
 int flag = 0;
 int i;
 int j;
 int n = *pin ;
// p = (int*)malloc(n*sizeof(int));
 p = (int*)array;

 //for(i=0;i<n;i++)
 {
 
 //printf("please enter the elements for p[%d] ",i);
 //scanf("%d",(p+i));
 
 }


 for(i=0;i<n;i++)
 {
 
 if(*(p + i)==1)
 {
 j = i + 1;
 
 while( j < n )
 {
 if(*(p+j)==9)
 break;
 j++;
 }
 if(j==n)
 flag = 1;
 else{
 *(p + i ) = 0;
 *(p + j ) = 0;
 }

 }
 }
 
 if(flag == 1)
 return 0;
 else 
 return 1;
}
