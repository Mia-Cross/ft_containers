/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 06:19:44 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/04 04:01:00 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "../templates/dynamicArray.hpp"
# include <memory>
# include <iostream>

namespace ft
{
    template < typename T, class Alloc = std::allocator<T> >
    class vector {

        public :

            //defining every member in my vector as in the STL
            typedef T                   value_type;
            typedef Alloc               allocator_type;
            typedef T &                 reference;
            typedef T *                 pointer;
            typedef const T &	        const_reference;
            typedef const T *	        const_pointer;
            typedef vectIter<T,Alloc>   iterator;
            typedef cVectIter<T,Alloc>  const_iterator;
            typedef rVectIter<T,Alloc>  reverse_iterator;
            typedef crVectIter<T,Alloc> const_reverse_iterator;
            typedef size_t              size_type;
            typedef ptrdiff_t           difference_type;

            // DEFAULT CONSTRUCTOR
            explicit vector(const allocator_type& alloc = allocator_type()) :
                _array(), _size(0), _alloc(alloc)
            { }
            // CONSTRUCTOR BY FILLING
            explicit vector(size_type n, const value_type &val = value_type(),
                const allocator_type& alloc = allocator_type()) :
                _array(n), _size(n), _alloc(alloc)
            {
                for (size_t i = 0; i < n; i++)
                    _array.addElement(val);
            }
            // CONSTRUCTOR BY RANGE
            vector(iterator first, iterator last,
                const allocator_type& alloc = allocator_type()) :
                _array(), _size(0), _alloc(alloc)
            {
                while (first != last)
                    push_back(*first++);
            }
            // CONSTRUCTOR BY COPY
            vector(const vector &ref) : _array(ref._size),
                _size(ref._size), _alloc(ref._alloc)
            {
                *this = ref;
            }
            // DESTRUCTOR
            ~vector()
            { }
            // ASSIGNATION
            const vector &operator=(const vector &ref)
            {
                this->_array = ref._array;
                this->_size = ref._size;
                return (*this);
            }

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(_array.getArray()); }
            iterator        end() { return iterator(_array.getArray() + _size); }
            const_iterator  begin() const { return const_iterator(_array.getArray()); }
            const_iterator  end() const { return const_iterator(_array.getArray() + _size); }
            reverse_iterator rbegin() { return reverse_iterator(_array.getArray() + _size - 1); }
            reverse_iterator rend() { return reverse_iterator(_array.getArray() - 1); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(_array.getArray() + _size - 1); }
            const_reverse_iterator rend() const { return const_reverse_iterator(_array.getArray() - 1); }

            // ----- CAPACITY ----- //
            
            size_type size() const { return (_size); }
            size_type max_size() const { return (_alloc.max_size()); }
            void resize(size_type n, value_type val = value_type()) {
                while (_size < n)
                    this->push_back(val);
                while (_size > n)
                    this->pop_back();
            }
            size_type capacity() const { return (_array.getCapacity()); }
            bool empty() const { return (_size == 0); }
            void reserve(size_type n) {
                if (capacity() < n)
                    _array.reallocateArray(n);
            }
            
            // ----- ELEMENT ACCESS ----- //
            
            reference front() {
                if (_size)
                    return (*(_array.getArray()));
                return (_array.throwNulRef());
            }
            const_reference front() const { 
                 if (_size)
                    return (*(_array.getArray()));
                return (_array.throwNulRef());
            }
            reference back() {
                if (_size)
                    return (*(_array.getArray() + _size - 1));
                return (_array.throwNulRef());
            }
            const_reference back() const {
                if (_size)
                    return (*(_array.getArray() + _size - 1));
                return (_array.throwNulRef());
            }
            reference operator[](size_type n) {
                return (*(_array.getArray() + n));
            }
            const_reference operator[] (size_type n) const {
                return (*(_array.getArray() + n));
            }
            reference at (size_type n) {
                if (n < _size)
                    return (*(_array.getArray() + n));
                return (_array.throwNulRef());
            }
            const_reference at (size_type n) const {
                if (n < _size)
                    return (*(_array.getArray() + n));
                return (_array.throwNulRef());
            }
            
            // ----- MODIFIERS ----- //
            
            void assign(iterator first, iterator last) {
                while (first != last)
                    push_back(*first++);
            }
            void assign(size_type n, const value_type &val) {
                while (_size < n)
                    push_back(val);
            }
            void push_back(const value_type &val) {
                _array.addElement(val);
                _size++;
            }
            void pop_back() {
                if (_size)
                    _array.deleteElements(--_size, 1);
            }
            iterator insert(iterator position, const value_type &val) {
                size_t index = position.distanceBetween(begin(), position);
                if (capacity() <= _size + 1)
                    _array.reallocateSplitArray(index, 1);
                _array.constructValue(index, val);
                _array.incrementSize(1);
                _size++;
                return (position);
            }
            void insert(iterator position, size_type n, const value_type &val) {
                // std::cout << "insert - begin" << std::endl;
                size_t index = position.distanceBetween(begin(), position);
                // std::cout << "nyaaaa" << std::endl;
                if (capacity() <= _size + n)
                    _array.reallocateSplitArray(index, n);
                for (size_t i = 0; i < n; i++)
                    _array.constructValue(index + i, val);
                _array.incrementSize(n);
                _size += n;
                // std::cout << "insert - end" << std::endl;
            }
            void insert(iterator position, iterator first, iterator last) {
                size_t index = position.distanceBetween(begin(), position);
                size_t dist = first.distanceBetween(first, last);
                if (capacity() <= _size + dist)
                    _array.reallocateSplitArray(index, dist);
                while (index < _size + dist && first != last)
                    _array.constructValue(index++, *first++);
                _size += dist;
            }
            iterator erase(iterator position) {
                if (_size)
                {
                    iterator to_erase = position--;
                    _array.deleteElements(position.distanceBetween(begin(), to_erase), 1);
                    _size--;
                }
                return (position);
            }
            iterator erase(iterator first, iterator last) {
                size_t dist = first.distanceBetween(first, last);
                _array.deleteElements(first.distanceBetween(begin(), first), dist);
                _size -= dist;
                return (last);
            }
            void swap(vector &x) {
                vector tmp(x);
                x = *this;
                *this = tmp;
            }
            void clear() { resize(0); }

        private :

            dynArr<T,Alloc> _array;
            size_type       _size;
            allocator_type  _alloc;
            difference_type _diff;

    };

    template < typename T, class Alloc >
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs == rhs); }
    template < typename T, class Alloc >
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs != rhs); }
    template < typename T, class Alloc >
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs < rhs); }
    template < typename T, class Alloc >
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs <= rhs); }
    template < typename T, class Alloc >
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs > rhs); }
    template < typename T, class Alloc >
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs >= rhs); }
    
    template < typename T >
    void swap(vector<T> &x, vector<T> &y) {
        vector<T> tmp;
        tmp = x;
        x = y;
        y = tmp;
    }
    
    template < typename T >
    std::ostream &operator<<(std::ostream &out, vector<T> const &vect) {
        size_t size = vect.size();
        out << "\t>> VECTOR [" << size << "]\t= { ";
        for (typename ft::vector<T>::const_iterator it = vect.begin(); size-- > 0; it++)
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