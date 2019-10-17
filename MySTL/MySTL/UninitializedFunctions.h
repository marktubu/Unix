#pragma once

#include "Algorithm.h"
#include "Constructor.h"
#include "TypeTraits.h"
#include "Iterator.h"

namespace MySTL
{
	//copy

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type);

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type);

	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
	{
		typedef typename _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type isPODType;
		return _uninitialized_copy_aux(first, last, result, isPODType());
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type)
	{
		memcpy(result, first, (last - first) * sizeof(*first));
		return result + (last - first);
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type)
	{
		ForwardIterator _cur = result;
		for (; first != last; ++first, ++_cur)
		{
			construct(&*_cur, *first);
		}

		return _cur;
	}

	//fill

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type);

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type);

	template<class ForwardIterator, class Tp, class Tp1>
	inline void _uninitialized_fill(ForwardIterator first, ForwardIterator last, const Tp& value, Tp1*)
	{
		typedef typename _type_traits<Tp1>::is_POD_type isPODType;
		_uninitialized_fill_aux(first, last, value, isPODType());
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		_uninitialized_fill(first, last, value, __VALUE_TYPE(first));
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type)
	{
		fill(first, last, value);
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type)
	{
		ForwardIterator _cur = first;
		for(; _cur != last; ++_cur)
		{
			construct(&*_cur, value);
		}
	}

	//fill_n

	template<class ForwardIterator, class Size, class T>
	void _uninitialized_fill_n_aux(ForwardIterator first, Size size, const T& value, _true_type);

	template<class ForwardIterator, class Size, class T>
	void _uninitialized_fill_n_aux(ForwardIterator first, Size size, const T& value, _false_type);

	template<class ForwardIterator, class Size, class Tp, class Tp1>
	inline void _uninitialized_fill_n(ForwardIterator first, Size size, const Tp& value, Tp1*)
	{
		typedef typename _type_traits<Tp1>::is_POD_type isPODType;
		_uninitialized_fill_n_aux(first, last, value, isPODType());
	}

	template<class ForwardIterator, class Size, class T>
	void _uninitialized_fill_n(ForwardIterator first, Size size, const T& value)
	{
		_uninitialized_fill_n(first, last, value, __VALUE_TYPE(first));
	}

	template<class ForwardIterator, class Size, class T>
	void _uninitialized_fill_n_aux(ForwardIterator first, Size size, const T& value, _true_type)
	{
		fill_n(first, size, value);
	}

	template<class ForwardIterator, class Size, class T>
	void _uninitialized_fill_n_aux(ForwardIterator first, Size size, const T& value, _false_type)
	{
		ForwardIterator _cur = first;
		for (; size > 0; --size, ++_cur)
		{
			construct(&*_cur, value);
		}
	}
}