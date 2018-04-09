#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


int universalHash(int x, int A, int B, int P, int M)
{
    return static_cast<int>(((static_cast<long long>(A) * x) + B) % P) % M;
}

const int DIGS = 31;
const int mersennep = (1L << DIGS) - 1;

int universalHash1(int x, int A, int B, int M)
{
    long long hashVal = static_cast<long long>(A) * x + B;

    hashVal = ((hashVal >> DIGS)) + (hashVal & mersennep));
    if(hashVal >= mersennep)
        hashVal -= mersennep;

    return static_cast<int>(hashVal) % M;
}

int main(int argc, char **argv)
{
    map<string,string> mp =parseHeader(str);
    for(map<string,string>::const_iterator it=mp.begin();it!=mp.end();++it){
        cout<<it->first <<"   "<<it->second<<endl;
    }
    return 0;
}