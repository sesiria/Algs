
/*
* Exercise 5.18 (b)
* Author: sesiria  2018
* word puzzle. Implementation by hashTable
* using a hashtable to index the dictionary.
* build a prefix hashtable to ignore some special cases.
*/

#include "../Lib/matrix.h"
#include <assert.h>
#include <iostream>
#include <string.h>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::vector<char>> vec = {
    std::vector<char>{'x', 'x', 'x', 'x', 'x', 'x'},
    std::vector<char>{'x', 't', 'h', 'i', 's', 'x'},
    std::vector<char>{'x', 'g', 't', 't', 's', 'x'},
    std::vector<char>{'x', 't', 'a', 'h', 'w', 'x'},
    std::vector<char>{'x', 'w', 'f', 'p', 's', 'x'},
    std::vector<char>{'x', 'x', 'x', 'x', 'x', 'x'}};

matrix<char> g_puzzle = vec;

std::vector<std::string> g_dict =
    {
        "this",
        "two",
        "fat",
        "that",
        "ask",
        "tag",
        "what",
        "gap",
        "shtt"};

// search that the lhs is match the rhs
class MatchString
{
  public:
    int operator()(const std::string &lhs, const std::string &rhs)
    {
        return strncmp(lhs.c_str(), rhs.c_str(), lhs.length());
    }
};

// basic method generate a string from the matrix.
std::string MaxtrixToString(
    const matrix<char> &mar, int x_begin, int y_begin, int x_end, int y_end)
{
    char buf[BUFSIZ] = {0};
    std::string str;
    int offsetX = (x_begin < x_end) ? 1 : (x_begin > x_end) ? -1 : 0;
    int offsetY = (y_begin < y_end) ? 1 : (y_begin > y_end) ? -1 : 0;
    int xGuard = x_end + offsetX;
    int yGuard = y_end + offsetY;
    int pos = 0;
    for (int i = x_begin, j = y_begin; i != xGuard || j != yGuard;
         i += offsetX, j += offsetY)
    {
        buf[pos++] = mar[i][j];
    }
    buf[pos] = '\0';
    return std::move(str = buf);
}

void printResult(const std::string &word, int x_start, int y_start, int x_end, int y_end)
{
    printf("found word '%s' in [%d,%d]-[%d,%d].\n",
           word.c_str(), x_start, y_start, x_end, y_end);
}

void getEndPoint(int x_start, int y_start, int length, int &x_end, int &y_end)
{
    int offsetX = (x_start < x_end) ? 1 : (x_start > x_end) ? -1 : 0;
    int offsetY = (y_start < y_end) ? 1 : (y_start > y_end) ? -1 : 0;
    x_end = x_start + offsetX * (length - 1);
    y_end = y_start + offsetY * (length - 1);
}

bool scanPuzzle(int xStart, int xEnd, int yStart, int yEnd,
                std::unordered_set<std::string> &hashTable, bool isPrefix = false)
{
    std::string getStr = MaxtrixToString(g_puzzle, xStart, yStart, xEnd, yEnd);
    if (hashTable.find(getStr) != hashTable.end())
    {
        // we found the string.
        if (!isPrefix)
        {
            getEndPoint(xStart, yStart, getStr.size(), xEnd, yEnd);
            printResult(getStr, xStart, yStart, xEnd, yEnd);
        }
        return true;
    }
    return false;
}

int main(int argc, char **argv)
{
    // we build the hashtable for search.
    std::unordered_set<std::string> hashTable;
    std::unordered_set<std::string> prefixTable;
    for (auto &word : g_dict)
        hashTable.insert(word);

    // we build the prefix table for eachword.
    for (auto &word : g_dict)
    {
        if (word.size() == 0)
            continue;
        for (auto iter = word.begin() + 1; iter != word.end(); ++iter)
            prefixTable.insert(std::string(word.begin(), iter));
        prefixTable.insert(word);
    }

    int nRow = g_puzzle.numrows();
    int nCol = g_puzzle.numcols();
    int xStart, yStart, xEnd, yEnd;
    for (int i = 0; i < nRow; i++)
        for (int j = 0; j < nCol; j++)
        {
            // scan for row from top-down
            if (i >= 0 && i != nRow - 1)
            {
                xStart = i;
                yStart = j;
                for (xEnd = xStart + 1, yEnd = j; xEnd < nRow; ++xEnd)
                {
                    if (!scanPuzzle(xStart, xEnd, yStart, yEnd, prefixTable, true))
                        break;
                    scanPuzzle(xStart, xEnd, yStart, yEnd, hashTable);
                }
            }
            // scan from down-top
            if (i <= nRow - 1 && i != 0)
            {
                xStart = i;
                yStart = j;
                for (xEnd = xStart - 1, yEnd = j; xEnd >= 0; --xEnd)
                {
                    if (!scanPuzzle(xStart, xEnd, yStart, yEnd, prefixTable, true))
                        break;
                    scanPuzzle(xStart, xEnd, yStart, yEnd, hashTable);
                }
            }

            // scan from left-right
            if (j >= 0 && j != nCol - 1)
            {
                xStart = i;
                yStart = j;
                for (xEnd = i, yEnd = yStart + 1; yEnd < nCol; ++yEnd)
                {
                    if (!scanPuzzle(xStart, xEnd, yStart, yEnd, prefixTable, true))
                        break;
                    scanPuzzle(xStart, xEnd, yStart, yEnd, hashTable);
                }
            }

            // scan from right-left
            if (j <= nCol - 1 && j != 0)
            {
                xStart = i;
                yStart = j;
                for (xEnd = i, yEnd = yStart - 1; yEnd >= 0; --yEnd)
                {
                    if (!scanPuzzle(xStart, xEnd, yStart, yEnd, prefixTable, true))
                        break;
                    scanPuzzle(xStart, xEnd, yStart, yEnd, hashTable);
                }
            }

            // scan from top-left to down-right
            {
                int xOffset = nRow - 1 - i;
                int yOffset = nCol - 1 - j;
                int ScanSize = (xOffset < yOffset) ? xOffset : yOffset;
                xStart = i;
                //xEnd = xStart + ScanSize;
                yStart = j;
                //yEnd = yStart + ScanSize;
                for (xEnd = xStart + 1, yEnd = yStart + 1;
                     xEnd <= xStart + ScanSize && yEnd <= yStart + ScanSize;
                     ++xEnd, ++yEnd)
                {
                    if (!scanPuzzle(xStart, xEnd, yStart, yEnd, prefixTable, true))
                        break;
                    scanPuzzle(xStart, xEnd, yStart, yEnd, hashTable);
                }
            }

            // scan from down-right to top-left
            {
                int xOffset = i;
                int yOffset = j;
                int ScanSize = (xOffset < yOffset) ? xOffset : yOffset;
                xStart = i;
                //xEnd = xStart - ScanSize;
                yStart = j;
                //yEnd = yStart - ScanSize;
                for (xEnd = xStart - 1, yEnd = yStart - 1;
                     xEnd >= (xStart - ScanSize) && yEnd >= (yStart - ScanSize);
                     --xEnd, --yEnd)
                {
                    if (!scanPuzzle(xStart, xEnd, yStart, yEnd, prefixTable, true))
                        break;
                    scanPuzzle(xStart, xEnd, yStart, yEnd, hashTable);
                }
            }
        }
    return 0;
}