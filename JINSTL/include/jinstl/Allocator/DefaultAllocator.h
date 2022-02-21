#pragma once
#include "../Allocator.h"

namespace jinStl
{
	class DefaultAllocator : public Allocator
	{
	protected:
		inline void* do_Alloc(const size_t size) final
		{
			return new char[size];
		}
		inline void do_DeAlloc(char* const ptr) final
		{
			delete ptr;
		}
	};
}