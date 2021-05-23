/*
* Deflate algorithm demo implementation base on zlib
* FileName: DeflatingStream.h
* author: sesiria	2021-05-23
*/
#ifndef _DEFLATING_STREAM_H_
#define _DEFLATING_STREAM_H_
#include <iostream>
#include <zlib.h>

//====================declaration types====================
enum StreamType {
    STREAM_ZLIB = 0,        // Create a zlib header, use Adler-32 checksum.
    STREAM_GZIP             // Create a gzip header, use CRC-32 checksum.
};

//====================declaration class====================
class DeflatingStream {
public:

    /**
     * Init the DeflatingStream Object.
     * type: type of the compress, only support STREAM_GZIP
     * level: the compress level from 0~9, the higher level the higher compress ratio.
     * orignName: the compressed target file name, support to 127 bytes.
     * return: None
     */ 
    DeflatingStream(const StreamType type, const int level, const std::string = "");

    /**
     * The default destructor.
     */ 
    ~DeflatingStream();

    /**
     * compress the data from the inBuf and write the output into the outStr buffer.
     * inBuf: the buffer point to the input data, set to NULL indicate that the input data has been transferred already.
     * inLen: the length of the input buffer.
     * outStr: the buffer to store the compressed data.
     * return: 0 normal, -1 abnormal.
     */ 
    int Deflate(char *inBuf, size_t inLen, std::string &outStr);
private:
    enum {
        STREAM_BUFFER_SIZE = 1024,
        DEFLATE_BUFFER_SIZE = 32768,
        ORIGN_NAME_BUFFER_SIZE = 128
    };

    char * _buffer;
    char * _orignNameBuffer;
    z_stream _zstr;
    gz_header _gzipHead;
    bool _eof;
};

#endif