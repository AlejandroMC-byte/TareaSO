#include <unistd.h> // execv()
#include <stdio.h>  // perror()
#include <stdlib.h>
#include <time.h> // EXIT_SUCCESS, EXIT_FAILURE

#define READ  0
#define WRITE 1

int main(void) {
  srand(time(NULL));
  rand();
  int numAleatorio = rand()%1000+1;
  
  printf("\nNumero aleatorio:%i \n",numAleatorio);

  pid_t pid;
  int   fd[2];

  if (pipe(fd) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }
  pid = fork();

  if(pid==-1){
    perror("Fork error");
    exit(EXIT_FAILURE);
  }
  if(pid==0 && numAleatorio <500){
    	close(fd[WRITE]);
      dup2(fd[READ], STDIN_FILENO);
    //execlp("Menor que 500",NULL);
    printf("\nMenor que 500");
  }else if(pid==0 && numAleatorio >=500){
    	close(fd[WRITE]);
      dup2(fd[READ], STDIN_FILENO);
    //execlp("mayor que 500",NULL);
    printf("\nMayor o igual que 500");
  }else{
    close(fd[READ]);
	// Redirect STDOUT to write to the pipe.
	dup2(fd[WRITE], STDOUT_FILENO);
  printf("Padre: %i",getpid());
  }
}