#include<stdio.h>
#include<omp.h>

#define N 5

int main() {

    int a[N], i;

    #pragma omp parallel
    {
        #pragma omp for
        for(i = 0; i < N; i++) {
            a[i] = i * i;
        }

        //Executed only by the master thread (0)
        #pragma omp master
        for(i = 0; i < N; i++) {
            printf("a[%d] = %d\n", i, a[i]);
        }

        //Master directive usually is coded with barriers to avoid multiple outputs of the same thing
        #pragma omp barrier
    }

    return 0; 
}