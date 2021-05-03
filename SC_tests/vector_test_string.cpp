/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test_string.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:51:30 by schene            #+#    #+#             */
/*   Updated: 2021/05/03 21:52:51 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <vector>
#include <limits>
#include "utils.hpp"
#include "color.h"
#include "../containers/vector.hpp"

template <class T>
void	error_diff(ft::vector<T> &myv, std::vector<T> vector)
{
	std::cout << _RED << "ERROR - DIFF" << _END << std::endl;
	std::cout << std::setw(30) << "myv.empty(): " << myv.empty() << std::endl;
	std::cout << std::setw(30) << "vector.empty(): " << vector.empty() << std::endl;
	std::cout << std::setw(30) << "myv.size(): " << myv.size() << std::endl;
	std::cout << std::setw(30) << "vector.size(): " << vector.size() << std::endl;
	std::cout << std::setw(30) << "myv : ";
	printContainer(myv);
	std::cout << std::setw(30) << "vector : ";
	printContainer(vector);
}

template <class T>
void	compareVector(std::string function, ft::vector<T> &myv, std::vector<T> vector)
{
	std::cout << std::setw(30) << function << ": ";
	if (myv.empty() != vector.empty())
	{
		error_diff(myv, vector);
	}	
	else if (myv.size() != vector.size())
	{
		error_diff(myv, vector);
	}
	else
	{
		typename ft::vector<T>::iterator	my_it;
		typename std::vector<T>::iterator	i;
		my_it = myv.begin();
		i = vector.begin();
		while (i != vector.end())
		{
			if (*i != *my_it)
			{
				error_diff(myv, vector);
				return ;
			}
			i++;
			my_it++;
		}
		
		std::cout << _GREEN << "OK " << _END << std::endl;
		std::cout << _YELLOW << "myvect";
		printContainer(myv);
		std::cout << _YELLOW<< "vector";
		printContainer(vector);
	}
}

void	test_vector_string()
{
	std::cout << _CYAN << "==================== CONSTRUCTOR ====================" << _END << std::endl;

	ft::vector<std::string> myJOHN;
	std::vector<std::string> JOHN;
	compareVector("[JOHN] default constructor", myJOHN, JOHN);
	
	ft::vector<std::string> myBOB(5, "Hello");
	std::vector<std::string> BOB(5, "Hello");
	compareVector("[BOB] fill constructor", myBOB, BOB);
	
	ft::vector<std::string> myMIKE(myBOB);
	std::vector<std::string> MIKE(BOB);
	compareVector("[MIKE] copy constructor", myMIKE, MIKE);
	
	std::cout << "myJOHN is empty ? " << std::boolalpha << myJOHN.empty() << '\n';
	std::cout << "JOHN is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	std::cout << "Size of myJOHN " << myJOHN.size() << std::endl;
	std::cout << "Size of JOHN " << JOHN.size() << std::endl << std::endl;
	
	std::cout << "myBOB is empty? " << myBOB.empty() << '\n';
	std::cout << "BOB is empty? " << BOB.empty() << '\n';
	std::cout << "Size of myBOB " << myBOB.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl << std::endl;

	std::cout << "Size of myMIKE " << myMIKE.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;

	std::cout << _CYAN << "==================== RESIZE ====================" << _END << std::endl;

	std::cout << "Size of myBOB " << myBOB.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl << std::endl;

	size_t	bob_resize = 2;
	myBOB.resize(bob_resize);
	BOB.resize(bob_resize);

	
	compareVector("BOB.resize(2)", myBOB, BOB);
	std::cout << "Size of myBOB " << myBOB.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl << std::endl;

	std::cout << "myBOB is empty now ? " << myBOB.empty() << '\n';
	std::cout << "BOB is empty now ? " << BOB.empty() << '\n' << '\n';

	size_t	mike_resize = 9;

	myMIKE.resize(mike_resize, "World");
	MIKE.resize(mike_resize, "World");
	compareVector("MIKE.resize(9, World)", myMIKE, MIKE);
	std::cout << "Size of myMIKE " << myMIKE.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	std::cout << "Capacity of myMIKE " << myMIKE.capacity() << std::endl;
	std::cout << "Capacity of MIKE " << MIKE.capacity() << std::endl;

	std::cout << _CYAN << "==================== RESERVE ====================" << _END << std::endl;

	compareVector("JOHN", myJOHN, JOHN);

	size_t	john_reserve = 5;
	size_t	bob_reserve = 3;
	size_t	mike_reserve = 83;

	std::cout << "Size of myJOHN " << _GREEN <<  myJOHN.size() << _END << std::endl;
	std::cout << "Capacity of myJOHN " << _GREEN <<  myJOHN.capacity() << _END <<  std::endl;
	std::cout << "Size of JOHN " << _GREEN <<  JOHN.size() << _END <<  std::endl;
	std::cout << "Capacity of JOHN " << _GREEN <<  JOHN.capacity() << _END << std::endl;
	myJOHN.reserve(john_reserve);
	JOHN.reserve(john_reserve);
	compareVector("JOHN.reserve(5) ", myJOHN, JOHN);
	std::cout << "Size of myJOHN " << _GREEN <<  myJOHN.size() << _END << std::endl;
	std::cout << "Capacity of myJOHN " << _GREEN <<  myJOHN.capacity() << _END <<  std::endl;
	std::cout << "Size of JOHN " << _GREEN <<  JOHN.size() << _END <<  std::endl;
	std::cout << "Capacity of JOHN " << _GREEN <<  JOHN.capacity() << _END << std::endl << std::endl;

	compareVector("BOB", myBOB, BOB);
	
	std::cout << "Size of myBOB " << _GREEN <<  myBOB.size() << _END << std::endl;
	std::cout << "Capacity of myBOB " << _GREEN <<  myBOB.capacity() << _END <<  std::endl;
	std::cout << "Size of BOB " << _GREEN <<  BOB.size() << _END <<  std::endl;
	std::cout << "Capacity of BOB " << _GREEN <<  BOB.capacity() << _END << std::endl ;
	myBOB.reserve(bob_reserve);
	BOB.reserve(bob_reserve);
	compareVector("BOB.reserve(3)", myBOB, BOB);
	std::cout << "Size of myBOB " << _GREEN <<  myBOB.size() << _END << std::endl;
	std::cout << "Capacity of myBOB " << _GREEN <<  myBOB.capacity() << _END <<  std::endl;
	std::cout << "Size of BOB " << _GREEN <<  BOB.size() << _END <<  std::endl;
	std::cout << "Capacity of BOB " << _GREEN <<  BOB.capacity() << _END << std::endl << std::endl;

	compareVector("MIKE", myMIKE, MIKE);
	std::cout << "Size of myMIK " << _GREEN <<  myMIKE.size() << _END << std::endl;
	std::cout << "Capacity of myMIKE " << _GREEN <<  myMIKE.capacity() << _END <<  std::endl;
	std::cout << "Size of MIKE " << _GREEN <<  MIKE.size() << _END <<  std::endl;
	std::cout << "Capacity of MIKE " << _GREEN <<  MIKE.capacity() << _END << std::endl;
	myMIKE.reserve(mike_reserve);
	MIKE.reserve(mike_reserve);
	compareVector("MIKE.reserve(83)", myMIKE, MIKE);
	std::cout << "Size of myMIKE " << _GREEN <<  myMIKE.size() << _END << std::endl;
	std::cout << "Capacity of myMIKE " << _GREEN <<  myMIKE.capacity() << _END <<  std::endl;
	std::cout << "Size of MIKE " << _GREEN <<  MIKE.size() << _END <<  std::endl;
	std::cout << "Capacity of MIKE " << _GREEN <<  MIKE.capacity() << _END << std::endl;

	std::cout << _CYAN << "==================== AT ====================" << _END << std::endl;

	try
	{
		std::cout << _YELLOW << "trying to access myMIKE.at(2)..." << _END << '\n';
		std::cout << myMIKE.at(2) << '\n';
		std::cout << _YELLOW << "trying to access myMIKE.at(87)..." << _END << '\n';
		std::cout << myMIKE.at(87) << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		std::cout << "OUT OF RANGE error caught\n";
	}

	std::cout << std::endl;
	
	try
	{
		std::cout << _YELLOW << "trying to access MIKE.at(2)..." << _END << '\n';
		std::cout << MIKE.at(2) << '\n';
		std::cout << _YELLOW << "trying to access MIKE.at(87)..." << _END << '\n';
		std::cout << MIKE.at(87) << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		std::cout << "OUT OF RANGE error caught\n";
	}

	std::cout << _CYAN << "==================== FRONT / BACK ====================" << _END << std::endl;
	
	std::cout << "front() of myMIKE : " << _GREEN << myMIKE.front() << _END << '\n';
	std::cout << "back() of myMIKE : "  << _GREEN << myMIKE.back() << _END<< '\n'<< '\n';
	std::cout << "front() of MIKE : " << _GREEN << MIKE.front() << _END << '\n';
	std::cout << "back() of MIKE : "  << _GREEN << MIKE.back() << _END<< '\n';

	std::cout << _CYAN << "==================== ASSIGN ====================" << _END << std::endl;

	compareVector("BOB", myBOB, BOB);
	myBOB.assign(42, "coding is fun");
	BOB.assign(42, "coding is fun");
	compareVector("BOB.assign(42, coding is fun)", myBOB, BOB);


	std::cout << _CYAN << "==================== ASSIGN RANGE ====================" << _END << std::endl;

	ft::vector<std::string>		my_assign_range(8, "blablabla");
	std::vector<std::string>	assign_range(8, "blablabla");
	
	compareVector("(constructor) assign_range(8, blablabla)", my_assign_range, assign_range);

	my_assign_range.assign(myBOB.begin() + 1, myBOB.begin() + 10);
	assign_range.assign(BOB.begin() + 1, BOB.begin() + 10);
	compareVector("assign_range.assign(BOB.begin() + 1, BOB.end() - 30)", my_assign_range, assign_range);

	std::cout << _CYAN << "==================== EMPTY ====================" << _END << std::endl;

	std::cout << "myBOB is empty ? " << _GREEN << myBOB.empty() << _END << '\n';
	std::cout << "BOB is empty ? " << _GREEN << BOB.empty() << _END << '\n' << '\n';

	std::cout << "myJOHN is empty ? " << _GREEN << myJOHN.empty() << _END << '\n';
	std::cout << "JOHN is empty ? " << _GREEN << JOHN.empty() << _END << '\n';

	std::cout << _CYAN << "==================== PUSH / POP_BACK ====================" << _END << std::endl;

	myBOB.push_back("I mean..");
	std::cout << "myBOB.push_back(I mean..)" << std::endl;
	std::cout << "last elem of myBOB : " << _YELLOW << myBOB.back() << _END  << '\n';
	myBOB.pop_back();
	std::cout << "myBOB.pop_back()" << std::endl;
	std::cout << "last elem of myBOB : " << _YELLOW << myBOB.back() << _END << '\n' << '\n';

	BOB.push_back("I mean..");
	std::cout << "BOB.push_back(I mean..)" << std::endl;
	std::cout << "last elem of BOB : " << _YELLOW << BOB.back() << _END << '\n';
	BOB.pop_back();
	std::cout << "BOB.pop_back()" << std::endl;
	std::cout << "last elem of BOB : " << _YELLOW << BOB.back() << _END << '\n';

	std::cout << _CYAN << "==================== INSERT ====================" << _END << std::endl;

	ft::vector<std::string>		my_insert_in_me;
	std::vector<std::string>	insert_in_me;

	for (size_t i = 0; i < 15; i++)
	{
		my_insert_in_me.push_back("HELLO");
		insert_in_me.push_back("HELLO");
	}
	compareVector("content of insert_in_me", my_insert_in_me, insert_in_me);

	ft::vector<std::string>::iterator	mytmp;
	std::vector<std::string>::iterator	tmp;
	mytmp = my_insert_in_me.begin() + 4;
	tmp = insert_in_me.begin() + 4;
	my_insert_in_me.insert(mytmp, 8, "Norminet");
	insert_in_me.insert(tmp, 8, "Norminet");
	compareVector("insert_in_me.insert(tmp, 8, Norminet);", my_insert_in_me, insert_in_me);

	std::cout << _CYAN << "==================== INSERT RANGE ====================" << _END << std::endl;
	
	compareVector("MIKE", myMIKE, MIKE);
	myMIKE.insert(myMIKE.begin() + 3, my_insert_in_me.begin(), my_insert_in_me.end());
	MIKE.insert(MIKE.begin() + 3, insert_in_me.begin(), insert_in_me.end());
	compareVector("MIKE.insert(MIKE.begin() + 3, insert_in_me.begin(), insert_in_me.end())", myMIKE, MIKE);

	std::cout << _CYAN << "==================== ERASE ====================" << _END << std::endl;

	myMIKE.erase(--myMIKE.end());
	MIKE.erase(--MIKE.end());
	compareVector("MIKE.erase(--MIKE.end())", myMIKE, MIKE);

	std::cout << _CYAN << "==================== ERASE RANGE ====================" << _END << std::endl;

	myMIKE.erase(myMIKE.begin(), myMIKE.begin() + 7);
	MIKE.erase(MIKE.begin(), MIKE.begin() + 7);
	compareVector("MIKE.erase(MIKE.begin(), MIKE.begin() + 7)", myMIKE, MIKE);

	std::cout << _CYAN << "==================== SWAP ====================" << _END << std::endl;
	
	compareVector("[JOHN]", myJOHN, JOHN);
	std::cout << "[size] myJOHN = " << myJOHN.size() << " JOHN = " << JOHN.size() << std::endl;
	std::cout << "[capacity] myJOHN = " << myJOHN.capacity() << " JOHN = " << JOHN.capacity() << std::endl;
	compareVector("[BOB]", myBOB, BOB);
	std::cout << "[size] myBOB = " << myBOB.size() << " BOB = " << BOB.size() << std::endl;
	std::cout << "[capacity] myBOB = " << myBOB.capacity() << " BOB = " << BOB.capacity() << std::endl;

	
	myJOHN.swap(myBOB);
	JOHN.swap(BOB);
	std::cout << std::endl << _YELLOW << "JOHN.swap(BOB)" << _END << std::endl << std::endl;
	
	compareVector("[JOHN]", myJOHN, JOHN);
	std::cout << "[size] myJOHN = " << myJOHN.size() << " JOHN = " << JOHN.size() << std::endl;
	std::cout << "[capacity] myJOHN = " << myJOHN.capacity() << " JOHN = " << JOHN.capacity() << std::endl;
	compareVector("[BOB]", myBOB, BOB);
	std::cout << "[size] myBOB = " << myBOB.size() << " BOB = " << BOB.size() << std::endl;
	std::cout << "[capacity] myBOB = " << myBOB.capacity() << " BOB = " << BOB.capacity() << std::endl;

	compareVector("[JOHN]", myJOHN, JOHN);
	std::cout << "[size] myJOHN = " << myJOHN.size() << " JOHN = " << JOHN.size() << std::endl;
	std::cout << "[capacity] myJOHN = " << myJOHN.capacity() << " JOHN = " << JOHN.capacity() << std::endl;
	compareVector("[MIKE]", myMIKE, MIKE);
	std::cout << "[size] myMIKE = " << myMIKE.size() << " MIKE = " << MIKE.size() << std::endl;
	std::cout << "[capacity] myMIKE = " << myMIKE.capacity() << " MIKE = " << MIKE.capacity() << std::endl;
	
	myMIKE.swap(myJOHN);
	MIKE.swap(JOHN);
	std::cout << std::endl << _YELLOW << "MIKE.swap(JOHN)" << _END << std::endl << std::endl;
	
	compareVector("[JOHN]", myJOHN, JOHN);
	std::cout << "[size] myJOHN = " << myJOHN.size() << " JOHN = " << JOHN.size() << std::endl;
	std::cout << "[capacity] myJOHN = " << myJOHN.capacity() << " JOHN = " << JOHN.capacity() << std::endl;
	compareVector("[MIKE]", myMIKE, MIKE);
	std::cout << "[size] myMIKE = " << myMIKE.size() << " MIKE = " << MIKE.size() << std::endl;
	std::cout << "[capacity] myMIKE = " << myMIKE.capacity() << " MIKE = " << MIKE.capacity() << std::endl;
	
	std::cout << _CYAN << "==================== CLEAR ====================" << _END << std::endl;

	myJOHN.clear();
	JOHN.clear();

	std::cout << std::endl << _YELLOW << "JOHN.clear()" << _END << std::endl;

	compareVector("[JOHN]", myJOHN, JOHN);
	std::cout << "[size] myJOHN = " << myJOHN.size() << " JOHN = " << JOHN.size() << std::endl;
	std::cout << "[capacity] myJOHN = " << myJOHN.capacity() << " JOHN = " << JOHN.capacity() << std::endl;
	
	std::cout << _CYAN << "==================== NON MEMBER Functions ====================" << _END << std::endl;

	std::cout << _CYAN << "----- SWAP -----" << _END << std::endl;

	compareVector("[BOB]", myBOB, BOB);
	std::cout << "[size] myBOB = " << myBOB.size() << " BOB = " << BOB.size() << std::endl;
	std::cout << "[capacity] myBOB = " << myBOB.capacity() << " BOB = " << BOB.capacity() << std::endl;
	compareVector("[MIKE]", myMIKE, MIKE);
	std::cout << "[size] myMIKE = " << myMIKE.size() << " MIKE = " << MIKE.size() << std::endl;
	std::cout << "[capacity] myMIKE = " << myMIKE.capacity() << " MIKE = " << MIKE.capacity() << std::endl;

	swap(myBOB, myMIKE);
	swap(BOB, MIKE);

	std::cout << std::endl << _YELLOW << "swap(BOB, MIKE)" << _END << std::endl;

	compareVector("[BOB]", myBOB, BOB);
	std::cout << "[size] myBOB = " << myBOB.size() << " BOB = " << BOB.size() << std::endl;
	std::cout << "[capacity] myBOB = " << myBOB.capacity() << " BOB = " << BOB.capacity() << std::endl;
	compareVector("[MIKE]", myMIKE, MIKE);
	std::cout << "[size] myMIKE = " << myMIKE.size() << " MIKE = " << MIKE.size() << std::endl;
	std::cout << "[capacity] myMIKE = " << myMIKE.capacity() << " MIKE = " << MIKE.capacity() << std::endl;

	std::cout << _CYAN << "----- RELATIONAL OPERATORS -----" << _END << std::endl;
	
	myMIKE.assign(5, "Hello");
	MIKE.assign(5, "Hello");
	myJOHN.assign(5, "hello");
	JOHN.assign(5, "hello");

	compareVector("[JOHN]", myJOHN, JOHN);
	std::cout << "[size] myJOHN = " << myJOHN.size() << " JOHN = " << JOHN.size() << std::endl;
	std::cout << "[capacity] myJOHN = " << myJOHN.capacity() << " JOHN = " << JOHN.capacity() << std::endl;
	compareVector("[MIKE]", myMIKE, MIKE);
	std::cout << "[size] myMIKE = " << myMIKE.size() << " MIKE = " << MIKE.size() << std::endl;
	std::cout << "[capacity] myMIKE = " << myMIKE.capacity() << " MIKE = " << MIKE.capacity() << std::endl << std::endl;

	std::cout << _CYAN << "myMIKE == myJOHN ? " << _GREEN << std::boolalpha << (myMIKE == myJOHN) << std::endl;
	std::cout << _CYAN << "MIKE == JOHN ? " << _GREEN << std::boolalpha << (MIKE == JOHN) << std::endl << std::endl;

	std::cout << _CYAN << "myMIKE != myJOHN ? " << _GREEN << std::boolalpha << (myMIKE != myJOHN) << std::endl;
	std::cout << _CYAN << "MIKE != JOHN ? " << _GREEN << std::boolalpha << (MIKE != JOHN) << std::endl << std::endl;
	
	std::cout << _CYAN << "myMIKE > myJOHN ? " << _GREEN << std::boolalpha << (myMIKE > myJOHN) << std::endl;
	std::cout << _CYAN << "MIKE > JOHN ? " << _GREEN << std::boolalpha << (MIKE > JOHN) << std::endl << std::endl;

	std::cout << _CYAN << "myMIKE >= myJOHN ? " << _GREEN << std::boolalpha << (myMIKE >= myJOHN) << std::endl;
	std::cout << _CYAN << "MIKE >= JOHN ? " << _GREEN << std::boolalpha << (MIKE >= JOHN) << std::endl << std::endl;

	std::cout << _CYAN << "myMIKE < myJOHN ? " << _GREEN << std::boolalpha << (myMIKE < myJOHN) << std::endl;
	std::cout << _CYAN << "MIKE < JOHN ? " << _GREEN << std::boolalpha << (MIKE < JOHN) << std::endl << std::endl;

	std::cout << _CYAN << "myMIKE <= myJOHN ? " << _GREEN << std::boolalpha << (myMIKE <= myJOHN) << std::endl;
	std::cout << _CYAN << "MIKE <= JOHN ? " << _GREEN << std::boolalpha << (MIKE <= JOHN) << std::endl << std::endl << _END;

}
