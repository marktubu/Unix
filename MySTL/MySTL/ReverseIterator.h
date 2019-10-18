#pragma once

#include "Iterator.h"

namespace MySTL
{
	template<class Iterator>
	class reverse_iterator_t
	{
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef const pointer const_pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef const reference const_reference;

	private:
		Iterator _base;
		Iterator _cur;
	public:
		//constructor, init _base and _cur to nullptr
		reverse_iterator_t() :_base(0), _cur(0) {}

		//explicit constructor
		explicit reverse_iterator_t(const iterator_type& it) :_base(it) 
		{
			auto tmp = it;
			_cur = --tmp;
		}

		template<class Iter>
		reverse_iterator_t(const reverse_iterator_t<Iter>& rev_it)
		{
			_base = (iterator_type)rev_it.base();
			auto tmp = _base;
			_cur = --tmp;
		}

		iterator_type base() { return _base; }
		reference operator*() { return (*_cur); }
		const_reference operator*()const { return (*_cur); }
		pointer operator->() { return &(operator*()); }
		const_pointer operator->()const { return &(operator*()); }

		reverse_iterator_t& operator ++()
		{
			--_base;
			--_cur;
			return *this;
		}

		reverse_iterator_t& operator ++(int)
		{
			reverse_iterator_t tmp = *this;
			++(*this);
			return tmp;
		}

		reverse_iterator_t& operator--()
		{
			++_base;
			++_cur;
			return *this;
		}

		reverse_iterator_t& operator --(int)
		{
			reverse_iterator_t tmp = *this;
			--(*this);
			return tmp;
		}
	};
}