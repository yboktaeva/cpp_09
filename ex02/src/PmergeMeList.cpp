/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeList.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:03:23 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/07 12:33:31 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*Determine if the array is even or odd numbered in length. If odd, remove the last number,
designate it as a ‘straggler’ and insert it later into the sorted array. Arbitrarily divide
the sequence to sort into pairs of two values.
Sort the pairs bitwise, so the order is always [less, greater].
Sort the sequence recursively by the value of it’s largest pair.
Create a new sequence ‘Main chain’, by pulling out the [highest] value of each pair and
inserting it into ‘Main chain’.
The remaining values form a ‘Pend chain’ array.
Based on the length of ‘Pend chain’, build the optimal insertion sequence using
relevant Jacobsthal numbers. Loop through the elements in ‘Pend chain’, and using the insertion
sequence built in the previous step, use binary search to insert each ‘pend’ element into ‘Main’.
If a ‘straggler’ was found, do a leftover loop and insertion to complete the list.*/

PmergeMe::PmergeMeList::PmergeMeList() : _straggler(-1) {}

PmergeMe::PmergeMeList::PmergeMeList(const PmergeMeList &src) {
    *this = src;
}

PmergeMe::PmergeMeList &PmergeMe::PmergeMeList::operator=(const PmergeMeList &src) {
    if (this == &src)
        return (*this);
    return(*this);
}

PmergeMe::PmergeMeList::~PmergeMeList() {}

void    PmergeMe::PmergeMeList::getListFromInput(char **argv) {
    try {
        for (size_t i = 1; argv[i] != NULL; i++) {
            char *end;
            int num = std::strtol(argv[i], &end, 10);
            if (*end != '\0' || num < 0) {
                throw std::invalid_argument("out of range or not a number");
            }
            _pmList.push_back(num);
        }
    }
    catch (std::exception &e) {
        std::cerr << RED << e.what() << RESET << std::endl;
        exit(1);
    }
}

void    PmergeMe::PmergeMeList::makePairsList() {
    std::list<int>::iterator it = _pmList.begin();
    while (it != _pmList.end()) {
        std::pair<int, int> pair = std::make_pair(*it, *(++it));
        _pairsList.push_back(pair);
        it++;
    }
    for (size_t i = 0; i < _pairsList.size(); i++) {
        std::list<std::pair<int, int> >::iterator it = _pairsList.begin();
        std::advance(it, i);
        if (it->first > it->second) {
            std::swap(it->first, it->second); // swap if first is bigger than second
        }
    }
}

void    PmergeMe::PmergeMeList::mergeSortPairs(std::list<std::pair<int, int> >& lst, std::list<std::pair<int, int> >::iterator begin,
    std::list<std::pair<int, int> >::iterator end) {
    if (std::distance(begin, end) <= 1) {
        return;
    }
    std::list<std::pair<int, int> >::iterator mid = begin;
    std::advance(mid, std::distance(begin, end) / 2);
    mergeSortPairs(lst, begin, mid);
    mergeSortPairs(lst, mid, end);

    std::list<std::pair<int, int> > merged;
    while (!lst.empty()) {
        std::list<std::pair<int, int> >::iterator minIt = lst.begin();
        for (std::list<std::pair<int, int> >::iterator it = lst.begin(); it != lst.end(); ++it) {
            if (minIt->second > it->second) {
                minIt = it;
            }
        }
        merged.splice(merged.end(), lst, minIt);
    }
    lst.swap(merged);
}

void    PmergeMe::PmergeMeList::getMainAndPendChain() {
    std::list<std::pair<int, int> >::iterator it = _pairsList.begin();
    while (it != _pairsList.end()) {
        _pendChainList.push_back(it->first);
        _mainChainList.push_back(it->second);
        it++;
    }
    if (_straggler != -1) {
        _pendChainList.push_back(_straggler);
    }
}

int     PmergeMe::PmergeMeList::getJacobsthalNumber(int n) {
    if (n == 0) {
        return (0);
    }
    if (n == 1) {
        return (1);
    }
    return (getJacobsthalNumber(n - 1) + 2 * getJacobsthalNumber(n - 2));
}

int     PmergeMe::PmergeMeList::binarySearchList(std::list<int> &lst, int target) {
    std::list<int>::iterator it = lst.begin();
    int start = 0;
    int end = lst.size() - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        std::advance(it, mid);
        if (*it == target) {
            return (mid);
        }
        if (*it < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return (start);
}

void    PmergeMe::PmergeMeList::mergeInsertionSortList(char **argv) {
    getListFromInput(argv);
    if (_pmList.size() < 2)
        return;
    if (_pmList.size() % 2 != 0) {
        _straggler = _pmList.back();
        _pmList.pop_back();
    }
    makePairsList();
    mergeSortPairs(_pairsList, _pairsList.begin(), _pairsList.end());
    getMainAndPendChain();
    // print(_mainChainList.begin(), _mainChainList.end());
    // std::cout << "=========" << std::endl;
    // print(_pendChainList.begin(), _pendChainList.end());
}