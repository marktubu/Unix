#pragma once

#include <new>

#include "TypeTraits.h"

namespace MySTL {
	template<class T1, class T2>
	inline void construct(T1* ptr1, const T2& value)
	{
		new(ptr1) T1(value);
	}

	template<class T>
	inline void destroy(T* ptr)
	{
		ptr->~T();
	}

	template<class ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type)
	{
	}

	template<class ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type)
	{
		for (; first != last; ++first)
		{
			destroy(&*first);
		}
	}

	template<class ForwardIterator, class Tp>
	inline void _destroy(ForwardIterator first, ForwardIterator last, Tp*)
	{
		typedef typename _type_traits<Tp>::has_trivial_destructor _trivial_destructor;
		_destroy(first, last, _trivial_destructor());
	}

	template<class ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last)
	{
		_destroy(first, last, __VALUE_TYPE(first));
	}
}