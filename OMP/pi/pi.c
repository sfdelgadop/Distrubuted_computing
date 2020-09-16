#include <stdio.h>
#include <sys/time.h>
#include "omp.h"

#define THREADS 16
#define CICLES 1e09

void main(){

    struct timeval tval_before, tval_after, tval_result;
    gettimeofday(&tval_before, NULL);

    double pi = 0.0;
    int it = CICLES;
    #pragma omp parallel for reduction(+:pi) num_threads(THREADS)
    for(int i = 0; i < it; i++){
        pi = pi + (double)(4.0 / (2*i+1));
        i++;
        pi = pi - (double)(4.0 / (2*i+1));
    }

    gettimeofday(&tval_after, NULL);
    timersub(&tval_after,&tval_before,&tval_result);

    printf("Time: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    printf("Threads: %d\n", THREADS);
    printf("Pi: %0.20f\n", pi);
}