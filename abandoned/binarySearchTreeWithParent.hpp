#ifndef BINARY_SEARCH_TREE_H
# define BINARY_SEARCH_TREE_H

# include "../containers/list.hpp"
# include <memory>
# include <cstddef>
# include <cstring>

# include <iostream>

template < class Key, class T, class Compare, class Alloc >
class binTree
{
    private:

        std::pair<const Key, T> *_pair;
        binTree *_root;
        binTree *_left;
        binTree *_right;
        binTree *_parent;
        Compare _comp;
        Alloc   _allocBT;
        // pair_t *_pair;

    public :

        typedef std::pair<const Key, T> pair_t;
        
        // create element with no content
        binTree() : _pair(NULL), _root(this), _left(NULL), _right(new binTree), _parent(NULL)
            _comp(Compare()), _allocBT(Alloc())
        {
            // std::cout << "Default Constructor called -> " << this << std::endl;
            _right->_root = this;
            _right->parent = this;
        }

        // create new element with a pair of values
        binTree(pair_t pair, binTree *parent) : _root(parent->_root), _left(NULL),
            _right(NULL), _parent(parent), _comp(Compare()), _allocBT(Alloc())
        {
            // std::cout << "Pair Constructor called -> " << this <<" ~ key=" << key << ",_pair=" << val << std::endl;
            _pair = _allocBT.allocate(1);
            _allocBT.construct(this->_pair, pair);
            if (_comp(_parent->getKey(), _pair->first))
                _parent->_right = this;
            else
                _parent->_left = this;
            // if (!_root)
            //     _root = this;
        }

        // create new element as a copy of an other
        binTree(const binTree &ref) : _root(this), _left(NULL), _right(new binTree), _parent(NULL),
            _comp(Compare()), _allocBT(Alloc())
        { 
            std::cout << "[BST] Copy constructor called" << std::endl;
            _pair = _allocBT.allocate(1);
            _allocBT.construct(_pair, *ref._pair);
            _right->_root = this;
            _right->parent = this;
        }
        
        ~binTree() {
            _allocBT.destroy(_pair);
            _allocBT.deallocate(_pair, 1);
        }
        
        binTree &operator=(const binTree &ref) {
            // std::cout << "/!\\ WARNING : BST operator= called -> undefined behavior for now..." << std::endl;
            _allocBT.destroy(_pair);
            _allocBT.construct(_pair, *ref._pair);
            // if (ref._pair)
            //     _allocBT.construct(_pair, *ref._pair);
            // else
            // {
            //     _allocBT.deallocate(_pair, 1);
            //     _pair = NULL;
            // }
            // this->_root = ref._root;
            // this->_left = ref._left;
            // this->_right = ref._right;
            return (*this);
        }

        binTree     *getRoot() const { return (this->_root); }
        const Key   &getKey() const { return (this->_pair->first); }
        T           &getValue() const { return (this->_pair->second); }
        pair_t      *getPair() const { return (this->_pair); }
        binTree     *getLeft() const { return (this->_left); }
        binTree     *getRight() const { return (this->_right); }
        void        setRoot(binTree *newRoot) { this->_root = newRoot; }
        
        binTree     *getMostLeft(binTree *node) const {
            if (node && node->_left)
                return (getMostLeft(node->_left));
            return (node);
        }
        binTree     *getMostRight(binTree *node) const {
            if (node && node->_right && node->_pair)
                return (getMostRight(node->_right));
            return (node);
        }
        binTree *getEnd() const { return (getMostRight(_root)->_right); }
       
        // bool couldBeParent(const Key &key) const {
        //     if (_comp(this->getKey(), key) && !this->_left)
        //         return (true);
        //     if (_comp(key, this->getKey()) && !this->_right)
        //         return (true);
        //     return (false);
        // }
        binTree     *getParent(const Key &key) const {  //optimisée pour chercher emplacement vide uniquement
            binTree *parent = _root;
            while (parent && (parent->_left || parent->_right))
            {
                if (parent->_left && _comp(key, parent->getKey()))
                    parent = parent->_left;
                else if (parent->_right && _comp(parent->getKey(), key))
                    parent = parent->_right;
                else
                    break;
            }
            return (parent);
        }
        binTree  *getNode(const Key &to_find, binTree *node) const {
            if (!node || node->getKey() == to_find)
                return (node);
            if (_comp(to_find, node->getKey()))
                return (getNode(to_find, node->_left));
            else
                return (getNode(to_find, node->_right));
        }

            // if (_comp(key, _root->getKey())) // _left side of the tree
            // else if (_comp(root->getKey(), key))     // _right side of the tree
            
        binTree *getNextIter(const Key &key) const {
            if (this == _root || (this->_right && (_comp(key, this->getKey()) || key == this->getKey()) ) )
                return (getMostLeft(this->_right));
            if (_comp(key, _parent->getKey()) || _parent == _root)
                return (_parent);
            return (_parent->getNextIter(key));
        }
        binTree *getNextReverseIter(const Key &key) const {
            if (this == getMostLeft(_root))
                return (getEnd());
            if (this == _root || (this->_left && (_comp(this->getKey(), key) || key == this->getKey()) ) )
                return (getMostRight(this->_left));
            if (_comp(_parent->getKey(), key) || _parent == _root)
                return (_parent);
            return (_parent->getPrevIter(key));
        }
        binTree *getPrevIter(const Key &key) const {
            if (this == _root || (this->_left && (_comp(this->getKey(), key) || key == this->getKey()) ) )
                return (getMostRight(this->_left));
            if (_comp(_parent->getKey(), key) || _parent == _root)
                return (_parent);
            return (_parent->getPrevIter(key));
        }
        binTree *getPrevReverseIter(const Key &key) const {
            if (this == _root || (this->_right && (_comp(key, this->getKey()) || key == this->getKey()) ) )
                return (getMostLeft(this->_right));
            if (_comp(key, _parent->getKey()) || _parent == _root)
                return (_parent);
            return (_parent->getNextIter(key));
        }
        std::pair<binTree*,bool> insertElement(binTree *node, const pair_t &pair) {
            static binTree *parent = node;
            if (!_root->_pair)
            {
                _pair = _allocBT.allocate(1);
                _allocBT.construct(_pair, pair);
                return (std::pair<binTree*,bool>(_root, true));
            }
            if (!node)
            {
                node = new binTree(pair, getParent(pair.first));
                // node->setChildInParent(node, pair.first);
                return (std::pair<binTree*,bool>(node, true));
            }
            if (node->getKey() == pair.first)
            {
                node->_pair->second = pair.second;
                return (std::pair<binTree*,bool>(node, false));
            }
            parent = node;
            if (_comp(pair.first, node->getKey()))
                return (insertElement(node->_left, pair));
            else
                return (insertElement(node->_right, pair));
        }

        // void setChildInParent(binTree *child, const Key &key) {
        //     binTree *parent = this->getParent();
        //     if (parent && parent != this)
        //     {
        //         if (_comp(parent->getKey(), key))
        //             parent->_right = child;
        //         else
        //             parent->_left = child;
        //     }
        // }

        void replaceInParent(binTree *newChild) {
            if (this == _root)
            {
                if (newChild)
                {
                    *this = *newChild;
                    newChild->deleteElement();
                }
                else
                {
                    _allocBT.destroy(this->_pair);
                    this->_pair = NULL;
                }
            }
            else
            {
                if (this == _parent->_left)
                    _parent->_left = newChild;
                else if (this == _parent->_right)
                    _parent->_right = newChild;
            }
        }

        void deleteElement() {
            if (this->_left && this->_right)  // If both children are present
            {
                binTree *successor = getMostLeft(this->_right);
                *this = *successor;
                if (this == _root)
                    *_root = *successor;
                successor->deleteElement();
                // successor->deleteKey(successor->getKey());
            }
            else if (this->_left)  // If the node has only a *_left* child
                this->replaceInParent(this->_left);
            else if (this->_right) // If the node has only a *_right* child
                this->replaceInParent(this->_right);
            else                    // This node has no children
                this->replaceInParent(NULL);
            if (this != _root)
                delete this;
            // else
            // {
            //     _allocBT.destroy(this->_pair);
            //     this->_pair = NULL;
            // }
            //      _root = getMostLeft(this->_right);

        }

        void deleteKey(const Key &key) {
            binTree *to_del = getNode(key, _root);
            if (to_del)
                to_del->deleteElement();
        }

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
        bstIter  &operator=(const bstIter &ref) { this->node = ref.node; return (*this); }
        bool        operator==(const bstIter &ref) const { return (this->node == ref.node); }
        bool        operator!=(const bstIter &ref) const { return (this->node != ref.node); }
        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (*this->node->getPair()); }
        elem_ptr_type   operator->() const { return (this->node); }
        
        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        bstIter  &operator++() { this->node = this->node->getNextIter(operator*().first); return (*this); }
        bstIter  operator++(int) { bstIter tmp(*this); operator++(); return (tmp); }
        bstIter  &operator--() { 
            if (!this->node->getPair())
                this->node = this->node->getMostRight(this->node->getRoot());
            else
                this->node = this->node->getPrevIter(operator*().first);
            return (*this); }
        bstIter  operator--(int) { bstIter tmp(*this); operator--(); return (tmp); }

    protected :

        elem_ptr_type   node;
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
        
        typedef std::pair< const Key, T > &     reference_type;
        typedef binTree<Key,T,Compare,Alloc> *   elem_ptr_type;

        //----- CONSTRUCTORS & DESTRUCTORS -----//
        rBSTIter() : bstIter<Key,T,Compare,Alloc>() {}
        rBSTIter(elem_ptr_type node) : bstIter<Key,T,Compare,Alloc>(node) {}
        rBSTIter(const rBSTIter &ref) : bstIter<Key,T,Compare,Alloc>(ref.node) {}
        virtual ~rBSTIter() {}
        rBSTIter  &operator=(const rBSTIter &ref) { this->node = ref.node; return (*this); }

        //----- OPERATORS : 'incrementation' & 'decrementation' -----//
        rBSTIter  &operator++() { this->node = this->node->getPrevIter(operator*().first); return (*this); }
        rBSTIter  operator++(int) { rBSTIter tmp(*this); operator++(); return (tmp); }
        rBSTIter  &operator--() { this->node = this->node->getNextIter(operator*().first); return (*this); }
        rBSTIter  operator--(int) { rBSTIter tmp(*this); operator--(); return (tmp); }
        
        //----- OPERATORS :  'dereference' -----//
        reference_type  operator*() const { return (*this->node->getPair()); }
        elem_ptr_type   operator->() const { return (this->node); }
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
        crBSTIter  &operator++() { this->node = this->node->getPrevIter(operator*().first); return (*this); }
        crBSTIter  operator++(int) { crBSTIter tmp(*this); operator++(); return (tmp); }
        crBSTIter  &operator--() { this->node = this->node->getNextIter(operator*().first); return (*this); }
        crBSTIter  operator--(int) { crBSTIter tmp(*this); operator--(); return (tmp); }

        //----- OPERATORS :  'dereference' -----//
        const_reference_type    operator*() const { return (*this->node->getPair()); }
        elem_ptr_type           operator->() const { return (this->node); }
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
        // void updateRoot(binTree *newRoot, binTree *node) {
            // // _root = newRoot;
            // static binTree *lastChecked = NULL;
            // if (node == newRoot && lastChecked == newRoot)
            //     return ;
            // if (node)
            // {
            //     node->_root = newRoot;
            //     lastChecked = node;
            //     if (node->_left && node->_left->_root != newRoot)
            //         updateRoot(newRoot, node->_left);
            //     else if (node->_right && node->_right->_root != newRoot)
            //         updateRoot(newRoot, node->_right);
            //     else
            //         updateRoot(newRoot, lastChecked);

            //     // std::cout << node << std::endl;
            // }

            // if (this == getMostRight(*_root))
            //     return (NULL);
            // std::cout << "DANGER !!!" << std::endl;
            // while (node && node->_root != newRoot)
            // {
            //     if (this == _root || (this->_right && (_comp(key, this->getKey()) || key == this->getKey()) ) )
            //         return (getMostLeft(this->_right));
            //     binTree *parent = this->getParent();
            //     if (_comp(key, parent->getKey()) || parent == _root)
            //         return (parent);
            //     return (parent->getNextIter(key));

            // }
        // }