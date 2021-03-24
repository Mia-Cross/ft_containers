/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 02:52:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/03/24 17:49:57 by lemarabe         ###   ########.fr       */
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
                const allocator_type& alloc = allocator_type()) : myAlloc(alloc),
                myMap(new binTree), mySize(0), myComp(comp)
            {}
            // CONSTRUCTOR BY RANGE
            // Map(iterator first, iterator last,
            //     const key_compare& comp = key_compare(),
            //     const allocator_type& alloc = allocator_type())
            // {}
            // CONSTRUCTOR BY COPY
            Map(const Map &ref)
            {
                *this = ref;
            }
            // DESTRUCTOR
            ~Map()
            {
                delete myMap;
            }
            // ASSIGNATION
            const Map &operator=(const Map &)
            {}

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(myMap->getFarLeft()); }
            iterator        end() { return iterator(myMap->getFarRight()->getRight()); }
            const_iterator  begin() const { return const_iterator(myMap->getFarLeft()); }
            const_iterator  end() const { return const_iterator(myMap->getFarRight()->getRight()); }
            // reverse_iterator rbegin() { return reverse_iterator(myVect.getArray() + mySize - 1); }
            // reverse_iterator rend() { return reverse_iterator(myVect.getArray() - 1); }
            // const_reverse_iterator rbegin() const { return const_reverse_iterator(myVect.getArray() + mySize - 1); }
            // const_reverse_iterator rend() const { return const_reverse_iterator(myVect.getArray() - 1); }
            
            // ----- CAPACITY ----- //
            
            bool empty() const { return (mySize == 0); }
            size_type size() const { return (mySize); }
            size_type max_size() const { return (myAlloc.max_size()); }

            // ----- ELEMENT ACCESS ----- //

            mapped_type& operator[] (const key_type &k) {
                if (!mySize)
                {
                    myMap->setRoot(myMap);
                    myMap->setValue(k);
                    mySize++;
                    return (myMap->getValueRef().second);
                }
                binTree *branch = myMap->getBranch(k);
                if (branch->getValueRef().first == k)
                    return (branch->getValueRef().second);
                binTree *newBranch = new binTree(k);
                myMap->insert(newBranch);
                mySize++;
                return (newBranch->getValueRef().second);
            }

            // ----- MODIFIERS ----- //

            std::pair<iterator,bool> insert(const value_type& val)
            {
                if (!mySize)
                {
                    myMap->setRoot(myMap);
                    myMap->setValue(val);
                    mySize++;
                    return (std::pair<iterator,bool>(iterator(myMap), true));
                }
                binTree *branch = myMap->getBranch(val.first);
                if (branch->getValueRef().first == val.first)
                    return (std::pair<iterator,bool>(iterator(branch), false));
                binTree *newBranch = new binTree(val);
                myMap->insert(newBranch);
                mySize++;
                return (std::pair<iterator,bool>(iterator(newBranch), true));
            }
            // iterator insert(iterator position, const value_type& val);
            // void insert(iterator first, iterator last);

            // ----- OBSERVERS ----- //

            // value_compare value_comp() const;
            key_compare key_comp() const { return (myComp); }

            // ----- OPERATIONS ----- //

            // binTree &getMap() const { return (const_cast<binTree &>(myMap)); }

        private :

            allocator_type  myAlloc;
            binTree         *myMap;
            size_type       mySize;
            key_compare     myComp;
            difference_type myDiff;
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
        out << "\t>> MAP [" << size << "]\t= { ";
        for (typename Map<Key,T,Compare,Alloc>::const_iterator it = map.begin(); size-- > 0; it++)
        {
            // std::cout << size << std::endl;
            std::pair<const Key, T> pair = *it;
            // std::cout << "KEY to display = " << pair.first << std::endl;
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