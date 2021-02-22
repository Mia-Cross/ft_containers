/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/22 16:41:19 by lemarabe         ###   ########.fr       */
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
            *this->content = ref.content; }
        dLList &operator=(const dLList &ref) {
            *this->content = ref.content;
            this->next = ref.next;
            this->prev = ref.prev;
            return (*this);
        }

        // ----- SETTERS & GETTERS  ----- //

        dLList  *getNext() const { return (this->next); }
        dLList  *getPrev() const { return (this->prev); }
        T       *getContentPtr() const { return (this->content); }
        T       &getContentRef() const { return (*this->content); }
        void    setContent(T const &val) { *this->content = val; std::cout << *this->content << std::endl;}

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
        dLList  *getFirstElement() {
            return (getHead()->next);
        }
        const dLList  *getFirstElement() const {
            return (getHead()->next);
        }
        dLList  *getLastElement() {
            return (getTail()->prev);
        }
        const dLList  *getLastElement() const {
            return (getTail()->prev);
        }
        dLList  *getElement(size_t index) {
            if (index < this->getSize())
            {
                dLList *elem = this->getHead();
                while (elem->next && index--)
                    elem = elem->next;
                return (elem);
            }
            return (NULL);
        }
        const dLList  *getElement(size_t index) const {
            if (index < this->getSize())
            {
                const dLList *elem = this->getHead();
                while (elem->next && index--)
                    elem = elem->next;
                return (elem);
            }
            return (NULL);
        }
        dLList  *getElement(dLList *to_find) {
            dLList *elem = this->getHead();
            while (elem)
            {
                if (elem == to_find)
                    return (elem);
                elem = elem->next;
            }
            return (NULL);
        }
        const dLList  *getElement(dLList *to_find) const {
            const dLList *elem = this->getHead();
            while (elem)
            {
                if (elem == to_find)
                    return (elem);
                elem = elem->next;
            }
            return (NULL);
        }
        size_t getSize() const {
            size_t          size = 0;
            const dLList    *elem = getHead();
            while (elem->next)
            {
                elem = elem->next;
                size++;
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
        void clearDLL() {
            dLList *elem = getHead();
            while (elem)
            {
                dLList *to_del = elem;
                elem = elem->next;
                delete to_del;
            }
            delete elem;
        }
        // void clearFromIndex(size_t n) {
        //     dLList *elem = getElement(n);
        //     while (elem)
        //     {
        //         dLList *to_del = elem;
        //         elem = elem->next;
        //         delete to_del;
        //     }
        //     elem = getLastElement();
        //     if (elem)
        //         elem->next = NULL;
        // }

};

#endif