/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:11:46 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/08 18:38:46 by yuboktae         ###   ########.fr       */
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
                
                void    getVectorFromInput(char **argv);
                void    mergeInsertionSortVector(char **argv);
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
                std::vector<int>     getJacobsthalSequence(int n);
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

                void    getListFromInput(char **argv);
                void    mergeInsertionSortList(char **argv);
                void    printBefore();
                void    printAfter();
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
                int     jacobsthalNumber(int n);
                std::list<int>     getJacobsthalSequence(int n);
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

#endif