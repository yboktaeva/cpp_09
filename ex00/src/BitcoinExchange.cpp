/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:02:08 by yuboktae          #+#    #+#             */
/*   Updated: 2024/01/10 19:09:12 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _rates() {}

BitcoinExchange::BitcoinExchange(std::map<std::string, double> rates) : _rates(rates) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    _rates = other._rates;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this == &other)
        return (*this);
    _rates = other._rates;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::checkDate(const std::string &date) {
    
    
}

void BitcoinExchange::readRates(std::string filename, std::map<std::string, double> &rates) {
    double rate;
    char *end;
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
        std::string str;
        ss >> str;
        rate = strtod(str.c_str(), &end);
        rates[date] = rate;
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