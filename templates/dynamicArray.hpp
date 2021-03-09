/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamicArray.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 01:49:53 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/09 05:25:45 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

template < typename T, class Alloc >
class dynArr {
    
    public :

        //create blank vector
        dynArr() : allocDA(Alloc()), capacity(1), size(0),
            array(allocDA.allocate(1)) {
                *this->array = 0;
            }

        //allocate empty new block
        dynArr(size_t n) : allocDA(Alloc()), capacity(n), size(0),
            array(allocDA.allocate(n)) {
                //*this->array = 0;
            }
        
        //copy dynamic array
        dynArr(const dynArr &ref) : allocDA(Alloc()), capacity(ref.size),
            size(ref.size), array(allocDA.allocate(ref.size)) {
                *this = ref;
        }

        ~dynArr() {
            allocDA.deallocate(array, size);
            }
        
        dynArr &operator=(const dynArr &ref) {
            if (this->capacity < ref.size)
                reallocate(ref.size);
            for (size_t i = 0; i != ref.size; i++)
                this->array[i] = ref.array[i];
            this->size = ref.size;
            // this->capacity = ref.size;
            return (*this);
        }

        void reallocate(size_t n) {
            T tmp(*this->array);
            allocDA.deallocate(this->array, this->capacity);
            this->array = allocDA.allocate(n);
            *this->array = tmp;
            this->capacity = n;
        }
        
        void deleteElement(size_t n) {
            if (n < size)
                allocDA.deallocate((this->array + n), 1);
        }
        
        void addElement(T value) {
            if (capacity < ++size)
                reallocate(size);
            array[size - 1] = value;
        }

        size_t getCapacity() const { return (capacity); }
        size_t getSize() const { return (size); }
        T*getArray() const { return (array);}
        
        T *getEnd() const {
            if (size > 0)
                return (array[size - 1]);
            return (NULL);
        }


    private :
    
        Alloc   allocDA;
        size_t  capacity;
        size_t  size;
        T       *array;
};


#endif