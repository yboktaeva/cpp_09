/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:34:59 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/12 17:27:28 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
    try {
        if (argc != 2)
            throw std::invalid_argument("Wrong number of arguments.");
    }
    catch (std::exception &e) {
        std::cout << RED << "Error: " << RESET << e.what() << std::endl;
        return (1);
    }
    try {
        RPN rpn(argv[1]);
        rpn.getResult();
    }
    catch (std::exception &e) {
        std::cout << RED << "Error: " << RESET << e.what() << std::endl;
        return (1);
    }
    return (0);
}