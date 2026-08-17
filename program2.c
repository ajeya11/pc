#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

int main(){
    int nthreads,iterations;
    printf("Enter Number of Threads : \n");
    scanf("%d",&nthreads);

    omp_set_num_threads(nthreads);

    printf("Enter Number of Iterations :\n");
    scanf("%d",&iterations);

    #pragma omp parallel
    {
        #pragma omp for schedule(static,2)
        for(int i=0;i<iterations;i++){
            printf("Thread %d: Iteration %d\n",omp_get_thread_num(),i);
        }
    }
    return 0;


}
