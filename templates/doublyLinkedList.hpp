/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/23 02:44:10 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

# include <memory>
# include <cstddef>

template < typename T, class Alloc >
class dLList
{
    private:

        T       *content;
        dLList  *head;
        dLList  *next;
        dLList  *prev;
        Alloc   allocDLL;

    public :

        //create blank list
        dLList() : head(this), next(this), prev(this),
            allocDLL(Alloc()) {
                this->content = allocDLL.allocate(1);
                *this->content = 0;
            }

        // create new element with given value
        dLList(T value) : head(NULL), next(NULL), prev(NULL), allocDLL(Alloc()) {
            this->content = allocDLL.allocate(1);
            *this->content = value;
        }

        ~dLList() { allocDLL.deallocate(this->content, 1); }
        
        dLList(const dLList &ref) { *this = ref; }
        
        dLList &operator=(const dLList &ref) {
            *this->content = *ref.content;
            this->head = ref.head;
            this->next = ref.next;
            this->prev = ref.prev;
            this->allocDLL = ref.allocDLL;
            return (*this);
        }

        dLList  *getNext() const { return (this->next); }
        dLList  *getPrev() const { return (this->prev); }
        T       *getContentPtr() const { return (this->content); }
        T       &getContentRef() const { return (*this->content); }
        dLList  *getFirst() const { return (head->next); }
        dLList  *getLast() const { return (head->prev); }
        // dLList  *getElement(T *to_find) const {
        //     if (head->content == to_find)
        //         return (head);
        //     dLList *elem = this->getFirst();
        //     while (elem && elem != head)
        //     {
        //         if (elem->content == to_find)
        //             return (elem);
        //         elem = elem->next;
        //     }
        //     return (NULL);
        // }               // euh pk j'en ai 2 ... ?
        dLList          *getElement(dLList *to_find) const {
            if (head == to_find)
                return (head);
            dLList *elem = this->getFirst();
            while (elem && elem != head)
            {
                if (elem == to_find)
                    return (elem);
                elem = elem->next;
            }
            return (NULL);
        }
        void insertBefore(dLList *to_add) {
            to_add->head = this->head;
            to_add->next = this;
            to_add->prev = this->prev;
            if (this->prev)
                this->prev->next = to_add;
            this->prev = to_add;
        }
        void insertAfter(dLList *to_add) {
            to_add->head = this->head;
            to_add->prev = this;
            to_add->next = this->next;
            if (this->next)
                this->next->prev = to_add;
            this->next = to_add;
        }
        void extractElement() {
            this->next->prev = this->prev;
            this->prev->next = this->next;
            this->head = NULL;
            this->next = NULL;
            this->prev = NULL;
        }
        void deleteElement() {
            this->extractElement();
            delete this;
        }
        void swapPointers() {
            dLList *tmp = this->next;
            this->next = this->prev;
            this->prev = tmp;
        }
        void swapWithNext() {
            dLList *next = this->next;
            this->next = this->next->next;
            next->extractElement();
            this->insertBefore(next);
        }
};

template < typename T, class Alloc >
class listIter
{
    public :

        typedef T                   value_type;
        typedef ptrdiff_t           difference_type;
        typedef T *                 pointer_type;
        typedef T &                 reference_type;
        typedef dLList<T,Alloc>     element_type;
        typedef dLList<T,Alloc> *   elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        listIter() {}
        listIter(elem_ptr_type p) : it(p) {}
        listIter(const listIter &ref) : it(ref.it) {}
        virtual ~listIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        listIter  &operator=(const listIter &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const listIter &ref) const { return (this->it == ref.it); }
        bool        operator!=(const listIter &ref) const { return (this->it != ref.it); }
        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (this->it->getContentRef()); }
        elem_ptr_type   operator->() const { return (this->it); }
        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        listIter  &operator++() { this->it = this->it->getNext(); return (*this); }
        listIter  operator++(int) { listIter tmp(*this); operator++(); return (tmp); }
        listIter  &operator--() { this->it = this->it->getPrev(); return (*this); }
        listIter  operator--(int) { listIter tmp(*this); operator--(); return (tmp); }

    protected :

        elem_ptr_type it;
};

template < typename T, class Alloc >
class cListIter : public virtual listIter<T, Alloc>
{
    public :
    
        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        typedef dLList<T,Alloc> *   elem_ptr_type;
        
        //----- CONSTRUCTORS & DESTRUCTORS -----//
        cListIter() : listIter<T,Alloc>() {}
        cListIter(elem_ptr_type p) : listIter<T,Alloc>(p) {}
        cListIter(const cListIter &ref) : listIter<T,Alloc>(ref.it) {}
        virtual ~cListIter() {}
        cListIter  &operator=(const cListIter &ref) { this->it = ref.it; return (*this); }
        //----- OPERATORS :  'dereference' -----//
        const_reference_type       operator*() const { return (this->it->getContentRef()); }
        const_pointer_type         operator->() const { return (this->it->getContentPtr()); }
};

template < typename T, class Alloc >
class rListIter : public virtual listIter<T, Alloc>
{
    public :
        
        typedef dLList<T,Alloc> *   elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        rListIter() : listIter<T,Alloc>() {}
        rListIter(elem_ptr_type p) : listIter<T,Alloc>(p) {}
        rListIter(const rListIter &ref) : listIter<T,Alloc>(ref.it) {}
        virtual ~rListIter() {}
        rListIter  &operator=(const rListIter &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        rListIter  &operator++() { this->it = this->it->getPrev(); return (*this); }
        rListIter  operator++(int) { rListIter tmp(*this); operator++(); return (tmp); }
        rListIter  &operator--() { this->it = this->it->getNext(); return (*this); }
        rListIter  operator--(int) { rListIter tmp(*this); operator--(); return (tmp); }
};

template < typename T, class Alloc >
class crListIter : public virtual cListIter<T, Alloc>, public virtual rListIter<T, Alloc>
{
    public :

        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        typedef dLList<T,Alloc> *   elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        crListIter() : listIter<T,Alloc>() {}
        crListIter(elem_ptr_type p) : listIter<T,Alloc>(p) {}
        crListIter(const crListIter &ref) : listIter<T,Alloc>(ref.it) {}
        virtual ~crListIter() {}
        crListIter  &operator=(const crListIter &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        crListIter  &operator++() { this->it = this->it->getPrev(); return (*this); }
        crListIter  operator++(int) { crListIter tmp(*this); operator++(); return (tmp); }
        crListIter  &operator--() { this->it = this->it->getNext(); return (*this);  }
        crListIter  operator--(int) { crListIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (this->it->getContentRef()); }
        const_pointer_type    operator->() const { return (this->it->getContentPtr()); }
};

#endif