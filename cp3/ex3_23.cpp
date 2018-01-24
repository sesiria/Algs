/*
 * Exercise 3.23
 * Author: sesiria  2018
 * a) convert expression from infix to postfix
 * b) support exponentiation operator "infixToPostfix"
 * c) convert from postfix to infix. "postfixToInfix"
 */
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string.h>
#include <string>

#define EOL (-1)
#define TOKEN (0)
#define OPERATOR (1)

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

std::map<std::string, int> g_operators;
int highestPriority;
/**
 * build the operator map.
 */
void buildOperatorPriority()
{
    int priority = 0;
    g_operators["("] = priority;
    ++priority;
    g_operators["+"] = priority;
    g_operators["-"] = priority;
    ++priority;
    g_operators["*"] = priority;
    g_operators["/"] = priority;
    ++priority;
    g_operators["^"] = priority; // for exponent.
    ++priority;
    g_operators[")"] = priority;
    highestPriority = priority;
}
/**
 * return the priority of a token.
 * if the token is invalid, return -1.
 * for convient we just use vector to store the priority of the token. O(N)
 */
int getOperatorPriority(const std::string &op)
{
    auto iter = g_operators.find(op);
    if (iter != g_operators.end())
    {
        return iter->second;
    }
    return -1;
}

/**
 *  if op1 has less priority than op2
 *  return true
 *  otherwise return false.
 */
bool operatorLessPriority(const std::string &op1, const std::string &op2)
{
    return getOperatorPriority(op1) < getOperatorPriority(op2);
}

bool operatorGreaterPriority(const std::string &op1, const std::string &op2)
{
    return getOperatorPriority(op1) > getOperatorPriority(op2);
}

/**
 *  convert expression from infix to postfix
 *  support for exponent.
 */
std::string infixToPostfix(const std::string &str)
{
    std::stack<std::string> codeStack;
    std::string output;
    std::string token;
    size_t pos = 0;
    int retVal = 0;
    while ((retVal = getTokenAndOperator(str, pos, token)) != EOL)
    {
        // std::cout << token << std::endl;
        switch (retVal)
        {
        case TOKEN:
            output.append(token);
            output.append(" ");
            break;
        case OPERATOR:
            if (getOperatorPriority(token) == -1) // illegal operator.
            {
                std::cout << "can't support the operator " << token << std::endl;
                abort(); // exit the process.
            }

            if (token == "(")
            {
                codeStack.push(token);
            }
            else if (token == ")")
            {
                // pop until we meet the "("
                while (!codeStack.empty() && codeStack.top() != "(")
                {
                    output.append(codeStack.top());
                    output.append(" ");
                    codeStack.pop();
                }
                if (codeStack.empty())
                {
                    std::cout << "Illegal expression " << std::endl;
                    abort(); // exit the process.
                }
                else
                {
                    codeStack.pop(); // pop the "(";
                }
            }
            else if (token == "^")
            {
                // pop until we meet the the less or equal priority token.
                while (!codeStack.empty() &&
                       operatorGreaterPriority(codeStack.top(), token))
                {
                    output.append(codeStack.top());
                    output.append(" ");
                    codeStack.pop();
                }
                codeStack.push(token);
            }
            else
            {
                // pop until we meet the the less priority token.
                while (!codeStack.empty() &&
                       !operatorLessPriority(codeStack.top(), token))
                {
                    output.append(codeStack.top());
                    output.append(" ");
                    codeStack.pop();
                }
                codeStack.push(token);
            }
            break;
        }
    }

    while (!codeStack.empty())
    {
        output.append(codeStack.top());
        output.append(" ");
        codeStack.pop();
    }

    return output;
}

typedef struct
{
    std::string expr; // expression string
    int priority;     // current expression priority
} Expression;

/**
 *  convert expression from postfix to infix
 *  support for exponent.
 *  ignore some error handling.
 *  time complexity O(N)
 */
std::string postfixToInfix(const std::string &str)
{
    std::stack<Expression> exprStack;
    std::string output;
    std::string token;
    size_t pos = 0;
    int retVal = 0;
    while ((retVal = getTokenAndOperator(str, pos, token)) != EOL)
    {
        switch (retVal)
        {
        case TOKEN:
            exprStack.push({token, highestPriority});
            break;

        case OPERATOR:
            if (getOperatorPriority(token) == -1) // illegal operator.
            {
                std::cout << "can't support the operator " << token << std::endl;
                abort(); // exit the process.
            }

            Expression exp2 = exprStack.top();
            exprStack.pop();
            Expression exp1 = exprStack.top();
            exprStack.pop();
            int tokenPriority = getOperatorPriority(token);
            if(exp2.priority < tokenPriority)
                exp2.expr = "(" + exp2.expr + ")";
            if(exp1.priority < tokenPriority)
                exp1.expr = "(" + exp1.expr + ")";
            exprStack.push({exp1.expr + " " + token + " " + exp2.expr, tokenPriority});
            break;
        }
    }
    output = exprStack.top().expr;
    return output;
}

int main(int argc, char **argv)
{
    buildOperatorPriority();
    std::string expr = "4.99 * 1.06 - 5.99 / 6.99 * 1.06";
    std::string exp1 = "a + b * c + (d * e + f) * g";
    std::string exp2 = "2 ^ (3 + 2) ^ 4";
    std::string exp3 = "(1 + (2) + 4)";
    std::cout << infixToPostfix(expr) << std::endl;
    std::cout << infixToPostfix(exp1) << std::endl;
    std::cout << infixToPostfix(exp2) << std::endl;
    std::cout << postfixToInfix(infixToPostfix(expr)) << std::endl;
    std::cout << postfixToInfix(infixToPostfix(exp1)) << std::endl;
    std::cout << postfixToInfix(infixToPostfix(exp2)) << std::endl;
    std::cout << postfixToInfix("6 5 2 3 + 8 * + 3 + *") << std::endl;
    return 0;
}