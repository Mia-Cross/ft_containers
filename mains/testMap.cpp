/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:16:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/06 17:23:59 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers/map.hpp"
#include <cstdlib>
#include <map>

void testMap()
{
    std::cout << "**       **       *       ********\n";
    std::cout << "***     ***      ***      **     **\n";
    std::cout << "****   ****     ** **     **      **\n";
    std::cout << "** ** ** **    **   **    **     **\n";
    std::cout << "**  ***  **   *********   *******\n";
    std::cout << "**   *   **  **       **  **\n";
    std::cout << "**       ** **         ** **\n\n";

    std::cout << "Creating map A with content \n";
    ft::map<int, char> mapA;
    std::cout << mapA;
    std::pair<ft::map<int, char>::iterator,bool> ret = mapA.insert(std::pair<int, char>(7, 's'));
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
    std::cout << "Creating map B with content (iterators) \n";
    ft::map<int, char> mapB(mapA.begin(), mapA.end());   
    std::cout << mapB;
    {
        std::cout << "Creating map C as a const copy of A\n";
        const ft::map<int, char> mapC(mapA);        
        std::cout << mapC;
    }
    std::cout << "Creating map D as a copy of B by assignation\n";
    ft::map<int, char> mapD;
    mapD = mapB;      
    std::cout << mapD;
    std::cout << "Creating map E empty\n";
    ft::map<int, char> mapE;
    std::cout << mapE;

    std::cout << "\n// ----- ITERATORS ----- //\n\n";

    std::cout << "Displaying MapA with ITERATION :\t\t";
    for (ft::map<int, char>::iterator it = mapA.begin(); it != mapA.end(); it++)
    {
        std::pair<int, char> pair = *it;
            std::cout << "[" << pair.first << "," << pair.second << "] ";
    }
    std::cout << "\nDisplaying MapA with REVERSE ITERATION :\t";
    for (ft::map<int, char>::reverse_iterator rit = mapA.rbegin(); rit != mapA.rend(); rit++)
    {
        std::pair<int, char> pair = *rit;
            std::cout << "[" << pair.first << "," << pair.second << "] ";
    }
    {
        std::cout << "\nDisplaying MapC with CONST ITERATION :\t\t";
        const ft::map<int, char> mapC(mapA);      
        for (ft::map<int, char>::const_iterator it = mapC.begin(); it != mapC.end(); it++)
        {
            std::pair<int, char> pair = *it;
                std::cout << "[" << pair.first << "," << pair.second << "] ";
        }
        std::cout << "\nDisplaying MapC with CONST REVERSE ITERATION :\t";
        for (ft::map<int, char>::const_reverse_iterator rit = mapC.rbegin(); rit != mapC.rend(); rit++)
        {
            std::pair<int, char> pair = *rit;
                std::cout << "[" << pair.first << "," << pair.second << "] ";
        }
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
    std::cout << "mapA[4] = " << mapA[4] << std::endl;
    std::cout << "mapA[45] = " << mapA[45] << std::endl;
    std::cout << "mapB[45] = " << mapB[45] << std::endl;
    // const int &i = mapC.front();
    // //i++;                      //can't modify value
    // //int &i = mapC.front();   //can't bind to non const
    // (void)i;

    // saving changes in backup maps
    std::cout << "\n >>>>> La j'efface des trucs dans mapA et mapB (dont les 2 roots) <<<<<<" << std::endl;
    mapB.erase(3);
    mapB.erase(1);
    mapB.erase(9);
    mapA.erase(7);
    const ft::map<int, char> mapC(mapA);      
    mapD = mapB;                            

    std::cout << "\n// ----- MODIFIERS ----- //\n\n";    
    
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
    
    std::cout << "\n/ - INSERT - /\n";
    std::cout << mapA << mapB << mapE;
    std::cout << " * Insert value '65-#' with hint :\n";
    std::cout << mapA.insert(mapA.begin(), std::pair<int, char>(65, '#')) << std::endl;
    std::cout << mapB.insert(mapB.begin(), std::pair<int, char>(65, '#')) << std::endl;
    std::cout << mapE.insert(mapE.begin(), std::pair<int, char>(65, '#')) << std::endl;
    std::cout << mapA << mapB << mapE;
    mapE.clear();
    std::cout << " * Insert using iterators\n";
    mapA.insert(mapC.begin(), mapC.end());
    mapB.insert(mapC.begin(), mapC.end());
    mapE.insert(mapC.begin(), mapC.end());
    std::cout << mapA << mapB << mapE;
    //restoring maps from const copies
    mapA = mapC;
    mapB = mapD;
    mapE.clear();

    std::cout << "\n/ - ERASE - /\n";
    std::cout << mapA << mapB << mapE;
    std::cout << " * Erase single value '2-d'\n";
    std::cout << "MapA -> " << mapA.erase(2) << std::endl;
    std::cout << "MapB -> " << mapB.erase(2) << std::endl;
    std::cout << "MapE -> " << mapE.erase(2) << std::endl;
    std::cout << mapA << mapB << mapE;
    std::cout << " * Erase using iterator (begin)\n";
    mapA.erase(mapA.begin());
    mapB.erase(mapB.begin());
    mapE.erase(mapE.begin());
    std::cout << mapA << mapB << mapE;
    //restoring maps from const copies
    mapA = mapC;
    mapB = mapD;

    std::cout << "\n/ - CLEAR - /\n";
    mapA.clear();
    mapB.clear();
    mapE.clear();
    std::cout << mapA << mapB << mapE;
    //restoring maps from const copies
    mapA = mapC;
    mapB = mapD;

    std::cout << "\n// ----- OPERATIONS ----- //\n\n";

    std::cout << "\n/ - FIND - /\n";
    std::cout << mapA << mapB << mapE;
    ft::map<int, char>::iterator it = mapA.find(3);
    std::cout << "Find 3 in map A -> " << it << std::endl;
    it = mapB.find(3);
    std::cout << "Find 3 in map B -> " << (it != mapB.end()) << std::endl;
    ft::map<int, char>::const_iterator itc = mapC.find(3);
    std::cout << "Find 3 in map C -> " << itc << std::endl;
    it = mapE.find(3);
    std::cout << "Find 3 in map E -> " << (it != mapE.end()) << std::endl;

    std::cout << "\n/ - COUNT - /\n";
    std::cout << mapA << mapB << mapE;
    std::cout << "Count 9 in map A -> " << mapA.count(9) << std::endl;
    std::cout << "Count 9 in map B -> " << mapB.count(9) << std::endl;
    std::cout << "Count 9 in map E -> " << mapE.count(9) << std::endl;

    //creating identical maps with the STL
    std::map<int, char> stdMapA;
    stdMapA[1] = 'u';
    stdMapA[2] = 'd';
    stdMapA[3] = 't';
    stdMapA[4] = 'q';
    stdMapA[5] = 'c';
    stdMapA[8] = 'h';
    stdMapA[9] = 'n';
    std::cout << stdMapA[45] << std::endl;
    std::map<int, char> stdMapB(stdMapA);
    stdMapB[7] = 'S';
    stdMapB[11] = '?';
    stdMapB[20] = '&';
    stdMapB[27] = '$';
    stdMapB[30] = '+';
    stdMapB[42] = '*';
    stdMapB[45] = '=';
    std::map<int, char> stdMapE;

    std::cout << "\n/ - LOWER_BOUND - /\n";
    std::cout << mapA << mapB << mapE;
    std::map<int,char>::iterator iter = stdMapA.lower_bound(5);
    std::pair<int,char> pair = *iter;
    std::cout << "[expected] Lower_bound for 5 in map A -> " << pair.first << "-" << pair.second << std::endl;
    iter = stdMapB.lower_bound(20); pair = *iter;
    std::cout << "[expected] Lower_bound for 20 in map B -> " << pair.first << "-" << pair.second << std::endl;
    iter = stdMapE.lower_bound(20); pair = *iter;
    std::cout << "[expected] Lower_bound for 20 in map E -> " << pair.first << "-" << pair.second << std::endl;
    iter = stdMapA.lower_bound(42); pair = *iter;
    std::cout << "[expected] Lower_bound for 42 in map A -> " << pair.first << "-" << pair.second << std::endl;
    std::cout << "Lower_bound for 5 in map A -> " << mapA.lower_bound(5) << std::endl;
    std::cout << "Lower_bound for 20 in map B -> " << mapB.lower_bound(20) << std::endl;
    std::cout << "Lower_bound for 20 in map E -> " << mapE.lower_bound(20) << std::endl;
    std::cout << "Lower_bound for 42 in map A -> " << mapA.lower_bound(42) << std::endl;
    mapE.clear();

    std::cout << "\n/ - UPPER_BOUND - /\n";
    std::cout << mapA << mapB << mapE;
    iter = stdMapA.upper_bound(5); pair = *iter;
    std::cout << "[expected] Upper_bound for 5 in map A -> " << pair.first << "-" << pair.second << std::endl;
    iter = stdMapB.upper_bound(20); pair = *iter;
    std::cout << "[expected] Upper_bound for 20 in map B -> " << pair.first << "-" << pair.second << std::endl;
    iter = stdMapE.upper_bound(20); pair = *iter;
    std::cout << "[expected] Upper_bound for 20 in map E -> " << pair.first << "-" << pair.second << std::endl;
    iter = stdMapA.upper_bound(42); pair = *iter;
    std::cout << "[expected] Upper_bound for 42 in map A -> " << pair.first << "-" << pair.second << std::endl;
    std::cout << "Upper_bound for 5 in map A -> " << mapA.upper_bound(5) << std::endl;
    std::cout << "Upper_bound for 20 in map B -> " << mapB.upper_bound(20) << std::endl;
    std::cout << "Upper_bound for 20 in map E -> " << mapE.upper_bound(20) << std::endl;
    std::cout << "Upper_bound for 42 in map A -> " << mapA.upper_bound(42) << std::endl;

    std::cout << std::endl << std::endl;
}