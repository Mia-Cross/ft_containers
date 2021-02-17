/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:19 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/17 03:55:30 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/list.hpp"
#include "containers/vector.hpp"
#include "containers/map.hpp"
#include "containers/stack.hpp"
#include "containers/queue.hpp"
#include "../utils/listIterator.hpp"
#include <iostream>

int main()
{
    ft::List<int> myList;
    ft::Vector<int> myVector;
    ft::Map<int> myMap;
  //  ft::Stack<int> myStack;
  //  ft::Queue<int> myQueue;

    std::cout << "   *  _ ___\n";
    std::cout << "|  | |_  | \n";
    std::cout << "|_ |  _| | \n";

    std::cout << "EMPTY : " << myList.empty() << std::endl;
    std::cout << "Filling my List with {  1, -2,  3,  4, -5,  6  }\n";
    myList.push_back(3);   // CONTENT = {          3              }
    myList.push_front(-2); // CONTENT = {     -2,  3              }
    myList.push_back(4);   // CONTENT = {     -2,  3,  4          }
    myList.push_back(-5);  // CONTENT = {     -2,  3,  4, -5      }
    myList.push_front(1);  // CONTENT = {  1, -2,  3,  4, -5      }
    myList.push_back(6);   // CONTENT = {  1, -2,  3,  4, -5,  6  }
    
    std::cout << "EMPTY :\t" << myList.empty() << std::endl;
    std::cout << "SIZE :\t" << myList.size() << std::endl;
    std::cout << "MAX_SIZE :\t" << myList.max_size() << std::endl;
    std::cout << "FRONT :\t" << myList.front() << std::endl;
    std::cout << "BACK :\t" << myList.back() << std::endl;

    std::cout << "Making a const copy of my List at this stage...\n";
    const ft::List<int> copy(myList);
    std::cout << "FRONT (const) :\t" << copy.front() << std::endl;
    std::cout << "BACK (const) :\t" << copy.back() << std::endl;

    std::cout << "Popping front and back of my List...\n";
    myList.pop_back();      // CONTENT = {  1, -2,  3,  4, -5, __  }
    myList.pop_front();     // CONTENT = {  __ -2,  3,  4, -5, __  }

    std::cout << "Displaying my List with ITERATION :\t\t";
    for (ft::List<int>::iterator it = myList.begin(); it != myList.end(); it++)
        std::cout << "[" << *it << "]";
    std::cout << ".\nDisplaying my List with REVERSE ITERATION :\t";
    for (ft::List<int>::reverse_iterator rit = myList.rbegin(); rit != myList.rend(); rit++)
        std::cout << "[" << *rit << "]";
    std::cout << ".\nDisplaying Copy with CONST ITERATION :\t\t";
    for (ft::List<int>::const_iterator it = copy.begin(); it != copy.end(); it++)
        std::cout << "[" << *it << "]";
    std::cout << ".\nDisplaying Copy with CONST REVERSE ITERATION :\t";
    for (ft::List<int>::const_reverse_iterator rit = copy.rbegin(); rit != copy.rend(); rit++)
        std::cout << "[" << *rit << "]";





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