#ifndef STACK_H
# define STACK_H

namespace ft
{
    template < typename T, class uContainer = ft::List<T> >
    class Stack {

        public :

            //defining every member in my List as in the STL
            typedef T                           value_type;
            typedef uContainer                  container_type;
            typedef size_t                      size_type;

            Stack() : T(NULL) {}
            ~Stack() {}
            Stack(const Stack &ref) {}
            const Stack &operator=(const Stack &) {}

            bool empty() const {}
            size_type size() const {}
            value_type &top() {}
            const value_type &top() const {}
            void push(const value_type &val) {}
            void pop() {}

        private :

            T               *stack;
            container_type  under;
            //size_type   size;

    };

    template < typename T >
    bool operator== (const Stack<T> &lhs, const Stack<T> &rhs) {}
    template < typename T >
    bool operator!= (const Stack<T> &lhs, const Stack<T> &rhs) {}
    template < typename T >
    bool operator<  (const Stack<T> &lhs, const Stack<T> &rhs) {}
    template < typename T >
    bool operator<= (const Stack<T> &lhs, const Stack<T> &rhs) {}
    template < typename T >
    bool operator>  (const Stack<T> &lhs, const Stack<T> &rhs) {}
    template < typename T >
    bool operator>= (const Stack<T> &lhs, const Stack<T> &rhs) {}
}


#endif