/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 02:52:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/04/08 04:52:03 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../templates/binarySearchTree.hpp"
# include <functional>
# include <iostream>
# include <memory>

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>,
        class Alloc = std::allocator< std::pair<const Key, T> > >
    class Map {

        public :

             //defining every member in my List as in the STL
            typedef Key                                 key_type;
            typedef T                                   mapped_type;
            typedef std::pair< const Key, T >           value_type;
            typedef Compare                             key_compare;
            //typedef ___                               value_compare;
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

            // DEFAULT CONSTRUCTOR
            explicit Map(const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : _alloc(alloc),
                _tree(new binTree), _size(0), _comp(comp)
            {}
            // CONSTRUCTOR BY RANGE
            Map(iterator first, iterator last, const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : _alloc(alloc),
                _tree(new binTree), _size(0), _comp(comp)
            {
                while (first != last)
                    insert(*first++);
            }
            // CONSTRUCTOR BY COPY
            Map(const Map &ref) : _alloc(ref._alloc), _tree(new binTree(*ref._tree)),
                _size(0), _comp(ref._comp)
            {
                *this = ref;
            }
            // DESTRUCTOR
            ~Map()
            {
                clear();
                delete _tree;
            }
            // ASSIGNATION
            const Map &operator=(const Map &ref)
            {
                if (_size)
                    clear();
                // *_tree = *ref._tree;
                for (iterator it = ref.begin(); it != ref.end(); it++)
                    insert(*it);
                return (*this);
            }

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(_tree->getMostLeft(_tree)); }
            iterator        end() { return iterator(); }
            const_iterator  begin() const { return const_iterator(_tree->getMostLeft(_tree)); }
            const_iterator  end() const { return const_iterator(); }
            reverse_iterator rbegin() { return reverse_iterator(_tree->getMostRight(_tree)); }
            reverse_iterator rend() { return reverse_iterator(); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree->getMostRight(_tree)); }
            const_reverse_iterator rend() const { return const_reverse_iterator(); }
            
            // ----- CAPACITY ----- //
            
            bool empty() const { return (_size == 0); }
            size_type size() const { return (_size); }
            size_type max_size() const { return (_alloc.max_size()); }

            // ----- ELEMENT ACCESS ----- //

            mapped_type& operator[] (const key_type &k) {
                binTree *node = _tree->getNode(k, _tree->getRoot());
                if (node)
                    return (node->getValue());
                std::pair<iterator,bool> ret = _tree->insertElement(_tree, k);
                _size++;
                node = ret.first.operator->();
                return (node->getValue());
            }

            // ----- MODIFIERS ----- //

            std::pair<iterator,bool> insert(const value_type& val)
            {
                std::pair<binTree*,bool> ret = _tree->insertElement(_tree, val.first, const_cast<char &>(val.second));
                if (ret.second)
                    _size++;
                return (std::pair<iterator,bool>(iterator(ret.first), ret.second));
            }

            // iterator insert(iterator position, const value_type& val);
            // void insert(iterator first, iterator last);
            
            void erase(iterator position) {
                if (_size)
                {
                    binTree *to_del = position.operator->();
                    _tree->deleteFromTree(to_del->getKey());
                    _size--;
                }
            }
            // size_type erase(const key_type& k) {}
            void erase(iterator first, iterator last) {
                while (first != last)
                {
                    iterator to_del = first++;
                    erase(to_del);
                }
            }
            
            void swap(Map &x) {
                binTree *tmp = x._tree;
                size_t tmpSize = x._size;
                x._tree = this->_tree;
                x._size = this->_size;
                this->_tree = tmp;
                this->_size = tmpSize;
            }

            void clear() {
                // for (iterator it = begin(); it != end(); it++)
                //     delete it.operator->();
                erase(begin(), end());
            }

            // ----- OBSERVERS ----- //

            // value_compare value_comp() const;
            key_compare key_comp() const { return (_comp); }

            // ----- OPERATIONS ----- //

            iterator        find (const key_type& k);
            const_iterator  find (const key_type& k) const;
            size_type       count (const key_type& k) const;
            iterator        lower_bound (const key_type& k);
            const_iterator  lower_bound (const key_type& k) const;
            iterator        upper_bound (const key_type& k);
            const_iterator  upper_bound (const key_type& k) const;
            std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
            std::pair<iterator,iterator>             equal_range (const key_type& k);
            // binTree *getMapRoot() const { return (_tree->getRoot()); }

        private :

            allocator_type  _alloc;
            binTree         *_tree;
            size_type       _size;
            key_compare     _comp;
            difference_type _diff;
    };
    
    template < class Key, class T, class Compare, class Alloc >
    bool operator==(const Map<Key,T,Compare,Alloc> &lhs, const Map<Key,T,Compare,Alloc> &rhs) { return (lhs == rhs); }
    template < class Key, class T, class Compare, class Alloc >
    bool operator!=(const Map<Key,T,Compare,Alloc> &lhs, const Map<Key,T,Compare,Alloc> &rhs) { return (lhs != rhs); }
    template < class Key, class T, class Compare, class Alloc >
    bool operator<(const Map<Key,T,Compare,Alloc> &lhs, const Map<Key,T,Compare,Alloc> &rhs) { return (lhs < rhs); }
    template < class Key, class T, class Compare, class Alloc >
    bool operator<=(const Map<Key,T,Compare,Alloc> &lhs, const Map<Key,T,Compare,Alloc> &rhs) { return (lhs <= rhs); }
    template < class Key, class T, class Compare, class Alloc >
    bool operator>(const Map<Key,T,Compare,Alloc> &lhs, const Map<Key,T,Compare,Alloc> &rhs) { return (lhs > rhs); }
    template < class Key, class T, class Compare, class Alloc >
    bool operator>=(const Map<Key,T,Compare,Alloc> &lhs, const Map<Key,T,Compare,Alloc> &rhs) { return (lhs >= rhs); }
    
    template < class Key, class T, class Compare, class Alloc >
    std::ostream &operator<<(std::ostream &out, Map<Key,T,Compare,Alloc> const &map) {
        size_t size = map.size();
        out << "\t>> MAP {" << size << "}\t= { ";
        // const binTree<Key,T,Compare,Alloc> *root = map.getMapRoot();
        // out << "ROOT->" << root;
        // if (root)
        // {
        //     out << " = [" << root->getKey() << "] [L=";
        //     out << root->getLeft() << "] [R=" << root->getRight() << "] || ";
        // }
        for (typename Map<Key,T,Compare,Alloc>::const_iterator it = map.begin(); size-- > 0; it++)
        {
            // std::cout << size << std::endl;
            std::pair<const Key, T> pair = *it;
            // std::cout << "\'" << pair.first << "-" << pair.second << "\'" << std::endl;
            out << "\'" << pair.first << "-" << pair.second << "\'";
            if (size)
                out << ", ";
        }
        out << " }" << std::endl;
        return (out);
    }
}

#endif