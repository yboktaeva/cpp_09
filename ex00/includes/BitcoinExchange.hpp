/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:01:09 by yuboktae          #+#    #+#             */
/*   Updated: 2024/01/10 19:09:04 by yuboktae         ###   ########.fr       */
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
        
        bool checkDate(const std::string &date);
        void readRates(std::string filename, std::map<std::string, double> &rates);
        std::map<std::string, float> getInput(std::string filename);
        void checkInput(std::map<std::string, float> &map);
};

#endif