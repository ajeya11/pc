#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define SIZE 100000

void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }
    i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
    free(L);
    free(R);
}

void serial_mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        serial_mergeSort(arr, left, mid);
        serial_mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void parallel_mergeSort(int arr[], int left, int right, int depth)
{
    int mid = left + (right - left) / 2;
    if (left < right)
    {

        if (depth <= 4)
        {
#pragma omp parallel sections
            {
#pragma omp section
                {
                    parallel_mergeSort(arr, left, mid, depth + 1);
                }
#pragma omp section
                {
                    parallel_mergeSort(arr, mid + 1, right, depth + 1);
                }
            }
        }
        else
        {
            serial_mergeSort(arr, left, mid);
            serial_mergeSort(arr, mid + 1, right);
        }
    }
    merge(arr, left, mid, right);
}

int main()
{

    int *serial_arr = (int *)malloc(SIZE * sizeof(int));
    int *parallel_arr = (int *)malloc(SIZE * sizeof(int));

    for (int i = 0; i < SIZE; i++)
    {
        int val = rand() % SIZE;
        serial_arr[i] = val;
        parallel_arr[i] = val;
    }

    double tstart_serial = omp_get_wtime();
    serial_mergeSort(serial_arr, 0, SIZE - 1);
    double tend_serial = omp_get_wtime();

    double serial_cmp_time = tend_serial - tstart_serial;

    double tstart_parallel = omp_get_wtime();
    parallel_mergeSort(parallel_arr, 0, SIZE - 1, 0);
    double tend_parallel = omp_get_wtime();

    double parallel_cmp_time = tend_parallel - tstart_parallel;

    printf("Serial Computation Takes : %.6f\n", serial_cmp_time);
    printf("Parallel Computation Takes : %.6f\n", parallel_cmp_time);

    int flag = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (serial_arr[i] != parallel_arr[i])
        {
            flag = 1;
            printf("Mis-Match Occured at : %d\n", i);
        }
    }
    if (!flag)
    {
        printf("Correctness Verified!.......\n");
    }

    free(serial_arr);
    free(parallel_arr);
    return 0;
}
