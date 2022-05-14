// Marek Traczyński (261748)
// Lista 2 Zadanie 2c
// Quicksort

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


void quick_sort(int array[], int left, int right, int k); 
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


void quick_sort(int array[], int left, int right, int k) 
{
    if(left < right)
    {
        simulation_data[k].comparisons++;
        int p = partition(array, left, right, k);
        quick_sort(array, left, p - 1, k);
        quick_sort(array, p + 1, right, k);
    }
}

int partition(int array[], int left, int right, int reps)
{
    int pivot = array[right];
    int index = left - 1;

    for(int i = left; i < right; i++) 
    {
        simulation_data[reps].comparisons++;
        
        if(array[i] <= pivot)
        {
            simulation_data[reps].comparisons++;
            simulation_data[reps].swaps++;
            index++;
            swap(&array[index], &array[i]);
        }
    }
  
    swap(&array[index+1], &array[right]);
    simulation_data[reps].swaps++;

    return index + 1;
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


    csvFile.open("QuickSimulationDataK" + to_string(SIMULATION_REPETITIONS) + ".csv");


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
            quick_sort(array, 0, (n * i)-1, k);  
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
