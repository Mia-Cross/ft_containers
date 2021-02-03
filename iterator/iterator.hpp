#ifndef MY_ITERATOR_H
# define MY_ITERATOR_H

#include <iterator>

template < typename T >
struct myIterator
{
    void *it;  //?

    myIterator() : it(NULL) {}
    ~myIterator() {}
    myIterator(const myIterator &) : it(NULL) {}
    const myIterator &operator=(const myIterator &) {}

    // advance();
    // distance();
};

#endif