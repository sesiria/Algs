#ifndef MATRIX_H
#define MATRIX_H

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
private:
    std::vector<std::vector<Object>> array;
};
#endif