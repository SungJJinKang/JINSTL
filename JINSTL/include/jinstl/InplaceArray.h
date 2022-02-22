#pragma once

#include <type_traits>

#include "AllocBase.h"
#include "Allocator.h"

namespace jinstl
{
	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	class InplaceArray : public AllocBase
	{
	public:

		using sizeType = size_t;
		using valueType = ELEMENT_TYPE;
		using reference = ELEMENT_TYPE&;
		using const_reference = const ELEMENT_TYPE&;
		using pointer = ELEMENT_TYPE*;
		using const_pointer = const ELEMENT_TYPE*;

	private:

		ELEMENT_TYPE mLocalBuffer[LOCAL_BUFFER_ELEMENT_COUNT];

		ELEMENT_TYPE* mBufferBegin;
		ELEMENT_TYPE* mBufferEnd;
		ELEMENT_TYPE* mBufferCapacityEnd;

	private:

		void Destroy();
		void NullifyBufferPtr();
		void CapacityResizeGrow(const sizeType size);
		void CapacityResizeShrink(const sizeType size);

		void Expand();

	public:

		InplaceArray();
		InplaceArray(allocator::Allocator* const allocator);
		~InplaceArray();
		InplaceArray(const InplaceArray& arr);
		InplaceArray(InplaceArray&& arr) noexcept;
		InplaceArray& operator=(const InplaceArray& arr);
		InplaceArray& operator=(InplaceArray&& arr) noexcept;
		void Reserve(const sizeType size);
		void PushBack(const ELEMENT_TYPE& element);
		void PushBack(ELEMENT_TYPE&& element);
		void PushBackUnInitialized();
		void PopBack();
		template<typename... ARGS>
		void EmplaceBack(ARGS&&... args);
		bool Empty() const;
		typename sizeType Count() const;
		typename sizeType Capacity() const;
		typename reference operator[](const sizeType index);
		typename const_reference operator[](const sizeType index) const;
		typename pointer RawPointer();
		typename const_pointer RawPointer() const;
		void ResizeCount(const sizeType targetCount);
		void Clear();

		typename reference LastElement();
		typename const_reference LastElement() const;
		typename reference FirstElement();
		typename const_reference FirstElement() const;

	};

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::Destroy()
	{
		if (mBufferBegin != nullptr)
		{
			const sizeType elementCount = Count();
			for (sizeType elementIndex = 0; elementIndex < elementCount; elementIndex++)
			{
				mBufferBegin[elementIndex].~ELEMENT_TYPE();
			}

			DeAllocate(mBufferBegin);
		}
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::NullifyBufferPtr()
	{
		mBufferBegin = nullptr;
		mBufferEnd = nullptr;
		mBufferCapacityEnd = nullptr;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::CapacityResizeGrow(const sizeType reAllocElementCount)
	{
		JINSTL_ASSERT(reAllocElementCount > Count());

		ELEMENT_TYPE* const newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(reAllocElementCount * sizeof(ELEMENT_TYPE)));

		const sizeType currentElementCount = Count();

		for (sizeType elementIndex = 0; elementIndex < currentElementCount; elementIndex++)
		{
			new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(std::move(mBufferBegin[elementIndex]));
		}

		if (mBufferBegin != nullptr)
		{
			DeAllocate(mBufferBegin);
		}

		mBufferBegin = newlyAllocatedBufferBegin;
		mBufferEnd = newlyAllocatedBufferBegin + currentElementCount;
		mBufferCapacityEnd = newlyAllocatedBufferBegin + reAllocElementCount;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::CapacityResizeShrink(const sizeType reAllocElementCount)
	{
		JINSTL_ASSERT(reAllocElementCount < Count());

		ELEMENT_TYPE* newlyAllocatedBufferBegin = nullptr;

		const sizeType currentElementCount = Count();

		if (reAllocElementCount > 0)
		{
			newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(reAllocElementCount * sizeof(ELEMENT_TYPE)));

			for (sizeType elementIndex = 0; elementIndex < reAllocElementCount; elementIndex++)
			{
				new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(std::move(mBufferBegin[elementIndex]));
			}
		}


		for (sizeType elementIndex = reAllocElementCount; elementIndex < currentElementCount; elementIndex++)
		{
			(mBufferBegin + elementIndex)->~ELEMENT_TYPE();
		}

		DeAllocate(mBufferBegin);

		mBufferBegin = newlyAllocatedBufferBegin;
		mBufferEnd = newlyAllocatedBufferBegin + reAllocElementCount;
		mBufferCapacityEnd = newlyAllocatedBufferBegin + reAllocElementCount;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::Expand()
	{
		const sizeType currentCapacity = Capacity();
		CapacityResizeGrow(currentCapacity == 0 ? (1) : (currentCapacity * 2));
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::InplaceArray()
	{
		NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::InplaceArray(allocator::Allocator* const allocator)
		: AllocBase(allocator)
	{
		NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::~InplaceArray()
	{
		Destroy();
		NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::InplaceArray(const InplaceArray& arr)
	{
		const sizeType passedInplaceArrayElementSize = arr.Count();
		if (passedInplaceArrayElementSize > 0)
		{
			mBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(passedInplaceArrayElementSize * sizeof(ELEMENT_TYPE)));
			mBufferEnd = mBufferBegin + passedInplaceArrayElementSize;
			mBufferCapacityEnd = mBufferEnd;

			for (sizeType elementIndex = 0; elementIndex < passedInplaceArrayElementSize; elementIndex++)
			{
				new (mBufferBegin + elementIndex) ELEMENT_TYPE(arr.mBufferBegin[elementIndex]);
			}
		}
		else
		{
			NullifyBufferPtr();
		}
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::InplaceArray(InplaceArray&& arr) noexcept
	{
		mBufferBegin = arr.mBufferBegin;
		mBufferEnd = arr.mBufferEnd;
		mBufferCapacityEnd = arr.mBufferCapacityEnd;

		arr.NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>& InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::operator=(const InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>& arr)
	{
		const sizeType currentInplaceArrayElementCount = Count();
		const sizeType passedInplaceArrayElementCount = arr.Count();
		if (currentInplaceArrayElementCount >= passedInplaceArrayElementCount)
		{
			for (sizeType elementIndex = 0; elementIndex < passedInplaceArrayElementCount; elementIndex++)
			{
				mBufferBegin[elementIndex] = arr.mBufferBegin[elementIndex];
			}

			for (sizeType elementIndex = passedInplaceArrayElementCount; elementIndex < currentInplaceArrayElementCount; elementIndex++)
			{
				mBufferBegin[elementIndex].~ELEMENT_TYPE();
			}

			mBufferEnd = mBufferBegin + passedInplaceArrayElementCount;
		}
		else
		{
			Destroy();

			mBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(passedInplaceArrayElementCount * sizeof(ELEMENT_TYPE)));
			mBufferEnd = mBufferBegin + passedInplaceArrayElementCount;
			mBufferCapacityEnd = mBufferEnd;

			for (sizeType elementIndex = 0; elementIndex < passedInplaceArrayElementCount; elementIndex++)
			{
				new (mBufferBegin + elementIndex) ELEMENT_TYPE(arr.mBufferBegin[elementIndex]);
			}
		}

		return *this;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>& InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::operator=(InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>&& arr) noexcept
	{
		Destroy();

		mBufferBegin = arr.mBufferBegin;
		mBufferEnd = arr.mBufferEnd;
		mBufferCapacityEnd = arr.mBufferCapacityEnd;

		arr.NullifyBufferPtr();

		return *this;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::Reserve(const sizeType reservationCount)
	{
		if (reservationCount > Count())
		{
			CapacityResizeGrow(reservationCount);
		}
	}



	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::PushBack(const ELEMENT_TYPE& element)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		*mBufferEnd = element;
		mBufferEnd++;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::PushBack(ELEMENT_TYPE&& element)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		*mBufferEnd = std::move(element);
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::PushBackUnInitialized()
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::PopBack()
	{
		if (Count() > 0)
		{
			(mBufferEnd - 1)->~ELEMENT_TYPE();
			--mBufferEnd;
		}
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	template <typename... ARGS>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::EmplaceBack(ARGS&&... args)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		new (mBufferEnd) ELEMENT_TYPE(std::move(args)...);
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	bool InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::Empty() const
	{
		return (mBufferBegin == mBufferEnd);
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::sizeType InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::Count() const
	{
		return mBufferEnd - mBufferBegin;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::sizeType InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::Capacity() const
	{
		return mBufferCapacityEnd - mBufferBegin;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::reference InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::operator[](const sizeType index)
	{
		JINSTL_ASSERT(Count() > index);
		return mBufferBegin[index];
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::const_reference InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::operator[](const sizeType index) const
	{
		JINSTL_ASSERT(Count() > index);
		return mBufferBegin[index];
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::pointer InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::RawPointer()
	{
		return mBufferBegin;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::const_pointer InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::RawPointer() const
	{
		return mBufferBegin;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::ResizeCount(const sizeType targetCount)
	{
		const sizeType curretCount = Count();
		JINSTL_ASSERT(curretCount != targetCount);
		if (targetCount > curretCount)
		{
			CapacityResizeGrow(targetCount);
			for (sizeType elementIndex = curretCount; elementIndex < targetCount; elementIndex++)
			{
				mBufferEnd = mBufferCapacityEnd;
				JINSTL_ASSERT(mBufferEnd == mBufferBegin + targetCount);
				new (mBufferBegin + elementIndex) ELEMENT_TYPE();
			}
		}
		else if (targetCount < curretCount)
		{
			CapacityResizeShrink(targetCount);
		}
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	void InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::Clear()
	{
		const sizeType elementCount = mBufferEnd - mBufferBegin;
		for (sizeType elementIndex = 0; elementIndex < elementCount; elementIndex++)
		{
			mBufferBegin[elementIndex].~ELEMENT_TYPE();
		}

		mBufferEnd = mBufferBegin;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::reference InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::LastElement()
	{
		JINSTL_ASSERT(Count() > 0);
		return *(mBufferEnd - 1);
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::const_reference InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::LastElement() const
	{
		JINSTL_ASSERT(Count() > 0);
		return *(mBufferEnd - 1);
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::reference InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::FirstElement()
	{
		JINSTL_ASSERT(Count() > 0);
		return *mBufferBegin;
	}

	template <typename ELEMENT_TYPE, size_t LOCAL_BUFFER_ELEMENT_COUNT>
	typename InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::const_reference InplaceArray<ELEMENT_TYPE, LOCAL_BUFFER_ELEMENT_COUNT>::FirstElement() const
	{
		JINSTL_ASSERT(Count() > 0);
		return *mBufferBegin;
	}
}

