/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 06:19:44 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/13 02:47:43 by lemarabe         ###   ########.fr       */
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
            typedef T                       value_type;
            typedef Alloc                   allocator_type;
            typedef T &                     reference;
            typedef T *                     pointer;
            typedef const T &	            const_reference;
            typedef const T *	            const_pointer;
            typedef myAccessIterator<T>     iterator;
            typedef myCAccessIterator<T>    const_iterator;
            typedef myRAccessIterator<T>    reverse_iterator;
            typedef myCRAccessIterator<T>   const_reverse_iterator;
            typedef size_t                  size_type;
            typedef ptrdiff_t               difference_type;

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
            }
            // CONSTRUCTOR BY COPY
            Vector(const Vector &ref) : myVect(ref.mySize),
                mySize(ref.mySize), myAlloc(ref.myAlloc)
            {
                *this = ref;
            }
            // DESTRUCTOR
            ~Vector()
            { }
            // ASSIGNATION
            const Vector &operator=(const Vector &ref)
            {
                this->myVect = ref.myVect;
                this->mySize = ref.mySize;
                return (*this);
            }

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(myVect.getArray()); }
            iterator        end() { return iterator(myVect.getArray() + mySize); }
            const_iterator  begin() const { return const_iterator(myVect.getArray()); }
            const_iterator  end() const { return const_iterator(myVect.getArray() + mySize); }
            reverse_iterator rbegin() { return reverse_iterator(myVect.getArray() + mySize - 1); }
            reverse_iterator rend() { return reverse_iterator(myVect.getArray() - 1); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(myVect.getArray() + mySize - 1); }
            const_reverse_iterator rend() const { return const_reverse_iterator(myVect.getArray() - 1); }

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
            void reserve(size_type n) {
                if (capacity() < n)
                    myVect.reallocateArray(n);
            }
            
            // ----- ELEMENT ACCESS ----- //
            
            reference front() {
                if (mySize)
                    return (*(myVect.getArray()));
                return (myVect.throwNulRef());
            }
            const_reference front() const { 
                 if (mySize)
                    return (*(myVect.getArray()));
                return (myVect.throwNulRef());
            }
            reference back() {
                if (mySize)
                    return (*(myVect.getArray() + mySize - 1));
                return (myVect.throwNulRef());
            }
            const_reference back() const {
                if (mySize)
                    return (*(myVect.getArray() + mySize - 1));
                return (myVect.throwNulRef());
            }
            reference operator[](size_type n) {
                return (*(myVect.getArray() + n));
            }
            const_reference operator[] (size_type n) const {
                return (*(myVect.getArray() + n));
            }
            reference at (size_type n) {
                if (n < mySize)
                    return (*(myVect.getArray() + n));
                return (myVect.throwNulRef());
            }
            const_reference at (size_type n) const {
                if (n < mySize)
                    return (*(myVect.getArray() + n));
                return (myVect.throwNulRef());
            }
            
            // ----- MODIFIERS ----- //
            
            void assign(iterator first, iterator last) {
                while (first != last)
                    push_back(*first++);
            }
            void assign(size_type n, const value_type &val) {
                while (mySize < n)
                    push_back(val);
            }
            void push_back(const value_type &val) {
                myVect.addElement(val);
                mySize++;
            }
            void pop_back() {
                if (mySize)
                    myVect.deleteElements(--mySize, 1);
            }
            iterator insert(iterator position, const value_type &val) {
                size_t index = position.distanceBetween(begin(), position);
                if (capacity() <= mySize + 1)
                    myVect.reallocateSplitArray(index, 1);
                myVect.constructValue(index, val);
                myVect.incrementSize(1);
                mySize++;
                return (position);
            }
            void insert(iterator position, size_type n, const value_type &val) {
                size_t index = position.distanceBetween(begin(), position);
                if (capacity() <= mySize + n)
                    myVect.reallocateSplitArray(index, n);
                for (size_t i = 0; i < n; i++)
                    myVect.constructValue(index + i, val);
                myVect.incrementSize(n);
                mySize += n;
            }
            void insert(iterator position, iterator first, iterator last) {
                size_t index = position.distanceBetween(begin(), position);
                size_t dist = first.distanceBetween(first, last);
                if (capacity() <= mySize + dist)
                    myVect.reallocateSplitArray(index, dist);
                while (index < mySize + dist && first != last)
                    myVect.constructValue(index++, *first++);
                mySize += dist;
            }
            iterator erase(iterator position) {
                if (mySize)
                {
                    iterator to_erase = position--;
                    myVect.deleteElements(position.distanceBetween(begin(), to_erase), 1);
                    mySize--;
                }
                return (position);
            }
            iterator erase(iterator first, iterator last) {
                size_t dist = first.distanceBetween(first, last);
                myVect.deleteElements(first.distanceBetween(begin(), first), dist);
                mySize -= dist;
                return (last);
            }
            void swap(Vector &x) {
                Vector tmp(x);
                x = *this;
                *this = tmp;
            }
            void clear() { resize(0); }

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
    std::ostream &operator<<(std::ostream &out, Vector<T> const &vect) {
        size_t size = vect.size();
        out << "\t>> VECTOR [" << size << "]\t= { ";
        for (typename Vector<T>::const_iterator it = vect.begin(); size-- > 0; it++)
        {
            out << *it;
            if (size)
                out << ", ";
        }
        out << " }" << std::endl;
        return (out);
    }
};

#endif