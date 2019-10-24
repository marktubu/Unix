#pragma once

#include <utility>

#include "Ref.h"

namespace MySTL
{
	template<class _T>
	class cow_ptr;

	template<class T>
	struct default_delete
	{
		void operator()(T* ptr) { if (ptr) delete ptr; }
	};

	template<class T>
	struct default_delete<T[]>
	{
		void operator()(T* ptr) { if (ptr) { delete[] ptr; } }
	};

	template<class T,class D = default_delete<T>>
	class unique_ptr
	{
	public:
		typedef T element_type;
		typedef D deleter_type;
		typedef element_type* pointer;
	public:
		explicit unique_ptr(T* data = nullptr) :_data(data) {}
		unique_ptr(T* data, deleter_type del) :_data(data), deleter(del) {}
		
		//通过右值引用作为构造函数的参数
		unique_ptr(unique_ptr&& up) :_data(nullptr)
		{
			MySTL::swap(_data, up.data);
		}

		//通过右值引用赋值
		unique_ptr& operator=(unique_ptr&& up)
		{
			if (&up != this)
			{
				clean();
				MySTL::swap(*this, up);
			}
			return *this;
		}

		//禁用拷贝构造
		unique_ptr(const unique_ptr&) = delete;
		//禁用赋值
		unique_ptr& operator = (const unique_ptr&) = delete;

		~unique_ptr() { clean(); }

		const pointer get()const { return _data; }
		pointer get() { return _data; }
		deleter_type& get_deleter() { return deleter; }
		const deleter_type& get_deleter()const { return deleter; }

		//可实现该类型对象到bool类型的隐式转换
		operator bool()const { return get() != nullptr; }

		//释放unique_ptr指向的对象
		pointer release()
		{
			T* p = nullptr;
			MySTL::swap(p, _data);
			return p;
		}

		//重置unique_ptr指向的对象
		void reset(pointer p = pointer())
		{
			clean();
			_data = p;
		}

		void swap(unique_ptr& up) { MySTL::swap(_data, up._data); }

		//解引用获取指向的对象
		const element_type& operator*()const { return *_data; }
		//获取对象的原始指针
		const pointer operator->()const { return _data; }

		//解引用获取指向的对象
		element_type& operator*(){ return *_data; }
		//获取对象的原始指针
		pointer operator->(){ return _data; }
	private:
		inline void clean()
		{
			deleter(_data);
			_data = nullptr;
		}

	private:
		pointer _data;
		deleter_type deleter;
	};

	template <class T, class D>
	void swap(unique_ptr<T, D>& x, unique_ptr<T, D>& y) {
		x.swap(y);
	}

	//两个unique_ptr比较
	template <class T1, class D1, class T2, class D2>
	bool operator == (const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
		return lhs.get() == rhs.get();
	}

	//空指针与unique_ptr比较
	template <class T, class D>
	bool operator == (const unique_ptr<T, D>& up, nullptr_t p) {
		return up.get() == p;
	}

	//空指针与unique_ptr比较
	template <class T, class D>
	bool operator == (nullptr_t p, const unique_ptr<T, D>& up) {
		return up.get() == p;
	}

	//两个unique_ptr比较
	template <class T1, class D1, class T2, class D2>
	bool operator != (const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
		return !(lhs == rhs);
	}

	//空指针与unique_ptr比较
	template <class T, class D>
	bool operator != (const unique_ptr<T, D>& up, nullptr_t p) {
		return up.get() != p;
	}

	//空指针与unique_ptr比较
	template <class T, class D>
	bool operator != (nullptr_t p, const unique_ptr<T, D>& up) {
		return up.get() != p;
	}

	template <class T, class... Args>
	unique_ptr<T> make_unique(Args&& ... args) {
		return unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
}