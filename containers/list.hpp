/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:15 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/11 07:21:38 by lemarabe         ###   ########.fr       */
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

            List() : myList(new dLList<T>), mySize(0) {}
            ~List() { this->clear(); delete (&myList);}
            List(const List &ref) : mySize(ref.mySize) { *this = ref; }
            List &operator=(const List &ref) {
                this->clear();
                this->mySize = ref.mySize;
                for (iterator it = ref.begin(); it != ref.end(); it++)
                    this->push_back(*it);
                return (*this);
            }

            // ----- ITERATORS ----- //
            iterator begin() { return iterator(myList->getNthElement(0)->getValue()); }
            iterator end() { return iterator(myList->getNthElement(myList->getSize())->getValue());}
            // reverse_iterator rbegin() {}
            // reverse_iterator rend() {}
            const_iterator begin() const { return const_iterator(myList->getNthElement(0)->getValue()); }
            const_iterator end() const { return const_iterator(myList->getNthElement(myList->getSize())->getValue());}
            // const_reverse_iterator rbegin() const {}
            // const_reverse_iterator rend() const {}

            // ----- CAPACITY ----- //
            bool empty() const { return (myList->getSize() > 0); }
            size_type size() const { return (mySize); }
            size_type max_size() const { return (myAlloc.max_size()); }

            // ----- ELEMENT ACCESS ----- //
            reference front() { return reference(myList->getNthElement(0)->getValue()); }
            const_reference front() const { return const_reference(myList->getNthElement(0)->getValue()); }
            reference back() { return reference(myList->getNthElement(mySize)->getValue()); }
            const_reference back() const { return const_reference(myList->getNthElement(mySize)->getValue()); }

            // ----- MODIFIERS ----- //
            // void assign(iterator first, iterator last) { //InputIterator in cppreference.comm
            //     ///
            // }
            void assign(size_type n, const value_type &val) {
                dLList<value_type> *elemN = myList->getNthElement(n);
                if (elemN)
                    elemN->setValue(val);
            }
            void push_front(const value_type &val) { 
                myList->insertElement(myList->newElement(val), 0);
                mySize++;
            }
            void pop_front() {
                myList->deleteElement(0);
                mySize--;
            }
            void push_back(const value_type &val) {
                myList->insertElement(myList->newElement(val), mySize);
                mySize++;
            }
            void pop_back() {
                myList->deleteElement(mySize);
                mySize--;
            }
            // iterator insert(iterator position, const value_type &val) {}
            // void insert(iterator position, size_type n, const value_type &val) {}
            // void insert(iterator position, iterator first, iterator last) {}    //InputIterator in cppreference.comm
            // iterator erase(iterator position) {}
            // iterator erase(iterator first, iterator last) {}
            void swap(List &x) {
                List tmp = *this;
                *this = x;
                x = tmp;
            }
            void resize (size_type n, value_type val = value_type()) {
                if (n < mySize)
                {
                    myList->getNthElement(n)->next = NULL;
                    dLList<value_type> *limit = myList->getNthElement(n + 1);
                    limit->clear();
                }
                else
                {
                    for (size_t diff = n - mySize; diff; diff--)
                        push_back(val);
                }
            }
            void clear() { myList->clear(); }

            // ----- OPERATIONS ----- //
            // void splice (iterator position, List& x) {}
            // void splice (iterator position, List& x, iterator i) {}
            // void splice (iterator position, List& x, iterator first, iterator last) {}
            // void remove (const value_type &val) {}
            // template < class Predicate >
            // void remove_if (Predicate pred) {}
            // void unique() {}
            // template < class BinaryPredicate >
            // void unique(BinaryPredicate binary_pred) {}
            // void merge(List &x) {}
            // template < class Compare >
            // void merge(List &x, Compare comp) {}
            // void sort() {}
            // template < class Compare >
            // void sort(Compare comp) {}
            // void reverse() {}
            
        private :

            dLList<T>       *myList;  //?
            allocator_type  myAlloc;
            size_type       mySize;
            difference_type myDiff;

    };

    template < typename T, class Alloc >
    bool operator==(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs) { return (lhs == rhs); }
    template < typename T, class Alloc >
    bool operator!=(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs) { return (lhs != rhs); }
    template < typename T, class Alloc >
    bool operator<(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs) { return (lhs < rhs); }
    template < typename T, class Alloc >
    bool operator<=(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs) { return (lhs <= rhs); }
    template < typename T, class Alloc >
    bool operator>(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs) { return (lhs > rhs); }
    template < typename T, class Alloc >
    bool operator>=(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs) { return (lhs >= rhs); }
    
    template < typename T >
    void swap(List<T> &x, List<T> &y) {
        List<T> tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

}

#endif