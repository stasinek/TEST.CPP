#include <cstdlib>

#include <iostream>

#include <cstdio>

#include <pthread.h>

#define NUMBER_OF_THREADS 10



using namespace std;



void *phw(void *tid)

{

	printf("Thread no.: %d\n", tid);

	pthread_exit(NULL);	

}



int main()

{

	pthread_t thr[NUMBER_OF_THREADS];

	int status, i;

	

	for (i=0; i<NUMBER_OF_THREADS; i++)

	{

		printf("Hello World %d\n", i);

		status = pthread_create(&thr[i], NULL, phw, &i);

	}
	getchar();
	system("pause");

}
