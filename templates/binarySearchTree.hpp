/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:33:33 by lemarabe          #+#    #+#             */
/*   Updated: 2021/04/07 03:51:47 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_H
# define BINARY_SEARCH_TREE_H

# include "../containers/list.hpp"
# include <memory>
# include <cstddef>

# include <iostream>

template < class Key, class T, class Compare, class Alloc >
class binTree
{
    private:

        std::pair<const Key, T> *value;
        binTree *root;
        binTree *left;
        binTree *right;
        Compare comp;
        Alloc   allocBT;
        // pair_t *value;

    public :

        typedef std::pair<const Key, T> pair_t;
        
        // create element with no content
        binTree() : root(NULL), left(NULL), right(NULL),
        comp(Compare()), allocBT(Alloc()) {
                // std::cout << "Default Constructor called -> " << this << std::endl;
                this->value = allocBT.allocate(1);
            }

        // create new element with a pair of values
        binTree(const Key &key, T &val, binTree *root) : root(root), left(NULL),
            right(NULL), comp(Compare()), allocBT(Alloc()) {
            // std::cout << "Pair Constructor called -> " << this <<" ~ key=" << key << ",value=" << val << std::endl;
            this->value = allocBT.allocate(1);
            allocBT.construct(this->value, pair_t(key, val));
        }

        // create new element with only a key
        binTree(const Key key, binTree *root) : root(root), left(NULL), right(NULL),
            comp(Compare()), allocBT(Alloc()) {
            // std::cout << "Key Constructor called -> " << this << " ~ key=" << key << std::endl;
            this->value = allocBT.allocate(1);
            allocBT.construct(this->value, pair_t(key, 42));
        }

        ~binTree() {
            allocBT.deallocate(this->value, 1);
        }
        
        binTree(const binTree &ref) { *this = ref; }
        
        binTree &operator=(const binTree &ref) {
            std::cout << "/!\\ WARNING : BST operator= called -> undefined behavior for now..." << std::endl;
            allocBT.destroy(this->value);
            allocBT.construct(this->value, *ref.value);
            // *this->value = ref.value;
            // this->root = ref.root;
            this->left = ref.left;
            this->right = ref.right;
            // this->comp = ref.comp;
            // this->allocBT = ref.allocBT;
            return (*this);
        }

        binTree     *getRoot() const { return (this->root); }
        const Key   &getKey() const { return (this->value->first); }
        T           &getValue() const { return (this->value->second); }
        pair_t      *getPair() const { return (this->value); }
        binTree     *getLeft() const { return (this->left); }
        binTree     *getRight() const { return (this->right); }
        
        binTree     *getMostRight(binTree *node) const {
            if (node && node->right)
                return (getMostRight(node->right));
            return (node);
        }
        binTree     *getMostLeft(binTree *node) const {
            if (node && node->left)
                return (getMostLeft(node->left));
            return (node);
        }
        binTree     *getParent() const {
            binTree *parent = root;
            // std::cout << "GET PARENT de " << this << " (key = " << this->getKey();
            while (parent && (parent->left || parent->right) && parent->left != this && parent->right != this)
            {
                if (comp(this->getKey(), parent->getKey()) && parent->left)
                    parent = parent->left;
                else if (comp(parent->getKey(), this->getKey()) && parent->right)
                    parent = parent->right;
                else
                    break;
            }
            // std::cout << ") : parent = " << parent << " // key = " << parent->getKey() << std::endl;
            return (parent);
        }

        binTree  *getNode(const Key &to_find, binTree *node) const {
            // std::cout << "GET NODE : node = " << node << " // key = " << node->getKey() << std::endl;
            if (!node || node->getKey() == to_find)
                return (node);
            if (comp(to_find, node->getKey()))
                return (getNode(to_find, node->left));
            else
                return (getNode(to_find, node->right));
        }

        binTree *getNextIter(const Key &key) const {
            std::cout << "/ this = " << this->getKey();
            if (this == root || (this->right && (comp(this->getKey(), key) || key == this->getKey()) ) )
                return (getMostLeft(this->right));
            binTree *parent = this->getParent();
            if (comp(key, parent->getKey()) || parent == root)// && comp(parent->getKey(), this->getKey())) )
                return (parent);
            return (parent->getNextIter(key));
            // if (comp(key, root->getKey())) // left side of the tree
            // {
            //     if (parent->right)
            //         return (root);
            //     // return (parent->getNextIter());
            //     // while (parent != root && comp(parent->getKey(), this->getKey()))
            //     //     parent = parent->getParent();
            // }
            // else if (comp(root->getKey(), key))     // right side of the tree
            // {
            //     if (parent == root)
            //         return (this->right);
            //     return (parent->getNextIter());
            // }
            // else
            //     return (root->right);
            
            // while (parent != root && comp(parent->getKey(), this->getKey()))
            //     parent = parent->getParent();
            //     return (parent);
            // if (parent->right)
            //     return (getMostLeft(parent->right));
            // return (parent->getParent()); // attention a pas tourner en boucle si on est root
        }

        std::pair<binTree*,bool> insert(binTree *node, const Key &key, T &val) {
            if (!root)
            {
                allocBT.construct(this->value, pair_t(key, val));
                root = this;
                return (std::pair<binTree*,bool>(root, true));
            }
            // std::cout << "node = " << node << std::endl;
            if (!node)
            {
                node = new binTree(key, val, root);
                node->setChildInParent(node, key);
                // std::cout << "root du new elemnt = " << node->root << std::endl;
                return (std::pair<binTree*,bool>(node, true));
            }
            if (key == node->getKey())
            {
                node->value->second = val;
                return (std::pair<binTree*,bool>(node, false));
            }
            if (comp(key, node->getKey()))
                return (insert(node->left, key, val));
            else
                return (insert(node->right, key, val));
        }

        std::pair<binTree*,bool> insert(binTree *node, const Key &key) {
            if (!root)
            {
                allocBT.construct(this->value, pair_t(key, 42));
                root = this;
                return (std::pair<binTree*,bool>(root, true));
            }
            if (!node)
            {
                node = new binTree(key, root);
                node->setChildInParent(node, key);
                // node->root = this;
                return (std::pair<binTree*,bool>(node, true));
            }
            if (comp(key, node->getKey()))
                return (insert(node->left, key));
            else
                return (insert(node->right, key));
        }

        void setChildInParent(binTree *child, const Key &key) {
            binTree *parent = this->getParent();
            // std::cout << "SET CHILD IN PARENT = ";
            if (comp(parent->getKey(), key))
            {
                parent->right = child;
                // std::cout << "parent (" << parent << ") -> right = " << child << std::endl;
            }
            else
            {
                parent->left = child;
                // std::cout << "parent (" << parent << ") -> left = " << child << std::endl;
            }
        }

        void replaceInParent(binTree *newChild) {
            binTree *parent = this->getParent();
            if (parent)
            {
                if (this == parent->left)
                    parent->left = newChild;
                else
                    parent->right = newChild;
            }
        }

        void deleteFromTree(const Key &to_del) {
            if (comp(to_del, this->getKey()))
            {
                this->left->deleteFromTree(to_del);
                return;
            }
            if (comp(this->getKey(), to_del))
            {
                this->right->deleteFromTree(to_del);
                return;
            }
            // Delete the key here
            if (this->left && this->right)  // If both children are present
            {
                binTree *successor = getMostLeft(this->right);
                // pair_t newContent(successor->getKey(), this->value->second);
                *this = *successor;
                // this->getKey() = successor->getKey();
                successor->deleteFromTree(successor->getKey());
            }
            else if (this->left)  // If the node has only a *left* child
                this->replaceInParent(this->left);
            else if (this->right) // If the node has only a *right* child
                this->replaceInParent(this->right);
            else
                this->replaceInParent(NULL);  // This node has no children
            delete this;
        }

};

template < class Key, class T, class Compare, class Alloc >
class bstIter
{
    public :

        typedef std::pair< const Key, T >       value_type;
        typedef std::pair< const Key, T > *     pointer_type;
        typedef std::pair< const Key, T > &     reference_type;
        typedef binTree<Key,T,Compare,Alloc>    element_type;
        typedef binTree<Key,T,Compare,Alloc> *  elem_ptr_type;
        // typedef ptrdiff_t                    difference_type;
        typedef Compare                         key_compare;
        //typedef ___                           value_compare;
        typedef Alloc                           allocator_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        bstIter() : node(NULL), tree() {}
        bstIter(elem_ptr_type node) : node(node), tree() {
            // size_t nbLevels = 0;
            
            // elem_ptr_type curr = node->getMostLeft(node->getRoot());
            // elem_ptr_type end = node->getMostRight(node->getRoot());
            // while (curr != end)
            // {
            //     tree.push_back(curr);
            //     elem_ptr_type parent = curr->getParent();
            //     if (parent != curr)
            //     {
            //         tree.push_back(parent);
            //         curr = curr->getMostLeft(parent->getRight());
            //     }
            // }
            // tree.push_back(end);
            
            // for (elem_ptr_type curr = node->getRoot(); curr != NULL; curr = curr->getLeft())
            //     tree.push_front(curr);
            // for (typename ft::List<elem_ptr_type>::iterator it = tree.begin(); it != tree.end(); it++)
            // {
            //     typename ft::List<elem_ptr_type>::iterator insert_it(it);
            //     elem_ptr_type prev = *it; 
            //     for (elem_ptr_type curr = prev->getRight(); curr != NULL; curr = curr->getLeft())
            //     // for (elem_ptr_type curr = *it->getRight(); curr != NULL; curr = curr->getLeft())
            //         insert_it = tree.insert(++insert_it, curr) ;
            //     // std::cout << "insert it = " << *insert_it << std::endl;
            // }
        }
        bstIter(const bstIter &ref) : node(ref.node), tree(ref.tree) {}
        virtual ~bstIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        bstIter  &operator=(const bstIter &ref) {
            this->node = ref.node;
            this->tree = ref.tree;
            return (*this); }
        bool        operator==(const bstIter &ref) const { return (this->node == ref.node); }
        bool        operator!=(const bstIter &ref) const { return (this->node != ref.node); }
        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (*this->node->getPair()); }
        elem_ptr_type   operator->() const { return (this->node); }
        elem_ptr_type   getNodeM() const { return (this->node); }
        
        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        bstIter  &operator++() {
            // std::cout << "tree for incrementation " << tree;
            // std::cout << "node avant increment " << node << std::endl;

            this->node = this->node->getNextIter(operator*().first); //return (*this);
            // typename ft::List<elem_ptr_type>::iterator it = tree.begin(); 
            // while (*it != node)
            //     it++;
            // node = *(++it);
            // std::cout << "node apres increment " << node << std::endl;
            return (*this);
        }
        bstIter  operator++(int) { bstIter tmp(*this); operator++(); return (tmp); }
        bstIter  &operator--() {
            return (*this); }
        bstIter  operator--(int) { bstIter tmp(*this); operator--(); return (tmp); }

    protected :

        elem_ptr_type   node;
        ft::List<elem_ptr_type>    tree;
        // ft::List<elem_ptr_type>    history;
        // size_t          level;
        // size_t   prevLvl;
        // pointer_type                it;
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
        cBSTIter(elem_ptr_type node) : bstIter<Key,T,Compare,Alloc>(node) { }
        cBSTIter(const cBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.node) {}
        virtual ~cBSTIter() {}
        cBSTIter  &operator=(const cBSTIter &ref) { this->node = ref.node; return (*this); }
        //----- OPERATORS :  'dereference' -----//
        const_reference_type  operator*() const { return (*this->node->getPair()); }
        elem_ptr_type           operator->() const { return (this->node); }
};

template < class Key, class T, class Compare, class Alloc >
class rBSTIter : public virtual bstIter<Key,T,Compare,Alloc>
{
    public :
        
        typedef binTree<Key,T,Compare,Alloc> *   elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        rBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        rBSTIter(elem_ptr_type node) : bstIter<Key,T,Compare,Alloc>(node) {}
        rBSTIter(const rBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.node) {}
        virtual ~rBSTIter() {}
        rBSTIter  &operator=(const rBSTIter &ref) { this->node = ref.node; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        rBSTIter  &operator++() { this->node = this->node->getRight(); return (*this); }
        rBSTIter  operator++(int) { rBSTIter tmp(*this); operator++(); return (tmp); }
        rBSTIter  &operator--() { this->node = this->node->getLeft(); return (*this); }
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
        crBSTIter(elem_ptr_type node) : bstIter<Key,T,Compare,Alloc>(node) {}
        crBSTIter(const crBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.node) {}
        virtual ~crBSTIter() {}
        crBSTIter  &operator=(const crBSTIter &ref) { this->node = ref.node; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        crBSTIter  &operator++() { this->node = this->node->getRight(); return (*this); }
        crBSTIter  operator++(int) { crBSTIter tmp(*this); operator++(); return (tmp); }
        crBSTIter  &operator--() { this->node = this->node->getLeft(); return (*this);  }
        crBSTIter  operator--(int) { crBSTIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type    operator*() const { return (*this->it); }
        elem_ptr_type           operator->() const { return (this->node); }
};

#endif