/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 02:52:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/07 15:52:18 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../templates/binarySearchTree.hpp"
# include "../templates/enable_if.hpp"
# include <functional>
# include <iostream>
# include <memory>

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>,
        class Alloc = std::allocator< std::pair<const Key, T> > >
    class map {

        public :

            //defining every member in my map as in the STL
            typedef Key                                 key_type;
            typedef T                                   mapped_type;
            typedef std::pair< const Key, T >           value_type;
            typedef Compare                             key_compare;
            typedef Alloc                               allocator_type;
            typedef T &                                 reference;
            typedef T *                                 pointer;
            typedef const T &	                        const_reference;
            typedef const T *	                        const_pointer;
            typedef bstIter<Key, T, Compare, Alloc>     iterator;
            typedef cBSTIter<Key, T, Compare, Alloc>    const_iterator;
            typedef rBSTIter<Key, T, Compare, Alloc>    reverse_iterator;
            typedef crBSTIter<Key, T, Compare, Alloc>   const_reverse_iterator;
            typedef ptrdiff_t                           difference_type;
            typedef size_t                              size_type;
            typedef binTree<Key, T, Compare, Alloc>     binTree;

            class CompObject : public std::binary_function<value_type,value_type,bool>
            {
                friend class map;
                protected:
                    Compare _comp;
                    CompObject(Compare c) : _comp(c) {}
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator() (const value_type &x, const value_type &y) const {
                        return _comp(x.first, y.first); }
            };
            typedef CompObject                          value_compare;


            // DEFAULT CONSTRUCTOR
            explicit map(const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : _alloc(alloc), _tree(new binTree),
                _size(0), _comp(comp)
            { }

            // CONSTRUCTOR BY RANGE
            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : _alloc(alloc), _tree(new binTree),
                _size(0), _comp(comp)
            {
                while (first != last)
                    insert(*first++);
            }

            // CONSTRUCTOR BY COPY
            map(const map &ref) : _alloc(ref._alloc), _tree(new binTree),
                _size(0), _comp(ref._comp)
            {
                *this = ref;
            }

            // DESTRUCTOR
            ~map()
            {
                clear();
                delete _tree;
            }

            // ASSIGNATION
            const map &operator=(const map &ref)
            {
                if (_size)
                    clear();
                if (ref._size)
                {
                    for (iterator it = ref.begin(); it != ref.end(); it++)
                        insert(*it);
                }
                return (*this);
            }

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(_tree->getMostLeft(_tree)); }
            iterator        end() { return iterator(_tree->getEnd()); }
            const_iterator  begin() const { return const_iterator(_tree->getMostLeft(_tree)); }
            const_iterator  end() const { return const_iterator(_tree->getEnd()); }
            reverse_iterator rbegin() { return reverse_iterator(_tree->getMostRight(_tree)); }
            reverse_iterator rend() { return reverse_iterator(_tree->getEnd()); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree->getMostRight(_tree)); }
            const_reverse_iterator rend() const { return const_reverse_iterator(_tree->getEnd()); }
            
            // ----- CAPACITY ----- //
            
            bool        empty() const { return (_size == 0); }
            size_type   size() const { return (_size); }
            size_type   max_size() const { return (_alloc.max_size()); }

            // ----- ELEMENT ACCESS ----- //

            mapped_type& operator[] (const key_type &k) {
                binTree *node = _tree->getNode(k, _tree);
                if (node)
                    return (node->getValue());
                value_type *val = new value_type(k, mapped_type());
                std::pair<binTree*,bool> ret = _tree->insertElement(_tree, *val, _size);
                delete val;
                _size++;
                return (ret.first->getValue());
            }

            // ----- MODIFIERS ----- //

            std::pair<iterator,bool> insert(const value_type &val)
            {
                std::pair<binTree*,bool> ret = _tree->insertElement(_tree, val, _size);
                if (ret.second)
                    _size++;
                return (std::pair<iterator,bool>(iterator(ret.first), ret.second));
            }

            iterator insert(iterator position, const value_type &val) {
                binTree *elem = position.getNode();
                if (elem && elem->getParent()->couldBeParent(val.first))
                {
                    std::pair<binTree*,bool> ret = elem->insertElement(elem->getParent(), val, _size);
                    _size++;
                    return (iterator(ret.first));
                }
                std::pair<iterator,bool> ret = insert(val);
                return (ret.first);
            }

            template <class InputIterator>
            void insert(InputIterator first, InputIterator last) {
                while (first != last)
                    insert(*first++);
            }

            void erase(iterator position) {
                if (!_size)
                    return ;
                binTree *to_del = position.getNode();
                to_del->deleteElement();
                _size--;
            }

            size_type erase(const key_type &k) {
                binTree *to_del = _tree->getNode(k, _tree);
                if (!to_del || !_size)
                    return (0);
                _tree->deleteKey(k);
                _size--;
                return (1);
            }

            void erase(iterator first, iterator last) {
                if (!_size)
                    return ;
                iterator iter = first;
                key_type lastKey;
                while (iter != last)
                    lastKey = iter++->first;
                key_type key = first->first;
                while (key != lastKey)
                {
                    key_type nextKey = upper_bound(key)->first;
                    iter = find(key);
                    erase(iter);
                    key = nextKey;
                }
                iter = find(lastKey);
                erase(iter);
            }
            
            void swap(map &x) {
                binTree *tmpRoot = x._tree;
                binTree *tmpEnd = x._tree->getEnd();
                size_t tmpSize = x._size;
                x._tree = this->_tree;
                x._tree->setEnd(this->_tree->getEnd());
                x._size = this->_size;
                this->_tree = tmpRoot;
                this->_size = tmpSize;
                this->_tree->setEnd(tmpEnd);
            }

            void clear() { erase(begin(), end()); }

            // ----- OBSERVERS ----- //

            value_compare   value_comp() const { return (value_compare(_comp)); }
            key_compare     key_comp() const { return (_comp); }

            // ----- OPERATIONS ----- //

            iterator        find(const key_type& k) {
                binTree *node = _tree->getNode(k, _tree);
                if (node)
                    return (iterator(node));
                return (iterator(_tree->getEnd()));
            }
            const_iterator  find(const key_type& k) const {
                binTree *node = _tree->getNode(k, _tree);
                if (node)
                    return (const_iterator(node));
                return (const_iterator(_tree->getEnd()));
            }

            size_type       count(const key_type& k) const {
                return (_tree->getNode(k, _tree) ? 1 : 0);
            }

            iterator        lower_bound(const key_type &k) {
                if (!_size)
                {
                    operator[](key_type());
                    return (find(key_type()));
                }
                iterator it = begin();
                while (it != end())
                {
                    value_type pair = *it;
                    if (!_comp(pair.first, k))
                        return (it);
                    it++;
                }
                return (it);
            }
            const_iterator  lower_bound(const key_type &k) const {
                if (!_size)
                {
                    operator[](key_type());
                    return (find(key_type()));
                }
                const_iterator it = begin();
                while (it != end())
                {
                    value_type pair = *it;
                    if (!_comp(pair.first, k))
                        return (it);
                    it++;
                }
                return (it);
            }

            iterator        upper_bound(const key_type &k) {
                if (!_size)
                {
                    operator[](key_type());
                    return (find(key_type()));
                }
                iterator it = begin();
                while (it != end())
                {
                    value_type pair = *it;
                    if (_comp(k, pair.first))
                        return (it);
                    it++;
                }
                return (it);
            }
            const_iterator  upper_bound(const key_type &k) const {
                if (!_size)
                {
                    operator[](key_type());
                    return (find(key_type()));
                }
                const_iterator it = begin();
                while (it != end())
                {
                    value_type pair = *it;
                    if (_comp(k, pair.first))
                        return (it);
                    it++;
                }
                return (it);
            }

            std::pair<iterator,iterator>             equal_range(const key_type &k) {
                return (std::pair<iterator,iterator>(lower_bound(k), upper_bound(k)));
            }
            std::pair<const_iterator,const_iterator> equal_range(const key_type &k) const {
                return (std::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k)));
            }

        private :

            allocator_type  _alloc;
            binTree         *_tree;
            size_type       _size;
            key_compare     _comp;
            difference_type _diff;
    };
   
    template < class Key, class T >
    bool operator==(const map<Key, T> &lhs, const map<Key, T> &rhs) { 
        if (lhs.size() != rhs.size())
            return false;
        typename map<Key,T>::iterator rhs_it = rhs.begin();
        for (typename map<Key,T>::iterator lhs_it = lhs.begin(); lhs_it != lhs.end(); lhs_it++)
        {
            if (*lhs_it != *rhs_it++)
                return false;
        }
        return true;
    }
    template < class Key, class T >
    bool operator!=(const map<Key, T> &lhs, const map<Key, T> &rhs) { return !(lhs == rhs); }
    template < class Key, class T >
    bool operator<(const map<Key, T> &lhs, const map<Key, T> &rhs) {
        typename map<Key,T>::iterator lhs_it = lhs.begin();
		typename map<Key,T>::iterator rhs_it = rhs.begin();
		while (lhs_it != lhs.end() && rhs_it != rhs.end())
		{
			if (*lhs_it++ < *rhs_it++)
				return true;
		}
		if (lhs_it == lhs.end() && rhs_it != rhs.end())
			return true;
		return false;
    }
    template < class Key, class T >
    bool operator<=(const map<Key, T> &lhs, const map<Key, T> &rhs) { return (lhs < rhs || lhs == rhs); }
    template < class Key, class T >
    bool operator>(const map<Key, T> &lhs, const map<Key, T> &rhs) {
        typename map<Key,T>::iterator lhs_it = lhs.begin();
		typename map<Key,T>::iterator rhs_it = rhs.begin();
		while (lhs_it != lhs.end() && rhs_it != rhs.end())
		{
			if (*lhs_it++ > *rhs_it++)
				return true;
		}
		if (rhs_it == lhs.end() && lhs_it != rhs.end())
			return true;
		return false;
    }
    template < class Key, class T >
    bool operator>=(const map<Key, T> &lhs, const map<Key, T> &rhs) { return (lhs > rhs || lhs == rhs); }
    
    template < class Key, class T >
    void swap(map<Key,T> &x, map<Key,T> &y) {
        map<Key,T> tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

    // THIS IS NOT PART OF THE STL CONTAINER
    template < class Key, class T, class Compare, class Alloc >
    std::ostream &operator<<(std::ostream &out, map<Key,T,Compare,Alloc> const &map) {
        size_t size = map.size();
        out << "\t>> MAP {" << size << "}\t= { ";
        for (typename ft::map<Key,T,Compare,Alloc>::const_iterator it = map.begin(); it != map.end(); it++)
        {
            out << it;
            if (--size)
                out << ", ";
        }
        out << " }" << std::endl;
        return (out);
    }
}

#endif