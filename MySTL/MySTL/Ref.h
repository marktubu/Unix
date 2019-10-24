#pragma once

#include <atomic>
#include <functional>
#include <memory>

namespace MySTL
{
	namespace Impl
	{
		template<class T>
		struct _default_delete
		{
			void operator()(T* ptr) { if (ptr) delete ptr; }
		};

		template<class T>
		struct ref_t
		{
			//std::function<void(T*)> 其中void(T*)中的void表示返回值，T*表示函数参数
			using deleter_type = std::function<void(T*)>;

			//类型为size_t的原子类型
			std::atomic<size_t> _ncount;
			T* _data;
			deleter_type _deleter;

			explicit ref_t(T* p = nullptr, deleter_type pfunc = deleter_type(_default_delete<T>())) :_ncount(0), _data(p), _deleter(pfunc)
			{
				if (_data)
					_ncount = 1;
			}

			ref_t(const ref_t&) = delete;
			ref_t& operator = (const ref_t&) = delete;

			~ref_t()
			{
				--ncount;
				if (_ncount == 0)
				{
					_deleter(_data);
				}
			}

			size_t count()const { return _ncount.load(); }
			T* get_data()const { return _data; }

			ref_t& operator++()
			{
				++_ncount;
				return *this;
			}

			ref_t operator++(int)
			{
				auto t = *this;
				++* this;
				return t;
			}

			ref_t& operator--()
			{
				--_ncount;
				return *this;
			}

			ref_t operator--(int)
			{
				auto t = *this;
				--* this;
				return t;
			}
		};

		template<class T>
		bool operator==(const ref_t<T>& lhs, const ref_t<T>& rhs)
		{
			return lhs.get_data() == rhs.get_data();
		}

		template<class T>
		bool operator!=(const ref_t<T>& lhs, const ref_t<T>& rhs)
		{
			return !(lhs == rhs);
		}
	}
}