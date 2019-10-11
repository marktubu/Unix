#include "../Alloc.h"

namespace MySTL
{
	char* alloc::start_free = 0;
	char* alloc::end_free = 0;
	size_t alloc::heap_size = 0;

	alloc::obj* alloc::free_list[NFREELISTS] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	};

	void* alloc::allocate(size_t bytes) 
	{
		if (bytes > (size_t)MAXBYTES)
		{
			return malloc(bytes);
		}

		size_t index = FREELIST_INDEX(bytes);
		alloc::obj* list = free_list[index];
		if (list)
		{
			free_list[index] = list->next;
			return list;
		}
		else
		{
			return refill(ROUND_UP(bytes));
		}
	}

	//如果大于MAXBYTES则直接free。
	//如果小于MAXBYTES则将对应的node重新加入空闲链表
	void alloc::deallocate(void* ptr, size_t bytes)
	{
		if (bytes > (size_t)MAXBYTES)
		{
			free(ptr);
		}
		else
		{
			size_t index = FREELIST_INDEX(bytes);
			obj* node = static_cast<obj*>(ptr);
			node->next = free_list[index];
			free_list[index] = node;
		}
	}

	void* alloc::reallocate(void* ptr, size_t old_sz, size_t new_sz)
	{
		deallocate(ptr, old_sz);
		ptr = allocate(new_sz);

		return ptr;
	}

	void* alloc::refill(size_t bytes)
	{
		size_t nobjs = (size_t)NOBJS;
		char* chunk = chunk_alloc(bytes, nobjs);

		obj** my_free_list = 0;
		obj* current_obj = 0;
		obj* next_obj = 0;
		obj* result = 0;

		if (nobjs == 1)
		{
			return chunk;
		}
		else
		{
			my_free_list = free_list + FREELIST_INDEX(bytes);
			//此时的my_free_list指向分配的chunk内存的index为1的部分
			*my_free_list = next_obj = (obj*)(chunk + bytes);
			result = (obj*)chunk;

			for (size_t i = 1;; i++)
			{
				current_obj = next_obj;
				next_obj = (obj*)((char*)next_obj + bytes);
				if (i == nobjs - 1)
				{
					current_obj->next = 0;
					break;
				}
				else
				{
					current_obj = next_obj;
				}
			}

			return result;
		}
	}

	char* alloc::chunk_alloc(size_t bytes, size_t& nobjs)
	{
		char* result = 0;
		size_t total_bytes = bytes * nobjs;
		size_t bytes_left = end_free - start_free;

		//完全可以满意内存要求的情况
		if (bytes_left >= total_bytes)
		{
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//部分满足内存要求的情况
		else if (bytes_left >= bytes)
		{
			result = start_free;
			nobjs = (size_t) (bytes_left / bytes);
			total_bytes = bytes * nobjs;
			start_free += total_bytes;
			return result;
		}
		//完全不满足内存要求的情况
		else
		{
			//尝试将剩余的空闲字节加入到空闲链表中
			if (bytes_left > 0)
			{
				obj** my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->next = *my_free_list;
				*my_free_list = (obj*)start_free;
			}

			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			start_free = (char*)malloc(bytes_to_get);
			//malloc失败，证明heap不足，尝试从空闲链表中寻找足够大的空间
			if (!start_free)
			{
				for (size_t i = bytes; i <= MAXBYTES; i += ALIGN)
				{
					obj** my_free_list = free_list + FREELIST_INDEX(i);
					obj* p = *my_free_list;
					if (p != 0)
					{
						//p!=0说明找到空间可以分配
						*my_free_list = p->next;
						start_free = (char*)p;
						end_free = start_free + i;
						//递归调用以调整nobjs的值
						return chunk_alloc(bytes, nobjs);
					}
				}

				end_free = 0;
				return nullptr;
			}

			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			//递归调用以调整nobjs的值
			return chunk_alloc(bytes, nobjs);
		}
	}
}