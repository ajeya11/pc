#include <stdio.h>
#include <omp.h>
#include<time.h>

int is_prime(int n)
{
	if (n < 2) return 0;
	for (int i = 2; i*i<= n; i++)
		if (n % i == 0) return 0;
	return 1;
}

int main()
{
	long n = 10000000;
	int nthreads;
	double start,end;
	double start1,end1;
	double cpu_time;
	printf("\nn the range of numbers is 1 to %ld\n",n);
	printf("\n------------------------------------------------------------------\n");

	// Serial Execution
	start=omp_get_wtime();
	for (int i = 1; i<= n; i++)
		is_prime(i);

	end = omp_get_wtime();
	cpu_time = end - start;
	
	printf(" Time to compute prime numbers serially: %f\n",cpu_time);

	// Parallel Execution
	printf("Enter the number of threads: ");
	scanf("%d", &nthreads);
	omp_set_num_threads(nthreads);
	start1=omp_get_wtime();;
	#pragma omp parallel for
	for (int i = 1; i<= n; i++)
		is_prime(i);

	end1 = omp_get_wtime();
	cpu_time = end1 - start1;
	printf("Time to compute prime numbers Parallel: %f\n",cpu_time);
	return 0;
}
