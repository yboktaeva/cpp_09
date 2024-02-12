/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:34:47 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/12 17:28:16 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : _stack(), _input(), _result(0) {}

RPN::RPN(std::string input) : _result(0) {
    _input = input;
    parseInput(_input);
}

RPN::RPN(const RPN &src) {
    *this = src;
}

RPN &RPN::operator=(const RPN &src) {
    if (this != &src) {
        _stack = src._stack;
        _result = src._result;
    }
    return (*this);
}

std::stack<int> RPN::getStack() const {
    return (_stack);
}

RPN::~RPN() {}

void    RPN::parseInput(std::string input) {
    for (int i = 0; input[i]; i++) {
        if (!IS_NUM(input[i]) && input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != ' ')
            throw std::invalid_argument("invalid input.");
        if (IS_NUM(input[i]) && IS_NUM(input[i + 1]))
            throw std::invalid_argument("number too big. Max 1 digit allowed.");
    }
}

void    RPN::getResult() {
    std::string operators = "+-*/";
    for (int i = 0; _input[i]; i++) {
        if (IS_NUM(_input[i])) {
            _stack.push(_input[i] - '0');
        }
        else if (operators.find(_input[i]) != std::string::npos) {
            int a = _stack.top();
            _stack.pop();
            if (_stack.empty())
                throw std::invalid_argument("invalid result. Not enough numbers to operate on.");
            int b = _stack.top();
            _stack.pop();
            switch (_input[i]) {
            case '+':
                _stack.push(a + b);
                break;
            case '-':
                _stack.push(b - a);
                break;
            case '*':
                _stack.push(a * b);
                break;
            case '/':
                if (a == 0)
                    throw std::invalid_argument("division by zero.");
                _stack.push(b / a);
                break;
            }
        }
    }
    _result = _stack.top();
    std::cout << GREEN << "Result: " << RESET << _result << std::endl;
}