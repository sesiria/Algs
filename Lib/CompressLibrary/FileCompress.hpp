/**
* The File Compress Library implementation via the HuffmanTree class
* FileName: FileCompress.hpp
* Author: Sesiria  2021-05-22
* Not support concurrency
*/
#define _CRT_SECURE_NO_WARNINGS
#ifndef _FILE_COMPRESS_H_
#define _FILE_COMPRESS_H_
#include "HuffmanTree.hpp"		// for HuffmanTree implementation
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

//===============type declaration================
typedef unsigned int CountType;
typedef unsigned char CharType;
struct CharInfo {
	CharType _ch;	// for character
	CountType _count;	// the count of the character
	std::string _code;	// the encode of the character in std::string

	bool operator!=(const CharInfo& info) {
		return _count != info._count;
	}

	CharInfo operator+(const CharInfo& info) {
		CharInfo ret;
		ret._count = _count + info._count;
		return ret;
	}

	bool operator<(const CharInfo& info) {
		return _count > info._count;
	}
};


//=============inline function defintion=============

// return the size of the specific file
inline unsigned long getFileSize(const char* path) {
	unsigned long filesize = -1;
	FILE* fp;
	fp = fopen(path, "r");
	if (fp == NULL)
		return filesize;
	fseek(fp, 0L, SEEK_END);
	filesize = ftell(fp);
	fclose(fp);
	return filesize;
}

//=============class defintion=============
class FileCompress {
	typedef HuffmanTreeNode<CharInfo> Node;
	struct TmpInfo {
		CharType _ch; // character
		CountType _count; // count of character
	};

public:
	FileCompress() {
		// init the CharInfo array
		for (size_t i = 0; i < 256; i++) {
			_infos[i]._ch = i;
			_infos[i]._count = 0;
		}
	}

	// Generate the huffman encode
	void GenerateHuffmanCode(Node* root, std::string code) {
		if (root == NULL)
			return;
		// preorder to generate the huffman code.
		if (root->_pLeft == nullptr && root->_pRight == nullptr) {
			_infos[(unsigned char)root->_weight._ch]._code = code; // assign the huffman Code.
			return;
		}
		GenerateHuffmanCode(root->_pLeft, code + '0');
		GenerateHuffmanCode(root->_pRight, code + '1');
	}

	// Compress the target file.
	// file: the path to the specific file
	void Compress(const char* file) {
		unsigned long fileSize = getFileSize(file);

		if (fileSize == (unsigned long)-1) {
			fprintf(stderr, "%s invalid file size -1\n", file);
			return;
		}

		// 1. count the number of characters
		FILE* fin = fopen(file, "rb");
		assert(fin);
		int ch;
		while ((ch = fgetc(fin)) != EOF) {
			_infos[(unsigned char)ch]._count++;
		}

		// 2. Huffmantree encode
		CharInfo invalid;
		invalid._count = 0;

		HuffmanTree<CharInfo> tree(_infos, 256, invalid);

		// 3. write to the compressed file header
		std::string compressfile = file;
		compressfile += ".huffman";
		FILE* fout = fopen(compressfile.c_str(), "wb");
		assert(fin);

		std::string code;
		// generate the huffman code
		GenerateHuffmanCode(tree.getRoot(), code);

		// write the huffman code table into the header
		int writeNum = 0;
		int objSize = sizeof(TmpInfo);
		for (size_t i = 0; i < 256; ++i) {
			if (_infos[i]._count > 0) {
				TmpInfo info;
				info._ch = _infos[i]._ch;
				info._count = _infos[i]._count;
				printf("codec ch:%u, count:%u\n", (unsigned char)info._ch, info._count);
				fwrite(&info, objSize, 1, fout);
				writeNum++;
			}
		}
		TmpInfo info;
		info._count = -1;
		printf("code objSize:%d\n", objSize);
		fwrite(&info, objSize, 1, fout);	//write the end tag as info._count = -1

		// 4. write the compressed binary code
		int writeCount = 0;
		int readCount = 0;
		fseek(fin, 0, SEEK_SET);	//seek into the front of the input file
		unsigned char value = 0;
		size_t pos = 0;

		while ((ch = fgetc(fin)) != EOF) {
			++readCount;

			std::string& code = _infos[(unsigned char)ch]._code;
			// printf("code[%d]:%u:%s\n", readCount, (unsigned char)ch, code.c_str());

			// convert into binary string and write to the file.
			for (size_t i = 0; i < code.size(); ++i) {
				if (code[i] == '1') {
					value |= (1 << pos);
				}
				else if (code[i] == '0') {
					value &= ~(1 << pos);
				}
				else {
					assert(false);
					printf("assert(false); invalid huffman code %u\n", (unsigned char)code[i]);
				}

				++pos;
				if (pos == 8) {
					writeCount++;
					fputc(value, fout); //write 8bit into file
					value = 0;
					pos = 0;

					if (writeCount % (1024 * 1024) == 0) {
						printf("compressed %d mBytes data\n", writeCount / (1024 * 1024));
					}
				}
			}
		}

		if (pos > 0) {
			writeCount++;
			fputc(value, fin);	// write the left byte.
		}

		printf("huffman code table size:%d\n", objSize * (writeNum + 1));
		printf("compress file data size:%d\n", writeCount);
		unsigned long totalSize = writeCount + objSize * (writeNum + 1);
		printf("compress file total size:%lu, orign file size:%lu, ratio:%0.2f\n",
			totalSize, fileSize, (float)(totalSize * 1.0 / fileSize));

		// clean up.
		fclose(fin);
		fclose(fout);
	}

	// uncompress the target file
	void Uncompress(const char* file) {
		std::string uncompressfile = file;	// the input file should be xxx.yyy.huffman
		size_t pos = uncompressfile.rfind('.'); // find the last '.'
		assert(pos != std::string::npos);
		uncompressfile.erase(pos);			// delete the ".huffman"
		uncompressfile += ".unhuffman";		// add the extension ".unhuffman"
		FILE * fout = fopen(uncompressfile.c_str(), "wb"); // the file to be uncompressed.
		assert(fout);
		FILE* fin = fopen(file, "rb");		
		assert(fin);

		// read the huffman table info
		TmpInfo info;
		int cycleNum = 1;
		int objSize = sizeof(TmpInfo);
		fread(&info, objSize, 1, fin);

		// read until to the end info tag.
		while (info._count != (CountType)-1) { 
			printf("decodec ch:%u, cout:%u\n", (unsigned char)info._ch, info._count);
			_infos[(unsigned char)info._ch]._ch = info._ch;
			_infos[(unsigned char)info._ch]._count = info._count;

			fread(&info, objSize, 1, fin);
			cycleNum++;
		}

		// construct the HuffmanTree
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);
		Node * root = tree.getRoot();
		Node* cur = root;
		CountType n = root->_weight._count;	// total characters
		int readCount = 0;
		int ch;

		while ((ch = fgetc(fin)) != EOF || n > 0) {
			for (size_t i = 0; i < 8; ++i) {
				if (!cur)
					break;
				if ((ch & (1 << i)) == 0)
					cur = cur->_pLeft;  // search from left
				else
					cur = cur->_pRight; // search from right

				if (cur && cur->_pLeft == NULL && cur->_pRight == NULL) {
					readCount++;
					if (readCount % 1024 == 0) {
						printf("uncompress %dk data\n", readCount / 1024);
					}

					fputc(cur->_weight._ch, fout);
					cur = root;
					if (--n == 0)
						break;
				}
			}
		}
		printf("uncompress end!\n");
		fclose(fin);
		fclose(fout);
	}
protected:
	CharInfo _infos[256];
};


#endif