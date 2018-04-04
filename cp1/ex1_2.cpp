/*
 * Exercise 1.2
 * Author: sesiria  2018
 * Write a program to solve the word puzzle.
 * Implementation by matrix.
 * to simplify the code for the IO
 */

#include "../Lib/matrix.h"
#include <assert.h>
#include <iostream>
#include <string.h>
#include <string>
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

// Template method.
// bubblesort time complexity is O(n^2)
template <typename Comparable>
void bubblesort(std::vector<Comparable> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr.size() - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
        }
    }
}

// binary search for checking that whether a key is in a vector.
// return the index in the array.
template <typename Object, typename Comparator>
int binarysearch(
    const std::vector<Object> &arr,
    const Object &key,
    Comparator cmp)
{
    int i = 0;
    int j = arr.size() - 1;
    while (i <= j)
    {
        int medium = i + (j - i) / 2;
        int retValue;
        if ((retValue = cmp(arr[medium], key)) < 0)
            i = medium + 1;
        else if (retValue > 0)
            j = medium - 1;
        else
            return medium;
    }
    return -1; // can't find the element.
}

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
    return (str = buf);
}

void printResult(int idx, int x_start, int y_start, int x_end, int y_end)
{
    assert(idx >= 0 && idx < g_dict.size());
    printf("found word '%s' in [%d,%d]-[%d,%d].\n",
           g_dict[idx].c_str(), x_start, y_start, x_end, y_end);
}

void getEndPoint(int x_start, int y_start, int length, int &x_end, int &y_end)
{
    int offsetX = (x_start < x_end) ? 1 : (x_start > x_end) ? -1 : 0;
    int offsetY = (y_start < y_end) ? 1 : (y_start > y_end) ? -1 : 0;
    x_end = x_start + offsetX * (length - 1);
    y_end = y_start + offsetY * (length - 1);
}

void scanPuzzle(int xStart, int xEnd, int yStart, int yEnd)
{
    int index = -1;
    if ((index = binarysearch(g_dict,
                              MaxtrixToString(g_puzzle, xStart, yStart, xEnd, yEnd),
                              MatchString{})) != -1)
    {
        // we found the string.
        getEndPoint(xStart, yStart, g_dict[index].length(), xEnd, yEnd);
        printResult(index, xStart, yStart, xEnd, yEnd);
    }
}

int main(int argc, char **argv)
{
    // we sort the dictionary at first.
    bubblesort(g_dict);

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
				xEnd = nRow - 1;
				yEnd = j;
				scanPuzzle(xStart, xEnd, yStart, yEnd);
			}
			// scan from down-top
			if (i <= nRow - 1 && i != 0)
			{
				xStart = i;
				yStart = j;
				xEnd = 0;
				yEnd = j;
				scanPuzzle(xStart, xEnd, yStart, yEnd);
			}

			// scan from left-right
			if (j >= 0 && j != nCol - 1)
			{
				xStart = i;
				xEnd = i;
				yStart = j;
				yEnd = nCol - 1;
				scanPuzzle(xStart, xEnd, yStart, yEnd);
			}

			// scan from right-left
			if (j <= nCol - 1 && j != 0)
			{
				xStart = i;
				xEnd = i;
				yStart = j;
				yEnd = 0;
				scanPuzzle(xStart, xEnd, yStart, yEnd);
			}

			// scan from top-left to down-right
			{
				int xOffset = nRow - 1 - i;
				int yOffset = nCol - 1 - j;
				int ScanSize = (xOffset < yOffset) ? xOffset : yOffset;
				xStart = i;
				xEnd = xStart + ScanSize;
				yStart = j;
				yEnd = yStart + ScanSize;
				scanPuzzle(xStart, xEnd, yStart, yEnd);
			}

			// scan from down-right to top-left
			{
				int xOffset = i;
				int yOffset = j;
				int ScanSize = (xOffset < yOffset) ? xOffset : yOffset;
				xStart = i;
				xEnd = xStart - ScanSize;
				yStart = j;
				yEnd = yStart - ScanSize;
				scanPuzzle(xStart, xEnd, yStart, yEnd);
			}
		}
    return 0;
}