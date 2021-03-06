/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testQueue.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:20:50 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/06 05:38:11 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers/queue.hpp"

void testQueue()
{
   std::cout << " _       _      _\n";
   std::cout << "| | | | |_ | | |_\n";
   std::cout << "|_|\\|_| |_ |_| |_\n\n";

   std::cout << "Creating Queue A with content \n";
   ft::Queue<int> QueueA;
   QueueA.push(0);
   QueueA.push(1);
   QueueA.push(2);
   QueueA.push(3);
   QueueA.push(4);
   std::cout << QueueA;
   std::cout << "Creating Queue B with content\n";
   ft::Queue<int> QueueB;
   QueueB.push(1000);
   std::cout << QueueB;
   std::cout << "Creating Queue C as a const copy of A\n";
   const ft::Queue<int> QueueC(QueueA);
   std::cout << QueueC;
   std::cout << "Creating Queue D as a copy of B by assignation\n";
   ft::Queue<int> QueueD = QueueB;
   std::cout << QueueD;
   std::cout << "Creating Queue E empty\n";
   ft::Queue<int> QueueE;
   std::cout << QueueE;

   std::cout << "\n// ----- CAPACITY ----- //\n\n";
    
   std::cout << QueueA;
   std::cout << "EMPTY (QueueA) :\t" << QueueA.empty() << std::endl;
   std::cout << QueueE;
   std::cout << "EMPTY (QueueE) :\t" << QueueE.empty() << std::endl;
   std::cout << QueueA;
   std::cout << "SIZE (QueueA) :\t" << QueueA.size() << std::endl;
   std::cout << QueueB;
   std::cout << "SIZE (QueueB) :\t" << QueueB.size() << std::endl;
   std::cout << QueueE;
   std::cout << "SIZE (QueueE) :\t" << QueueE.size() << std::endl;

   std::cout << "\n// ----- ELEMENT ACCESS ----- //\n\n";

   std::cout << QueueA;
   std::cout << "FRONT :\t" << QueueA.front() << std::endl;
   std::cout << "BACK :\t" << QueueA.back() << std::endl;
   std::cout << QueueB;
   std::cout << "FRONT :\t" << QueueB.front() << std::endl;
   std::cout << "BACK :\t" << QueueB.back() << std::endl;
   std::cout << QueueE;
   std::cout << "FRONT :\t" << QueueE.front() << std::endl;
   std::cout << "BACK :\t" << QueueE.back() << std::endl;
   std::cout << QueueC;
   std::cout << "FRONT :\t" << QueueC.front() << " (const ref)" << std::endl;
   const int &i = QueueC.front();
   // i++;                      //can't modify value
   // int &i = QueueC.front();   //can't bind to non const
   (void)i;
   std::cout << "BACK :\t" << QueueC.back() << " (const ref)" << std::endl;
   
   std::cout << "\n// ----- MODIFIERS ----- //\n\n";

   std::cout << "/ - PUSH - /\n";
   QueueA.push(2147483647);
   QueueB.push(2147483647);
   QueueE.push(2147483647);
   std::cout << QueueA << QueueB << QueueE;
   QueueE.pop();

   std::cout << "\n/ - POP - /\n";
   QueueA.pop();
   QueueB.pop();
   QueueE.pop();
   std::cout << QueueA << QueueB << QueueE;
}