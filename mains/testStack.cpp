/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testStack.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:22:30 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/03 21:52:15 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers/stack.hpp"

void testStack()
{
   std::cout << " _ ___      _    \n";
   std::cout << "|_  |  /_\\ |  |/ \n";
   std::cout << " _| | /   \\|_ |\\\n\n";

   std::cout << "Creating stack A with content \n";
   ft::stack<int> stackA;
   stackA.push(4);
   stackA.push(3);
   stackA.push(2);
   stackA.push(1);
   stackA.push(0);
   std::cout << stackA;
   std::cout << "Creating stack B with content\n";
   ft::stack<int> stackB;
   stackB.push(1000);
   std::cout << stackB;
   std::cout << "Creating stack C as a const copy of A\n";
   const ft::stack<int> stackC(stackA);
   std::cout << stackC;
   std::cout << "Creating stack D as a copy of B by assignation\n";
   ft::stack<int> stackD = stackB;
   std::cout << stackD;
   std::cout << "Creating stack E empty\n";
   ft::stack<int> stackE;
   std::cout << stackE;

   std::cout << "\n// ----- CAPACITY ----- //\n\n";
    
   std::cout << stackA;
   std::cout << "EMPTY :\t" << stackA.empty() << std::endl;
   std::cout << stackE;
   std::cout << "EMPTY :\t" << stackE.empty() << std::endl;
   std::cout << stackA;
   std::cout << "SIZE :\t" << stackA.size() << std::endl;
   std::cout << stackB;
   std::cout << "SIZE :\t" << stackB.size() << std::endl;
   std::cout << stackE;
   std::cout << "SIZE :\t" << stackE.size() << std::endl;

   std::cout << "\n// ----- ELEMENT ACCESS ----- //\n\n";

   std::cout << stackA;
   std::cout << "TOP :\t" << stackA.top() << std::endl;
   std::cout << stackB;
   std::cout << "TOP :\t" << stackB.top() << std::endl;
   std::cout << stackE;
   std::cout << "TOP :\t" << stackE.top() << std::endl;
   std::cout << stackC;
   std::cout << "TOP :\t" << stackC.top() << " (const ref)" << std::endl;
   const int &i = stackC.top();
   // i++;                      //can't modify value
   // int &i = stackC.front();   //can't bind to non const
   (void)i;
   
   std::cout << "\n// ----- MODIFIERS ----- //\n\n";

   std::cout << "/ - PUSH - /\n";
   stackA.push(2147483647);
   stackB.push(2147483647);
   stackE.push(2147483647);
   std::cout << stackA << stackB << stackE;
   stackE.pop();

   std::cout << "\n/ - POP - /\n";
   stackA.pop();
   stackB.pop();
   stackE.pop();
   std::cout << stackA << stackB << stackE;
}

