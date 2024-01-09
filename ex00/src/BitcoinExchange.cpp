/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:02:08 by yuboktae          #+#    #+#             */
/*   Updated: 2024/01/09 17:45:29 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other)
        *this = other;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::readRates(std::string filename, std::map<std::string, float> &rates) {
    
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        std::cout << RED << "Error: " << RESET << "could not open file for read or file does not exist."  << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string date;
        std::getline(ss, date, ',');
        float rate;
        ss >> rate;
        rates.insert(std::pair<std::string, float>(date, rate));
    }
    ifs.close();
}

std::map<std::string, float> BitcoinExchange::getInput(std::string filename) {
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        std::cout << RED << "Error: " << RESET << "could not open file for read or file does not exist." << std::endl;
        exit(1);
    }
    std::string line;
    std::map<std::string, float> input;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string date;
        std::getline(ss, date, '|');
        float value;
        ss >> value;
        input.insert(std::pair<std::string, float>(date, value));
    }
    ifs.close();
    return (input);
}