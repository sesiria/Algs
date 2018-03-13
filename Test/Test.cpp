#include <iostream>
#include <map>
#include <string>
#include <vector>

void permute(const std::string& str, const std::string & prefix)
{
    if(str.length() == 0) {
        std::cout << prefix << std::endl;
    } else {
        for (int i = 0; i < str.length(); ++i) {
            std::string rem = str.substr(0, i) + str.substr(i + 1);
            permute(rem, prefix + str[i]);
        }
    }
}


void permuatation(const std::string& str)
{
    permute(str, "");
}


int fib(int n, std::vector<int> & memo)
{
    if(n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else if (memo[n] > 0)
        return memo[n];

    memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
    return memo[n];
}

void allFib(int n) {
    std::vector<int> memo(n + 1, 0);
    for (int i = 0; i <= n; ++i)
        std::cout << i
                  << ": " << fib(i, memo) << std::endl;
}


int powersOf2(int n) {
    if(n < 1) {
        return 0;
    } else if (n == 1) {
        std::cout << 1 << std::endl;
        return 1;
    } else {
        int prev = powersOf2(n / 2);
        int curr = prev * 2;
        std::cout << curr << std::endl;
        return curr;
    }
}

int main(int argc, char **argv)
{
    //permuatation("Hello");
    //allFib(5);

    powersOf2(8);
    return 0;
}