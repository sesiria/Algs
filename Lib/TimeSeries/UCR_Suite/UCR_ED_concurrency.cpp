#include <iostream>
#include <fstream>      // for file IO
#include <thread>
#include <atomic>
#include <vector>
#include <queue>
#include <algorithm>    // for sort algorithm
#include <chrono>       // get exactly time stamp

using namespace std;

/// global variable definition.
constexpr double INF = 10e20;

/// Data structure for sorting the query.
struct Index {
    double value;
    int index;
};

/// Comparison function for sorting the query.
/// The query will be sorted by absolute z-normalization value, |z_norm(Q[i])| from high to low.
struct comp {
    bool operator()(const Index&  l, const Index & r) {
        return abs(l.value) - abs(r.value);
    }
};

/// Main function for calculating ED distance between the query, Q, and current data, T.
/// Note that Q is already sorted by absolute z-normalization value, |z_norm(Q[i])|
/// Q is the query series
/// T is the target series searched
/// order is the sorted index of the query series.
double distance(const vector<double>& Q, 
                const vector<double>& T, 
                const vector<int> & order,
                const int& j, 
                const int& m, 
                const double& mean, 
                const double& std,
                const double& bsf = INF)
{
    int i;
    double sum = 0;
    for ( i = 0 ; i < m && sum < bsf ; i++ )
    {
        double x = (T[(order[i]+j)]-mean)/std;
        sum += (x-Q[i])*(x-Q[i]);
    }
    return sum;
}

/// If serious error happens, terminate the program.
void error(int id)
{
    if(id==1)
        cout <<"ERROR : Memory can't be allocated!!!\n\n";
    else if ( id == 2 )
        cout <<"ERROR : File not Found!!!\n\n";
    else if ( id == 3 )
        cout <<"ERROR : Can't create Output File!!!\n\n";
    else if ( id == 4 )
    {
        cout << "ERROR: Invalid Number of Arguments!!!\n";
        cout << "Command Usage:   UCR_ED.exe  data_file  query_file   m   \n";
        cout << "For example  :   UCR_ED.exe  data.txt   query.txt   128  \n";
    }
    exit(1);
}


/// Helper functions

/// return the exactly time stamp 
/// precise: milliseconds
time_t getTimeStamp()
{
    chrono::time_point<chrono::system_clock, chrono::milliseconds> tp =
        chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    return tp.time_since_epoch().count();
}

int main(int argc, char *argv[])
{
    time_t start = getTimeStamp();
    for(int i = 0; i <= 100000000; ++i)
        ;
    time_t elspaed = getTimeStamp() - start;
    cout << elspaed << endl;
    return 0;
}