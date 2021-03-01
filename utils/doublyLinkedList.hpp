/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/01 04:52:50 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

# include <memory>
# include <iostream>
// # include "myIterator.hpp"

template < typename T, class Alloc >
class dLList
{
    private:

        T       *content;
        // dLList  *head;
        // dLList  *first;
        // dLList  *last;
        dLList  *next;
        dLList  *prev;
        Alloc   allocDLL;
        // size_t  sizeDLL;

    public :

        //create blank list
        dLList() : next(NULL), prev(NULL), allocDLL(Alloc()) {}

        // create new element with given value
        dLList(T value) : next(NULL), prev(NULL),
            allocDLL(Alloc()) {
                this->content = allocDLL.allocate(1);
                *this->content = value;
            }

        // create new element by value and insert it at iter
        dLList(T value, dLList *iter) : next(iter->next),
            prev(iter->prev), allocDLL(Alloc()) {
                this->content = allocDLL.allocate(1);
                *this->content = value;
                if (iter->prev)
                    iter->prev->next = this;
                iter->prev = this;
                // sizeDLL++;
            }

        ~dLList() {
            if (this->content)
                allocDLL.deallocate(this->content, 1);
        }
        
        dLList(const dLList &ref) { *this = ref; }
        
        dLList &operator=(const dLList &ref) {
            *this->content = *ref.content;
            this->first = ref.first;
            this->last = ref.last;
            this->next = ref.next;
            this->prev = ref.prev;
            // this->sizeDLL = ref.sizeDLL;
            this->allocDLL = ref.allocDLL;
            return (*this);
        }

        // dLList         *getHead() { return (head); }
        // const dLList   *getHead() const { return (head); }
        // dLList         *getTail() { return (last); }
        // const dLList   *getTail() const { return (last); }
        // dLList         *getFirst() { return (head->next); }
        // const dLList   *getFirst() const { return (head->next); }
        dLList *getFirst() {
            dLList *elem = this;
            while (elem->prev)
                elem = elem->prev;
            return (elem);
        }
        const dLList *getFirst() const {
            const dLList *elem = this;
            while (elem->prev)
                elem = elem->prev;
            return (elem);
        }
        dLList *getLast() {
            dLList *elem = this;
            while (elem->next)
                elem = elem->next;
            return (elem);
        }
        const dLList *getLast() const {
            const dLList *elem = this;
            while (elem->next)
                elem = elem->next;
            return (elem);
        }
        dLList *getNext() const { return (this->next); }
        dLList *getPrev() const { return (this->prev); }
        T       *getContentPtr() const { return (this->content); }
        T       &getContentRef() const { return (*this->content); }
        // size_t  getSize() const { return (this->sizeDLL); }
        dLList  *getElement(T *to_find) {
            dLList *elem = this->getFirst();
            while (elem && elem->content)
            {
                if (elem->content == to_find)
                    return (elem);
                elem = elem->next;
            }
            return (NULL);
        }

        // void linkWith(dLList *to_follow) {
        //     if (this->next)
        //         this->next->prev = to_follow;
        //     if (this->prev)
        //         this->prev->next
        //     to_follow->next = this->next;
        //     this->next = to_follow;
        //     to_follow->prev = this;
        //     // this->sizeDLL++;
        // }
        void insertBefore(dLList *to_add) {
            to_add->next = this;
            to_add->prev = this->prev;
            if (this->prev)
                this->prev->next = to_add;
            this->prev = to_add;
        }
        void extractElement() {
            if (this->next)
                this->next->prev = this->prev;
            if (this->prev)
                this->prev->next = this->next;
            // this->sizeDLL--;
        }
        void deleteElement() {
            this->extractElement();
            delete this;
        }



        
        // dLList  *getElement(size_t index) {
        //     dLList *elem = this->getHead();
        //     while (elem->next && index--)
        //         elem = elem->next;
        //     if (!elem->content)
        //         return (NULL);
        //     return (elem);
        // }
        // const dLList  *getElement(size_t index) const {
        //     const dLList *elem = this->getHead();
        //     while (elem && index--)
        //         elem = elem->next;
        //     if (!elem->content)
        //         return (NULL);
        //     return (elem);
        // }

        // dLList *addElement(dLList *to_add) {
            
        // }

        // void insertElements(dLList *begin, dLList *end) {
        //     dLList *elem = this->prev;
        //     while (elem && end->prev && end != begin)
        //     {
        //         // std::cout << "end = " << end << std::endl;
        //         // std::cout << "end->prev = " << end->prev << std::endl;
        //         // std::cout << "begin = " << begin << std::endl;
        //         // std::cout << "content = " << *end->content << std::endl;
        //         end = end->prev;
        //         elem->insertAfter(end);
        //     }
        // }

        // void spliceDLL(dLList *src) {
        //     if (src->next)
        //         src->next->prev = src->prev;
        //     if (src->prev)
        //         src->prev->next = src->next;
        //     this->insertBefore(src);
        // }
        // dLList  *forward() const { return (next); }
        // dLList  *backward() const { return (prev); }
        

        // void copyList(dLList *src) {
        //     dLList *dest = this->getHead();
        //     while (src && src->content)
        //     {
        //         std::cout << "src = " << *src->content << std::endl;
        //         dest->insertAfter(new element(*(src->content)));
        //         // dest = dest->next;
        //         src = src->next;
        //     }
        // }
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

        // size_t getSize() const {
        //     size_t          size = 0;
        //     const dLList    *elem = getHead();
        //     while (elem->next && elem->next->content)
        //     {
        //         size++;
        //         elem = elem->next;
        //     }
        //     return (size);
        // }
};

#endif