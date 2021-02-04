#ifndef MY_FORWARD_ITERATOR_H
# define MY_FORWARD_ITERATOR_H

#include "ioIterator.hpp"

template < typename T >
struct myForwardIterator : public virtual myIOIterator<T>
{
    typedef myForwardIterator  iterator_category;

    //----- CONSTRUCTORS AND DESTRUCTORS -----//
    myForwardIterator() : it(NULL) {}
    myForwardIterator(T *p) : myIOIterator<T>(p) {}
    myForwardIterator(const myForwardIterator &ref) { this->it = ref.it; };
    virtual ~myForwardIterator() {}

    //----- OPERATORS : 'dereference as lvalue' -----//
    T                   &operator*() { return (*this->it); }

};

#endif