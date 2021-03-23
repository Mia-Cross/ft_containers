/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/23 01:24:26 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_H
# define BINARY_SEARCH_TREE_H

# include <memory>
# include <iostream>

template < class Key, class T, class Compare, class Alloc >
class binTree
{
    private:

        Key     key;
        T       *value;
        binTree *root;
        binTree *right;
        binTree *left;
        Compare comp;
        Alloc   allocBT;

    public :

        //create blank list
        binTree() : head(this), next(this), prev(this),
            allocDLL(Alloc()) {
                this->content = allocDLL.allocate(1);
                *this->content = 0;
            }

        // create new element with given value
        binTree(T value) : head(NULL), next(NULL), prev(NULL), allocDLL(Alloc()) {
            this->content = allocDLL.allocate(1);
            *this->content = value;
        }

        ~binTree() { allocDLL.deallocate(this->content, 1); }
        
        binTree(const binTree &ref) { *this = ref; }
        
        binTree &operator=(const binTree &ref) {
            *this->content = *ref.content;
            this->head = ref.head;
            this->last = ref.last;
            this->next = ref.next;
            this->prev = ref.prev;
            this->allocDLL = ref.allocDLL;
            return (*this);
        }

        binTree  *getNext() const { return (this->next); }
        binTree  *getPrev() const { return (this->prev); }
        T       *getContentPtr() const { return (this->content); }
        T       &getContentRef() const { return (*this->content); }
        binTree  *getFirst() const { return (head->next); }
        binTree  *getLast() const { return (head->prev); }
        binTree  *getElement(T *to_find) const {
            if (head->content == to_find)
                return (head);
            binTree *elem = this->getFirst();
            while (elem && elem != head)
            {
                if (elem->content == to_find)
                    return (elem);
                elem = elem->next;
            }
            return (NULL);
        }               // euh pk j'en ai 2 ... ?
        binTree          *getElement(binTree *to_find) const {
            if (head == to_find)
                return (head);
            binTree *elem = this->getFirst();
            while (elem && elem != head)
            {
                if (elem == to_find)
                    return (elem);
                elem = elem->next;
            }
            return (NULL);
        }
        void insertBefore(binTree *to_add) {
            to_add->head = this->head;
            to_add->next = this;
            to_add->prev = this->prev;
            if (this->prev)
                this->prev->next = to_add;
            this->prev = to_add;
        }
        void insertAfter(binTree *to_add) {
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
            binTree *tmp = this->next;
            this->next = this->prev;
            this->prev = tmp;
        }  //check si je veux virer
        void swapWithNext() {
            binTree *next = this->next;
            this->next = this->next->next;
            next->extractElement();
            this->insertBefore(next);
        }


};

#endif