#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define SIZE 10

int main() {

    int i;
    int max = 0; 
    int a[SIZE];

    for(i = 0; i < SIZE; i++) {
        a[i] = rand();
        printf("%d\n", a[i]);
    }

    max = a[0]; 

    #pragma omp parallel for num_threads(4)

    for(i = 1; i < SIZE; i++) {

        //Critical section prevents multiple threads from accessing a section of code at the same time
        //Only one active thread can update the data referenced by the code
        #pragma omp critical
        if(a[i] > max) {
            max = a[i]; 
        }
    }

    printf("Max = %d\n", max); 
}