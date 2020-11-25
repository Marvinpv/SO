#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include <sys/types.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
    pid_t pid;
    pid_t hijo_esperado;
    int i;

    for(i = 0 ; i < 5 ; i++){
        if((pid = fork()) < 0){
            perror("Error en el fork\n");
            exit(-1);
        }
        
        if(!pid){
            break;
        }
    }


    if(pid){
        while(i > 0){
            hijo_esperado = wait(0);
            printf("Ha terminado mi hijo con PID: %d\n",hijo_esperado);
            i--;
            printf("Quedan %d hijos executando...\n",i);
        }
    }else{
        printf("Soy el hijo PID\n");
        exit(0);
    }

    return 0;
}