/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:25:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/04/08 04:32:59 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "list.hpp"
# include <memory>
# include <iostream>

namespace ft
{
    template < typename T, class C = ft::List<T> >
    class Queue {

        public :

            //defining every member in my List as in the STL
            typedef T                                   value_type;
            typedef C                                   container_type;
            typedef typename container_type::size_type  size_type;

            // CONSTRUCTOR BY CONTAINER TYPE
            explicit Queue(const container_type& ctnr = container_type()) :
                _container(ctnr)
            { }
            // CONSTRUCTOR BY COPY
            Queue(const Queue &ref) : _container(ref._container)
            { }
            // DESTRUCTOR
            ~Queue()
            { }
            // ASSIGNATION
            const Queue &operator=(const Queue &ref) { 
                _container = ref._container;
                return (*this);
            }

            // MEMBER FUNCTIONS
            bool empty() const { return (_container.empty()); }
            size_type size() const { return (_container.size()); }
            value_type &front() { return (_container.front()); }
            const value_type &front() const { return (_container.front()); }
            value_type &back() { return (_container.back()); }
            const value_type &back() const { return (_container.back()); }
            void push(const value_type &val) { _container.push_back(val); }
            void pop() { _container.pop_back(); }
            
            // ADDITION ( ONLY FOR DISPLAY )
            C &getContainer() const { return (const_cast<C&>(_container)); }

        private :

            container_type  _container;

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

    template < typename T >
    std::ostream &operator<<(std::ostream &out, Queue<T> const &queue) {
        size_t size = queue.size();
        out << "\t>> QUEUE [" << size << "]\t= { ";
        if (size)
        {
            for (typename List<T>::iterator it = queue.getContainer().begin(); size-- > 0; it++)
            {
                out << *it;
                if (size)
                    out << ", ";
            }
        }
        out << " }" << std::endl;
        return (out);
    }
}

#endif