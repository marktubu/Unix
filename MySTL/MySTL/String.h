#pragma once

#include <iostream>
#include <cstring>
#include <type_traits>

#include "Allocator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"
#include "Utility.h"

namespace MySTL
{
	class string
	{
	public:
		typedef char								value_type;
		typedef char* pointer;
		typedef const char* const_pointer;
		typedef char* iterator;
		typedef const iterator						const_iterator;
		typedef reverse_iterator_t<iterator>		reverse_iterator;
		typedef reverse_iterator_t<const_iterator>	const_reverse_iterator;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef size_t								size_type;
		typedef ptrdiff_t							difference_type;

		//1.This value, when used as the value for a len (or sublen) parameter in string's member functions, means "until the end of the string".
		//2.As a return value, it is usually used to indicate no matches.
		//it usually acts as a symbol or something. its actual value is not very important.
		static const size_type npos = -1;

	private:
		pointer _start;
		pointer _finish;
		pointer _end_of_storage;

		typedef MySTL::allocator<value_type> data_allocator;

	public:
		string() :_start(0), _finish(0), _end_of_storage(0) {}
		string(const string& s);
		string(string&& s);
		string(const string& s, size_type pos, size_type len = npos);
		string(const char* s);
		string(const char* s, size_type n);
		string(size_type n, value_type c);

		template<class InputIterator>
		string(InputIterator first, InputIterator last);

		string& operator=(const string& s);
		string& operator=(string&& s);
		string& operator=(const char* s);
		string& operator=(char c);

		~string();

	public:
		iterator begin() { return _start; }
		iterator end() { return _finish; }
		const_iterator begin()const { return _start; }
		const_iterator end()const { return _finish; }
		reverse_iterator rbegin() { return reverse_iterator(_finish); }
		reverse_iterator rend() { return reverse_iterator(_start); }
		const_reverse_iterator rbegin()const { return reverse_iterator(_finish); }
		const_reverse_iterator rend()const { return reverse_iterator(_start); }
		const_iterator cbegin() const { return _start; }
		const_iterator cend() const { return _finish; }
		const_reverse_iterator crbegin() const { return const_reverse_iterator(_finish); }
		const_reverse_iterator crend() const { return const_reverse_iterator(_start); }

		size_type size()const { return _finish - _start; }
		size_type length()const { return size(); }
		size_type capacity()const { return _end_of_storage - _start; }

	};

	template<class InputIterator>
	inline string::string(InputIterator first, InputIterator last)
	{
	}
}