/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 02:52:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/23 06:06:30 by lemarabe         ###   ########.fr       */
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
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< std::pair<const Key, T> > >
    class Map {

        public :

             //defining every member in my List as in the STL
            typedef Key                                 key_type;
            typedef T                                   mapped_type;
            typedef std::pair< Key, T >                 value_type;
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

            // DEFAULT CONSTRUCTOR
            explicit Map(const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : myAlloc(alloc),
                myMap(std::pair<int, char>(42, '*')), mySize(0), myComp(comp)
            {}
            // CONSTRUCTOR BY RANGE
            // Map(iterator first, iterator last,
            //     const key_compare& comp = key_compare(),
            //     const allocator_type& alloc = allocator_type())
            // {}
            // CONSTRUCTOR BY COPY
            Map(const Map &)
            {}
            // DESTRUCTOR
            ~Map()
            {}
            // ASSIGNATION
            const Map &operator=(const Map &)
            {}

            // ----- ITERATORS ----- //
            
            // iterator        begin() { return iterator(myVect.getArray()); }
            // iterator        end() { return iterator(myVect.getArray() + mySize); }
            // const_iterator  begin() const { return const_iterator(myVect.getArray()); }
            // const_iterator  end() const { return const_iterator(myVect.getArray() + mySize); }
            // reverse_iterator rbegin() { return reverse_iterator(myVect.getArray() + mySize - 1); }
            // reverse_iterator rend() { return reverse_iterator(myVect.getArray() - 1); }
            // const_reverse_iterator rbegin() const { return const_reverse_iterator(myVect.getArray() + mySize - 1); }
            // const_reverse_iterator rend() const { return const_reverse_iterator(myVect.getArray() - 1); }
            
            // ----- CAPACITY ----- //
            
            bool empty() const { return (mySize == 0); }
            size_type size() const { return (mySize); }
            size_type max_size() const { return (myAlloc.max_size()); }

            // ----- ELEMENT ACCESS ----- //

            // mapped_type& operator[] (const key_type& k) {}

            // ----- MODIFIERS ----- //

            // std::pair<iterator,bool> insert(const value_type& val);
            // iterator insert(iterator position, const value_type& val);
            // void insert(iterator first, iterator last);

            // ----- OBSERVERS ----- //

            // value_compare value_comp() const;
            key_compare key_comp() const { return (myComp); }

            // ----- OPERATIONS ----- //

            binTree<Key,T,Compare,Alloc> &getMap() const { return (const_cast<binTree<Key,T,Compare,Alloc> &>(myMap)); }

        private :

            allocator_type                  myAlloc;
            binTree<Key,T,Compare,Alloc>    myMap;
            size_type                       mySize;
            key_compare                     myComp;
            difference_type                 myDiff;
    };
    
    template < class Key, class T >
    bool operator==(const Map<Key,T> &lhs, const Map<Key,T> &rhs) { return (lhs == rhs); }
    template < class Key, class T >
    bool operator!=(const Map<Key,T> &lhs, const Map<Key,T> &rhs) { return (lhs != rhs); }
    template < class Key, class T >
    bool operator<(const Map<Key,T> &lhs, const Map<Key,T> &rhs) { return (lhs < rhs); }
    template < class Key, class T >
    bool operator<=(const Map<Key,T> &lhs, const Map<Key,T> &rhs) { return (lhs <= rhs); }
    template < class Key, class T >
    bool operator>(const Map<Key,T> &lhs, const Map<Key,T> &rhs) { return (lhs > rhs); }
    template < class Key, class T >
    bool operator>=(const Map<Key,T> &lhs, const Map<Key,T> &rhs) { return (lhs >= rhs); }
    
    template < class Key, class T >
    std::ostream &operator<<(std::ostream &out, Map<Key,T> const &map) {
        // size_t size = vect.size();
        // out << "\t>> VECTOR [" << size << "]\t= { ";
        // for (typename Map<Key,T>::const_iterator it = vect.begin(); size-- > 0; it++)
        // {
        //     out << *it;
        //     if (size)
        //         out << ", ";
        // }
        // out << " }" << std::endl;
        out << map.getMap().value->first << ", " << map.getMap().value->second << std::endl;
        return (out);
    }
}

#endif