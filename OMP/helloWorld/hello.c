#include <stdio.h>
#include "omp.h"

void main(){
    #pragma omp parallel num_threads(8) //inicio de region paralela
    {
        int ID = omp_get_thread_num();
        printf(" hello( %d) ", ID);
        printf(" world( %d) \n", ID);
    } //fin de region paralela
}