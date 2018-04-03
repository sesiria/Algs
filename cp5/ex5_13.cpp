/*
* Exercise 5.13
* Author: sesiria  2018
* calculate polynomials
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct PolynomialItem
{
    int exponent = 0;
    double coeValue = 0;

    PolynomialItem(){};
    PolynomialItem(int exponentValue, double coe)
        : exponent{exponentValue}, coeValue{coe}
    {
    }
};

bool lessThan(const PolynomialItem &lhs, const PolynomialItem &rhs)
{
    return lhs.exponent < rhs.exponent;
}

vector<PolynomialItem>
multiplePolynomials(const vector<PolynomialItem> &poly1,
                    const vector<PolynomialItem> &poly2)
{
    unordered_map<int, double> hashTable;
    for (auto &item1 : poly1)
    {
        for (auto &item2 : poly2) {
            cout << item1.exponent + item2.exponent << " " << item1.coeValue * item2.coeValue << endl;
            hashTable[item1.exponent + item2.exponent] += item1.coeValue * item2.coeValue;       
        }
    }

    // sort the result.
    vector<PolynomialItem> result;
    for (auto &poly : hashTable)
        result.push_back(PolynomialItem( poly.first, poly.second));

    sort(result.begin(), result.end(), lessThan);
    return result;
}

int main()
{
    vector<PolynomialItem> poly1 = {PolynomialItem{0, 1}, PolynomialItem{1, 1}};
    vector<PolynomialItem> poly2 = {PolynomialItem{0, 1}, PolynomialItem{1, 1}};
    vector<PolynomialItem> result = multiplePolynomials(poly1, poly2);

    for(auto &x : result)
        cout << x.exponent << " " << x.coeValue << endl;
    return 0;
}