/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listIterThomas.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 12:08:50 by thgermai          #+#    #+#             */
/*   Updated: 2021/05/04 01:44:30 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTITERATOR
# define LISTITERATOR

# include "utilsThomas.hpp"
# include <cstddef>

namespace	ft
{
	template<typename T, class Alloc>
	class	ConstListIterator;
	template<typename T, class Alloc>
	class	ConstReverseListIterator;

	template<typename T, class Alloc>
	class	ListIterator
	{
	public :
		typedef T								value_type;
		typedef value_type*						pointer_type;
		typedef value_type&						reference_type;
		typedef Node<value_type, Alloc>*		node;
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;

		ListIterator() {}
		ListIterator(ListIterator const &ref) {*this = ref;}
		ListIterator(node _ptr) : ptr(_ptr) {}
		~ListIterator() {}
		ListIterator			&operator=(ListIterator const &ref) { ptr = ref.ptr; return *this; }

		operator ConstListIterator<T, Alloc>() const { return ConstListIterator<T, Alloc>(ptr); }

		pointer_type			operator->() const { return ptr->data; }
		reference_type			operator*() const { return *ptr->data; }

		bool					operator==(ListIterator const &ref) const { return ptr->data == ref.ptr->data; }
		bool					operator!=(ListIterator const &ref) const { return !(*this == ref); }

		ListIterator			&operator++() { ptr = ptr->next; return *this; }
		ListIterator			&operator--() { ptr = ptr->prev; return *this; }
		ListIterator			operator++(int) { ListIterator	tmp(*this); ++(*this); return tmp; }
		ListIterator			operator--(int) { ListIterator	tmp(*this); --(*this); return tmp; }

	private :
		node		ptr;
	};

	template<typename T, class Alloc>
	class	ConstListIterator
	{
	public :
		typedef T								value_type;
		typedef const value_type&				reference_type;
		typedef const value_type*				pointer_type;
		typedef Node<value_type, Alloc>*		node;
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;

		ConstListIterator() {}
		ConstListIterator(node _ptr) : ptr(_ptr) {}
		ConstListIterator(ConstListIterator const &ref) : ptr(ref.ptr) {}
		~ConstListIterator() {} ;
		ConstListIterator		&operator=(ConstListIterator const &ref) { ptr = ref.ptr; return *this;}

		pointer_type			operator->() const { return ptr->data; }
		reference_type			operator*() const { return *ptr->data; }

		bool					operator==(ConstListIterator const &ref) const { return ptr->data == ref.ptr->data; }
		bool					operator!=(ConstListIterator const &ref) const { return !(*this == ref); }

		ConstListIterator		&operator++() { ptr = ptr->next; return *this; }
		ConstListIterator		&operator--() { ptr = ptr->prev; return *this; }
		ConstListIterator		operator++(int) { ConstListIterator	tmp(*this); ptr = ptr->next; return tmp; }
		ConstListIterator		operator--(int) { ConstListIterator	tmp(*this); ptr = ptr->prev; return tmp; }

	private :
			node	ptr;
	};

	template<typename T, class Alloc>
	class	ReverseListIterator
	{
	public :
		typedef ListIterator<T, Alloc>					iterator;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::iterator_category	iterator_category;
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::pointer_type			pointer_type;
		typedef typename iterator::reference_type		reference_type;

		ReverseListIterator() {}
		ReverseListIterator(iterator const &ref) : _base(ref) {}
		ReverseListIterator(ReverseListIterator const &ref) { *this = ref; }
		~ReverseListIterator() {}
		ReverseListIterator		&operator=(ReverseListIterator const &ref) { _base = ref._base; return *this; }

		operator ConstReverseListIterator<T, Alloc>() const { return ConstReverseListIterator<T, Alloc>(_base); }

		pointer_type			operator->() const { iterator _tmp = _base; return (--_tmp).operator->(); }
		reference_type			operator*() const { iterator _tmp = _base; return (--_tmp).operator*(); }

		ReverseListIterator		&operator++() { --_base; return *this; }
		ReverseListIterator		&operator--() { ++_base ; return *this; }
		ReverseListIterator		operator++(int) { ReverseListIterator tmp(*this); --_base; return tmp; }
		ReverseListIterator		operator--(int) { ReverseListIterator tmp(*this); ++_base; return tmp; }

		bool					operator==(ReverseListIterator const &ref) const { return _base == ref._base; }
		bool					operator!=(ReverseListIterator const &ref) const { return !(*this == ref); }

		iterator				base() const { return _base; }

	private :
		iterator		_base;
	};

	template<typename T, class Alloc>
	class	ConstReverseListIterator
	{
	public :
		typedef ConstListIterator<T, Alloc>				iterator;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::iterator_category	iterator_category;
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::pointer_type			pointer_type;
		typedef typename iterator::reference_type		reference_type;

		ConstReverseListIterator() {}
		ConstReverseListIterator(iterator const &ref) : _base(ref) {}
		ConstReverseListIterator(ConstReverseListIterator const &ref) { *this = ref; }
		~ConstReverseListIterator() {}
		ConstReverseListIterator		&operator=(ConstReverseListIterator const &ref) { _base = ref._base; return *this; }

		pointer_type			operator->() const { iterator _tmp = _base; return (--_tmp).operator->(); }
		reference_type			operator*() const { iterator _tmp = _base; return (--_tmp).operator*(); }

		ConstReverseListIterator		&operator++() { --_base; return *this; }
		ConstReverseListIterator		&operator--() { ++_base ; return *this; }
		ConstReverseListIterator		operator++(int) { ConstReverseListIterator tmp(*this); --_base; return tmp; }
		ConstReverseListIterator		operator--(int) { ConstReverseListIterator tmp(*this); ++_base; return tmp; }

		bool					operator==(ConstReverseListIterator const &ref) const { return _base == ref._base; }
		bool					operator!=(ConstReverseListIterator const &ref) const { return !(*this == ref); }

		iterator				base() const { return _base; }

	private :
		iterator		_base;
	};

};

#endif