/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:02:08 by yuboktae          #+#    #+#             */
/*   Updated: 2024/01/31 18:59:04 by yuboktae         ###   ########.fr       */
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

std::map<std::string, double> BitcoinExchange::getRates() const {
    return (_rates);
}

void BitcoinExchange::readRates(std::string filename, std::map<std::string, double> &rates) {
    double rate;
    char *end;
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        throw std::runtime_error("could not open file for read or file does not exist.");
    }
    std::string line;
    std::getline(ifs, line);
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string date;
        std::getline(ss, date, ',');
        struct tm tmSruct = {};
        if (!strptime(date.c_str(), "%Y-%m-%d", &tmSruct)) {
            throw std::runtime_error("bad format => " + date + ". Format must be YYYY-MM-DD.");
        }
        std::string str;
        if (!(ss >> str))
            throw std::runtime_error("no rate.");
        rate = strtod(str.c_str(), &end);
        if (rate < 0)
            throw std::runtime_error("not a positive number.");
        rates[date] = rate;
    }
    ifs.close();
}

std::string BitcoinExchange::checkDate(std::stringstream &ss) {
    std::string date;
    std::getline(ss, date, '|');
    struct tm tmSruct = {};
    if (!strptime(date.c_str(), "%Y-%m-%d", &tmSruct)) {
        throw std::runtime_error("bad format => " + date + ". Format must be YYYY-MM-DD.");
    }
    date = date.substr(0, 10);
    return (date);
    
}

double  BitcoinExchange::checkValue(std::stringstream &ss) {
    std::string str;
    if (!(ss >> str)) {
        throw std::runtime_error("no value.");
    }
    double value;
    value = strtod(str.c_str(), NULL);
    if (value < 0) {
        throw std::runtime_error("not a positive number.");
    }
    else if (value > 1001) {
        throw std::runtime_error("too large number.");
    }
    return (value);
}

void    BitcoinExchange::printResult(std::string filename) {
    std::string date;
    double value;
    try {
        std::ifstream ifs(filename.c_str());
        if (!ifs.is_open()) {
            throw std::runtime_error("could not open file for read or file does not exist.");
        }
        std::string line;
        std::getline(ifs, line);
        while (std::getline(ifs, line)) {
            std::stringstream ss(line);
            date = checkDate(ss);
            value = checkValue(ss);
            std::cout << "test " << date << " | " << value << std::endl;
            std::map<std::string, double>::iterator it = _rates.lower_bound(date);
            if (it != _rates.begin() && (--it)->first == date) {
                std::cout << date << " | " << value << " => " << value * it->second << std::endl;
            }
            else if (it != _rates.begin()) {
                --it;
                std::cout << date << " | " << value << " => " << value * it->second << std::endl;
            }
            else {
                std::cout << date << " | " << value << " => " << value * it->second << std::endl;
            }
        }
        ifs.close();
    }
    catch (std::exception &e) {
        std::cout << RED << "Error: " << RESET << e.what() << std::endl;
    }
}