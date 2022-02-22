#include "Allocator.h"

#include "DefaultAllocator.h"

jinstl::allocator::Allocator* jinstl::allocator::details::GlobalAllocator{ GlobalAllocator };
jinstl::allocator::Allocator* jinstl::allocator::details::GetDefaultAllocator()
{
	static DefaultAllocator GlobalDefaultAllocator{};
	return &GlobalDefaultAllocator;
}
