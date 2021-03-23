/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/23 06:09:22 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_H
# define BINARY_SEARCH_TREE_H

# include <memory>
# include <cstddef>

# include <iostream>

template < class Key, class T, class Compare, class Alloc >
class binTree
{
    private:

        binTree *root;
        binTree *left;
        binTree *right;
        Compare comp;
        Alloc   allocBT;

    public :
        std::pair<const Key, T> *value;

        //create blank list
        binTree() : root(this), left(this), right(this),
            allocBT(Alloc()) {
                // std::cout << "Constructor called" << std::endl;
                this->value = allocBT.allocate(1);
            }

        // create new element with given value
        binTree(std::pair<const Key, T> value) : root(NULL), left(NULL), right(NULL), allocBT(Alloc()) {
            this->value = allocBT.allocate(1);
            allocBT.construct(this->value, value);
        }

        ~binTree() {
            allocBT.deallocate(this->value, 1);
        }
        
        binTree(const binTree &ref) { *this = ref; }
        
        binTree &operator=(const binTree &ref) {
            *this->value = *ref.value;
            this->root = ref.root;
            this->left = ref.left;
            this->right = ref.right;
            this->allocBT = ref.allocBT;
            return (*this);
        }

        binTree  *getLeft() const { return (this->left); }
        binTree  *getRight() const { return (this->right); }
        binTree  *getHead() const { return (this->root); }
        // T       *getContentPtr() const { return (this->content); }
        Key       &getKeyRef() const { return (*this->key); }
        T       &getValueRef() const { return (*this->value); }
        // binTree  *getLast() const { return (root->right); }
        // binTree  *getElement(T *to_find) const {
        //     if (root->content == to_find)
        //         return (root);
        //     binTree *elem = this->getFirst();
        //     while (elem && elem != root)
        //     {
        //         if (elem->content == to_find)
        //             return (elem);
        //         elem = elem->left;
        //     }
        //     return (NULL);
        // }               // euh pk j'en ai 2 ... ?
        // binTree          *getElement(binTree *to_find) const {
        //     if (root == to_find)
        //         return (root);
        //     binTree *elem = this->getFirst();
        //     while (elem && elem != root)
        //     {
        //         if (elem == to_find)
        //             return (elem);
        //         elem = elem->left;
        //     }
        //     return (NULL);
        // }
        // void insertBefore(binTree *to_add) {
        //     to_add->root = this->root;
        //     to_add->left = this;
        //     to_add->right = this->right;
        //     if (this->right)
        //         this->right->left = to_add;
        //     this->right = to_add;
        // }
        // void insertAfter(binTree *to_add) {
        //     to_add->root = this->root;
        //     to_add->right = this;
        //     to_add->left = this->left;
        //     if (this->left)
        //         this->left->right = to_add;
        //     this->left = to_add;
        // }
        // void extractElement() {
        //     this->left->right = this->right;
        //     this->right->left = this->left;
        //     this->root = NULL;
        //     this->left = NULL;
        //     this->right = NULL;
        // }
        // void deleteElement() {
        //     this->extractElement();
        //     delete this;
        // }
        // void swapPointers() {
        //     binTree *tmp = this->left;
        //     this->left = this->right;
        //     this->right = tmp;
        // }  //check si je veux virer
        // void swapWithNext() {
        //     binTree *left = this->left;
        //     this->left = this->left->left;
        //     left->extractElement();
        //     this->insertBefore(left);
        // }
};

template < class Key, class T, class Compare, class Alloc >
class bstIter
{
    public :

        typedef std::pair< Key, T >     value_type;
        typedef std::pair< Key, T > *   value_ptr_type;
        typedef T *                     pointer_type;
        typedef T &                     reference_type;
        // typedef binTree<Key,T,Compare,Alloc>     element_type;
        // typedef binTree<Key,T,Compare,Alloc> *   elem_ptr_type;
        // typedef ptrdiff_t               difference_type;
        typedef Compare                 key_compare;
        //typedef ___                   value_compare;
        typedef Alloc                   allocator_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        bstIter() {}
        bstIter(value_ptr_type p) : it(p) {}
        bstIter(const bstIter &ref) : it(ref.it) {}
        virtual ~bstIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        bstIter  &operator=(const bstIter &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const bstIter &ref) const { return (this->it == ref.it); }
        bool        operator!=(const bstIter &ref) const { return (this->it != ref.it); }
        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (this->it->getContentRef()); }
        value_ptr_type   operator->() const { return (this->it); }
        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        bstIter  &operator++() { this->it = this->it->getLeft(); return (*this); }
        bstIter  operator++(int) { bstIter tmp(*this); operator++(); return (tmp); }
        bstIter  &operator--() { this->it = this->it->getRight(); return (*this); }
        bstIter  operator--(int) { bstIter tmp(*this); operator--(); return (tmp); }

    protected :

        value_ptr_type it;
};

template < class Key, class T, class Compare, class Alloc >
class cBSTIter : public virtual bstIter<Key,T,Compare,Alloc>
{
    public :
    
        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        typedef std::pair< Key, T > *   value_ptr_type;
        
        //----- CONSTRUCTORS & DESTRUCTORS -----//
        cBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        cBSTIter(value_ptr_type p) : bstIter<Key,T,Compare,Alloc>(p) {}
        cBSTIter(const cBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.it) {}
        virtual ~cBSTIter() {}
        cBSTIter  &operator=(const cBSTIter &ref) { this->it = ref.it; return (*this); }
        //----- OPERATORS :  'dereference' -----//
        const_reference_type       operator*() const { return (this->it->getContentRef()); }
        const_pointer_type         operator->() const { return (this->it->getContentPtr()); }
};

template < class Key, class T, class Compare, class Alloc >
class rBSTIter : public virtual bstIter<Key,T,Compare,Alloc>
{
    public :
        
        typedef std::pair< Key, T > *   value_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        rBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        rBSTIter(value_ptr_type p) : bstIter<Key,T,Compare,Alloc>(p) {}
        rBSTIter(const rBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.it) {}
        virtual ~rBSTIter() {}
        rBSTIter  &operator=(const rBSTIter &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        rBSTIter  &operator++() { this->it = this->it->getRight(); return (*this); }
        rBSTIter  operator++(int) { rBSTIter tmp(*this); operator++(); return (tmp); }
        rBSTIter  &operator--() { this->it = this->it->getLeft(); return (*this); }
        rBSTIter  operator--(int) { rBSTIter tmp(*this); operator--(); return (tmp); }
};

template < class Key, class T, class Compare, class Alloc >
class crBSTIter : public virtual cBSTIter<Key,T,Compare,Alloc>, public virtual rBSTIter<Key,T,Compare,Alloc>
{
    public :

        typedef const T *   const_pointer_type;
        typedef const T &   const_reference_type;
        typedef std::pair< Key, T > *   value_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        crBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        crBSTIter(value_ptr_type p) : bstIter<Key,T,Compare,Alloc>(p) {}
        crBSTIter(const crBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.it) {}
        virtual ~crBSTIter() {}
        crBSTIter  &operator=(const crBSTIter &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        crBSTIter  &operator++() { this->it = this->it->getRight(); return (*this); }
        crBSTIter  operator++(int) { crBSTIter tmp(*this); operator++(); return (tmp); }
        crBSTIter  &operator--() { this->it = this->it->getLeft(); return (*this);  }
        crBSTIter  operator--(int) { crBSTIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (this->it->getContentRef()); }
        const_pointer_type    operator->() const { return (this->it->getContentPtr()); }
};

#endif