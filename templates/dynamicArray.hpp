/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamicArray.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 01:49:53 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/11 23:30:13 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

# include "myIterator.hpp"

template < typename T, class Alloc = std::allocator<T> >
class dynArr {
    
    public :

        // typedef myAccessIterator<T>  iterator;

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
        const T &throwNulRef() const { return (nul); }
        T       *getArray() const { return (array);}
        // T *getEnd() const {
        //     if (size > 0)
        //         return (array[size - 1]);
        //     return (NULL);
        // }
        
        void addElement(const T &value) {
            if (capacity == size)
                reallocateArray(capacity + 1);
            allocDA.construct(array + size++, value);
        }
        
        void deleteElement(size_t n) {
            if (n <= size - 1)
                allocDA.destroy(this->array + n);
            size--;
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



        // size_t iteratorDistance(iterator begin, iterator end) {
        //     size_t dist = 0;
        //     while (begin++ != end)
        //         dist++;
        //     return (dist);
        // }


    private :
    
        Alloc   allocDA;
        size_t  capacity;
        size_t  size;
        T       *array;
        const T nul;
};


#endif