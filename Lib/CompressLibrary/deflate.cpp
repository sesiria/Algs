/*
* Deflate algorithm demo implementation base on zlib
* FileName: deflate.cpp
* author: sesiria	2021-05-23
* compile commandline: g++ -o deflate deflate.cpp DeflatingStream.cpp -lz -std=c++11
*/

#include "DeflatingStream.h"
#include <iostream>
#include <fstream>
#include <stdio.h>


#define DATA_SIZE       1024

// compress the file to the specific name and output to the target filename.
int compressOneFile(const char * infilename, const char * outfilename) {
    int numRead = 0;
    char inbuffer[DATA_SIZE] = {0};
    FILE *infile = fopen(infilename, "rb");
    FILE *outfile = fopen(outfilename, "wb");
    std::string outStr;

    if(!infile || !outfile) {
        perror("invalid file name!\n");
        return -1;
    }

    DeflatingStream *deflate = nullptr;

    try {
        deflate = new DeflatingStream(STREAM_GZIP, Z_DEFAULT_COMPRESSION, std::string(infilename));
    } catch (const char * c) {
        printf(" new DeflatingStream failed, it is %s \n", c);
        if(deflate)
            delete deflate;
        return -1;
    }

    // read data from the input file.
    while((numRead = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0) {
        outStr.clear();
        // compress the data from inbuffer and write into the outStr stream
        int ret = deflate->Deflate(inbuffer, numRead, outStr); 
        printf("%s(%d) ret:%d, outStr size:%ld\n", __FUNCTION__, __LINE__, ret, outStr.size());
        // write the data into the output file
        if(outStr.size() > 0)
            fwrite(outStr.c_str(), outStr.size(), 1, outfile);
    }
    outStr.clear();
    // fflush the zstream buffer into the outStr.
    int ret = deflate->Deflate(NULL, 0, outStr);
    printf("%s(%d) ret:%d, outStr size:%ld\n",  __FUNCTION__, __LINE__, ret, outStr.size());
    fwrite(outStr.c_str(), outStr.size(), 1, outfile);

    fclose(infile);
    fclose(outfile);

    if(deflate)
        delete deflate;
    
    return 0;
}


int main(int argc, char * argv[]) 
{
    if(argc != 3) {
        std::cout << "usage: " << argv[0] << ": <input_file> <output_file.gz>" << std::endl
                  << "       read <input_file>, deflate (compress) it and write the result to <output_file>"
                  << std::endl;
    }

    compressOneFile(argv[1], argv[2]);

    return 0;
}