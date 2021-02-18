/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:25:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/17 22:25:26 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

namespace ft
{
    template < typename T, class uContainer = ft::List<T> >
    class Queue {

        public :

            //defining every member in my List as in the STL
            typedef T                           value_type;
            typedef uContainer                  container_type;
            typedef size_t                      size_type;

            Queue() {}
            ~Queue() {}
            Queue(const Queue &) {}
            const Queue &operator=(const Queue &) {}

            // bool empty() const {}
            // size_type size() const {}
            // value_type &front() {}
            // const value_type &front() const {}
            // value_type &back() {}
            // const value_type &back() const {}
            // void push(const value_type &val) {}
            // void pop() {}

        private :

            container_type under;

    };

    template < typename T, class Alloc >
    bool operator==(const Queue<T, Alloc> &lhs, const Queue<T, Alloc> &rhs) { return (lhs == rhs); }
    template < typename T, class Alloc >
    bool operator!=(const Queue<T, Alloc> &lhs, const Queue<T, Alloc> &rhs) { return (lhs != rhs); }
    template < typename T, class Alloc >
    bool operator<(const Queue<T, Alloc> &lhs, const Queue<T, Alloc> &rhs) { return (lhs < rhs); }
    template < typename T, class Alloc >
    bool operator<=(const Queue<T, Alloc> &lhs, const Queue<T, Alloc> &rhs) { return (lhs <= rhs); }
    template < typename T, class Alloc >
    bool operator>(const Queue<T, Alloc> &lhs, const Queue<T, Alloc> &rhs) { return (lhs > rhs); }
    template < typename T, class Alloc >
    bool operator>=(const Queue<T, Alloc> &lhs, const Queue<T, Alloc> &rhs) { return (lhs >= rhs); }
}

#endif