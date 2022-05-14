// Marek Traczyński (261748)
// Lista 2 Zadanie 2c
// Dual-pivot Quicksort

#include <iostream>
#include <fstream>
#include "generator.h"

#define GENERATED_NUMBERS_BASE 100
#define SIMULATION_REPETITIONS 100

using namespace std;

struct Data {
    int comparisons;
    int swaps;
};

Data simulation_data[SIMULATION_REPETITIONS];


void insertion_sort(int array[], int start, int n, int k);
void hybrid_quicksort(int array[], int left, int right, int k); 
int partition(int array[], int left, int right, int reps);
void swap(int *x, int *y);
void simulation(int array[], int n);
bool sort_check(int array[], int n);


int main()
{
    int array[1000];

    simulation(array, GENERATED_NUMBERS_BASE);

    return 0;
}


void insertion_sort(int array[], int start, int n, int k)
{
    int i, j, key;


    for(i = start+1; i <= n; i++)
    {
        key = array[i];
        j = i;
        simulation_data[k].comparisons++;

        while(j > start && array[j-1] > key)
        {
            array[j] = array[j-1];
            j--;
            simulation_data[k].comparisons++;
            simulation_data[k].swaps++;
        }
        array[j] = key;
    }
}

void hybrid_quicksort(int array[], int left, int right, int k) 
{
    while(left < right)
    {
        if(right - left < 10)
        {
            insertion_sort(array, left, right, k);
            break;
        }
        else
        {
            simulation_data[k].comparisons++;
            int p = partition(array, left, right, k);

            if(p - left < right - p)
            {
                hybrid_quicksort(array, left, p - 1, k);
                left = p + 1;
            }
            else
            {
                hybrid_quicksort(array, p + 1, right, k);
                right = p - 1;
            }
        }
    }
} 

int partition(int array[], int left, int right, int reps)
{
    int pivot = array[right];
    int index = left;

    for(int i = left; i < right; i++) 
    {
        simulation_data[reps].comparisons++;
        
        if(array[i] <= pivot)
        {
            simulation_data[reps].comparisons++;
            simulation_data[reps].swaps++;
            swap(&array[i], &array[index]);
            index++;
        }
    }
  
    swap(&array[index], &array[right]);
    simulation_data[reps].swaps++;

    return index;
}

void swap(int *x, int *y) 
{ 
    int z = *x; 
    *x = *y; 
    *y = z; 
}

void simulation(int array[], int n)
{
    ofstream csvFile;
    int k;


    csvFile.open("HybridSimulationDataK" + to_string(SIMULATION_REPETITIONS) + ".csv");


    csvFile << "n; comparisons";
    for(k = 0; k < SIMULATION_REPETITIONS; k++)
    {
        csvFile << "; ";
    }
    csvFile << "moves;\n";


    for(int i = 1; i <= 10; i++)
    {
        csvFile << n * i << "; ";

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            simulation_data[k] = {0, 0};
            fill_rand(array, n * i);
            hybrid_quicksort(array, 0, (n * i)-1, k);  
        }
        
        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            csvFile << simulation_data[k].comparisons << "; ";
        }

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            csvFile << simulation_data[k].swaps << "; ";
        }

        csvFile << "\n";              
    }

    csvFile.close();

    if(sort_check(array, n) == true)
    {
        cout << "Array sort check: true";
    } 
    else
    {
        cout << "Array sort check: false";
    }
}

bool sort_check(int array[], int n)
{
    for(int i = 1; i < n; i++)
    {
        if(array[i-1] > array[i])
        {
            return false;
        }
    }

    return true;
}
