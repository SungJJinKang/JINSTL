#include "jinstl/Allocator.h"

#include "jinstl/DefaultAllocator.h"

jinstl::allocator::Allocator* jinstl::allocator::details::GlobalAllocator{ GlobalAllocator };
jinstl::allocator::Allocator* jinstl::allocator::details::GetDefaultAllocator()
{
	static DefaultAllocator GlobalDefaultAllocator{};
	return &GlobalDefaultAllocator;
}
