#ifndef MY_INPUT_ITERATOR_H
# define MY_INPUT_ITERATOR_H

#include "iterator.hpp"

template < typename T >
class myIOIterator : public virtual myIterator<T>
{
    public :

        typedef myIOIterator  iterator_category;

        //----- CONSTRUCTORS AND DESTRUCTORS -----//
        myIOIterator(T *p) : myIterator<T>(p) {}
        myIOIterator(const myIOIterator &ref) { this->it = ref.it; };
        virtual ~myIOIterator() {}

        //----- OPERATORS : 'equality' 'inequality' 'dereference as rvalue' -----//
        bool    operator==(const myIOIterator &ref) const { return (this->it == ref.it); }
        bool    operator!=(const myIOIterator &ref) const { return (this->it != ref.it); }
        T       &operator*() { return (*this->it); }

    private :

        myIOIterator() {}
};

#endif