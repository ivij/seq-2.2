#include <iostream>
#include <time.h>
#include <chrono>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>

using namespace std;
using namespace std::chrono;

long size = 1000000;

void swap(int* first_number, int* second_number)
{
    int temporary_element = *first_number;
    *first_number = *second_number;
    *second_number = temporary_element;
}


int partition(int* array, int low, int high)
{
    int pivot_element = array[high];
    int low_element = (low - 1);

    for(int x = low; x < high; x++)
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


void quicksort(int* array, int low, int high)
{
    if(low < high)
    {
        int partitioning_index = partition(array, low, high);
        quicksort(array, low, partitioning_index - 1);
        quicksort(array, partitioning_index + 1, high);
    }
}

void printArray(int* array, int size)
{
	for(int x = 0; x < size; x++)
	{
        printf("%d ", array[x]);
    }
    printf("\n");
}

int main()
{
    int* array = (int *)malloc(size * sizeof(int*));;
    for(int x = 0; x < size; x++)
	{ 
        array[x] = rand() % 100; 
    }


    cout<<"Unsorted Array: \n";
    printArray(array, size);


	auto start_time = high_resolution_clock::now();

    quicksort(array, 0, size-1);

    auto stop_time = high_resolution_clock::now();
	auto Sortting_Time = duration_cast<microseconds>(stop_time - start_time);

    cout<<"Sorted Array :\n";
    printArray(array, size);

	cout << "Array Size: " << size << " / " << "Sorting Time: " << Sorting_Time.count() << " microseconds";


    return 0;
}
