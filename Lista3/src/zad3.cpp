// Marek Traczyński (261748)
// Lista 3 Zadanie 3
// Median of medians Select
// With variable subarrays sizes

#include <iostream>     
#include <chrono>
#include <fstream>
#include "../utils/generator.h"
#include "../utils/quicksort.h"

#define GENERATED_NUMBERS_BASE 100
#define ITERATIONS_MULTIPLIER 100
#define SIMULATION_REPETITIONS 25

using std::cout;

struct Data {
    int comparisons;
    int swaps;
    double duration;
};

Data simulation_data[SIMULATION_REPETITIONS];

int median_select(int array[], int left, int right, int index, int reps, int subsize); 
int median_of_medians(int array[], int left, int right, int subsize);
int subpartition_median(int array[], int left, int right);
int partition(int array[], int left, int right, int pivot, int reps);
void simulation(int array[], int n, int subsize);


int main()
{
    int *array = (int *) malloc((ITERATIONS_MULTIPLIER * GENERATED_NUMBERS_BASE) * sizeof(int));

    for(int subarray_size = 3; subarray_size <= 9; subarray_size+=2)
    {
        simulation(array, GENERATED_NUMBERS_BASE, subarray_size);
    }

    return 0;
}

void simulation(int array[], int n, int subsize)
{
    std::ofstream csvFile;
    int k;

    csvFile.open("../csvdata/zad3/MedianSelectDataSubarray" + std::to_string(subsize) + ".csv");

    csvFile << "n; comparisons";
    for(k = 0; k < SIMULATION_REPETITIONS; k++)
    {
        csvFile << "; ";
    }
    csvFile << "swaps";
    for(k = 0; k < SIMULATION_REPETITIONS; k++)
    {
        csvFile << "; ";
    }
    csvFile << "duration;\n";


    for(int i = 1; i <= ITERATIONS_MULTIPLIER; i++)
    {
        csvFile << n * i << "; ";

        int upper_bound = n * i;
        int random_statistic = mersenne_generator(1, upper_bound);
        
        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            simulation_data[k] = {0, 0};
            fill_rand(array, upper_bound);

            auto start = Clock::now();

            median_select(array, 0, upper_bound - 1, random_statistic, subsize, k);
        
            auto finish = Clock::now();

            duration<double> time_elapsed = finish - start;
            simulation_data[k].duration = duration_cast<microseconds>(time_elapsed).count();
        }
        
        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            csvFile << simulation_data[k].comparisons << "; ";
        }

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            csvFile << simulation_data[k].swaps << "; ";
        }

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            csvFile.precision(1);
            csvFile << std::fixed << simulation_data[k].duration << "; ";
        }

        csvFile << "\n";              
    }

    csvFile.close();
}

int median_select(int array[], int left, int right, int index, int subsize, int reps) 
{
    if(left == right)
    {
        return array[left];
    }

    int pivot = median_of_medians(array, left, right, subsize);
    int r = partition(array, left, right, pivot, reps);
    int k = r - left + 1;

    simulation_data[reps].comparisons++;

    if(index == k)
    {
        return array[r];
    }
    else if(index < k)
    {
        return median_select(array, left, r - 1, index, subsize, reps);
    }
    else
    {
        return median_select(array, r + 1, right, index - k, subsize, reps);
    }
}

int median_of_medians(int array[], int left, int right, int subsize)
{
    int j = 0;

    if(right - left < subsize)
    {
        return subpartition_median(array, left, right);
    }

    int subarrays_count = ceil((right - left) / subsize) + 1;
    int medians[subarrays_count];

    for(int i = left; i <= right; i += subsize)
    {
        int sub_right = i + (subsize - 1);

        if(sub_right > right)
        {
            sub_right = right;
        }

        medians[j] = subpartition_median(array, i, sub_right);
        j++;
    }

    int median_of_medians = subpartition_median(medians, 0, subarrays_count);

    return median_of_medians;
}

int subpartition_median(int array[], int left, int right)
{
    for(int i = left + 1; i <= right; i++)
    {
        int j = i;

        while(j > left && array[j-1] > array[j])
        {
            swap(&array[j-1], &array[j]);
            j--;
        }
    }
    
    int sub_median = floor((left + right) / 2);

    return array[sub_median];
}

int partition(int array[], int left, int right, int pivot, int reps)
{
    for(int i = left; i < right; i++)
    {
        if(array[i] == pivot)
        {
            swap(&array[i], &array[right]);
            simulation_data[reps].swaps++;
        }
    }
    
    int j = left - 1;

    for(int i = left; i < right; i++) 
    {
        simulation_data[reps].comparisons++;
        
        if(array[i] <= pivot)
        {
            j++;
            swap(&array[j], &array[i]);
            simulation_data[reps].swaps++;
        }
    }
  
    swap(&array[j+1], &array[right]);
    simulation_data[reps].swaps++;

    return j + 1;
}

