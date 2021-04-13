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

        std::pair<const Key, T> *_value;
        // const Key *_key;
        // T       *_mapped;
        binTree *_root;
        binTree *_left;
        binTree *_right;
        Compare _comp;
        Alloc   _allocBT;
        // pair_t *_value;

    public :

        typedef std::pair<const Key, T> pair_t;
        
        // create element with no content
        binTree() : _value(NULL), _root(NULL), _left(NULL), _right(NULL),
            _comp(Compare()), _allocBT(Alloc())
        {
            // std::cout << "Default Constructor called -> " << this << std::endl;
            // _value = _allocBT.allocate(1);
        }

        // create new element with a pair of values
        binTree(pair_t pair, binTree *root) : _root(root), _left(NULL),
            _right(NULL), _comp(Compare()), _allocBT(Alloc())
        {
            // std::cout << "Pair Constructor called -> " << this <<" ~ key=" << key << ",_value=" << val << std::endl;
            _value = _allocBT.allocate(1);
            _allocBT.construct(this->_value, pair);
            if (!_root)
                _root = this;
        }

        // create new element with only a key
        // binTree(const Key key, binTree *root) : _root(root), _left(NULL), _right(NULL),
        //     _comp(Compare()), _allocBT(Alloc())
        // {
        //     // std::cout << "Key Constructor called -> " << this << " ~ key=" << key << std::endl;
        //     _value = _allocBT.allocate(1);
        //     _allocBT.construct(_value, pair_t(key, 0));
        //     if (!_root)
        //         _root = this;
        // }

        binTree(const binTree &ref) : _root(NULL), _left(NULL), _right(NULL),
            _comp(Compare()), _allocBT(Alloc())
        { 
            std::cout << "[BST] Copy constructor called" << std::endl;
            _value = _allocBT.allocate(1);
            _allocBT.construct(_value, *ref._value);
        }
        
        ~binTree() {
            _allocBT.deallocate(_value, 1);
        }
        
        binTree &operator=(const binTree &ref) {
            std::cout << "/!\\ WARNING : BST operator= called -> undefined behavior for now..." << std::endl;
            _allocBT.destroy(_value);
            _allocBT.construct(_value, *ref._value);
            // *this->_value = ref._value;
            // this->_root = ref._root;
            // this->_left = ref._left;
            // this->_right = ref._right;
            // this->comp = ref.comp;
            // this->_allocBT = ref._allocBT;
            return (*this);
        }

        binTree     *getRoot() const { return (this->_root); }
        const Key   &getKey() const { return (this->_value->first); }
        T           &getValue() const { return (this->_value->second); }
        pair_t      *getPair() const { return (this->_value); }
        binTree     *getLeft() const { return (this->_left); }
        binTree     *getRight() const { return (this->_right); }
        void        setRoot(binTree *newRoot) { this->_root = newRoot; }
        
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
            while (parent && (parent->_left || parent->_right) && parent->_left != this && parent->_right != this)
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
            if (_comp(this->getKey(), key) && !this->_left)
                return (true);
            if (_comp(key, this->getKey()) && !this->_right)
                return (true);
            return (false);
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
            if (this == getMostRight(_root))
                return (NULL);
            if (this == _root || (this->_right && (_comp(key, this->getKey()) || key == this->getKey()) ) )
                return (getMostLeft(this->_right));
            binTree *parent = this->getParent();
            if (_comp(key, parent->getKey()) || parent == _root)
                return (parent);
            return (parent->getNextIter(key));
        }
        
        binTree *getPrevIter(const Key &key) const {
            if (this == getMostLeft(_root))
                return (NULL);
            if (this == _root || (this->_left && (_comp(this->getKey(), key) || key == this->getKey()) ) )
                return (getMostRight(this->_left));
            binTree *parent = this->getParent();
            if (_comp(parent->getKey(), key) || parent == _root)
                return (parent);
            return (parent->getPrevIter(key));
        }

        void updateRoot(binTree *newRoot, binTree *node) {
            // _root = newRoot;
            static binTree *lastChecked = NULL;
            if (node == newRoot && lastChecked == newRoot)
                return ;
            if (node)
            {
                node->_root = newRoot;
                lastChecked = node;
                if (node->_left && node->_left->_root != newRoot)
                    updateRoot(newRoot, node->_left);
                else if (node->_right && node->_right->_root != newRoot)
                    updateRoot(newRoot, node->_right);
                else
                    updateRoot(newRoot, lastChecked);

                // std::cout << node << std::endl;
            }
        }

        std::pair<binTree*,bool> insertElement(binTree *node, const pair_t &pair) {
            // if (!_root)
            // {
            //     _allocBT.construct(this->_value, pair);
            //     _root = this;
            //     return (std::pair<binTree*,bool>(_root, true));
            // }
            if (!node)
            {
                node = new binTree(pair, _root);
                node->setChildInParent(node, pair.first);
                return (std::pair<binTree*,bool>(node, true));
            }
            if (node->getKey() == pair.first)
            {
                node->_value->second = pair.second;
                return (std::pair<binTree*,bool>(node, false));
            }
            if (_comp(pair.first, node->getKey()))
                return (insertElement(node->_left, pair));
            else
                return (insertElement(node->_right, pair));
        }

        void setChildInParent(binTree *child, const Key &key) {
            binTree *parent = this->getParent();
            if (parent && parent != this)
            {
                if (_comp(parent->getKey(), key))
                    parent->_right = child;
                else
                    parent->_left = child;
            }
        }

        void replaceInParent(binTree *newChild) {
            binTree *parent = this->getParent();
            if (parent && parent != this)
            {
                if (this == _root)
                    updateRoot(newChild, _root);
                if (this == parent->_left)
                    parent->_left = newChild;
                else
                    parent->_right = newChild;
            }
            else if (parent == this)
            {
                *this = *newChild;
                this->_root = newChild;
            }
        }

        void deleteElement() {
            if (this->_left && this->_right)  // If both children are present
            {
                binTree *successor = getMostLeft(this->_right);
                // if (this == _root)
                //     updateRoot(newChild);
                *this = *successor;
                // pair_t newContent(successor->getKey(), this->_value->second);
                // this->getKey() = successor->getKey();
                successor->deleteElement();
                // successor->deleteKey(successor->getKey());

                // probleme ici : si c'etait root qu'on a delete, rien ne fait le lien entre _tree et la nouvelle root\
                // et on peut plus check apres pour eviter puisqu'elle a ete changee entre temps
            }
            else if (this->_left)  // If the node has only a *_left* child
                this->replaceInParent(this->_left);
            else if (this->_right) // If the node has only a *_right* child
                this->replaceInParent(this->_right);
            else                    // This node has no children
                this->replaceInParent(NULL);
            delete this;
            // if (this != _root)
            // else
            //     updateRoot();
            // {
            //     _allocBT.destroy(this->_value);
            //     this->_root = NULL;
            //     return ;
            // }
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
        bstIter  &operator--() { this->node = this->node->getPrevIter(operator*().first); return (*this); }
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