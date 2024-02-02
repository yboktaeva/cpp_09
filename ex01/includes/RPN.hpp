/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:34:34 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/02 16:20:51 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# define RED "\033[1;31m"
# define RESET "\033[0m"
# define IS_NUM(x) (x >= '0' && x <= '9')

# include <iostream>
# include <stack>
# include <cstdlib>
# include <exception>

class   RPN{
    private:
        std::stack<int> _stack;
        std::string _input;
        int _result;
        RPN();
    public:
        RPN(std::string input);
        RPN(const RPN &src);
        ~RPN();
        RPN &operator=(const RPN &src);
        void parseInput(std::string input);
        void getResult();
        std::stack<int> getStack() const;
};

#endif