#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main(int argc, char **argv)
{
    map<string,string> mp =parseHeader(str);
    for(map<string,string>::const_iterator it=mp.begin();it!=mp.end();++it){
        cout<<it->first <<"   "<<it->second<<endl;
    }
    return 0;
}