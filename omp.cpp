#include<stdio.h>
#include <time.h>
#include<omp.h>
#include<math.h>
#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;
using namespace std::chrono;

#define size 100000
#define THREADS 8


void swap(int* first_number, int* second_number)
{
 int temporary_element = *first_number;
    *first_number = *second_number;
    *second_number = temporary_element;
}

int partition (int array[], int low, int high)
{
	int pivot_element = array[high];
    int low_element = (low - 1);

    for(int x = low; x < high - 1; x++)
    { 
        if(array[x] <= pivot_element)
        { 
            low_element++;
            swap(&array[low_element], &array[x]);
        } 
    }
    swap(&array[low_element+1], &array[high]);

    return (low_element + 1);
}

void quickSort(int array[], int low, int high)
{
	if (low < high)
	{
		int partitioning_index = partition(array, low, high);

		#pragma omp task firstprivate(array,low,partitioning_index)
		{
			quickSort(array,low, partitioning_index - 1);

		}
		#pragma omp task firstprivate(array, high,partitioning_index)
		{
			quickSort(array, partitioning_index + 1, high);
		}
	}
}

void printArray(int array[], int size)
{
	for(int x = 0; x < size; x++)
	{
        printf("%d ", array[x]);
    }
    printf("\n");
}

int main()
{
    int* array;

    array = (int *) malloc(size * sizeof(int*));

	for(int x = 0; x < size; x++)
	{ 
        array[x] = rand() % 100; 
    }

	int n = sizeof(array)/sizeof(array[0]);

	omp_set_num_threads(THREADS);
	auto start_time = high_resolution_clock::now();

	#pragma omp parallel
	{
		#pragma omp single nowait
			quickSort(array, 0, n-1);
	}
    auto stop_time = high_resolution_clock::now();
	auto Sorting_Time = duration_cast<microseconds>(stop_time - start_time);

	printf("Sorted array of size: " + size +"\n");
    printArray(array, size);


	printf("Array Size: " + size + " / " + "Sorting Time: " + Sorting_Time.count() + "microseconds");


	return 0;
}
