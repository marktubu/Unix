#pragma once

namespace MySTL
{
	template<class T, class Alloc>
	vector<T, Alloc>::~vector() 
	{
		destroy_and_deallocate_all();
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n) 
	{
		allocate_and_fill_n(n, value_type());
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n, const value_type& value) 
	{
		allocate_and_fill_n(n, value);
	}

	template<class T, class Alloc>
	template<class InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last) 
	{
		//处理指针和数字间的区别的函数
		vector_aux(first, last, typename std::is_integral<InputIterator>::type());
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(const vector<T, Alloc>& v)
	{
		allocate_and_copy(v._start, v._finish);
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(vector<T, Alloc>&& v)
	{
		_start = v._start;
		_finish = v._finish;
		_end_of_storage = v._end_of_storage;
		v._start = v._finish = v._end_of_storage = 0;
	}

	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator = (const vector<T, Alloc>& v)
	{
		if (this != &v) 
		{
			allocate_and_copy(v._start, v._finish);
		}
		return *this;
	}

	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator = (vector<T, Alloc>&& v)
	{
		if (this != &v) 
		{
			destroy_and_deallocate_all();
			_start = v._start;
			_finish = v._finish;
			_end_of_storage = v._end_of_storage;
			v._start = v._finish = v._end_of_storage = 0;
		}
		return *this;
	}


	template<class T,class Alloc>
	void vector<T, Alloc>::resize(size_type n, value_type val = value_type())
	{
		if (n < size())
		{
			data_allocator::destroy(_start + n, _finish);
			_finish = _start + n;
		}
		else if (n > size() && n <= capacity())
		{
			auto len_of_insert = n - size();
			_finish = MySTL::uninitialized_fill_n(_finish, len_of_insert, val);
		}
		else if (n > capacity())
		{
			auto len_of_insert = n - size();
			T* new_start = data_allocator::allocate(get_new_capacity(len_of_insert));
			T* new_finish = MySTL::uninitialized_copy(begin(), end(), new_start);
			new_finish = MySTL::uninitialized_fill_n(new_finish, len_of_insert, val);

			destroy_and_deallocate_all();

			_start = new_start;
			_finish = new_finish;
			_end_of_storage = _start + n;
		}
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::reserve(size_type n)
	{
		if (n <= capacity())
			return;
		T* new_start = data_allocator::allocate(n);
		T* new_finish = MySTL::uninitialized_copy(begin(), end(), new_start);

		destroy_and_deallocate_all();

		_start = new_start;
		_finish = new_finish;
		_end_of_storage = _start + n;
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
	{
		return erase(position, position + 1);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
	{
		difference_type len_of_tail = end() - last;
		difference_type len_of_removed = last - first;
		_finish = _finish - len_of_removed;
		for (; len_of_tail != 0; --len_of_tail)
		{
			auto tmp = (last - len_of_removed);
			*tmp = *(last++);
		}

		return (first);
	}

	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::reallocate_and_copy(iterator position, InputIterator first, InputIterator last)
	{
		difference_type new_capacity = get_new_capacity(last - first);

		T* new_start - data_allocator::allocate(new_capacity);
		T* new_end_of_storage = new_start + new_capacity;
		T* new_finish = MySTL::uninitialized_copy(begin(), position, new_start);
		new_finish = MySTL::uninitialized_copy(first, last, new_finish);
		new_finish = MySTL::uninitialized_copy(position, end(), new_finish);

		destroy_and_deallocate_all();

		_start = new_start;
		_finish = new_finish;
		_end_of_storage = new_end_of_storage;
	}

	template<class T,class Alloc>
	void vector<T, Alloc>::reallocate_and_fill_n(iterator position, const size_type& n, const value_type& val)
	{
		difference_type new_capacity = get_new_capacity(n);

		T* new_start - data_allocator::allocate(new_capacity);
		T* new_end_of_storage = new_start + new_capacity;
		T* new_finish = MySTL::uninitialized_copy(begin(), position, new_start);
		new_finish = MySTL::uninitialized_fill_n(new_finish, n, val);
		new_finish = MySTL::uninitialized_copy(position, end(), new_finish);

		destroy_and_deallocate_all();

		_start = new_start;
		_finish = new_finish;
		_end_of_storage = new_end_of_storage;
	}

	template<class T, class Alloc>
	template<class Integer>
	void vector<T, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type)
	{
		difference_type spaceLeft = _end_of_storage - _finish;
		difference_type spaceNeed = distance(first, last);

		if (spaceLeft >= spaceNeed)
		{
			if (_finish - position > spaceNeed)
			{
				MySTL::uninitialized_copy(_finish - spaceNeed, _finish, _finish);
				std::copy_backward(position, _finish - spaceNeed, _finish);
				std::copy(first, last, position);
			}
			else
			{
				iterator tmp = MySTL::uninitialized_copy(first + (_finish - position), last, _finish);
				MySTL::uninitilaized_copy(position, _finish, tmp);
				std::copy(first, first + (_finish - position), position);
			}
			_finish += spaceNeed;
		}
		else
		{
			reallocate_and_copy(position, first, last);
		}
	}


	//position : 插入的位置
	//n : 插入数量
	//value : 插入的值
	template<class T, class Alloc>
	template<class Integer>
	void vector<T, Alloc>::insert_aux(iterator position, Integer n, const value_type& value, std::true_type)
	{
		assert(n != 0);
		difference_type spaceLeft = _end_of_storage - _finish;
		difference_type spaceNeed = n;
		if (spaceLeft > spaceNeed)
		{
			auto insertpos = end() - 1;
			for (; insertpos - position >= 0; --insertpos)
			{
				construct(insertpos + spaceNeed, *insertpos);
			}

			MySTL::uninitialized_fill_n(position, n, value);
			_finish += spaceNeed;
		}
		else
		{
			reallocate_and_fill_n(position, n, value);
		}
	}

	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last) {
		insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::insert(iterator position, const size_type& n, const value_type& val) {
		insert_aux(position, n, val, typename std::is_integral<size_type>::type());
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type& val) {
		const auto index = position - begin();
		insert(position, 1, val);
		return begin() + index;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type& value) {
		insert(end(), value);
	}

	template<class T, class Alloc>
	bool vector<T, Alloc>::operator==(const vector<T, Alloc>& v)const
	{
		if (size() != v.size())
		{
			return false;
		}
		else
		{
			auto ptr1 = _start;
			auto ptr2 = v._start;
			for (; ptr1 != _finish && ptr2 != v._finish; ++ptr1, ++ptr2)
			{
				if (*ptr1 != *ptr2)
					return false;
			}
			return true;
		}
	}

	template<class T,class Alloc>
	bool vector<T, Alloc>::operator!=(const vector<T, Alloc>& v)const
	{
		return !(*this == v);
	}

	template<class T, class Alloc>
	bool vector<T, Alloc>::operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2)
	{
		return v1.operator==(v2);
	}

	template<class T,class Alloc>
	bool operator != (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2)
	{
		return !(v1 == v2);
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::shrink_to_fit()
	{
		T* t = (T*)data_allocator::allocate(size());
		_finish = MySTL::uninitialized_copy(_start, _finish, t);
		data_allocator::deallocate(_start, capacity());
		_start = t;
		_end_of_storage = _finish;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::clear()
	{
		data_allocator::destroy(_start, _finish);
		_finish = _start;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::swap(vector& v)
	{
		if (this != &v)
		{
			MySTL::swap(_start, v._start);
			MySTL::swap(_finish, v._finish);
			MySTL::swap(_end_of_storage, v._end_of_storage);
		}
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::pop_back()
	{
		--_finish;
		data_allocator::destroy(_finish);
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::destroy_and_deallocate_all()
	{
		if (capacity() != 0)
		{
			data_allocator::destroy(_start, _finish);
			data_allocator::deallocate(_start, capacity());
		}
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::allocate_and_fill_n(const size_type n, const value_type& value)
	{
		_start = data_allocator::allocate(n);
		MySTL::uninitialized_fill_n(_start, n, value);
		_end_of_storage = _finish = _start + n;
	}
	
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::allocate_and_copy(InputIterator first, InputIterator last)
	{
		_start = data_allocator::allocate(last - first);
		_finish = MySTL::uninitialized_copy(first, last, _start);
		_end_of_storage = _finish;
	}

	template<class T,class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::vector_aux(InputIterator first, InputIterator last, std::false_type)
	{
		allocate_and_copy(first, last);
	}

	template<class T,class Alloc>
	template<class Integer>
	void vector<T, Alloc>::vector_aux(Integer n, const value_type& value, std::true_type)
	{
		allocate_and_fill_n(n, value);
	}

	template<class T,class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::get_new_capacity(size_type len)const
	{
		size_type old_capacity = _end_of_storage - _start;
		auto res = MySTL::max(old_capacity, len);
		size_type new_capacity = old_capacity != 0 ? (old_capacity + res) : len;
		return new_capacity;
	}
}