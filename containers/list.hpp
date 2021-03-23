/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:15 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/23 02:21:05 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../templates/doublyLinkedList.hpp"
# include <memory>
# include <iostream>

namespace ft
{
    template < typename T, class Alloc = std::allocator<T> >
    class List {

        public :

            //defining every member in my List as in the STL
            typedef T                       value_type;
            typedef Alloc                   allocator_type;
            typedef T &                     reference;
            typedef T *                     pointer;
            typedef const T &	            const_reference;
            typedef const T *	            const_pointer;
            typedef listIter<T, Alloc>      iterator;
            typedef cListIter<T, Alloc>     const_iterator;
            typedef rListIter<T, Alloc>     reverse_iterator;
            typedef crListIter<T, Alloc>    const_reverse_iterator;
            typedef size_t                  size_type;
            typedef ptrdiff_t               difference_type;

            // DEFAULT CONSTRUCTOR
            explicit List(const allocator_type& alloc = allocator_type()) :
                myList(new dLList<T, Alloc>), mySize(0), myAlloc(alloc)
            { }
            // CONSTRUCTOR BY FILLING
            explicit List(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) : 
                myList(new dLList<T, Alloc>), mySize(0), myAlloc(alloc)
            {
                while (mySize < n)
                    push_front(val);
            }
            // CONSTRUCTOR BY RANGE
            List(iterator first, iterator last,
                const allocator_type& alloc = allocator_type()) :
                myList(new dLList<T, Alloc>), mySize(0), myAlloc(alloc)
            {
                while (first != last)
                    push_back(*first++);
            }
            // CONSTRUCTOR BY COPY
            List(const List &ref) : myList(new dLList<T, Alloc>),
                mySize(0), myAlloc(ref.myAlloc)
            {
                *this = ref;
            }
            // DESTRUCTOR
            ~List()
            {
                this->clear();
                delete myList;
            }
            // ASSIGNATION
            List &operator=(const List &ref)
            {
                resize(0);
                assign(ref.begin(), ref.end());
                return (*this);
            }

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(myList->getFirst()); }
            iterator        end() { return iterator(myList); }
            const_iterator  begin() const { return const_iterator(myList->getFirst()); }
            const_iterator  end() const { return const_iterator(myList); }
            reverse_iterator rbegin() { return reverse_iterator(myList->getLast()); }
            reverse_iterator rend() { return reverse_iterator(myList); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(myList->getLast()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(myList); }

            // ----- CAPACITY ----- //
            
            bool empty() const { return (mySize == 0); }
            size_type size() const { return (mySize); }
            size_type max_size() const { return (myAlloc.max_size()); }

            // ----- ELEMENT ACCESS ----- //
            
            reference front() { return (myList->getFirst()->getContentRef()); }
            const_reference front() const { return (myList->getFirst()->getContentRef()); }
            reference back() { return (myList->getLast()->getContentRef()); }
            const_reference back() const { return (myList->getLast()->getContentRef()); }
            
            // ----- MODIFIERS ----- //
            
            void assign(iterator first, iterator last) {
                while (first != last)
                    push_back(*first++);
            }
            void assign(size_type n, const value_type &val) {
                while (mySize < n)
                    push_back(val);
            }
            void push_front(const value_type &val) {
                dLList<T, Alloc> *elem = new dLList<T, Alloc>(val);
                myList->insertAfter(elem);
                mySize++;
            }
            void pop_front() {
                if (!mySize)
                    return ;
                myList->getFirst()->deleteElement();
                mySize--;
            }
            void push_back(const value_type &val) {
                dLList<T, Alloc> *elem = new dLList<T, Alloc>(val);
                myList->insertBefore(elem);
                mySize++;
            }
            void pop_back() {
                if (!mySize)
                    return ;
                myList->getLast()->deleteElement();
                mySize--;
            }
            iterator insert(iterator position, const value_type &val) {
                dLList<T, Alloc> *elem = myList->getElement(position.operator->());
                if (elem)
                {
                    elem->insertBefore(new dLList<T, Alloc>(val));
                    position--;
                    mySize++;
                }
                return (position);
            }
            void insert(iterator position, size_type n, const value_type &val) {
                while (position != NULL && n--)
                    position = this->insert(position, val);
            }
            void insert(iterator position, iterator first, iterator last) {
                while (position != NULL && last != NULL && last != first)
                    position = this->insert(position, *(--last));
            }
            iterator erase(iterator position) {
                dLList<T, Alloc> *elem = myList->getElement(position.operator->());
                if (elem && mySize)
                {
                    position--;
                    elem->deleteElement();
                    mySize--;
                }
                return (position);
            }
            iterator erase(iterator first, iterator last) {
                --last;
                while (last != NULL && last != first)
                    last = this->erase(last);
                return (last);
            }
            void swap(List &x) {
                List tmp(x);
                x = *this;
                *this = tmp;
            }
            void resize (size_type n, value_type val = value_type()) {
                while (mySize < n)
                    this->push_back(val);
                while (mySize > n)
                    this->pop_back();
            }
            void clear() { resize(0); }

            ////////////////////////////
            // ----- OPERATIONS ----- //
            ////////////////////////////
            
            // ----- SPLICE ----- //
            
            void splice(iterator position, List& x) {
                splice(position, x, x.begin(), x.end());
            }
            void splice(iterator position, List& x, iterator i) {
                dLList<T, Alloc> *dest = position.operator->();
                dLList<T, Alloc> *src = i.operator->();
                if (dest && src && x.mySize)
                {
                    src->extractElement();
                    dest->insertBefore(src);
                    this->mySize++;
                    x.mySize--;
                }
            }
            void splice(iterator position, List& x, iterator first, iterator last) {
                --last;
                while (last != NULL && last != first)
                    splice(position, x, last--);
                splice(position, x, first);
            }
            
            // ----- REMOVE ----- //
            
            void remove (const value_type &val) {
                iterator it = begin();
                while (it != end())
                {
                    if (*it == val)
                    {
                        dLList<T, Alloc> *to_remove = it++.operator->();
                        to_remove->deleteElement();
                        mySize--;
                    }
                    else
                        it++;
                }
            }
            template < class Predicate >
            void remove_if (Predicate pred) {
                iterator it = begin();
                while (it != end())
                {
                    if (pred(*it) == true)
                    {
                        dLList<T, Alloc> *to_remove = it++.operator->();
                        to_remove->deleteElement();
                        mySize--;
                    }
                    else
                        it++;
                }
            }

            // ----- UNIQUE ----- //
            
            void unique() {
                iterator it = begin();
                while (it != end())
                {
                    iterator comp = it++;
                    if (*it == *comp)
                    {
                        dLList<T, Alloc> *to_remove = it++.operator->();
                        to_remove->deleteElement();
                        mySize--;
                        it--;
                    }
                }
            }
            template < class BinaryPredicate >
            void unique(BinaryPredicate binary_pred) {
                iterator it = begin();
                while (it != end())
                {
                    iterator comp = it++;
                    if (binary_pred(*comp, *it) == true)
                    {
                        dLList<T, Alloc> *to_remove = it++.operator->();
                        to_remove->deleteElement();
                        mySize--;
                        it--;
                    }
                }
            }

            // ----- MERGE ----- //
            
            void merge(List &x) {
                iterator itx = x.begin();
                iterator ity = this->begin();
                while (itx != x.end())
                {
                    if (*itx < *ity || ity == this->end())
                        splice(ity, x, itx++);
                    else
                        ity++;
                }
            }
            template < class Compare >
            void merge(List &x, Compare comp) {
                iterator itx = x.begin();
                iterator ity = this->begin();
                while (itx != x.end())
                {
                    if (comp(*itx, *ity) || ity == this->end())
                        splice(ity, x, itx++);
                    else
                        ity++;
                }
            }

            // ----- SORT ----- //

            void sort() {
                iterator it = begin();
                while (it != end())
                {
                    iterator current = it++;
                    if (*it < *current && it != end())
                    {
                        dLList<T, Alloc> *elem = current.operator->();
                        elem->swapWithNext();
                        it = begin();
                    }
                }
            }
            template < class Compare >
            void sort(Compare comp) {
                iterator it = begin();
                while (it != end())
                {
                    iterator current = it++;
                    if (comp(*it, *current) && it != end())
                    {
                        dLList<T, Alloc> *elem = current.operator->();
                        elem->swapWithNext();
                        it = begin();
                    }
                }
            }

            // ----- REVERSE ----- //

            void reverse() {
                iterator it = begin();
                while (it != end())
                {
                    dLList<T, Alloc> *elem = it++.operator->();
                    elem->swapPointers();
                }
                myList->swapPointers();
            }
            
        private :

            dLList<T, Alloc>    *myList;
            size_type           mySize;
            allocator_type      myAlloc;
            difference_type     myDiff;

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
    
    template < typename T >
    std::ostream &operator<<(std::ostream &out, List<T> const &list) {
        size_t size = list.size();
        out << "\t>> LIST [" << size << "]\t= { ";
        if (size)
        {
            for (typename List<T>::const_iterator it = list.begin(); size-- > 0; it++)
            {
                out << *it;
                if (size)
                    out << ", ";
            }
        }
        out << " }" << std::endl;
        return (out);
    }
}

#endif