#include <Allocator/AllocatorContainer.h>

#include <Allocator/DefaultAllocator.h>

namespace jinStl
{
	namespace allocator
	{
		namespace details
		{
			static DefaultAllocator GlobalDefaultAllocator{};
		}
	}
}

jinStl::allocator::details::AllocatorContainer::AllocatorContainer()
	: DefaultAllocator(&GlobalDefaultAllocator), GlobalAllocator(&GlobalDefaultAllocator)
{
	JINSTL_ASSERT(GlobalAllocator != nullptr);
}

jinStl::allocator::details::AllocatorContainer::~AllocatorContainer()
{
	if (GlobalAllocator != nullptr)
	{
		GlobalAllocator->Clear();

		if(GlobalAllocator != &GlobalDefaultAllocator)
		{
			delete GlobalAllocator;
			GlobalDefaultAllocator.Clear();
		}
	}
}

void jinStl::allocator::details::AllocatorContainer::SetGlobalAllocator(Allocator* const allocator)
{
	JINSTL_ASSERT(allocator != nullptr);

	if (GlobalAllocator != nullptr)
	{
		delete GlobalAllocator;
		GlobalAllocator = nullptr;
	}

	GlobalAllocator = allocator;
}

void jinStl::allocator::details::AllocatorContainer::SetDefaultAllocatorToGlobalAllocator()
{
	JINSTL_ASSERT(DefaultAllocator != nullptr);
	GlobalAllocator = DefaultAllocator;
}
