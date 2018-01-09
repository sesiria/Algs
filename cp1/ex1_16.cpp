/*
 * Exercise 1.16
 * Author: sesiria  2018
 * Class template matrix.
 * add extra resize and zero-parameter constructor.
 */
#include <iostream>
#include <vector>

template <typename Object>
class matrix
{
public:
    matrix(int rows, int cols)
        : array(rows)
    {
        for(auto & thisRow : array)
            thisRow.resize(cols);
    }

    // copy constructor
    matrix(std::vector<std::vector<Object>> & v)
        : array{v}
    { }

    // move constructor
    matrix(std::vector<std::vector<Object>> && v)
        : array{ std::move(v)}
    { }

    const std::vector<Object> & operator[](int row) const
    { return array[row]; }

    std::vector<Object> & operator[] (int row)
    { return array[row]; }

    int numrows() const
    { return array.size(); }

    int numcols() const
    { return numrows() ? array[0].size() : 0; }

    // resize array
    void resize(int rows, int cols)
    {
        array.resize(rows);
        for(auto & thisRow : array)
            thisRow.resize(cols);
    }
private:
    std::vector<std::vector<Object>> array;
};

int main(int argc, char ** argv)
{
    matrix<int> ma{3, 4};
    printf("The size of matrix is %d * %d\n", 
        ma.numrows(), ma.numcols());
    ma.resize(7, 8);
    printf("The size of matrix is %d * %d\n", 
        ma.numrows(), ma.numcols());
    return 0;
}