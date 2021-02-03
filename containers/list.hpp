#ifndef LIST_H
# define LIST_H

#include "../iterator/iterator.hpp"
#include <memory>

namespace ft
{
    template < typename T >
    class List {

        public :

			//defining every member in my List as in the STL
            typedef T           value_type;
            typedef std::allocator<T>       allocator_type;
            typedef T &         reference;
            typedef T *         pointer;
            typedef const T &	const_reference;
            typedef const T *	const_pointer;
			typedef myIterator<T> iterator;
			typedef myIterator<T> const_iterator;
			typedef myIterator<T> reverse_iterator;
			typedef myIterator<T> const_reverse_iterator;
			typedef size_t		size_type;
			//typedef ptrdiff_t	difference_type;


            List() {}
            ~List() {}
            List(const List &) {}
            const List &operator=(const List &) {}

        private :

            T *list;  //?

    };
}

#endif