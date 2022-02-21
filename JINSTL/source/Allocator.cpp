#include <Allocator.h>

#include <Allocator/DefaultAllocator.h>

jinStl::allocator::details::AllocatorContainer jinStl::allocator::details::InternalAllocatorContainer{new jinStl::DefaultAllocator()};

void jinStl::allocator::SetGlobalAllocator(Allocator* const allocator)
{
	JINSTL_ASSERT(allocator != nullptr);

	if(jinStl::allocator::details::InternalAllocatorContainer.GlobalAllocator != nullptr)
	{
		delete jinStl::allocator::details::InternalAllocatorContainer.GlobalAllocator;
		jinStl::allocator::details::InternalAllocatorContainer.GlobalAllocator = nullptr;
	}

	jinStl::allocator::details::InternalAllocatorContainer.GlobalAllocator = allocator;
}