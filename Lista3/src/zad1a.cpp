// Marek Traczyński (261748)
// Lista 3 Zadanie 1a
// Randomized Select

#include <iostream>
#include "../utils/generator.h"
#include "../utils/quicksort.h"

#define PRINTING_THRESHOLD 50

using std::cout;
using std::cin;

struct Data {
    int comparisons;
    int swaps;
};

Data algorithm_data = {0, 0};
bool print_state_flag = false;
int depth = 0;

int random_select(int array[], int left, int right, int index); 
int random_partition(int array[], int left, int right);
void algorithm_test(int array[], int n, int statistic);
void print_array(int array[], int n);


int main()
{
    int array_size, statistic;


    cout << "\nPlease enter array size: ";
    cin >> array_size;
    cout << "Please enter statistic index to find: ";
    cin >> statistic;


    int *array = (int *) malloc(array_size * sizeof(int));
    algorithm_test(array, array_size, statistic);
    
    return 0;
}

void algorithm_test(int array[], int n, int statistic)
{
    fill_rand(array, n);
    int select_result = random_select(array, 0, n - 1, statistic);
    
    if(n <= PRINTING_THRESHOLD)
    {
        print_state_flag = true;
        algorithm_data = {0, 0};
        depth = 0;

        cout << "\n===========================================================\n";
        cout << "\nUNSORTED ARRAY:\n";
        print_array(array, n);

        cout << "\n===========================================================\n\n";
        random_select(array, 0, n - 1, statistic);
        cout << "\n/ " << statistic << "-TH STATISTIC FOUND: " << select_result << "\n";            
        cout << "| COMPARISONS: " << algorithm_data.comparisons << "\n";
        cout << "\\ SWAPS: " << algorithm_data.swaps << "\n";
        cout << "\n===========================================================\n";

        cout << "\nSORTED ARRAY:\n";
        quick_sort(array, 0, n - 1);
        print_array(array, n);
        cout << "\n===========================================================\n\n";
    }
    else
    {
        print_state_flag = false;
        
        cout << "\n============================\n";
        cout << "\n/ " << statistic << "-TH STATISTIC FOUND: " << select_result << "\n";
        cout << "| COMPARISONS: " << algorithm_data.comparisons << "\n";
        cout << "\\ SWAPS: " << algorithm_data.swaps << "\n";
        cout << "\n============================\n\n";
    }
}

int random_select(int array[], int left, int right, int index) 
{
    depth++;

    if(left == right)
    {
        return array[left];
    }

    int r = random_partition(array, left, right);
    int k = r - left + 1;

    algorithm_data.comparisons++;

    if(index == k)
    {
        return array[r];
    }
    else if(index < k)
    {
        return random_select(array, left, r - 1, index);
    }
    else
    {
        return random_select(array, r + 1, right, index - k);
    }
}

int random_partition(int array[], int left, int right)
{
    int pivot = left + rand() % ((right + 1) - left);
    
    swap(&array[pivot], &array[right]);
    algorithm_data.swaps++;
    
    int pivot_value = array[right];
    pivot = left - 1;

    for(int i = left; i < right; i++) 
    {
        algorithm_data.comparisons++;

        if(array[i] <= pivot_value)
        {
            pivot++;
            swap(&array[pivot], &array[i]);
            algorithm_data.swaps++;
        }
    }

    swap(&array[pivot+1], &array[right]);
    algorithm_data.swaps++;

    if(print_state_flag)
    {
        cout << "DEPTH: " << depth << "\nPIVOT = " << pivot_value << "\t||\tPARTITION = [";
        for(int k = left; k <= right; k++)
        {
            if(array[k] == pivot_value)
            {
                cout << "("<< array[k] << ")";
            }
            else
            {
                cout << array[k];
            }

            if(right != k)
            {
                cout << " ";
            }
        }
        cout << "]\n------------------------------\n";
    }

    return pivot + 1;
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
