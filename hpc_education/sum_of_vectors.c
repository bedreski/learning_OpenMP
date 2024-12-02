#include<stdio.h>
#include<omp.h>


#define N 10000

int main() {

    int A[N], B[N], C[N];
    //It's better to declare private variables inside the parallel region when possible
    int i; 

    double start_time, end_time;

    for(i = 0; i < N; i++) {
        A[i] = i; 
        B[i] = i * 3;
    }

    start_time = omp_get_wtime();

    //shared(A, B, C) because all threads need to access the vectors to calculate the values
    //private(i) to avoid racing conditions
    #pragma omp parallel shared(A, B, C) private(i)
    {
        #pragma omp for
        for(i = 0; i < N; i++) {
            C[i] = A[i] + B[i];
        }
    }

    end_time = omp_get_wtime(); 

    for(i = 0; i < 10; i++) {
        printf("C[%d] = %d\n", i, C[i]);
    }

    printf("Total time: %f\n", end_time - start_time);

    return 0; 
}