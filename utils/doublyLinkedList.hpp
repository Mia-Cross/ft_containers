/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/19 02:59:19 by lemarabe         ###   ########.fr       */
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
        void    setContent(T const &val) { *this->content = val; }

        dLList  *getHead() {
            dLList *elem = this;
            while (elem->prev)
                elem = elem->prev;
            return (elem);
        }
        dLList  *getFirstElement() {
            return (getHead()->next);
        }
        dLList  *getLastElem() {
            dLList *elem = this;
            while (elem->next)
                elem = elem->next;
            return (elem);
        }
        dLList  *getElement(size_t n) {
            std::cout << "get " << n << "th element : ";
            dLList *elem = this->getHead();
            while (elem->next && n--)
                elem = elem->next;
            std::cout << *elem->content << "\n";
            if (n)
                return (NULL);
            return (elem);
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

        void insert(dLList &to_add) {
            to_add.prev = this;
            to_add.next = this->next;
            if (this->next)
                this->next->prev = &to_add;
            this->next = &to_add;
        }
        // void insertBefore(dLList &to_add) {
        //     to_add.next = this;
        //     if (this->prev)
        //         this->prev->next = &to_add;
        //     this->prev = &to_add;
        //     to_add.prev = this->prev;
        // }
        // void insertAfter(dLList &to_add) {
        //     to_add.prev = this;
        //     to_add.next = this->next;
        //     if (this->next)
        //         this->next->prev = &to_add;
        //     this->next = &to_add;
        // }
        void deleteElement() {
            if (this->next)
                this->next->prev = this->prev;
            if (this->prev)
                this->prev->next = this->next;
            myAlloc.deallocate(this->content, 1);
            delete this;
        }
        void clearDLL() {
            dLList *elem = getHead();
            if (elem)
            {
                while (elem && elem->next)
                {
                    dLList *to_del = elem;
                    elem = elem->next;
                    myAlloc.deallocate(to_del->content, 1);
                }
                myAlloc.deallocate(elem->content, 1);
                //delete elem;
            }
        }

        // ----- GETTERS FOR CONST INSTANCES ----- //
        
        const dLList  *getHead() const {
            const dLList *elem = this;
            while (elem->prev)
                elem = elem->prev;
            return (elem);
        }
        const dLList  *getFirstElement() const {
            const dLList *elem = getHead();
            return (elem->next);
        }
        const dLList  *getLastElem() const {
            const dLList *elem = this;
            while (elem->next)
                elem = elem->next;
            return (elem);
        }
        const dLList  *getElement(size_t n) const {
            std::cout << "get " << n << "th element : ";
            const dLList *elem = this->getHead();
            while (elem->next && n--)
                elem = elem->next;
            std::cout << *elem->content << "\n";
            if (n)
                return (NULL);
            return (elem);
        }
};

#endif