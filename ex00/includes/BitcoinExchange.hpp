/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:01:09 by yuboktae          #+#    #+#             */
/*   Updated: 2024/01/09 18:04:49 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"

# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <map>

class BitcoinExchange {
    private:
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        void readRates(std::string filename, std::map<std::string, float> &rates);
        std::map<std::string, float> getInput(std::string filename);
        void checkInput(std::map<std::string, float> &map);
};

// class Input {
//     private:
//     public:
//         Input();
//         Input(const Input &other);
//         Input &operator=(const Input &other);
//         ~Input();
//         std::map<std::string, float> getInput(std::string filename);
//         void checkInput(std::map<std::string, float> &map);
// };

#endif