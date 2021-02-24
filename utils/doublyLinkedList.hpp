/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/24 04:31:48 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

# include <memory>
# include <iostream>

template < typename T, class Alloc = std::allocator<T> >
class dLList
{
    private:

        T       *content;
        dLList  *next;
        dLList  *prev;
        Alloc   myAlloc;

    public :

        // ----- COPLIEN FORM  ----- //

        dLList() : content(NULL), next(NULL), prev(NULL) {}
        dLList(T value) : next(NULL), prev(NULL) {
            this->content = myAlloc.allocate(1); 
            *this->content = value; }
        ~dLList() { myAlloc.deallocate(this->content, 1); }
        dLList(const dLList &ref) : next(ref.next), prev(ref.prev) {
            this->content = myAlloc.allocate(1); 
            *this->content = *ref.content; }
        dLList &operator=(const dLList &ref) {
            std::cout << "J'affecte " << *ref.content << " a " << this << std::endl;
            *this->content = *ref.content;
            // std::cout << "J'ai affecté " << *this->content << std::endl;
            // this->next = ref.next;
            // this->prev = ref.prev;
            return (*this);
        }

        // ----- SETTERS & GETTERS  ----- //

        dLList  *getNext() const { return (this->next); }
        dLList  *getPrev() const { return (this->prev); }
        T       *getContentPtr() const { return (this->content); }
        T       &getContentRef() const { return (*this->content); }
        void    setContent(T const &val) { *this->content = val; }
        
        void resetPointers() {
            this->next = NULL;
            this->prev = NULL;
        }

        dLList  *getHead() {
            dLList *elem = this;
            while (elem->prev)
                elem = elem->prev;
            return (elem);
        }
        const dLList  *getHead() const {
            const dLList *elem = this;
            while (elem->prev)
                elem = elem->prev;
            return (elem);
        }
        dLList  *getTail() {
            dLList *elem = this;
            while (elem->next)
                elem = elem->next;
            return (elem);
        }
        const dLList  *getTail() const {
            const dLList *elem = this;
            while (elem->next)
                elem = elem->next;
            return (elem);
        }
        dLList  *getFirst() {
            return (getHead()->next);
        }
        const dLList  *getFirst() const {
            return (getHead()->next);
        }
        dLList  *getLast() {
            return (getTail()->prev);
        }
        const dLList  *getLast() const {
            return (getTail()->prev);
        }
        dLList  *getElement(size_t index) {
            if (index >= this->getSize())
                return (NULL);
            dLList *elem = this->getHead();
            while (elem->next && index--)
                elem = elem->next;
            return (elem);
        }
        const dLList  *getElement(size_t index) const {
            if (index >= this->getSize())
                return (NULL);
            const dLList *elem = this->getHead();
            while (elem->next && index--)
                elem = elem->next;
            return (elem);
        }
        size_t getSize() const {
            size_t          size = 0;
            const dLList    *elem = getHead();
            while (elem->next && elem->next->content)
            {
                size++;
                elem = elem->next;
            }
            return (size);
        }

        // ----- LIST MODIFIERS  ----- //

        void insertBefore(dLList *to_add) {
            to_add->next = this;
            to_add->prev = this->prev;
            if (this->prev)
                this->prev->next = to_add;
            this->prev = to_add;
        }
        void insertAfter(dLList *to_add) {
            to_add->prev = this;
            to_add->next = this->next;
            if (this->next)
                this->next->prev = to_add;
            this->next = to_add;
        }
        void deleteElement() {
            if (this->next)
                this->next->prev = this->prev;
            if (this->prev)
                this->prev->next = this->next;
            delete this;
        }
        // void clearDLL() {
        //     dLList *elem = getFirst();
        //     while (elem != getTail())
        //         elem->deleteElement();
        //     //getHead()->next = NULL;
        // }
        
        // void swapElement(dLList &elem) {
        //     dLList tmp = *this;
        //     *this = elem;
        //     elem = tmp;
        // }

        // void swapDLL(dLList *head) {
        //     dLList *elem1 = this->getFirstElement;
        //     dLList *elem2 = head;
        //     while 
        // }

};

#endif