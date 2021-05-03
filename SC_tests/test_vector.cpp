/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:13:03 by schene            #+#    #+#             */
/*   Updated: 2021/05/03 23:04:53 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <vector>
#include <limits>
#include "utils.hpp"
#include "color.h"
#include "../containers/vector.hpp"

template <class T>
void	error_diff(ft::vector<T> myv, std::vector<T> vector)
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
void	compareVector(std::string function, ft::vector<T> myv, std::vector<T> vector)
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

int 		main()
{	
	{
		std::cout << _CYAN << "==================== CONSTRUCTOR TEST ====================" << _END << std::endl;

		ft::vector<int>		myvector;
		std::vector<int>	vector;
		
		compareVector("default -> vector;", myvector, vector);
	}
	{
		ft::vector<int>		myvector(5);
		std::vector<int>	vector(5);
			
		compareVector("fill with one argument -> vector(5);", myvector, vector);
	}
	{
		ft::vector<int>		myvector(5, 42);
		std::vector<int>	vector(5, 42);
		compareVector("fill with two argument -> vector(5, 42);", myvector, vector);

		ft::vector<int>		mycopy(myvector);
		std::vector<int>	copy(vector);
		compareVector("copy -> copy(vector);", mycopy, copy);
	}
	{
		int myints[] = {566,79,42, 521, 765};
		ft::vector<int>		myvector(myints, myints + 5);
		std::vector<int>	vector(myints, myints + 5);
		compareVector("range from a tab of ints -> vector(myints, myints + 5);", myvector, vector);

		ft::vector<int>		myrange(myvector.begin() + 1, myvector.end() - 1);
		std::vector<int>	range(vector.begin() + 1, vector.end() - 1);
		compareVector("range from a vector -> range(vector.begin() + 1, vector.end() - 1);", myrange, range);
	}
	{
		std::cout << _CYAN << "==================== OPERATOR = TEST ====================" << _END << std::endl;

		ft::vector<int> my_foo(3,2);
		ft::vector<int> my_bar(5,5);

		std::vector<int> foo(3,2);
		std::vector<int> bar(5,5);

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);

		my_bar = my_foo;
		bar = foo;
		std::cout << _PURPLE << "bar = foo" << _END << std::endl;

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);
	}
	{
		std::cout << _CYAN << "==================== RBEGIN / REND TEST ====================" << _END << std::endl;
		
		ft::vector<int>		myvector(5);
		std::vector<int>	vector(5);

		compareVector("content", myvector, vector);

		ft::vector<int>::reverse_iterator	my_rit = myvector.rbegin();
		std::vector<int>::reverse_iterator	rit = vector.rbegin();
	
		int i = 0;
		for (; my_rit != myvector.rend(); ++my_rit)
			*my_rit = ++i;
		i = 0;
		for (; rit!= vector.rend(); ++rit)
			*rit = ++i;

		compareVector("after iterating from rbegin to rend", myvector, vector);
	}
	{
		std::cout << _CYAN << "==================== MAX_SIZE TEST ====================" << _END << std::endl;

		ft::vector<int>		myvector;
		std::vector<int>	vector;

		// set some content in the vector:
		for (int i=0; i<100; i++)
		{
			myvector.push_back(i);
			vector.push_back(i);
		}
		compareVector("content", myvector, vector);

		std::cout << "myvector max_size: " << myvector.max_size() << "\n";
		std::cout << "vector max_size:   " << vector.max_size() << "\n";
		
	}
	{
		std::cout << _CYAN << "==================== RESIZE TEST ====================" << _END << std::endl;
		
		ft::vector<int>		myvector;
		std::vector<int>	vector;

		// set some initial content:
		for (int i = 1; i < 10; i++)
		{
			myvector.push_back(i);
			vector.push_back(i);
		}
		compareVector("content", myvector, vector);


		myvector.resize(5);
		vector.resize(5);
		compareVector("resize(5)", myvector, vector);

		myvector.resize(8,100);
		vector.resize(8,100);
		compareVector("resize(8,100)", myvector, vector);

		myvector.resize(12);
		vector.resize(12);
		compareVector("resize(12)", myvector, vector);
	}
	{
		std::cout << _CYAN << "==================== CAPACITY TEST ====================" << _END << std::endl;

		ft::vector<int> myvector;
		std::vector<int> vector;

		// set some content in the vector:
		for (int i=0; i<100; i++)
		{
			myvector.push_back(i);
			vector.push_back(i);
		}
		compareVector("content", myvector, vector);

		std::cout << "myvector size: " << _GREEN << (int) myvector.size() << _YELLOW << std::endl;
		std::cout << "myvector capacity : " << _GREEN << (int) myvector.capacity() << _YELLOW << std::endl;

		std::cout << '\n' << "vector size: " << _GREEN  << (int) vector.size() << _YELLOW << std::endl;
		std::cout << "vector capacity : " << _GREEN  << (int) vector.capacity() << _YELLOW << std::endl;
	}
	{
		std::cout << _CYAN << "==================== EMPTY TEST ====================" << _END << std::endl;

		ft::vector<int>		myvector;
		std::vector<int>	vector;

		for (int i = 1; i <= 10; i++)
		{
			myvector.push_back(i);
			vector.push_back(i);
		}
		compareVector("content", myvector, vector);

		std::cout << _YELLOW << "is myvector empty ? "<< std::boolalpha << _GREEN << myvector.empty() << _END << std::endl;
		std::cout << _YELLOW << "is vector empty ? "<< std::boolalpha << _GREEN << vector.empty() << _END << std::endl;

		while (!myvector.empty())
			myvector.pop_back();

		while (!vector.empty())
			vector.pop_back();

		compareVector("after a loop of pop_back, vector is empty ", myvector, vector);

		std::cout << _YELLOW << "is myvector empty ? "<< std::boolalpha << _GREEN << myvector.empty() << _END << std::endl;
		std::cout << _YELLOW << "is vector empty ? "<< std::boolalpha << _GREEN << vector.empty() << _END << std::endl;
	}
	{
		std::cout << _CYAN << "==================== RESERVE TEST ====================" << _END << std::endl;

		ft::vector<int>::size_type	my_sz;
		std::vector<int>::size_type	sz;

		ft::vector<int>		my_foo;
		std::vector<int>	foo;
	
		my_sz = my_foo.capacity();
		sz = foo.capacity();

		std::cout << _PURPLE << "making my_foo grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			my_foo.push_back(i);
			// printContainer(my_foo);
			if (my_sz != my_foo.capacity())
			{
				my_sz = my_foo.capacity();
				std::cout << _YELLOW << "capacity changed: " << _GREEN << my_sz << '\n';
			}
		}

		std::cout << _PURPLE << "making foo grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			foo.push_back(i);
			if (sz != foo.capacity())
			{
				sz = foo.capacity();
				std::cout << _YELLOW << "capacity changed: " << _GREEN << sz << '\n';
			}
		}

		ft::vector<int>		my_bar;
		std::vector<int>	bar;
	
		my_sz = my_bar.capacity();
		sz = bar.capacity();

		my_bar.reserve(100);   // this is the only difference with foo above
		bar.reserve(100);   // this is the only difference with foo above
		
		std::cout << _PURPLE << "making my_bar grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			my_bar.push_back(i);
			if (my_sz != my_bar.capacity())
			{
				my_sz = my_bar.capacity();
				std::cout << _YELLOW << "capacity changed: " << _GREEN << my_sz << _END << '\n';
			}
		}
		try
		{
			my_bar.reserve(my_bar.max_size() * 2);
		}
		catch(std::exception& e) { std::cout << e.what() << std::endl; }

		std::cout << _PURPLE << "making bar grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			bar.push_back(i);
			if (sz!=bar.capacity())
			{
				sz = bar.capacity();
				std::cout << _YELLOW << "capacity changed: " << _GREEN << sz << _END << '\n';
			}
		}
		try
		{
			bar.reserve(bar.max_size() * 2);
		}
		catch(std::exception& e) { std::cout << e.what() << std::endl; }
	}
		{
		std::cout << _CYAN << "==================== OPERATOR [] TEST ====================" << _END << std::endl;

		ft::vector<int>		myvector(10); // 10 zero-initialized elements
		std::vector<int>	vector(10);

		ft::vector<int>::size_type sz = myvector.size();

		// assign some values:
		for (unsigned i = 0; i < sz; i++) 
		{
			myvector[i] = i;
			vector[i] = i;
		}

		compareVector("content", myvector, vector);

		// reverse vector using operator[]:
		for (unsigned i=0; i < sz/2; i++)
		{
			int tmp;
			tmp = myvector[sz - 1 - i];
			myvector[sz - 1 - i] = myvector[i];
			myvector[i] = tmp;
		}

		for (unsigned i=0; i < sz/2; i++)
		{
			int tmp;
			tmp = vector[sz - 1 - i];
			vector[sz - 1 - i] = vector[i];
			vector[i] = tmp;
		}
		compareVector("reverse vector using operator[]", myvector, vector);
	}
	{
		std::cout << _CYAN << "==================== AT TEST ====================" << _END << std::endl;
	
		ft::vector<int> myvector (10);   // 10 zero-initialized ints
		std::vector<int> vector (10);   // 10 zero-initialized ints

		compareVector("content after vector (10) ", myvector, vector);

		// assign some values:
		for (unsigned i=0; i < myvector.size(); i++)
		{
			myvector.at(i) = i;
			vector.at(i) = i;
		}
		compareVector("after assigning some value w/ at: ", myvector, vector);
	}
	{
		std::cout << _CYAN << "==================== FRONT and BACK TEST ====================" << _END << std::endl;

		ft::vector<int>		myvector;
		std::vector<int>	vector;

		myvector.push_back(78);
		vector.push_back(78);

		myvector.push_back(16);
		vector.push_back(16);

		compareVector("content", myvector, vector);

		std::cout << _YELLOW << "myvector.front() is " << _GREEN << myvector.front() << '\n';
		std::cout << _YELLOW << "vector.front() is " << _GREEN << vector.front() << _END <<'\n' <<'\n';
		std::cout << _YELLOW << "myvector.back() is " << _GREEN << myvector.back() << '\n';
		std::cout << _YELLOW << "vector.back() is " << _GREEN << vector.back() << _END <<'\n' <<'\n';

		myvector.front() -= myvector.back();
		vector.front() -= vector.back();
		
		compareVector("vector.front() -= vector.back()", myvector, vector);

		std::cout << _YELLOW << "myvector.front() is now " << _GREEN << myvector.front() << '\n';
		std::cout << _YELLOW << "vector.front() is now " << _GREEN << vector.front() << _END <<'\n';
		std::cout << _YELLOW << "myvector.back() is " << _GREEN << myvector.back() << '\n';
		std::cout << _YELLOW << "vector.back() is " << _GREEN << vector.back() << _END <<'\n' <<'\n';

		myvector.push_back(42);
		vector.push_back(42);
		compareVector("vector.push_back(42)", myvector, vector);

		std::cout << _YELLOW << "myvector.front() is now " << _GREEN << myvector.front() << '\n';
		std::cout << _YELLOW << "vector.front() is now " << _GREEN << vector.front() << _END <<'\n';
		std::cout << _YELLOW << "myvector.back() is " << _GREEN << myvector.back() << '\n';
		std::cout << _YELLOW << "vector.back() is " << _GREEN << vector.back() << _END <<'\n' <<'\n';
	}
	{
		std::cout << _CYAN << "==================== ASSIGN TEST ====================" << _END << std::endl;

		ft::vector<int> first;
		ft::vector<int> second;
		ft::vector<int> third;

		std::vector<int> stl_first;
		std::vector<int> stl_second;
		std::vector<int> stl_third;

		first.assign (7,100);             // 7 ints with a value of 100
		stl_first.assign (7,100);             // 7 ints with a value of 100

		ft::vector<int>::iterator it;
		it = first.begin()+1;
		std::vector<int>::iterator stl_it;
		stl_it = stl_first.begin()+1;

		second.assign (it,first.end()-1); 	// the 5 central values of first
		stl_second.assign (stl_it,stl_first.end()-1); // the 5 central values of first

		int myints[] = {1776,7,4};
		third.assign (myints, myints+3);   // assigning from array.
		stl_third.assign (myints, myints+3);   // assigning from array.

		compareVector("first.assign (7,100)", first, stl_first);
		compareVector("second.assign (it,first.end()-1)", second, stl_second);
		compareVector("third.assign (myints, myints+3)", third, stl_third);
	}
	{
		std::cout << _CYAN << "==================== PUSH_BACK TEST ====================" << _END << std::endl;

		ft::vector<int> myvector;
		std::vector<int> vector;

		myvector.push_back(10);
		vector.push_back(10);

		while (myvector.back() != 0 && vector.back() != 0)
		{
			myvector.push_back ( myvector.back() -1 );
			vector.push_back ( vector.back() -1 );
		}
		compareVector("after a loop of vector.push_back", myvector, vector);
	}
	{
		std::cout << _CYAN << "==================== PUSH_BACK TEST 2====================" << _END << std::endl;

		ft::vector<int>		myvector;
		std::vector<int>	vector;
		int myint = 42;

		do {
			myint += 5;
			myint /= 9;
			myint -= 2;
			myint *= 42;
			myvector.push_back (myint);
			vector.push_back (myint);
		} while (myint < 1000000);

		compareVector("after a loop of push_back", myvector, vector);
		std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
		std::cout << "vector stores " << int(vector.size()) << " numbers.\n";
	}
	{
		std::cout << _CYAN << "==================== POP_BACK TEST ====================" << _END << std::endl;

		ft::vector<int>		myvector;
		std::vector<int>	vector;
		int sum (0);

		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);

		vector.push_back (100);
		vector.push_back (200);
		vector.push_back (300);

		compareVector("content", myvector, vector);

		while (!myvector.empty())
		{
			sum+=myvector.back();
			myvector.pop_back();
		}
		std::cout << _YELLOW << "The elements of myvector add up to " << sum << '\n';

		sum = 0;
		while (!vector.empty())
		{
			sum += vector.back();
			vector.pop_back();
		}

		std::cout << "The elements of vector add up to " << sum << _END << '\n' << '\n';

		compareVector("after a loop of pop_back", myvector, vector);
	}
	{
		std::cout << _CYAN << "==================== INSERT TEST ====================" << _END << std::endl;

		ft::vector<int>		myvector(3,100);
		std::vector<int>	vector(3,100);
		
		compareVector("content", myvector, vector);

		ft::vector<int>::iterator my_it;
		std::vector<int>::iterator it;

		my_it = myvector.begin()++;
		it = vector.begin()++;
		// my_it = ++myvector.begin();
		// it = ++vector.begin();
		my_it = myvector.insert (my_it , 200);
		it = vector.insert (it , 200);

		compareVector("vector.insert ( it , 200 )", myvector, vector);

std::cout << "hey" << std::endl;
		myvector.insert (my_it, 2, 300);
std::cout << "yo" << std::endl;
		vector.insert (it, 2, 300);
		compareVector("vector.insert (it, 2, 300)", myvector, vector);
// 		// "it" no longer valid, get a new one:
		my_it = myvector.begin();
		it = vector.begin();

		ft::vector<int> my_anothervector (2,400);
		std::vector<int> anothervector (2,400);

		myvector.insert (my_it + 2, my_anothervector.begin(), my_anothervector.end());
		vector.insert (it + 2, anothervector.begin(), anothervector.end());
		compareVector("vector.insert (it + 2, anothervector.begin(), anothervector.end())", myvector, vector);

		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);
		vector.insert (vector.begin(), myarray, myarray+3);

		compareVector("vector.insert(vector.begin(), myarray, myarray+3)", myvector, vector);
	}
	{
		std::cout << _CYAN << "==================== ERASE TEST ====================" << _END << std::endl;

		ft::vector<int>		myvector;
		std::vector<int>	vector;

		// set some values (from 1 to 10)
		for (int i=1; i<=10; i++)
		{
			myvector.push_back(i);
			vector.push_back(i);
		}

		compareVector("set some values (from 1 to 10)", myvector, vector);

		// erase the 6th element
		myvector.erase (myvector.begin()+5);
		vector.erase (vector.begin()+5);

		compareVector("erase the 6th element", myvector, vector);

		// erase the first 3 elements:
		myvector.erase (myvector.begin(),myvector.begin()+3);
		vector.erase (vector.begin(),vector.begin()+3);

		compareVector("erase the first 3 elements", myvector, vector);
	}
	{
		std::cout << _CYAN << "==================== MEMBER SWAP TEST ====================" << _END << std::endl;

		// unsigned int i;
		ft::vector<int>		my_foo (3,100);   // three ints with a value of 100
		ft::vector<int>		my_bar (5,200);   // five ints with a value of 200

		std::vector<int>	foo (3,100);   // three ints with a value of 100
  		std::vector<int>	bar (5,200);   // five ints with a value of 200

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);
		
		my_foo.swap(my_bar);
		foo.swap(bar);

		std::cout << _PURPLE << "foo.swap(bar)" << _END << std::endl;

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);
	}
	{
		std::cout << _CYAN << "==================== CLEAR TEST ====================" << _END << std::endl;

		ft::vector<int> myvector;
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);

		std::vector<int> vector;
		vector.push_back (100);
		vector.push_back (200);
		vector.push_back (300);

		compareVector("content", myvector, vector);

		myvector.clear();
		vector.clear();
		compareVector("after a clear", myvector, vector);

	
		myvector.push_back (1101);
		myvector.push_back (2202);
		vector.push_back (1101);
		vector.push_back (2202);

		compareVector("after 2 push_back", myvector, vector);
		
		myvector.clear();
		vector.clear();
		compareVector("after another clear", myvector, vector);
	}
	{
		std::cout << _CYAN << "==================== RELATIONNAL OPERATOR TEST ====================" << _END << std::endl;
		
		ft::vector<int> my_foo(3,100);
		ft::vector<int> my_bar(2,200);

		std::vector<int> foo(3,100);
		std::vector<int> bar(2,200);

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);

		if (my_foo == my_bar) std::cout << "my_foo and my_bar are equal\n";
		if (my_foo != my_bar) std::cout << "my_foo and my_bar are not equal\n";
		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		std::cout << std::endl;
		
		if (my_foo <  my_bar) std::cout << "my_foo is less than my_bar\n";
		if (my_foo >  my_bar) std::cout << "my_foo is greater than my_bar\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		std::cout << std::endl;

		if (my_foo <= my_bar) std::cout << "my_foo is less than or equal to my_bar\n";
		if (my_foo >= my_bar) std::cout << "my_foo is greater than or equal to my_bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

		my_foo = my_bar;
		foo = bar;
		std::cout << _PURPLE << "foo = bar" << _END << std::endl;

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);

		if (my_foo == my_bar) std::cout << "my_foo and my_bar are equal\n";
		if (my_foo != my_bar) std::cout << "my_foo and my_bar are not equal\n";
		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		std::cout << std::endl;
		
		if (my_foo <  my_bar) std::cout << "my_foo is less than my_bar\n";
		if (my_foo >  my_bar) std::cout << "my_foo is greater than my_bar\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		std::cout << std::endl;

		if (my_foo <= my_bar) std::cout << "my_foo is less than or equal to my_bar\n";
		if (my_foo >= my_bar) std::cout << "my_foo is greater than or equal to my_bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	{
		std::cout << _CYAN << "==================== NON MEMBER SWAP TEST ====================" << _END << std::endl;

		// unsigned int i;
		ft::vector<int>		my_foo (3,100);   // three ints with a value of 100
		ft::vector<int>		my_bar (5,200);   // five ints with a value of 200

		std::vector<int>	foo (3,100);   // three ints with a value of 100
  		std::vector<int>	bar (5,200);   // five ints with a value of 200

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);
		
		swap(my_foo, my_bar);
		swap(foo, bar);

		std::cout << _PURPLE << "swap(foo, bar)" << _END << std::endl;

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);
	}
	test_vector_string();
	return 0;
}