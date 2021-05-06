/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testQueue.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:20:50 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/06 17:24:07 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../containers/queue.hpp"
#include <queue>

void testQueue()
{
   std::cout << " _       _      _\n";
   std::cout << "| | | | |_ | | |_\n";
   std::cout << "|_|\\|_| |_ |_| |_\n\n";

   std::cout << "Creating queue A with content \n";
   ft::queue<int> QueueA;
   std::queue<int> realQueueA;
   QueueA.push(0);
   QueueA.push(1);
   QueueA.push(2);
   QueueA.push(3);
   QueueA.push(4);
   realQueueA.push(0);
   realQueueA.push(1);
   realQueueA.push(2);
   realQueueA.push(3);
   realQueueA.push(4);
   std::cout << QueueA;
   std::cout << "Creating queue B with content\n";
   ft::queue<int> QueueB;
   std::queue<int> realQueueB;
   QueueB.push(1000);
   realQueueB.push(1000);
   std::cout << QueueB;
   std::cout << "Creating queue C as a const copy of A\n";
   const ft::queue<int> QueueC(QueueA);
   const std::queue<int> realQueueC(realQueueA);
   std::cout << QueueC;
   std::cout << "Creating queue D as a copy of B by assignation\n";
   ft::queue<int> QueueD = QueueB;
   std::queue<int> realQueueD = realQueueB;
   std::cout << QueueD;
   std::cout << "Creating queue E empty\n";
   ft::queue<int> QueueE;
   std::queue<int> realQueueE;
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
   std::cout << "[expected] FRONT :\t" << realQueueA.front() << std::endl;
   std::cout << "[expected] BACK :\t" << realQueueA.back() << std::endl;
   std::cout << QueueB;
   std::cout << "FRONT :\t" << QueueB.front() << std::endl;
   std::cout << "BACK :\t" << QueueB.back() << std::endl;
   std::cout << "[expected] FRONT :\t" << realQueueB.front() << std::endl;
   std::cout << "[expected] BACK :\t" << realQueueB.back() << std::endl;
   std::cout << QueueE;
   std::cout << "FRONT :\t" << QueueE.front() << std::endl;
   std::cout << "BACK :\t" << QueueE.back() << std::endl;
   // std::cout << "[expected] FRONT :\t" << realQueueE.front() << std::endl;
   // std::cout << "[expected] BACK :\t" << realQueueE.back() << std::endl;
   std::cout << QueueC;
   std::cout << "FRONT :\t" << QueueC.front() << " (const ref)" << std::endl;
   const int &i = QueueC.front();
   // i++;                      //can't modify value
   // int &i = QueueC.front();   //can't bind to non const
   (void)i;
   std::cout << "BACK :\t" << QueueC.back() << " (const ref)" << std::endl;
   std::cout << "[expected] FRONT :\t" << realQueueC.front() << std::endl;
   std::cout << "[expected] BACK :\t" << realQueueC.back() << std::endl;
   
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

   std::cout << std::endl << std::endl;
}