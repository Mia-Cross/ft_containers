/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/09 02:23:15 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

# include <memory>
# include <iostream>

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
            this->last = ref.last;
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
        dLList  *getElement(T *to_find) const {
            if (head->content == to_find)
                return (head);
            dLList *elem = this->getFirst();
            while (elem && elem != head)
            {
                if (elem->content == to_find)
                    return (elem);
                elem = elem->next;
            }
            return (NULL);
        }               // euh pk j'en ai 2 ... ?
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
        }  //check si je veux virer
        void swapWithNext() {
            dLList *next = this->next;
            this->next = this->next->next;
            next->extractElement();
            this->insertBefore(next);
        }


};

#endif