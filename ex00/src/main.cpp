/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:02:25 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/01 18:00:42 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    try {
        if (argc != 2)
            throw std::invalid_argument("Wrong number of arguments");
    }
    catch (std::exception &e) {
        std::cout << RED << "Error: " << RESET << e.what() << std::endl;
        return 1;
    }
    BitcoinExchange exchange("data.csv");
    exchange.printResult(argv[1]);
    return 0;
}