/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:14:38 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/06 16:27:42 by yuboktae         ###   ########.fr       */
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
    PmergeMe::PmergeMeVector pmVec;
    PmergeMe::PmergeMeList pmLst;
    pmVec.mergeInsertionSortVector(argv);
    pmLst.mergeInsertionSortList(argv);
    // std::time_t start_time;
    // start_time = time.time();
    //print ("Sort took ", time.time() - start_time, " seconds.")
    return (0);
}