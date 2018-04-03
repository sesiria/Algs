/*
* Exercise 5.15
* Author: sesiria  2018
* string search algorithm implementation by hash function.
* expected complexity O(N + k)
*/
#include <iostream>
#include <cstring>

#define HASH_FACTOR (37)

typedef unsigned long long hashType;

hashType power(long long x, int n)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	if (n % 2 == 0)
		return power(x * x, n / 2);
	else
		return power(x * x, n / 2) * x;
}

/**
* ansi c-style hash function for performance.
* complexity O(k)
*/
hashType hash(const char * array, size_t nlen)
{
	long long hashValue = 0;
	for (size_t p = 0; p < nlen; ++p)
		hashValue = HASH_FACTOR * hashValue + array[p];
	return hashValue;
}

/**
* rehash function, time complexity O(1)
*/
inline hashType
rehash(hashType hashValue, hashType factor, const char firstChar, const char lastChar)
{
	return HASH_FACTOR * hashValue - factor * firstChar + lastChar;
}

/**
* Pattern search algorithm by hash function and rehash function.
* time complexity O(n + k)
*/
const char * patternSearch(const char *str, const char *pattern)
{
	size_t lenPattern = strlen(pattern);
	size_t lenStr = strlen(str);

	if (lenStr < lenPattern)
		return nullptr;

	hashType hashPattern = hash(pattern, lenPattern);

	const char *p = str;
	hashType hashMatch = hash(p, lenPattern);
	hashType factor = power(HASH_FACTOR, lenPattern);

	while (p <= (str + lenStr - lenPattern) &&
		(hashMatch != hashPattern || strncmp(p, pattern, lenPattern) != 0)) {
		hashMatch = rehash(hashMatch, factor, p[0], p[lenPattern]);
		++p;
	}

	return (hashMatch == hashPattern) ? p : nullptr;
}

int main()
{
	char str[] = "Sometimes the analysis is shown empirically to be an overestimate. If this is the case, then either the analysis needs to be tightened(usually by a clever observation), or it may be that the average running time is significantly less than the worst-case running time and no improvement in the bound is possible. For many complicated algorithms the worst-case bound is achievable by some bad input but is usually an overestimate in practice. Unfortunately, for the most these problems, an average-case analysis is extremely complex(int many cases still unsolved), and a word-case bound, even though overly perssimistic, is the best analytical result known.";
	char pattern[] = "If this is the case, then either the analysis needs to be tightened(usually by a clever observation)";

	if (patternSearch(str, pattern))
		std::cout << "found pattern" << std::endl;

	else
		std::cout << "not found!" << std::endl;

	return 0;
}

