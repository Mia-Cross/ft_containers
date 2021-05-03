/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testList.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:19 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/03 21:50:49 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers/list.hpp"
#include <cstdlib>

bool isOdd(int x) { return (x % 2 ? true : false); }
bool isDigit(int x) { return (x < 10 && x > -1 ? true : false); }
bool compareAbs(int x, int y){ return ( abs(x) < abs(y) ? true : false);}
bool isNear(int x, int y) { return (abs(x - y) < 5); }

void testList()
{
    std::cout << "   *  _ ___\n";
    std::cout << "|  | |_  | \n";
    std::cout << "|_ |  _| | \n\n";

    std::cout << "Creating list A with content \n";
    ft::list<int> listA;
    listA.resize(2, 0);
    listA.resize(4, 2);
    listA.resize(6, 1);
    listA.resize(7, 3);
    listA.push_front(42);
    listA.push_back(-42);
    std::cout << listA;
    std::cout << "Creating list B with content \n";
    ft::list<int> listB(4, 667);
    listB.push_back(1000);
    std::cout << listB;
    std::cout << "Creating list C as a const copy of A\n";
    const ft::list<int> listC(listA);
    std::cout << listC;
    std::cout << "Creating list D as a copy of B by assignation\n";
    ft::list<int> listD = listB;
    std::cout << listD;
    std::cout << "Creating list E empty\n";
    ft::list<int> listE;
    std::cout << listE;

    std::cout << "\n// ----- ITERATORS ----- //\n\n";

    std::cout << "Displaying ListA with ITERATION :\t\t";
    for (ft::list<int>::iterator it = listA.begin(); it != listA.end(); it++)
        std::cout << "[" << *it << "]";
    std::cout << "\nDisplaying ListA with REVERSE ITERATION :\t";
    for (ft::list<int>::reverse_iterator rit = listA.rbegin(); rit != listA.rend(); rit++)
        std::cout << "[" << *rit << "]";
    std::cout << "\nDisplaying ListC with CONST ITERATION :\t\t";
    for (ft::list<int>::const_iterator it = listC.begin(); it != listC.end(); it++)
        std::cout << "[" << *it << "]";
    std::cout << "\nDisplaying ListC with CONST REVERSE ITERATION :\t";
    for (ft::list<int>::const_reverse_iterator rit = listC.rbegin(); rit != listC.rend(); rit++)
        std::cout << "[" << *rit << "]";
    std::cout << std::endl;
    
    std::cout << "\n// ----- CAPACITY ----- //\n\n";
    
    std::cout << listA;
    std::cout << "EMPTY (listA) :\t" << listA.empty() << std::endl;
    std::cout << listE;
    std::cout << "EMPTY (listE) :\t" << listE.empty() << std::endl;
    std::cout << listA;
    std::cout << "SIZE (listA) :\t" << listA.size() << std::endl;
    std::cout << listB;
    std::cout << "SIZE (listB) :\t" << listB.size() << std::endl;
    std::cout << listE;
    std::cout << "SIZE (listE) :\t" << listE.size() << std::endl;
    std::cout << "MAX_SIZE (listA) :\t" << listA.max_size() << std::endl;
    std::cout << "MAX_SIZE (listE) :\t" << listE.max_size() << std::endl;

    std::cout << "\n// ----- ELEMENT ACCESS ----- //\n\n";

    std::cout << listA;
    std::cout << "FRONT :\t" << listA.front() << std::endl;
    std::cout << "BACK :\t" << listA.back() << std::endl;
    std::cout << listB;
    std::cout << "FRONT :\t" << listB.front() << std::endl;
    std::cout << "BACK :\t" << listB.back() << std::endl;
    std::cout << listE;
    std::cout << "FRONT :\t" << listE.front() << std::endl;
    std::cout << "BACK :\t" << listE.back() << std::endl;
    std::cout << listC;
    std::cout << "FRONT :\t" << listC.front() << " (const ref)" << std::endl;
    const int &i = listC.front();
    //i++;                      //can't modify value
    //int &i = listC.front();   //can't bind to non const
    (void)i;
    std::cout << "BACK :\t" << listC.back() << " (const ref)" << std::endl;

    std::cout << "\n// ----- MODIFIERS ----- //\n\n";

    std::cout << "\n/ - ASSIGN - /\n";
    std::cout << listA << listB << listE;
    std::cout << " * Assigning '100' with new size 7\n";
    listA.assign(7, 100);
    listB.assign(7, 100);
    listE.assign(7, 100);
    std::cout << listA << listB << listE;
    listE.clear();
    //listC.assign(10, 42);      //can't assign to const list
    std::cout << " * Assigning from ListC using iterators\n";
    listA.assign(listC.begin(), listC.end());
    listB.assign(listC.begin(), listC.end());
    listE.assign(listC.begin(), listC.end());
    std::cout << listA << listB << listE;
    listE.clear();

    std::cout << "\n/ - PUSH - /\n";
    std::cout << " * Pushing front...\n";
    listA.push_front(2147483647);
    listB.push_front(2147483647);
    listE.push_front(2147483647);
    std::cout << listA << listB << listE;
    listE.clear();
    std::cout << " * Pushing back...\n";
    listA.push_back(-2147483648);
    listB.push_back(-2147483648);
    listE.push_back(-2147483648);
    std::cout << listA << listB << listE;
    listE.clear();

    std::cout << "\n/ - POP - /\n";
    std::cout << " * Popping front...\n";
    listA.pop_front();
    listB.pop_front();
    listE.pop_front();
    std::cout << listA << listB << listE;
    std::cout << " * Popping back...\n";
    listA.pop_back();
    listB.pop_back();
    listE.pop_back();
    std::cout << listA << listB << listE;

    //restoring lists from const copies
    listA = listC;
    listB = listD;

    std::cout << "\n/ - INSERT - /\n";
    std::cout << listA << listB << listE;
    std::cout << "Placing an iterator at 3rd position of lists A & B, at begin() of list E\n";
    ft::list<int>::iterator it = listA.begin(); it++; it++;
    ft::list<int>::iterator it2 = listB.begin(); it2++; it2++;
    ft::list<int>::iterator it3 = listE.begin();
    it = listA.insert(it, 123);
    it2 = listB.insert(it2, 123);
    it3 = listE.insert(it3, 123);
    std::cout << " * Insert value '123' :\n";
    std::cout << "Return = " << *it << listA;
    std::cout << "Return = " << *it2 << listB;
    std::cout << "Return = " << *it3 << listE;
    listE.clear();
    it3 = listE.begin();
    std::cout << " * Insert value '808' 3 times\n";
    listA.insert(it, 3, 808);
    listB.insert(it2, 3, 808);
    listE.insert(it3, 3, 808);
    std::cout << listA << listB << listE;
    listE.clear();
    std::cout << " * Insert using iterators\n";
    listA.insert(it, listC.begin(), listC.end());
    listB.insert(it2, listC.begin(), listC.end());
    listE.insert(it3, listC.begin(), listC.end());
    std::cout << listA << listB << listE;
    listE.clear();

    std::cout << "\n/ - ERASE - /\n";
    std::cout << " * Erase single value '123'\n";
    it = listA.erase(it);
    it2 = listB.erase(it2);
    it3 = listE.erase(it3);
    std::cout << "Return = " << *it << listA;
    std::cout << "Return = " << *it2 << listB;
    std::cout << "Return = " << *it3 << listE;
    std::cout << " * Erase using iterators (3rd position)\n";
    it = listA.begin(); it++; it++;
    it2 = listB.begin(); it2++; it2++;
    it3 = listE.begin();
    it = listA.erase(it, listA.end());
    it2 = listB.erase(it2, listB.end());
    it3 = listE.erase(it3, listE.end());
    std::cout << "Return = " << *it << listA;
    std::cout << "Return = " << *it2 << listB;
    std::cout << "Return = " << *it3 << listE;

    std::cout << "\n/ - SWAP - /\n";
    std::cout << "Before :\tlist A -> " << &listA << listA << "\t\tlist B -> " << &listB << listB;
    listA.swap(listB);
    std::cout << "After :\t\tlist A -> " << &listA << listA << "\t\tlist B -> " << &listB << listB;
    std::cout << "Before :\tlist A -> " << &listA << listA << "\t\tlist E -> " << &listE << listE;
    listA.swap(listE);
    std::cout << "After :\t\tlist A -> " << &listA << listA << "\t\tlist E -> " << &listE << listE;
    //restoring lists from const copies
    listA = listC;
    listB = listD;
    listE.clear();

    std::cout << "\n/ - RESIZE - /\n";
    std::cout << " * Resize to 10 elements\n";
    listA.resize(10);
    listB.resize(10);
    listE.resize(10);
    std::cout << listA << listB << listE;
    listE.clear();
    std::cout << " * Resize to 5 elements\n";
    listA.resize(5);
    listB.resize(5);
    listE.resize(5);
    std::cout << listA << listB << listE;
    listE.clear();
    std::cout << " * Resize to 10 elements, filling with '-1'\n";
    listA.resize(10, -1);
    listB.resize(10, -1);
    listE.resize(10, -1);
    std::cout << listA << listB << listE;
    
    std::cout << "\n/ - CLEAR - /\n";
    listA.clear();
    listB.clear();
    listE.clear();
    std::cout << listA << listB << listE;
    //restoring lists from const copies
    listA = listC;
    listB = listD;

    std::cout << "\n// ----- OPERATIONS ----- //\n\n";

    std::cout << "\n/ - SPLICE - /\n";
    std::cout << " * Splicing whole listB in listA\n";
    std::cout << "Before :\tlist A -> " << listA << "\t\tlist B -> " << listB;
    listA.splice(listA.rend(), listB);
    std::cout << "After :\t\tlist A -> " << listA << "\t\tlist B -> " << listB;
    //restoring lists from const copies
    listA = listC;
    listB = listD;
    std::cout << " * Splicing single element with iterator : listB -> listA\n";
    std::cout << "Before :\tlist A -> " << listA << "\t\tlist B -> " << listB;
    listA.splice(listA.begin(), listB, listB.begin());
    std::cout << "After :\t\tlist A -> " << listA << "\t\tlist B -> " << listB;
    //restoring lists from const copies
    listA = listC;
    listB = listD;
    std::cout << " * Splicing elements with iterators : listA -> listB\n";
    std::cout << "Placing an iterator at 3rd position of list A\n";
    it = listA.begin(); it++; it++;
    std::cout << "Before :\tlist A -> " << listA << "\t\tlist B -> " << listB;
    listB.splice(listB.begin(), listA, it, listA.end());
    std::cout << "After :\t\tlist A -> " << listA << "\t\tlist B -> " << listB;
    //restoring lists from const copies
    listA = listC;
    listB = listD;

    std::cout << "\n/ - REMOVE - /\n";
    std::cout << "  Removing value '0' from all lists\n";
    listA.remove(0);
    listB.remove(0);
    listD.remove(0);
    std::cout << listA << listB << listE;
    //restoring lists from const copies
    listA = listC;
    listB = listD;

    std::cout << "\n/ - REMOVE IF - /\n";
    std::cout << " * Removing elements if they are odd numbers\n";
    listA.remove_if(&isOdd);
    listB.remove_if(&isOdd);
    listE.remove_if(&isOdd);
    std::cout << listA << listB << listE;
    //restoring lists from const copies
    listA = listC;
    listB = listD;
    std::cout << " * Removing elements if they are digits\n";
    listA.remove_if(&isDigit);
    listB.remove_if(&isDigit);
    listE.remove_if(&isDigit);
    std::cout << listA << listB << listE;
    //restoring lists from const copies
    listA = listC;
    listB = listD;
    
    std::cout << "\n/ - UNIQUE - /\n";
    std::cout << listA << listB << listE;
    std::cout << " * Removing non unique values\n";
    listA.unique();
    listB.unique();
    listE.unique();
    std::cout << listA << listB << listE;
    //restoring lists from const copies
    listA = listC;
    listB = listD;
    std::cout << " * Removing values if they are near the previous (+-5)\n";
    listA.unique(isNear);
    listB.unique(isNear);
    listE.unique(isNear);
    std::cout << listA << listB << listE;
    //restoring lists from const copies
    listA = listC;
    listB = listD;
    
    std::cout << "\n/ - MERGE - /\n";
    std::cout << " * Merge listA in listB\n";
    std::cout << "Before :\tlist A -> " << listA << "\t\tlist B -> " << listB;
    listB.merge(listA);
    std::cout << "After :\t\tlist A -> " << listA << "\t\tlist B -> " << listB;
    //restoring lists from const copies
    listA = listC;
    listB = listD;
    listA.sort(compareAbs);
    listB.sort(compareAbs);
    std::cout << " * Merge listA in listB according to predicate (abs)\n";
    std::cout << "Before :\tlist A -> " << listA << "\t\tlist B -> " << listB;
    listB.merge(listA, compareAbs);
    std::cout << "After :\t\tlist A -> " << listA << "\t\tlist B -> " << listB;
    //restoring lists from const copies
    listA = listC;
    listB = listD;

    std::cout << "\n/ - SORT - /\n";
    std::cout << listA << listB << listE;
    std::cout << " * Sort by value order\n";
    listA.sort();
    listB.sort();
   // listC.sort();  //can't modify const list
    listE.sort();
    std::cout << listA << listB << listE;
    std::cout << " * Sort by predicate order (abs)\n";
    listA.sort(compareAbs);
    listB.sort(compareAbs);
    listE.sort(compareAbs);
    std::cout << listA << listB << listE;

    std::cout << "\n/ - REVERSE - /\n";
    std::cout << " * Reverse elements in all lists\n";
    listA.reverse();
    listB.reverse();
    listE.reverse();
    std::cout << listA << listB << listE;
    std::cout << std::endl << std::endl;

}