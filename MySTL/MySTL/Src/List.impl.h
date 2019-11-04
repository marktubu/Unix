#pragma once

#include "..//List.h"

namespace MySTL
{
	namespace Impl
	{
		template<class T>
		list_iterator<T>& list_iterator<T>::operator++()
		{
			p = p->next;
			return *this;
		}

		template<class T>
		list_iterator<T> list_iterator<T>::operator++(int)
		{
			list_iterator<T> tmp(*this);
			operator++();
			return tmp;
		}

		template<class T>
		list_iterator<T>& list_iterator<T>::operator--()
		{
			p = p->prev;
			return *this;
		}

		template<class T>
		list_iterator<T> list_iterator<T>::operator--(int)
		{
			list_iterator<T> tmp(*this);
			operator--();
			return tmp;
		}

		template<class T>
		bool operator==(const list_iterator<T>& lhs, const list_iterator<T>& rhs)
		{
			return lhs.p == rhs.p;
		}

		template<class T>
		bool operator!=(const list_iterator<T>& lhs, const list_iterator<T>& rhs)
		{
			return !(lhs == rhs);
		}
	}
}