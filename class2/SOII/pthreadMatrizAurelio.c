#include <pthread.h>
#include <stdio.h>

int matriz[4][4] = {1,2,3,4,
                    5,6,7,8,
                    9,10,11,12,
                    13,14,15,16};
int linha = 4;
int coluna = 4;
int resultado = 0;
int soma = 0;
int total = 0;

void* resultSoma (void* param)
{ 
  int j;
  int *alg = (int*)param; 
  soma = 0;

  for (j=0; j<coluna; j++) {
    soma += alg[j];
  }
  return (void*) soma;
}


int main ()
{
  int i;
  pthread_t thread_id[linha];

  for (i=0; i<linha; i++) {
    /* Criando Thread */
    pthread_create (&thread_id[i], NULL, &resultSoma, matriz[i]);
  } 

  /* Print das linhas */ 
  for (i=0; i<linha; i++) {
    //Unindo resultados das Threads
    pthread_join (thread_id[i], (void*) &resultado);
    //total += resultado;
    printf("Linha %d: %d    %d \n",i+1,resultado,total);
    total += resultado;
  }
  //Print Total
  printf("Total: %d \n\n",total);
  return 0;
}
