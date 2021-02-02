#ifndef LIST_H
# define LIST_H

namespace ft
{
    template < typename T >
    class List {

        public :

            List() {}
            ~List() {}
            List(const List &) {}
            const List &operator=(const List &) {}

        private :

            T *list;

    };
}

#endif