/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:19 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/11 06:27:59 by lemarabe         ###   ########.fr       */
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
  //  ft::Stack<int> myStack;
  //  ft::Queue<int> myQueue;

    myList.push_back(24);
    myList.push_front(41);
    myList.push_back(23);
    myList.push_back(22);
    myList.push_front(42);
    myList.push_back(21);

    const ft::List<int> copy(myList);

    myList.pop_back();
    myList.pop_front();

    for (ft::List<int>::iterator it = myList.begin(); it != myList.end(); it++)
        std::cout << *it << "-";
    std::cout << std::endl;
    for (ft::List<int>::const_iterator it = copy.begin(); it != copy.end(); it++)
        std::cout << *it << "-";
    std::cout << std::endl;

    // int tab[4];
    // tab[0] = 1;
    // tab[1] = 2;
    // tab[2] = 3;
    // tab[3] = 4;
    // ::myBidirectionalIterator<int>it(&tab[0]);
    // ::myBidirectionalIterator<int>itend(&tab[3]);
    // // ::myForwardIterator<int>it(&tab[0]);
    // // ::myForwardIterator<int>itend(&tab[3]);
    // // ::myForwardIterator<int>itdef;
    // std::cout << (it == itend) << std::endl;
    // std::cout << *itend-- << std::endl;
    // std::cout << *itend << std::endl;
    // //it = itend;
    // *itend = tab[1];
    // std::cout << (tab[2] == tab[1]) << std::endl;
    // tab[2] = *it;    //output = input
    // std::cout << (tab[2] == tab[0]) << std::endl;

    // //std::cout << *it << std::endl;
}