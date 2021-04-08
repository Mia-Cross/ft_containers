/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:16:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/04/08 03:32:29 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers/map.hpp"
#include <cstdlib>

// bool isOdd(int x) { return (x % 2 ? true : false); }
// bool isDigit(int x) { return (x < 10 && x > -1 ? true : false); }
// bool compareAbs(int x, int y){ return ( abs(x) < abs(y) ? true : false);}
// bool isNear(int x, int y) { return (abs(x - y) < 5); }

void testMap()
{
    std::cout << "**       **       *       ********\n";
    std::cout << "***     ***      ***      **     **\n";
    std::cout << "****   ****     ** **     **      **\n";
    std::cout << "** ** ** **    **   **    **     **\n";
    std::cout << "**  ***  **   *********   *******\n";
    std::cout << "**   *   **  **       **  **\n";
    std::cout << "**       ** **         ** **\n\n";

    std::cout << "Creating Map A with content \n";
    ft::Map<int, char> mapA;
    std::cout << mapA;
    std::pair<ft::Map<int, char>::iterator,bool> ret = mapA.insert(std::pair<int, char>(7, 's'));
    std::cout << "INSERT '7-s' : Return = \'" << ret.first.operator*().first << "-";
    std::cout << ret.first.operator*().second << "\'\t" << ret.second << std::endl;
    std::cout << mapA;
    ret = mapA.insert(std::pair<int, char>(8, 'h'));
    std::cout << "INSERT '8-h' : Return = \'" << ret.first.operator*().first << "-";
    std::cout << ret.first.operator*().second << "\'\t" << ret.second << std::endl;
    std::cout << mapA;
    ret = mapA.insert(std::pair<int, char>(7, 'S'));
    std::cout << "INSERT '7-S' : Return = \'" << ret.first.operator*().first << "-";
    std::cout << ret.first.operator*().second << "\'\t" << ret.second << std::endl;
    std::cout << mapA;
    std::cout << "+ 4" << std::endl;
    mapA[4] = 'q';
    std::cout << mapA;
    std::cout << "+ 9" << std::endl;
    mapA[9] = 'n';
    std::cout << mapA;
    std::cout << "+ 1" << std::endl;
    mapA[1] = 'u';
    std::cout << mapA;
    std::cout << "+ 2" << std::endl;
    mapA[2] = 'd';
    std::cout << mapA;
    std::cout << "+ 5" << std::endl;
    mapA[5] = 'c';
    std::cout << mapA;
    std::cout << "+ 3" << std::endl;
    mapA[3] = 't';
    std::cout << mapA;
    std::cout << "Creating Map B with content (iterators) \n";
    ft::Map<int, char> mapB(mapA.begin(), mapA.end()); 
    std::cout << mapB;
    std::cout << "Creating Map C as a const copy of A\n";
    const ft::Map<int, char> mapC(mapA);
    std::cout << mapC;
    std::cout << "Creating Map D as a copy of B by assignation\n";
    ft::Map<int, char> mapD = mapB;
    std::cout << mapD;
    std::cout << "Creating Map E empty\n";
    ft::Map<int, char> mapE;
    std::cout << mapE;

    std::cout << "\n// ----- ITERATORS ----- //\n\n";

    std::cout << "Displaying MapA with ITERATION :\t\t";
    for (ft::Map<int, char>::iterator it = mapA.begin(); it != mapA.end(); it++)
    {
        std::pair<int, char> pair = *it;
            std::cout << "[" << pair.first << "," << pair.second << "] ";
    }
    std::cout << "\nDisplaying MapA with REVERSE ITERATION :\t";
    for (ft::Map<int, char>::reverse_iterator rit = mapA.rbegin(); rit != mapA.rend(); rit++)
    {
        std::pair<int, char> pair = *rit;
            std::cout << "[" << pair.first << "," << pair.second << "] ";
    }
    std::cout << "\nDisplaying MapC with CONST ITERATION :\t\t";
    for (ft::Map<int, char>::const_iterator it = mapC.begin(); it != mapC.end(); it++)
    {
        std::pair<int, char> pair = *it;
            std::cout << "[" << pair.first << "," << pair.second << "] ";
    }
    std::cout << "\nDisplaying MapC with CONST REVERSE ITERATION :\t";
    for (ft::Map<int, char>::const_reverse_iterator rit = mapC.rbegin(); rit != mapC.rend(); rit++)
    {
        std::pair<int, char> pair = *rit;
            std::cout << "[" << pair.first << "," << pair.second << "] ";
    }
    std::cout << std::endl;
    
    std::cout << "\n// ----- CAPACITY ----- //\n\n";
    
    std::cout << mapA;
    std::cout << "EMPTY (mapA) :\t" << mapA.empty() << std::endl;
    std::cout << mapE;
    std::cout << "EMPTY (mapE) :\t" << mapE.empty() << std::endl;
    std::cout << mapA;
    std::cout << "SIZE (mapA) :\t" << mapA.size() << std::endl;
    std::cout << mapB;
    std::cout << "SIZE (mapB) :\t" << mapB.size() << std::endl;
    std::cout << mapE;
    std::cout << "SIZE (mapE) :\t" << mapE.size() << std::endl;
    std::cout << "MAX_SIZE (mapA) :\t" << mapA.max_size() << std::endl;
    std::cout << "MAX_SIZE (mapE) :\t" << mapE.max_size() << std::endl;

    std::cout << "\n// ----- ELEMENT ACCESS ----- //\n\n";

    std::cout << "Adding content with operator[] :\n" << mapB;
    mapB[27] = '$';
    mapB[42] = '*';
    mapB[11] = '?';
    mapB[45] = '=';
    mapB[30] = '+';
    mapB[20] = '&';
    std::cout << mapB;
    std::cout << mapA;
    std::cout << "mapA[8] = " << mapA[8] << std::endl;
    std::cout << "mapA[7] = " << mapA[4] << std::endl;
    std::cout << "mapA[45] = " << mapA[45] << std::endl; /// a voir si il faut regler ca 
    std::cout << "mapB[45] = " << mapB[45] << std::endl;
    // const int &i = mapC.front();
    // //i++;                      //can't modify value
    // //int &i = mapC.front();   //can't bind to non const
    // (void)i;

    //restoring maps from const copies
    // mapA = mapC;
    // mapB = mapD;

    std::cout << "\n// ----- MODIFIERS ----- //\n\n";    
    
    // std::cout << "\n/ - INSERT - /\n";
    // std::cout << mapA << mapB << mapE;
    // std::cout << "Placing an iterator at 3rd position of maps A & B, at begin() of map E\n";
    // ft::Map<int>::iterator it = mapA.begin(); it++; it++;
    // ft::Map<int>::iterator it2 = mapB.begin(); it2++; it2++;
    // ft::Map<int>::iterator it3 = mapE.begin();
    // it = mapA.insert(it, 123);
    // it2 = mapB.insert(it2, 123);
    // it3 = mapE.insert(it3, 123);
    // std::cout << " * Insert value '123' :\n";
    // std::cout << "Return = " << *it << mapA;
    // std::cout << "Return = " << *it2 << mapB;
    // std::cout << "Return = " << *it3 << mapE;
    // mapE.clear();
    // it3 = mapE.begin();
    // std::cout << " * Insert value '808' 3 times\n";
    // mapA.insert(it, 3, 808);
    // mapB.insert(it2, 3, 808);
    // mapE.insert(it3, 3, 808);
    // std::cout << mapA << mapB << mapE;
    // mapE.clear();
    // std::cout << " * Insert using iterators\n";
    // mapA.insert(it, mapC.begin(), mapC.end());
    // mapB.insert(it2, mapC.begin(), mapC.end());
    // mapE.insert(it3, mapC.begin(), mapC.end());
    // std::cout << mapA << mapB << mapE;
    // mapE.clear();

    // std::cout << "\n/ - ERASE - /\n";
    // std::cout << " * Erase single value '123'\n";
    // it = mapA.erase(it);
    // it2 = mapB.erase(it2);
    // it3 = mapE.erase(it3);
    // std::cout << "Return = " << *it << mapA;
    // std::cout << "Return = " << *it2 << mapB;
    // std::cout << "Return = " << *it3 << mapE;
    // std::cout << " * Erase using iterators (3rd position)\n";
    // it = mapA.begin(); it++; it++;
    // it2 = mapB.begin(); it2++; it2++;
    // it3 = mapE.begin();
    // it = mapA.erase(it, mapA.end());
    // it2 = mapB.erase(it2, mapB.end());
    // it3 = mapE.erase(it3, mapE.end());
    // std::cout << "Return = " << *it << mapA;
    // std::cout << "Return = " << *it2 << mapB;
    // std::cout << "Return = " << *it3 << mapE;

    std::cout << "\n/ - SWAP - /\n";
    std::cout << "Before :\tmap A -> " << &mapA << mapA << "\t\tmap B -> " << &mapB << mapB;
    mapA.swap(mapB);
    std::cout << "After :\t\tmap A -> " << &mapA << mapA << "\t\tmap B -> " << &mapB << mapB;
    std::cout << "Before :\tmap A -> " << &mapA << mapA << "\t\tmap E -> " << &mapE << mapE;
    mapA.swap(mapE);
    std::cout << "After :\t\tmap A -> " << &mapA << mapA << "\t\tmap E -> " << &mapE << mapE;
    //restoring maps from const copies
    mapA = mapC;
    mapB = mapD;
    mapE.clear();
    
    // std::cout << "\n/ - CLEAR - /\n";
    // mapA.clear();
    // mapB.clear();
    // mapE.clear();
    // std::cout << mapA << mapB << mapE;
    // //restoring maps from const copies
    // mapA = mapC;
    // mapB = mapD;

    // std::cout << "\n// ----- OPERATIONS ----- //\n\n";
}