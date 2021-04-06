/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:25:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/04/05 21:25:40 by lemarabe         ###   ########.fr       */
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
                container(ctnr)
            { }
            // CONSTRUCTOR BY COPY
            Queue(const Queue &ref) : container(ref.container)
            { }
            // DESTRUCTOR
            ~Queue()
            { }
            // ASSIGNATION
            const Queue &operator=(const Queue &ref) { 
                container = ref.container;
                return (*this);
            }

            // MEMBER FUNCTIONS
            bool empty() const { return (container.empty()); }
            size_type size() const { return (container.size()); }
            value_type &front() { return (container.front()); }
            const value_type &front() const { return (container.front()); }
            value_type &back() { return (container.back()); }
            const value_type &back() const { return (container.back()); }
            void push(const value_type &val) { container.push_back(val); }
            void pop() { container.pop_back(); }
            
            // ADDITION ( ONLY FOR DISPLAY )
            C &getContainer() const { return (const_cast<C&>(container)); }

        private :

            container_type  container;

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