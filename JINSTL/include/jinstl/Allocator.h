#pragma once

#include "Core.h"

namespace jinStl
{
	class Allocator
	{

	protected:

		virtual void* do_Alloc(const size_t size) = 0;
		virtual void do_DeAlloc(char* const ptr) = 0;

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
	};

	namespace allocator
	{
		namespace details
		{
			class AllocatorContainer
			{
			public:

				Allocator* GlobalAllocator;

				AllocatorContainer(Allocator* const defaultAllocator)
					:GlobalAllocator(defaultAllocator)
				{
					JINSTL_ASSERT(GlobalAllocator != nullptr);
				}
				~AllocatorContainer()
				{
					if (GlobalAllocator != nullptr)
					{
						delete GlobalAllocator;
					}
				}
			};

			extern AllocatorContainer InternalAllocatorContainer;
		}

		extern void SetGlobalAllocator(Allocator* const allocator);
		extern inline Allocator* GetSetGlobalAllocator()
		{
			JINSTL_ASSERT(details::InternalAllocatorContainer.GlobalAllocator != nullptr);
			return details::InternalAllocatorContainer.GlobalAllocator;
		}
	}

}