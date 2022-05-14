// Marek Traczyński (261748)
// Lista 2 Zadanie 1b
// Quicksort

#include <iostream>
#include <cstdint>
#include "generator.h"

using namespace std;

struct Data {
    uint64_t comparisons;
    uint64_t swaps;
};

Data simulation_data = {0, 0};


void quick_sort(int array[], int left, int right); 
int partition(int array[], int left, int right);
void swap(int *x, int *y);
void simulation(int array[], int n, int type);
void print_array(int array[], int n);
bool sort_check(int array[], int n);


int main()
{
    int array_size, gen_type;
    int err_flag = 0;


    cout << "\nPlease enter array size: ";
    cin >> array_size;
    cout << "\nPlease enter array generation method:\n";
    cout << "1 - Random values\n2 - Sorted descending\n3 - Sorted ascending\nChoice: ";
    cin >> gen_type;

    if(gen_type < 1 || gen_type > 3)
    {
        cout << "\nPlease enter correct value!\n\n";
        err_flag = -1;
    }

    int array[array_size];

    if(err_flag == 0)
    {
        simulation(array, array_size, gen_type);
    }

    return 0;
}


void quick_sort(int array[], int left, int right) 
{
    if(left < right)
    {
        simulation_data.comparisons++;
        int p = partition(array, left, right);
        quick_sort(array, left, p - 1);
        quick_sort(array, p + 1, right);
    }
}

int partition(int array[], int left, int right)
{
    int pivot = array[right];
    int index = left - 1;

    for(int i = left; i < right; i++) 
    {
        simulation_data.comparisons++;
        
        if(array[i] <= pivot)
        {
            simulation_data.comparisons++;
            simulation_data.swaps++;
            index++;
            swap(&array[index], &array[i]);
        }
    }
  
    swap(&array[index+1], &array[right]);
    simulation_data.swaps++;

    return index + 1;
}

void swap(int *x, int *y) 
{ 
    int z = *x; 
    *x = *y; 
    *y = z; 
} 

void simulation(int array[], int n, int type)
{
    if(type == 1)
    {
        fill_rand(array, n);
    }
    else if(type == 2)
    {
        fill_desc(array, n);
    }
    else if(type == 3)    
    {
        fill_asc(array, n);
    }


    if(n < 50)
    {
        cout << "\n===========================================================\n";
        cout << "\nUNSORTED ARRAY:\n";
        print_array(array, n);

        quick_sort(array, 0, n-1);           

        cout << "\nSORTED ARRAY:\n";
        print_array(array, n);
        cout << "\nCOMPARISONS: " << simulation_data.comparisons << "\n";
        cout << "SWAPS: " << simulation_data.swaps << "\n";
    }
    else
    {
        quick_sort(array, 0, n-1);

        cout << "\n============================\n";
        cout << "\nARRAY LENGTH: " << n << "\n";
        cout << "COMPARISONS: " << simulation_data.comparisons << "\n";
        cout << "SWAPS: " << simulation_data.swaps << "\n";
    }
    
    if(sort_check(array, n))
    {
        cout << "\nSORT CHECK: TRUE\n\n";
    } 
    else
    {
        cout << "\nSORT CHECK: FALSE\n\n";
    }
}

void print_array(int array[], int n)
{
    for(int i = 0; i < n; i++)
    {
        if((i+1) % 8 != 0)
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
