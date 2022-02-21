#pragma once

#include "Core.h"
#include "Allocator/AllocatorContainer.h"

namespace jinStl
{
	namespace allocator
	{
		class Allocator
		{

		protected:

			virtual void* do_Alloc(const size_t size) = 0;
			virtual void do_DeAlloc(char* const ptr) = 0;
			virtual void do_clear() = 0;
		public:

			Allocator() = default;
			Allocator(const Allocator&) = delete;
			Allocator(Allocator&&) noexcept = delete;
			Allocator& operator=(const Allocator&) = delete;
			Allocator& operator=(Allocator&&) noexcept = delete;
			virtual ~Allocator() = default;

			inline void* Allocate(const size_t size)
			{
				void* allocatedPtr = do_Alloc(size);
				JINSTL_ASSERT(allocatedPtr != nullptr);

				return allocatedPtr;
			}
			inline void DeAllocate(void* const ptr)
			{
				do_DeAlloc(reinterpret_cast<char*>(ptr));
			}
			inline void Clear()
			{
				do_clear();
			}
		};


		namespace details
		{
			extern AllocatorContainer InternalAllocatorContainer;
		}

		extern void SetGlobalAllocator(Allocator* const allocator);
		extern void SetDefaultAllocatorToGlobalAllocator();
		extern inline Allocator* GetSetGlobalAllocator()
		{
			JINSTL_ASSERT(details::InternalAllocatorContainer.GlobalAllocator != nullptr);
			return details::InternalAllocatorContainer.GlobalAllocator;
		}
	}
}
