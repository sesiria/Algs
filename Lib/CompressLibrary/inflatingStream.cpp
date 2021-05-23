/*
* Inflate algorithm demo implementation base on zlib
* FileName: inflatingStream.cpp
* author: sesiria	2021-05-23
*/

#include <string.h>
#include "inflatingStream.h"

InflatingStream::InflatingStream(StreamType type)
    : _eof(false)
{
    _zstr.zalloc = Z_NULL;
    _zstr.zfree = Z_NULL;
    _zstr.opaque = Z_NULL;
    _zstr.next_in = 0;
    _zstr.avail_in = 0;
    _zstr.next_out = 0;
    _zstr.avail_out = 0;


    // alloc the buffer and call the inflateInit2.
    _buffer = new char[INFLATE_BUFFER_SIZE];
    _orignNameBuffer = new char[ORIGN_NAME_BUFFER_SIZE];
    int rc = inflateInit2(&_zstr, 15 + (type == STREAM_GZIP ? 16 : 0));
    if(rc != Z_OK) {
        delete [] _buffer;
        delete [] _orignNameBuffer;
        _buffer = NULL;
        _orignNameBuffer = NULL;
        printf("InflatingStream failed;%s\n", zError(rc));
        throw "inflateInit2 failed!";
    }

    // init the gzip header
    if(STREAM_GZIP == type) {
        memset(&_gzipHead, 0, sizeof(gz_header));
        _gzipHead.extra = (Bytef *) _orignNameBuffer;
        _gzipHead.extra_max = ORIGN_NAME_BUFFER_SIZE;
        _gzipHead.name = (Bytef *) _orignNameBuffer;
        _gzipHead.name_max = ORIGN_NAME_BUFFER_SIZE;
        _gzipHead.comment = (Bytef *)_orignNameBuffer;
        _gzipHead.comm_max = ORIGN_NAME_BUFFER_SIZE;
        int rc = inflateGetHeader(&_zstr, &_gzipHead);
        printf("inflateGetHeader = %d\n", rc);
    }
}

InflatingStream::~InflatingStream() {
    if(_buffer)
        delete [] _buffer;
    if(_orignNameBuffer) 
        delete [] _orignNameBuffer;
    inflateEnd(&_zstr);
}


int InflatingStream::Inflate(const char *inBuf, const size_t inLen, std::string &outBuf) {

    // if the input data and len is zero ,zet the flag to the end of the file.
    if(!inBuf || inLen == 0) {
        _eof = true;
    }

    _zstr.next_in = (unsigned char *)inBuf;
    _zstr.avail_in = static_cast<unsigned>(inLen);
    _zstr.next_out = (unsigned char *)_buffer;
    _zstr.avail_out = INFLATE_BUFFER_SIZE;

    // we not met the end of the file, the normal process
    if(!_eof) {
        for(;;) {
            int rc = inflate(&_zstr, Z_NO_FLUSH);
            if(_gzipHead.done) {
                printf("inflate name:%s, extra:%s\n", _gzipHead.name, _gzipHead.extra);
            }
            if(rc == Z_STREAM_END) {
                outBuf.append(_buffer, _buffer + (INFLATE_BUFFER_SIZE - _zstr.avail_out));
                break;
            }
            if(rc != Z_OK) {
                perror("inflate error: ");
                return -1;
            }
            if(_zstr.avail_out == 0) {
                outBuf.append(_buffer, _buffer + INFLATE_BUFFER_SIZE);
                _zstr.next_out = (unsigned char *) _buffer;
                _zstr.avail_out = INFLATE_BUFFER_SIZE;
            }
            else if (_zstr.avail_in == 0) {
                outBuf.append(_buffer, _buffer + (INFLATE_BUFFER_SIZE - _zstr.avail_out));
                _zstr.next_out = (unsigned char*)_buffer;
                _zstr.avail_out =  INFLATE_BUFFER_SIZE;
                break;
            }
        }
    } 
    else {  // we met the end of the file.
        if(_zstr.next_out) {
            int rc = inflate(&_zstr, Z_FINISH);
            printf("%s(%d) ret:%d, avail_in:%u, avail_out:%u\n",
                    __FUNCTION__, __LINE__, rc, _zstr.avail_in, _zstr.avail_out);
            if(rc != Z_OK && rc != Z_STREAM_END) {
                perror("inflate ");
                return -1;
            }
            outBuf.append(_buffer, INFLATE_BUFFER_SIZE - _zstr.avail_out);
            _zstr.next_out = (unsigned char *)_buffer;
            _zstr.avail_out = INFLATE_BUFFER_SIZE;
            while(rc != Z_STREAM_END) {
                rc = inflate(&_zstr, Z_FINISH);
                printf("%s(%d) ret:%d, avail_in:%u, avail_out:%u\n",
                        __FUNCTION__, __LINE__, rc, _zstr.avail_in, _zstr.avail_out);
                if(rc != Z_OK && rc != Z_STREAM_END) {
                    perror("inflate ");
                    return -1;
                }
                outBuf.append(_buffer, INFLATE_BUFFER_SIZE - _zstr.avail_out);
                _zstr.next_out = (unsigned char *)_buffer;
                _zstr.avail_out = INFLATE_BUFFER_SIZE;
            }
        }
    }

    return 0;
}