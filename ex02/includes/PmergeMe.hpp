/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:11:46 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/05 19:10:29 by yuboktae         ###   ########.fr       */
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
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

template <typename T>
class   PmergeMe {
    public:
        PmergeMe(const std::vector<int> &vec) : container(vec.begin(), vec.end()) {};
        PmergeMe(const std::list<int> &lst) : container(lst.begin(), lst.end()) {};
        PmergeMe(const PmergeMe &src) : container(src.container) {};
        PmergeMe &operator=(const PmergeMe &src) {
            if (this == &src)
                return (*this);
            container = src.container;
            return (*this);
        }
        
        ~PmergeMe() {};
        
        void    sortInsidePairs(); //sorts each pair of elements
        void    mergeSortPairs();
        void    createMainChain();
        void    createPendElements();
        void    binaryInsertionSort();
        void    mergeInsertionSort();
    private:
        T   container;
        PmergeMe(); // private default constructor for cannonical form
};

template <typename It> 
void    print(It begin, It end) {
    while (begin != end) {
        std::cout << *begin << " ";
        begin++;
    }
    std::cout << std::endl;
};

template <typename ContainerType, typename ItemType>
void    pushback(ConatinerType& container, const ItemType& item) {
    container.push_back(item);
};

#endif