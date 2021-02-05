/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:15 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/05 01:59:43 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

#include "../utils/bidirectionalIterator.hpp"
#include "../utils/doublyLinkedList.hpp"
#include <memory>

namespace ft
{
    template < typename T, class Alloc = std::allocator<T> >
    class List {

        public :

			//defining every member in my List as in the STL
            typedef T                           value_type;
            typedef Alloc                       allocator_type;
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

//             dLList<T>       myList;  //?
//             allocator_type  myAlloc;
//             size_type       mySize;
//             difference_type myDiff;

            List() : mySize(0) {}
            ~List() {}
            List(const List &ref) : mySize(ref.mySize) { *this = ref; }
            List &operator=(const List &) {
                this->clear();
                for (iterator it )
            }

            // ----- ITERATORS ----- //
            iterator begin() { return iterator(myList.content); }
            iterator end() {}
            reverse_iterator rbegin() {}
            reverse_iterator rend() {}
            const_iterator begin() const {}
            const_iterator end() const {}
            const_reverse_iterator rbegin() const {}
            const_reverse_iterator rend() const {}

            // ----- CAPACITY ----- //
            bool empty() const { return (mySize > 0); }
            size_type size() const { return (mySize); }
            size_type max_size() const {}

            // ----- ELEMENT ACCESS ----- //
            reference front() { return reference(myList.content); }
            const_reference front() const { return reference(myList.content); }
            reference back() {}
            const_reference back() const {}

            // ----- MODIFIERS ----- //
            void assign(iterator first, iterator last) {}    //InputIterator in cppreference.comm
            void assign(size_type n, const value_type &val) {}
            void push_front(const value_type &val) { 
                
            }
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

            // ----- OPERATIONS ----- //
            void splice (iterator position, List& x) {}
            void splice (iterator position, List& x, iterator i) {}
            void splice (iterator position, List& x, iterator first, iterator last) {}
            void remove (const value_type &val) {}
            template < class Predicate >
            void remove_if (Predicate pred) {}
            void unique() {}
            template < class BinaryPredicate >
            void unique(BinaryPredicate binary_pred) {}
            void merge(List &x) {}
            template < class Compare >
            void merge(List &x, Compare comp) {}
            void sort() {}
            template < class Compare >
            void sort(Compare comp) {}
            void reverse() {}
            
        private :

            dLList<T>       myList;  //?
            allocator_type  myAlloc;
            size_type       mySize;
            difference_type myDiff;

    };

    template < typename T, class Alloc >
    bool operator==(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) { return (lhs == rhs); }
    template < typename T, class Alloc >
    bool operator!=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) { return (lhs != rhs); }
    template < typename T, class Alloc >
    bool operator<(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) { return (lhs < rhs); }
    template < typename T, class Alloc >
    bool operator<=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) { return (lhs <= rhs); }
    template < typename T, class Alloc >
    bool operator>(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) { return (lhs > rhs); }
    template < typename T, class Alloc >
    bool operator>=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) { return (lhs >= rhs); }
    
    template < typename T >
    void swap(List<T> &x, List<T> &y) {
        List<T> tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

}

#endif