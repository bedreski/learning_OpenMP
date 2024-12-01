#include<stdio.h>
#include<omp.h>

//Numerical approximation of the value of Pi using the method of rectangles to numerically integrate the function

int main() {

    //num_steps: Number of rectangles used in the approximation
    static long num_steps = 1000000;

    //Step: calculates the width of each rectangle
    double step;

    //Pi = used to store the final result
    //Sum = accumulates the areas of the rectangles
    double x, pi, sum = 0.0;
    int i;

    //Calculates the step size, i.e. the width of each rectangle, which is the distance between two consecutive points in the inverval of [0,1]
    step = 1.0/(double) num_steps;

    //Start of time measurement
    double start_time = omp_get_wtime();

    #pragma omp parallel private(i)
    {
        //Local sum for each thread - this avoids thread conflicts 
        double local_sum = 0.0; 

        #pragma omp for

        //Iteration to calculate the sum of the areas
        for(i = 0; i < num_steps; i++) {

            //x = calculates the Xi position of the center of each rectangle. This uses the midpoint of the Step variable range to calculate the height.
            x = ((double) (i + 0.5)) * step;

            //4.0/(1.0 + x * x) is the height of each rectangle. 
            //Sum accumulates the sum of the areas of all rectangles.
            local_sum += 4.0/(1.0 + x * x);
        }

        //The partial local sum of each thread is added to the global variable sum - this avoids racing conditions
        #pragma omp atomic
        sum += local_sum;
    }

    double end_time = omp_get_wtime(); 

    //Multiply the sum of the heights by the step size to get the approximate value of the integral.
    pi = step * sum; 

    printf("%.24f\n", pi); 
    printf("Execution Time: %f seconds\n", end_time - start_time);

    return 0; 
}