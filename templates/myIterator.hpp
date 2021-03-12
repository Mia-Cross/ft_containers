/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myIterator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:13 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/12 02:51:09 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_ITERATOR_H
# define MY_ITERATOR_H

# include "doublyLinkedList.hpp"
# include "dynamicArray.hpp"
# include <cstddef>

template < typename T, class E >
class myIterator
{
    public :

        typedef T               value_type;
        typedef ptrdiff_t       difference_type;
        typedef T *             pointer_type;
        typedef T &             reference_type;
        typedef E               element_type;
        typedef E *             elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myIterator() {}
        myIterator(E *p) : it(p) {}
        myIterator(const myIterator &ref) : it(ref.it) {}
        virtual ~myIterator() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        myIterator  &operator=(const myIterator &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const myIterator &ref) const { return (this->it == ref.it); }
        bool        operator!=(const myIterator &ref) const { return (this->it != ref.it); }
        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (this->it->getContentRef()); }
        elem_ptr_type   operator->() const { return (this->it); }
        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        myIterator  &operator++() { this->it = this->it->getNext(); return (*this); }
        myIterator  operator++(int) { myIterator tmp(*this); operator++(); return (tmp); }
        myIterator  &operator--() { this->it = this->it->getPrev(); return (*this); }
        myIterator  operator--(int) { myIterator tmp(*this); operator--(); return (tmp); }

    protected :

        E *it;
};

template < typename T, class E >
class myCIterator : public virtual myIterator<T, E>
{
    public :
    
        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        
        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myCIterator() : myIterator<T,E>() {}
        myCIterator(E *p) : myIterator<T,E>(p) {}
        myCIterator(const myCIterator &ref) : myIterator<T,E>(ref.it) {}
        virtual ~myCIterator() {}
        myCIterator  &operator=(const myCIterator &ref) { this->it = ref.it; return (*this); }
        //----- OPERATORS :  'dereference' -----//
        const_reference_type       operator*() const { return (this->it->getContentRef()); }
        const_pointer_type         operator->() const { return (this->it->getContentPtr()); }
};

template < typename T, class E >
class myRIterator : public virtual myIterator<T, E>
{
    public :
        
        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myRIterator() : myIterator<T,E>() {}
        myRIterator(E *p) : myIterator<T,E>(p) {}
        myRIterator(const myRIterator &ref) : myIterator<T,E>(ref.it) {}
        virtual ~myRIterator() {}
        myRIterator  &operator=(const myRIterator &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        myRIterator  &operator++() { this->it = this->it->getPrev(); return (*this); }
        myRIterator  operator++(int) { myRIterator tmp(*this); operator++(); return (tmp); }
        myRIterator  &operator--() { this->it = this->it->getNext(); return (*this); }
        myRIterator  operator--(int) { myRIterator tmp(*this); operator--(); return (tmp); }
};

template < typename T, class E >
class myCRIterator : public virtual myCIterator<T, E>, public virtual myRIterator<T, E>
{
    public :

        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myCRIterator() : myIterator<T,E>() {}
        myCRIterator(E *p) : myIterator<T,E>(p) {}
        myCRIterator(const myCRIterator &ref) : myIterator<T,E>(ref.it) {}
        virtual ~myCRIterator() {}
        myCRIterator  &operator=(const myCRIterator &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        myCRIterator  &operator++() { this->it = this->it->getPrev(); return (*this); }
        myCRIterator  operator++(int) { myCRIterator tmp(*this); operator++(); return (tmp); }
        myCRIterator  &operator--() { this->it = this->it->getNext(); return (*this);  }
        myCRIterator  operator--(int) { myCRIterator tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (this->it->getContentRef()); }
        const_pointer_type    operator->() const { return (this->it->getContentPtr()); }
};

template < typename T >
class myAccessIterator
{
    public :

        typedef T               value_type;
        typedef ptrdiff_t       difference_type;
        typedef T *             pointer_type;
        typedef T &             reference_type;
        typedef dynArr<T> *     dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myAccessIterator() {}
        myAccessIterator(T *ptr) : it(ptr) {}
        myAccessIterator(dynamic_array arr) : it(arr->getArray()) {}
        myAccessIterator(const myAccessIterator &ref) : it(ref.it) {}
        virtual ~myAccessIterator() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        myAccessIterator  &operator=(const myAccessIterator &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const myAccessIterator &ref) const { return (this->it == ref.it); }
        bool        operator!=(const myAccessIterator &ref) const { return (this->it != ref.it); }

        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (*it); }
        reference_type  operator[](difference_type n) const {
            dynamic_array arr = it->getArray();
            if (n < arr->size())
                return (*(arr + n));
            return (arr->throwNulRef());
        }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        myAccessIterator  &operator++() { this->it++; return (*this); }
        myAccessIterator  operator++(int) { myAccessIterator tmp(*this); operator++(); return (tmp); }
        myAccessIterator  &operator--() { this->it--; return (*this); }
        myAccessIterator  operator--(int) { myAccessIterator tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS : 'pointers arithmetics' -----//
        myAccessIterator  &operator+(difference_type x) {
            while (x--)
                this->it++;
            return (*this); }
        myAccessIterator  &operator-(difference_type x) {
            while (x--)
                this->it--;
            return (*this); }

        //----- OPERATORS : 'pointers distance' -----//
        size_t distanceBetween(myAccessIterator begin, myAccessIterator end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }

    protected :

        T *it;
};

template < typename T >
class myCAccessIterator : public virtual myAccessIterator<T>
{
    public :

        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        typedef ptrdiff_t       difference_type;
        typedef dynArr<T> *     dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myCAccessIterator() {}
        myCAccessIterator(T *ptr) : myAccessIterator<T>(ptr) {}
        myCAccessIterator(dynamic_array arr) : myAccessIterator<T>(arr->getArray()) {}
        myCAccessIterator(const myCAccessIterator &ref) : myAccessIterator<T>(ref.it) {}
        virtual ~myCAccessIterator() {}
        myCAccessIterator  &operator=(const myCAccessIterator &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (*this->it); }
        const_reference_type  operator[](difference_type n) const {
            dynamic_array arr = this->it->getArray();
            if (n < arr->size())
                return (*(arr + n));
            return (arr->throwNulRef());
        }
        
        //----- OPERATORS : 'pointers distance' -----//
        size_t distanceBetween(myCAccessIterator begin, myCAccessIterator end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }
};

template < typename T >
class myRAccessIterator : public virtual myAccessIterator<T>
{
    public :

        typedef T               value_type;
        typedef ptrdiff_t       difference_type;
        typedef T *             pointer_type;
        typedef T &             reference_type;
        typedef dynArr<T> *     dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myRAccessIterator() {}
        myRAccessIterator(T *ptr) : myAccessIterator<T>(ptr) {}
        myRAccessIterator(dynamic_array arr) : myAccessIterator<T>(arr->getArray()) {}
        myRAccessIterator(const myRAccessIterator &ref) : myAccessIterator<T>(ref.it) {}
        virtual ~myRAccessIterator() {}
        myRAccessIterator  &operator=(const myRAccessIterator &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : & 'incrementation''decrementation' -----//
        myRAccessIterator  &operator++() { this->it--; return (*this); }
        myRAccessIterator  operator++(int) { myRAccessIterator tmp(*this); operator++(); return (tmp); }
        myRAccessIterator  &operator--() { this->it++; return (*this); }
        myRAccessIterator  operator--(int) { myRAccessIterator tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS : 'pointers arithmetics' -----//
        myRAccessIterator  &operator+(difference_type x) {
            while (x--)
                this->it--;   //?
            return (*this); }
        myRAccessIterator  &operator-(difference_type x) {
            while (x--)
                this->it++;  //?
            return (*this); }
        
        //----- OPERATORS : 'pointers distance' -----//
        size_t distanceBetween(myRAccessIterator begin, myRAccessIterator end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }
};

template < typename T >
class myCRAccessIterator : public virtual myCAccessIterator<T>, public virtual myRAccessIterator<T>
{
    public :
    
        typedef T               value_type;
        typedef ptrdiff_t       difference_type;
        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        typedef dynArr<T> *     dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myCRAccessIterator() {}
        myCRAccessIterator(T *ptr) : myAccessIterator<T>(ptr) {}
        myCRAccessIterator(dynamic_array arr) : myAccessIterator<T>(arr->getArray()) {}
        myCRAccessIterator(const myCRAccessIterator &ref) : myAccessIterator<T>(ref.it) {}
        virtual ~myCRAccessIterator() {}
        myCRAccessIterator  &operator=(const myCRAccessIterator &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (*this->it); }
        const_reference_type  operator[](difference_type n) const {
            dynamic_array arr = this->it->getArray();
            if (n < arr->size())
                return (*(arr + n));
            return (arr->throwNulRef());
        }

        //----- OPERATORS : & 'incrementation''decrementation' -----//
        myCRAccessIterator  &operator++() { this->it--; return (*this); }
        myCRAccessIterator  operator++(int) { myCRAccessIterator tmp(*this); operator++(); return (tmp); }
        myCRAccessIterator  &operator--() { this->it++; return (*this); }
        myCRAccessIterator  operator--(int) { myCRAccessIterator tmp(*this); operator--(); return (tmp); }
        
        //----- OPERATORS : 'pointers arithmetics' -----//
        myCRAccessIterator  &operator+(difference_type x) {
            while (x--)
                this->it--;
            return (*this); }
        myCRAccessIterator  &operator-(difference_type x) {
            while (x--)
                this->it++;
            return (*this); }

        //----- OPERATORS : 'pointers distance' -----//
        size_t distanceBetween(myCRAccessIterator begin, myCRAccessIterator end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }
};

#endif