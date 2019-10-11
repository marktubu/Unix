#pragma once

#include <cstdlib>

namespace MySTL {
	//空间配置器

	class alloc{
	private:
		//8字节对齐
		enum { ALIGN = 8 };
		//空闲链表最大node为128字节
		enum { MAXBYTES = 128 };
		//空闲链表数目
		enum { NFREELISTS = 16 }; //(MAXBYTES / ALIGN)
		enum { NOBJS = 20 };

	private:
		union obj {
			union obj* next;
			char client[1];
		};

		//16个空闲链表的head节点
		static obj* free_list[NFREELISTS];

	private:
		//内存池空闲部分的开始
		static char* start_free;
		//内存池空闲部分的结束
		static char* end_free;
		static size_t heap_size;

	private:
		//8字节对齐
		static size_t ROUND_UP(size_t bytes) {
			return ((bytes+ (size_t)ALIGN - 1) & ~((size_t)ALIGN - 1));
		}

		//获得bytes对应的free_list
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes)+(size_t)ALIGN - 1) / (size_t)ALIGN - 1);
		}

		//某一空闲链表空间不足，从内存池中重新分配
		static void* refill(size_t n);

		//扩展内存池
		static char* chunk_alloc(size_t size, size_t& nobjs);

	public:
		//分配
		static void* allocate(size_t bytes);
		//释放
		static void deallocate(void* ptr, size_t bytes);
		//重新分配
		static void* reallocate(void* ptr, size_t old_sz, size_t new_sz);
	};
}