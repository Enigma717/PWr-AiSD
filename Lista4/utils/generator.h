// Marek Traczyński (261748)
// Lista 4
// RNG

#include <chrono>
#include <random>

using namespace std::chrono;

int mersenne_generator(const int& A, const int& B)
{
    static unsigned seed = system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);
    static std::uniform_int_distribution<int> distribution;

    distribution.param(std::uniform_int_distribution<int>::param_type(A, B));
   
    return distribution(generator);
}
