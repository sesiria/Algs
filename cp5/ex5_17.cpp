
/*
* Exercise 5.17
* Author: sesiria  2018
* remap the line number and update from the original basic code.
*/
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

char basic_program[] = "10 INPUT \"What is your name: \"; U$ \n"
                       "20 PRINT \"Hello \"; U$  \n"
                       "30 INPUT \"How many stars do you want: \"; N  \n"
                       "40 S$ = \"\"  \n"
                       "50 FOR I = 1 TO N  \n"
                       "60 S$ = S$ + \"*\"  \n"
                       "70 NEXT I  \n"
                       "80 PRINT S$  \n"
                       "90 INPUT \"Do you want more stars? \"; A$  \n"
                       "100 IF LEN(A$) = 0 THEN GOTO 90  \n"
                       "110 A$ = LEFT$(A$, 1)  \n"
                       "120 IF A$ = \"Y\" OR A$ = \"y\" THEN GOTO 30  \n"
                       "130 PRINT \"Goodbye \"; U$  \n"
                       "140 END\n";

bool mapLineNo(const string &line, const string &keyword, string &newLine, size_t &posCur, unordered_map<int, int> &hashtable)
{
    decltype(line.size()) posTemp = 0;
    char buf[BUFSIZ] = {0};
    if ((posTemp = line.find(keyword, posCur)) != string::npos)
    {
        newLine = line.substr(posCur, posTemp - posCur + keyword.size());
        posCur = posTemp + keyword.size();

        // skip whitespace
        while (posCur < line.size() && isblank(line[posCur]))
        {
            newLine += line[posCur];
            ++posCur;
        }

        // read digit.
        string sDigit;
        while (posCur < line.size() && isdigit(line[posCur]))
        {
            sDigit += line[posCur];
            ++posCur;
        }

        // append digit.
        newLine.append(_itoa(hashtable[atoi(sDigit.c_str())], buf, 10));
        return true;
    }

    return false;
}

string remapLineNumber(const string &src, int lineStart, int interval)
{
    stringstream ssr(src);
    vector<string> codes;
    unordered_map<int, int> hashTable;
    string line;
    int lineNO = lineStart;
    while (getline(ssr, line))
    {
        int oldNum;
        if (sscanf(line.c_str(), "%d", &oldNum) > 0) // legal line
        {
            hashTable[oldNum] = lineNO;
            decltype(line.size()) pos = 0;
            while (pos < line.size() && isdigit(line[pos]))
                ++pos;

            char buf[BUFSIZ] = {0};
            codes.push_back(
                string(_itoa(lineNO, buf, 10)) +
                line.substr(pos, line.size() - pos));
            lineNO += interval;
        }
    }

    // replace the line no.
    for (auto &line : codes)
    {
        string word;
        string newLine;
        decltype(line.size()) pos = 0;
        while (pos < line.size())
        {
            decltype(line.size()) posTemp = 0;
            if (!mapLineNo(line, "GOTO", newLine, pos, hashTable) && !mapLineNo(line, "GOSUB", newLine, pos, hashTable))
            {
                newLine.append(string(line.begin() + pos, line.end())); // append the left string.
                pos = line.size();
            }
        }
        line = newLine;
    }

    std::string result;
    for (auto &line : codes)
    {
        result.append(line);
        result.append("\n");
    }

    return result;
}

int main()
{
    cout << remapLineNumber(basic_program, 0, 1);
    return 0;
}