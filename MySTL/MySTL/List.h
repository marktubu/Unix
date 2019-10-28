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


		};
	}
}