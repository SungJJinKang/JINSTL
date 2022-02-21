#include <Allocator.h>

#include <Allocator/DefaultAllocator.h>

jinStl::allocator::details::AllocatorContainer jinStl::allocator::details::InternalAllocatorContainer{};

void jinStl::allocator::SetGlobalAllocator(Allocator* const allocator)
{
	details::InternalAllocatorContainer.SetGlobalAllocator(allocator);
}

void jinStl::allocator::SetDefaultAllocatorToGlobalAllocator()
{
	details::InternalAllocatorContainer.SetDefaultAllocatorToGlobalAllocator();
}
