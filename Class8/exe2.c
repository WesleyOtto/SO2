/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* We must define union semun ourselves.  */

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *__buf;
};

/* Obtain a binary semaphore's ID, allocating if necessary.  */

int binary_semaphore_allocation (key_t key, int sem_flags)
{
  return semget (key, 1, sem_flags);
}

/* Deallocate a binary semaphore.  All users must have finished their
   use.  Returns -1 on failure.  */

int binary_semaphore_deallocate (int semid)
{
  union semun ignored_argument;
  return semctl (semid, 1, IPC_RMID, ignored_argument);
}

/* Initialize a binary semaphore with a value of one.  */

int binary_semaphore_initialize (int semid)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl (semid, 0, SETALL, argument);
}


/* Wait on a binary semaphore.  Block until the semaphore value is
   positive, then decrement it by one.  */

int binary_semaphore_wait (int semid)
{
  struct sembuf operations[1];
  /* Use the first (and only) semaphore.  */
  operations[0].sem_num = 0;
  /* Decrement by 1.  */
  operations[0].sem_op = -1;
  /* Permit undo'ing.  */
  operations[0].sem_flg = SEM_UNDO;

  return semop (semid, operations, 1);
}

/* Post to a binary semaphore: increment its value by one.  This
   returns immediately.  */

int binary_semaphore_post (int semid)
{
  struct sembuf operations[1];
  /* Use the first (and only) semaphore.  */
  operations[0].sem_num = 0;
  /* Increment by 1.  */
  operations[0].sem_op = 1;
  /* Permit undo'ing.  */
  operations[0].sem_flg = SEM_UNDO;

  return semop (semid, operations, 1);
}

int main ()
{
  int segment_id;
  char* shared_memory;
  struct shmid_ds shmbuffer;
  int segment_size;
  int idsem;
  const int shared_segment_size = 0x6400;
  pid_t child_pid;

  idsem = binary_semaphore_allocation(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
  binary_semaphore_initialize(idsem);
  /* Allocate a shared memory segment.  */
  segment_id = shmget (IPC_PRIVATE, shared_segment_size,
		       IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

  /* Attach the shared memory segment.  */
  shared_memory = (char*) shmat (segment_id, 0, 0);
//  printf ("shared memory attached at address %p\n", shared_memory);
  /* Determine the segment's size.  */
  shmctl (segment_id, IPC_STAT, &shmbuffer);
  segment_size = shmbuffer.shm_segsz;
  //printf ("segment size: %d\n", segment_size);
  /* Write a 100 to the shared memory segment.  */
  sprintf (shared_memory,"%d" ,100);
  //printf ("%s\n", shared_memory);

  child_pid = fork ();
  int i, integer, result;
  for(i = 0 ; i <= 100000; i++){
    binary_semaphore_wait(idsem);
    sscanf (shared_memory, "%d", &integer);
    sprintf ((char*) shared_memory, "%d\n",++integer);
    sprintf ((char*) shared_memory, "%d\n", --integer);
    sscanf (shared_memory, "%d", &result);
    printf(" PID :%d number: %d \n",getpid(),result );
    binary_semaphore_post(idsem);
  }

  /* Deatch the shared memory segment.  */
  shmdt (shared_memory);
  /* Deallocate the shared memory segment.  */
  shmctl (segment_id, IPC_RMID, 0);
  binary_semaphore_deallocate(idsem);

  return 0;
}
