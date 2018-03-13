/*
* Exercise 4.50
* Author: sesiria  2018
* read input from a c++ source code file outputs a list of all identifies.
*/
#include <fstream>
#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <vector>

#define TOKEN (0)
#define COMMENT (1)
#define LITERAL (2)
#define MACRO (3)

unsigned char utf8TAG[3] = { 0xef, 0xbb, 0xbf };

std::string keywords[] =
{
	"asm", "auto", "bool", "break", "case", "catch", "char", "class", "const", "const_cast", "continue", "default", "delete",
	"do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", "friend", "goto",
	"if", "inline", "int", "long", "mutable", "namespace", "new", "operator", "private", "protected", "public", "register", "reinterpret_cast",
	"return", "short", "signed", "sizeof", "static", "struct", "switch", "template", "this", "throw", "true",
	"try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while" };

std::string ops[] =
{
	"+", "-", "*", "/", "%", "'", "\"", "{", "}", "(", ")",
	"<<", ">>", ",", ".", ";", "->", "==", "!=", "<", ">", "<=", ">=",
	"&&", "||", "!", "++", "--", "+=", "-=", "*=", "/=", "%=", "=", "::",
	"[", "]", "&", "|", "\\", ":" };

// the more efficient way is to use binary search.
bool isReserved(const std::string &token)
{
	for (int i = 0; i < _countof(keywords); ++i)
		if (token == keywords[i])
			return true;

	for (int i = 0; i < _countof(ops); ++i)
		if (token == ops[i])
			return true;

	return false;
}

bool isNumber(const std::string &token)
{
	if (isdigit(token[0]))
		return true;
	else
		return false;
}

// skip blank space '\n' '\t'
int skipblank(const std::string &str, size_t &pos)
{
	int skipline = 0;
	while ((isblank(str[pos]) || str[pos] == '\n' || str[pos] == '\r') && pos < str.size())
	{
		if (str[pos] == '\n')
			++skipline;
		pos++;
	}
	return skipline;
}

// seek to token/operator end.
void seekToTokenEnd(const std::string &str, size_t &pos)
{
	while ((isalnum(str[pos]) || str[pos] == '_') && pos < str.size())
		pos++;
}

// seek cpp comment /**/
// return the number of lines skipped
// -1 for abnormal error
int seekCppComment(const std::string &str, size_t &pos)
{
	int skipLine = 0;
	while (pos < str.size())
	{
		if (str[pos] == '*' &&
			(pos + 1) < str.size() &&
			str[pos + 1] == '/')
		{
			++pos;
			return skipLine; // found the end of the comment.
		}

		if (str[pos] == '\n')
			++skipLine;
		pos++;
	}
	return -1;
}

// seek to the next line.
// return number of lines skipped.
int seektoNextLine(const std::string &str, size_t &pos)
{
	while (pos < str.size())
	{
		if (str[pos] == '\n') // seek to the double comment end
		{
			++pos;
			return 1;
		}
		++pos;
	}
	return -1;
}

// seek cpp double comment
// return number of lines skipped.
int seektoNextColon(const std::string &str, size_t &pos)
{
	while (pos < str.size())
	{
		if (str[pos] == '"') // seek to the double comment end
		{
			++pos;
			return 1;
		}
		else if (str[pos] == '\\') // ignore the escape character
		{
			++pos;
		}
		++pos;
	}
	return EOF;
}

// get token from the input string.
int getTokenAndOperator(const std::string &str, size_t &pos, std::string &token, int &totalSkipLine)
{
	totalSkipLine += skipblank(str, pos);
	size_t startPos = pos;
	size_t endpos = startPos;
	seekToTokenEnd(str, endpos);
	if (endpos >= str.size())
		return EOF;        // seek to the end of the string.
	if (endpos > startPos) // it is an token
	{
		token = str.substr(startPos, endpos - startPos); // combine an token.
		pos = endpos;                                    // update pos.
	}
	else // it is an operator for more sophisciated, we need and function to check the token.
	{
		if (str[endpos] == '/' && (endpos + 1) < str.size() && str[endpos + 1] == '*')
		{
			endpos += 2;
			int skipLine = 0;
			if ((skipLine = seekCppComment(str, endpos)) == EOF)
			{
				printf("Syntax error mismatched for comment \n");
				return EOF;
			}
			else
			{
				token = "";
				pos = endpos;
				totalSkipLine += skipLine;
				return COMMENT;
			}
		}
		else if (str[endpos] == '/' && (endpos + 1) < str.size() && str[endpos + 1] == '/') // double comment
		{
			int skipLine = 0;
			endpos += 2;
			if ((skipLine = seektoNextLine(str, endpos)) == EOF)
			{
				printf("Syntax error mismatched for comment \n");
				return EOF;
			}
			else
			{
				token = "";
				pos = endpos;
				totalSkipLine += skipLine;
				return COMMENT;
			}
		}
		else if (str[endpos] == '#') // skip one line macro
		{
			int skipLine = 0;
			endpos += 1;
			if ((skipLine = seektoNextLine(str, endpos)) == EOF)
			{
				printf("Syntax error mismatched for macro \n");
				return EOF;
			}
			else
			{
				token = "";
				pos = endpos;
				totalSkipLine += skipLine;
				return MACRO;
			}
		}
		else if (str[endpos] == '\'') // skip char
		{
			if (str[endpos + 1] == '\\')	// escape type of char
				endpos += 4;
			else
				endpos += 3;	// normal type of char
			token = "";
			pos = endpos;
			return LITERAL;
		}
		else if (str[endpos] == '"') // skip literal string
		{
			endpos += 1;
			if (seektoNextColon(str, endpos) == EOF)
			{
				printf("Syntax error mismatched for literal string \n");
				return EOF;
			}
			else
			{
				token = "";
				pos = endpos;
				return LITERAL;
			}
		}
		else

			token = str.substr(startPos, 1);
		pos = endpos + 1; // update pos.
	}
	return TOKEN;
}

bool checkForCpp(const std::string &str)
{
	std::map<std::string, std::vector<int>> codeStack;
	std::string token;
	size_t pos = 0;
	int lineCount = 1;
	int tokenType;
	while ((tokenType = getTokenAndOperator(str, pos, token, lineCount)) != EOF)
	{
		if (tokenType == TOKEN)
		{
			if (token == "\n")
			{
				lineCount++;
			}
			else if (!isReserved(token) && !isNumber(token))
			{
				codeStack[token].push_back(lineCount);
			}
		}
	}

	for (auto &x : codeStack)

	{
		std::cout << x.first << "\t";
		for (auto &y : x.second)
			std::cout << y << " ";
		std::cout << std::endl;
	}

	return true;
}

int main(int argc, char **argv)
{
	FILE *pfile = fopen("D:\\test.txt", "r");
	if (pfile == nullptr)
	{
		exit(1);
	}

	fseek(pfile, 0, SEEK_END);
	size_t lSize = ftell(pfile);
	rewind(pfile);

	char *buffer = new char[lSize];
	if (buffer == nullptr)
	{
		exit(2);
	}

	int c;
	size_t fileSize = 0;
	char *pBuf = buffer;
	while ((c = getc(pfile)) != EOF)
	{
		*pBuf++ = c;
		fileSize++;
	}
	*pBuf = '\0';

	// skip utf8 header.
	size_t pos = 0;
	if (fileSize > 3 &&
		(buffer[0] == utf8TAG[0] && buffer[1] == utf8TAG[1] && buffer[2] == utf8TAG[2]))
	{
		pos += 3;
	}

	std::string codeBuf = &buffer[pos];

	checkForCpp(codeBuf);

	delete[] buffer;
	fclose(pfile);
	return 0;
}