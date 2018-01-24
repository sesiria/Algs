/*
 * Exercise 3.27
 * Author: sesiria  2018
 * evalutation the value of the postfix expression
 * with data structure stack.
 * time complexity is O(N)
 */
#include <iostream>
#include <sstream>
#include <stack>
#include <exception>
#include <string.h>
#include <string>
#include <cmath>

#define EOL (-1)
#define TOKEN (0)
#define OPERATOR (1)


// exception
class DivedByZeroException : std::exception
{
    virtual const char * what() const noexcept
    {
        return "divided by zero exception!.";
    }
};


// skip blank space '\n' '\t'
void skipblank(const std::string &str, size_t &pos)
{
    while (isblank(str[pos]) && pos < str.size())
        pos++;
}

// seek to token/operator end.
void seekToTokenEnd(const std::string &str, size_t &pos)
{
    while (!isblank(str[pos]) &&
           (isalnum(str[pos]) || str[pos] == '.') &&
           pos < str.size())
        pos++;
}

/**
 * get token from the input string.
 * return value:
 * -1 error, or EOL.
 * 0 TOKEN
 * 1 OPERATOR
 */
int getTokenAndOperator(const std::string &str, size_t &pos, std::string &token)
{
    if (pos >= str.size())
        return EOL; // seek to the end of the string.

    skipblank(str, pos);

    if (pos >= str.size())
        return EOL; // seek to the end of the string.

    size_t startPos = pos;
    seekToTokenEnd(str, pos);

    if (pos > startPos) // it is an token
    {
        token = str.substr(startPos, pos - startPos); // combine an token.
        return TOKEN;
    }
    else // it is an operator for more sophisciated, we need a function to check the token.
    {
        token = str.substr(startPos, 1);
        pos++; // update pos.
        return OPERATOR;
    }
}

int StringToDouble(const std::string &str)
{
    std::stringstream ss(str);
    double val;
    ss >> val;
    return val;
}

/**
 * this routine will evaluate the value of the postfix expression.
 * time complexity O(N)
 */
double evaluateExpression(const std::string &expr)
{
    std::stack<double> exprStack;
    std::string token;
    size_t pos = 0;
    int retVal = 0;
    while ((retVal = getTokenAndOperator(expr, pos, token)) != EOL)
    {
        switch (retVal)
        {
        case TOKEN:
            exprStack.push(StringToDouble(token));
            break;

        case OPERATOR:
            double exp2 = exprStack.top();
            exprStack.pop();
            double exp1 = exprStack.top();
            exprStack.pop();

            // suppose we only support one character operator.
            switch (token[0])
            {
            case '+':
                exprStack.push(exp1 + exp2);
                break;
            case '-':
                exprStack.push(exp1 - exp2);
                break;
            case '*':
                exprStack.push(exp1 * exp2);
                break;
            case '/':
                if(exp2 == 0)
                    throw DivedByZeroException{};
                exprStack.push(exp1 / exp2);
                break;
            case '^':
                exprStack.push(pow(exp1, exp2));
                break;
            }
            //exprStack.push({exp1.expr + " " + token + " " + exp2.expr, tokenPriority});
            break;
        }
    }

    if(exprStack.empty())
        return 0.0f;
    double output = exprStack.top();
    return output;
}

int main(int argc, char **argv)
{
    std::string expr = "6 5 2 3 + 8 * + 3 + *";
    std::cout << evaluateExpression(expr) << std::endl;
    return 0;
}
