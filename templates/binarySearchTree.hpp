/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:07:17 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/07 15:42:16 by lemarabe         ###   ########.fr       */
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
    public :

        typedef std::pair<const Key, T> pair_t;
        
        // create root element with no content
        binTree() : _pair(NULL), _root(this), _left(NULL), _right(NULL), _end(this),
            _comp(Compare()), _allocBT(Alloc())
        {
            _pair = _allocBT.allocate(1);
            _allocBT.construct(_pair, pair_t(Key(), T()));
        }

        // create new element with a pair of values
        binTree(const pair_t &pair, binTree *root) : _root(root), _left(NULL),
            _right(NULL), _end(root->_end), _comp(Compare()), _allocBT(Alloc())
        {
            _pair = _allocBT.allocate(1);
            _allocBT.construct(_pair, pair);
        }

        // create temporary element with same content
        binTree(const binTree &ref) : _root(NULL), _left(NULL), _right(NULL), _end(NULL),
            _comp(Compare()), _allocBT(Alloc())
        { 
            _pair = _allocBT.allocate(1);
            _allocBT.construct(_pair, *ref._pair);
        }
        
        ~binTree() {
            _allocBT.destroy(_pair);
            _allocBT.deallocate(_pair, 1);
        }
        
        binTree &operator=(const binTree &ref) {
            _allocBT.destroy(_pair);
            if (ref._pair)
                _allocBT.construct(_pair, *ref._pair);
            else
            {
                _allocBT.destroy(_pair);
                _allocBT.deallocate(_pair, 1);
                _pair = NULL;
            }
            return (*this);
        }

        binTree     *getRoot() const { return (this->_root); }
        pair_t      *getPair() const { return (this->_pair); }
        const Key   &getKey() const { return (this->_pair->first); }
        T           &getValue() const { return (this->_pair->second); }
        binTree     *getEnd() const { return (this->_end); }
        void        setEnd(binTree *end) { this->_end = end; }
        
        binTree     *getMostRight(binTree *node) const {
            if (node && node->_right)
                return (getMostRight(node->_right));
            return (node);
        }
        binTree     *getMostLeft(binTree *node) const {
            if (node && node->_left)
                return (getMostLeft(node->_left));
            return (node);
        }
        binTree     *getParent() const {
            binTree *parent = _root;
            while (parent && parent->_pair && parent->_left != this && parent->_right != this)
            {
                if (_comp(this->getKey(), parent->getKey()) && parent->_left)
                    parent = parent->_left;
                else if (_comp(parent->getKey(), this->getKey()) && parent->_right)
                    parent = parent->_right;
                else
                    break;
            }
            return (parent);
        }
        bool couldBeParent(const Key &key) const {
            if (!_pair)
                return (true);
            if (_comp(this->getKey(), key) && !this->_left)
                return (true);
            if (_comp(key, this->getKey()) && !this->_right)
                return (true);
            return (false);
        }

        binTree  *getNode(const Key &to_find, binTree *node) const {
            if (!node || !node->_pair)
                return (NULL);
            if (node->getKey() == to_find)
                return (node);
            if (_comp(to_find, node->getKey()))
                return (getNode(to_find, node->_left));
            else
                return (getNode(to_find, node->_right));
        }

        /////////////////////
        //    ITERATION    //
        /////////////////////

        binTree *getNextIter(const Key &key) const {
            if (!_root->_pair || this == getMostRight(_root))
                return (_end);
            if (this == _root || (this->_right && (_comp(key, this->getKey()) || key == this->getKey()) ) )
                return (getMostLeft(this->_right));
            binTree *parent = this->getParent();
            if (_comp(key, parent->getKey()) || parent == _root)
                return (parent);
            return (parent->getNextIter(key));
        }
        
        binTree *getPrevIter(const Key &key) const {
            if (this == _end)
                return (getMostRight(_root));
            if (!_root->_pair || this == getMostLeft(_root))
                return (_end);
            if (this == _root || (this->_left && (_comp(this->getKey(), key) || key == this->getKey()) ) )
                return (getMostRight(this->_left));
            binTree *parent = this->getParent();
            if (_comp(parent->getKey(), key) || parent == _root)
                return (parent);
            return (parent->getPrevIter(key));
        }

        /////////////////////
        //    INSERTION    //
        /////////////////////

        std::pair<binTree*,bool> insertElement(binTree *node, const pair_t &pair, size_t mapSize) {
            if (_root == _end)
            {
                _allocBT.destroy(_pair);
                _allocBT.construct(_pair, pair);
                _end = new binTree(pair_t(Key(), T()), _root);
                _end->_end = _root->_end;
                return (std::pair<binTree*,bool>(_root, true));
            }
            if (!node)
            {
                node = new binTree(pair, _root);
                node->setChildInParent(node, pair.first);
                return (std::pair<binTree*,bool>(node, true));
            }
            if (node->getKey() == pair.first)
            {
                node->_pair->second = pair.second;
                return (std::pair<binTree*,bool>(node, false));
            }
            if (_comp(pair.first, node->getKey()))
                return (insertElement(node->_left, pair, mapSize));
            else
                return (insertElement(node->_right, pair, mapSize));
        }

        void setChildInParent(binTree *child, const Key &key) {
            binTree *parent = this->getParent();
            if (_comp(parent->getKey(), key))
                parent->_right = child;
            else if (_comp(key, parent->getKey()))
                parent->_left = child;
        }

        /////////////////////
        //     DELETION    //
        /////////////////////

        void replaceInParent(binTree *newChild) {
            binTree *parent = this->getParent();
            if (parent)
            {
                if (this == parent->_left)
                    parent->_left = newChild;
                else if (this == parent->_right)
                    parent->_right = newChild;
                delete this;
            }
        }

        void deleteElement() {
            if (this == _root)
                return (deleteRoot());
            if (this->_left && this->_right)
            {
                binTree *successor = getMostLeft(this->_right);
                binTree tmp = *successor;
                successor->deleteElement();
                *this = tmp;
            }
            else if (this->_left)
                this->replaceInParent(this->_left);
            else if (this->_right)
                this->replaceInParent(this->_right);
            else
                this->replaceInParent(NULL);
        }

        void deleteRoot() {
            binTree *successor = NULL;
            if (this->_right)
                successor = getMostLeft(this->_right);
            else if (this->_left)
                successor = getMostRight(this->_left);
            else
            {
                _allocBT.destroy(this->_pair);
                binTree *tmp = _end;
                _end = _root;
                delete tmp;
            }
            if (successor)
            {
                binTree tmp = *successor;
                successor->deleteElement();
                *this = tmp;
            }
        }

        void deleteKey(const Key &key) {
            binTree *to_del = getNode(key, _root);
            if (to_del)
                to_del->deleteElement();
        }

    private:

        pair_t  *_pair;
        binTree *_root;
        binTree *_left;
        binTree *_right;
        binTree *_end;
        Compare _comp;
        Alloc   _allocBT;
};

template < class Key, class T, class Compare, class Alloc >
class bstIter
{
    public :

        typedef std::pair< const Key, T > *     pointer_type;
        typedef std::pair< const Key, T > &     reference_type;
        typedef binTree<Key,T,Compare,Alloc> *  elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        bstIter() : node(NULL) {}
        bstIter(elem_ptr_type node) : node(node) { }
        bstIter(const bstIter &ref) : node(ref.node) {}
        virtual ~bstIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        bstIter     &operator=(const bstIter &ref) { this->node = ref.node; return (*this); }
        bool        operator==(const bstIter &ref) const { return (this->node == ref.node); }
        bool        operator!=(const bstIter &ref) const { return (this->node != ref.node); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        bstIter  &operator++() { this->node = this->node->getNextIter(operator*().first); return (*this); }
        bstIter  operator++(int) { bstIter tmp(*this); operator++(); return (tmp); }
        bstIter  &operator--() { this->node = this->node->getPrevIter(operator*().first); return (*this); }
        bstIter  operator--(int) { bstIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (*this->node->getPair()); }
        pointer_type    operator->() const { return (this->node->getPair()); }
        elem_ptr_type   getNode() const { return (this->node); }

    protected :

        elem_ptr_type   node;
};

template < class Key, class T, class Compare, class Alloc >
class cBSTIter : public virtual bstIter<Key,T,Compare,Alloc>
{
    public :
    
        typedef const std::pair< const Key, T > *   const_pointer_type;
        typedef const std::pair< const Key, T > &   const_reference_type;
        typedef binTree<Key,T,Compare,Alloc> *      elem_ptr_type;
        
        //----- CONSTRUCTORS & DESTRUCTORS -----//
        cBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        cBSTIter(elem_ptr_type node) : bstIter<Key,T,Compare,Alloc>(node) { }
        cBSTIter(const cBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.node) {}
        virtual ~cBSTIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        cBSTIter  &operator=(const cBSTIter &ref) { this->node = ref.node; return (*this); }
        bool        operator==(const cBSTIter &ref) const { return (this->node == ref.node); }
        bool        operator!=(const cBSTIter &ref) const { return (this->node != ref.node); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        cBSTIter  &operator++() { this->node = this->node->getNextIter(operator*().first); return (*this); }
        cBSTIter  operator++(int) { cBSTIter tmp(*this); operator++(); return (tmp); }
        cBSTIter  &operator--() { this->node = this->node->getPrevIter(operator*().first); return (*this); }
        cBSTIter  operator--(int) { cBSTIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type    operator*() const { return (*this->node->getPair()); }
        const_pointer_type      operator->() const { return (this->node->getPair()); }
        elem_ptr_type           getNode() const { return (this->node); }
};

template < class Key, class T, class Compare, class Alloc >
class rBSTIter : public virtual bstIter<Key,T,Compare,Alloc>
{
    public :

        typedef std::pair< const Key, T > *     pointer_type;
        typedef std::pair< const Key, T > &     reference_type;
        typedef binTree<Key,T,Compare,Alloc> *   elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        rBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        rBSTIter(elem_ptr_type node) : bstIter<Key,T,Compare,Alloc>(node) {}
        rBSTIter(const rBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.node) {}
        virtual ~rBSTIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        rBSTIter  &operator=(const rBSTIter &ref) { this->node = ref.node; return (*this); }
        bool        operator==(const rBSTIter &ref) const { return (this->node == ref.node); }
        bool        operator!=(const rBSTIter &ref) const { return (this->node != ref.node); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        rBSTIter  &operator++() { this->node = this->node->getPrevIter(operator*().first); return (*this); }
        rBSTIter  operator++(int) { rBSTIter tmp(*this); operator++(); return (tmp); }
        rBSTIter  &operator--() { this->node = this->node->getNextIter(operator*().first); return (*this); }
        rBSTIter  operator--(int) { rBSTIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (*this->node->getPair()); }
        pointer_type    operator->() const { return (this->node->getPair()); }
        elem_ptr_type   getNode() const { return (this->node); }
};

template < class Key, class T, class Compare, class Alloc >
class crBSTIter : public virtual cBSTIter<Key,T,Compare,Alloc>, public virtual rBSTIter<Key,T,Compare,Alloc>
{
    public :

        typedef const std::pair< const Key, T > *   const_pointer_type;
        typedef const std::pair< const Key, T > &   const_reference_type;
        typedef binTree<Key,T,Compare,Alloc> *      elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        crBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        crBSTIter(elem_ptr_type node) : bstIter<Key,T,Compare,Alloc>(node) {}
        crBSTIter(const crBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.node) {}
        virtual ~crBSTIter() {}

        //----- OPERATORS : 'assignation' 'equality' 'inequality' -----//
        crBSTIter  &operator=(const crBSTIter &ref) { this->node = ref.node; return (*this); }
        bool        operator==(const crBSTIter &ref) const { return (this->node == ref.node); }
        bool        operator!=(const crBSTIter &ref) const { return (this->node != ref.node); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        crBSTIter  &operator++() { this->node = this->node->getPrevIter(operator*().first); return (*this); }
        crBSTIter  operator++(int) { crBSTIter tmp(*this); operator++(); return (tmp); }
        crBSTIter  &operator--() { this->node = this->node->getNextIter(operator*().first); return (*this); }
        crBSTIter  operator--(int) { crBSTIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type    operator*() const { return (*this->node->getPair()); }
        const_pointer_type      operator->() const { return (this->node->getPair()); }
        elem_ptr_type           getNode() const { return (this->node); }
};

template < class Key, class T, class Compare, class Alloc >
std::ostream &operator<<(std::ostream &out, bstIter<Key,T,Compare,Alloc> const &iter) {
    std::pair<const Key, T> pair = *iter;
    out << "\'" << pair.first << "-" << pair.second << "\' ";
    return (out);
}
template < class Key, class T, class Compare, class Alloc >
std::ostream &operator<<(std::ostream &out, rBSTIter<Key,T,Compare,Alloc> const &iter) {
    std::pair<const Key, T> pair = *iter;
    out << "\'" << pair.first << "-" << pair.second << "\' ";
    return (out);
}
template < class Key, class T, class Compare, class Alloc >
std::ostream &operator<<(std::ostream &out, cBSTIter<Key,T,Compare,Alloc> const &iter) {
    std::pair<const Key, T> pair = *iter;
    out << "\'" << pair.first << "-" << pair.second << "\' ";
    return (out);
}
template < class Key, class T, class Compare, class Alloc >
std::ostream &operator<<(std::ostream &out, crBSTIter<Key,T,Compare,Alloc> const &iter) {
    std::pair<const Key, T> pair = *iter;
    out << "\'" << pair.first << "-" << pair.second << "\' ";
    return (out);
}

#endif