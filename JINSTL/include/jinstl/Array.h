#pragma once

#include <type_traits>

#include "AllocBase.h"
#include "Allocator.h"

namespace jinstl
{
	// TODO : support std iterator

	/**
	 * \brief Templated Dynamic Array. 
	 * \tparam ELEMENT_TYPE Element Type
	 */
	template <typename ELEMENT_TYPE>
	class Array : public AllocBase
	{
	public:

		using sizeType = size_t;
		using valueType = ELEMENT_TYPE;
		using reference = ELEMENT_TYPE&;
		using const_reference = const ELEMENT_TYPE&;
		using pointer = ELEMENT_TYPE*;
		using const_pointer = const ELEMENT_TYPE*;

	private:

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

		Array();
		Array(allocator::Allocator* const allocator);
		~Array();
		Array(const Array& arr);
		Array(Array&& arr) noexcept;
		Array& operator=(const Array& arr);
		Array& operator=(Array&& arr) noexcept;
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
		void ClearNoDestructor();
		void Remove(const sizeType index);
		void SwapPopBack(const sizeType removedIndex);
		typename sizeType Find(const_reference cmpValue) const;

		typename reference LastElement();
		typename const_reference LastElement() const;
		typename reference FirstElement();
		typename const_reference FirstElement() const;

		bool Contain(const_reference cmpValue) const;

	};

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::Destroy()
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

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::NullifyBufferPtr()
	{
		mBufferBegin = nullptr;
		mBufferEnd = nullptr;
		mBufferCapacityEnd = nullptr;
	}

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::CapacityResizeGrow(const sizeType reAllocElementCount)
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

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::CapacityResizeShrink(const sizeType reAllocElementCount)
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

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::Expand()
	{
		const sizeType currentCapacity = Capacity();
		CapacityResizeGrow(currentCapacity == 0 ? (1) : (currentCapacity * 2));
	}

	template <typename ELEMENT_TYPE>
	Array<ELEMENT_TYPE>::Array()
	{
		NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE>
	Array<ELEMENT_TYPE>::Array(allocator::Allocator* const allocator)
		: AllocBase(allocator)
	{
		NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE>
	Array<ELEMENT_TYPE>::~Array()
	{
		Destroy();
		NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE>
	Array<ELEMENT_TYPE>::Array(const Array& arr)
	{
		const sizeType passedArrayElementSize = arr.Count();
		if (passedArrayElementSize > 0)
		{
			mBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(passedArrayElementSize * sizeof(ELEMENT_TYPE)));
			mBufferEnd = mBufferBegin + passedArrayElementSize;
			mBufferCapacityEnd = mBufferEnd;

			for (sizeType elementIndex = 0; elementIndex < passedArrayElementSize; elementIndex++)
			{
				new (mBufferBegin + elementIndex) ELEMENT_TYPE(arr.mBufferBegin[elementIndex]);
			}
		}
		else
		{
			NullifyBufferPtr();
		}
	}

	template <typename ELEMENT_TYPE>
	Array<ELEMENT_TYPE>::Array(Array&& arr) noexcept
	{
		mBufferBegin = arr.mBufferBegin;
		mBufferEnd = arr.mBufferEnd;
		mBufferCapacityEnd = arr.mBufferCapacityEnd;

		arr.NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE>
	Array<ELEMENT_TYPE>& Array<ELEMENT_TYPE>::operator=(const Array<ELEMENT_TYPE>& arr)
	{
		const sizeType currentArrayElementCount = Count();
		const sizeType passedArrayElementCount = arr.Count();
		if (currentArrayElementCount >= passedArrayElementCount)
		{
			for (sizeType elementIndex = 0; elementIndex < passedArrayElementCount; elementIndex++)
			{
				mBufferBegin[elementIndex] = arr.mBufferBegin[elementIndex];
			}

			for (sizeType elementIndex = passedArrayElementCount; elementIndex < currentArrayElementCount; elementIndex++)
			{
				mBufferBegin[elementIndex].~ELEMENT_TYPE();
			}

			mBufferEnd = mBufferBegin + passedArrayElementCount;
		}
		else
		{
			Destroy();

			mBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(passedArrayElementCount * sizeof(ELEMENT_TYPE)));
			mBufferEnd = mBufferBegin + passedArrayElementCount;
			mBufferCapacityEnd = mBufferEnd;

			for (sizeType elementIndex = 0; elementIndex < passedArrayElementCount; elementIndex++)
			{
				new (mBufferBegin + elementIndex) ELEMENT_TYPE(arr.mBufferBegin[elementIndex]);
			}
		}

		return *this;
	}

	template <typename ELEMENT_TYPE>
	Array<ELEMENT_TYPE>& Array<ELEMENT_TYPE>::operator=(Array<ELEMENT_TYPE>&& arr) noexcept
	{
		Destroy();

		mBufferBegin = arr.mBufferBegin;
		mBufferEnd = arr.mBufferEnd;
		mBufferCapacityEnd = arr.mBufferCapacityEnd;

		arr.NullifyBufferPtr();

		return *this;
	}

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::Reserve(const sizeType reservationCount)
	{
		if (reservationCount > Count())
		{
			CapacityResizeGrow(reservationCount);
		}
	}



	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::PushBack(const ELEMENT_TYPE& element)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		*mBufferEnd = element;
		mBufferEnd++;
	}

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::PushBack(ELEMENT_TYPE&& element)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		*mBufferEnd = std::move(element);
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::PushBackUnInitialized()
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::PopBack()
	{
		JINSTL_ASSERT(Empty() == false);
		(mBufferEnd - 1)->~ELEMENT_TYPE();
		--mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	template <typename... ARGS>
	void Array<ELEMENT_TYPE>::EmplaceBack(ARGS&&... args)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		new (mBufferEnd) ELEMENT_TYPE(std::forward<ARGS>(args)...);
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	bool Array<ELEMENT_TYPE>::Empty() const
	{
		return (mBufferBegin == mBufferEnd);
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::sizeType Array<ELEMENT_TYPE>::Count() const
	{
		return mBufferEnd - mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::sizeType Array<ELEMENT_TYPE>::Capacity() const
	{
		return mBufferCapacityEnd - mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::reference Array<ELEMENT_TYPE>::operator[](const sizeType index)
	{
		JINSTL_ASSERT(Count() > index);
		return mBufferBegin[index];
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::const_reference Array<ELEMENT_TYPE>::operator[](const sizeType index) const
	{
		JINSTL_ASSERT(Count() > index);
		return mBufferBegin[index];
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::pointer Array<ELEMENT_TYPE>::RawPointer()
	{
		return mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::const_pointer Array<ELEMENT_TYPE>::RawPointer() const
	{
		return mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::ResizeCount(const sizeType targetCount)
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

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::Clear()
	{
		const sizeType elementCount = mBufferEnd - mBufferBegin;
		for (sizeType elementIndex = 0; elementIndex < elementCount; elementIndex++)
		{
			mBufferBegin[elementIndex].~ELEMENT_TYPE();
		}

		mBufferEnd = mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::ClearNoDestructor()
	{
		mBufferEnd = mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::Remove(const sizeType removedIndex)
	{
		JINSTL_ASSERT(Count() > removedIndex);

		const size_t count = Count();

		(mBufferBegin + removedIndex)->~ELEMENT_TYPE();

		for(size_t index = removedIndex ; index < count ; ++index)
		{
			*(mBufferBegin + index) = std::move(*(mBufferBegin + index + 1));
		}
		--mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	void Array<ELEMENT_TYPE>::SwapPopBack(const sizeType removedIndex)
	{
		JINSTL_ASSERT(Count() > removedIndex);

		if(removedIndex == Count() - 1)
		{
			PopBack();
		}
		else
		{
			std::swap(LastElement(), mBufferBegin[removedIndex]);
			PopBack();
		}
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::sizeType Array<ELEMENT_TYPE>::Find(const_reference cmpValue) const
	{
		Array<ELEMENT_TYPE>::sizeType targetIndex = Count();

		const size_t count = Count();
		for (size_t index = 0; index < count; ++index)
		{
			if (mBufferBegin[index] == cmpValue)
			{
				targetIndex = index;
				break;
			}
		}

		return targetIndex;
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::reference Array<ELEMENT_TYPE>::LastElement()
	{
		JINSTL_ASSERT(Count() > 0);
		return *(mBufferEnd - 1);
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::const_reference Array<ELEMENT_TYPE>::LastElement() const
	{
		JINSTL_ASSERT(Count() > 0);
		return *(mBufferEnd - 1);
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::reference Array<ELEMENT_TYPE>::FirstElement()
	{
		JINSTL_ASSERT(Count() > 0);
		return *mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	typename Array<ELEMENT_TYPE>::const_reference Array<ELEMENT_TYPE>::FirstElement() const
	{
		JINSTL_ASSERT(Count() > 0);
		return *mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	bool Array<ELEMENT_TYPE>::Contain(const_reference cmpValue) const
	{
		bool isExist = false;

		const size_t count = Count();
		for(size_t index = 0 ; index < count ; ++index)
		{
			if(mBufferBegin[index] == cmpValue)
			{
				isExist = true;
				break;
			}
		}

		return isExist;
	}
}

