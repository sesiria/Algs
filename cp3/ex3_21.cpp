/*
 * Exercise 3.21
 * Author: sesiria  2018
 * balancing symbols check rountine.
 */
#include <iostream>
#include <stack>
#include <string.h>
#include <string>

// skip blank space '\n' '\t'
void skipblank(const std::string &str, size_t &pos)
{
    while (isblank(str[pos]) && pos < str.size())
        pos++;
}

// seek to token/operator end.
void seekToTokenEnd(const std::string &str, size_t &pos)
{
    while (!isblank(str[pos]) && (isalnum(str[pos])) && pos < str.size())
        pos++;
}

// seek cpp comment
bool seekCppComment(const std::string &str, size_t &pos)
{
    while (pos < str.size())
    {
        if (str[pos] == '*' &&
            (pos + 1) < str.size() &&
            str[pos + 1] == '/')
            return true; // found the end of the comment.
        pos++;
    }
    return false;
}

// get token from the input string.
bool getTokenAndOperator(const std::string &str, size_t &pos, std::string &token)
{
    skipblank(str, pos);
    size_t startPos = pos;
    size_t endpos = startPos;
    seekToTokenEnd(str, endpos);
    if (endpos >= str.size())
        return false;      // seek to the end of the string.
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
            if (!seekCppComment(str, endpos))
            {
                printf("Syntax error mismatched for comment \n");
                return false;
            }
            else
            {
                token = "";
                pos = endpos;
                return true;
            }
        }

        token = str.substr(startPos, 1);
        pos = endpos + 1; // update pos.
    }
    return true;
}

/**
 *  check for pascal language. with (begin/end, (), [], {})
 *  time complexity O(N) N is the size of the input string.
 */
bool checkForPascal(const std::string &str)
{
    std::stack<std::string> codeStack;
    std::string token;
    size_t pos = 0;
    while (getTokenAndOperator(str, pos, token))
    {
        std::cout << token << std::endl;
        if (token == "begin" || token == "(" || token == "[" || token == "{")
            codeStack.push(token);
        else if (token == "end")
        {

            if (codeStack.empty() || codeStack.top() != "begin")
            {
                printf("Syntax error mismatched for begin/end at position %u\n", pos);
                return false;
            }
            codeStack.pop();
        }
        else if (token == ")")
        {
            if (codeStack.empty() || codeStack.top() != "(")
            {
                printf("Syntax error mismatched for () at position %u\n", pos);
                return false;
            }
            codeStack.pop();
        }
        else if (token == "]")
        {
            if (codeStack.empty() || codeStack.top() != "[")
            {
                printf("Syntax error mismatched for [] at position %u\n", pos);
                return false;
            }
            codeStack.pop();
        }
        else if (token == "}")
        {
            if (codeStack.empty() || codeStack.top() != "{")
            {
                printf("Syntax error mismatched for {} at position %u\n", pos);
                return false;
            }
            codeStack.pop();
        }
    }
    if (codeStack.size() > 0)
        printf("Syntax error mismatched for %s \n", codeStack.top().c_str());
    return true;
}

/**
 *  check for c++ language. with (comment, (), [], {})
 *  time complexity O(N) N is the size of the input string.
 */
bool checkForCpp(const std::string &str)
{
    std::stack<std::string> codeStack;
    std::string token;
    size_t pos = 0;
    while (getTokenAndOperator(str, pos, token))
    {
        std::cout << token << std::endl;
        if (token == "begin" || token == "(" || token == "[" || token == "{")
            codeStack.push(token);
        else if (token == "end")
        {

            if (codeStack.empty() || codeStack.top() != "begin")
            {
                printf("Syntax error mismatched for begin/end at position %u\n", pos);
                return false;
            }
            codeStack.pop();
        }
        else if (token == ")")
        {
            if (codeStack.empty() || codeStack.top() != "(")
            {
                printf("Syntax error mismatched for () at position %u\n", pos);
                return false;
            }
            codeStack.pop();
        }
        else if (token == "]")
        {
            if (codeStack.empty() || codeStack.top() != "[")
            {
                printf("Syntax error mismatched for [] at position %u\n", pos);
                return false;
            }
            codeStack.pop();
        }
        else if (token == "}")
        {
            if (codeStack.empty() || codeStack.top() != "{")
            {
                printf("Syntax error mismatched for {} at position %u\n", pos);
                return false;
            }
            codeStack.pop();
        }
    }
    if (codeStack.size() > 0)
        printf("Syntax error mismatched for %s \n", codeStack.top().c_str());
    return true;
}

int main(int argc, char **argv)
{

    checkForPascal("int main(char); /*test comment");
    return 0;
}