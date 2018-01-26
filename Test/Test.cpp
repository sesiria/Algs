#include <iostream>
#include <vector>
#include <time.h>
#include <ostream>
#include "../Lib/Vector.h"
#include "../Lib/List.h"


int main(int argc, char ** argv) 
{
    Vector<int> vec(0);
    List<int> lst;
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i);
        lst.push_back(i);
    }
        
    
    for(auto &X : vec)
        std::cout << X << " ";

    std::cout << std::endl;

    for(auto &y : lst)
        std::cout << y << " ";

    List<int>::const_iterator iter;
    for (iter = lst.begin(); iter != lst.end(); ++iter)
        std::cout << *iter << std::endl;

    return 0;
}