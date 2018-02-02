#include "../Lib/randomize.h"
#include <iostream>
#include <map>

int rand01()
{
    return RNG::getInstance().getInteger() % 2;
}

#define N (10)

int random(int num)
{
    int result = 0;
    int upperbound = 1;
    while (upperbound < (num + 1))
            upperbound *= 2;
    do
    {
        result = 0;
        int nBound = upperbound;
        while ((nBound /= 2) > 0)
            result += nBound * rand01();
    } while (result > num);
    return result;
}

int main(int argc, char **argv)
{
    printf("Randomly test 1,000,000 of rand01 result:\n");

    long long  resultN[N + 1] = {0};
    for (long long i = 0; i < 1000000; ++i)
        ++resultN[random(N)];

    for (int i = 0; i <= N; ++i)
        printf("%d is : %ld\n", i, resultN[i]);
    return 0;
}