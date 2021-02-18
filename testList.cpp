/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testList.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:19 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/18 05:18:47 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/list.hpp"
#include "../utils/myIterator.hpp"
#include <iostream>

void testList()
{
    ft::List<int> myList;

    std::cout << "   *  _ ___\n";
    std::cout << "|  | |_  | \n";
    std::cout << "|_ |  _| | \n\n";

    std::cout << "EMPTY : " << myList.empty() << std::endl;
    std::cout << myList;
    std::cout << "Filling my List\n";
    myList.push_front(-2); // CONTENT = {     -2,  3              }
   std::cout << myList;
    std::cout << "mep" << std::endl;
    myList.push_front(1);  // CONTENT = {  1, -2,  3,  4, -5      }
    std::cout << "mep" << std::endl;
    myList.push_back(3);   // CONTENT = {          3              }
    std::cout << "yo" << std::endl;
    std::cout << myList.size() << std::endl;
    std::cout << myList;
    std::cout << "yo";
    myList.push_back(-5);  // CONTENT = {     -2,  3,  4, -5      }
    std::cout << myList;
    myList.push_back(4);   // CONTENT = {     -2,  3,  4          }
    std::cout << myList;
    std::cout << myList;
    myList.push_back(6);   // CONTENT = {  1, -2,  3,  4, -5,  6  }
    std::cout << myList;
    std::cout << "Making a const copy of my List...\n";
    const ft::List<int> copy(myList);
    std::cout << copy;

    
    // ----- CAPACITY ----- //
    
    std::cout << "EMPTY :\t" << myList.empty() << std::endl;
    std::cout << "SIZE :\t" << myList.size() << std::endl;
    std::cout << "MAX_SIZE :\t" << myList.max_size() << std::endl;

    // ----- ELEMENT ACCESS ----- //

    std::cout << "FRONT :\t" << myList.front() << std::endl;
    std::cout << "BACK :\t" << myList.back() << std::endl;
   std::cout << "FRONT (copy) :\t" << copy.front() << std::endl;
   std::cout << "BACK (copy) :\t" << copy.back() << std::endl;

    // ----- MODIFIERS ----- //

    std::cout << "Assigning 42 to 4th position...\n";
    myList.assign(4, 42);
    //copy.assign(4, 42);      //can't assign to const list
    //assign(iterator first, iterator last)

    std::cout << "Popping front and back...\n";
    myList.pop_back();      // CONTENT = {  1, -2,  3,  4, -5, __  }
    myList.pop_front();     // CONTENT = {  __ -2,  3,  4, -5, __  }

    // ----- ITERATORS ----- //

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


    // ----- OPERATIONS ----- //


}