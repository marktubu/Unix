#pragma once

#include "Vector.h"

namespace MySTL
{
	template<class T, class Container = MySTL::vector<T>>
	class stack
	{
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::reference reference;
		typedef typename Container::size_type size_type;
		typedef Container container_type;

	private:
		container_type _container;

	public:
		explicit stack(const container_type& container = container_type()) :_container(container) {}
		size_type size() const { return _container.size(); }
		value_type& top() { return _container.back(); }
		const value_type& top() const { return _container.back(); }
		void push(const value_type& val) { _container.push_back(val); }
		void pop() { _container.pop_back(); }
		void swap(stack& x) { MySTL::swap(_container, x._container); }

	public:
		template<class T, class Container>
		friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
		template<class T, class Container>
		friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
		template<class T,class Container>
		friend void swap(stack<T, Container>& x, stack<T, Container>& y);
	};
	template<class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs._container == rhs._container;
	}
	template<class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return lhs._container != rhs._container;
	}
	template<class T, class Container>
	void swap(stack<T, Container>& x, stack<T, Container>& y)
	{
		x.swap(y);
	}
}