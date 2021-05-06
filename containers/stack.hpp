/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:25:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/06 17:10:41 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "list.hpp"
# include <memory>
# include <iostream>

namespace ft
{
    template < typename T, class C = ft::list<T> >
    class stack {

        public :

            //defining every member in my stack as in the STL
            typedef T                                   value_type;
            typedef C                                   container_type;
            typedef typename container_type::size_type  size_type;

            // CONSTRUCTOR BY CONTAINER TYPE
            explicit stack(const container_type& ctnr = container_type()) :
                _container(ctnr)
            { }
            // CONSTRUCTOR BY COPY
            stack(const stack &ref) : _container(ref._container)
            { }
            // DESTRUCTOR
            ~stack()
            { }
            // ASSIGNATION
            const stack &operator=(const stack &ref) {
                _container = ref._container;
                return (*this);
            }

            // MEMBER FUNCTIONS
            bool empty() const { return (_container.empty()); }
            size_type size() const { return (_container.size()); }
            value_type &top() { return (_container.back()); }
            const value_type &top() const { return (_container.back()); }
            void push(const value_type &val) { _container.push_back(val); }
            void pop() { _container.pop_back(); }
            
            // ADDITION ( ONLY FOR DISPLAY )
            C &getContainer() const { return (const_cast<C&>(_container)); }

            friend bool operator==(const stack<T, C> &lhs, const stack<T, C> &rhs) { return (lhs._container == rhs._container); }
            friend bool operator!=(const stack<T, C> &lhs, const stack<T, C> &rhs) { return (lhs._container != rhs._container); }
            friend bool operator<(const stack<T, C> &lhs, const stack<T, C> &rhs) { return (lhs._container < rhs._container); }
            friend bool operator<=(const stack<T, C> &lhs, const stack<T, C> &rhs) { return (lhs._container <= rhs._container); }
            friend bool operator>(const stack<T, C> &lhs, const stack<T, C> &rhs) { return (lhs._container > rhs._container); }
            friend bool operator>=(const stack<T, C> &lhs, const stack<T, C> &rhs) { return (lhs._container >= rhs._container); }

        private :

            container_type  _container;

    };

    // THIS IS NOT PART OF THE STL CONTAINER
    template < typename T >
    std::ostream &operator<<(std::ostream &out, stack<T> const &stack) {
        size_t size = stack.size();
        out << "\t>> STACK [" << size << "]\t= { ";
        if (size)
        {
            for (typename ft::list<T>::reverse_iterator it = stack.getContainer().rbegin(); size-- > 0; it++)
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