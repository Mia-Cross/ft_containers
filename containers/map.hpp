/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 02:52:25 by lemarabe          #+#    #+#             */
/*   Updated: 2021/04/06 02:29:15 by lemarabe         ###   ########.fr       */
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
                clear();
            }
            // ASSIGNATION
            const Map &operator=(const Map &)
            {}

            // ----- ITERATORS ----- //
            
            iterator        begin() { return iterator(myMap->getMostLeft(myMap)); }
            iterator        end() { return iterator(); }
            // iterator        end() { return iterator(myMap->getMostRight(myMap)->getRight()); }
            const_iterator  begin() const { return const_iterator(myMap->getMostLeft(myMap)); }
            const_iterator  end() const { return const_iterator(); }
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
                binTree *node = myMap->getNode(k, myMap->getRoot());
                if (node)
                    return (node->getValue());
                std::cout <<"pas trouve mon node donc je construis" << std::endl;
                std::pair<iterator,bool> ret = myMap->insert(myMap, k);
                mySize++;
                node = ret.first.operator->();
                // std::cout << node->getKey() << std::endl;
                return (node->getValue());
                // if (!mySize)
                // {
                //     myMap->setRootSingle(myMap);
                //     myMap->setValue(k);
                //     mySize++;
                //     return (myMap->getValue().second);
                // }
                // binTree *branch = myMap->getBranch(k);
                // if (branch->getValue().first == k)
                //     return (branch->getValue().second);
                // binTree *newBranch = new binTree(k, myMap);
                // myMap->insert(newBranch);
                // mySize++;
                // return (newBranch->getValue().second);
            }

            // ----- MODIFIERS ----- //

            std::pair<iterator,bool> insert(const value_type& val)
            {
                std::pair<binTree*,bool> ret = myMap->insert(myMap, val.first, const_cast<char &>(val.second));
                // std::cout << "root left = " << myMap->getLeft() << std::endl;
                // std::cout << "root right = " << myMap->getRight() << std::endl;
                mySize++;
                return (std::pair<iterator,bool>(iterator(ret.first), ret.second));
            //     if (!mySize)
            //     {
            //         myMap->setRootSingle(myMap);
            //         myMap->setValue(val);
            //         mySize++;
            //         return (std::pair<iterator,bool>(iterator(myMap), true));
            //     }
            //     binTree *branch = myMap->getBranch(val.first);
            //     if (branch->getValue().first == val.first)
            //         return (std::pair<iterator,bool>(iterator(branch), false));
            //     binTree *newBranch = new binTree(val);
            //     myMap->insert(newBranch);
            //     mySize++;
            //     return (std::pair<iterator,bool>(iterator(newBranch), true));
            }

            // iterator insert(iterator position, const value_type& val);
            // void insert(iterator first, iterator last);
            
            void erase(iterator position) {
                if (mySize)
                {
                    binTree *to_del = position.operator->();
                    myMap->deleteFromTree(to_del->getKey());
                    mySize--;
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

            void clear() {
                // for (iterator it = begin(); it != end(); it++)
                //     delete it.operator->();
                erase(begin(), end());
            }

            // ----- OBSERVERS ----- //

            // value_compare value_comp() const;
            key_compare key_comp() const { return (myComp); }

            // ----- OPERATIONS ----- //

            binTree *getMapRoot() const { return (myMap->getRoot()); }

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