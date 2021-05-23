/*
* A Simple LZ77 Implementation Demo include the compress and decompress
* FileName: LZ77.cpp
* author: sesiria	2021-05-15
*/
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <stdint.h>
#include <assert.h>

typedef std::tuple<int, int, char> encodeUnit;

// the longestMatch will be used by the LZ77 compress funciton.
encodeUnit longestMatch(const std::string& inputBuffer, int cursor, int windowSize, int bufferSize) {
	int pos = -1;
	int len = -1;
	char c = '\0';	// the candidate string.
	int endBuffer = std::min(cursor + bufferSize, (int)inputBuffer.size());

	// i indicate the end of the candidate substring.
	// we search from a max silding window to small,
	// as a result, if we find a match it must be the longestMatch one.
	int startIndex = std::max(0, cursor - windowSize); // the start position of the window
	for (int i = endBuffer; i > cursor; i--) {
		std::string subStr(inputBuffer, cursor, i - cursor);

		// the candidate string.
		for (int j = startIndex; j < cursor &&  (cursor  - j) >= subStr.size(); j++) {
			std::string candidate(inputBuffer, j, subStr.size());
			if (candidate == subStr) {
				pos = j + windowSize - cursor;
				len = candidate.size();

				// if we meet the end of the string.
				//adjust the length.
				if (i == endBuffer) {
					len--; 
					i--;
				}
				c = inputBuffer[i];
				break;
			}
		}
		// there is a match
		if (len != -1) 
			break;
	}
	// if there is not any  match we push the current character
	if (pos == -1 || len == -1)
		return std::make_tuple(0, 0, inputBuffer[cursor]);
	return std::make_tuple(pos, len, c);
}

/* the compress routine of the Lz77 algorithm.
 inputBuffer: the buffer to be compressed.
 windowSize: the size of the sliding window
 bufferSize: the size of the buffer.
 the output is a vector of the tuples which indicates the pos, len, and the next character.
*/
std::vector<encodeUnit> lz77Compress(const std::string& inputBuffer, int windowSize, int bufferSize)
{
	int lenData = inputBuffer.size();
	int curSor = 0;
	std::vector<encodeUnit> compressData;
	while (curSor < lenData) {
		auto ret = longestMatch(inputBuffer, curSor, windowSize, bufferSize);
		curSor += (std::get<1>(ret) + 1);
		compressData.push_back(ret);
	}
	return compressData;
}

/* the decompress routine of the Lz77 algorithm.
 compressedData: the compressed data include vector of tuples (pos, len, character).
 windowSize: the size of the sliding window
 bufferSize: the size of the buffer.
 the output is a string of the decompress data.
*/
std::string lz77Decompress(std::vector<encodeUnit>& compressedData, int windowSize, int bufferSize)
{
	int cursor = 0;
	std::string out;

	for (auto& unit : compressedData) {
		int pos = std::get<0>(unit), len = std::get<1>(unit);
		char c = std::get<2>(unit);

		// normal character
		if (len > 0)
			out.append(std::string(out, cursor - windowSize + pos, len));
		out.append(1, c);
		cursor += (len + 1);
	}
	return out;
}

// test functions
void printEncodeUnit(const encodeUnit& eu) {
	std::cout << std::get<0>(eu) << ", ";
	std::cout << std::get<1>(eu) << ", ";
	std::cout << std::get<2>(eu) << "\n";
}

void testLZ77Compress()
{
	std::string str = "ABABCBABABCAD";
	//std::string str = "ABCDEFABCDEF";
	auto compressData = lz77Compress(str, 8, 8);

	for (auto& e : compressData)
		printEncodeUnit(e);
}

void testLZ77Decompress()
{
	std::string str = "ABABCBABABCAD";
	//std::string str = "ABCDEFABCDEF";
	auto compressData = lz77Compress(str, 8, 8);
	auto ret = lz77Decompress(compressData, 8, 8);
	assert(ret == str);
	if (ret == str)
		std::cout << "test decompress successful!\n";
	else
		std::cout << "test decompress failed!\n";
}

int main(int argc, char * argv[]) 
{
	testLZ77Compress();
	testLZ77Decompress();
	return 0;
}