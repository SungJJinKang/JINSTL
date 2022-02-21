#pragma once

#include "JINSTLCore.h"

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
			extern Allocator* GetDefaultAllocator();
			extern Allocator* GlobalAllocator;

			struct DefaultAllocatorToGlobalAllocatorSetter
			{
				DefaultAllocatorToGlobalAllocatorSetter()
				{
					GlobalAllocator = GetDefaultAllocator();
				}
			};
			
			extern inline void InitDefaultAllocatorToGlobalAllocatorSetter()
			{
				static details::DefaultAllocatorToGlobalAllocatorSetter defaultAllocatorToGlobalAllocatorSetter{};
			}
		}

		extern inline Allocator* GetGlobalAllocator();
		extern inline void SetDefaultAllocatorToGlobalAllocator();
		extern inline void SetGlobalAllocator(Allocator* const allocator);

		extern inline void SetGlobalAllocator(Allocator* const allocator)
		{
			JINSTL_ASSERT(allocator != nullptr);

			details::InitDefaultAllocatorToGlobalAllocatorSetter();

			details::GlobalAllocator = allocator;
		}
		extern inline void SetDefaultAllocatorToGlobalAllocator()
		{
			details::GlobalAllocator = details::GetDefaultAllocator();
		}
		extern inline Allocator* GetGlobalAllocator()
		{
			details::InitDefaultAllocatorToGlobalAllocatorSetter();

			return details::GlobalAllocator;
		}
	}
}
