// Marek Traczyński (261748)
// Lista 2 Zadanie 2a
// Insertion Sort

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


void insertion_sort(int array[], int n, int k);
void simulation(int array[], int n);
bool sort_check(int array[], int n);


int main()
{
    int array[1000];

    simulation(array, GENERATED_NUMBERS_BASE);

    return 0;
}

void insertion_sort(int array[], int n, int k)
{
    int i, j, key;


    for(i = 1; i < n; i++)
    {
        key = array[i];
        j = i - 1;
        simulation_data[k].comparisons++;

        while(j >= 0 && array[j] > key)
        {
            array[j+1] = array[j];
            j--;
            simulation_data[k].comparisons++;
            simulation_data[k].swaps++;
        }
        array[j+1] = key;
    }
}

void simulation(int array[], int n)
{
    ofstream csvFile;
    int k;


    csvFile.open("InsertionSimulationDataK" + to_string(SIMULATION_REPETITIONS) + ".csv");


    csvFile << "n; comparisons";
    for(k = 0; k < SIMULATION_REPETITIONS; k++)
    {
        csvFile << "; ";
    }
    csvFile << "swaps;\n";


    for(int i = 1; i <= 10; i++)
    {
        csvFile << n * i << "; ";

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            simulation_data[k] = {0, 0};
            fill_rand(array, n * i);
            insertion_sort(array, n * i, k);  
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
