/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:19 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/05 01:24:18 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/list.hpp"
#include "containers/vector.hpp"
#include "containers/map.hpp"
#include "containers/stack.hpp"
#include "containers/queue.hpp"
#include "../utils/bidirectionalIterator.hpp"
#include "../utils/forwardIterator.hpp"
#include <iostream>

int main()
{
    ft::List<int> myList;
    ft::Vector<int> myVector;
    ft::Map<int> myMap;
    ft::Stack<int> myStack;
    ft::Queue<int> myQueue;

    int tab[4];
    tab[0] = 1;
    tab[1] = 2;
    tab[2] = 3;
    tab[3] = 4;
    ::myBidirectionalIterator<int>it(&tab[0]);
    ::myBidirectionalIterator<int>itend(&tab[3]);
    // ::myForwardIterator<int>it(&tab[0]);
    // ::myForwardIterator<int>itend(&tab[3]);
    // ::myForwardIterator<int>itdef;
    std::cout << (it == itend) << std::endl;
    std::cout << *itend-- << std::endl;
    std::cout << *itend << std::endl;
    //it = itend;
    *itend = tab[1];
    std::cout << (tab[2] == tab[1]) << std::endl;
    tab[2] = *it;    //output = input
    std::cout << (tab[2] == tab[0]) << std::endl;

    //std::cout << *it << std::endl;
}