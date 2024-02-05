/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:14:38 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/05 19:11:47 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    try {
        if (argc < 2) {
            throw std::invalid_argument("usage: ./PmergeMe 2 1 5 4 3 etc...");
        }
    } catch (std::exception &e) {
        std::cerr << RED << e.what() << RESET << std::endl;
        return (1);
    }
    std::list<int> lst;
    std::vector<int> vec;
    try {
        for (size_t i = 1; i < argc; i++) {
            bool is_digit = true;
            for (size_t j = 0; argv[i][j] != '\0'; j++) {
                if (!isdigit(argv[i][j])) {
                    is_digit = false;
                    break;
                }
            }
            if (!is_digit) {
                throw std::invalid_argument("argument is not a number");
            }
            int num = std::atoi(argv[i]);
            if (num < 0) {
                throw std::invalid_argument("only positive integers are allowed");
            } 
            if (num > UINT_MAX) {
                throw std::out_of_range("number is too big");
            }
            vec.push_back(num);
            lst.push_back(num);
        }
    } catch (std::exception &e) {
        std::cerr << RED << e.what() << RESET << std::endl;
        return (1);
    }
    PmergeMe<int> pm(vec);
    PmergeMe<int> pm2(lst);
    print(vec.begin(), vec.end());
    print(lst.begin(), lst.end());
    // std::time_t start_time;
    // start_time = time.time();
    //print ("Sort took ", time.time() - start_time, " seconds.")
    return (0);
}