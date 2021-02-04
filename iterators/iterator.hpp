#ifndef MY_ITERATOR_H
# define MY_ITERATOR_H

#include <iterator>
#include <cstddef>

template < typename T >
class myIterator
{
    public :

        typedef myIterator  iterator_category;
        typedef T           value_type;
        typedef ptrdiff_t   difference_type;
        typedef T *         pointer;
        typedef T &         reference;

        //----- COPY CONSTRUCTIBLE, ASSIGNABLE AND DESTRUCTIBLE -----//
        myIterator(T *p) : it(p) {}
        myIterator(const myIterator &ref) { this->it = ref.it; }
        virtual ~myIterator() {}

        //----- OPERATORS : 'assignation' & 'incrementation' -----//
        virtual myIterator  &operator=(const myIterator &ref) { this->it = ref.it; return (*this); }
        virtual myIterator  &operator++() { this->it++; return (*this); }
        virtual myIterator  operator++(int) { myIterator tmp(*this); operator++(); return (tmp); }

    protected :

        T *it;
    
    private :

        myIterator() {}
};

#endif