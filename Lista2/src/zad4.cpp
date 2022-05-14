// Marek Traczyński (261748)
// Lista 2 Zadanie 1b
// Hybrid (Insertion + Quick) Sort

#include <iostream>
#include <cstdint>
#include "generator.h"

using namespace std;

struct Data {
    uint64_t comparisons;
    uint64_t swaps;
};

Data simulation_data = {0, 0};


void insertion_sort(int array[], int start, int n);
void hybrid_quicksort(int array[], int left, int right); 
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

void insertion_sort(int array[], int start, int n)
{
    int i, j, key;


    for(i = start+1; i <= n; i++)
    {
        key = array[i];
        j = i;
        simulation_data.comparisons++;

        while(j > start && array[j-1] > key)
        {
            array[j] = array[j-1];
            j--;
            simulation_data.comparisons++;
            simulation_data.swaps++;
        }
        array[j] = key;
    }
}

void hybrid_quicksort(int array[], int left, int right) 
{
    while(left < right)
    {
        if(right - left < 10)
        {
            insertion_sort(array, left, right);
            break;
        }
        else
        {
            simulation_data.comparisons++;
            int p = partition(array, left, right);

            if(p - left < right - p)
            {
                hybrid_quicksort(array, left, p - 1);
                left = p + 1;
            }
            else
            {
                hybrid_quicksort(array, p + 1, right);
                right = p - 1;
            }
        }
    }
} 

int partition(int array[], int left, int right)
{
    int pivot = array[right];
    int index = left;

    for(int i = left; i < right; i++) 
    {
        simulation_data.comparisons++;
        
        if(array[i] <= pivot)
        {
            simulation_data.comparisons++;
            simulation_data.swaps++;
            swap(&array[i], &array[index]);
            index++;
        }
    }
  
    swap(&array[index], &array[right]);
    simulation_data.swaps++;

    return index;
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

        hybrid_quicksort(array, 0, n-1);           

        cout << "\nSORTED ARRAY:\n";
        print_array(array, n);
        cout << "\nCOMPARISONS: " << simulation_data.comparisons << "\n";
        cout << "SWAPS: " << simulation_data.swaps << "\n";
    }
    else
    {
        hybrid_quicksort(array, 0, n-1);

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
