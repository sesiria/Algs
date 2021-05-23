/*
* Inflate algorithm demo implementation base on zlib
* FileName: inflatingStream.h
* author: sesiria	2021-05-23
*/
#ifndef _INFLATING_STREAM_H_
#define _INFLATING_STREAM_H_
#include <iostream>
#include <zlib.h>

//====================declaration types====================
enum StreamType {
    STREAM_ZLIB = 0,        // Create a zlib header, use Adler-32 checksum.
    STREAM_GZIP             // Create a gzip header, use CRC-32 checksum.
};


//====================declaration class====================
class InflatingStream {
public:
    /**
     * Init the InflatingStream Object.
     * type: type of the compress, only support STREAM_GZIP
     * return: None
     */ 
    InflatingStream(StreamType type);

    /**
     * The default destructor.
     */ 
    ~InflatingStream();

    /**
     * decompress the data from the inBuf and write the output into the outBuf buffer.
     * inBuf: the buffer point to the input data, set to NULL indicate that the input data has been transferred already.
     * inLen: the length of the input buffer.
     * outBuf: the buffer to store the decompressed data.
     * return: 0 normal, -1 abnormal.
     */ 
    int Inflate(const char* inBuf, const size_t inLen, std::string &outBuf);
private:
    enum {
        STREAM_BUFFER_SIZE = 1024,
        INFLATE_BUFFER_SIZE = 32768,
        ORIGN_NAME_BUFFER_SIZE = 128
    };

    char * _buffer;
    char * _orignNameBuffer;
    z_stream _zstr;
    gz_header _gzipHead;
    bool _eof;
};

#endif