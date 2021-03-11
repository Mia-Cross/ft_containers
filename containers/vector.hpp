/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 06:19:44 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/11 23:27:12 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "../templates/myIterator.hpp"
# include "../templates/dynamicArray.hpp"
# include <memory>
# include <iostream>

namespace ft
{
    template < typename T, class Alloc = std::allocator<T> >
    class Vector {

        public :

            //defining every member in my Vector as in the STL
            typedef T                                       value_type;
            typedef Alloc                                   allocator_type;
            typedef T &                                     reference;
            typedef T *                                     pointer;
            typedef const T &	                            const_reference;
            typedef const T *	                            const_pointer;
            typedef myAccessIterator<T>        iterator;
            // typedef myCIterator< T, dynArr<T,Alloc> >       const_iterator;
            // typedef myRIterator< T, dynArr<T,Alloc> >       reverse_iterator;
            // typedef myCRIterator< T, dynArr<T,Alloc> >      const_reverse_iterator;
            typedef size_t                                  size_type;
            typedef ptrdiff_t                               difference_type;

            // DEFAULT CONSTRUCTOR
            explicit Vector(const allocator_type& alloc = allocator_type()) :
                myVect(), mySize(0), myAlloc(alloc)
            { }
            // CONSTRUCTOR BY FILLING
            explicit Vector(size_type n, const value_type &val = value_type(),
                const allocator_type& alloc = allocator_type()) :
                myVect(n), mySize(n), myAlloc(alloc)
            {
                for (size_t i = 0; i < n; i++)
                    myVect.addElement(val);
            }
            // CONSTRUCTOR BY RANGE
            Vector(iterator first, iterator last,
                const allocator_type& alloc = allocator_type()) :
                myVect(), mySize(0), myAlloc(alloc)
            {
                while (first != last)
                    push_back(*first++);
                // for (size_t size = 0 && iterator it = first; it != last; i++)
                //     size++;
                // myVect = new dynArr(size);
                // while (first != last)
                //     push_back(*first++);
            }
            // CONSTRUCTOR BY COPY
            Vector(const Vector &ref) : myVect(ref.mySize),
                mySize(ref.mySize), myAlloc(ref.myAlloc)
            {
                *this = ref;
            }
            // DESTRUCTOR
            ~Vector()
            { // delete myVect;
             }
            // ASSIGNATION
            const Vector &operator=(const Vector &ref)
            {
                this->myVect = ref.myVect;
                this->mySize = ref.mySize;
                return (*this);
            }

            // ----- ITERATORS ----- //
            
            // iterator        begin() { return iterator(myVector->getFirst()); }
            // iterator        end() { return iterator(myVector); }
            // const_iterator  begin() const { return const_iterator(myVector->getFirst()); }
            // const_iterator  end() const { return const_iterator(myVector); }
            // reverse_iterator rbegin() { return reverse_iterator(myVector->getLast()); }
            // reverse_iterator rend() { return reverse_iterator(myVector); }
            // const_reverse_iterator rbegin() const { return const_reverse_iterator(myVector->getLast()); }
            // const_reverse_iterator rend() const { return const_reverse_iterator(myVector); }

            // ----- CAPACITY ----- //
            
            size_type size() const { return (mySize); }
            size_type max_size() const { return (myAlloc.max_size()); }
            void resize(size_type n, value_type val = value_type()) {
                while (mySize < n)
                    this->push_back(val);
                while (mySize > n)
                    this->pop_back();
            }
            size_type capacity() const { return (myVect.getCapacity()); }
            bool empty() const { return (mySize == 0); }
            // void reserve(size_type n) {}
            
            // ----- ELEMENT ACCESS ----- //
            
            // reference front() { return (myVector->getFirst()->getContentRef()); }
            // const_reference front() const { return (myVector->getFirst()->getContentRef()); }
            // reference back() { return (myVector->getLast()->getContentRef()); }
            // const_reference back() const { return (myVector->getLast()->getContentRef()); }
            reference operator[](size_type n) {
                if (n < mySize)
                    return (*(myVect + n));
                return (myVect.throwNulRef());
            }
            const_reference operator[] (size_type n) const {
                if (n < mySize)
                    return (*(myVect + n));
                return (myVect.throwNulRef());
            }
            // reference at (size_type n);
            // const_reference at (size_type n) const;
            
            // ----- MODIFIERS ----- //
            
            // void assign(iterator first, iterator last) {
            //     while (first != last)
            //         push_back(*first++);
            // }
            // void assign(size_type n, const value_type &val) {
            //     while (mySize < n)
            //         push_back(val);
            // }
            void push_back(const value_type &val) {
                // std::cout << mySize << std::endl;
                myVect.addElement(val);
                mySize++;
            }
            void pop_back() {
                // std::cout << mySize << std::endl;
                if (mySize)
                    myVect.deleteElement(--mySize);
            }
            // iterator insert(iterator position, const value_type &val) {
            //     dLVector<T, Alloc> *elem = myVector->getElement(position.operator->());
            //     if (elem)
            //     {
            //         elem->insertBefore(new dLVector<T, Alloc>(val));
            //         position--;
            //         mySize++;
            //     }
            //     return (position);
            // }
            // void insert(iterator position, size_type n, const value_type &val) {
            //     while (position != NULL && n--)
            //         position = this->insert(position, val);
            // }
            // void insert(iterator position, iterator first, iterator last) {
            //     while (position != NULL && last != NULL && last != first)
            //         position = this->insert(position, *(--last));
            // }
            // iterator erase(iterator position) {
            //     dLVector<T, Alloc> *elem = myVector->getElement(position.operator->());
            //     if (elem && mySize)
            //     {
            //         position--;
            //         elem->deleteElement();
            //         mySize--;
            //     }
            //     return (position);
            // }
            // iterator erase(iterator first, iterator last) {
            //     --last;
            //     while (last != NULL && last != first)
            //         last = this->erase(last);
            //     return (last);
            // }
            // void swap(Vector &x) {
            //     Vector tmp(x);
            //     x = *this;
            //     *this = tmp;
            // }
            // void clear() { resize(0); }

            // ADDITION ( ONLY FOR DISPLAY )
            T *getDynArray() const { return (myVect.getArray()); }

        private :

            dynArr<T,Alloc> myVect;
            size_type       mySize;
            allocator_type  myAlloc;
            difference_type myDiff;

    };

    template < typename T, class Alloc >
    bool operator==(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) { return (lhs == rhs); }
    template < typename T, class Alloc >
    bool operator!=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) { return (lhs != rhs); }
    template < typename T, class Alloc >
    bool operator<(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) { return (lhs < rhs); }
    template < typename T, class Alloc >
    bool operator<=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) { return (lhs <= rhs); }
    template < typename T, class Alloc >
    bool operator>(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) { return (lhs > rhs); }
    template < typename T, class Alloc >
    bool operator>=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) { return (lhs >= rhs); }
    
    template < typename T >
    void swap(Vector<T> &x, Vector<T> &y) {
        Vector<T> tmp;
        tmp = x;
        x = y;
        y = tmp;
    }
    
    template < typename T >
    std::ostream &operator<<(std::ostream &out, Vector<T> const &Vector) {
        T *arr = Vector.getDynArray();
        // size_t size = 2;
        size_t size = Vector.size();
        out << "\t>> VECTOR [" << size << "]\t= { ";
        while (size-- > 0)
        {
            out << *arr++;
            if (size)
                out << ", ";
        }
        out << " }" << std::endl;
        return (out);
    }
};

#endif