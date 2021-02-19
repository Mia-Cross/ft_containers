/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myIterator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 04:26:13 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/19 02:14:55 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_ITERATOR_H
# define MY_ITERATOR_H

# include "doublyLinkedList.hpp"
# include <iterator>
# include <cstddef>

template < typename T, class C >
class myIterator
{
    public :

        typedef T               value_type;
        typedef ptrdiff_t       difference_type;
        typedef T *             pointer_type;
        typedef T &             reference_type;
        typedef C               container_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myIterator() {}
        myIterator(C *p) : it(p) {}
        myIterator(const myIterator &ref) : it(ref.it) {}
        virtual ~myIterator() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        myIterator  &operator=(const myIterator &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const myIterator &ref) const { return (this->it == ref.it); }
        bool        operator!=(const myIterator &ref) const { return (this->it != ref.it); }
        //----- OPERATORS :  'dereference' -----//
        reference_type       operator*() const { return (this->it->getContentRef()); }
        pointer_type         operator->() const { return (this->it->getContentPtr()); }
        //----- OPERATORS : & 'incrementation''decrementation' -----//
        myIterator  &operator++() { this->it = this->it->getNext(); return (*this); }
        myIterator  operator++(int) { myIterator tmp(*this); operator++(); return (tmp); }
        myIterator  &operator--() { this->it = this->it->getPrev(); return (*this); }
        myIterator  operator--(int) { myIterator tmp(*this); operator--(); return (tmp); }

    protected :

        C *it;
};

template < typename T, class C >
class myConstIterator : public virtual myIterator<T, C>
{
    public :
    
        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        
        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myConstIterator() : myIterator<T,C>() {}
        myConstIterator(C *p) : myIterator<T,C>(p) {}
        myConstIterator(const myConstIterator &ref) : myIterator<T,C>(ref.it) {}
        virtual ~myConstIterator() {}
        myConstIterator  &operator=(const myConstIterator &ref) { this->it = ref.it; return (*this); }
        //----- OPERATORS :  'dereference' -----//
        const_reference_type       operator*() const { return (this->it->getContentRef()); }
        const_pointer_type         operator->() const { return (this->it->getContentPtr()); }
};

template < typename T, class C >
class myReverseIterator : public virtual myIterator<T, C>
{
    public :
        
        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myReverseIterator() : myIterator<T,C>() {}
        myReverseIterator(C *p) : myIterator<T,C>(p) {}
        myReverseIterator(const myReverseIterator &ref) : myIterator<T,C>(ref.it) {}
        virtual ~myReverseIterator() {}
        myReverseIterator  &operator=(const myReverseIterator &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : & 'incrementation''decrementation' -----//
        myReverseIterator  &operator++() { this->it = this->it->getPrev(); return (*this); }
        myReverseIterator  operator++(int) { myReverseIterator tmp(*this); operator++(); return (tmp); }
        myReverseIterator  &operator--() { this->it = this->it->getNext(); return (*this); }
        myReverseIterator  operator--(int) { myReverseIterator tmp(*this); operator--(); return (tmp); }
};

template < typename T, class C >
class myConstReverseIterator : public virtual myConstIterator<T, C>, public virtual myReverseIterator<T, C>
{
    public :

        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        myConstReverseIterator() : myIterator<T,C>() {}
        myConstReverseIterator(C *p) : myIterator<T,C>(p) {}
        myConstReverseIterator(const myConstReverseIterator &ref) : myIterator<T,C>(ref.it) {}
        virtual ~myConstReverseIterator() {}
        myConstReverseIterator  &operator=(const myConstReverseIterator &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : & 'incrementation''decrementation' -----//
        myConstReverseIterator  &operator++() { this->it = this->it->getPrev(); return (*this); }
        myConstReverseIterator  operator++(int) { myConstReverseIterator tmp(*this); operator++(); return (tmp); }
        myConstReverseIterator  &operator--() { this->it = this->it->getNext(); return (*this);  }
        myConstReverseIterator  operator--(int) { myConstReverseIterator tmp(*this); operator--(); return (tmp); }
         //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (myConstIterator<T,C>::operator*()); }
        const_pointer_type    operator->() const { return (myConstIterator<T,C>::operator->()); }
};

#endif