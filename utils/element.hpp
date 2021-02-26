/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:19:52 by lemarabe          #+#    #+#             */
/*   Updated: 2021/02/26 03:55:19 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H

# include <memory>
# include <iostream>

            // std::cout << " *** Jalloue un element vide// addr = " << this << std::endl;
            // std::cout << " *** Jalloue un element // addr = " << this << " // avec content.addr = " << content << std::endl;
            // std::cout << " *** Je free un element // addr = " << this;
                // std::cout << " // avec content.addr = " << content;
            // std::cout << std::endl;
template < typename T, class Alloc >
class element
{
    private :
        
        T       *content;
        element *next;
        element *prev;
        Alloc   myAlloc;

    public :

        element() : next(NULL), prev(NULL), myAlloc(Alloc()) {
            this->content = myAlloc.allocate(1);
            *this->content = 0; }
        element(T value) : next(NULL), prev(NULL), myAlloc(Alloc()) {
            this->content = myAlloc.allocate(1);
            *this->content = value; }
        element(const element &ref) : next(NULL), prev(NULL), myAlloc(Alloc()) {
            this->content = myAlloc.allocate(1); 
            *this->content = *ref.content; }
        ~element() {
            if (this->content)
                myAlloc.deallocate(this->content, 1); }
        element &operator=(const element &ref) {
            // std::cout << "J'affecte " << *ref.content << " a " << this << std::endl;
            *this->content = *ref.content;
            // std::cout << "J'ai affecté " << *this->content << std::endl;
            this->next = ref.next;
            this->prev = ref.prev;
            return (*this);
        }
    
        element  *getFirst() {
            element *elem = this;
            while (elem->prev)
                elem = elem->prev;
            return (elem);
        }
        const element  *getFirst() const {
            const element *elem = this;
            while (elem->prev)
                elem = elem->prev;
            return (elem);
        }
        element  *getLast() {
            element *elem = this;
            while (elem->next)
                elem = elem->next;
            return (elem);
        }
        const element  *getLast() const {
            const element *elem = this;
            while (elem->next)
                elem = elem->next;
            return (elem);
        }
        
        void linkWith(element *next) {
            this->next = next;
            next->prev = this;
        }
        void insertBefore(element *to_add) {
            to_add->next = this;
            to_add->prev = this->prev;
            if (this->prev)
                this->prev->next = to_add;
            this->prev = to_add;
        }
        void insertAfter(element *to_add) {
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
            // std::cout << "Je delete elem -> " << this << std::endl;
            delete this;
        }
        element *getNext() const { return (this->next); }
        element *getPrev() const { return (this->prev); }
        T       *getContentPtr() const { return (this->content); }
        T       &getContentRef() const { return (*this->content); }
};

#endif