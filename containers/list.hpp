/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:15 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/22 22:18:57 by lemarabe         ###   ########.fr       */
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
            typedef T                                       value_type;
            typedef Alloc                                   allocator_type;
            typedef T &                                     reference;
            typedef T *                                     pointer;
            typedef const T &	                            const_reference;
            typedef const T *	                            const_pointer;
            typedef myIterator< T, dLList<T> >              iterator;
            typedef myConstIterator< T, dLList<T> >         const_iterator;
            typedef myReverseIterator< T, dLList<T> >       reverse_iterator;
            typedef myConstReverseIterator< T, dLList<T> >  const_reverse_iterator;
            typedef size_t                                  size_type;
            typedef ptrdiff_t                               difference_type;

            List() : myList(new dLList<T, Alloc>), mySize(0) {
                myList->insertAfter(new dLList<T, Alloc>);
            }
            ~List() {
                this->clear();
            }
            List(const List &ref) : myList(new dLList<T, Alloc>), mySize(0) {
                myList->insertAfter(new dLList<T, Alloc>);
                *this = ref;
            }
            List &operator=(const List &ref) {
                std::cout << "\\" << mySize << std::endl;
                if (this->mySize)
                   this->erase(myList->getFirstElement(), myList->getTail());
                this->mySize = ref.mySize;
                std::cout << "/" << mySize << std::endl;
                for (typename List<T>::const_iterator it = ref.begin(); it != ref.end(); it++)
                {
                    std::cout << "+" << *it << std::endl;
                    this->push_back(*it);
                }
                return (*this);
            }

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(myList->getFirstElement()); }
            iterator        end() { return iterator(myList->getTail()); }
            const_iterator  begin() const { return const_iterator(myList->getFirstElement()); }
            const_iterator  end() const { return const_iterator(myList->getTail()); }
            reverse_iterator rbegin() { return reverse_iterator(myList->getLastElement()); }
            reverse_iterator rend() { return reverse_iterator(myList->getHead()); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(myList->getLastElement()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(myList->getHead()); }

            // ----- CAPACITY ----- //
            
            bool empty() const { return (mySize == 0); }
            size_type size() const { return (mySize); }
            size_type max_size() const { return (myAlloc.max_size()); }

            // ----- ELEMENT ACCESS ----- //
            
            reference front() { return (myList->getFirstElement()->getContentRef()); }
            const_reference front() const { return (myList->getFirstElement()->getContentRef()); }
            reference back() { return (myList->getLastElement()->getContentRef()); }
            const_reference back() const { return (myList->getLastElement()->getContentRef()); }

            // ----- MODIFIERS ----- //
            
            void assign(iterator first, iterator last) {
                for (iterator it = first; it != last; it++)
                    push_back(*it);
            }
            void assign(size_type n, const value_type &val) {
                while (mySize < n)
                    push_back(val);
            }
            void push_front(const value_type &val) {
                myList->getHead()->insertAfter(new dLList<T, Alloc>(val));
                mySize++;
            }
            void pop_front() {
                myList->getFirstElement()->deleteElement();
                mySize--;
            }
            void push_back(const value_type &val) {
                myList->getTail()->insertBefore(new dLList<T, Alloc>(val));
                mySize++;
            }
            void pop_back() {
                myList->getLastElement()->deleteElement();
                mySize--;
            }
            iterator insert(iterator position, const value_type &val) {
                dLList<T, Alloc> *elem = myList->getElement(position.operator->());
                // std::cout << "I want to add " << val<< std::endl;
                // std::cout << elem << elem->getContentRef() ;
                if (elem)
                {
                    elem->insertBefore(new dLList<T, Alloc>(val));
                    mySize++;
                    return (iterator(elem->getPrev()));
                }
                return (position);
            }
            void insert(iterator position, size_type n, const value_type &val) {
                while (position != NULL && n--)
                    position = this->insert(position, val);
            }
            void insert(iterator position, iterator first, iterator last) {
                while (position != NULL && last != first)
                    position = this->insert(position, *(--last));
                // if (position != NULL)
                //     position = this->insert(position, *(first));
            }
            iterator erase(iterator position) {
                dLList<T, Alloc> *elem = myList->getElement(position.operator->());
                position--;
                if (elem)
                    elem->deleteElement();
                return (position);
            }
            iterator erase(iterator first, iterator last) {
                --last;
                while (last != NULL && last != first)
                    last = this->erase(last);
                return (last);
            }
            void swap(List &x) {
                std::cout << "1" << std::endl;
                List *tmp = new List(*this);
                // List tmp = *this;
                std::cout << "2" << std::endl;
                *this = x;
                // *this = x;
                std::cout << "3" << std::endl;
                x = *tmp;
                // x = tmp;
                std::cout << "4" << std::endl;
            }
            void resize (size_type n, value_type val = value_type()) {
                dLList<T, Alloc> *limit = myList->getElement(n);
                if (limit)
                    this->erase(iterator(limit), myList->getTail());
                else
                {
                    while (mySize < n)
                        this->push_back(val);
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
        out << "\t>> LIST = { ";
        if (!list.empty())
        {
            for (typename List<T>::const_iterator it = list.begin(); it != list.end(); it++)
                out << "[" << *it << "]";
        }
        out << " }" << std::endl;
        return (out);
    }
}

#endif