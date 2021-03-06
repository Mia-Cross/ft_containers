/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testVector.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:23:12 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/06 06:40:14 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include "../templates/myIterator.hpp"

void testVector()
{
    std::cout << "      _  _ ___  _   _\n";
    std::cout << "\\  / |_ |   |  | | |_|\n";
    std::cout << " \\/  |_ |_  |  |_| |\\\n\n";

    std::cout << "Creating vector A with content \n";
    ft::Vector<int> vectorA;
    // vectorA.push_front(42);
    // vectorA.push_back(-42);
    // std::cout << vectorA;
    std::cout << "Creating vector B with content \n";
    // ft::Vector<int> vectorB(4, 667);
    // vectorB.push_back(1000);
    // std::cout << vectorB;
    std::cout << "Creating vector C as a const copy of A\n";
    const ft::Vector<int> vectorC(vectorA);
    // std::cout << vectorC;
    std::cout << "Creating vector D as a copy of B by assignation\n";
    // ft::Vector<int> vectorD = vectorB;
    // std::cout << vectorD;
    std::cout << "Creating vector E empty\n";
    ft::Vector<int> vectorE;
    // std::cout << vectorE;

}
