/**
* The File Compress Library implementation via the HuffmanTree class
* FileName: FileCompress.cpp
* Author: Sesiria  2021-05-22
* Not support concurrency
*/
#include "FileCompress.hpp"
#include <string.h>

int main(int argc, char * argv[])
{
	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		printf("usage: -c filename		compress the target file\n");
		printf("usage: -d filename		decompress the target file\n");
		return -1;
	}

	if (argc == 3) {
		if (strcmp(argv[1], "-c") == 0) {
			FileCompress obj;
			obj.Compress(argv[2]);
		}
		else if (strcmp(argv[1],"-d") == 0) {
			FileCompress obj;
			obj.Uncompress(argv[2]);
		}
		else {
			printf("Invalid parameter!\n");
		}
	}
	return 0;
}