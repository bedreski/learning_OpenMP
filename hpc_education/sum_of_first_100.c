#include<stdio.h>
#include<omp.h>

int main() {

    int i, sum = 0;

    //Using Padding to avoid shared cache lines - this helps with false sharing problem
    int thread_sum[4][8] = {0};

    omp_set_num_threads(4);

    //Private (i) to avoid racing conditions
    #pragma omp parallel private(i) 
    {

        int id = omp_get_thread_num();

        thread_sum[id][0] = 0;

        //It could be slower than serial version because of false sharing problem
        #pragma omp for 
        for(i = 1; i <= 100; i++) {
            thread_sum[id][0] += i;
        }
        
    }

    for(i = 0; i < 4; i++) {
        sum += thread_sum[i][0]; 
    }

    printf("Sum = %d\n", sum); 

    return 0; 
}