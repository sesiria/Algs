/*
* Inflate algorithm demo implementation base on zlib
* FileName: inflate.cpp
* author: sesiria	2021-05-23
* compile commandline: g++ -o inflate inflate.cpp inflatingStream.cpp -lz -std=c++11
*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "inflatingStream.h"

#define DATA_SIZE       1024

// decompress the file to the specific name and output to the target filename.
int decompressOneFile(const char * infilename, const char* outfilename) {

    int numRead = 0;
    char inbuffer[DATA_SIZE] = {0};
    FILE *infile = fopen(infilename, "rb");
    FILE *outfile = fopen(outfilename, "wb");
    std::string outStr;

    if(!infile || !outfile) {
        perror("invalid file name!\n");
        return -1;
    }

    InflatingStream * inflate = nullptr;
    try {
        inflate = new InflatingStream(STREAM_GZIP);
    }
    catch (const char *c) {
        printf(" new InflatingStream failed, it is %s \n", c);
        if(inflate)
            delete inflate;
        return -1;
    }

    while((numRead = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0) {
        outStr.clear();
        int ret = inflate->Inflate(inbuffer, numRead, outStr);
        printf("%s(%d) ret:%d, outStr size:%ld\n",
                __FUNCTION__, __LINE__, ret, outStr.size());
        fwrite(outStr.c_str(), outStr.size(), 1, outfile);
    }
    outStr.clear();
    // fllush the buffer from the zstream
    int ret = inflate->Inflate(NULL, 0,  outStr);
    printf("%s(%d) ret:%d, outStr size:%ld\n",
            __FUNCTION__, __LINE__, ret, outStr.size());
    fwrite(outStr.c_str(), outStr.size(), 1, outfile);

    fclose(infile);
    fclose(outfile);

    if(inflate)
        delete inflate;
    return 0;
}

int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << ": <input_file> <output_file>" << std::endl
                  << "       read <input_file>, deflate (compress) it and write the result to <output_file>"
                  << std::endl;
        return 1;
    }

    decompressOneFile(argv[1], argv[2]);

    return 0;
}