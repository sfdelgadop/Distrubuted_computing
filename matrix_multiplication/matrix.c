#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "matrix.h"

#define THREADS 16

void *multiply(int *id){
    int bash = SIZE/THREADS;
    int init = bash * *id;
    int end = init + bash;
    int i, j;
    double sum;

    do{
        for(i = 0; i < SIZE; i++){
            sum = 0.0;
            for(j = 0; j < SIZE; j++){
                sum += m1[init][j] * m2[j][i];
            }
            result[init][i] = sum;
        }
        init++;
    }while(init < end);
}

void print_result(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            printf("%1.8f ", result[i][j]);
        }
        printf("\n");
    }
}

int main(){

    struct timeval tval_before, tval_after, tval_result;
    gettimeofday(&tval_before, NULL);

    pthread_t thread[THREADS];
    int ok;
    int i_values[THREADS];

    for(int i = 0; i < THREADS; i++){
        i_values[i] = i;
        ok = pthread_create(&thread[i], NULL, (void *)multiply, (void*)&i_values[i]);
        if(ok < 0){
            perror("");
            exit(-1);
        }
    }

    for(int i = 0; i < THREADS; i++){
        ok = pthread_join(thread[i], NULL);
        if(ok < 0){
            perror("");
            exit(-1);
        }
    }

    gettimeofday(&tval_after, NULL);
    timersub(&tval_after,&tval_before,&tval_result);

    printf("Threads: %d\t", THREADS);
    printf("Time: %ld.%06lds\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    // print_result();
    
    return 0;
}