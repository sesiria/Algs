CC=g++
CPPFLAGS = -Wall -std=c++11
TARGET=LZ77 FileCompress
OBJ=LZ77.o FileCompress.o
 
${OBJ}:%.o:%.cpp
	${CC} -c ${CPPFLAGS} $< -o $@
 
all:${TARGET}
 
LZ77:LZ77.o ${LIB}
	${CC}  $^ -o $@
FileCompress:FileCompress.o 
	${CC}  $^ -o $@
clean:
	rm -rf ${TARGET} ${OBJ}
