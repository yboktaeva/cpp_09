/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:01:09 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/12 15:29:06 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# define RESET "\033[0m"
# define RED "\033[1;31m"

# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <exception>
# include <map>
# include <cmath>
# include <limits>

class BitcoinExchange {
    private:
        std::string _dataBaseName;
        std::map<std::string, double> _rates;
        BitcoinExchange(); // private default constructor (not used)
    public:
        BitcoinExchange(std::string dataBaseName);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        
        std::map<std::string, double> getRates() const;
        std::map<std::string, double> readRates(std::string dataBaseName);
        std::string checkDate(std::stringstream &ss);
        double checkValue(std::stringstream &ss);
        bool    isValidDigits(const std::string &str);
        void printResult(std::string filename);
};

#endif