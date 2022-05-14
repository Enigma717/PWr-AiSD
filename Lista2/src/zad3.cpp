// Marek Traczyński (261748)
// Lista 2 Zadanie 3
// Dual-pivot Quicksort

#include <iostream>
#include <cstdint>
#include "generator.h"

using namespace std;

struct Data {
    uint64_t comparisons;
    uint64_t swaps;
};

Data simulation_data = {0, 0};


void dualpivot_quicksort(int array[], int left, int right); 
int partition(int array[], int left, int right, int *left_pivot);
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


void dualpivot_quicksort(int array[], int left, int right)
{
    if (left < right) 
    {
        int left_pivot, right_pivot;
        
        simulation_data.comparisons++;
        right_pivot = partition(array, left, right, &left_pivot);
        dualpivot_quicksort(array, left, left_pivot - 1);
        dualpivot_quicksort(array, left_pivot + 1, right_pivot - 1);
        dualpivot_quicksort(array, right_pivot + 1, right);
    }
}
 
int partition(int array[], int left, int right, int *left_pivot)
{
    if (array[left] > array[right])
    {
        simulation_data.comparisons++;
        swap(&array[left], &array[right]);
        simulation_data.swaps++;
    }
 
    int j = left + 1;
    int k = j;
    int g = right - 1;
    int p = array[left], q = array[right];

    while (k <= g)
    {
        simulation_data.comparisons++;

        if (array[k] < p)
        {
            simulation_data.comparisons++;
            swap(&array[k], &array[j]);
            simulation_data.swaps++;
            j++;
        }
 
        else if (array[k] >= q)
        {
            simulation_data.comparisons++;

            while (array[g] > q && k < g)
            {
                simulation_data.comparisons++;
                g--;
            }

            swap(&array[k], &array[g]);
            simulation_data.swaps++;
            g--;
            
            if (array[k] < p)
            {
                simulation_data.comparisons++;
                swap(&array[k], &array[j]);
                simulation_data.swaps++;
                j++;
            }
        }

        k++;
    }

    j--;
    g++;
 
    swap(&array[left], &array[j]);
    swap(&array[right], &array[g]);
    simulation_data.swaps += 2;
 
    *left_pivot = j;
 
    return g;
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

        dualpivot_quicksort(array, 0, n-1);           

        cout << "\nSORTED ARRAY:\n";
        print_array(array, n);
        cout << "\nCOMPARISONS: " << simulation_data.comparisons << "\n";
        cout << "SWAPS: " << simulation_data.swaps << "\n";
    }
    else
    {
        dualpivot_quicksort(array, 0, n-1);

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
