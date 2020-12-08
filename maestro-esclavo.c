/**
 * @file ejercicio5.c
 * @author Marvin Peinado Vidaña
 * @brief 
 * @version 0.1
 * @date 2020-12-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>

int esPrimo(int num);

int main(int argc, char *argv[]){
    //[0,1000]
    //Padre crea a dos hijos

    //Padre -> H1 [0-500] - H2 [501-1000]
    //H1 -> P
    //H2 -> P

    //./maestro 0 1000

    int minA, maxA;
    int minB, maxB;
    int fdM[2];
    pid_t PID1, PID2;
    int primo;

    if(argc != 3){
        printf("Sintaxis de ejecucion incorrecta\n");
        exit(-1);
    }

    minA = strtol(argv[1],NULL,10);
    maxB = strtol(argv[2],NULL,10);
    maxA = (minA + maxB)/2;
    minB = maxA + 1;

    pipe(fdM);

    if ((PID1 = fork()) == 0){
        
        //esclavo 1 (hijo 1)
        close(fdM[0]);

        dup2(fdM[1], STDOUT_FILENO);

        int i;

        for(i = minA; i <= maxA ; i++) {
            if(esPrimo(i)){
                write(fdM[1], &i, sizeof(int));
            }
        }

    }else if((PID2 = fork()) == 0){

        // esclavo 2 (hijo 2)
        close(fdM[0]);

        int i;

        for(i = minB; i <= maxB ; i++) {
            if(esPrimo(i)){
                write(fdM[1], &i, sizeof(int));
            }
        }

    }else{

        //maestro (padre)
        close(fdM[1]);

        while((read(fdM[0], &primo, sizeof(int))) != 0) {
            printf("%d\n",primo);
        }

    }

}


int esPrimo(int num){
    int i;
    int bandera = 1;

    for(i = 2 ; i <= sqrt(num) ; i++){
        if(num % i == 0){
            bandera = 0;
        }
    }

    return bandera;
}