/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllThomas.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:11:03 by thgermai          #+#    #+#             */
/*   Updated: 2021/05/04 01:40:19 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLL
# define DLL

# include <iostream>
# include "utilsThomas.hpp"

namespace		ft
{
	template<class T, class Alloc = std::allocator<T> >
	struct			Node
	{
		typedef T									value_type;
		typedef Alloc								allocator_type;
		typedef Node<T, Alloc>*						node;
		typedef typename allocator_type::pointer 	pointer;
		typedef typename allocator_type::reference	reference;

		Node(const value_type& val, allocator_type& alloc = allocator_type())
		{
			data = alloc.allocate(1);
			alloc.construct(data, val);
			link(NULL, NULL);
		}

		~Node()
		{
			allocator_type		alloc;
			alloc.destroy(data);
			alloc.deallocate(data, 1);
		}

		pointer				operator->() const { return data; }
		reference			operator*() const { return *data; }

		node				link(node _prev, node _next)
		{
			prev = _prev;
			next = _next;
			return this;
		}
		node				insert(node _prev, node _next)
		{
			next = _prev->next;
			_prev->next = this;
			prev = _next->prev;
			_next->prev = this;
			return this;
		}
		node				extract()
		{
			prev->next = next;
			next->prev = prev;
			return this;
		}

		void				swap_data(node n)
		{
			pointer		tmp = data;

			data = n->data;
			n->data = tmp;
		}

		pointer			data;
		node			prev;
		node			next;
	};




	template<class T, class Alloc = std::allocator<T> >
	class			DoublyLinkedList
	{
	public :
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef Node<T, Alloc>*								node;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef typename allocator_type::const_reference	const_reference;
		typedef size_t										size_type;

		DoublyLinkedList(const allocator_type& alloc = allocator_type())
		{
			_allocator = alloc;
			head = new Node<T, Alloc>(value_type(), _allocator);
			tail = head;
			head->link(tail, tail);
			_size = 0;
		}
		DoublyLinkedList(const DoublyLinkedList &ref)
		{
			_allocator = ref._allocator;
			head = new Node<T, Alloc>(value_type(), _allocator);
			tail = head;
			head->link(tail, tail);
			_size = 0;
			*this = ref;
		}
		DoublyLinkedList			&operator=(const DoublyLinkedList& ref)
		{
			if (_size)
				_clean_list();
			if (!ref._size)
				return *this;
			node		curr = ref.head->next;
			while (curr != ref.head)
			{
				push_back(*curr->data);
				curr = curr->next;
			}
			return *this;
		}

		~DoublyLinkedList() { _clean_list(); delete head; }

		bool					empty() const { return _size == 0; }
		size_type				size() const { return _size; }
		void					increase_size(const size_type& n = 1) { _size += n; }
		void					decrease_size(const size_type& n = 1) { _size -= n; }

		reference				front() { return *head->next->data; }
		const_reference			front() const { return *head->next->data; }
		reference				back() { return *tail->data; }
		const_reference			back() const { return *tail->data; }

		node					get_head() const { return head; }
		void					clear() { _clean_list(); }

		void					push_front(const value_type& val)
		{
			if (!_size)
				_first_insert(val);
			else
				_insert_front(val);
		}

		void					push_back(const value_type& val)
		{
			if (!_size)
				_first_insert(val);
			else
				_insert_back(val);
		}

		void					insert(const value_type& val, node position)
		{
			if (position == head->next)
				push_front(val);
			else if (position == head)
				push_back(val);
			else
			{
				if (!_size)
					_first_insert(val);
				else
					_insert_at(val, position);
			}
		}

		void					pop_front()
		{
			if (_size)
			{
				delete head->next->extract();
				--_size;
			}
		}

		void					pop_back()
		{
			if (_size)
			{
				delete tail->extract();
				--_size;
			}
			tail = head->prev;
		}

		void					delete_node(node n)
		{
			if (n == head)
				return ;
			if (n == head->next)
				pop_front();
			else if (n == tail)
				pop_back();
			else
			{
				delete n->extract();
				--_size;
			}
		}

		void					move_to(node n, node destination)
		{
			n->extract();
			n->insert(destination->prev, destination);
			if (destination == head)
				tail = n;
		}

		void					move_range_to(node start, node end, node position)
		{
			node				p_position = position->prev;

			_unlink_range(start, end);
			p_position->link(p_position->prev, start);
			start->link(position->prev, start->next);
			end->link(end->prev, position);
			position->link(end, position->next);
		}

		node					find_node(const value_type *addr)
		{
			node		curr = head->next;

			while (curr != head)
			{
				if (curr->data == addr)
					return curr;
				curr = curr->next;
			}
			if (curr->data == addr)
				return curr;
			return NULL;
		}

		void					swap(DoublyLinkedList& ref)
		{
			ft::_swap(head, ref.head);
			ft::_swap(tail, ref.tail);
			ft::_swap(_size, ref._size);
		}

		template<class Compare>
		void					sort(Compare comp)
		{
			node 			curr = head->next;

			while (curr->next != head)
			{
				node		next = curr->next;
				if (comp(*next->data, *curr->data))
				{
					curr->swap_data(next);
					curr = head;
				}
				curr = curr->next;
			}
		}

		void					reverse()
		{
			node			start = head->next;
			node			end = head->prev;

			for (size_type i = 0; i < _size / 2; ++i)
			{
				start->swap_data(end);
				start = start->next;
				end = end->prev;
			}
		}

		void					refresh_tail() { tail = head->prev; }

	private :
		node				head;
		node				tail;
		size_type			_size;
		allocator_type		_allocator;

		node					_new_node(const value_type& val) { return new Node<value_type, allocator_type>(val, _allocator); }

		void					_first_insert(const value_type& val)
		{
			tail = _new_node(val);

			tail->link(head, head);
			head->link(tail, tail);
			++_size;
		}

		void					_insert_front(const value_type& val)
		{
			node		n = _new_node(val);

			n->insert(head, head->next);
			++_size;
		}

		void					_insert_back(const value_type& val)
		{
			node		n = _new_node(val);

			n->insert(tail, head);
			tail = n;
			++_size;
		}

		node					_insert_at(const value_type& val, node position)
		{
			node		n = _new_node(val);

			n->insert(position->prev, position);
			++_size;
			return n;
		}

		void					_unlink_range(node start, node end)
		{
			start->prev->next = end->next;
			end->next->prev = start->prev;
		}

		void					_clean_list()
		{
			node		curr = head->next;
			if (!_size)
				return ;
			while (curr != head)
			{
				node next = curr->next;
				delete curr;
				curr = next;
			}
			_size = 0;
			tail = NULL;
			head->link(NULL, NULL);
		}
	};
};

#endif