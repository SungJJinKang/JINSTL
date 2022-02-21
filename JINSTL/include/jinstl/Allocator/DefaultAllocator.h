#pragma once
#include "../Allocator.h"

namespace jinStl
{
	namespace allocator
	{
		class DefaultAllocator : public jinStl::allocator::Allocator
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

			inline void do_clear() final
			{
				
			}
		};
	}
}