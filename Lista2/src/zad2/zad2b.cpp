// Marek Traczyński (261748)
// Lista 2 Zadanie 2b
// Merge Sort

#include <iostream>
#include <fstream>
#include "generator.h"

#define GENERATED_NUMBERS_BASE 100
#define SIMULATION_REPETITIONS 100

using namespace std;

struct Data {
    int comparisons;
    int moves;
};

Data simulation_data[SIMULATION_REPETITIONS];


void merge_sort(int array[], int left, int right, int k);
void merge(int array[], int left, int mid, int right, int reps);
void simulation(int array[], int n);
bool sort_check(int array[], int n);


int main()
{
    int array[1000];

    simulation(array, GENERATED_NUMBERS_BASE);

    return 0;
}


void merge_sort(int array[], int left, int right, int k)
{
    if(left < right)
    {
        int mid = (left + right - 1) / 2;
        merge_sort(array, left, mid, k);
        merge_sort(array, mid + 1, right, k);
        merge(array, left, mid, right, k);
    }
}

void merge(int array[], int left, int mid, int right, int reps)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int temp_left[n1], temp_right[n2];
 
    for(int i = 0; i < n1; i++)
    {
        temp_left[i] = array[left+i];
    }

    for(int j = 0; j < n2; j++)
    {
        temp_right[j] = array[mid+1+j];
    }
 
    int i = 0, j = 0;
    int k = left;

    while(i < n1 && j < n2)
    {
        simulation_data[reps].comparisons++;

        if(temp_left[i] <= temp_right[j]) 
        {
            array[k] = temp_left[i];
            i++;
        }
        else 
        {
            array[k] = temp_right[j];
            j++;
        }

        simulation_data[reps].comparisons++;
        simulation_data[reps].moves++;

        k++;
    }

    while(i < n1) 
    {
        array[k] = temp_left[i];
        simulation_data[reps].comparisons++;
        simulation_data[reps].moves++;
        i++;
        k++;
    }

    while(j < n2) 
    {
        array[k] = temp_right[j];
        simulation_data[reps].comparisons++;
        simulation_data[reps].moves++;
        j++;
        k++;
    }
}

void simulation(int array[], int n)
{
    ofstream csvFile;
    int k;


    csvFile.open("MergeSimulationDataK" + to_string(SIMULATION_REPETITIONS) + ".csv");


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
            merge_sort(array, 0, (n * i)-1, k);  
        }
        
        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            csvFile << simulation_data[k].comparisons << "; ";
        }

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            csvFile << simulation_data[k].moves << "; ";
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
