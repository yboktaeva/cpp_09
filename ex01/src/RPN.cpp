/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:34:47 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/02 13:55:18 by yuboktae         ###   ########.fr       */
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
    try {
        for (int i = 0; input[i]; i++) {
            if (!IS_NUM(input[i]) && input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != ' ')
                throw std::invalid_argument("Invalid input");
        }
    }
    catch (std::exception &e) {
        std::cout << RED << "Error: " << RESET << e.what() << std::endl;
        exit(1);
    }
}

void    RPN::getResult() {
    for (int i = 0; _input[i]; i++) {
        if (IS_NUM(_input[i])) {
            _stack.push(_input[i] - '0');
        }
        else if (_input[i] == '+' || _input[i] == '-' || _input[i] == '*' || _input[i] == '/') {
            int a = _stack.top();
            _stack.pop();
            int b = _stack.top();
            _stack.pop();
            if (_input[i] == '+')
                _stack.push(a + b);
            else if (_input[i] == '-')
                _stack.push(b - a);
            else if (_input[i] == '*')
                _stack.push(a * b);
            else if (_input[i] == '/')
                _stack.push(b / a);
            }
    }
    _result = _stack.top();
    std::cout << "Result: " << _result << std::endl;
}