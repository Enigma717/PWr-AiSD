// Marek Traczyński (261748)
// Lista 3 Zadanie 4a
// Binary Search

#include <iostream>     
#include <chrono>
#include <fstream>
#include "../utils/generator.h"
#include "../utils/quicksort.h"

#define GENERATED_NUMBERS_BASE 1000
#define ITERATIONS_MULTIPLIER 100
#define SIMULATION_REPETITIONS 25

using std::cout;

struct Data {
    int comparisons;
    double duration;
};

Data simulation_data[SIMULATION_REPETITIONS];
auto start = Clock::now();

bool binary_search(int array[], int left, int right, int value, int reps);
void simulation(int array[], int n, int mode);


int main()
{
    int *array = (int *) malloc((ITERATIONS_MULTIPLIER * GENERATED_NUMBERS_BASE) * sizeof(int));

    for(int mode = 0; mode < 5; mode++)
    {
        cout << mode << "\n";
        simulation(array, GENERATED_NUMBERS_BASE, mode);
    }
    
    return 0;
}

void simulation(int array[], int n, int mode)
{
    std::ofstream csvFile;
    int k;

    csvFile.open("../csvdata/zad4/BinarySearchMode" + std::to_string(mode) + ".csv");

    csvFile << "n; comparisons";
    for(k = 0; k < SIMULATION_REPETITIONS; k++)
    {
        csvFile << "; ";
    }
    csvFile << "duration;\n";


    for(int i = 1; i <= ITERATIONS_MULTIPLIER; i++)
    {
        csvFile << n * i << "; ";

        int upper_bound = n * i;
        int value = 0;

        if(mode == 0)           // beggining of the array
        {
            value = mersenne_generator(1, (upper_bound / 5));
        }
        else if(mode == 1)      // middle of the array
        {
            value = mersenne_generator(((upper_bound / 2) - (upper_bound / 5)), ((upper_bound / 2) + (upper_bound / 5)));
        }
        else if(mode == 2)      // ending of the array
        {
            value = mersenne_generator((upper_bound - (upper_bound / 5)), upper_bound);
        }
        else if(mode == 3)      // outside of the array
        {
            value = mersenne_generator(upper_bound + 1, upper_bound + 2);
        }
        else if(mode == 4)      // random value
        {
            value = mersenne_generator(1, upper_bound);
        }
           
        start = Clock::now();

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            simulation_data[k] = {0, 0};
            fill_rand(array, upper_bound);
            quick_sort(array, 0, upper_bound - 1);
            
            binary_search(array, 0, upper_bound - 1, value, k);

            auto finish = Clock::now();
            duration<double> time_elapsed = finish - start;

            simulation_data[k].duration = time_elapsed.count();
        }
        
        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            csvFile << simulation_data[k].comparisons << "; ";
        }

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            csvFile.precision(6);
            
            if(k == 0)
            {
                csvFile << std::fixed << (simulation_data[k].duration) << "; ";
            }
            else
            {
                csvFile << std::fixed << (simulation_data[k].duration - simulation_data[k-1].duration) << "; ";
            }
        }

        csvFile << "\n";              
    }

    csvFile.close();
}

bool binary_search(int array[], int left, int right, int value, int reps)
{
    if (right >= left) 
    {
        int mid = left + (right - left) / 2;
        simulation_data[reps].comparisons++;
 
        if (array[mid] == value)
        {
            return true;
        }

        if (array[mid] > value)
        {
            return binary_search(array, left, mid - 1, value, reps);
        }
        
        return binary_search(array, mid + 1, right, value, reps);
    }

    return false;
}

void print_array(int array[], int n)
{
    for(int i = 0; i < n; i++)
    {
        if((i+1) % 10 != 0)
        {
            if(array[i] < 10)
            {
                cout << "0" << array[i] << "\t";
            }
            else
            {
                cout << array[i] << "\t";
            }
        }
        else
        {
            if(array[i] < 10)
            {
                cout << "0" << array[i] << "\n";
            }
            else
            {
                cout << array[i] << "\n";
            }
        }
    }
}
