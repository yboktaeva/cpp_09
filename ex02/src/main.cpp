/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:14:38 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/08 19:24:33 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    try {
        if (argc < 2) {
            throw std::invalid_argument("usage: ./PmergeMe 2 1 5 4 3 etc...");
        }
    } catch (std::exception &e) {
        std::cerr << RED << "Error: " << RESET << e.what() << std::endl;
        return (1);
    }
    
    try {
        PmergeMe::PmergeMeVector pmVec;
        clock_t vecTime = 0;
        vecTime = clock();
        pmVec.mergeInsertionSortVector(argv);
        pmVec.printBefore();
        vecTime = clock() - vecTime;
        pmVec.printAfter();
        std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector: " << (float)vecTime * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;
        PmergeMe::PmergeMeList pmLst;
        clock_t lstTime = 0;
        lstTime = clock();
        pmLst.mergeInsertionSortList(argv);
        pmLst.printBefore();
        lstTime = clock() - lstTime;
        pmLst.printAfter();
        std::cout << "Time to process a range of " << argc - 1 << " elements with std::list: " << (float)lstTime * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << RED << "Error: " << RESET << e.what() << std::endl;
        return (1);
    }
    return (0);
}