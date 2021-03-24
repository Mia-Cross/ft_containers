/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/24 05:30:52 by lemarabe         ###   ########.fr       */
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
        binTree *prev;
        Compare comp;
        Alloc   allocBT;
        std::pair<const Key, T> *value;

    public :

        //create blank list
        binTree() : root(this), left(this), right(this), prev(this),
        comp(Compare()), allocBT(Alloc()) {
                // std::cout << "Constructor called" << std::endl;
                this->value = allocBT.allocate(1);
            }

        // create new element with a pair of values
        binTree(std::pair<const Key, T> value) : root(NULL), left(NULL),
            right(NULL), prev(NULL), comp(Compare()), allocBT(Alloc()) {
            this->value = allocBT.allocate(1);
            allocBT.construct(this->value, value);
        }

        // create new element with only a key
        binTree(const Key key) : root(NULL), left(NULL), right(NULL), prev(NULL),
            comp(Compare()), allocBT(Alloc()) {
            std::pair<const Key, T> *newKey = new std::pair<const Key, T>(key, 42);
            allocBT.construct(this->value, *newKey);
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
            this->comp = ref.comp;
            this->allocBT = ref.allocBT;
            return (*this);
        }

        std::pair<const Key, T> &getValueRef() const { return (*this->value); }
        binTree                 *getRoot() const { return (this->root); }
        binTree                 *getPrev() const { return (this->prev); }
        binTree                 *getLeft() const { return (this->left); }
        binTree                 *getRight() const { return (this->right); }
        binTree                 *getFarLeft() const {  //a ne lancer que depuis root !
            binTree *farLeft = this->left;
            std::cout << farLeft <<std::cout;
            while (farLeft && farLeft->left != NULL)
                farLeft = farLeft->left;
            return (farLeft);
        }
        binTree                 *getFarRight() const {  //a ne lancer que depuis root !
            binTree *farRight = this->right;
            while (farRight && farRight->right != NULL)
                farRight = farRight->right;
            return (farRight);
        }

        binTree  *getBranch(const Key &to_find) const {
            binTree *elem = root;
            while (elem->value->first != to_find)
            {
                if (comp(elem->value->first, to_find))
                {
                    if (!elem->right)
                        break;
                    elem = elem->right;
                }
                else
                {
                    if (!elem->left)
                        break;
                    elem = elem->left;
                }
            }
            return (elem);
        }

        void insert(binTree *to_add) {
            to_add->root = this->root;
            binTree *elem = this->root;
            while (elem != to_add)
            {
                if (this->comp(elem->value->first, to_add->value->first))
                {
                    if (!elem->right)
                    {
                        elem->right = to_add;
                        to_add->prev = elem;
                    }
                    elem = elem->right;
                }
                else
                {
                    if (!elem->left)
                    {
                        elem->left = to_add;
                        to_add->prev = elem;
                    }
                    elem = elem->left;
                }
            }
        }

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

        typedef std::pair< const Key, T > *           pointer_type;
        typedef std::pair< const Key, T > &           reference_type;
        // typedef T *                          pointer_type;
        // typedef T &                          reference_type;
        typedef binTree<Key,T,Compare,Alloc>    element_type;
        typedef binTree<Key,T,Compare,Alloc> *  elem_ptr_type;
        // typedef ptrdiff_t                    difference_type;
        typedef Compare                         key_compare;
        //typedef ___                           value_compare;
        typedef Alloc                           allocator_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        bstIter() {}
        bstIter(elem_ptr_type p) : it(p) {}
        bstIter(const bstIter &ref) : it(ref.it) {}
        virtual ~bstIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        bstIter  &operator=(const bstIter &ref) { this->it = ref.it; return (*this); }
        bool        operator==(const bstIter &ref) const { return (this->it == ref.it); }
        bool        operator!=(const bstIter &ref) const { return (this->it != ref.it); }
        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (this->it->getValueRef()); }
        elem_ptr_type   operator->() const { return (this->it); }
        
        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        bstIter  &operator++() {
            if (this->it->getRight())
                this->it = this->it->getRight();
            else
                this->it = this->it->getPrev();
            return (*this);
        }
        bstIter  operator++(int) { bstIter tmp(*this); operator++(); return (tmp); }
        bstIter  &operator--() { this->it = this->it->getRight(); return (*this); }
        bstIter  operator--(int) { bstIter tmp(*this); operator--(); return (tmp); }

    protected :

        elem_ptr_type   it;
        // key_compare     comp;
};

template < class Key, class T, class Compare, class Alloc >
class cBSTIter : public virtual bstIter<Key,T,Compare,Alloc>
{
    public :
    
        typedef const std::pair< const Key, T > *   const_pointer_type;
        typedef const std::pair< const Key, T > &   const_reference_type;
        typedef binTree<Key,T,Compare,Alloc> *   elem_ptr_type;
        
        //----- CONSTRUCTORS & DESTRUCTORS -----//
        cBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        cBSTIter(elem_ptr_type p) : bstIter<Key,T,Compare,Alloc>(p) {}
        cBSTIter(const cBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.it) {}
        virtual ~cBSTIter() {}
        cBSTIter  &operator=(const cBSTIter &ref) { this->it = ref.it; return (*this); }
        //----- OPERATORS :  'dereference' -----//
        const_reference_type       operator*() const { return (this->it->getValueRef()); }
        const_pointer_type         operator->() const { return (this->it->getValuePtr()); }
};

template < class Key, class T, class Compare, class Alloc >
class rBSTIter : public virtual bstIter<Key,T,Compare,Alloc>
{
    public :
        
        typedef binTree<Key,T,Compare,Alloc> *   elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        rBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        rBSTIter(elem_ptr_type p) : bstIter<Key,T,Compare,Alloc>(p) {}
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

        typedef const std::pair< const Key, T > *   const_pointer_type;
        typedef const std::pair< const Key, T > &   const_reference_type;
        typedef binTree<Key,T,Compare,Alloc> *   elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        crBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        crBSTIter(elem_ptr_type p) : bstIter<Key,T,Compare,Alloc>(p) {}
        crBSTIter(const crBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.it) {}
        virtual ~crBSTIter() {}
        crBSTIter  &operator=(const crBSTIter &ref) { this->it = ref.it; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        crBSTIter  &operator++() { this->it = this->it->getRight(); return (*this); }
        crBSTIter  operator++(int) { crBSTIter tmp(*this); operator++(); return (tmp); }
        crBSTIter  &operator--() { this->it = this->it->getLeft(); return (*this);  }
        crBSTIter  operator--(int) { crBSTIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (this->it->getValueRef()); }
        const_pointer_type    operator->() const { return (this->it->getValuePtr()); }
};

#endif