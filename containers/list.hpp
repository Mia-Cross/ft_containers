/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:15 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/04 03:00:48 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../templates/doublyLinkedList.hpp"
# include <memory>
# include <iostream>
# include <limits>

namespace ft
{
    template < typename T, class Alloc = std::allocator<T> >
    class list {

        public :

            //defining every member in my list as in the STL
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
            explicit list(const allocator_type& alloc = allocator_type()) :
                _list(new dLList<T, Alloc>), _size(0), _alloc(alloc)
            { }
            // CONSTRUCTOR BY FILLING
            explicit list(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) : 
                _list(new dLList<T, Alloc>), _size(0), _alloc(alloc)
            {
                while (_size < n)
                    push_front(val);
            }
            // CONSTRUCTOR BY RANGE
            template <class InputIterator>
            list(InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type()) :
                _list(new dLList<T, Alloc>), _size(0), _alloc(alloc)
            {
                // while (first != last)
                //     push_back(*first++);
                assign(first, last);
            }
            // CONSTRUCTOR BY COPY
            list(const list &ref) : _list(new dLList<T, Alloc>),
                _size(0), _alloc(ref._alloc)
            {
                *this = ref;
            }
            // DESTRUCTOR
            ~list()
            {
                clear();
                delete _list;
            }
            // ASSIGNATION
            list &operator=(const list &ref)
            {
                resize(0);
                assign(ref.begin(), ref.end());
                return (*this);
            }

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(_list->getFirst()); }
            iterator        end() { return iterator(_list); }
            const_iterator  begin() const { return const_iterator(_list->getFirst()); }
            const_iterator  end() const { return const_iterator(_list); }
            reverse_iterator rbegin() { return reverse_iterator(_list->getLast()); }
            reverse_iterator rend() { return reverse_iterator(_list); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(_list->getLast()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(_list); }

            // ----- CAPACITY ----- //
            
            bool empty() const { return (_size == 0); }
            size_type size() const { return (_size); }
            size_type max_size() const { return (_alloc.max_size()); }

            // ----- ELEMENT ACCESS ----- //
            
            reference front() { return (_list->getFirst()->getContentRef()); }
            const_reference front() const { return (_list->getFirst()->getContentRef()); }
            reference back() { return (_list->getLast()->getContentRef()); }
            const_reference back() const { return (_list->getLast()->getContentRef()); }
            
            // ----- MODIFIERS ----- //
            
            template <class InputIterator>
            void assign(InputIterator first, InputIterator last) {
                clear();
                insert(begin(), first, last);
                // while (first != last)
                    // push_back(first++);
            }
            void assign(size_type n, const value_type &val) {
                clear();
                insert(begin(), n, val);
                // while (_size < n)
                //     push_back(val);
            }
            void push_front(const value_type &val) {
                dLList<T, Alloc> *elem = new dLList<T, Alloc>(val);
                _list->insertAfter(elem);
                _size++;
            }
            void pop_front() {
                if (!_size)
                    return ;
                _list->getFirst()->deleteElement();
                _size--;
            }
            void push_back(const value_type &val) {
                dLList<T, Alloc> *elem = new dLList<T, Alloc>(val);
                _list->insertBefore(elem);
                _size++;
            }
            void pop_back() {
                if (!_size)
                    return ;
                _list->getLast()->deleteElement();
                _size--;
            }
            iterator insert(iterator position, const value_type &val) {
                dLList<T, Alloc> *elem = _list->getElement(position.operator->());
                if (elem)
                {
                    elem->insertBefore(new dLList<T, Alloc>(val));
                    position--;
                    _size++;
                }
                return (position);
            }
            void insert(iterator position, size_type n, const value_type &val) {
                while (position != NULL && n--)
                    position = insert(position, val);
            }
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last) {
                while (position != NULL && first != last)
                    insert(position, *first++);
                // while (position != NULL && last != NULL && last != first)
                    // position = insert(position, *(--last));
            }
            iterator erase(iterator position) {
                dLList<T, Alloc> *elem = _list->getElement(position.operator->());
                if (elem && _size)
                {
                    position--;
                    elem->deleteElement();
                    _size--;
                }
                return (position);
            }
            iterator erase(iterator first, iterator last) {
                --last;
                while (last != NULL && last != first)
                    last = this->erase(last);
                return (last);
            }
            void swap(list &x) {
                list tmp(x);
                x = *this;
                *this = tmp;
            }
            void resize (size_type n, value_type val = value_type()) {
                while (_size < n)
                    this->push_back(val);
                while (_size > n)
                    this->pop_back();
            }
            void clear() { resize(0); }

            ////////////////////////////
            // ----- OPERATIONS ----- //
            ////////////////////////////
            
            // ----- SPLICE ----- //
            
            void splice(iterator position, list& x) {
                splice(position, x, x.begin(), x.end());
            }
            void splice(iterator position, list& x, iterator i) {
                dLList<T, Alloc> *dest = position.operator->();
                dLList<T, Alloc> *src = i.operator->();
                if (dest && src && x._size)
                {
                    src->extractElement();
                    dest->insertBefore(src);
                    this->_size++;
                    x._size--;
                }
            }
            void splice(iterator position, list& x, iterator first, iterator last) {
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
                        _size--;
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
                        _size--;
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
                        _size--;
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
                        _size--;
                        it--;
                    }
                }
            }

            // ----- MERGE ----- //
            
            void merge(list &x) {
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
            void merge(list &x, Compare comp) {
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
                _list->swapPointers();
            }
            
        private :

            dLList<T, Alloc>    *_list;
            size_type           _size;
            allocator_type      _alloc;
            difference_type     _diff;

    };

    template < typename T, class Alloc >
    bool operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return (lhs == rhs); }
    template < typename T, class Alloc >
    bool operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return (lhs != rhs); }
    template < typename T, class Alloc >
    bool operator<(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return (lhs < rhs); }
    template < typename T, class Alloc >
    bool operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return (lhs <= rhs); }
    template < typename T, class Alloc >
    bool operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return (lhs > rhs); }
    template < typename T, class Alloc >
    bool operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return (lhs >= rhs); }
    
    template < typename T >
    void swap(list<T> &x, list<T> &y) {
        list<T> tmp;
        tmp = x;
        x = y;
        y = tmp;
    }
    
    template < typename T >
    std::ostream &operator<<(std::ostream &out, list<T> const &list) {
        size_t size = list.size();
        out << "\t>> LIST [" << size << "]\t= { ";
        if (size)
        {
            for (typename ft::list<T>::const_iterator it = list.begin(); size-- > 0; it++)
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