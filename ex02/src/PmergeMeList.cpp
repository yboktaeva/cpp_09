/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeList.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:03:23 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/12 14:46:26 by yuboktae         ###   ########.fr       */
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

PmergeMe::PmergeMeList::PmergeMeList() :  _pmList(), _pairsList(), _mainChainList(), _pendChainList(), _straggler(-1) {}

PmergeMe::PmergeMeList::PmergeMeList(const PmergeMeList &src) {
    *this = src;
}

PmergeMe::PmergeMeList &PmergeMe::PmergeMeList::operator=(const PmergeMeList &src) {
    if (this == &src)
        return (*this);
    return(*this);
}

PmergeMe::PmergeMeList::~PmergeMeList() {}

bool    PmergeMe::PmergeMeList::getListFromInput(char **argv) {
    bool success = true;
    try {
        std::list<int> tempLst;
        for (size_t i = 1; argv[i] != NULL; i++) {
            char *end;
            int num = std::strtol(argv[i], &end, 10);
            if (*end != '\0' || num < 0) {
                success = false;
                throw std::invalid_argument("out of range or not a number");
            }
            tempLst.push_back(num);
        }
        if (hasDuplicates(tempLst.begin(), tempLst.end())) {
            tempLst.clear();
            success = false;
            throw std::runtime_error("duplicates found");
        }
        else if (tempLst.size() < 2) {
            tempLst.clear();
            success = false;
            throw std::invalid_argument("not enough elements to sort");
        }
        else if (isSorted(tempLst.begin(), tempLst.end())) {
            tempLst.clear();
            success = false;
            throw std::runtime_error("already sorted");
        }
        else {
            _pmList = tempLst;
            tempLst.clear();
        }
    }
    catch (std::exception &e) {
        std::cerr << RED << "Error: " << RESET << e.what()  << std::endl;
        success = false;
    }
    return (success);
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
        merged.splice(merged.end(), lst, minIt); // move the smallest to merged
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

size_t     PmergeMe::PmergeMeList::jacobsthalNumber(size_t n) {
    if (n == 0) {
        return (0);
    }
    if (n == 1) {
        return (1);
    }
    return (jacobsthalNumber(n - 1) + 2 * jacobsthalNumber(n - 2));
}

std::list<size_t>     PmergeMe::PmergeMeList::getJacobsthalSequence(size_t n) {
    std::list<size_t> jacobsthalSeq;
    size_t  jbIndex;
    size_t i = 3;
    while ((jbIndex = this->jacobsthalNumber(i) < n)) {
        jacobsthalSeq.push_back(jacobsthalNumber(i));
        i++;
    }
    return (jacobsthalSeq);
}

int     PmergeMe::PmergeMeList::binarySearchList(std::list<int> &lst, int target) {
    std::list<int>::iterator left = lst.begin();
    std::list<int>::iterator right = lst.end();
    --right;
    while (left != right) {
        std::list<int>::iterator mid = left;
        std::advance(mid, std::distance(left, right) / 2);
        if (*mid == target) {
            return (std::distance(lst.begin(), mid));
        }
        else if (*mid < target) {
            left = ++mid;
        }
        else {
            right = mid;
        }
    }
    return (std::distance(lst.begin(), left));
}

void    PmergeMe::PmergeMeList::insertInMainChain() {
    std::list<size_t> jacobsthalSequence = getJacobsthalSequence(_pendChainList.size());
    for (std::list<size_t>::iterator it = jacobsthalSequence.begin(); it != jacobsthalSequence.end(); ++it) {
        size_t index = *it;
        if (index > _pendChainList.size())
            index = _pendChainList.size() - 1;
        std::list<int>::iterator pendIt = _pendChainList.begin();
        std::list<int>::iterator mainIt = _mainChainList.begin();
        std::advance(pendIt, index);
        int insertIndex = binarySearchList(_mainChainList, *pendIt);
        std::advance(mainIt, insertIndex);
        _mainChainList.insert(mainIt, *pendIt);
        _pendChainList.erase(pendIt);
    }
    for (std::list<int>::iterator pendIt = _pendChainList.begin(); pendIt != _pendChainList.end(); ++pendIt) {
        while (_pendChainList.size() != 0) {
            std::list<int>::iterator insertPos = _mainChainList.begin();
            std::advance(insertPos, std::distance(_mainChainList.begin(), std::upper_bound(_mainChainList.begin(), _mainChainList.end(), *pendIt)));
            _mainChainList.insert(insertPos, *pendIt);
            pendIt = _pendChainList.erase(pendIt);
        }
    }
}

void    PmergeMe::PmergeMeList::mergeInsertionSortList() {
    if (_pmList.size() % 2 != 0) {
        _straggler = _pmList.back();
        _pmList.pop_back();
    }
    makePairsList();
    if (_pairsList.size() == 1 && _straggler == -1) {
        _mainChainList.push_back(_pairsList.front().first);
        _mainChainList.push_back(_pairsList.front().second);
        return;
    }
    else {
        mergeSortPairs(_pairsList, _pairsList.begin(), _pairsList.end());
        getMainAndPendChain();
        insertInMainChain();
    }
}

void    PmergeMe::PmergeMeList::printBefore() {
    std::cout << CYAN << "List Before:  " << RESET;
    print(_pmList.begin(), _pmList.end());
}

void    PmergeMe::PmergeMeList::printAfter() {
    std::cout << GREEN << "List After:  " << RESET;
    print(_mainChainList.begin(), _mainChainList.end());
}