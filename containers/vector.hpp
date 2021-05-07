/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 06:19:44 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/07 04:20:14 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "../templates/dynamicArray.hpp"
# include "../templates/enable_if.hpp"
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
            template <class InputIterator>
            vector(typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first,
				InputIterator last, const allocator_type& alloc = allocator_type()) :
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
                if (this->_size)
                    clear();
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
                return (_array.throwNullRef());
            }
            const_reference front() const { 
                 if (_size)
                    return (*(_array.getArray()));
                return (_array.throwNullRef());
            }
            reference back() {
                if (_size)
                    return (*(_array.getArray() + _size - 1));
                return (_array.throwNullRef());
            }
            const_reference back() const {
                if (_size)
                    return (*(_array.getArray() + _size - 1));
                return (_array.throwNullRef());
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
                throw std::out_of_range("vector");
            }
            const_reference at (size_type n) const {
                if (n < _size)
                    return (*(_array.getArray() + n));
                throw std::out_of_range("vector");
            }
            
            // ----- MODIFIERS ----- //
            
            template <class InputIterator>
            void assign(typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first,
				InputIterator last)
            {
                clear();
                while (first != last)
                    push_back(*first++);
            }
            void assign(size_type n, const value_type &val) {
                clear();
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
                size_t newSize = _size + 1;
                if (capacity() <= newSize)
                    _array.reallocateSplitArray(index, 1);
                _array.constructValue(index, val);
                // _size++;
                _size = newSize;
                return (iterator(_array.getArray() + index));
                // return (position);
            }
            void insert(iterator position, size_type n, const value_type &val) {
                size_t index = position.distanceBetween(begin(), position);
                size_t newSize = _size + n;
                if (capacity() <= newSize)
                    _array.reallocateSplitArray(index, n);
                else
                    _array.splitArray(newSize, index, n);
                for (size_t i = 0; i < n; i++)
                    _array.constructValue(index + i, val);
                _size = newSize;
                // _size += n;
            }
            template <class InputIterator>
            void insert(iterator position, InputIterator first, 
				typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last)
            {
                size_t index = position.distanceBetween(begin(), position);
                size_t dist = position.distanceBetween(first, last);
                size_t newSize = _size + dist;
                if (capacity() <= newSize)
                    _array.reallocateSplitArray(index, dist);
                else
                    _array.splitArray(newSize, index, dist);
                while (index < newSize && first != last)
                {
                    // std::cout << "index " << index << std::endl;
                    _array.constructValue(index++, *first);
                    first++;
                }
                _size = newSize;
                // _size += dist;
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
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return false;
        typename vector<T>::iterator rhs_it = rhs.begin();
        for (typename vector<T>::iterator lhs_it = lhs.begin(); lhs_it != lhs.end(); lhs_it++)
        {
            if (*lhs_it != *rhs_it++)
                return false;
        }
        return true;
    }
    template < typename T, class Alloc >
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }
    template < typename T, class Alloc >
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        typename vector<T>::iterator lhs_it = lhs.begin();
		typename vector<T>::iterator rhs_it = rhs.begin();
		while (lhs_it != lhs.end() && rhs_it != rhs.end())
		{
			if (*lhs_it++ < *rhs_it++)
				return true;
		}
		if (lhs_it == lhs.end() && rhs_it != rhs.end())
			return true;
		return false;
    }
    template < typename T, class Alloc >
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs < rhs || lhs == rhs); }
    template < typename T, class Alloc >
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        typename vector<T>::iterator lhs_it = lhs.begin();
		typename vector<T>::iterator rhs_it = rhs.begin();
		while (lhs_it != lhs.end() && rhs_it != rhs.end())
		{
			if (*lhs_it++ > *rhs_it++)
				return true;
		}
		if (rhs_it == lhs.end() && lhs_it != rhs.end())
			return true;
		return false;
    }
    template < typename T, class Alloc >
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs > rhs || lhs == rhs); }
    
    template < typename T >
    void swap(vector<T> &x, vector<T> &y) {
        vector<T> tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

    // THIS IS NOT PART OF THE STL CONTAINER
    template < typename T >
    std::ostream &operator<<(std::ostream &out, vector<T> const &vect) {
        size_t size = vect.size();
        out << "\t>> VECTOR [" << size << "]\t= { ";
        for (typename ft::vector<T>::const_iterator it = vect.begin(); it != vect.end(); it++)
        {
            out << *it;
            if (--size)
                out << ", ";
        }
        out << " }" << std::endl;
        return (out);
    }
};

#endif