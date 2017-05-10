#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <inttypes.h>

void nada()
{

}
int main( int argc, char *argv[ ] )
{
    int barber = 0 , chair_wait = 0 , time_cut = 0, time_next_customers = 0;
    int i = 0;

    barber = atoi(argv[1]);
    chair_wait = atoi(argv[2]);
    //time_cut = atoi(argv[3]);
    //time_next_customers = atoi(argv[4]);

    printf("barber %d\n",barber );
    printf("barber %d\n",chair_wait );


    return 0;
}
