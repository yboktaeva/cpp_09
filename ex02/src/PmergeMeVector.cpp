/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVector.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:02:02 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/12 14:47:56 by yuboktae         ###   ########.fr       */
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


PmergeMe::PmergeMeVector::PmergeMeVector() : _pmVector(), _pairsVector(), _mainChainVector(), _pendChainVector(), _straggler(-1) {}

PmergeMe::PmergeMeVector::PmergeMeVector(const PmergeMeVector &src) {
    *this = src;
}

PmergeMe::PmergeMeVector &PmergeMe::PmergeMeVector::operator=(const PmergeMeVector &src) {
    if (this == &src)
        return (*this);
    return (*this);
}

PmergeMe::PmergeMeVector::~PmergeMeVector() {}

bool    PmergeMe::PmergeMeVector::getVectorFromInput(char **argv) {
    bool success = true;
    try {
        std::vector<int> tempVec;
        for (size_t i = 1; argv[i] != NULL; i++) {
            char *end;
            int num = std::strtol(argv[i], &end, 10);
            if (*end != '\0' || num < 0) {
                success = false;
                throw std::invalid_argument("out of range or not a number");
            }
            tempVec.push_back(num);
        }
        if (hasDuplicates(tempVec.begin(), tempVec.end())) {
            tempVec.clear();
            success = false;
            throw std::runtime_error("duplicates found");
        }
        else if (tempVec.size() < 2) {
            tempVec.clear();
            success = false;
            throw std::invalid_argument("not enough elements to sort");
        }
        else if (isSorted(tempVec.begin(), tempVec.end())) {
            tempVec.clear();
            success = false;
            throw std::runtime_error("already sorted");
        }
        else {
            _pmVector = tempVec;
            tempVec.clear();
        }
    }
    catch (std::exception &e) {
        std::cerr << RED << "Error: " << RESET << e.what() << std::endl;
        success = false;
    }
    return (success);
}

void    PmergeMe::PmergeMeVector::makePairsVector() {
    size_t size = _pmVector.size() / 2;
    size_t i = 0;
    while (size != 0) {
        _pairsVector.push_back(std::make_pair(_pmVector[i], _pmVector[i + 1]));
        i += 2;
        size--;
    }
    for (size_t i = 0; i < _pairsVector.size(); i++)
        if (_pairsVector[i].first > _pairsVector[i].second) {
            std::swap(_pairsVector[i].first, _pairsVector[i].second); // swap if first is bigger than second
        }
}

void    PmergeMe::PmergeMeVector::mergeSortPairs(std::vector<std::pair<int, int> >& vec, int start, int end) {
    if (start >= end) { // if the array is empty or has only one element, return
        return;
    }
    int mid = start + (end - start) / 2; // find the middle index
    mergeSortPairs(vec, start, mid); // sort the left half
    mergeSortPairs(vec, mid + 1, end); // sort the right half
    
    std::vector<std::pair<int, int> > merged;
    int left = start;
    int right = mid + 1; 
    while (left <= mid && right <= end) { // merge the two halves
        if (vec[left].second < vec[right].second) { // if left is smaller than right, push left
            merged.push_back(vec[left]);
            left++;
        } 
        else { // if right is smaller than left, push right
            merged.push_back(vec[right]);
            right++;
        }
    }
    while (left <= mid) { // if there are any remaining elements in the left half, push them
        merged.push_back(vec[left]);
        left++;
    }
    while (right <= end) { // if there are any remaining elements in the right half, push them
        merged.push_back(vec[right]);
        right++;
    }
    std::copy(merged.begin(), merged.end(), vec.begin() + start); // copy the merged vector to the original vector
}

void    PmergeMe::PmergeMeVector::getMainAndPendChain() {
    for (size_t i = 0; i < _pairsVector.size(); i++) {
        _pendChainVector.push_back(_pairsVector[i].first);
        _mainChainVector.push_back(_pairsVector[i].second);
    }
    if (_straggler != -1) {
        _pendChainVector.push_back(_straggler);
    }
}

int    PmergeMe::PmergeMeVector::binarySearchVector(std::vector<int>& vec, int target) {
    int left = 0;
    int right = vec.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (vec[mid] == target) {
            return (mid);
        }
        if (vec[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return (left);
}

std::vector<size_t>     PmergeMe::PmergeMeVector::getJacobsthalSequence(size_t n) {
    std::vector<size_t> jacobsthalSeq(n);
    jacobsthalSeq[0] = 1;
    jacobsthalSeq[1] = 3;
    for (size_t i = 2; i < n; i++) {
        jacobsthalSeq[i] = jacobsthalSeq[i - 1] + 2 * jacobsthalSeq[i - 2];
    }
    return (jacobsthalSeq);
}

void    PmergeMe::PmergeMeVector::insertInMainChain() {
    std::vector<size_t> jacobsthalSequence = getJacobsthalSequence(_pendChainVector.size());
    for (size_t i = 0; i < jacobsthalSequence.size(); ++i) {
        size_t index = jacobsthalSequence[i];
        if (index > _pendChainVector.size()) {
            index = _pendChainVector.size() - 1;
        }
        int target = _pendChainVector[index];
        int insertIndex = binarySearchVector(_mainChainVector, target);
        _mainChainVector.insert(_mainChainVector.begin() + insertIndex, target);
        _pendChainVector.erase(_pendChainVector.begin() + index);
    }
}

void    PmergeMe::PmergeMeVector::mergeInsertionSortVector() {
    if (_pmVector.size() % 2 != 0) {
        _straggler = _pmVector.back();
        _pmVector.pop_back();
    }
    makePairsVector();
    if (_pairsVector.size() == 1 && _straggler == -1) {
        _mainChainVector.push_back(_pairsVector.front().first);
        _mainChainVector.push_back(_pairsVector.front().second);
    }
    else {
        mergeSortPairs(_pairsVector, 0, _pairsVector.size() - 1);
        getMainAndPendChain();
        insertInMainChain();
    }
}

void    PmergeMe::PmergeMeVector::printBefore() {
    std::cout << CYAN << "Vector Before:  " << RESET;
    print(_pmVector.begin(), _pmVector.end());
}

void    PmergeMe::PmergeMeVector::printAfter() {
    std::cout << GREEN << "Vector After:  " << RESET;
    print(_mainChainVector.begin(), _mainChainVector.end());
}