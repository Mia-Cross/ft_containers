/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testList.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:19 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/04 04:46:31 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/list.hpp"
#include "../utils/myIterator.hpp"
#include <iostream>

bool isEven(int x) { return (x % 2 ? false : true); }
bool isDigit(int x) { return (x < 10 && x > -1 ? true : false); }

void testList()
{
    std::cout << "   *  _ ___\n";
    std::cout << "|  | |_  | \n";
    std::cout << "|_ |  _| | \n\n";

    std::cout << "Creating List A\n";
    ft::List<int> listA;
    std::cout << listA;

    std::cout << "\nEMPTY : " << listA.empty() << std::endl;
    std::cout << "\nFilling List A :\n";
    listA.push_back(3);   // CONTENT = {          3              }
    std::cout << listA;
    listA.push_front(-2); // CONTENT = {     -2,  3              }
    std::cout << listA;
    listA.push_back(4);   // CONTENT = {     -2,  3,  4          }
    std::cout << listA;
    listA.push_back(-5);  // CONTENT = {     -2,  3,  4, -5      }
    std::cout << listA;
    listA.push_front(1);  // CONTENT = {  1, -2,  3,  4, -5      }
    std::cout << listA;
    listA.push_back(6);   // CONTENT = {  1, -2,  3,  4, -5,  6  }
    std::cout << listA;
    std::cout << "\nCreating List C, a const copy List A...\n";
    const ft::List<int> listC(listA);
    std::cout << listC;
    std::cout << "Creating empty Lists B & D... (for later)\n";
    ft::List<int> listB;
    ft::List<int> listD;

    std::cout << "\n// ----- ITERATORS ----- //\n\n";

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
    
    std::cout << "\n// ----- CAPACITY ----- //\n\n";
    
    std::cout << "EMPTY :\t" << listA.empty() << std::endl;
    std::cout << "SIZE :\t" << listA.size() << std::endl;
    std::cout << "MAX_SIZE :\t" << listA.max_size() << std::endl;

    std::cout << "\n// ----- ELEMENT ACCESS ----- //\n\n";

    std::cout << "FRONT :\t" << listA.front() << std::endl;
    std::cout << "BACK :\t" << listA.back() << std::endl;
   std::cout << "FRONT (List C):\t" << listC.front() << std::endl;
   std::cout << "BACK (List C):\t" << listC.back() << std::endl;

    std::cout << "\n// ----- MODIFIERS ----- //\n\n";

    std::cout << "\n/ - ASSIGN - /\n";
    std::cout << "List A : Assigning 42 with new size 3 (already assigned)\n";
    listA.assign(3, 42);
    std::cout << listA;
    std::cout << "List A : Assigning 42 with new size 10\n";
    listA.assign(10, 42);
    std::cout << listA;
    //listC.assign(10, 42);      //can't assign to const list
    std::cout << "Assigning empty list B and  with iterators\n";
    listB.assign(listC.begin(), listC.end());
    std::cout << listB;

    std::cout << "\n/ - POP - /\n";
    std::cout << "List A : Popping back...\n";
    listA.pop_back();      // CONTENT = {  1, -2,  3,  4, -5, __  }
    std::cout << listA;
    std::cout << "List A : Popping front...\n";
    listA.pop_front();     // CONTENT = {  __ -2,  3,  4, -5, __  }
    std::cout << listA;

    std::cout << "\n/ - INSERT - /\n";
    ft::List<int>::iterator it = listA.begin(); it++; it++; it++; it++; it++;
    std::cout << "List A : insert value\t\tReturn = " << *(listA.insert(it, 667));
    std::cout << listA << "List A : insert 3 * 7\t\t\t";
    listA.insert(it, 3, 7);
    std::cout << listA << "List A : insert iterators\t\t";
    listA.insert(it, listC.begin(), listC.end()); // this works
    std::cout << listA;

    std::cout << "\n/ - ERASE - /\n";
    ft::List<int>::iterator it2 = listA.begin(); it2++; it2++; it2++; it2++; it2++;
    it2 = listA.erase(it2);
    std::cout << "List A : erase value 667\tReturn : " << *it2 << listA;
    it2 = listA.erase(it2, it);
    std::cout << "List A : erase iterators\tReturn : " << *it2 << listA; // this works

    std::cout << "\n/ - RESIZE - /\n";
    std::cout << "List D (empty) : Resize to 10 elements\n";
    listD.resize(10);
    std::cout << listD;
    std::cout << "List D : Resize to 5 elements\n";
    listD.resize(5);
    std::cout << listD;
    std::cout << "List D : Resize to 10 elements, filling with 123\n";
    listD.resize(10, 123);
    std::cout << listD;
    
    std::cout << "\n/ - CLEAR - /\n";
    std::cout << "List B : Clear\n";
    std::cout << listB;
    listB.clear();
    std::cout << listB;

    std::cout << "\n/ - SWAP - /\n";
    std::cout << "Before :\tlist A -> " << &listA << listA << "\t\tlist B -> " << &listB << listB;
    listA.swap(listB);
    std::cout << "After :\t\tlist A -> " << &listA << listA << "\t\tlist B -> " << &listB << listB;
    // listA.swap(listB);
    
    std::cout << "\n// ----- OPERATIONS ----- //\n\n";

    // std::cout << "\n/ - SPLICE - /\n";
    // std::cout << "1) Before :\tlist A -> " << listA << "\t\tlist D -> " << listD;
    // it = listA.begin(); it++; it++; it++;
    // listA.splice(listD.begin(), listA, it);
    // std::cout << "   After :\tlist A -> " << listA << "\t\tlist D -> " << listD;
    // std::cout << "2) Before :\tlist A -> "<< listA;
    // std::cout << "\t\tlist B -> " << listB;
    // it = listA.begin(); it++;
    // listB.splice(listB.begin(), listA, it, listA.end());
    // std::cout << "   After :\tlist A -> " << listA << "\t\tlist B -> " << listB;
    
    std::cout << "\n/ - UNIQUE - /\n";
    std::cout << "Removing value 123 from all lists\n";
    listA.unique();
    listB.unique();
    listD.unique();
    std::cout << listA << listB << listD;

    std::cout << "\n/ - REMOVE - /\n";
    std::cout << "Removing value 123 from all lists\n";
    listA.remove(123);
    listB.remove(123);
    listD.remove(123);
    std::cout << listA << listB << listD;

    std::cout << "\n/ - REMOVE IF - /\n";
    std::cout << "List A & D : Removing elements if they are even numbers\n";
    listA.remove_if(&isEven);
    listD.remove_if(&isEven);
    std::cout << listA << listD;
    std::cout << "List B : Removing elements if they are digits\n";
    listB.remove_if(&isDigit);
    std::cout << listB;


}