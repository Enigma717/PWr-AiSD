// Marek Traczyński (261748)
// Lista 3
// Quicksort algorithm

void swap(int *x, int *y) 
{ 
    int z = *x; 
    *x = *y; 
    *y = z; 
} 

int qs_partition(int array[], int left, int right)
{
    int pivot = array[right];
    int index = left - 1;

    for(int i = left; i < right; i++) 
    {
        if(array[i] <= pivot)
        {
            index++;
            swap(&array[index], &array[i]);
        }
    }
  
    swap(&array[index+1], &array[right]);

    return index + 1;
}

void quick_sort(int array[], int left, int right) 
{
    if(left < right)
    {
        int p = qs_partition(array, left, right);
        quick_sort(array, left, p - 1);
        quick_sort(array, p + 1, right);
    }
}
