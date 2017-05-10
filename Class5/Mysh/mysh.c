// Wesley Otto Garcia Utsunomiya
//Mini shell -> Faltou tratar ctrl + c e ctrl + c
//Tratamento to Prompt, acabar escondendo uma parte

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//Imprime o Prompt

void type_prompt(){
  char cwd[1024];
  char hostname[200];
  if (getcwd(cwd, sizeof(cwd)) != NULL) // Pego diretório local e aloco em cwd
  {
    gethostname(hostname,sizeof(hostname)); //Pego o nameuser e coloco em hostname
    fprintf(stdout, "[Mysg]%s@:%s ",hostname, cwd);
    printf("$ ");
  }
  else
     perror("getcwd() error");
}

int main(void) {

  char commands[256];
  char Xexit[10];
  int varExit;
  strcpy(Xexit,"exit");

  while(1){
      type_prompt();                              // Mostra o prmpt na tela
      fgets(commands,256,stdin);                  //lê a linha de entrada do teclado
       commands [strlen(commands) - 1 ] = '\0';   // tira se o "enter "\n
      varExit = strcmp(commands,Xexit);           // verifica se o comando passado é exit
      if(varExit == 0)                            // Exit
        exit(-1);

// Part Arg_list
      int i,j,numberoEspacos = 0;                 //Pego a qtd de espaços que tenho no meus comandos
      for(i = 0; i < strlen(commands);i++)
        if(commands[i] == ' ')
          numberoEspacos++;

      char* splitCommand;
      splitCommand = strtok(commands, " ");

      char** arg_list = (char**)malloc((numberoEspacos + 2) * sizeof(char*)); // aloco minha arg_list
      arg_list[0] = (char*)malloc(256 * sizeof(char));
      strcpy(arg_list[0], splitCommand);          // coloco meu comando em arg_list[0]

      j=1;
      splitCommand = strtok(NULL," ");

      while(splitCommand != NULL){
        arg_list[j] = (char*)malloc(256 * sizeof(char));
        strcpy(arg_list[j], splitCommand);        //Copio os argumentos para arg_list
        splitCommand = strtok(NULL, " ");
        j++;
      }

  //Cd part
  if(strcmp(arg_list[0],"cd") == 0){             //se meu primeiro argumento for cd
      if(numberoEspacos == 0){                  // verifico o numero de espaços, se for 0 , ou seja passar só Cd, passo home para minha arg_list
        char homeDir[50] = "";
          strcpy(homeDir, getenv("HOME"));
            arg_list[1] =  (char*)malloc(256 * sizeof(char));
            strcpy(arg_list[1], homeDir);
          }
          if(chdir(arg_list[1]) != 0)           // se não existir o diretório, ele dá erro
            fprintf(stderr, "cd: %s file or directory not found\n",arg_list[i] );
    continue;
  }

  //Criação de processo Pai e filho

     pid_t pid;
      pid = fork();                            // cria um processo filho
      if(pid < 0){
        printf("Unable to fork\n");           // condição de erro
        continue;                             // repete laço
      }

      int status;
      if( pid != 0 )
        waitpid(-1, &status,0);           // pai espera filho
      else{

        execvp(arg_list[0], arg_list);      // filho traz o trabalho
        fprintf (stderr, "Error: no such file or directory\n");
      }

        //Desalocando arg_list

        for(i = 0; i < numberoEspacos + 2; i++)
            free(arg_list[i]);
        free(arg_list);
  }
  return 0;
}
