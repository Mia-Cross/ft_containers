#ifndef MY_FORWARD_ITERATOR_H
# define MY_FORWARD_ITERATOR_H

#include "ioIterator.hpp"

template < typename T >
struct myForwardIterator : public virtual myIOIterator<T>
{
    typedef myForwardIterator  iterator_category;

    //----- CONSTRUCTORS AND DESTRUCTORS -----//
    myForwardIterator() : myIOIterator<T>(NULL) { }
    myForwardIterator(T *p) : myIOIterator<T>(p) {}
    myForwardIterator(const myForwardIterator &ref) { this->it = ref.it; };
    virtual ~myForwardIterator() {}
};

#endif