#pragma once

#include "Allocator.h"
#include "Iterator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"

#include <type_traits>

namespace MySTL
{
	template<class T>
	class list;

	namespace Impl
	{
		template<class T>
		struct node
		{
			T data;
			node* prev;
			node* next;
			list<T>* container;

			node(const T& d, node* p, node* n, list<T>* c) :data(d), prev(p), next(n), container(c) {}
			bool operator ==(const node& n)
			{
				return data == n.data && prev == n.prev && next == n.next && container == n.container;
			}
		};

		template<class T>
		struct list_iterator : public iterator<bidirectional_iterator_tag, T>
		{
			template<class T>
			friend class list;
		public:
			typedef node<T>* node_ptr;
			node_ptr p;

		public:
			explicit list_iterator(node_ptr ptr = nullptr) :p(ptr) {}

			list_iterator& operator++();
			list_iterator operator ++(int);
			list_iterator& operator--();
			list_iterator operator--(int);
			T& operator*() { return p->data; }
			T* operator->() { return &(operator*()); }

			template<class T>
			friend bool operator==(const list_iterator<T>& lhs, const list_iterator<T>& rhs);

			template<class T>
			friend bool operator!=(const list_iterator<T>& lhs, const list_iterator<T>& rhs);
		};

		template<class T>
		class list
		{
			template<class T>
			friend struct list_iterator;
		private:
			typedef allocator<Impl::node<T>> node_allocator;
			typedef Impl::node<T>* node_ptr;
		public:
			typedef T value_type;
			typedef Impl::list_iterator<T> iterator;
			typedef Impl::list_iterator<const T> const_iterator;
			typedef reverse_iterator_t<iterator> reverse_iterator;
			typedef T& reference;
			typedef size_t size_type;
		private:
			iterator head;
			iterator tail;
		public:
			list();
			explicit list(size_type n, const value_type& val = value_type());

			template<class InputIterator>
			list(InputIterator first, InputIterator last);

			list(const list& l);
			list& operator=(const list& l);
			~list();

			bool empty()const { return head == tail; }
			size_type size()const;
			reference front() { return (head.p->data); }
			reference back() { return (tail.p->prev->data); }

			void push_front(const value_type& val);
			void pop_front();
			void push_back(const value_type& val);
			void pop_back();

			iterator begin();
			iterator end();
			const_iterator begin()const;
			const_iterator end()const;
			reverse_iterator rbegin();
			reverse_iterator rend();

			iterator insert(iterator position, const value_type& val);
			void insert(iterator position, size_type n, const value_type& val);

			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last);

			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);

			void swap(list& x);
			void clear();
			void splice(iterator position, list& x);
			void splice(iterator position, list& x, iterator i);
			void splice(iterator position, list& x, iterator first, iterator last);

			void remove(const value_type& val);

			template<class Predicate>
			void remove_if(Predicate pred);

			void unique();

			template<class BinaryPredicate>
			void unique(BinaryPredicate binary_pred);

			void merge(list& x);

			template<class Compare>
			void merge(list& x, Compare comp);

			void sort();

			template<class Compare>
			void sort(Compare comp);

			void reverse();

		private:
			void ctor_aux(size_type n, const value_type& val, std::true_type);

			template<class InputIterator>
			void ctor_aux(InputIterator first, InputIterator last, std::false_type);

			node_ptr new_node(const T& val = T());
			void delete_node(node_ptr p);
			void insert_aux(iterator position, size_type n, const T& val, std::true_type);

			template<class InputIterator>
			void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);

			const_iterator change_iterator_to_const_iterator(iterator& it) const;

		public:
			template<class T>
			friend void swap(list<T>& x, list<T>& y);

			template<class T>
			friend bool operator==(const list<T>& lhs, const list<T>& rhs);

			template<class T>
			friend bool operator!=(const list<T>& lhs, const list<T>& rhs);
		};
	}
}