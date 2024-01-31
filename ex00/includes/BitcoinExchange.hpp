/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:01:09 by yuboktae          #+#    #+#             */
/*   Updated: 2024/01/31 16:39:20 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"

# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <map>

class BitcoinExchange {
    private:
        std::map<std::string, double> _rates;
        BitcoinExchange();
    public:
        BitcoinExchange(std::map<std::string, double> rates);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        
        std::map<std::string, double> getRates() const;
        void readRates(std::string filename, std::map<std::string, double> &rates);
        std::string checkDate(std::stringstream &ss);
        double checkValue(std::stringstream &ss);
        void printResult(std::string filename);
};

#endif