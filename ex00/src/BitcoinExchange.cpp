/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:02:08 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/05 16:54:32 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _dataBaseName("data.csv"), _rates() {}

BitcoinExchange::BitcoinExchange(std::string dataBaseName) : _dataBaseName(dataBaseName) {
    _rates = readRates(_dataBaseName);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    _dataBaseName = other._dataBaseName;
    _rates.insert(other._rates.begin(), other._rates.end());
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this == &other)
        return (*this);
    _dataBaseName = other._dataBaseName;
    _rates.insert(other._rates.begin(), other._rates.end());
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

std::map<std::string, double> BitcoinExchange::getRates() const {
    return (_rates);
}

std::map<std::string, double> BitcoinExchange::readRates(std::string dataBaseName) {
    std::map<std::string, double> rates;
    double rate;
    char *end;
    std::ifstream ifs(dataBaseName.c_str());
    if (!ifs.is_open()) {
        throw std::runtime_error("could not open file for read or file does not exist.");
    }
    std::string line;
    std::getline(ifs, line);
    try {
        while (std::getline(ifs, line)) {
            std::stringstream ss(line);
            if (line.find(",") == std::string::npos)
                throw std::runtime_error("not valid delimiter in database file. Use ','.");
            int count = std::count(line.begin(), line.end(), ',');
            if (count != 1)
                throw std::runtime_error("too many delimiters in database file.");
            std::string date;
            std::getline(ss, date, ',');
            struct tm tmStruct = {};
            if (!strptime(date.c_str(), "%Y-%m-%d", &tmStruct)) {
                throw std::runtime_error("bad input => " + date + ". Format must be YYYY-MM-DD.");
            }
            if (tmStruct.tm_mday < 1 || tmStruct.tm_mday > 31) {
                throw std::runtime_error("day out of range. Day must be between 1 and 31.");
            }
            if (tmStruct.tm_mon < 0 || tmStruct.tm_mon > 12) {
                throw std::runtime_error("month out of range. Month must be between 1 and 12.");
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
    catch (std::exception &e) {
        std::cout << RED << "Error: " << RESET << e.what() << " Could not construct object."<< std::endl;
        ifs.close();
        exit(1);
    }
    return (rates);
}

std::string BitcoinExchange::checkDate(std::stringstream &ss) {
    std::string date;
    std::getline(ss, date, '|');
    date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
    struct tm tmStruct = {};
    if (!strptime(date.c_str(), "%Y-%m-%d", &tmStruct)) {
        throw std::runtime_error("bad input => " + date + ". Format must be YYYY-MM-DD.");
    }
    if (tmStruct.tm_mday < 1 || tmStruct.tm_mday > 31) {
        throw std::runtime_error("day out of range. Day must be between 1 and 31.");
    }
    if (tmStruct.tm_mon < 0 || tmStruct.tm_mon > 12) {
        throw std::runtime_error("month out of range. Month must be between 1 and 12.");
    }
    if (date.size() != 10)
        throw std::runtime_error("bad input => " + date + ". Format must be YYYY-MM-DD.");
    int year = tmStruct.tm_year + 1900; // tm_year starts from 1900
    int month = tmStruct.tm_mon + 1; // tm_mon starts from 0
    if (year < 2009 || year > 2022) {
        throw std::runtime_error("year out of range. Year must be between 2009 and 2022.");
    }
    if (year == 2022 && month > 3) {
        throw std::runtime_error("no rates later 2022-03-29.");
    }
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
    else if (value == NAN || value == INFINITY || value == -INFINITY) {
        throw std::runtime_error("not a number.");
    }
    else if (value > 1001) {
        throw std::runtime_error("too large number.");
    }
    return (value);
}

void    BitcoinExchange::printResult(std::string filename) {
    std::string date;
    double value;
        std::ifstream ifs(filename.c_str());
        if (!ifs.is_open()) {
            throw std::runtime_error("could not open file for read or file does not exist.");
        }
        std::string line;
        std::getline(ifs, line);
        while (std::getline(ifs, line)) {
            try {
            std::stringstream ss(line);
            date = checkDate(ss);
            if (line.find("|") == std::string::npos)
                throw std::runtime_error("not valid delimiter in input file. Use '|'.");
            value = checkValue(ss);
            std::map<std::string, double>::iterator it = _rates.lower_bound(date);
            if (it != _rates.begin() && it->first == date) {
                std::cout << date << " => " << value << " = " << value * it->second << std::endl;
            }
            else if (it != _rates.begin()) {
                --it;
                std::cout << date << " => " << value << " = " << value * it->second << std::endl;
            }
        }
        catch (std::exception &e) {
            std::cout << RED << "Error: " << RESET << e.what() << std::endl;
            continue;
        }
    }
    ifs.close();
}