/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:13 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/04 05:28:23 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_RANDOM_ACCESS_ITERATOR_H
# define MY_RANDOM_ACCESS_ITERATOR_H

#include "bidirectionalIterator.hpp"

template < typename T >
struct myRandomAccessIterator : public virtual myBidirectionalIterator<T>
{
    typedef myRandomAccessIterator  iterator_category;

    //----- CONSTRUCTORS AND DESTRUCTORS -----//
    myRandomAccessIterator() {}
    myRandomAccessIterator(T *p) : myBidirectionalIterator<T>(p) {}
    myRandomAccessIterator(const myRandomAccessIterator &ref) { this->it = ref.it; };
    virtual ~myRandomAccessIterator() {}

    //----- OPERATORS : 'decrementation' -----//
    myRandomAccessIterator  &operator=(const myRandomAccessIterator &ref) { this->it = ref.it; return (*this); }
    //[...]
};

#endif