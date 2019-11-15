#pragma once

#include "Allocator.h"
#include "Iterator.h"
#include "UninitializedFunctions.h"


namespace MySTL
{
	template<class T, size_t N, class Alloc>
	class circular_buffer;

	namespace Impl
	{
		template<class T, size_t N, class Alloc>
		class cb_iterator : public iterator<bidirectional_iterator_tag, T>
		{
		public:
			typedef iterator<bidirectional_iterator_tag, T> base_iterator;
			typedef typename base_iterator::pointer pointer;
			typedef typename base_iterator::reference reference;
		public:
			cb_iterator& operator ++();
			cb_iterator& operator ++(int);

			cb_iterator& operator --();
			cb_iterator& operator --(int);

			pointer operator ->() { return data; }
			reference operator *() { return *data; }

		private:
			pointer data;
		};

		template<class T, size_t N, class Alloc = allocator<T>>
		class circular_buffer
		{

		};
	}

}
