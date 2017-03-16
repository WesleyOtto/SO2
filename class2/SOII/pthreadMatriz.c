#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <pthread.h>

#define NUM_CORE 4

int m[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

int aux[4][4];

pthread_mutex_t mutex;

void *thread(void *args)
{
   	int i, j, n;
	int id = (int) args;
	int block = n/NUM_CORE;
   		
	for (i= id*block ; i<=(id*block)+(block-1); i++)
	{
		for(j=0;j<n;j++)
      		{
		    // Calcula a soma dos valores referentes à linha
		    aux[i][j] = m[i-1][j] + m[i][j-1] + m[i+1][j] + m[i][j+1];
	      	}
	}
	return NULL;
}
     
int main()
{
   int i = 0;
   int j = 0;
   int n = 0;
      
   pthread_t threads[NUM_CORE];

   pthread_mutex_init(&mutex, NULL);
   
   for (i=0; i<NUM_CORE; i++) {
		if (pthread_create(&threads[i], NULL, thread, (void *)i)) {
			printf("could not create thread\n");
			exit(-1);
		}
	}

	void *status;
	for (i=0; i<NUM_CORE; i++) {
		if (pthread_join(threads[i], &status)) {
			printf("could not join thread\n");
			exit(-1);
		}
	}
	
   int acc = 0;
   for(i=0;i<n;i++)
   {
      for(j=0;j<n;j++)
      {
         printf(" Linha %d: %d ", i, aux[i][j]);
         acc = acc + aux[i][j];
      }
      printf("\n");
   }
   printf(" Total: %d", acc);

   return 0;
}

     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
