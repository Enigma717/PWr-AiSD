// Marek Traczyński (261748)
// Lista 3 Zadanie 2a
// Randomized Select

#include <iostream>
#include <fstream>
#include "../utils/generator.h"
#include "../utils/quicksort.h"

#define GENERATED_NUMBERS_BASE 100
#define ITERATIONS_MULTIPLIER 100
#define SIMULATION_REPETITIONS 50

using std::cout;

struct Data {
    int comparisons;
    int swaps;
};

Data simulation_data[SIMULATION_REPETITIONS];

int random_select(int array[], int left, int right, int index, int reps); 
int random_partition(int array[], int left, int right, int reps);
void simulation(int array[], int n);


int main()
{
    int *array = (int *) malloc((GENERATED_NUMBERS_BASE * ITERATIONS_MULTIPLIER) * sizeof(int));

    simulation(array, GENERATED_NUMBERS_BASE);

    return 0;
}

void simulation(int array[], int n)
{
    std::ofstream csvFile;
    int k;

    csvFile.open("../csvdata/zad2/RandomSelectDataK" + std::to_string(SIMULATION_REPETITIONS) + ".csv");

    csvFile << "n; comparisons";
    for(k = 0; k < SIMULATION_REPETITIONS; k++)
    {
        csvFile << "; ";
    }
    csvFile << "swaps;\n";


    for(int i = 1; i <= ITERATIONS_MULTIPLIER; i++)
    {
        csvFile << n * i << "; ";

        int upper_bound = n * i;
        int random_statistic = mersenne_generator(1, upper_bound);

        for(k = 0; k < SIMULATION_REPETITIONS; k++)
        {
            simulation_data[k] = {0, 0};
            fill_rand(array, upper_bound);
            random_select(array, 0, upper_bound - 1, random_statistic, k);
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
}

int random_select(int array[], int left, int right, int index, int reps) 
{
    if(left == right)
    {
        return array[left];
    }

    int r = random_partition(array, left, right, reps);
    int k = r - left + 1;

    simulation_data[reps].comparisons++;

    if(index == k)
    {
        return array[r];
    }
    else if(index < k)
    {
        return random_select(array, left, r - 1, index, reps);
    }
    else
    {
        return random_select(array, r + 1, right, index - k, reps);
    }
}

int random_partition(int array[], int left, int right, int reps)
{
    int pivot = left + rand() % ((right + 1) - left);
    
    swap(&array[pivot], &array[right]);
    simulation_data[reps].swaps++;
    
    int pivot_value = array[right];
    pivot = left - 1;

    for(int i = left; i < right; i++) 
    {
        simulation_data[reps].comparisons++;

        if(array[i] <= pivot_value)
        {
            pivot++;
            swap(&array[pivot], &array[i]);
            simulation_data[reps].swaps++;
        }
    }

    swap(&array[pivot+1], &array[right]);
    simulation_data[reps, reps].swaps++;

    return pivot + 1;
}
