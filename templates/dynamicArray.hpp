/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamicArray.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 01:49:53 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/07 15:11:16 by lemarabe         ###   ########.fr       */
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
        dynArr() : _allocDA(Alloc()), _capacity(1), _sizeDA(0),
            _arrayDA(_allocDA.allocate(1)), _nullRef(T()) { }

        //allocate empty new block
        dynArr(size_t n) : _allocDA(Alloc()), _capacity(n), _sizeDA(0),
            _arrayDA(_allocDA.allocate(n)), _nullRef(T()) { }
        
        //copy dynamic array
        dynArr(const dynArr &ref) : _allocDA(Alloc()), _capacity(ref._sizeDA),
            _sizeDA(0), _arrayDA(_allocDA.allocate(ref._sizeDA)), _nullRef(T()) {
                *this = ref;  }

        ~dynArr() { _allocDA.deallocate(_arrayDA, _capacity); }

        dynArr &operator=(const dynArr &ref) {
            if (_capacity < ref._sizeDA)
                reallocateArray(ref._sizeDA);
            for (size_t i = 0; i != ref._sizeDA; i++)
                constructValue(i, *(ref._arrayDA + i));
            return (*this);
        }

        size_t  getCapacity() const { return (_capacity); }
        size_t  getSize() const { return (_sizeDA); }
        T       &throwNullRef() const { return (const_cast<T&>(_nullRef)); }
        T       *getArray() const { return (_arrayDA); }

        void addElement(const T &value) {
            if (_capacity <= _sizeDA)
                reallocateArray(_capacity + 1);
            constructValue(_sizeDA, value);
        }

        void constructValue(size_t index, const T &value) {
            _allocDA.construct(_arrayDA + index, value);
            _sizeDA++; 
        }

        void deleteElements(size_t index, size_t n) {
            if (index >= _sizeDA || !_sizeDA)
                return;
            for (size_t i = index; i < index + n; i++)
                _allocDA.destroy(_arrayDA + i);
            _sizeDA -= n;
            for (size_t i = index; i < _sizeDA; i++)
                _allocDA.construct(_arrayDA + i, *(_arrayDA + i + n));
        }

        T *duplicateArray(size_t size, size_t newCapacity) {
            T *dup = _allocDA.allocate(newCapacity);
            for (size_t i = 0; i < size; i++)
                _allocDA.construct(dup + i, *(_arrayDA + i));
            return (dup);
        }

        void reallocateArray(size_t n) {
            T *newArr = duplicateArray(_sizeDA, n);
            _allocDA.deallocate(_arrayDA, _capacity);
            _arrayDA = newArr;
            _capacity = n;
        }

        void splitArray(size_t newSize, size_t index, size_t length) {
            for (size_t i = newSize - 1; i >= index + length; i--)
                _allocDA.construct(_arrayDA + i, *(_arrayDA + i - length));
            for (size_t i = index; i < index + length; i++)
                _allocDA.destroy(_arrayDA + i);
        }

        T *duplicateSplitArray(size_t index, size_t length) {
            T *dup = _allocDA.allocate(_capacity + length);
            size_t j = 0;
            for (size_t i = 0; i < index; i++)
                _allocDA.construct(dup + i, *(_arrayDA + j++));
            for (size_t i = index + length; i < _capacity + length; i++)
                _allocDA.construct(dup + i, *(_arrayDA + j++));
            _capacity += length;
            return (dup);
        }
        
        void reallocateSplitArray(size_t index, size_t length) {
            T *newArr = duplicateSplitArray(index, length);
            _allocDA.deallocate(_arrayDA, _capacity);
            _arrayDA = newArr;
        }

    private :
    
        Alloc   _allocDA;
        size_t  _capacity;
        size_t  _sizeDA;
        T       *_arrayDA;
        const T _nullRef;
};

template < typename T, class Alloc >
class vectIter
{
    public :

        typedef T *                 pointer_type;
        typedef T &                 reference_type;
        typedef ptrdiff_t           difference_type;
        typedef dynArr<T,Alloc> *   dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        vectIter() {}
        vectIter(pointer_type ptr) : it(ptr) {}
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
            return (arr->throwNullRef()); }

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
        template <class InputIterator>
        size_t distanceBetween(InputIterator begin, InputIterator end) {
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

        typedef T *                 pointer_type;
        typedef const T *           const_pointer_type;
        typedef const T &           const_reference_type;
        typedef ptrdiff_t           difference_type;
        typedef dynArr<T,Alloc> *   dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        cVectIter() {}
        cVectIter(pointer_type ptr) : vectIter<T,Alloc>(ptr) {}
        cVectIter(dynamic_array arr) : vectIter<T,Alloc>(arr->getArray()) {}
        cVectIter(const cVectIter &ref) : vectIter<T,Alloc>(ref.it) {}
        virtual ~cVectIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        cVectIter  &operator=(const cVectIter &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const cVectIter &ref) const { return (this->it == ref.it); }
        bool        operator!=(const cVectIter &ref) const { return (this->it != ref.it); }
        
        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (*this->it); }
        const_reference_type  operator[](difference_type n) const {
            dynamic_array arr = this->it->getArray();
            if (n < arr->size())
                return (*(arr + n));
            return (arr->throwNullRef()); }
        
        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        cVectIter  &operator++() { this->it++; return (*this); }
        cVectIter  operator++(int) { cVectIter tmp(*this); operator++(); return (tmp); }
        cVectIter  &operator--() { this->it--; return (*this); }
        cVectIter  operator--(int) { cVectIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS : 'pointers arithmetics' -----//
        cVectIter  &operator+(difference_type x) {
            while (x--)
                this->it++;
            return (*this); }
        cVectIter  &operator-(difference_type x) {
            while (x--)
                this->it--;
            return (*this); }
        
        //----- OPERATORS : 'pointers distance' -----//
        size_t distanceBetween(cVectIter begin, cVectIter end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }
        template <class InputIterator>
        size_t distanceBetween(InputIterator begin, InputIterator end) {
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

        typedef T *                 pointer_type;
        typedef T &                 reference_type;
        typedef ptrdiff_t           difference_type;
        typedef dynArr<T,Alloc> *   dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        rVectIter() {}
        rVectIter(pointer_type ptr) : vectIter<T,Alloc>(ptr) {}
        rVectIter(dynamic_array arr) : vectIter<T,Alloc>(arr->getArray()) {}
        rVectIter(const rVectIter &ref) : vectIter<T,Alloc>(ref.it) {}
        virtual ~rVectIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        rVectIter  &operator=(const rVectIter &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const rVectIter &ref) const { return (this->it == ref.it); }
        bool        operator!=(const rVectIter &ref) const { return (this->it != ref.it); }

        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (*this->it); }
        reference_type  operator[](difference_type n) const {
            dynamic_array arr = this->it->getArray();
            if (n < arr->size())
                return (*(arr + n));
            return (arr->throwNullRef()); }

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
        template <class InputIterator>
        size_t distanceBetween(InputIterator begin, InputIterator end) {
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
    
        typedef T *                 pointer_type;
        typedef const T *           const_pointer_type;
        typedef const T &           const_reference_type;
        typedef ptrdiff_t           difference_type;
        typedef dynArr<T,Alloc> *   dynamic_array;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        crVectIter() {}
        crVectIter(pointer_type ptr) : vectIter<T,Alloc>(ptr) {}
        crVectIter(dynamic_array arr) : vectIter<T,Alloc>(arr->getArray()) {}
        crVectIter(const crVectIter &ref) : vectIter<T,Alloc>(ref.it) {}
        virtual ~crVectIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        crVectIter  &operator=(const crVectIter &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const crVectIter &ref) const { return (this->it == ref.it); }
        bool        operator!=(const crVectIter &ref) const { return (this->it != ref.it); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (*this->it); }
        const_reference_type  operator[](difference_type n) const {
            dynamic_array arr = this->it->getArray();
            if (n < arr->size())
                return (*(arr + n));
            return (arr->throwNullRef()); }

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
        template <class InputIterator>
        size_t distanceBetween(InputIterator begin, InputIterator end) {
            size_t dist = 0;
            while (begin++ != end)
                dist++;
            return (dist);
        }
};

#endif