/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/11 07:19:12 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

# include <memory>

template < typename T, class Alloc = std::allocator<T> >
class dLList
{
    private:

        T       *content;
        dLList  *next;
        dLList  *prev;
        Alloc   myAlloc;

    public :

        dLList() : next(NULL), prev(NULL) {}
        ~dLList() { this->clear(); }
        dLList(const dLList &ref) { *this = ref; }
        dLList &operator=(const dLList &ref) {
            this->clear();
            for (size_t i = 0; i < ref.getSize(); i++)
                insertElement(newElement(*(ref.getNthElement(i)->content)), i);
            return (*this);
        }

        T *getValue() const { return (this->content); }
        void setValue(T const &val) { *this->content = val; }

        dLList *getNthElement(size_t n) {
            dLList *elem = this;
            while (elem && elem->next && n--)
                elem = elem->next;
            return (elem);
        }

        const dLList *getNthElement(size_t n) const {
            const dLList *elem = this;
            while (elem && elem->next && n--)
                elem = elem->next;
            return (elem);
        }

        size_t getSize() const {
            size_t size = 0;
            const dLList *elem = this;
            while (elem && elem->next)
            {
                elem = elem->next;
                size++;
            }
            return (size);
        }

        dLList  *newElement(T value) {
            dLList *elem = new dLList;
            elem->content = myAlloc.allocate(1);
            elem->content = &value;
            elem->next = NULL;
            elem->prev = NULL;
            return (elem);
        }

        void insertElement(dLList *to_add, size_t n)
        {
            dLList *elemN = getNthElement(n);
            if (elemN)
            {
                dLList *tmp = elemN->next;
                elemN->next = to_add;
                to_add->next = tmp;
                to_add->prev = elemN;
            }
            else
            {
                *this = *to_add;
                delete to_add;
            }
        }

        void deleteElement(size_t n) {
            dLList *to_del = getNthElement(n);
            if (to_del)
            {
                dLList *previous = to_del->prev;
                previous->next = to_del->next;
                to_del->next->prev = previous;
                myAlloc.deallocate(to_del->content, 1);
                delete to_del;
            }
        }

        void clear() {
            dLList *elem = this;
            if (elem)
            {
                while (elem && elem->next)
                {
                    dLList *to_del = elem;
                    elem = elem->next;
                    myAlloc.deallocate(to_del->content, 1);
                    delete to_del;
                }
                myAlloc.deallocate(elem->content, 1);
                delete elem;
            }
        }

        // void push_back(T value) {
        //     dLList *last = this->getLast();
        //     if (last)
        //         last->next = newElement(value);
        // }

        // void push_front(T value) {
            
        // }
        // dLList *getFirst() {
        //     return (this);
        // }

        // dLList *getLast() {
        //     dLList *elem = this;
        //     while (elem && elem->next)
        //         elem = elem.next;
        //     return (elem);
        // }
};

#endif