/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:49:51 by schene            #+#    #+#             */
/*   Updated: 2021/05/03 21:52:51 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <stack>
# include <list>
#include <iomanip>
#include "color.h"
#include "../containers/stack.hpp"
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

		ft::stack<std::string> 								mystack(mylist);
		std::stack<std::string, std::list<std::string> >	stack(list);

		std::cout << _CYAN << "stack is construct from a list of std::string " << _END << std::endl << std::endl;
		for (int i = 0; i < 4 ; i++)
		{
			std::cout << _YELLOW << "mystack top -> " << _GREEN << mystack.top() << std::endl;
			std::cout << _YELLOW << "mystack size =  " << _GREEN << mystack.size() << std::endl;
			std::cout << _YELLOW << "stack top ->  " << _GREEN <<  stack.top() << std::endl;
			std::cout << _YELLOW << "stack size =  " << _GREEN <<  stack.size() << std::endl;

			mystack.pop();
			stack.pop();

			std::cout << std::endl << _CYAN << "call to stack.pop() ..." << _END << std::endl << std::endl;
		}
		

	}
	{
		std::cout << _CYAN << "==================== EMPTY TEST ====================" << _END << std::endl;
		
		ft::stack<int> 	mystack;
		std::stack<int> stack;
		// std::stack<int, std::list<int> > stack;
		
		std::cout << _YELLOW << "mystack empty ? " << _GREEN <<  std::boolalpha << mystack.empty() << std::endl;
		std::cout << _YELLOW << "stack empty ? " << _GREEN <<  std::boolalpha << stack.empty() << std::endl;


		mystack.push(42);
		stack.push(42);
		std::cout << std::endl << _CYAN << "stack.push(42)" << _END << std::endl << std::endl;

		std::cout << _YELLOW << "mystack empty ? " << _GREEN <<  std::boolalpha << mystack.empty() << std::endl;
		std::cout << _YELLOW << "stack empty ? " << _GREEN <<  std::boolalpha << stack.empty() << std::endl;

		mystack.pop();
		stack.pop();
		std::cout << std::endl << _CYAN << "stack.pop()" << _END << std::endl << std::endl;

		std::cout << _YELLOW << "mystack empty ? " << _GREEN <<  std::boolalpha << mystack.empty() << std::endl;
		std::cout << _YELLOW << "stack empty ? " << _GREEN <<  std::boolalpha << stack.empty() << std::endl;
	}
	{
		std::cout << _CYAN << "==================== SIZE TEST ====================" << _END << std::endl;
		
		ft::stack<int>						mystack;
		std::stack<int>	stack;
		// std::stack<int, std::list<int> >	stack;
		
		std::cout << _YELLOW << "mystack size =  " << _GREEN << mystack.size() << std::endl;
		std::cout << _YELLOW << "stack size =  " << _GREEN <<  stack.size() << std::endl;

		for (int i = 0; i < 15 ; i++)
		{
			mystack.push(i * 3 - 7);
			stack.push  (i * 3 - 7);
		}
		
		std::cout << std::endl << _CYAN << "pushing 15 int..." << _END << std::endl << std::endl;

		std::cout << _YELLOW << "mystack size =  " << _GREEN << mystack.size() << std::endl;
		std::cout << _YELLOW << "stack size =  " << _GREEN <<  stack.size() << std::endl;

		for (int i = 0; i < 10 ; i++)
		{
			mystack.pop();
			stack.pop();
		}

		std::cout << std::endl << _CYAN << "poping 10 int..." << _END << std::endl << std::endl;

		std::cout << _YELLOW << "mystack size =  " << _GREEN << mystack.size() << std::endl;
		std::cout << _YELLOW << "stack size =  " << _GREEN <<  stack.size() << std::endl;
	}
	{
		std::cout << _CYAN << "==================== TOP TEST ====================" << _END << std::endl;
		
		ft::stack<int>	mystack;
		std::stack<int>	stack;
		// std::stack<int, std::list<int> >	stack;

		for (int i = 0; i < 5 ; i++)
		{
			mystack.push(i * 3 - 7);
			stack.push  (i * 3 - 7);
		
			std::cout << std::endl << _CYAN << "pushing -> " << (i * 3 - 7) << _END << std::endl;

			std::cout << _YELLOW << "mystack top -> " << _GREEN << mystack.top() << std::endl;
			std::cout << _YELLOW << "mystack size =  " << _GREEN << mystack.size() << std::endl;
			std::cout << _YELLOW << "stack top ->  " << _GREEN <<  stack.top() << std::endl;
			std::cout << _YELLOW << "stack size =  " << _GREEN <<  stack.size() << std::endl;
		}

		for (int i = 0; i < 4 ; i++)
		{
			mystack.pop();
			stack.pop();

			std::cout << std::endl << _CYAN << "call to stack.pop() " << _END << std::endl << std::endl;

			std::cout << _YELLOW << "mystack top -> " << _GREEN << mystack.top() << std::endl;
			std::cout << _YELLOW << "mystack size =  " << _GREEN << mystack.size() << std::endl;
			std::cout << _YELLOW << "stack top ->  " << _GREEN <<  stack.top() << std::endl;
			std::cout << _YELLOW << "stack size =  " << _GREEN <<  stack.size() << std::endl << _END;
		}
	}
	{
		std::cout << _CYAN << "==================== RELATIONNAL OPERATOR TEST ====================" << _END << std::endl;


		// ft::stack<int, ft::list<int> > a, b, c;

		// a.push(10);
		// a.push(20);
		// a.push(30);

		// b.push(10);
		// b.push(20);
		// b.push(30);

		// c.push(30);
		// c.push(20);
		// c.push(10);

		// if (a==b) std::cout << "a and b are equal\n";
		// if (b!=c) std::cout << "b and c are not equal\n";
		// if (b<c)  std::cout << "b is less than c\n";
		// if (c>b)  std::cout << "c is greater than b\n";
		// if (a<=b) std::cout << "a is less than or equal to b\n";
		// if (a>=b) std::cout << "a is greater than or equal to b\n";

		ft::stack<int, ft::list<int> >	mystack, mycomp, mystack2;
		std::stack<int, std::list<int> >	stack, comp, stack2;

		for (int i = 0; i < 15 ; i++)
		{
			mystack.push(i * 3 - 7);
			mystack2.push(i * 3 - 7);
			stack.push(i * 3 - 7);
			stack2.push(i * 3 - 7);
		}

		for (int i = 0; i < 15 ; i++)
		{
			mycomp.push(i);
			comp.push  (i);
		}

		if (mystack == mystack2) std::cout << "mystack and mystack2 are equal\n";
		if (stack == stack2) std::cout << "stack and stack2 are equal\n";
		if (mystack == mycomp) std::cout << "mystack and mycomp are equal\n";
		if (stack == comp) std::cout << "stack and comp are equal\n";
		std::cout << std::endl;

		if (mystack != mystack2) std::cout << "mystack and mystack2 are not equal\n";
		if (stack != stack2) std::cout << "stack and stack2 are not equal\n";
		if (mystack != mycomp) std::cout << "mystack and mycomp are not equal\n";
		if (stack != comp) std::cout << "stack and comp are not equal\n";
		std::cout << std::endl;

		if (mystack < mystack2) std::cout << "mystack is less than mystack2\n";
		if (stack < stack2) std::cout << "stack is less than stack2\n";
		if (mystack < mycomp) std::cout << "mystack is less than mycomp\n";
		if (stack < comp) std::cout << "stack is less than comp\n";
		std::cout << std::endl;

		if (mystack <= mystack2) std::cout << "mystack is less than or equal to mystack2\n";
		if (stack <= stack2) std::cout << "stack is less than or equal to stack2\n";
		if (mystack <= mycomp) std::cout << "mystack is less than or equal to mycomp\n";
		if (stack <= comp) std::cout << "stack is less than or equal to comp\n";
		std::cout << std::endl;

		if (mystack > mystack2) std::cout << "mystack is greater than mystack2\n";
		if (stack > stack2) std::cout << "stack is greater than stack2\n";
		if (mystack > mycomp) std::cout << "mystack is greater than mycomp\n";
		if (stack > comp) std::cout << "stack is greater than comp\n";
		std::cout << std::endl;

		if (mystack >= mystack2) std::cout << "mystack is greater than or equal to mystack2\n";
		if (stack >= stack2) std::cout << "stack is greater than or equal to stack2\n";
		if (mystack >= mycomp) std::cout << "mystack is greater than or equal to mycomp\n";
		if (stack >= comp) std::cout << "stack is greater than or equal to comp\n";
		std::cout << std::endl;
	}
	return 0;
}