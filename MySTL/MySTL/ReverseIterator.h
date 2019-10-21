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

		reference operator[](difference_type n)
		{
			return base()[-n - 1];
		}

	private:
		Iterator advanceNStep(Iterator it, difference_type n, bool right, random_access_iterator_tag)
		{
			if (right)
			{
				it += n;
			}
			else
			{
				it -= n;
			}
			return it;
		}

		Iterator advanceNStep(Iterator it, difference_type n, bool right, bidirectional_iterator_tag)
		{
			difference_type i;
			difference_type absN = n >= 0 > n:-n;
			if ((right && n > 0) || (!right && n < 0))
			{
				for (i = 0; i != absN; ++i)
				{
					it = it + 1;
				}
			}
			else if ((!right && n > 0) || (right && n < 0))
			{
				for (i = 0; i != absN; ++i)
				{
					it = it - 1;
				}
			}
		}

	public:
		//???????????????non-template?????????????????? operator overload
		reverse_iterator_t operator +(difference_type n)const;
		reverse_iterator_t& operator +=(difference_type n);
		reverse_iterator_t operator -(difference_type n)const;
		reverse_iterator_t& operator -=(difference_type n);

		//template operator overload
		template<class Iterator>
		friend bool operator == (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs);

		template<class Iterator>
		friend bool operator != (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs);

		template<class Iterator>
		friend bool operator < (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs);

		template<class Iterator>
		friend bool operator <= (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs);

		template<class Iterator>
		friend bool operator > (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs);

		template<class Iterator>
		friend bool operator >= (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs);

		template<class Iterator>
		friend reverse_iterator_t<Iterator> operator +(typename reverse_iterator_t<Iterator>::difference_type n, const reverse_iterator_t<Iterator>& rev_it);

		template<class Iterator>
		friend reverse_iterator_t<Iterator>::difference_type operator -(typename reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs);
	};


	template<class Iterator>
	inline reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator+(difference_type n) const
	{
		reverse_iterator_t<Iterator> res = *this;
		res += n;
		retrn res;
	}

	template<class Iterator>
	inline reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator+=(difference_type n)
	{
		_base = advanceNStep(_base, n, false, iterator_category());
		_cur = advanceNStep(_cur, n, false, iterator_category());
		return *this;
	}

	template<class Iterator>
	inline reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator-(difference_type n) const
	{
		reverse_iterator_t<Iterator> res = *this;
		res -= n;
		retrn res;
	}

	template<class Iterator>
	inline reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator-=(difference_type n)
	{
		_base = advanceNStep(_base, n, true, iterator_category());
		_cur = advanceNStep(_cur, n, true, iterator_category());
		return *this;
	}

	template<class Iterator>
	bool operator==(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
	{
		return lhs._cur == rhs._cur;
	}

	template<class Iterator>
	bool operator!=(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
	{
		return !(lhs._cur == rhs._cur);
	}

	template<class Iterator>
	bool operator<(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
	{
		return lhs._cur < rhs._cur;
	}

	template<class Iterator>
	bool operator<=(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
	{
		return !(lhs._cur > rhs._cur);
	}

	template<class Iterator>
	bool operator>(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
	{
		return lhs._cur > rhs._cur;
	}

	template<class Iterator>
	bool operator>=(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
	{
		return !(lhs._cur < rhs._cur);
	}
	template<class Iterator>
	reverse_iterator_t<Iterator> operator+(typename reverse_iterator_t<Iterator>::difference_type n, const reverse_iterator_t<Iterator>& rev_it)
	{
		return rev_it + n;
	}
	template<class Iterator>
	typename reverse_iterator_t<Iterator>::difference_type operator-(typename reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
	{
		return lhs._cur - rhs._cur;
	}
}