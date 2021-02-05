/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forwardIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:10 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/04 04:26:11 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_FORWARD_ITERATOR_H
# define MY_FORWARD_ITERATOR_H

#include <iterator>
#include <cstddef>

template < typename T >
class myForwardIterator
{
    public :

        typedef myForwardIterator  iterator_category;
        typedef T           value_type;
        typedef ptrdiff_t   difference_type;
        typedef T *         pointer;
        typedef T &         reference;

        //----- COPY CONSTRUCTIBLE, ASSIGNABLE AND DESTRUCTIBLE -----//
        myForwardIterator() {}
        myForwardIterator(T *p) : it(p) {}
        myForwardIterator(const myForwardIterator &ref) : it(ref.it) {}//{ this->it = ref.it; }
        virtual ~myForwardIterator() {}

        //----- OPERATORS : 'assignation' & 'incrementation' -----//
        myForwardIterator  &operator=(const myForwardIterator &ref) { this->it = ref.it; return (*this); }
        virtual myForwardIterator  &operator++() { this->it++; return (*this); }
        virtual myForwardIterator  operator++(int) { myForwardIterator tmp(*this); operator++(); return (tmp); }
        //----- OPERATORS : 'equality' 'inequality' 'dereference' -----//
        virtual bool    operator==(const myForwardIterator &ref) const { return (this->it == ref.it); }
        virtual bool    operator!=(const myForwardIterator &ref) const { return (this->it != ref.it); }
        virtual T       &operator*() { return (*this->it); }

    protected :

        T *it;
};

#endif