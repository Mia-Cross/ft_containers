/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:03:28 by schene            #+#    #+#             */
/*   Updated: 2021/05/03 21:49:00 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <list>
#include <tgmath.h>
#include <limits>
#include <functional>
#include "utils.hpp"
#include "color.h"
#include "../containers/list.hpp"

template <class T>
void	error_diff(ft::list<T> &mylst, std::list<T> &list)
{
	std::cout << _RED << "ERROR - DIFF" << _END << std::endl;
	std::cout << std::setw(30) << "mylst.empty(): " << mylst.empty() << std::endl;
	std::cout << std::setw(30) << "list.empty(): " << list.empty() << std::endl;
	std::cout << std::setw(30) << "mylst.size(): " << mylst.size() << std::endl;
	std::cout << std::setw(30) << "list.size(): " << list.size() << std::endl;
	std::cout << std::setw(30) << "mylst : ";
	printContainer(mylst);
	std::cout << std::setw(30) << "list : ";
	printContainer(list);
}

template <class T>
void	compareList(std::string function, ft::list<T> &mylst, std::list<T> &list)
{
	std::cout << std::setw(30) << function << ": ";
	if (mylst.empty() != list.empty())
		error_diff(mylst, list);
	else if (mylst.size() != list.size())
		error_diff(mylst, list);
	else
	{
		typename ft::list<T>::iterator	my_it;
		typename std::list<T>::iterator	i;
		my_it = mylst.begin();
		i = list.begin();
		while (i != list.end())
		{
			if (*i != *my_it)
			{
				error_diff(mylst, list);
				return ;
			}
			i++;
			my_it++;
		}
		
		std::cout << _GREEN << "OK " << _END << std::endl;
		std::cout << _YELLOW << "mylst   ";
		printContainer(mylst);
		std::cout << _YELLOW<< "list";
		printContainer(list);
	}
}

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value < 10); }
bool too_high (const int& value) { return (value > 2147483647); }
bool first_b (const std::string& value) { return (value[0] == 'b'); }

// a predicate implemented as a class:
struct is_odd {
  bool operator() (const int& value) { return (value % 2) == 1; }
};

bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

int		main(void)
{
	std::cout << _CYAN << "==================== CONSTRUCTOR TEST ====================" << _END << std::endl;
	{
		ft::list<int>	mylist;
		std::list<int>	list;

		compareList("default -> list;", mylist, list);
	}
	{
		ft::list<int>	mylist(5);
		std::list<int>	list(5);
		
		compareList("fill with one argument -> list(5);", mylist, list);
	}
	{
		ft::list<int>	mylist(5, 42);
		std::list<int>	list(5, 42);
		
		compareList("fill with one argument -> list(5, 42);", mylist, list);
		
		ft::list<int>		mycopy(mylist);
		std::list<int>		copy(list);
		compareList("copy -> copy(list);", mycopy, copy);
	}
	{
		int myints[] = {566,79,42, 521, 765};
		ft::list<int>		mylist(myints, myints + 5);
		std::list<int>	list(myints, myints + 5);
		compareList("range from a tab of ints -> list(myints, myints + 5);", mylist, list);

		ft::list<int>		myrange(++mylist.begin(), --mylist.end());
		std::list<int>		range(++list.begin(), --list.end());
		compareList("range from a list -> range(++list.begin(), --list.end());", myrange, range);
	}
	{
		std::cout << _CYAN << "==================== OPERATOR = TEST ====================" << _END << std::endl;

		ft::list<int> my_foo(3,2);
		ft::list<int> my_bar(5,5);

		std::list<int> foo(3,2);
		std::list<int> bar(5,5);

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
		
		ft::list<int>		mylist;
		std::list<int>		list;

		for (int i = 0; i < 10; ++i)
		{
			mylist.push_back(i);
			list.push_back(i);
		}

		compareList("content", mylist, list);

		ft::list<int>::reverse_iterator		my_rit = mylist.rbegin();
		std::list<int>::reverse_iterator	rit = list.rbegin();
	
		std::cout << _YELLOW << "let's print mylist from rbegin through rend" << _END << std::endl;
		while (my_rit != mylist.rend())
			std::cout << *my_rit++ << ' ';
		std::cout << std::endl << std::endl;
		std::cout << _YELLOW << "let's print list from rbegin through rend"<< _END << std::endl;
		while (rit != list.rend())
			std::cout << *rit++ << ' ';
		std::cout << std::endl;
	}
	{
		std::cout << _CYAN << "==================== MAX_SIZE TEST ====================" << _END << std::endl;

		ft::list<int>		mylist;
		std::list<int>	list;

		// set some content in the list:
		for (int i=0; i<100; i++)
		{
			mylist.push_back(i);
			list.push_back(i);
		}
		compareList("content", mylist, list);
		
		std::cout << "\n" << "mylist max_size: " << mylist.max_size() << "\n";
		std::cout << "list max_size: " << list.max_size() << "\n";	
	}
	{
		std::cout << _CYAN << "==================== RESIZE TEST ====================" << _END << std::endl;
		
		ft::list<int>		mylist;
		std::list<int>	list;

		// set some initial content:
		for (int i = 1; i < 10; i++)
		{
			mylist.push_back(i);
			list.push_back(i);
		}
		compareList("content", mylist, list);


		mylist.resize(5);
		list.resize(5);
		compareList("resize(5)", mylist, list);

		mylist.resize(8,100);
		list.resize(8,100);
		compareList("resize(8,100)", mylist, list);

		mylist.resize(12);
		list.resize(12);
		compareList("resize(12)", mylist, list);
	}
	{
		std::cout << _CYAN << "==================== EMPTY TEST ====================" << _END << std::endl;

		ft::list<int>	mylist;
		std::list<int>	list;

		for (int i = 1; i <= 10; i++)
		{
			mylist.push_back(i);
			list.push_back(i);
		}
		compareList("content ", mylist, list);
		std::cout << _YELLOW << "is mylist empty ? "<< std::boolalpha << _GREEN << mylist.empty() << _END << std::endl;
		std::cout << _YELLOW << "is list empty ? "<< std::boolalpha << _GREEN << list.empty() << _END << std::endl << std::endl;

		while (!mylist.empty())
			mylist.pop_back();

		while (!list.empty())
			list.pop_back();

		compareList("empty after a loop of pop_back", mylist, list);
		std::cout << _YELLOW << "is mylist empty ? "<< std::boolalpha << _GREEN << mylist.empty() << _END << std::endl;
		std::cout << _YELLOW << "is list empty ? "<< std::boolalpha << _GREEN << list.empty() << _END << std::endl;
	}
	{
		std::cout << _CYAN << "==================== FRONT and BACK TEST ====================" << _END << std::endl;

		ft::list<int>		mylist;
		std::list<int>	list;

		mylist.push_back(78);
		list.push_back(78);

		mylist.push_back(16);
		list.push_back(16);

		compareList("content", mylist, list);

		std::cout << _YELLOW << "mylist.front() is " << _GREEN << mylist.front() << '\n';
		std::cout << _YELLOW << "list.front() is " << _GREEN << list.front() << _END <<'\n' <<'\n';
		std::cout << _YELLOW << "mylist.back() is " << _GREEN << mylist.back() << '\n';
		std::cout << _YELLOW << "list.back() is " << _GREEN << list.back() << _END <<'\n' <<'\n';

		mylist.front() -= mylist.back();
		list.front() -= list.back();
		
		compareList("list.front() -= list.back()", mylist, list);

		std::cout << _YELLOW << "mylist.front() is now " << _GREEN << mylist.front() << '\n';
		std::cout << _YELLOW << "list.front() is now " << _GREEN << list.front() << _END <<'\n';
		std::cout << _YELLOW << "mylist.back() is " << _GREEN << mylist.back() << '\n';
		std::cout << _YELLOW << "list.back() is " << _GREEN << list.back() << _END <<'\n' <<'\n';

		mylist.push_back(42);
		list.push_back(42);
		compareList("list.push_back(42)", mylist, list);

		std::cout << _YELLOW << "mylist.front() is now " << _GREEN << mylist.front() << '\n';
		std::cout << _YELLOW << "list.front() is now " << _GREEN << list.front() << _END <<'\n';
		std::cout << _YELLOW << "mylist.back() is " << _GREEN << mylist.back() << '\n';
		std::cout << _YELLOW << "list.back() is " << _GREEN << list.back() << _END <<'\n' <<'\n';
	}
	{
		std::cout << _CYAN << "==================== ASSIGN TEST ====================" << _END << std::endl;

		ft::list<int> first;
		ft::list<int> second;
		ft::list<int> third;

		std::list<int> stl_first;
		std::list<int> stl_second;
		std::list<int> stl_third;

		first.assign (7,100);             // 7 ints with a value of 100
		stl_first.assign (7,100);             // 7 ints with a value of 100

		ft::list<int>::iterator it;
		it = ++first.begin();
		std::list<int>::iterator stl_it;
		stl_it = ++stl_first.begin();

		second.assign (it, --first.end()); 	// the 5 central values of first
		stl_second.assign (stl_it, --stl_first.end()); // the 5 central values of first

		int myints[] = {1776,7,4};
		third.assign (myints, myints+3);   // assigning from array.
		stl_third.assign (myints, myints+3);   // assigning from array.

		compareList("first.assign (7,100)", first, stl_first);
		compareList("second.assign (it, --first.end())", second, stl_second);
		compareList("third.assign (myints, myints+3)", third, stl_third);
	}
	{
		std::cout << _CYAN << "==================== PUSH_BACK TEST ====================" << _END << std::endl;

		ft::list<int> mylist;
		std::list<int> list;

		mylist.push_back(10);
		list.push_back(10);

		while (mylist.back() != 0 && list.back() != 0)
		{
			mylist.push_back ( mylist.back() -1 );
			list.push_back ( list.back() -1 );
		}
		compareList("after a loop of list.push_back", mylist, list);
	}
	{
		std::cout << _CYAN << "==================== PUSH_FRONT TEST ====================" << _END << std::endl;

		ft::list<int> mylist;
		std::list<int> list;

		mylist.push_front(10);
		list.push_front(10);

		while (mylist.front() != 0 && list.front() != 0)
		{
			mylist.push_front( mylist.front() -1 );
			list.push_front ( list.front() -1 );
		}
		compareList("after a loop of list.push_front", mylist, list);
	}
	{
		std::cout << _CYAN << "==================== PUSH_BACK and PUSH_FRONT TEST ====================" << _END << std::endl;

		ft::list<int>		mylist;
		std::list<int>	list;
		int myint = 42;

		do {
			myint += 5; 
			myint /= 9;
			myint -= 2;
			myint *= 42;
			mylist.push_back (myint);
			mylist.push_front (myint);
			list.push_back (myint);
			list.push_front (myint);
		} while (myint < 1000000);

		compareList("after a loop of push_back and push_front", mylist, list);
		std::cout << "mylist stores " << int(mylist.size()) << " numbers.\n";
		std::cout << "list stores " << int(list.size()) << " numbers.\n";
	}
	{
		std::cout << _CYAN << "==================== POP_BACK TEST ====================" << _END << std::endl;

		ft::list<int>		mylist;
		std::list<int>	list;
		int sum (0);

		mylist.push_back (100);
		mylist.push_back (200);
		mylist.push_back (300);

		list.push_back (100);
		list.push_back (200);
		list.push_back (300);

		compareList("content", mylist, list);

		while (!mylist.empty())
		{
			sum+=mylist.back();
			mylist.pop_back();
		}
		std::cout << _YELLOW << "The elements of mylist add up to " << sum << '\n';

		sum = 0;
		while (!list.empty())
		{
			sum += list.back();
			list.pop_back();
		}

		std::cout << "The elements of list add up to " << sum << _END << '\n' << '\n';

		compareList("after a loop of pop_back", mylist, list);
	}
	{
		std::cout << _CYAN << "==================== INSERT TEST ====================" << _END << std::endl;

		ft::list<int>		mylist(3,100);
		std::list<int>	list(3,100);
		
		compareList("content", mylist, list);

		ft::list<int>::iterator my_it = ++mylist.begin();
		std::list<int>::iterator it = ++list.begin();

		my_it = mylist.insert (my_it , 200);
		it = list.insert (it , 200);

		compareList("list.insert ( it , 200 )", mylist, list);

		mylist.insert (my_it, 2, 300);
		list.insert (it, 2, 300);

		compareList("list.insert (it, 2, 300)", mylist, list);
		// "it" no longer valid, get a new one:
		my_it = mylist.begin();
		it = list.begin();
		my_it++;
		my_it++;
		it++;
		it++;

		ft::list<int> my_anotherlist (2,400);
		std::list<int> anotherlist (2,400);
		compareList("anotherlist: ", my_anotherlist, anotherlist);

		mylist.insert (my_it, my_anotherlist.begin(), my_anotherlist.end());
		list.insert (it, anotherlist.begin(), anotherlist.end());
		compareList("list.insert (it, anotherlist.begin(), anotherlist.end())", mylist, list);

		int myarray [] = { 501,502,503 };
		mylist.insert (mylist.begin(), myarray, myarray+3);
		list.insert (list.begin(), myarray, myarray+3);

		compareList("list.insert(list.begin(), myarray, myarray+3)", mylist, list);
	}
	{
		std::cout << _CYAN << "==================== ERASE TEST ====================" << _END << std::endl;

		ft::list<int>	mylist;
		std::list<int>	list;

		for (int i=1; i<=10; i++)
		{
			mylist.push_back(i);
			list.push_back(i);
		}

		compareList("set some values (from 1 to 10)", mylist, list);

		ft::list<int>::iterator my_it = mylist.begin();
		std::list<int>::iterator it = list.begin();

		for (int i = 0; i < 5; i++)
		{
			my_it++;
			it++;
		}
		mylist.erase (my_it);
		list.erase (it);

		compareList("erase the 6th element", mylist, list);

		my_it = mylist.begin();
		it = list.begin();
		for (int i = 0; i < 3; i++)
		{
			my_it++;
			it++;
		}

		mylist.erase(mylist.begin(), my_it);
		list.erase(list.begin(), it);

		compareList("erase the first 3 elements", mylist, list);
	}
	{
		std::cout << _CYAN << "==================== MEMBER SWAP TEST ====================" << _END << std::endl;

		// unsigned int i;
		ft::list<int>		my_foo (3,100);   // three ints with a value of 100
		ft::list<int>		my_bar (5,200);   // five ints with a value of 200

		std::list<int>	foo (3,100);   // three ints with a value of 100
  		std::list<int>	bar (5,200);   // five ints with a value of 200

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

		ft::list<int> mylist;
		mylist.push_back (100);
		mylist.push_back (200);
		mylist.push_back (300);

		std::list<int> list;
		list.push_back (100);
		list.push_back (200);
		list.push_back (300);

		compareList("content", mylist, list);

		mylist.clear();
		list.clear();
		compareList("after a clear", mylist, list);

	
		mylist.push_back (1101);
		mylist.push_back (2202);
		list.push_back (1101);
		list.push_back (2202);

		compareList("after 2 push_back", mylist, list);
		
		mylist.clear();
		list.clear();
		compareList("after another clear", mylist, list);
	}
	{
		std::cout << _CYAN << "==================== SPLICE TEST ====================" << _END << std::endl;

		ft::list<int>	mylist1, mylist2;
		std::list<int>	list1, list2;
		ft::list<int>::iterator my_it;
		std::list<int>::iterator it;

		for (int i=1; i<=4; ++i)
		{
			mylist1.push_back(i);
			list1.push_back(i);
		}
		compareList("list1", mylist1, list1);


		for (int i=1; i<=3; ++i)
		{
			mylist2.push_back(i*10);
			list2.push_back(i*10);
		}
		compareList("list2", mylist2, list2);


		my_it = mylist1.begin();
		it = list1.begin();
		++my_it;
		++it;

		mylist1.splice(my_it, mylist2);
		list1.splice(it, list2); 
		compareList("list1.splice(it, list2)", mylist1, list1);
		compareList("list2", mylist2, list2);
												
		mylist2.splice (mylist2.begin(), mylist1, my_it);
		list2.splice (list2.begin(), list1, it);
		compareList("list2.splice (list2.begin(), list1, it)", mylist2, list2);
		compareList("list1", mylist1, list1);
	
		my_it = mylist1.begin();
		it = list1.begin();
		for (int i = 0; i < 3; i++)
		{
			my_it++;
			it++;
		}

		mylist1.splice ( mylist1.begin(), mylist1, my_it, mylist1.end());
		list1.splice ( list1.begin(), list1, it, list1.end());

		compareList("list1.splice ( list1.begin(), list1, it, list1.end())", mylist1, list1);
	}
	{
		std::cout << _CYAN << "==================== REMOVE and REMOVE_IF TEST ====================" << _END << std::endl;

		ft::list<int>	mylist;
		std::list<int>	list;
		
		compareList("content", mylist, list);

		mylist.remove(42);
		list.remove(42);
		compareList("list.remove(42)", mylist, list);


		mylist.push_front(89);
		list.push_front(89);

		compareList("content", mylist, list);

		mylist.remove(0);
		list.remove(0);
		compareList("list.remove(0)", mylist, list);

		
		mylist.remove(89);
		list.remove(89);
		compareList("list.remove(89)", mylist, list);


		for (int i = 0; i < 8; i++)
		{
			mylist.push_back(57);
			list.push_back(57);
		}
		compareList("content", mylist, list);

		mylist.remove(42);
		list.remove(42);
		compareList("list.remove(42)", mylist, list);


		mylist.remove(57);
		list.remove(57);
		compareList("list.remove(57)", mylist, list);



		for (int i = 0; i < 8; i++)
		{
			mylist.push_back(456);
			list.push_back(456);
		}	
		for (int i = 0; i < 4; i++)
		{
			mylist.push_back(3 * i);
			list.push_back(3 * i);
		}
		for (int i = 0; i < 2; i++)
		{
			mylist.push_front(5 * i);
			list.push_front(5 * i);
		}
		compareList("content", mylist, list);

		mylist.remove(9);
		list.remove(9);
		compareList("list.remove(9)", mylist, list);


		mylist.remove_if(single_digit);
		list.remove_if(single_digit);
		compareList("list.remove_if(single_digit)", mylist, list);

		
		mylist.remove_if(is_odd());
		list.remove_if(is_odd());
		compareList("list.remove_if(is_odd())", mylist, list);


		mylist.remove_if(too_high);
		list.remove_if(too_high);
		compareList("list.remove_iftoo_high)", mylist, list);
		

		ft::list<std::string>		mystr;
		std::list<std::string>		str;

		mystr.remove_if(first_b);
		str.remove_if(first_b);
		compareList("str.remove_if(first_b)", mystr, str);


		mystr.push_front("salut");
		mystr.push_front("bien");
		mystr.push_front("salade");
		mystr.push_front("beatau");

		str.push_front("salut");
		str.push_front("bien");
		str.push_front("salade");
		str.push_front("beatau");
		compareList("after a few push_front ", mystr, str);

		mystr.remove_if(first_b);
		str.remove_if(first_b);
		compareList("str.remove_if(first_b)", mystr, str);

	}
	{
		int myints[]= {15,36,7,17,20,39,4,1};
		ft::list<int>	mylist(myints,myints+8);
		std::list<int>	list(myints,myints+8);

		compareList("content", mylist, list);

		mylist.remove_if (single_digit);
		list.remove_if (single_digit);
		compareList("list.remove_if (single_digit)", mylist, list);

		mylist.remove_if (is_odd());
		list.remove_if (is_odd());
		compareList("list.remove_if (is_odd())", mylist, list);
	}
	{
		std::cout << _CYAN << "==================== UNIQUE TEST ====================" << _END << std::endl;

  		double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                       12.77, 73.35, 72.25, 15.3,  72.25 };
		ft::list<double>	mylist (mydoubles,mydoubles+10);
		std::list<double>	list (mydoubles,mydoubles+10);
		
		mylist.sort();
		list.sort();
		compareList("list.sort()", mylist, list);

		mylist.unique();
		list.unique();
		compareList("list.unique()", mylist, list);
		
		mylist.unique(same_integral_part);  
		list.unique(same_integral_part);  
		compareList("list.unique(same_integral_part)", mylist, list);


		mylist.unique (is_near());
		list.unique (is_near());
		compareList("list.unique(is_near())", mylist, list);
	}
	{
		std::cout << _CYAN << "==================== MERGE TEST ====================" << _END << std::endl;

		ft::list<double> myfirst, mysecond;
		std::list<double> first, second;

		myfirst.push_back (3.1);
		myfirst.push_back (2.2);
		myfirst.push_back (2.9);
		mysecond.push_back (3.7);
		mysecond.push_back (7.1);
		mysecond.push_back (1.4);

		first.push_back (3.1);
		first.push_back (2.2);
		first.push_back (2.9);
		second.push_back (3.7);
		second.push_back (7.1);
		second.push_back (1.4);

		compareList("first list", myfirst, first);
		compareList("second list", mysecond, second);

		myfirst.sort();
		first.sort();
		compareList("sorted first list", myfirst, first);

		mysecond.sort();
		second.sort();
		compareList("sorted second list", mysecond, second);

		myfirst.merge(mysecond);
		first.merge(second);
		std::cout << _GREEN << "first.merge(second)" << _END <<  std::endl;
		compareList("first list", myfirst, first);
		compareList("second list", mysecond, second);


		mysecond.push_back (2.1);
		second.push_back (2.1);
		compareList("second list", mysecond, second);

		myfirst.merge(mysecond, mycomparison);
		first.merge(second, mycomparison);
		std::cout << _GREEN << "first.merge(second, mycomparison)" << _END << std::endl;
		compareList("first list", myfirst, first);
		compareList("second list", mysecond, second);
	}
	{
		std::cout << _CYAN << "==================== SORT and REVERSE TEST ====================" << _END << std::endl;

		ft::list<std::string>		mylist;
		std::list<std::string>		list;
		ft::list<std::string>::iterator	my_it;
		std::list<std::string>::iterator	it;
		
		mylist.push_back ("one");
		mylist.push_back ("two");
		mylist.push_back ("Three");

		list.push_back ("one");
		list.push_back ("two");
		list.push_back ("Three");

		compareList("content", mylist, list);

		mylist.sort();
		list.sort();
		compareList("content after list.sort()", mylist, list);

		mylist.sort(compare_nocase);
		list.sort(compare_nocase);
		compareList("list.sort(compare_nocase)", mylist, list);


		mylist.reverse();
		list.reverse();
		compareList("list.reverse()", mylist, list);

		mylist.sort();
		list.sort();
		compareList("list.sort()", mylist, list);

	}
	{
		std::cout << _CYAN << "==================== SORT and REVERSE TEST 2 ====================" << _END << std::endl;

		ft::list<double>		mylist;
		std::list<double>		list;
		ft::list<double>::iterator		my_it;
		std::list<double>::iterator	it;

		for (double i = 1.5; i < 14.7; i *= -2.3)
		{
			mylist.push_front(i * - 3.8);
			list.push_front(i * - 3.8);
			mylist.push_back(mylist.front() * 14.2);
			list.push_back(list.front() * 14.2);
		}
		compareList("list content", mylist, list);

		ft::list<double>	mylist2(mylist);
		std::list<double>	list2(list);
		mylist2.sort();
		list2.sort();

		compareList("list2 = copy of list + sort", mylist2, list2);

		mylist.reverse();
		list.reverse();
		compareList("list.reverse()", mylist, list);

		mylist.sort();
		list.sort();
		compareList("list.sort()", mylist, list);

		mylist.reverse();
		list.reverse();
		compareList("list.reverse()", mylist, list);

		mylist.sort();
		list.sort();
		compareList("list.sort()", mylist, list);
	}

	{
		std::cout << _CYAN << "==================== RELATIONNAL OPERATOR TEST ====================" << _END << std::endl;
		
		ft::list<int> my_foo(3,100);
		ft::list<int> my_bar(2,200);

		std::list<int> foo(3,100);
		std::list<int> bar(2,200);

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
		ft::list<int>		my_foo (3,100);
		ft::list<int>		my_bar (5,200);

		std::list<int>	foo (3,100);
  		std::list<int>	bar (5,200);

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);
		
		swap(my_foo, my_bar);
		swap(foo, bar);

		std::cout << _PURPLE << "foo.swap(bar)" << _END << std::endl;

		std::cout << "my_foo -> ", printContainer(my_foo);
		std::cout << "my_bar -> ", printContainer(my_bar);
		std::cout << "foo -> ", printContainer(foo);
		std::cout << "bar -> ", printContainer(bar);
	}
	return 0;
}