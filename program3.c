#include <stdio.h>
#include <time.h>
#include<omp.h>

int fibo(int n)
{
    int i, j;
    if (n < 2)
    {
        return n;
    }
    else
    {
#pragma omp task shared(i) firstprivate(n)
        i = fibo(n - 1);
#pragma omp task shared(j) firstprivate(n)
        j = fibo(n - 2);
#pragma omp taskwait
        return i + j;
    }
}

int main()
{

    int n = 35;

    omp_set_dynamic(0);
    omp_set_num_threads(4);
#pragma omp parallel shared(n)
    {
         double start = omp_get_wtime();
#pragma omp single
        printf("fibo(%d) = %d\n", n, fibo(n));
        double end = omp_get_wtime();
        printf("Total Time = %.6f",end-start);
    }

    return 0;
}
