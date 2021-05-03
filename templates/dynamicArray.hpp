/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamicArray.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 01:49:53 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/03 22:53:21 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

# include <cstddef>
# include <memory>

template < typename T, class Alloc >
class dynArr {
    
    public :

        //create empty vector
        dynArr() : allocDA(Alloc()), capacity(1), size(0),
            array(allocDA.allocate(1)), nul(0) {}

        //allocate empty new block
        dynArr(size_t n) : allocDA(Alloc()), capacity(n), size(0),
            array(allocDA.allocate(n)), nul(0) {}
        
        //copy dynamic array
        dynArr(const dynArr &ref) : allocDA(Alloc()), capacity(ref.size),
            size(ref.size), array(allocDA.allocate(ref.size)), nul(0) {
                *this = ref;
        }

        ~dynArr() {
            allocDA.deallocate(array, capacity);
        }
        
        dynArr &operator=(const dynArr &ref) {
            if (this->capacity < ref.size)
                reallocateArray(ref.size);
            for (size_t i = 0; i != ref.size; i++)
                allocDA.construct(this->array + i, *(ref.array + i));
            this->size = ref.size;
            return (*this);
        }

        size_t  getCapacity() const { return (capacity); }
        size_t  getSize() const { return (size); }
        T       &throwNulRef() const { return (const_cast<T&>(nul)); }
        T       *getArray() const { return (array); }
        void    incrementSize(size_t n) { size += n; }
        
        void addElement(const T &value) {
            if (capacity <= size)
                reallocateArray(capacity + 1);
            allocDA.construct(array + size++, value);
        }

        void constructValue(size_t index, const T &value) {
            allocDA.construct(array + index, value);
        }

        void deleteElements(size_t index, size_t n) {
            if (index >= size || !size)
                return;
            for (size_t i = index; i < index + n; i++)
                allocDA.destroy(array + i);
            size -= n;
            for (size_t i = index; i < size; i++)
                array[i] = array[i + n];
        }

        T *duplicateArray(size_t size, size_t capacity) {
            T *dup = allocDA.allocate(capacity);
            for (size_t i = 0; i < size; i++)
                allocDA.construct(dup + i, *(array + i));
            return (dup);
        }

        void reallocateArray(size_t n) {
            T *newArr = duplicateArray(this->size, n);
            allocDA.deallocate(this->array, this->capacity);
            this->array = newArr;
            this->capacity = n;
        }

        T *duplicateSplitArray(size_t index, size_t length) {
            T *dup = allocDA.allocate(this->capacity + length);
            size_t j = 0;
            for (size_t i = 0; i < index; i++)
                allocDA.construct(dup + i, *(array + j++));
            for (size_t i = index + length; i < capacity + length; i++)
                allocDA.construct(dup + i, *(array + j++));
            capacity += length;
            size += length;
            return (dup);
        }
        
        void reallocateSplitArray(size_t index, size_t length) {
            T *newArr = duplicateSplitArray(index, length);
            allocDA.deallocate(this->array, this->capacity);
            this->array = newArr;
        }

    private :
    
        Alloc   allocDA;
        size_t  capacity;
        size_t  size;
        T       *array;
        const T nul;
};

template < typename T, class Alloc >
class vectIter
{
    public :

        typedef T               value_type;
        typedef ptrdiff_t       difference_type;
        typedef T *             pointer_type;
        typedef T &             reference_type;
        typedef dynArr<T,Alloc> *dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        vectIter() {}
        vectIter(T *ptr) : it(ptr) {}
        vectIter(dynamic_array arr) : it(arr->getArray()) {}
        vectIter(const vectIter &ref) : it(ref.it) {}
        virtual ~vectIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        vectIter  &operator=(const vectIter &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const vectIter &ref) const { return (this->it == ref.it); }
        bool        operator!=(const vectIter &ref) const { return (this->it != ref.it); }

        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (*it); }
        reference_type  operator[](difference_type n) const {
            dynamic_array arr = it->getArray();
            if (n < arr->size())
                return (*(arr + n));
            return (arr->throwNulRef());
        }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        vectIter  &operator++() { this->it++; return (*this); }
        vectIter  operator++(int) { vectIter tmp(*this); operator++(); return (tmp); }
        vectIter  &operator--() { this->it--; return (*this); }
        vectIter  operator--(int) { vectIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS : 'pointers arithmetics' -----//
        vectIter  &operator+(difference_type x) {
            while (x--)
                this->it++;
            return (*this); }
        vectIter  &operator-(difference_type x) {
            while (x--)
                this->it--;
            return (*this); }

        //----- OPERATORS : 'pointers distance' -----//
        size_t distanceBetween(vectIter begin, vectIter end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }

    protected :

        T *it;
};

template < typename T, class Alloc >
class cVectIter : public virtual vectIter<T,Alloc>
{
    public :

        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        typedef ptrdiff_t       difference_type;
        typedef dynArr<T,Alloc> *dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        cVectIter() {}
        cVectIter(T *ptr) : vectIter<T,Alloc>(ptr) {}
        cVectIter(dynamic_array arr) : vectIter<T,Alloc>(arr->getArray()) {}
        cVectIter(const cVectIter &ref) : vectIter<T,Alloc>(ref.it) {}
        virtual ~cVectIter() {}
        cVectIter  &operator=(const cVectIter &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (*this->it); }
        const_reference_type  operator[](difference_type n) const {
            dynamic_array arr = this->it->getArray();
            if (n < arr->size())
                return (*(arr + n));
            return (arr->throwNulRef());
        }
        
        //----- OPERATORS : 'pointers distance' -----//
        size_t distanceBetween(cVectIter begin, cVectIter end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }
};

template < typename T, class Alloc >
class rVectIter : public virtual vectIter<T,Alloc>
{
    public :

        typedef T               value_type;
        typedef ptrdiff_t       difference_type;
        typedef T *             pointer_type;
        typedef T &             reference_type;
        typedef dynArr<T,Alloc> *dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        rVectIter() {}
        rVectIter(T *ptr) : vectIter<T,Alloc>(ptr) {}
        rVectIter(dynamic_array arr) : vectIter<T,Alloc>(arr->getArray()) {}
        rVectIter(const rVectIter &ref) : vectIter<T,Alloc>(ref.it) {}
        virtual ~rVectIter() {}
        rVectIter  &operator=(const rVectIter &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : & 'incrementation''decrementation' -----//
        rVectIter  &operator++() { this->it--; return (*this); }
        rVectIter  operator++(int) { rVectIter tmp(*this); operator++(); return (tmp); }
        rVectIter  &operator--() { this->it++; return (*this); }
        rVectIter  operator--(int) { rVectIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS : 'pointers arithmetics' -----//
        rVectIter  &operator+(difference_type x) {
            while (x--)
                this->it--;   //?
            return (*this); }
        rVectIter  &operator-(difference_type x) {
            while (x--)
                this->it++;  //?
            return (*this); }
        
        //----- OPERATORS : 'pointers distance' -----//
        size_t distanceBetween(rVectIter begin, rVectIter end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }
};

template < typename T, class Alloc >
class crVectIter : public virtual cVectIter<T,Alloc>, public virtual rVectIter<T,Alloc>
{
    public :
    
        typedef T               value_type;
        typedef ptrdiff_t       difference_type;
        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        typedef dynArr<T,Alloc> *dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        crVectIter() {}
        crVectIter(T *ptr) : vectIter<T,Alloc>(ptr) {}
        crVectIter(dynamic_array arr) : vectIter<T,Alloc>(arr->getArray()) {}
        crVectIter(const crVectIter &ref) : vectIter<T,Alloc>(ref.it) {}
        virtual ~crVectIter() {}
        crVectIter  &operator=(const crVectIter &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (*this->it); }
        const_reference_type  operator[](difference_type n) const {
            dynamic_array arr = this->it->getArray();
            if (n < arr->size())
                return (*(arr + n));
            return (arr->throwNulRef());
        }

        //----- OPERATORS : & 'incrementation''decrementation' -----//
        crVectIter  &operator++() { this->it--; return (*this); }
        crVectIter  operator++(int) { crVectIter tmp(*this); operator++(); return (tmp); }
        crVectIter  &operator--() { this->it++; return (*this); }
        crVectIter  operator--(int) { crVectIter tmp(*this); operator--(); return (tmp); }
        
        //----- OPERATORS : 'pointers arithmetics' -----//
        crVectIter  &operator+(difference_type x) {
            while (x--)
                this->it--;
            return (*this); }
        crVectIter  &operator-(difference_type x) {
            while (x--)
                this->it++;
            return (*this); }

        //----- OPERATORS : 'pointers distance' -----//
        size_t distanceBetween(crVectIter begin, crVectIter end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }
};

#endif