#pragma once
#include "../Allocator.h"

#include <cstdlib>

namespace jinStl
{
	namespace allocator
	{
		class DefaultAllocator : public jinStl::allocator::Allocator
		{
		protected:
			inline void* do_Alloc(const size_t size) final
			{
				return std::malloc(size);
			}
			inline void do_DeAlloc(char* const ptr) final
			{
				std::free(ptr);
			}

			inline void do_clear() final
			{
				
			}
		};
	}
}