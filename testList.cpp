/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testList.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:19 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/22 06:45:14 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/list.hpp"
#include "../utils/myIterator.hpp"
#include <iostream>

void testList()
{
    std::cout << "Creating List A\n";
    ft::List<int> listA;

    std::cout << "   *  _ ___\n";
    std::cout << "|  | |_  | \n";
    std::cout << "|_ |  _| | \n\n";

    std::cout << "EMPTY : " << listA.empty() << std::endl;
    std::cout << listA;
    std::cout << "Filling List A\n";
    listA.push_front(-2); // CONTENT = {     -2,  3              }
    std::cout << listA;
    listA.push_back(3);   // CONTENT = {          3              }
    std::cout << listA;
    listA.push_back(4);   // CONTENT = {     -2,  3,  4          }
    std::cout << listA;
    listA.push_back(-5);  // CONTENT = {     -2,  3,  4, -5      }
    std::cout << listA;
    listA.push_front(1);  // CONTENT = {  1, -2,  3,  4, -5      }
    std::cout << listA;
    listA.push_back(6);   // CONTENT = {  1, -2,  3,  4, -5,  6  }
    std::cout << listA;
    std::cout << "Creating List C, a const copy List A...\n";
    const ft::List<int> listC(listA);
    std::cout << listC;
    // std::cout << "Making a modifiable copy of my List...\n";
    // ft::List<int> copy(listA);

    // ----- ITERATORS ----- //

    std::cout << "Displaying List A with ITERATION :\t\t";
    for (ft::List<int>::iterator it = listA.begin(); it != listA.end(); it++)
        std::cout << "[" << *it << "]";
    std::cout << "\nDisplaying List A with REVERSE ITERATION :\t";
    for (ft::List<int>::reverse_iterator rit = listA.rbegin(); rit != listA.rend(); rit++)
        std::cout << "[" << *rit << "]";
    std::cout << "\nDisplaying List C with CONST ITERATION :\t\t";
    for (ft::List<int>::const_iterator it = listC.begin(); it != listC.end(); it++)
        std::cout << "[" << *it << "]";
    std::cout << "\nDisplaying List C with CONST REVERSE ITERATION :\t";
    for (ft::List<int>::const_reverse_iterator rit = listC.rbegin(); rit != listC.rend(); rit++)
        std::cout << "[" << *rit << "]";
    std::cout << std::endl;
    
    // ----- CAPACITY ----- //
    
    std::cout << "EMPTY :\t" << listA.empty() << std::endl;
    std::cout << "SIZE :\t" << listA.size() << std::endl;
    std::cout << "MAX_SIZE :\t" << listA.max_size() << std::endl;

    // ----- ELEMENT ACCESS ----- //

    std::cout << "FRONT :\t" << listA.front() << std::endl;
    std::cout << "BACK :\t" << listA.back() << std::endl;
   std::cout << "FRONT (List C) :\t" << listC.front() << std::endl;
   std::cout << "BACK (List C) :\t" << listC.back() << std::endl;

    // ----- MODIFIERS ----- //

    std::cout << "List A : Assigning 42 with new size 3 (already assigned)\n";
    listA.assign(3, 42);
    std::cout << listA;
    std::cout << "List A : Assigning 42 with new size 10\n";
    listA.assign(10, 42);
    std::cout << listA;
    //listC.assign(10, 42);      //can't assign to const list
    std::cout << "Creating an empty list B and assigning with iterators\n";
    ft::List<int> listB;
    listB.assign(listC.begin(), listC.end());
    std::cout << listB;

    std::cout << "List A : Popping front and back...\n";
    listA.pop_back();      // CONTENT = {  1, -2,  3,  4, -5, __  }
    std::cout << listA;
    listA.pop_front();     // CONTENT = {  __ -2,  3,  4, -5, __  }
    std::cout << listA;

    ft::List<int>::iterator it = listA.begin(); it++; it++; it++; it++; it++;
    std::cout << "List A : insert 667 to 6th place\tReturn : " << *(listA.insert(it, 667));
    std::cout << listA;
    std::cout << "List A : insert 3 * 7 to 6th place\n";
    listA.insert(it, 3, 7);
    it++; it++;
    std::cout << listA << "List A : insert iterators to ?th place\n";
    listA.insert(it, listC.rbegin(), listC.rend());
    std::cout << listA;

    std::cout << "Before SWAP :\tlist A" << listA << "\t\tlist B" << listB;
    //listA.swap(listB);
    std::cout << "After SWAP : list A" << listA << " list B" << listB;
        // ----- OPERATIONS ----- //


}