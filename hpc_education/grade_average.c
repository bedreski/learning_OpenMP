#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>

#define N 2500

int main() {

    int A[N], B[N] = {0};
    int i;
    double average_A, average_B, sum_A = 0, sum_B = 0;
    double start_time, end_time; 

    srand(time(NULL));

    for(i = 0; i < N; i++) {
        A[i] = rand() % 100 + 1;
        B[i] = rand() % 100 + 1;
    }

    start_time = omp_get_wtime();

    omp_set_num_threads(4); 

    #pragma omp parallel for if(N > 1000) reduction(+:sum_A, sum_B)
    for(i = 0; i < N; i++) {
        sum_A += A[i];
        sum_B += B[i];
    }

    end_time = omp_get_wtime();
    
    average_A = sum_A/(double)N; 
    average_B = sum_B/(double)N; 

    printf("Average of A: %f\nAverage of B: %f\n", average_A, average_B); 
    printf("Total time: %f\n", end_time - start_time); 

    return 0; 
}