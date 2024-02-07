/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:14:38 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/07 16:57:59 by yuboktae         ###   ########.fr       */
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
        clock_t vecTime = 0;
        clock_t lstTime = 0;
        PmergeMe::PmergeMeVector pmVec;
        //PmergeMe::PmergeMeList pmLst;
        vecTime = clock();
        pmVec.mergeInsertionSortVector(argv);
        vecTime = clock() - vecTime;
        //lstTime = clock();
        //pmLst.mergeInsertionSortList(argv);
        //lstTime = clock() - lstTime;
        std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector: " << (float)vecTime * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;
        std::cout << "Time to process a range of " << argc - 1 << " elements with std::list: " << (float)lstTime / CLOCKS_PER_SEC << " us" << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << RED << "Error: " << RESET << e.what() << std::endl;
        return (1);
    }
    return (0);
}