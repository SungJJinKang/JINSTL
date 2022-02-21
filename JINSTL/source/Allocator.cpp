#include "Allocator.h"

#include "DefaultAllocator.h"

jinStl::allocator::Allocator* jinStl::allocator::details::GlobalAllocator{ GlobalAllocator };
jinStl::allocator::Allocator* jinStl::allocator::details::GetDefaultAllocator()
{
	static DefaultAllocator GlobalDefaultAllocator{};
	return &GlobalDefaultAllocator;
}
