/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/17 03:41:44 by lemarabe         ###   ########.fr       */
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
        ~dLList() { this->clearDLL(); }
        dLList(const dLList &ref) { *this = ref; }
        dLList &operator=(const dLList &ref) {
            if (this->content)
                this->deleteElement();
            this->content = ref.content;
            this->next = ref.next;
            this->prev = ref.prev;
            return (*this);
        }

        // ----- SETTERS & GETTERS  ----- //

        void    setValue(T const &val) { *this->content = val; }
        T       &getValueRef() const { return (*this->content); }
        T       *getValuePtr() const { return (this->content); }
        dLList  *getNext() const { return (this->next); }
        dLList  *getPrev() const { return (this->prev); }

        dLList  *getFrontEnd() {
            dLList *elem = this;
            while (elem && elem->prev)
                elem = elem->prev;
            return (elem);
        }
        dLList  *getBackEnd() {
            dLList *elem = this;
            while (elem && elem->next)
                elem = elem->next;
            return (elem);
        }
        dLList  *getElement(size_t n) {
            if (n < 0 || n > this->getSize())
                return (NULL);
            // std::cout << "get " << n << "th element : ";
            dLList *elem = this->getFrontEnd();
            while (elem && elem->next && n-- > 0)
                elem = elem->next;
            // std::cout << *elem->content << "\n";
            return (elem);
        }
        size_t getSize() const {
            size_t          size = 0;
            const dLList    *elem = getFrontEnd();
            if (this->content)
                size++;
            while (elem->next)
            {
                elem = elem->next;
                size++;
            }
            return (size);
        }

        // ----- LIST MODIFIERS  ----- //

        dLList  &newElement(T value) {
            dLList *elem = new dLList;
            elem->content = myAlloc.allocate(1);
            *elem->content = value;
            elem->next = NULL;
            elem->prev = NULL;
            return (*elem);
        }
        void insertBefore(dLList &to_add) {
            if (this->getSize())
            {
                to_add.next = this;
                to_add.prev = this->prev;
                if (this->prev)
                    this->prev->next = &to_add;
                this->prev = &to_add;
            }
            else
            {
                *this = to_add;
                //delete to_add;
            }
        }
        void insertAfter(dLList &to_add) {
            if (this->getSize())
            {
                to_add.next = this->next;
                to_add.prev = this;
                if (this->next)
                    this->next->prev = &to_add;
                this->next = &to_add;
            }
            else
            {
                *this = to_add;
                //delete to_add;
            }
        }
        void deleteElement() {
            if (this->next)
                this->next->prev = this->prev;
            if (this->prev)
                this->prev->next = this->next;
            //dLList *to_del = this;
            myAlloc.deallocate(this->content, 1);
            //delete this;
        }
        void clearDLL() {
            dLList *elem = getFrontEnd();
            if (elem)
            {
                while (elem && elem->next)
                {
                    dLList *to_del = elem;
                    elem = elem->next;
                    myAlloc.deallocate(to_del->content, 1);
                    //delete to_del;
                }
                myAlloc.deallocate(elem->content, 1);
                //delete elem;
            }
        }

        // void clearFromIndex(size_t n) {
        //     dLList *elem = getElement(n);
        //     if (elem)
        //     {
        //         elem->next = NULL;
        //         while (elem->next)
        //         {
        //             dLList *to_del = elem;
        //             elem = elem->next;
        //             myAlloc.deallocate(to_del->content, 1);
        //             //delete to_del;
        //         }
        //         myAlloc.deallocate(elem->content, 1);
        //         //delete elem;
        //     }
        // }
        // ----- GETTERS FOR CONST INSTANCES ----- //
        
        const dLList  *getFrontEnd() const {
            const dLList *elem = this;
            while (elem->prev)
                elem = elem->prev;
            return (elem);
        }
        const dLList  *getBackEnd() const {
            const dLList *elem = this;
            while (elem->next)
                elem = elem->next;
            return (elem);
        }
        const dLList  *getElement(size_t n) const {
            if (n < 0 || n > this->getSize())
                return (NULL);
            // std::cout << "get " << n << "th element : ";
            const dLList *elem = this->getFrontEnd();
            while (elem && elem->next && n-- > 0)
                elem = elem->next;
            // std::cout << *elem->content << "\n";
            return (elem);
        }
};

#endif