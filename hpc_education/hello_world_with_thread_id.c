#include<stdio.h>
#include<omp.h>

void main() {

    omp_set_num_threads(4);
    int thread_id; 

    #pragma omp parallel
    {
        thread_id = omp_get_thread_num();
        printf("Thread: %d, Hello world!\n", thread_id);
    }
}