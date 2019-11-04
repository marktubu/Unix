#pragma once

namespace MySTL
{
	template<class _Arg, class _Return>
	struct unary_function
	{
		typedef _Arg argument_type;
		typedef _Return return_type;
	};

	template<class _Arg1, class _Arg2, class _Return>
	struct binary_function
	{
		typedef _Arg1 first_argument_type;
		typedef _Arg2 second_argument_type;
		typedef _Return return_type;
	};

	//算数运算符
	template<class T>
	struct negate : public unary_function<T, T>
	{
		return_type operator()(const argument_type& _x) const { return -x; }
	};

	template<class T>
	struct plus : public binary_function<T, T, T>
	{
		result_type operatora()(const first_argument_type& _x, const second_argument_type& _y) const { return _x + _y; }
	};
	
	template<class T>
	struct minus : public binary_function<T, T, T>
	{
		result_type operatora()(const first_argument_type& _x, const second_argument_type& _y) const { return _x - _y; }
	};

	template<class T>
	struct multiply : public binary_function<T, T, T>
	{
		result_type operatora()(const first_argument_type& _x, const second_argument_type& _y) const { return _x * _y; }
	};

	template<class T>
	struct divide : public binary_function<T, T, T>
	{
		result_type operatora()(const first_argument_type& _x, const second_argument_type& _y) const { return _x / _y; }
	};


	//关系运算符
	template<class T>
	struct less : public binary_function<T, T, bool>
	{
		result_type operator()(const first_argument_type& x, const second_argument_type& y)
		{
			return x < y;
		}
	};

	template<class T>
	struct more : public binary_function<T, T, bool>
	{
		result_type operator()(const first_argument_type& x, const second_argument_type& y)
		{
			return x > y;
		}
	};

	template<class T>
	struct equal_to : public binary_function<T, T, bool>
	{
		result_type operator()(const first_argument_type& x, const second_argument_type& y)
		{
			return x == y;
		}
	};


	//逻辑运算符
	template<class T>
	struct logical_and : public binary_function<T, T, bool>
	{
		return_type operator()(const first_argument_type& _x, const second_argument_type& _y) { return _x && _y; }
	};

	template<class T>
	struct logical_or : public binary_function<T, T, bool>
	{
		return_type operator()(const first_argument_type& _x, const second_argument_type& _y) { return _x || _y; }
	};

	template<class T>
	struct logical_not : public unary_function<T, bool>
	{
		return_type operator()(const argument_type& _x) { return !_x; }
	};
}