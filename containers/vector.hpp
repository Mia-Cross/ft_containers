/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 06:19:44 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/06 06:39:57 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "../templates/myIterator.hpp"
#include <memory>
#include <iostream>

namespace ft
{
    template < typename T, class Alloc = std::allocator<T> >
    class Vector {

        public :

            //defining every member in my List as in the STL
            typedef T                                       value_type;
            typedef Alloc                                   allocator_type;
            typedef T &                                     reference;
            typedef T *                                     pointer;
            typedef const T &	                            const_reference;
            typedef const T *	                            const_pointer;
            typedef myIterator< T, dLList<T,Alloc> >        iterator;
            typedef myCIterator< T, dLList<T,Alloc> >       const_iterator;
            typedef myRIterator< T, dLList<T,Alloc> >       reverse_iterator;
            typedef myCRIterator< T, dLList<T,Alloc> >      const_reverse_iterator;
            typedef size_t                                  size_type;
            typedef ptrdiff_t                               difference_type;

            // DEFAULT CONSTRUCTOR
            explicit Vector(const allocator_type& alloc = allocator_type()) {}
            // CONSTRUCTOR BY FILLING
            explicit Vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) {}
            // CONSTRUCTOR BY RANGE
            Vector(iterator first, iterator last,
                const allocator_type& alloc = allocator_type()) {}
            // CONSTRUCTOR BY COPY
            Vector(const Vector &ref) {}
            // DESTRUCTOR
            ~Vector() {}
            // ASSIGNATION
            const Vector &operator=(const Vector &ref) {}

        private :



    };
}

#endif