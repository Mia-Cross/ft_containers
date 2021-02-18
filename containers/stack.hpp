/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:25:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/17 22:26:43 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "list.hpp"

namespace ft
{
    template < typename T, class C = ft::List<T> >
    class Stack {

        public :

            //defining every member in my List as in the STL
            typedef T       value_type;
            typedef C       container_type;
            typedef size_t  size_type;

            Stack() : T(NULL) {}
            ~Stack() {}
            Stack(const Stack &) { }
            const Stack &operator=(const Stack &) {}

            // bool empty() const {}
            // size_type size() const {}
            // value_type &top() {}
            // const value_type &top() const {}
            // void push(const value_type &val) {}
            // void pop() {}

        private :

            T               *stack;
            container_type  under;
            //size_type   size;

    };

    template < typename T, class Alloc >
    bool operator==(const Stack<T, Alloc> &lhs, const Stack<T, Alloc> &rhs) { return (lhs == rhs); }
    template < typename T, class Alloc >
    bool operator!=(const Stack<T, Alloc> &lhs, const Stack<T, Alloc> &rhs) { return (lhs != rhs); }
    template < typename T, class Alloc >
    bool operator<(const Stack<T, Alloc> &lhs, const Stack<T, Alloc> &rhs) { return (lhs < rhs); }
    template < typename T, class Alloc >
    bool operator<=(const Stack<T, Alloc> &lhs, const Stack<T, Alloc> &rhs) { return (lhs <= rhs); }
    template < typename T, class Alloc >
    bool operator>(const Stack<T, Alloc> &lhs, const Stack<T, Alloc> &rhs) { return (lhs > rhs); }
    template < typename T, class Alloc >
    bool operator>=(const Stack<T, Alloc> &lhs, const Stack<T, Alloc> &rhs) { return (lhs >= rhs); }
}


#endif