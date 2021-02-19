/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:15 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/19 03:04:28 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

#include "../utils/myIterator.hpp"
#include "../utils/doublyLinkedList.hpp"
#include <memory>

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
			typedef myIterator< T, dLList<T> >              iterator;
			typedef myConstIterator< T, dLList<T> >         const_iterator;           //not exactly
			typedef myReverseIterator< T, dLList<T> >       reverse_iterator;         //not exactly
			typedef myConstReverseIterator< T, dLList<T> >  const_reverse_iterator;     //not exactly
			typedef size_t		            size_type;
			typedef ptrdiff_t	            difference_type;

            List() : myList(new dLList<T, Alloc>), mySize(0) {}
            ~List() { delete (myList);}
            List(const List &ref) : myList(new dLList<T, Alloc>) { *this = ref; }
            List &operator=(const List &ref) {
                if (this->mySize)
                    this->clear();
                this->mySize = ref.mySize;
                for (typename List<T>::const_iterator it = ref.begin(); it != ref.end(); it++)
                    this->push_back(*it);
                return (*this);
            }

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(myList->getFirstElement()); }
            iterator        end() { return iterator(myList->getLastElem()->getNext()); }
            const_iterator  begin() const { return const_iterator(myList->getFirstElement()); }
            const_iterator  end() const { return const_iterator(myList->getLastElem()->getNext()); }
            reverse_iterator rbegin() { return reverse_iterator(myList->getLastElem()); }
            reverse_iterator rend() { return reverse_iterator(myList); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(myList->getLastElem()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(myList); }

            // ----- CAPACITY ----- //
            
            bool empty() const { return (mySize == 0); }
            size_type size() const { return (mySize); }
            size_type max_size() const { return (myAlloc.max_size()); }

            // ----- ELEMENT ACCESS ----- //
            
            reference front() { return (myList->getFirstElement()->getContentRef()); }
            const_reference front() const { return (myList->getFirstElement()->getContentRef()); }
            reference back() { return (myList->getLastElem()->getContentRef()); }
            const_reference back() const { return (myList->getLastElem()->getContentRef()); }

            // ----- MODIFIERS ----- //
            
            // void assign(iterator first, iterator last) { //InputIterator in cppreference.comm
            //     ///
            // }
            void assign(size_type n, const value_type &val) {
                dLList<T, Alloc> *elem = myList->getElement(n);
                if (elem)
                    elem->setContent(val);
            }
            void push_front(const value_type &val) {
                dLList<T, Alloc> *to_add = new dLList<T, Alloc>(val);
                myList->getHead()->insert(*to_add);
                mySize++;

            }
            void pop_front() {
                myList->getFirstElement()->deleteElement();
                mySize--;
            }
            void push_back(const value_type &val) {
                dLList<T, Alloc> *to_add = new dLList<T, Alloc>(val);
                myList->getLastElem()->insert(*to_add);
                mySize++;

            }
            void pop_back() {
                myList->getLastElem()->deleteElement();
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
                    dLList<T, Alloc> *limit = myList->getElement(n);
                    limit->clearFromIndex(n);
                    limit->next = NULL;
                }
                else
                {
                    for (size_t diff = n - mySize; diff; diff--)
                        push_back(val);
                }
            }
            void clear() { myList->clearDLL(); }

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

            dLList<T, Alloc>    *myList;
            allocator_type      myAlloc;
            size_type           mySize;
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
        out << "LIST = [";
        if (!list.empty())
        {
            for (typename List<T>::const_iterator it = list.begin(); it != list.end(); it++)
                out << *it << "][";
        }
        out << "]" << std::endl;
        return (out);
    }
}

#endif