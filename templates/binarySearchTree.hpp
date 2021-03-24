/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/24 19:23:07 by lemarabe         ###   ########.fr       */
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
        // pair_t *value;
        std::pair<const Key, T> *value;

    public :

        typedef std::pair<const Key, T> pair_t;
        //create element with no content
        binTree() : root(NULL), left(NULL), right(NULL), prev(NULL),
        comp(Compare()), allocBT(Alloc()) {
                // std::cout << "Default Constructor called" << std::endl;
                this->value = allocBT.allocate(1);
            }

        // create new element with a pair of values
        binTree(pair_t value) : root(NULL), left(NULL),
            right(NULL), prev(NULL), comp(Compare()), allocBT(Alloc()) {
            // std::cout << "Pair Constructor called" << std::endl;
            this->value = allocBT.allocate(1);
            allocBT.construct(this->value, value);
        }

        // create new element with only a key
        binTree(const Key key) : root(NULL), left(NULL), right(NULL), prev(NULL),
            comp(Compare()), allocBT(Alloc()) {
            // std::cout << "Key Constructor called" << std::endl;
            // pair_t *newKey = new pair_t(key, 42);
            this->value = allocBT.allocate(1);
            allocBT.construct(this->value, *(new pair_t(key, 42)));
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
        void setValue(pair_t value) { allocBT.construct(this->value, value); }
        void setValue(const Key key) {
            pair_t *newKey = new pair_t(key, 42);
            allocBT.construct(this->value, *newKey);
        }
        binTree                 *getRoot() const { return (this->root); }
        void setRootSingle(binTree *newRoot) { this->root = newRoot; }
        void setRootAll(binTree *newRoot) {
            binTree *elem = getFarLeft();
            while (elem != getFarRight())
                elem->root = newRoot;
            elem->root = newRoot;
        }
        binTree                 *getPrev() const { return (this->prev); }
        binTree                 *getLeft() const { return (this->left); }
        binTree                 *getRight() const { return (this->right); }
        binTree                 *getFarLeft() const {
            binTree *farLeft = root;
            while (farLeft && farLeft->left)
                farLeft = farLeft->left;
            return (farLeft);
        }
        binTree                 *getFarRight() const {
            binTree *farRight = root;
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

        void extractElement() {
            if (this->left)
            {
                this->left->prev = this->prev;
                this->prev->right = this->left;
                if (this->right)
                {
                    this->right->prev = this->left;
                    this->left->right = this->right;
                }
                if (this == root)
                    setRootAll(this->left);
            }
            else if (this->right)
            {
                this->left->prev = this->prev;
                this->prev->right = this->left;
                if (this->right)
                {
                    this->right->prev = this->left;
                    this->left->right = this->right;
                }
                if (this == root)
                    setRootAll(this->right);
            }
        }
        void deleteElement() {
            this->extractElement();
            delete this;
        }
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
        cBSTIter(elem_ptr_type p) : bstIter<Key,T,Compare,Alloc>(p) { }
        cBSTIter(const cBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.it) {}
        virtual ~cBSTIter() {}
        cBSTIter  &operator=(const cBSTIter &ref) { this->it = ref.it; return (*this); }
        //----- OPERATORS :  'dereference' -----//
        const_reference_type       operator*() const { return (this->it->getValueRef()); }
        elem_ptr_type         operator->() const { return (this->it); }
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
        elem_ptr_type         operator->() const { return (this->it); }
};

#endif