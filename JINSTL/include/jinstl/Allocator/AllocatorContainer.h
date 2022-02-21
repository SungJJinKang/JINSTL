#pragma once

namespace jinStl
{
	namespace allocator
	{
		class Allocator;
		namespace details
		{
			class AllocatorContainer
			{
				Allocator* DefaultAllocator;

			public:

				Allocator* GlobalAllocator;

				AllocatorContainer();
				~AllocatorContainer();

				void SetGlobalAllocator(Allocator* const allocator);
				void SetDefaultAllocatorToGlobalAllocator();
			};
		}
	}
}
