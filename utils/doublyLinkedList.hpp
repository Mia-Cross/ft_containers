/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublyLinkedList.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/26 03:57:17 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

# include <memory>
# include <iostream>
# include "element.hpp"

template < typename T, class Alloc >
class dLList
{
    private:

        element<T, Alloc> *first;
        element<T, Alloc> *last;

    public :

        typedef element< T, Alloc > elem_type;

        dLList() : first(new elem_type), last(new elem_type) {
            first->linkWith(last);
        }
        ~dLList() {
            delete first;
            delete last;
        }
        dLList(const dLList &ref) { *this = ref; }
        dLList &operator=(const dLList &ref) {
            this->first = ref.first;
            this->last = ref.last;
            return (*this);
        }

        // elem_type  *forward() const { return (getNext()); }
        // elem_type  *backward() const { return (getPrev()); }
        
        elem_type         *getHead() { return (first); }
        const elem_type   *getHead() const { return (first); }
        elem_type         *getTail() { return (last); }
        const elem_type   *getTail() const { return (last); }
        elem_type         *getFirst() { return (first->getNext()); }
        const elem_type   *getFirst() const { return (first->getNext()); }
        elem_type         *getLast() { return (last->getPrev()); }
        const elem_type   *getLast() const { return (last->getPrev()); }
        
        elem_type  *getElement(size_t index) {
            elem_type *elem = this->getHead();
            while (elem->next && index--)
                elem = elem->next;
            if (!elem->content)
                return (NULL);
            return (elem);
        }
        const elem_type  *getElement(size_t index) const {
            const elem_type *elem = this->getHead();
            while (elem && index--)
                elem = elem->next;
            if (!elem->content)
                return (NULL);
            return (elem);
        }

        // elem_type *addElement(elem_type *to_add) {
            
        // }

        void insertElements(dLList *begin, dLList *end) {
            dLList *elem = this->prev;
            while (elem && end->prev && end != begin)
            {
                // std::cout << "end = " << end << std::endl;
                // std::cout << "end->prev = " << end->prev << std::endl;
                // std::cout << "begin = " << begin << std::endl;
                // std::cout << "content = " << *end->content << std::endl;
                end = end->prev;
                elem->insertAfter(end);
            }
        }
        

        void spliceDLL(dLList *src) {
            if (src->next)
                src->next->prev = src->prev;
            if (src->prev)
                src->prev->next = src->next;
            this->insertBefore(src);
        }

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