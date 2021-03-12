/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testVector.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:23:12 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/12 04:33:50 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers/vector.hpp"
#include "../templates/myIterator.hpp"

void testVector()
{
    std::cout << "      _  _ ___  _   _\n";
    std::cout << "\\  / |_ |   |  | | |_|\n";
    std::cout << " \\/  |_ |_  |  |_| |\\\n\n";

    std::cout << "Creating vector A with content \n";
    ft::Vector<int> vectorA;
    vectorA.push_back(42);
    vectorA.resize(2, 0);
    vectorA.resize(4, 2);
    vectorA.resize(6, 1);
    vectorA.resize(7, 3);
    vectorA.push_back(-42);
    std::cout << vectorA;
    std::cout << "Creating vector B with content \n";
    ft::Vector<int> vectorB(4, 667);
    vectorB.push_back(1000);
    std::cout << vectorB;
    std::cout << "Creating vector C as a const copy of A\n";
    const ft::Vector<int> vectorC(vectorA);
    std::cout << vectorC;
    std::cout << "Creating vector D as a const copy of B by assignation\n";
    const ft::Vector<int> vectorD = vectorB;
    std::cout << vectorD;
    std::cout << "Creating vector E empty\n";
    ft::Vector<int> vectorE;
    std::cout << vectorE;
    std::cout << "Creating vector F with iterators\n";
    ft::Vector<int> vectorF(vectorB.begin(), vectorB.end());
    std::cout << vectorF;
    std::cout << vectorF[4] << std::endl;

    std::cout << "\n// ----- ITERATORS ----- //\n\n";

    std::cout << "Displaying vectorA with ITERATION :\t\t";
    for (ft::Vector<int>::iterator it = vectorA.begin(); it != vectorA.end(); it++)
        std::cout << "[" << *it << "]";
    std::cout << "\nDisplaying vectorA with REVERSE ITERATION :\t";
    for (ft::Vector<int>::reverse_iterator rit = vectorA.rbegin(); rit != vectorA.rend(); rit++)
        std::cout << "[" << *rit << "]";
    std::cout << "\nDisplaying vectorC with CONST ITERATION :\t\t";
    for (ft::Vector<int>::const_iterator it = vectorC.begin(); it != vectorC.end(); it++)
        std::cout << "[" << *it << "]";
    std::cout << "\nDisplaying vectorC with CONST REVERSE ITERATION :\t";
    for (ft::Vector<int>::const_reverse_iterator rit = vectorC.rbegin(); rit != vectorC.rend(); rit++)
        std::cout << "[" << *rit << "]";
    std::cout << std::endl;
    std::cout << "Begin + 3 = " << *(vectorA.begin() + 3) << std::endl;
    std::cout << "RBegin + 3 = " << *(vectorA.rbegin() + 3) << std::endl;

    std::cout << "\n// ----- CAPACITY ----- //\n\n";
    
    std::cout << vectorA;
    std::cout << "EMPTY (vectorA) :\t" << vectorA.empty() << std::endl;
    std::cout << vectorE;
    std::cout << "EMPTY (vectorE) :\t" << vectorE.empty() << std::endl;
    std::cout << vectorA;
    std::cout << "SIZE (vectorA) :\t" << vectorA.size() << std::endl;
    std::cout << vectorB;
    std::cout << "SIZE (vectorB) :\t" << vectorB.size() << std::endl;
    std::cout << vectorE;
    std::cout << "SIZE (vectorE) :\t" << vectorE.size() << std::endl;
    std::cout << "MAX_SIZE (vectorA) :\t" << vectorA.max_size() << std::endl;
    std::cout << "MAX_SIZE (vectorE) :\t" << vectorE.max_size() << std::endl;

    std::cout << "\n// ----- ELEMENT ACCESS ----- //\n\n";

    std::cout << vectorA;
    std::cout << "FRONT :\t" << vectorA.front() << std::endl;
    std::cout << "BACK :\t" << vectorA.back() << std::endl;
    std::cout << vectorB;
    std::cout << "FRONT :\t" << vectorB.front() << std::endl;
    std::cout << "BACK :\t" << vectorB.back() << std::endl;
    std::cout << vectorE;
    std::cout << "FRONT :\t" << vectorE.front() << std::endl;
    std::cout << "BACK :\t" << vectorE.back() << std::endl;
    std::cout << vectorC;
    std::cout << "FRONT :\t" << vectorC.front() << " (const ref)" << std::endl;
    const int &i = vectorC.front();
    // i++;                      //can't modify value
    // int &i = vectorC.front();   //can't bind to non const
    (void)i;
    std::cout << "BACK :\t" << vectorC.back() << " (const ref)" << std::endl;
std::cout << "\n// ----- MODIFIERS ----- //\n\n";

    std::cout << "\n/ - ASSIGN - /\n";
    std::cout << vectorA << vectorB << vectorE;
    std::cout << " * Assigning '100' with new size 7\n";
    vectorA.assign(7, 100);
    vectorB.assign(7, 100);
    vectorE.assign(7, 100);
    std::cout << vectorA << vectorB << vectorE;
    vectorE.clear();
    //vectorC.assign(10, 42);      //can't assign to const vector
    std::cout << " * Assigning from VectorC using iterators\n";
    vectorA.assign(vectorC.begin(), vectorC.end());
    vectorB.assign(vectorC.begin(), vectorC.end());
    vectorE.assign(vectorC.begin(), vectorC.end());
    std::cout << vectorA << vectorB << vectorE;
    vectorE.clear();

    std::cout << "\n/ - PUSH - /\n";
    vectorE.clear();
    std::cout << " * Pushing back...\n";
    vectorA.push_back(-2147483648);
    vectorB.push_back(-2147483648);
    vectorE.push_back(-2147483648);
    std::cout << vectorA << vectorB << vectorE;
    vectorE.clear();

    std::cout << "\n/ - POP - /\n";
    std::cout << " * Popping back...\n";
    vectorA.pop_back();
    vectorB.pop_back();
    vectorE.pop_back();
    std::cout << vectorA << vectorB << vectorE;

    //restoring vectors from const copies
    vectorA = vectorC;
    vectorB = vectorD;

    std::cout << "\n/ - INSERT - /\n";
    std::cout << vectorA << vectorB << vectorE;
    std::cout << "Placing an iterator at 3rd position of vectors A & B, at begin() of vector E\n";
    ft::Vector<int>::iterator it = vectorA.begin(); it++; it++;
    ft::Vector<int>::iterator it2 = vectorB.begin(); it2++; it2++;
    ft::Vector<int>::iterator it3 = vectorE.begin();
    it = vectorA.insert(it, 123);
    it2 = vectorB.insert(it2, 123);
    it3 = vectorE.insert(it3, 123);
    std::cout << " * Insert value '123' :\n";
    std::cout << "Return = " << *it << vectorA;
    std::cout << "Return = " << *it2 << vectorB;
    std::cout << "Return = " << *it3 << vectorE;
    vectorE.clear();
    it3 = vectorE.begin();
    std::cout << " * Insert value '808' 3 times\n";
    vectorA.insert(it, 3, 808);
    vectorB.insert(it2, 3, 808);
    vectorE.insert(it3, 3, 808);
    std::cout << vectorA << vectorB << vectorE;
    vectorE.clear();
    std::cout << " * Insert using iterators\n";
    vectorA.insert(it, vectorC.begin(), vectorC.end());
    vectorB.insert(it2, vectorC.begin(), vectorC.end());
    vectorE.insert(it3, vectorC.begin(), vectorC.end());
    std::cout << vectorA << vectorB << vectorE;
    vectorE.clear();

    std::cout << "\n/ - ERASE - /\n";
    std::cout << " * Erase single value at 3rd position\n";
    std::cout << "Return = " << *(vectorA.erase(vectorA.begin() + 2)) << vectorA;
    std::cout << "Return = " << *(vectorB.erase(vectorB.begin() + 2)) << vectorB;
    std::cout << "Return = " << *(vectorE.erase(vectorE.begin())) << vectorE;
    std::cout << " * Erase using iterators (3rd position)\n";
    it = vectorA.begin(); it++; it++;
    it2 = vectorB.begin(); it2++; it2++;
    it3 = vectorE.begin();
    std::cout << "Return = " << *(vectorA.erase(it, vectorA.end())) << vectorA;
    std::cout << "Return = " << *(vectorB.erase(it2, vectorB.end())) << vectorB;
    std::cout << "Return = " << *(vectorE.erase(it3, vectorE.end())) << vectorE;

    std::cout << "\n/ - SWAP - /\n";
    std::cout << "Before :\tvector A -> " << &vectorA << vectorA << "\t\tvector B -> " << &vectorB << vectorB;
    vectorA.swap(vectorB);
    std::cout << "After :\t\tvector A -> " << &vectorA << vectorA << "\t\tvector B -> " << &vectorB << vectorB;
    std::cout << "Before :\tvector A -> " << &vectorA << vectorA << "\t\tvector E -> " << &vectorE << vectorE;
    vectorA.swap(vectorE);
    std::cout << "After :\t\tvector A -> " << &vectorA << vectorA << "\t\tvector E -> " << &vectorE << vectorE;
    //restoring vectors from const copies
    vectorA = vectorC;
    vectorB = vectorD;
    vectorE.clear();

    std::cout << "\n/ - RESIZE - /\n";
    std::cout << " * Resize to 10 elements\n";
    vectorA.resize(10);
    vectorB.resize(10);
    vectorE.resize(10);
    std::cout << vectorA << vectorB << vectorE;
    vectorE.clear();
    std::cout << " * Resize to 5 elements\n";
    vectorA.resize(5);
    vectorB.resize(5);
    vectorE.resize(5);
    std::cout << vectorA << vectorB << vectorE;
    vectorE.clear();
    std::cout << " * Resize to 10 elements, filling with '-1'\n";
    vectorA.resize(10, -1);
    vectorB.resize(10, -1);
    vectorE.resize(10, -1);
    std::cout << vectorA << vectorB << vectorE;
    
    std::cout << "\n/ - CLEAR - /\n";
    vectorA.clear();
    vectorB.clear();
    vectorE.clear();
    std::cout << vectorA << vectorB << vectorE;
    //restoring vectors from const copies
    vectorA = vectorC;
    vectorB = vectorD;
}
