#include <iostream>
#include <sstream>
#include <string>
#include "../Lib/ExtendibleHashTable.h"

// Pre-c++11 style; not all compilers have new to_string function
template <typename Object>
std::string toString( Object x )
{
    std::ostringstream oss;
    oss << x;
    return oss.str( );
}


int main()
{
    ExtendibleHashTable<std::string, hash<std::string>> eh;
    eh.contains("test");


    const int NUMS = 2000000;
    const int GAP  =  37;
    const int ATTEMPTS = 1;
    int i;

    std::cout << "Checking... (no more output means success)" << std::endl;

    for( int att = 0; att < ATTEMPTS; ++att )
    { 
        std::cout << "ATTEMPT: " << att << std::endl;
        
        ExtendibleHashTable<std::string, hash<std::string>> h1;
        ExtendibleHashTable<std::string, hash<std::string>> h2;
        
        for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        {
            if( !h1.insert( toString( i ) ) )
            {
                std::cout << "OOPS insert fails!!!! " << i << std::endl;
            }
            
        }

        for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
            if( h1.insert( toString( i ) ) )
                std::cout << "INSERT OOPS!!! " << i << std::endl;
        
        h2 = h1;
        
       /* for( i = 1; i < NUMS; i += 2 )
            h2.remove( toString( i ) );*/
        
        for( i = 2; i < NUMS; i += 2 )
            if( !h2.contains( toString( i ) ) )
                std::cout << "Contains fails " << i << std::endl;
        
       /* for( i = 1; i < NUMS; i += 2 )
        {
            if( h2.contains( toString( i ) ) )
                std::cout << "CONTAINS OOPS!!! " <<  i << std::endl;
        }*/
        
        std::cout << "END OF ATTEMPT" << std::endl;
        
       /* if( h2.capacity( ) > NUMS * 4 )
            std::cout << "LARGE CAPACITY " << h2.capacity( ) << std::endl;*/
        
    }


    return 0;
}