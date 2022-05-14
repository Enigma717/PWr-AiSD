// Marek Traczyński (261748)
// Lista 2 Zadanie 1b
// Merge Sort

#include <iostream>
#include <cstdint>
#include "generator.h"

using namespace std;

struct Data {
    uint64_t comparisons;
    uint64_t moves;
};

Data simulation_data = {0, 0};


void merge_sort(int array[], int left, int right);
void merge(int array[], int left, int mid, int right);
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


void merge_sort(int array[], int left, int right)
{
    if(left < right)
    {
        int mid = (left + right - 1) / 2;
        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void merge(int array[], int left, int mid, int right)
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
        simulation_data.comparisons++;

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

        simulation_data.comparisons++;
        simulation_data.moves++;

        k++;
    }

    while(i < n1) 
    {
        array[k] = temp_left[i];
        simulation_data.comparisons++;
        simulation_data.moves++;
        i++;
        k++;
    }

    while(j < n2) 
    {
        array[k] = temp_right[j];
        simulation_data.comparisons++;
        simulation_data.moves++;
        j++;
        k++;
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

        merge_sort(array, 0, n-1);           

        cout << "\nSORTED ARRAY:\n";
        print_array(array, n);
        cout << "\nCOMPARISONS: " << simulation_data.comparisons << "\n";
        cout << "SWAPS: " << simulation_data.moves << "\n";
    }
    else
    {
        merge_sort(array, 0, n-1);

        cout << "\n============================\n";
        cout << "\nARRAY LENGTH: " << n << "\n";
        cout << "COMPARISONS: " << simulation_data.comparisons << "\n";
        cout << "MOVES: " << simulation_data.moves << "\n";
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
