CC=g++
CPPFLAGS = -Wall -std=c++11
TARGET=LZ77 FileCompress deflate inflate
OBJ=LZ77.o FileCompress.o deflate.o DeflatingStream.o inflate.o inflatingStream.o
 
${OBJ}:%.o:%.cpp
	${CC} -c ${CPPFLAGS} $< -o $@
 
all:${TARGET}
 
LZ77:LZ77.o ${LIB}
	${CC}  $^ -o $@
FileCompress:FileCompress.o 
	${CC}  $^ -o $@
deflate:deflate.o DeflatingStream.o
	${CC}  $^ -o $@ -lz
inflate:inflate.o inflatingStream.o
	${CC}  $^ -o $@ -lz
clean:
	rm -rf ${TARGET} ${OBJ}
