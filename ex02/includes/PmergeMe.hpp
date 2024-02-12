/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:11:46 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/12 14:43:13 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <list>
# include <vector>
# include <ctime>
# include <exception>
# include <algorithm>
# include <string>
# include <cstdlib>
# include <climits>

# define RED "\033[1;31m"
# define CYAN "\033[1;36m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

class   PmergeMe {
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &src);
        PmergeMe &operator=(const PmergeMe &src);
        ~PmergeMe();
        
        class PmergeMeVector {
            public:
                PmergeMeVector();
                PmergeMeVector(const PmergeMeVector &src);
                PmergeMeVector &operator=(const PmergeMeVector &src);
                ~PmergeMeVector();
                
                bool    getVectorFromInput(char **argv);
                void    mergeInsertionSortVector();
                void    printBefore();
                void    printAfter();
            private:
                std::vector<int>    _pmVector;
                std::vector<std::pair<int, int> >    _pairsVector;
                std::vector<int>    _mainChainVector;
                std::vector<int>    _pendChainVector;
                int     _straggler;
                
                void    makePairsVector();
                void    mergeSortPairs(std::vector<std::pair<int, int> >& vec, int start, int end); //recursive
                std::vector<size_t>     getJacobsthalSequence(size_t n);
                void    getMainAndPendChain();
                int     binarySearchVector(std::vector<int>& vec, int target);
                void    insertInMainChain();
        };
        
        class PmergeMeList {
            public:
                PmergeMeList();
                PmergeMeList(const PmergeMeList &src);
                PmergeMeList &operator=(const PmergeMeList &src);
                ~PmergeMeList();

                bool    getListFromInput(char **argv);
                void    mergeInsertionSortList();
                void    printBefore();
                void    printAfter();
                size_t  jacobsthalNumber(size_t n);
            private:
                std::list<int>    _pmList;
                std::list<std::pair<int, int> >    _pairsList;
                std::list<int>    _mainChainList;
                std::list<int>    _pendChainList;
                int     _straggler;
                
                void    makePairsList();
                void    mergeSortPairs(std::list<std::pair<int, int> >& lst, std::list<std::pair<int, int> >::iterator begin,
                    std::list<std::pair<int, int> >::iterator end); //recursive
                void    getMainAndPendChain();
                std::list<size_t>     getJacobsthalSequence(size_t n);
                int     binarySearchList(std::list<int>& lst, int target);
                void    insertInMainChain();
        };
};

template <typename It> 
void    print(It begin, It end) {
    while (begin != end) {
        std::cout << *begin << " ";
        begin++;
    }
    std::cout << std::endl;
};

template <typename It>
bool    hasDuplicates(It begin, It end) {
    while (begin != end) {
        It it = begin;
        while (++it != end) {
            if (*begin == *it) {
                return (true);
            }
        }
        begin++;
    }
    return (false);
};

template <typename It>
bool    isSorted(It begin, It end) {
    It it = begin;
    while (++it != end) {
        if (*begin > *it) {
            return (false);
        }
        begin++;
    }
    return (true);
};

#endif