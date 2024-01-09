/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:02:25 by yuboktae          #+#    #+#             */
/*   Updated: 2024/01/09 17:45:52 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    (void)argv;
    (void)argc;
    // if (argc != 2)
    // {
    //     std::cout << RED << "Error: " << RESET << "could not open file." << std::endl;
    //     return 1;
    // }
    BitcoinExchange exchange;
    std::map<std::string, float> rates;
    exchange.readRates("data.csv", rates);
    for (std::map<std::string, float>::iterator it = rates.begin(); it != rates.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
    // if (rates.find(date) != rates.end()) {
    //     std::cout << "Rate for " << date << ": " << rates[date] << std::endl;
    // } else {
    //     std::cout << "No rate found for " << date << std::endl;
    // }
    // std::map<std::string, float> input = exchange.getInput(argv[1]);
    // for (std::map<std::string, float>::iterator it = input.begin(); it != input.end(); ++it) {
    //     std::cout << it->first << " " << it->second << std::endl;
    // }
    //exchange.checkMap(map);
    return 0;
}