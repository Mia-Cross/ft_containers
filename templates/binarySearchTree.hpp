#ifndef BINARY_SEARCH_TREE_H
# define BINARY_SEARCH_TREE_H

# include "../containers/list.hpp"
# include <memory>
# include <cstddef>

# include <iostream>

template < class Key, class T, class Compare, class Alloc >
class binTree
{
    public :

        typedef std::pair<const Key, T> pair_t;
        
        // create root element with no content
        binTree() : _pair(NULL), _root(this), _left(NULL), _right(NULL), _end(new binTree(this)),
            _comp(Compare()), _allocBT(Alloc())
        { }
        
        // create end element with no content
        binTree(binTree *root) : _pair(NULL), _root(root), _left(NULL), _right(NULL), _end(this),
            _comp(Compare()), _allocBT(Alloc())
        { }

        // create new element with a pair of values
        binTree(const pair_t &pair, binTree *root) : _root(root), _left(NULL),
            _right(NULL), _end(root->_end), _comp(Compare()), _allocBT(Alloc())
        {
            _pair = _allocBT.allocate(1);
            _allocBT.construct(_pair, pair);
        }

        binTree(const binTree &ref) : _root(this), _left(NULL), _right(NULL), _end(new binTree(this)),
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
        const Key   &getKey() const { return (this->_pair->first); }
        T           &getValue() const { return (this->_pair->second); }
        pair_t      *getPair() const { return (this->_pair); }
        binTree     *getLeft() const { return (this->_left); }
        binTree     *getRight() const { return (this->_right); }
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
            // std::cout << "GET PARENT de " << this << " (key = " << this->getKey();
            while (parent && parent->_pair && parent->_left != this && parent->_right != this)
            // while (parent && (parent->_left || parent->_right) && parent->_left != this && parent->_right != this)
            {
                if (_comp(this->getKey(), parent->getKey()) && parent->_left)
                    parent = parent->_left;
                else if (_comp(parent->getKey(), this->getKey()) && parent->_right)
                    parent = parent->_right;
                else
                    break;
            }
            // std::cout << ") : parent = " << parent << " // key = " << parent->getKey() << std::endl;
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
            // std::cout << "GET NODE : node = " << node << " // key = " << node->getKey() << std::endl;
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
            if (this == getMostRight(_root) || !_root->_pair)
                return (_end);
            if (this == _root || (this->_right && (_comp(key, this->getKey()) || key == this->getKey()) ) )
                return (getMostLeft(this->_right));
            binTree *parent = this->getParent();
            if (_comp(key, parent->getKey()) || parent == _root)
                return (parent);
            return (parent->getNextIter(key));
        }
        
        binTree *getPrevIter(const Key &key) const {
            if (this == getMostLeft(_root) || !_root->_pair)
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

        std::pair<binTree*,bool> insertElement(binTree *node, const pair_t &pair) {
            if (!_pair)
            {
                _pair = _allocBT.allocate(1);
                _allocBT.construct(_pair, pair_t(pair.first, pair.second));
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
                return (insertElement(node->_left, pair));
            else
                return (insertElement(node->_right, pair));
        }

        void setChildInParent(binTree *child, const Key &key) {
            binTree *parent = this->getParent();
            // std::cout << "SET CHILD IN PARENT = ";
            if (_comp(parent->getKey(), key))
                parent->_right = child;
            else if (_comp(key, parent->getKey()))
                parent->_left = child;
        }

        /////////////////////
        //     DELETION    //
        /////////////////////

        // new version

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
                this->_pair = NULL;
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
        // elem_ptr_type   getNodeM() const { return (this->node); }
        
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