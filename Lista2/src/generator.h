// Marek Traczyński (261748)
// Lista 2 Zadanie 1
// RNG + arrays generator

#include <chrono>
#include <random>

using namespace std;
using namespace chrono;
typedef steady_clock Clock;


int mersenne_generator(const int& A, const int& B) {
    static unsigned seed = system_clock::now().time_since_epoch().count();
    static mt19937 generator(seed);
    static uniform_int_distribution<int> distribution;

    distribution.param(uniform_int_distribution<int>::param_type(A, B));
   
    return distribution(generator);
}

void fill_rand(int array[], int n)
{
    for(int i = 0; i < n; i++)
    {
        array[i] = mersenne_generator(0, (2*n) - 1);
    }
}

void fill_desc(int array[], int n)
{
    for(int i = n; i > 0; i--)
    {
        array[-1*(i-n)] = i;
    }
}

void fill_asc(int array[], int n)
{
    for(int i = 0; i < n; i++)
    {
        array[i] = i;
    }
}