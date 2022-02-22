#pragma once

#include "Allocator.h"

namespace jinstl
{
	class AllocBase
	{
	private:

		allocator::Allocator* mAllocator;

	protected:

		void* Allocate(const size_t size)
		{
			void* allocatedPtr = mAllocator->Allocate(size);
			JINSTL_ASSERT(allocatedPtr != nullptr);

			return allocatedPtr;
		}

		void DeAllocate(void* const ptr)
		{
			mAllocator->DeAllocate(reinterpret_cast<char*>(ptr));
		}

		allocator::Allocator* ChangeAllocator(allocator::Allocator* const newAllocator)
		{
			JINSTL_ASSERT(newAllocator != nullptr);

			allocator::Allocator* const originalAllocator = mAllocator;

			mAllocator = newAllocator;

			return originalAllocator;
		}

	public:

		AllocBase()
			: mAllocator(allocator::GetGlobalAllocator())
		{
			JINSTL_ASSERT(mAllocator != nullptr);
		}
		AllocBase(allocator::Allocator* const allocator)
			: mAllocator(allocator)
		{
			JINSTL_ASSERT(mAllocator != nullptr);
		}
	};
}