/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:14:38 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/02 18:43:51 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    try {
        if (argc < 2) {
            throw std::invalid_argument("usage: ./PmergeMe 2 1 5 4 3");
        }
    } catch (std::exception &e) {
        std::cerr << RED << e.what() << RESET << std::endl;
        return (1);
    }
    for (int i = 1; i < argc; i++) {
        std::cout << "Before: " << argv[i] << " "; //print pour test apres utiliser template ostream
    }
    PmergeMe pm();
    // std::time_t start_time;
    // start_time = time.time();
    //print ("Sort took ", time.time() - start_time, " seconds.")
    return (0);
}