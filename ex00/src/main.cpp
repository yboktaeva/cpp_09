/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:02:25 by yuboktae          #+#    #+#             */
/*   Updated: 2024/01/31 18:24:48 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << RED << "Error: " << RESET << "could not open file." << std::endl;
        return 1;
    }
    std::map<std::string, double> rates;
    BitcoinExchange exchange(rates);
    try {
        exchange.readRates("data.csv", rates);
        // for (std::map<std::string, double>::iterator it = rates.begin(); it != rates.end(); it++) {
        //     std::cout << it->first << ", " << it->second << std::endl;
        // }
    }
    catch (std::exception &e) {
        std::cout << RED << "Error: " << RESET << e.what() << std::endl;
        return 1;
    }
    exchange.printResult(argv[1]);
    return 0;
}