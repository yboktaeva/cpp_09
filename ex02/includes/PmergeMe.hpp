/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:11:46 by yuboktae          #+#    #+#             */
/*   Updated: 2024/02/02 18:43:05 by yuboktae         ###   ########.fr       */
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

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

class   PmergeMe {
    public:
        PmergeMe();
        PmergeMe(std::string input);
        PmergeMe(const PmergeMe &src);
        PmergeMe &operator=(const PmergeMe &src);
        ~PmergeMe();
        void    parseInput(std::string input);
        void    mergeSort();
    private:
        // std::vector<int> _vector;
        // std::list<int>   _list;
        // std::string     _input;
};

template <typename T> 
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); it++) {
        os << *it << " ";
    }
    return (os);
}

#endif