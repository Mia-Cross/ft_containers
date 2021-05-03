/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 18:39:53 by schene            #+#    #+#             */
/*   Updated: 2021/05/03 21:52:51 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <queue>
# include <list>
#include <iomanip>
#include "color.h"
#include "../containers/queue.hpp"
#include "../containers/list.hpp"
#include "../containers/vector.hpp"

int		main()
{
	{
		std::cout << _CYAN << "==================== CONSTRUCTOR TEST ====================" << _END << std::endl;
		
		ft::list<std::string>							mylist;
		std::list<std::string>							list;

		mylist.push_back("salut");
		mylist.push_back("tu vas bien?");
		mylist.push_back("super");
		mylist.push_back("et toi?");

		list.push_back("salut");
		list.push_back("tu vas bien?");
		list.push_back("super");
		list.push_back("et toi?");

		ft::queue<std::string> 								myqueue(mylist);
		std::queue<std::string, std::list<std::string> >	queue(list);

		std::cout << _CYAN << "queue is construct from a list of std::string " << _END << std::endl << std::endl;
		for (int i = 0; i < 4 ; i++)
		{
			// std::cout << _YELLOW << "myqueue top -> " << _GREEN << myqueue.top() << std::endl;
			std::cout << _YELLOW << "myqueue size =  " << _GREEN << myqueue.size() << std::endl;
			// std::cout << _YELLOW << "queue top ->  " << _GREEN <<  queue.top() << std::endl;
			std::cout << _YELLOW << "queue size =  " << _GREEN <<  queue.size() << std::endl;

			myqueue.pop();
			queue.pop();

			std::cout << std::endl << _CYAN << "call to queue.pop() ..." << _END << std::endl << std::endl;
		}
		

	}
	{
		std::cout << _CYAN << "==================== EMPTY TEST ====================" << _END << std::endl;
		
		ft::queue<int> 	myqueue;
		std::queue<int> queue;
		// std::queue<int, std::list<int> > queue;
		
		std::cout << _YELLOW << "myqueue empty ? " << _GREEN <<  std::boolalpha << myqueue.empty() << std::endl;
		std::cout << _YELLOW << "queue empty ? " << _GREEN <<  std::boolalpha << queue.empty() << std::endl;


		myqueue.push(42);
		queue.push(42);
		std::cout << std::endl << _CYAN << "queue.push(42)" << _END << std::endl << std::endl;

		std::cout << _YELLOW << "myqueue empty ? " << _GREEN <<  std::boolalpha << myqueue.empty() << std::endl;
		std::cout << _YELLOW << "queue empty ? " << _GREEN <<  std::boolalpha << queue.empty() << std::endl;

		myqueue.pop();
		queue.pop();
		std::cout << std::endl << _CYAN << "queue.pop()" << _END << std::endl << std::endl;

		std::cout << _YELLOW << "myqueue empty ? " << _GREEN <<  std::boolalpha << myqueue.empty() << std::endl;
		std::cout << _YELLOW << "queue empty ? " << _GREEN <<  std::boolalpha << queue.empty() << std::endl;
	}
	{
		std::cout << _CYAN << "==================== SIZE TEST ====================" << _END << std::endl;
		
		ft::queue<int>						myqueue;
		std::queue<int>	queue;
		// std::queue<int, std::list<int> >	queue;
		
		std::cout << _YELLOW << "myqueue size =  " << _GREEN << myqueue.size() << std::endl;
		std::cout << _YELLOW << "queue size =  " << _GREEN <<  queue.size() << std::endl;

		for (int i = 0; i < 15 ; i++)
		{
			myqueue.push(i * 3 - 7);
			queue.push  (i * 3 - 7);
		}
		
		std::cout << std::endl << _CYAN << "pushing 10 int..." << _END << std::endl << std::endl;

		std::cout << _YELLOW << "myqueue size =  " << _GREEN << myqueue.size() << std::endl;
		std::cout << _YELLOW << "queue size =  " << _GREEN <<  queue.size() << std::endl;

		for (int i = 0; i < 10 ; i++)
		{
			myqueue.pop();
			queue.pop();
		}

		std::cout << std::endl << _CYAN << "poping 15 int..." << _END << std::endl << std::endl;

		std::cout << _YELLOW << "myqueue size =  " << _GREEN << myqueue.size() << std::endl;
		std::cout << _YELLOW << "queue size =  " << _GREEN <<  queue.size() << std::endl;
	}
	{
		std::cout << _CYAN << "==================== FRONT and BACK TEST ====================" << _END << std::endl;
		
		ft::queue<int>	myqueue;
		std::queue<int>	queue;
		// std::queue<int, std::list<int> >	queue;

		for (int i = 0; i < 5 ; i++)
		{
			myqueue.push(i * 3 - 7);
			queue.push  (i * 3 - 7);
		
			std::cout << std::endl << _CYAN << "pushing -> " << (i * 3 - 7) << _END << std::endl;

			std::cout << _YELLOW << "myqueue front -> " << _GREEN << myqueue.front() << std::endl;
			std::cout << _YELLOW << "myqueue back -> " << _GREEN << myqueue.back() << std::endl;
			std::cout << _YELLOW << "myqueue size =  " << _GREEN << myqueue.size() << std::endl  << std::endl;
			std::cout << _YELLOW << "queue front ->  " << _GREEN <<  queue.front() << std::endl;
			std::cout << _YELLOW << "queue back ->  " << _GREEN <<  queue.back() << std::endl;
			std::cout << _YELLOW << "queue size =  " << _GREEN <<  queue.size() << std::endl;
		}

		for (int i = 0; i < 4 ; i++)
		{
			myqueue.pop();
			queue.pop();

			std::cout << std::endl << _CYAN << "call to queue.pop() " << _END << std::endl << std::endl;

			std::cout << _YELLOW << "myqueue front -> " << _GREEN << myqueue.front() << std::endl;
			std::cout << _YELLOW << "myqueue back -> " << _GREEN << myqueue.back() << std::endl;
			std::cout << _YELLOW << "myqueue size =  " << _GREEN << myqueue.size() << std::endl  << std::endl;
			std::cout << _YELLOW << "queue front ->  " << _GREEN <<  queue.front() << std::endl;
			std::cout << _YELLOW << "queue back ->  " << _GREEN <<  queue.back() << std::endl;
			std::cout << _YELLOW << "queue size =  " << _GREEN <<  queue.size() << std::endl;
		}
	}
	{
		std::cout << _CYAN << "==================== RELATIONNAL OPERATOR TEST ====================" << _END << std::endl;
		
		ft::queue<int, ft::list<int> >	myqueue, mycomp, myqueue2;
		std::queue<int, std::list<int> >	queue, comp, queue2;

		for (int i = 0; i < 15 ; i++)
		{
			myqueue.push(i * 3 - 7);
			myqueue2.push(i * 3 - 7);
			queue.push(i * 3 - 7);
			queue2.push(i * 3 - 7);
		}

		for (int i = 0; i < 15 ; i++)
		{
			mycomp.push(i);
			comp.push  (i);
		}

		if (myqueue == myqueue2) std::cout << "myqueue and myqueue2 are equal\n";
		if (queue == queue2) std::cout << "queue and queue2 are equal\n";
		if (myqueue == mycomp) std::cout << "myqueue and mycomp are equal\n";
		if (queue == comp) std::cout << "queue and comp are equal\n";
		std::cout << std::endl;

		if (myqueue != myqueue2) std::cout << "myqueue and myqueue2 are not equal\n";
		if (queue != queue2) std::cout << "queue and queue2 are not equal\n";
		if (myqueue != mycomp) std::cout << "myqueue and mycomp are not equal\n";
		if (queue != comp) std::cout << "queue and comp are not equal\n";
		std::cout << std::endl;

		if (myqueue < myqueue2) std::cout << "myqueue is less than myqueue2\n";
		if (queue < queue2) std::cout << "queue is less than queue2\n";
		if (myqueue < mycomp) std::cout << "myqueue is less than mycomp\n";
		if (queue < comp) std::cout << "queue is less than comp\n";
		std::cout << std::endl;

		if (myqueue <= myqueue2) std::cout << "myqueue is less than or equal to myqueue2\n";
		if (queue <= queue2) std::cout << "queue is less than or equal to queue2\n";
		if (myqueue <= mycomp) std::cout << "myqueue is less than or equal to mycomp\n";
		if (queue <= comp) std::cout << "queue is less than or equal to comp\n";
		std::cout << std::endl;

		if (myqueue > myqueue2) std::cout << "myqueue is greater than myqueue2\n";
		if (queue > queue2) std::cout << "queue is greater than queue2\n";
		if (myqueue > mycomp) std::cout << "myqueue is greater than mycomp\n";
		if (queue > comp) std::cout << "queue is greater than comp\n";
		std::cout << std::endl;

		if (myqueue >= myqueue2) std::cout << "myqueue is greater than or equal to myqueue2\n";
		if (queue >= queue2) std::cout << "queue is greater than or equal to queue2\n";
		if (myqueue >= mycomp) std::cout << "myqueue is greater than or equal to mycomp\n";
		if (queue >= comp) std::cout << "queue is greater than or equal to comp\n";
		std::cout << std::endl;
	}
	return 0;
}