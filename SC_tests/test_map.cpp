/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:00:10 by schene            #+#    #+#             */
/*   Updated: 2021/05/06 03:03:59 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <map>
#include <limits>
#include "utils.hpp"
#include "color.h"
#include "../containers/map.hpp"

template<typename K, typename V>
void print_map(std::map<K,V> const &m)
{
	for (typename std::map<K,V>::const_iterator it = m.begin(); it != m.end(); it++)
        std::cout  << "{" << _GREEN <<  (*it).first << _YELLOW ": " << _GREEN << (*it).second << _YELLOW "} ";
        // std::cout << "{" << (*it).first << ": " << (*it).second << "} ";
	std::cout << std::endl;
}

template<typename K, typename V>
void print_mymap(ft::map<K,V> const &m)
{
	for (typename ft::map<K,V>::const_iterator it = m.begin(); it != m.end(); it++)
        std::cout  << "{" << _GREEN <<  (*it).first << _YELLOW ": " << _GREEN << (*it).second << _YELLOW "} ";
	std::cout << _END << std::endl ;
}

template<typename K, typename V>
void	error_diff(ft::map<K,V> &mymap, std::map<K,V> &map)
{
	std::cout << _RED << "ERROR - DIFF" << _END << std::endl;
	std::cout << std::setw(30) << "mymap.empty(): " << mymap.empty() << std::endl;
	std::cout << std::setw(30) << "map.empty(): " << map.empty() << std::endl;
	std::cout << std::setw(30) << "mymap.size(): " << mymap.size() << std::endl;
	std::cout << std::setw(30) << "map.size(): " << map.size() << std::endl;
	std::cout << std::setw(30) << "mymap : ";
	print_mymap(mymap);
	std::cout << std::setw(30) << "map : ";
	print_map(map);
}

template<typename K, typename V>
void	compareMap(std::string function, ft::map<K,V> &mymap, std::map<K,V> &map)
{
	std::cout << std::setw(30) << function << ": ";
	if (mymap.empty() != map.empty())
		error_diff(mymap, map);
	else if (map.size() != map.size())
		error_diff(mymap, map);
	else
	{
		typename ft::map<K,V>::iterator	my_it;
		typename std::map<K,V>::iterator	i;
		my_it = mymap.begin();
		i = map.begin();
		while (i != map.end())
		{
			if ((*i).first != (*my_it).first || (*i).second != (*my_it).second)
			{
				error_diff(mymap, map);
				return ;
			}
			i++;
			my_it++;
		}
		
		std::cout << _GREEN << "OK " << _END << std::endl;
		std::cout << _YELLOW << "mymap ";
		print_mymap(mymap);
		std::cout << _YELLOW << "map   ";
		print_map(map);
		std::cout << _END << std::endl;
	}
}

int		main()
{
	{
		std::cout << _CYAN << "==================== empty CONSTRUCTOR TEST ====================" << _END << std::endl;
		ft::map<char, int>	mymap;
		std::map<char, int>	map;

		compareMap("default -> map", mymap, map);

		std::cout << _CYAN << "==================== (single and with int) INSERT TEST ====================" << _END << std::endl;

		//single element:
		mymap.insert(std::pair<char, int>('a', 100));
		mymap.insert(std::pair<char, int>('c', 80));
		mymap.insert(std::pair<char, int>('e', 60));
		map.insert(std::pair<char, int>('a', 100));
		map.insert(std::pair<char, int>('c', 80));
		map.insert(std::pair<char, int>('e', 60));

		compareMap("3 insert of single element", mymap, map);

		//with int:
		mymap.insert(++mymap.begin(), std::pair<char, int>('b', 90));
		map.insert(++map.begin(), std::pair<char, int>('b', 90));
		
		compareMap("insert b w/ correct hint", mymap, map);
		
		mymap.insert(mymap.begin(), std::pair<char, int>('d', 70));
		map.insert(map.begin(), std::pair<char, int>('d', 70));
		
		compareMap("insert d w/ an incorrect hint", mymap, map);
		
		std::cout << _CYAN << "==================== range CONSTRUCTOR TEST ====================" << _END << std::endl;
		
		ft::map<char, int>	myrange(++mymap.begin(), --mymap.end());
		std::map<char, int>	range(++map.begin(), --map.end());

		compareMap("map<char, int>	range(++map.begin(), map.end())", myrange, range);

		std::cout << _CYAN << "==================== copy CONSTRUCTOR TEST ====================" << _END << std::endl;
		
		ft::map<char, int>	mycopy(myrange);
		std::map<char, int>	copy(range);

		compareMap("map<char, int>	copy(range)", mycopy, copy);

		std::cout << _CYAN << "==================== (range) INSERT TEST ====================" << _END << std::endl;

		myrange.insert(mymap.begin(), mymap.end());
		range.insert(map.begin(), map.end());

		compareMap("range.insert(map.begin(), map.end())", myrange, range);

		std::cout << _CYAN << "==================== OPERATOR = TEST ====================" << _END << std::endl;

		mycopy = myrange;
		copy = range;
		
		compareMap("copy = range", mycopy, copy);

		std::cout << _CYAN << "==================== ERASE TEST ====================" << _END << std::endl;

		compareMap("content", mymap, map);

		mymap.erase(--mymap.end());
		map.erase(--map.end());

		compareMap("from an iterator -> map.erase(--mymap.end())", mymap, map);

		// from key
		mymap.erase('c');
		map.erase('c');

		compareMap("from a key -> map.erase('c')", mymap, map);
		
		// from a range
		mymap.erase(++mymap.begin(), mymap.end());
		map.erase(++map.begin(), map.end());
		
		compareMap("from a range -> map.erase(++map.begin(), map.end())", mymap, map);

		std::cout << _CYAN << "==================== FIND and COUNT TEST ====================" << _END << std::endl;

		mymap = mycopy;
		map = copy;

		mymap.erase('c');
		map.erase('c');

		compareMap("content", mymap, map);

		std::cout << "FIND function return an iterator to the element corrsponding to the given key" << std::endl;
		std::cout << "(if no corresponding element map.end() is return)" << std::endl << std::endl;

		std::cout << "COUNT: Searches the container for elements with a key equivalent to the given  key and returns the number of matches." << std::endl;
		std::cout << "Because all elements in a map container are unique, the function can only return 1 (if the element is found) or 0 (otherwise)" << std::endl << std::endl;

		ft::map<char, int>::iterator	myit;
		std::map<char, int>::iterator	it;
		int		myi, i;

		for (char c = '`'; c < 'g'; c++)
		{
			myit = mymap.find(c);
			it = map.find(c);
			myi = mymap.count(c);
			i = map.count(c);

			if (myit != mymap.end())
				std::cout << c << _GREEN <<  " was found in mymap, value = " << _END << (*myit).second << std::endl;
			else
				std::cout << "mymap.find(" << c << ") " << _RED << "return mymap.end()..." << _END << std::endl;

			if (it != map.end())
				std::cout << c << _GREEN <<  " was found in map, value = " << _END << (*it).second << std::endl;
			else
				std::cout << "map.find(" << c << ") " << _RED << "return map.end()..." << _END << std::endl;

			std::cout << "mymap.count(" << c << ") return ";
			if (myi)
				std::cout << _GREEN <<  myi << _END << std::endl;
			else
				std::cout << _RED <<  myi << _END << std::endl;
			
			std::cout << "map.count(" << c << ") return ";
			if (i)
				std::cout << _GREEN <<  i << _END << std::endl;
			else
				std::cout << _RED <<  i << _END << std::endl;
			std::cout << std::endl;
		}
	}
	{
		std::cout << _CYAN << "==================== OPERATOR [] TEST ====================" << _END << std::endl;
		ft::map<char, int>	mymap;
		std::map<char, int>	map;

		int i = 42;
		for (char c = 'a'; c < 'g'; c++)
		{
			mymap[c] = i;
			map[c] = i;
			i = i * 2 - 10;
		}
		compareMap("after a loop of assignation with []", mymap, map);
		std::cout << _YELLOW << "mymap size = " << _GREEN << mymap.size() << _END << std::endl;
		std::cout << _YELLOW << "map size = " << _GREEN << map.size() << _END << std::endl << std::endl;

		std::cout << _YELLOW << "mymap['b'] = " << _GREEN << mymap['b'] << _END << std::endl;
		std::cout << _YELLOW << "map['b'] = " << _GREEN << map['b'] << _END << std::endl << std::endl;

		std::cout << _YELLOW << "mymap['z'] = " << _GREEN << mymap['z'] << _END << std::endl;
		std::cout << _YELLOW << "map['z'] = " << _GREEN << map['z'] << _END << std::endl;
		std::cout << "-> since z does not match with any element in the container , the function inserts a new element with 'z' as a key" << std::endl << std::endl;
	
		compareMap("content", mymap, map);
		std::cout << _YELLOW << "mymap size = " << _GREEN << mymap.size() << _END << std::endl;
		std::cout << _YELLOW << "map size = " << _GREEN << map.size() << _END << std::endl;
	}
	{
		std::cout << _CYAN << "==================== OPERATOR [] TEST ====================" << _END << std::endl;
		ft::map<char, int>	mymap;
		std::map<char, int>	map;

		compareMap("default constructor (map is empty)", mymap, map);
		std::cout << _YELLOW << "mymap size = " << _GREEN << mymap.size() << _END << std::endl;
		std::cout << _YELLOW << "map size = " << _GREEN << map.size() << _END << std::endl;
		std::cout << _CYAN << "mymap empty ? " << _GREEN << std::boolalpha << mymap.empty() << _END << std::endl;
		std::cout << _CYAN << "map empty ? " << _GREEN << std::boolalpha <<  map.empty() << _END << std::endl << std::endl;

		int i = 10;
		for (char c = 'a'; c < 'd'; c++)
		{
			mymap[c] = i;
			map[c] = i;
			i += 10;
		}
		compareMap("content after some assignation ", mymap, map);
		std::cout << _YELLOW << "mymap size = " << _GREEN << mymap.size() << _END << std::endl;
		std::cout << _YELLOW << "map size = " << _GREEN << map.size() << _END << std::endl;
		std::cout << _CYAN << "mymap empty ? " << _GREEN << std::boolalpha << mymap.empty() << _END << std::endl;
		std::cout << _CYAN << "map empty ? " << _GREEN << std::boolalpha <<  map.empty() << _END << std::endl << std::endl;

		mymap.clear();
		map.clear();
		
		compareMap("map.clear() -> map is empty again", mymap, map);
		std::cout << _YELLOW << "mymap size = " << _GREEN << mymap.size() << _END << std::endl;
		std::cout << _YELLOW << "map size = " << _GREEN << map.size() << _END << std::endl;
		std::cout << _CYAN << "mymap empty ? " << _GREEN << std::boolalpha << mymap.empty() << _END << std::endl;
		std::cout << _CYAN << "map empty ? " << _GREEN << std::boolalpha <<  map.empty() << _END << std::endl << std::endl;
	}
	{
		std::cout << _CYAN << "==================== RBEGIN and REND TEST ====================" << _END << std::endl;
		ft::map<char, int>	mymap;
		std::map<char, int>	map;

		int i = 10;
		for (char c = 'a'; c < 'd'; c++)
		{
			mymap[c] = i;
			map[c] = i;
			i += 10;
		}
		compareMap("content", mymap, map);
		
		std::cout << _YELLOW << "iterating from rbegin to rend in mymap : " << _END << std::endl;
		for (ft::map<char,int>::reverse_iterator it = mymap.rbegin(); it != mymap.rend(); it++)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << _YELLOW << "the same in map : " << _END << std::endl;
		for (std::map<char,int>::reverse_iterator it = map.rbegin(); it != map.rend(); it++)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		std::cout << _CYAN << "==================== SWAP TEST ====================" << _END << std::endl;
		ft::map<char, int>	myfoo, mybar;
		std::map<char, int>	foo, bar;

		int i = 1;
		for (char c = 'a'; c < 'm'; c++)
		{
			myfoo[c] = i;
			foo[c] = i;
			i++;
		}
		
		i = 348;
		for (char c = 'v'; c < 'z'; c++)
		{
			mybar[c] = i;
			bar[c] = i;
			i = i * 3 - 234;
		}
		compareMap("content of foo ", myfoo, foo);
		std::cout << _YELLOW << "myfoo size = " << _GREEN << myfoo.size() << _END << std::endl;
		std::cout << _YELLOW << "foo size = " << _GREEN << foo.size() << _END << std::endl;
		compareMap("content of bar ", mybar, bar);
		std::cout << _YELLOW << "mybar size = " << _GREEN << mybar.size() << _END << std::endl;
		std::cout << _YELLOW << "bar size = " << _GREEN << bar.size() << _END << std::endl;


		myfoo.swap(mybar);
		foo.swap(bar);
		std::cout << std::endl << _CYAN << "foo.swap(bar)  (member function)" << _END << std::endl << std::endl;

		compareMap("content of foo ", myfoo, foo);
		std::cout << _YELLOW << "myfoo size = " << _GREEN << myfoo.size() << _END << std::endl;
		std::cout << _YELLOW << "foo size = " << _GREEN << foo.size() << _END << std::endl;
		compareMap("content of bar ", mybar, bar);
		std::cout << _YELLOW << "mybar size = " << _GREEN << mybar.size() << _END << std::endl;
		std::cout << _YELLOW << "bar size = " << _GREEN << bar.size() << _END << std::endl;

		swap(mybar, myfoo);
		swap(bar, foo);
		std::cout << std::endl << _CYAN << "swap(bar, foo)  (non member function)" << _END << std::endl << std::endl;

		compareMap("content of foo ", myfoo, foo);
		std::cout << _YELLOW << "myfoo size = " << _GREEN << myfoo.size() << _END << std::endl;
		std::cout << _YELLOW << "foo size = " << _GREEN << foo.size() << _END << std::endl;
		compareMap("content of bar ", mybar, bar);
		std::cout << _YELLOW << "mybar size = " << _GREEN << mybar.size() << _END << std::endl;
		std::cout << _YELLOW << "bar size = " << _GREEN << bar.size() << _END << std::endl;
	}
	{
		std::cout << _CYAN << "==================== MAX_SIZE TEST ====================" << _END << std::endl;
		ft::map<char, int>	mymap;
		std::map<char, int>	map;

		std::cout << _YELLOW << "mymap max_size = " << _END << mymap.max_size() <<std::endl;
		std::cout << _YELLOW << "  map max_size = " << _END << map.max_size() <<std::endl;
	}
	{
		std::cout << _CYAN << "==================== KEY_COMP TEST ====================" << _END << std::endl;
		ft::map<char, int>	mymap;
		std::map<char, int>	map;

		ft::map<char,int>::key_compare		mycomp = mymap.key_comp();
		std::map<char,int>::key_compare		comp = map.key_comp();

		int i = 10;
		for (char c = 'a'; c < 'd'; c++)
		{
			mymap[c] = i;
			map[c] = i;
			i += 10;
		}
		compareMap("content", mymap, map);

		char myhighest = mymap.rbegin()->first;     // key value of last element
		char highest = map.rbegin()->first;     // key value of last element

		std::cout << _YELLOW << "using map.key_comp() to iter trough our maps : " << _END << std::endl;
		std::cout << "mymap contains:\n";
		ft::map<char,int>::iterator myit = mymap.begin();
		do {
			std::cout << myit->first << " => " << myit->second << '\n';
		} while ( mycomp((*myit++).first, myhighest) );

		std::cout << std::endl;

		std::cout << "map contains:\n";
		std::map<char,int>::iterator it = map.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( comp((*it++).first, highest) );
	}
	{
		std::cout << _CYAN << "==================== VALUE_COMP TEST ====================" << _END << std::endl;
		ft::map<char, int>	mymap;
		std::map<char, int>	map;

		int i = 54;
		for (char c = 'm'; c < 'q'; c++)
		{
			mymap[c] = i;
			map[c] = i;
			i *= 2 + 31;
		}
		compareMap("content", mymap, map);

		std::pair<char,int> myhighest = *mymap.rbegin();          // last element
		std::pair<char,int> highest = *map.rbegin();          // last element

		std::cout << _YELLOW << "using map.value_comp() to iter trough our maps : " << _END << std::endl;
		std::cout << "mymap contains:\n";
		ft::map<char,int>::iterator myit = mymap.begin();
		do {
			std::cout << myit->first << " => " << myit->second << '\n';
		} while ( mymap.value_comp()(*myit++, myhighest) );

		std::cout << std::endl;

		std::cout << "map contains:\n";
		std::map<char,int>::iterator it = map.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( map.value_comp()(*it++, highest) );
	}
	{
		std::cout << _CYAN << "==================== LOWER_BOUND and UPPER_BOUND TEST ====================" << _END << std::endl;
		ft::map<char, int>	mymap;
		std::map<char, int>	map;
		ft::map<char,int>::iterator myitlow, myitup;
		std::map<char,int>::iterator itlow, itup;

		int i = 10;
		for (char c = 'a'; c < 'f'; c++)
		{
			mymap[c] = i;
			map[c] = i;
			i += 15;
		}
		compareMap("content", mymap, map);

		myitlow = mymap.lower_bound ('b');  // itlow points to b
		myitup = mymap.upper_bound ('d');   // itup points to e (not d!)

		itlow = map.lower_bound ('b');  // itlow points to b
		itup = map.upper_bound ('d');   // itup points to e (not d!)

		std::cout << _YELLOW << "mymap low : " << _GREEN << myitlow->first << _END << std::endl;
		std::cout << _YELLOW << "map low : " << _GREEN << itlow->first << _END << std::endl;
		std::cout << _YELLOW << "mymap up : " << _GREEN << myitup->first << _END << std::endl;
		std::cout << _YELLOW << "map up : " << _GREEN << itup->first << _END << std::endl;
		
		mymap.erase(myitlow, myitup);        // erases [itlow,itup)
		map.erase(itlow, itup);        // erases [itlow,itup)
		compareMap("map.erase(itlow, itup)", mymap, map);
	}
	{
		std::cout << _CYAN << "==================== EQUAL_RANGE TEST ====================" << _END << std::endl;
		ft::map<char, int>	mymap;
		std::map<char, int>	map;

		int i = 10;
		for (char c = 'a'; c < 'e'; c++)
		{
			mymap[c] = i;
			map[c] = i;
			i += 10;
		}
		compareMap("content", mymap, map);

		std::pair<ft::map<char,int>::iterator, ft::map<char,int>::iterator>	myret;
		std::pair<std::map<char,int>::iterator, std::map<char,int>::iterator>	ret;
		
		myret = mymap.equal_range('b');
		ret = map.equal_range('b');

		std::cout << "lower bound points to: " << std::endl;
		std::cout << _YELLOW << "[mymap] " << _GREEN << myret.first->first << " => " << myret.first->second << _END << std::endl;
		std::cout << _YELLOW << "[map]   " << _GREEN << ret.first->first << " => " << ret.first->second << _END << std::endl;

		std::cout << "upper bound points to: " << std::endl;
		std::cout << _YELLOW << "[mymap] " << _GREEN << myret.second->first << " => " << myret.second->second << _END << std::endl;
		std::cout << _YELLOW << "[map]   " << _GREEN << ret.second->first << " => " << ret.second->second << _END << std::endl;
	}
	{
		std::cout << _CYAN << "==================== RELATIONNAL OPERATOR TEST ====================" << _END << std::endl;
		ft::map<char, int>	myfoo, mybar;
		std::map<char, int>	foo, bar;

		int i = 1;
		for (char c = 'a'; c < 'd'; c++)
		{
			myfoo[c] = i;
			foo[c] = i;
			i++;
		}
		
		i = 348;
		for (char c = 'a'; c < 'd'; c++)
		{
			mybar[c] = i;
			bar[c] = i;
			i = i * 3 - 234;
		}
		compareMap("content of foo ", myfoo, foo);
		compareMap("content of bar ", mybar, bar);

		if (myfoo == mybar) std::cout << "myfoo and mybar are equal\n";
		if (myfoo != mybar) std::cout << "myfoo and mybar are not equal\n";
		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		std::cout << std::endl;
		
		if (myfoo <  mybar) std::cout << "myfoo is less than mybar\n";
		if (myfoo >  mybar) std::cout << "myfoo is greater than mybar\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		std::cout << std::endl;

		if (myfoo <= mybar) std::cout << "myfoo is less than or equal to mybar\n";
		if (myfoo >= mybar) std::cout << "myfoo is greater than or equal to mybar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

		swap(myfoo, mybar);
		swap(foo, bar);

		std::cout << _YELLOW << "swap(foo, bar)" << _END << std::endl << std::endl;

		compareMap("content of foo ", myfoo, foo);
		compareMap("content of bar ", mybar, bar);

		if (myfoo == mybar) std::cout << "myfoo and mybar are equal\n";
		if (myfoo != mybar) std::cout << "myfoo and mybar are not equal\n";
		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		std::cout << std::endl;
		
		if (myfoo <  mybar) std::cout << "myfoo is less than mybar\n";
		if (myfoo >  mybar) std::cout << "myfoo is greater than mybar\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		std::cout << std::endl;

		if (myfoo <= mybar) std::cout << "myfoo is less than or equal to mybar\n";
		if (myfoo >= mybar) std::cout << "myfoo is greater than or equal to mybar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		std::cout << std::endl;

		myfoo = mybar;
		foo = bar;

		std::cout << _YELLOW << "foo = bar" << _END << std::endl << std::endl;

		compareMap("content of foo ", myfoo, foo);
		compareMap("content of bar ", mybar, bar);

		if (myfoo == mybar) std::cout << "myfoo and mybar are equal\n";
		if (myfoo != mybar) std::cout << "myfoo and mybar are not equal\n";
		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		std::cout << std::endl;
		
		if (myfoo <  mybar) std::cout << "myfoo is less than mybar\n";
		if (myfoo >  mybar) std::cout << "myfoo is greater than mybar\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		std::cout << std::endl;

		if (myfoo <= mybar) std::cout << "myfoo is less than or equal to mybar\n";
		if (myfoo >= mybar) std::cout << "myfoo is greater than or equal to mybar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	return 0;
}