/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVector.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:02:02 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/07 17:13:56 by yuboktae         ###   ########.fr       */
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


PmergeMe::PmergeMeVector::PmergeMeVector() : _straggler(-1) {}

PmergeMe::PmergeMeVector::PmergeMeVector(const PmergeMeVector &src) {
    *this = src;
}

PmergeMe::PmergeMeVector &PmergeMe::PmergeMeVector::operator=(const PmergeMeVector &src) {
    if (this == &src)
        return (*this);
    return (*this);
}

PmergeMe::PmergeMeVector::~PmergeMeVector() {}

void    PmergeMe::PmergeMeVector::getVectorFromInput(char **argv) {
    try {
        for (size_t i = 1; argv[i] != NULL; i++) {
            char *end;
            int num = std::strtol(argv[i], &end, 10);
            if (*end != '\0' || num < 0) {
                throw std::invalid_argument("out of range or not a number");
            } 
            _pmVector.push_back(num);
        }
    }
    catch (std::exception &e) {
        std::cerr << RED << "Error: " << RESET << e.what() << std::endl;
        exit(1);
    }
}

void    PmergeMe::PmergeMeVector::makePairsVector() {
    int size = _pmVector.size() / 2;
    size_t i = 0;
    while (size != 0) {
        _pairsVector.push_back(std::make_pair(_pmVector[i], _pmVector[i + 1]));
        i += 2;
        size--;
    }
    for (size_t i = 0; i < _pairsVector.size(); i++) {
        if (_pairsVector[i].first > _pairsVector[i].second) {
            std::swap(_pairsVector[i].first, _pairsVector[i].second); // swap if first is bigger than second
        }
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

std::vector<int>     PmergeMe::PmergeMeVector::getJacobsthalSequence(int n) {
    std::vector<int> jacobsthalSeq(n + 1);
    jacobsthalSeq[0] = 0;
    jacobsthalSeq[1] = 1;
    for (int i = 3; i <= n; i++) {
        jacobsthalSeq[i] = jacobsthalSeq[i - 1] + 2 * jacobsthalSeq[i - 2];
    }
    return (jacobsthalSeq);
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

void    PmergeMe::PmergeMeVector::insertInMainChain() {
    std::vector<int> jacobsthalSequence = getJacobsthalSequence(_pendChainVector.size());
    std::cout << "Jacobsthal Sequence: ";
    print(jacobsthalSequence.begin(), jacobsthalSequence.end());
    for (size_t i = 0; i < jacobsthalSequence.size(); ++i) {
        size_t index = jacobsthalSequence[i];
        //std::cout << "Index: " << index << std::endl;
        if (index < _pendChainVector.size()) {
            int target = _pendChainVector[index];
            int insertIndex = binarySearchVector(_mainChainVector, target);
            _mainChainVector.insert(_mainChainVector.begin() + insertIndex, target);
            //std::cout << "Inserting " << target << " at insertIndex " << insertIndex << std::endl;
            _pendChainVector.erase(_pendChainVector.begin() + index);
        }
    }
}

void    PmergeMe::PmergeMeVector::mergeInsertionSortVector(char **argv) {
    getVectorFromInput(argv);
    if (_pmVector.size() < 2) {
        throw std::invalid_argument("Not enough elements to sort");
    }
    // std::cout << "Before:  ";
    // print(_pmVector.begin(), _pmVector.end());
    if (_pmVector.size() % 2 != 0) {
        _straggler = _pmVector.back();
        _pmVector.pop_back();
    }
    makePairsVector();
    mergeSortPairs(_pairsVector, 0, _pairsVector.size() - 1);
    getMainAndPendChain();
    //std::cout << "=========" << std::endl;
    //std::cout << "Main:  ";
    //print(_mainChainVector.begin(), _mainChainVector.end());
    //std::cout << "Pending:  ";
    //print(_pendChainVector.begin(), _pendChainVector.end());
    insertInMainChain();
    //std::cout << "=========" << std::endl;
    std::cout << "After:  ";
    print(_mainChainVector.begin(), _mainChainVector.end());
}