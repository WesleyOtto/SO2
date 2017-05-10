/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
  int segment_id;
  char* shared_memory;
  struct shmid_ds shmbuffer;
  int segment_size;
  const int shared_segment_size = 0x6400;
  pid_t child_pid;

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
    sscanf (shared_memory, "%d", &integer);
    sprintf ((char*) shared_memory, "%d\n",++integer);
    sprintf ((char*) shared_memory, "%d\n", --integer);
    sscanf (shared_memory, "%d", &result);
    printf(" PID :%d number: %d \n",getpid(),result );
  }

  /* Deatch the shared memory segment.  */
  shmdt (shared_memory);
  /* Deallocate the shared memory segment.  */
  shmctl (segment_id, IPC_RMID, 0);

  return 0;
}
