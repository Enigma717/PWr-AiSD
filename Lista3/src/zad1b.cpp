// Marek Traczyński (261748)
// Lista 3 Zadanie 1b
// Median of medians Select

#include <iostream>
#include <math.h>
#include "../utils/generator.h"
#include "../utils/quicksort.h"

#define PRINTING_THRESHOLD 50
#define SUBARRAY_SIZE 5

using std::cout;
using std::cin;

struct Data {
    int comparisons;
    int swaps;
};

Data algorithm_data = {0, 0};
bool print_state_flag = false;
int depth = 0;

int median_select(int array[], int left, int right, int index); 
int median_of_medians(int array[], int left, int right);
int subpartition_median(int array[], int left, int right);
int partition(int array[], int left, int right, int pivot);
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
    int select_result = median_select(array, 0, n - 1, statistic);
    
    if(n <= PRINTING_THRESHOLD)
    {
        print_state_flag = true;
        algorithm_data = {0, 0};
        depth = 0;

        cout << "\n===========================================================\n";
        cout << "\nUNSORTED ARRAY:\n";
        print_array(array, n);

        cout << "\n===========================================================\n\n";
        median_select(array, 0, n - 1, statistic);
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

int median_select(int array[], int left, int right, int index) 
{
    depth++;

    if(left == right)
    {
        return array[left];
    }

    int pivot = median_of_medians(array, left, right);
    int r = partition(array, left, right, pivot);
    int k = r - left + 1;

    algorithm_data.comparisons++;

    if(index == k)
    {
        return array[r];
    }
    else if(index < k)
    {
        return median_select(array, left, r - 1, index);
    }
    else
    {
        return median_select(array, r + 1, right, index - k);
    }
}

int median_of_medians(int array[], int left, int right)
{
    int j = 0;

    if(right - left < SUBARRAY_SIZE)
    {
        return subpartition_median(array, left, right);
    }

    int subarrays_count = ceil((right - left) / SUBARRAY_SIZE) + 1;
    int medians[subarrays_count];

    for(int i = left; i <= right; i += SUBARRAY_SIZE)
    {
        int sub_right = i + (SUBARRAY_SIZE - 1);

        if(sub_right > right)
        {
            sub_right = right;
        }

        medians[j] = subpartition_median(array, i, sub_right);
        j++;
    }


    if(print_state_flag)
    {
        int i = 0;
        cout << "DEPTH: " << depth << "\nSUBARRAYS = [";
        
        for(int k = left; k <= right; k++)
        {
            cout << array[k];
            if((i % 5) == 4 && i != (right-left))
            {
                cout << " |";
            }
            if(right != k)
            {
                cout << " ";
            }
            i++;
        }

        cout << "]\nMEDIANS OF SUBARRAYS = [";
        for(int k = 0; k < j; k++)
        {
            cout << medians[k];
            if((j - 1) != k)
            {
                cout << " ";
            }
        }
        cout << "]    ||    ";
    }

    int median_of_medians = subpartition_median(medians, 0, subarrays_count);

    if(print_state_flag)
    {
        cout << "MEDIAN OF MEDIANS = " << median_of_medians << "\n------------------------------\n";
    }

    return median_of_medians;
}

int subpartition_median(int array[], int left, int right)
{
    for(int i = left + 1; i <= right; i++)
    {
        int j = i;

        while(j > left && array[j-1] > array[j])
        {
            swap(&array[j-1], &array[j]);
            j--;
        }
    }
    
    int sub_median = floor((left + right) / 2);

    return array[sub_median];
}

int partition(int array[], int left, int right, int pivot)
{
    for(int i = left; i < right; i++)
    {
        if(array[i] == pivot)
        {
            swap(&array[i], &array[right]);
            algorithm_data.swaps++;
        }
    }
    
    int j = left - 1;

    for(int i = left; i < right; i++) 
    {
        algorithm_data.comparisons++;
        
        if(array[i] <= pivot)
        {
            j++;
            swap(&array[j], &array[i]);
            algorithm_data.swaps++;
        }
    }
  
    swap(&array[j+1], &array[right]);
    algorithm_data.swaps++;

    return j + 1;
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
