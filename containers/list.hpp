/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:15 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/04 05:25:30 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

#include "../iterators/bidirectionalIterator.hpp"
#include <memory>

namespace ft
{
    template < typename T >
    class List {

        public :

			//defining every member in my List as in the STL
            typedef T                           value_type;
            typedef std::allocator<T>           allocator_type;
            typedef T &                         reference;
            typedef T *                         pointer;
            typedef const T &	                const_reference;
            typedef const T *	                const_pointer;
			typedef myBidirectionalIterator<T>  iterator;
			typedef myBidirectionalIterator<T>  const_iterator;           //not exactly
			typedef myBidirectionalIterator<T>  reverse_iterator;         //not exactly
			typedef myBidirectionalIterator<T>  const_reverse_iterator;     //not exactly
			typedef size_t		                size_type;
			typedef ptrdiff_t	                difference_type;

            List() {}
            ~List() {}
            List(const List &) {}
            List &operator=(const List &) {}

            iterator begin() {}
            iterator end() {}
            reverse_iterator rbegin() {}
            reverse_iterator rend() {}
            const_iterator begin() const {}
            const_iterator end() const {}
            const_reverse_iterator rbegin() const {}
            const_reverse_iterator rend() const {}

            bool empty() const {}
            size_type size() const {}
            size_type max_size() const {}

            reference front() {}
            const_reference front() const {}
            reference back() {}
            const_reference back() const {}

            void assign(iterator first, iterator last) {}    //InputIterator in cppreference.comm
            void assign(size_type n, const value_type &val) {}
            void push_front(const value_type &val) {}
            void pop_front() {}
            void push_back(const value_type &val) {}
            void pop_back() {}
            iterator insert(iterator position, const value_type &val) {}
            void insert(iterator position, size_type n, const value_type &val) {}
            void insert(iterator position, iterator first, iterator last) {}    //InputIterator in cppreference.comm
            iterator erase(iterator position) {}
            iterator erase(iterator first, iterator last) {}
            void swap(List &x) {}
            void resize (size_type n, value_type val = value_type()) {} //?
            void clear() {}

            void splice (iterator position, list& x);
            void splice (iterator position, list& x, iterator i);
            void splice (iterator position, list& x, iterator first, iterator last);
            void remove (const value_type &val);
            template < class Predicate >
            void remove_if (Predicate pred);
            void unique() {}
            template < class BinaryPredicate >
            void unique(BinaryPredicate binary_pred);
            void merge(List &x) {}
            void sort() {}
            template < class Compare >
            void merge(List &x, Compare comp) {}
            void sort(Compare comp) {}
            void reverse() {}
            
        private :

            T *list;  //?

    };

    template < typename T >
    bool operator== (const List<T>& lhs, const List<T>& rhs) {}
    template <class T>  //pas pareil qu'en haut
    bool operator!= (const List<T>& lhs, const List<T>& rhs) {}
    template <class T>
    bool operator<  (const List<T>& lhs, const List<T>& rhs) {}
    template <class T>
    bool operator<= (const List<T>& lhs, const List<T>& rhs) {}
    template <class T>
    bool operator>  (const List<T>& lhs, const List<T>& rhs) {}
    template <class T>
    bool operator>= (const List<T>& lhs, const List<T>& rhs) {}
    
    template < typename T >
    void swap(List<T> &x, List<T> &y) {}

    // template < typename T, class Alloc >
    // bool operator== (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {}
    // template <class T, class Alloc>
    // bool operator!= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs);
    // template <class T, class Alloc>
    // bool operator<  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs);
    // template <class T, class Alloc>
    // bool operator<= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs);
    // template <class T, class Alloc>
    // bool operator>  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs);
    // template <class T, class Alloc>
    // bool operator>= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs);
}

#endif