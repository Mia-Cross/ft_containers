/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/18 05:31:24 by lemarabe         ###   ########.fr       */
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

        dLList() : content(NULL), next(NULL), prev(NULL) {
            this->content = myAlloc.allocate(1);
        }
        dLList(T value) : next(NULL), prev(NULL) {
            this->content = myAlloc.allocate(1);
            this->content = &value;
        }
        ~dLList() {
            this->clearDLL();
        }
        dLList(const dLList &ref) {
            *this = ref;
        }
        dLList &operator=(const dLList &ref) {
            // if (this->content)
            //     this->deleteElement();
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

        dLList  *getFirstElem() {
            dLList *elem = this;
            while (elem->prev && elem->prev->content)
            {
                std::cout << "+" << std::endl;
                elem = elem->prev;
            }
            return (elem);
        }
        dLList  *getLastElem() {
            dLList *elem = this;
            while (elem->next && elem->next->content)
                elem = elem->next;
            return (elem);
        }
        dLList  *getElement(size_t n) {
            if (n < 0 || n > this->getSize())
                return (NULL);
            // std::cout << "get " << n << "th element : ";
            dLList *elem = this->getFrontEnd();
            while (elem->next && n--)
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

        void insertBefore(dLList *to_add) {
            std::cout << "ho" << std::endl;
            to_add->next = this;
            this->prev = to_add;
            if (this->prev)
            {
                to_add->prev = this->prev;
                this->prev->next = to_add;
            }
            std::cout << "ho" << std::endl;
        }
        void insertAfter(dLList *to_add) {
            std::cout << "hi" << std::endl;
            if (!this->content)
                
            to_add->prev = this;
            this->next = to_add;
            if (this->next)
            {
                to_add->next = this->next;
                this->next->prev = to_add;
            }
            std::cout << "hi" << std::endl;
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
                }
                myAlloc.deallocate(elem->content, 1);
                //delete elem;
            }
        }

        // ----- GETTERS FOR CONST INSTANCES ----- //
        
        const dLList  *getFrontEnd() const {
            const dLList *elem = this;
            while (elem->prev && elem->content)
                elem = elem->prev;
            return (elem);
        }
        const dLList  *getBackEnd() const {
            const dLList *elem = this;
            while (elem->next && elem->content)
                elem = elem->next;
            return (elem);
        }
        const dLList  *getElement(size_t n) const {
            if (n < 0 || n > this->getSize())
                return (NULL);
            // std::cout << "get " << n << "th element : ";
            const dLList *elem = this->getFrontEnd();
            while (elem->next && n--)
                elem = elem->next;
            // std::cout << *elem->content << "\n";
            return (elem);
        }
};

#endif