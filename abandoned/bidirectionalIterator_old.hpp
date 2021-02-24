/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectionalIterator.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:13 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/16 20:35:29 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_BIDIRECTIONAL_ITERATOR_H
# define MY_BIDIRECTIONAL_ITERATOR_H

#include "forwardIterator.hpp"

template < typename T >
struct myBidirectionalIterator : public virtual myForwardIterator<T>
{
    typedef myBidirectionalIterator  iterator_category;

    //----- CONSTRUCTORS AND DESTRUCTORS -----//
    myBidirectionalIterator() {}
    myBidirectionalIterator(T *p) : myForwardIterator<T>(p) {}
    myBidirectionalIterator(const myBidirectionalIterator &ref) { this->it = ref.it; };
    virtual ~myBidirectionalIterator() {}

    //----- OPERATORS : 'decrementation' -----//
    myBidirectionalIterator  &operator=(const myBidirectionalIterator &ref) { this->it = ref.it; return (*this); }
    virtual myBidirectionalIterator  &operator--() { this->it = this->it->prev; return (*this); }
    virtual myBidirectionalIterator  operator--(int) { myBidirectionalIterator tmp(*this); operator--(); return (tmp); }
};

#endif