// Marek Traczyński (261748)
// Lista 2 Zadanie 1a
// Insertion Sort

#include <iostream>
#include <cstdint>
#include "generator.h"

using namespace std;

struct Data {
    uint64_t comparisons;
    uint64_t swaps;
};

Data simulation_data = {0, 0};


void insertion_sort(int array[], int n);
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


void insertion_sort(int array[], int n)
{
    int i, j, key;


    for(i = 1; i < n; i++)
    {
        key = array[i];
        j = i - 1;
        simulation_data.comparisons++;

        while(j >= 0 && array[j] > key)
        {
            array[j+1] = array[j];
            j--;
            simulation_data.comparisons++;
            simulation_data.swaps++;
        }
        array[j+1] = key;
    }
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

        insertion_sort(array, n);           

        cout << "\nSORTED ARRAY:\n";
        print_array(array, n);
        cout << "\nCOMPARISONS: " << simulation_data.comparisons << "\n";
        cout << "SWAPS: " << simulation_data.swaps << "\n";
    }
    else
    {
        insertion_sort(array, n);

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
