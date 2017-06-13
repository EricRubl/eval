//
// Created by Eric on 12.06.2017.
//

#ifndef EVAL_EXPRESSION_HPP
#define EVAL_EXPRESSION_HPP

#include <string>
#include <algorithm>
#include <utility>
#include <regex>
#include <iostream>
#include "DynamicQueue.hpp"
#include "DynamicStack.hpp"

namespace Eval
{
    enum class Operation : int
    {
        ADD = -1, SUB = -2, MUL = -3, DIV = -4, LEFT = -5, RIGHT = -6
    };

    int Priority(int code)
    {
        if(code == -1 or code == -2)
            return 1;
        else
            return 2;
    }

    class Expression
    {
    public:
        DynamicQueue<int> infix;
        DynamicQueue<int> postfix;
    public:
        Expression() = default;
        ~Expression() = default;

        friend std::istream& operator>>(std::istream& input, Expression& exp)
        {
            std::string buffer;
            std::cout << "Expression: ";
            std::cin >> buffer;

            std::regex syntax_check("^\\(*[0-9]+([-+*/]\\(*[0-9]+\\)*)*$");

            auto left = std::count(buffer.begin(), buffer.end(), '(');
            auto right = std::count(buffer.begin(), buffer.end(), ')');

            if(!std::regex_match(buffer, syntax_check) or (left not_eq right))
                throw "Syntax error :(";

            std::string number;
            bool nr = false;

            for(char& c : buffer)
                if(c == '+' or c == '-' or c == '*' or c == '/' or c == '(' or c == ')'){
                    if(nr){
                        exp.infix.push(std::stoi(number));
                        number = "";
                        nr = false;
                    }
                    switch(c){
                        case '+':
                            exp.infix.push((int)Operation::ADD);
                            break;
                        case '-':
                            exp.infix.push((int)Operation::SUB);
                            break;
                        case '*':
                            exp.infix.push((int)Operation::MUL);
                            break;
                        case '/':
                            exp.infix.push((int)Operation::DIV);
                            break;
                        case '(':
                            exp.infix.push((int)Operation::LEFT);
                            break;
                        case ')':
                            exp.infix.push((int)Operation::RIGHT);
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    nr = true;
                    number += c;
                }
            if(number not_eq "")
                exp.infix.push(std::stoi(number));
        }

        void toPostfix()
        {
            DynamicStack<int> stack;
            while(not infix.empty())
            {
                int token = infix.front();
                if(token >= 0)
                {
                    postfix.push(token);
                    infix.pop();
                }
                else
                {
                    if(stack.empty() or stack.top() == (int)Operation::LEFT or token == (int)Operation::LEFT)
                    {
                        stack.push(token);
                        infix.pop();
                    }
                    else if(token == (int)Operation::RIGHT)
                    {
                        while(stack.top() not_eq (int)Operation::LEFT)
                        {
                            postfix.push(stack.top());
                            stack.pop();
                        }
                        stack.pop();
                        infix.pop();
                    }
                    else if(Priority(token) > Priority(stack.top()))
                    {
                        stack.push(token);
                        infix.pop();
                    }
                    else if(Priority(token) == Priority(stack.top()))
                    {
                        postfix.push(stack.top());
                        stack.pop();
                        stack.push(token);
                        infix.pop();
                    }
                    else if(Priority(token) < Priority(stack.top()))
                    {
                        postfix.push(stack.top());
                        stack.pop();

                        if(stack.empty())
                            goto here;
                        while(Priority(token) < Priority(stack.top()))
                        {
                            postfix.push(stack.top()); // mai usor cu ; galatan
                            stack.pop();
                        }
                        if(Priority(token) == Priority(stack.top()))
                        {
                            postfix.push(stack.top());
                            stack.pop();
                            stack.push(token);
                        }
                        else if(Priority(token) > Priority(stack.top()))
                            stack.push(token);
                        here:
                        stack.push(token);
                        infix.pop();
                    }
                }
            }
            while(not stack.empty())
            {
                postfix.push(stack.top());
                stack.pop();
            }
        }

        int eval()
        {
            DynamicStack<int> stack;
            while(not postfix.empty())
            {
                int token = postfix.front();
                if(token >= 0)
                {
                    stack.push(token);
                    postfix.pop();
                }
                else
                {
                    auto temp = stack.top();
                    stack.pop();
                    int res;
                    switch(token)
                    {
                        case -1:
                            res = stack.top() + temp;
                            break;
                        case -2:
                            res = stack.top() - temp;
                            break;
                        case -3:
                            res = stack.top() * temp;
                            break;
                        case -4:
                            if(temp == 0)
                                throw "Division by 0 impossible!";
                            res = stack.top() / temp;
                            break;
                        default:
                            break;
                    }
                    stack.pop();
                    stack.push(res);
                    postfix.pop();
                }
            }
            return stack.top();
        }
    };
}

#endif //EVAL_EXPRESSION_HPP
