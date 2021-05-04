/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listThomas.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:43:56 by thgermai          #+#    #+#             */
/*   Updated: 2021/05/04 01:42:58 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST
# define LIST

# include <iostream>
# include "dllThomas.hpp"
# include "listIterThomas.hpp"

namespace	ft
{
	template<class T, class Alloc = std::allocator<T> >
	class		list
	{
	public :
		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef	size_t										size_type;
		typedef Node<value_type, allocator_type>*			node;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef	ListIterator<T, Alloc>						iterator;
		typedef ConstListIterator<T, Alloc>					const_iterator;
		typedef ReverseListIterator<T, Alloc>				reverse_iterator;
		typedef ConstReverseListIterator<T, Alloc>			const_reverse_iterator;
		typedef typename iterator::difference_type			difference_type;
		typedef	ft::DoublyLinkedList<T, Alloc>				dl_list;

					/* *** ************************ *** */
					/* *** Constructor / Destructor *** */
					/* *** ************************ *** */
		explicit list(const allocator_type& alloc = allocator_type()) : lst(alloc), _allocator(alloc) {}
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : lst(alloc), _allocator(alloc)
		{
			while (n--)
				lst.push_back(val);
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : lst(alloc), _allocator(alloc)
		{
			while (first != last)
				lst.push_back(*first++);
		}
		list(const list& x) :_allocator(x._allocator) { *this = x; }
		list				&operator=(const list& x)
		{
			lst = x.lst;
			return *this;
		}
		~list() {}

		iterator				begin() { return iterator(lst.get_head()->next); }
		const_iterator			begin() const { return const_iterator(lst.get_head()->next); }
		iterator				end() { return iterator(lst.get_head()); }
		const_iterator			end() const { return const_iterator(lst.get_head()); }

		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

		bool					empty() const { return lst.empty(); }
		size_type				size() const { return lst.size(); }
		size_type				max_size() const { return _allocator.max_size() / sizeof(node); }

		reference				front() { return lst.front(); }
		const_reference			front() const { return lst.front(); }
		reference				back() { return lst.back(); }
		const_reference			back() const { return lst.back(); }

		void					assign(size_type n, const value_type& val)
		{
			lst.clear();
			while (n-- > 0)
				lst.push_back(val);
		}
		template<class InputIterator>
		void					assign(InputIterator first, InputIterator last)
		{
			lst.clear();
			while (first != last)
				lst.push_back(*first++);
		}
		void					push_front(value_type const& val) { lst.push_front(val); }
		void					pop_front() { lst.pop_front(); }

		void					push_back(value_type const& val) { lst.push_back(val); }
		void					pop_back() { lst.pop_back(); }

		iterator				insert(iterator position, const value_type& val)
		{
			node		n = lst.find_node(position.operator->());

			lst.insert(val, n);
			return iterator(n->prev);
		}
		void					insert(iterator position, size_type n, const value_type& val)
		{
			while (n--)
				position = insert(position, val);
		}
		template<typename InputIterator>
		void					insert(iterator position, InputIterator first, InputIterator last)
		{
			while (first != last)
				insert(position, *first++);
		}

		iterator				erase(iterator position)
		{
			node		n = lst.find_node(position.operator->());

			++position;
			lst.delete_node(n);
			return position;
		}
		iterator				erase(iterator first, iterator last)
		{
			while (first != last)
				first = erase(first);
			return last;
		}

		void					resize(size_type n, value_type val = value_type())
		{
			int			resize = n - size();

			if (resize < 0)
				while (resize++)
					lst.pop_back();
			else
				while (resize--)
					lst.push_back(val);
		}

		void					swap(list& c) { lst.swap(c.lst); }
		void					clear() { lst.clear(); }

		void					splice(iterator position, list& x, iterator i)
		{
			node		pos = lst.find_node(position.operator->());
			node		it = x.lst.find_node(i.operator->());

			lst.move_to(it, pos);
			lst.increase_size();
			x.lst.decrease_size();
			x.lst.refresh_tail();
		}
		void					splice(iterator position, list& x, iterator first, iterator last)
		{
			node		pos = lst.find_node(position.operator->());
			node		first_n = x.lst.find_node(first.operator->());
			node		last_n = x.lst.find_node((--last).operator->());
			size_type	dist = _distance(first, last) + 1;

			lst.move_range_to(first_n, last_n, pos);
			lst.increase_size(dist);
			lst.refresh_tail();
			x.lst.decrease_size(dist);
			x.lst.refresh_tail();
		}
		void					splice(iterator position, list& x)
		{
			splice(position, x, x.begin(), x.end());
		}

		void					remove(const value_type& val)
		{
			iterator		it = begin();

			while (it != end())
			{
				if (*it == val)
					it = erase(it);
				else
					++it;
			}
		}
		template<class Predicate>
		void					remove_if(Predicate pred)
		{
			iterator		it = begin();

			while (it != end())
			{
				if (pred(*it))
					it = erase(it);
				else
					++it;
			}
		}

		void					unique()
		{
			iterator			prev = begin();
			iterator			current = prev;

			while (++current != end())
			{
				if (*prev == *current)
				{
					erase(current);
					current = prev;
				}
				else
					prev = current;
			}
		}

		template<class BinaryPredicate>
		void					unique(BinaryPredicate binary_pred)
		{
			iterator			prev = begin();
			iterator			current = prev;
			while (++current != end())
			{
				if (binary_pred(*prev, *current))
				{
					erase(current);
					current = prev;
				}
				else
					prev = current;
			}
		}

		void					sort()
		{
			lst.sort(basic_comp<value_type>);
		}
		template<class Compare>
		void					sort(Compare comp)
		{
			lst.sort(comp);
		}

		void					merge(list& x) { merge(x, basic_comp<value_type>); }
		template<class Compare>
		void					merge(list& x, Compare comp)
		{
			iterator			it;
			iterator			xit;
			if (&x == this)
				return ;
			for (it = begin(); it != end(); ++it)
			{
				xit = x.begin();
				while (xit != x.end() && comp(*xit, *it))
				{
					lst.move_to(x.lst.find_node(xit.operator->()), lst.find_node(it.operator->()));
					xit = x.begin();
				}
			}
			while (xit != x.end())
			{
				lst.move_to(x.lst.find_node(xit.operator->()), lst.find_node(it.operator->()));
				xit = x.begin();
			}
			lst.increase_size(x.size());
			x.lst.decrease_size(x.size());
		}

		void					reverse() { lst.reverse();  }

	private :
		dl_list					lst;
		allocator_type			_allocator;

		size_type				_distance(iterator start, iterator last)
		{
			size_type			i = 0;
			while (start++ != last)
				++i;
			return i;
		}
	};

	template<class T, class Alloc>
	bool				operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::list<T, Alloc>::const_iterator		lit = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator		rit = rhs.begin();
		while (lit != lhs.end())
		{
			if (*lit++ != *rit++)
				return false;
		}
		return true;
	}
	template<class T, class Alloc>
	bool				operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		typename ft::list<T, Alloc>::const_iterator		lit = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator		rit = rhs.begin();
		while (lit != lhs.end() && rit != rhs.end())
		{
			if (*lit != *rit)
				return *lit < *rit;
			++lit;
			++rit;
		}
		if (rit != rhs.end())
			return true;
		return false;
	}
	template<class T, class Alloc>
	bool				operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) { return !(lhs == rhs); }
	template<class T, class Alloc>
	bool				operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) { return rhs < lhs; }
	template<class T, class Alloc>
	bool				operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) { return !(lhs < rhs); }
	template<class T, class Alloc>
	bool				operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) { return !(rhs < lhs); }
	template<class T, class Alloc>
	void				swap(list<T, Alloc>& x, list<T, Alloc>& y) { x.swap(y); }
};

#endif