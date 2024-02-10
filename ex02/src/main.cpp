/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:14:38 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/10 17:55:51 by yuboktae         ###   ########.fr       */
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
    // try {
    //     PmergeMe::PmergeMeVector pmVec;
    //     if (!pmVec.getVectorFromInput(argv)) {
    //         return (1);
    //     }
    //     clock_t vecTime = 0;
    //     pmVec.printBefore();
    //     vecTime = clock();
    //     pmVec.mergeInsertionSortVector();
    //     vecTime = clock() - vecTime;
    //     pmVec.printAfter();
    //     std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector: " << (float)vecTime * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;
    // }
    // catch (std::exception &e) {
    //     std::cerr << RED << "Error: " << RESET << e.what() << std::endl;
    //     return (1);
    // }
    try {
        PmergeMe::PmergeMeList pmLst;
        if (!pmLst.getListFromInput(argv)) {
            return (1);
        }
        clock_t lstTime = 0;
        pmLst.printBefore();
        lstTime = clock();
        pmLst.mergeInsertionSortList();
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