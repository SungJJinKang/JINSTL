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
			if(size != 0)
			{
				void* allocatedPtr = mAllocator->Allocate(size);
				JINSTL_ASSERT(allocatedPtr != nullptr);

				return allocatedPtr;
			}
			else
			{
				return nullptr;
			}			
		}

		void DeAllocate(void* const ptr)
		{
			if(ptr != nullptr)
			{
				mAllocator->DeAllocate(reinterpret_cast<char*>(ptr));
			}			
		}

		allocator::Allocator* ChangeAllocator(allocator::Allocator* const newAllocator)
		{
			JINSTL_ASSERT(newAllocator != nullptr);

			allocator::Allocator* const originalAllocator = mAllocator;

			mAllocator = newAllocator;

			return originalAllocator;
		}

		allocator::Allocator* GetAllocator() const
		{
			return mAllocator;
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