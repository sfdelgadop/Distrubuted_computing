#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ITERATIONS 1.0e+9
#define THREADS 16

double pi_total[THREADS];

void *pi_calc(int *id){
    int bash = ITERATIONS/THREADS;
    int init = bash * *id;
    int end = init + bash;

    do{
        pi_total[*id] = pi_total[*id] + 4.0/((2*init)+1);
        init++;
        pi_total[*id] = pi_total[*id] - 4.0/((2*init)+1);
        init++;
    }while(init < end);
}

int main(){

    struct timeval tval_before, tval_after, tval_result;
    gettimeofday(&tval_before, NULL);

    pthread_t thread[THREADS];
    int ok;
    int i_values[THREADS];
    double pi = 0.0;

    for(int i = 0; i < THREADS; i++){
        i_values[i] = i;
        ok = pthread_create(&thread[i], NULL, (void *)pi_calc, (void*)&i_values[i]);
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
        pi += pi_total[i];
    }

    gettimeofday(&tval_after, NULL);
    timersub(&tval_after,&tval_before,&tval_result);

    printf("Time: %ld.%06lds\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    printf("Threads: %d\n", THREADS);
    printf("Pi: %1.20f\n", pi);
    
    return 0;
}