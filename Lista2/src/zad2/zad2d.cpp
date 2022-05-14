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


void dualpivot_quicksort(int array[], int left, int right, int k); 
int partition(int array[], int left, int right, int *left_pivot, int reps);
void swap(int *x, int *y);
void simulation(int array[], int n);
bool sort_check(int array[], int n);


int main()
{
    int array[1000];

    simulation(array, GENERATED_NUMBERS_BASE);

    return 0;
}


void dualpivot_quicksort(int array[], int left, int right, int k)
{
    if (left < right) 
    {
        int left_pivot, right_pivot;
        
        simulation_data[k].comparisons++;
        right_pivot = partition(array, left, right, &left_pivot, k);
        dualpivot_quicksort(array, left, left_pivot - 1, k);
        dualpivot_quicksort(array, left_pivot + 1, right_pivot - 1, k);
        dualpivot_quicksort(array, right_pivot + 1, right, k);
    }
}
 
int partition(int array[], int left, int right, int *left_pivot, int reps)
{
    if (array[left] > array[right])
    {
        simulation_data[reps].comparisons++;
        swap(&array[left], &array[right]);
        simulation_data[reps].swaps++;
    }
 
    int j = left + 1;
    int k = j;
    int g = right - 1;
    int p = array[left], q = array[right];

    while (k <= g)
    {
        simulation_data[reps].comparisons++;

        if (array[k] < p)
        {
            simulation_data[reps].comparisons++;
            swap(&array[k], &array[j]);
            simulation_data[reps].swaps++;
            j++;
        }
 
        else if (array[k] >= q)
        {
            simulation_data[reps].comparisons++;

            while (array[g] > q && k < g)
            {
                simulation_data[reps].comparisons++;
                g--;
            }

            swap(&array[k], &array[g]);
            simulation_data[reps].swaps++;
            g--;
            
            if (array[k] < p)
            {
                simulation_data[reps].comparisons++;
                swap(&array[k], &array[j]);
                simulation_data[reps].swaps++;
                j++;
            }
        }

        k++;
    }

    j--;
    g++;
 
    swap(&array[left], &array[j]);
    swap(&array[right], &array[g]);
    simulation_data[reps].swaps += 2;
 
    *left_pivot = j;
 
    return g;
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


    csvFile.open("DualQuickSimulationDataK" + to_string(SIMULATION_REPETITIONS) + ".csv");


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
            dualpivot_quicksort(array, 0, (n * i)-1, k);  
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
