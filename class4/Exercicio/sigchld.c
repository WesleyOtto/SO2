/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

sig_atomic_t child_exit_status;

void clean_up_child_process (int signal_number)
{
  /* Clean up the child process.  */
  int status;
  wait (&status);
  /* Store its exit status in a global variable.  */
  child_exit_status = status;
}

int main ()
{
  /* Handle SIGCHLD by calling clean_up_child_process.  */
  struct sigaction sigchld_action;
  memset (&sigchld_action, 0, sizeof (sigchld_action));
  sigchld_action.sa_handler = &clean_up_child_process;
  sigaction (SIGCHLD, &sigchld_action, NULL);

  /* Now do things, including forking a child process.  */
  /* ...  */

  pid_t child_pid;
  int i = 0;
  int t = -1;
  while( t!= 0 )
  {
    printf("Digite quantos segundos o filho deve viver (ou 0 para encerrar): \n");
    while(t== -1 ) scanf("%i\n",&t );
    if(t==0) return 0;
    i++;
    printf("Criando %d processo filho, vivera %d segundos\n",i,t );
    child _pid = fork();
    if(child_pid == 0)
    {
      sleep(t);
      return(0);
    }
    t = -1;
  }


  return 0;
}
