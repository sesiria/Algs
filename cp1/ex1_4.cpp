/*
 * Exercise 1.4
 * Author: sesiria  2018
 * Read in a file and outputs the file as modified by the include
 * statement.
 */
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

#define MAXLN   255

std::vector<std::string> g_fileList;

bool IsFileOpen(const std::string & sFileName)
{
    for (int i = 0; i < g_fileList.size(); i++)
    {
        if(g_fileList[i] == sFileName)
            return true;
    }
    return false;
}

void ProcessFile(const std::string & sFileName)
{
    char buff[MAXLN] = {0};

    if(IsFileOpen(sFileName))
        return;

    FILE *pFile = fopen(sFileName.c_str(), "rb");
    if(!pFile)
        return;

    g_fileList.push_back(sFileName);    // store the filename

    char *p = NULL;
    while(fgets(buff, MAXLN, pFile)){
        if(buff[strlen(buff) - 1] == '\n') // fgets will read '\n'
            buff[strlen(buff) - 1] = '\0';

        if((p = strstr(buff, "#include"))) {
            p = strchr(p, '<');
            ++p;    // skip '<'
            std::string sNewFileName = p;
            sNewFileName[sNewFileName.size() - 1] = '\0';   //ignore the '>' at the end.
            ProcessFile(sNewFileName);
        }       
    }
}

int main(int argc, char ** argv)
{
    return 0;
}