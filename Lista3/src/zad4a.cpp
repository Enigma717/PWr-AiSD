// Marek Traczyński (261748)
// Lista 3 Zadanie 4a
// Binary Search

#include <iostream>
#include <chrono>
#include "../utils/generator.h"
#include "../utils/quicksort.h"

using std::cout;
using std::cin;

int comparisons = 0;
int depth = 0;
auto start = Clock::now();

bool binary_search(int array[], int left, int right, int value);
void algorithm_test(int array[], int n, int value);
void print_array(int array[], int n);


int main()
{
    int array_size, value;    
    
    cout << "\nPlease enter array size: ";
    cin >> array_size;
    cout << "Please enter value to find in array: ";
    cin >> value;

    int *array = (int*) malloc(array_size * sizeof(int));
    start = Clock::now();
    algorithm_test(array, array_size, value);
    
    return 0;
}

void algorithm_test(int array[], int n, int value)
{
    fill_rand(array, n);
    quick_sort(array, 0, n - 1);

    if(n <= 50)
    {
        cout << "\n===========================================================\n";
        cout << "\nGENERATED ARRAY:\n";
        print_array(array, n);      
    }

    cout << "\n===========================================================\n";
    cout << "\n/ BINARY SEARCH RESULT: " << (binary_search(array, 0, n - 1, value) ? "VALUE FOUND" : "VALUE NOT FOUND") << "\n"; 
    
    auto finish = Clock::now(); 
    duration<double> time_elapsed = finish - start;

    cout << "| COMPARISONS: " << comparisons << "\n";
    cout << "\\ TIME ELAPSED: " << std::fixed << time_elapsed.count() << " seconds\n";
    cout << "\n===========================================================\n";
}

bool binary_search(int array[], int left, int right, int value)
{
    if (right >= left) 
    {
        int mid = left + (right - left) / 2;
        comparisons++;
 
        if (array[mid] == value)
        {
            return true;
        }

        if (array[mid] > value)
        {
            return binary_search(array, left, mid - 1, value);
        }
        
        return binary_search(array, mid + 1, right, value);
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
