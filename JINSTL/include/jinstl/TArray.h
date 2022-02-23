#pragma once

#include <type_traits>

#include "AllocBase.h"
#include "Allocator.h"

namespace jinstl
{
	/**
	 * \brief Templated Dynamic Array. 
	 * \tparam ELEMENT_TYPE Element Type
	 */
	template <typename ELEMENT_TYPE>
	class TArray : public AllocBase
	{
	public:

		using size_type = size_t;
		using value_type = ELEMENT_TYPE;
		using reference_type = ELEMENT_TYPE&;
		using const_reference_type = const ELEMENT_TYPE&;
		using pointer_type = ELEMENT_TYPE*;
		using const_pointer_type = const ELEMENT_TYPE*;

	private:

		ELEMENT_TYPE* mBufferBegin;
		ELEMENT_TYPE* mBufferEnd;
		ELEMENT_TYPE* mBufferCapacityEnd;

	private:

		void Destroy();
		void NullifyBufferPtr();
		void CapacityResizeGrow(const size_type size);
		void CapacityResizeGrowForInsert(const size_type insertedIndex, const size_type insertedElementCount);
		void CapacityResizeShrink(const size_type size);

		void Expand();

	public:

		TArray();
		TArray(allocator::Allocator* const allocator);
		~TArray();
		TArray(const TArray& arr);
		TArray(TArray&& arr) noexcept;
		TArray& operator=(const TArray& arr);
		TArray& operator=(TArray&& arr) noexcept;
		void ReserveCapacity(const size_type size);
		void PushBack(const ELEMENT_TYPE& element);
		void PushBack(ELEMENT_TYPE&& element);
		void PushBackUnInitialized();
		void PopBack();
		template<typename... ARGS>
		void EmplaceBack(ARGS&&... args);
		inline bool Empty() const;
		inline typename size_type Count() const;
		inline typename size_type Capacity() const;
		inline typename reference_type operator[](const size_type index);
		inline typename const_reference_type operator[](const size_type index) const;
		inline typename pointer_type RawPointer();
		inline typename const_pointer_type RawPointer() const;
		void ResizeCount(const size_type targetCount);
		void Clear();
		void ClearNoDestructor();
		void Insert(const size_type insertedIndex, const ELEMENT_TYPE& insertedValue);
		void Insert(const size_type insertedIndex, ELEMENT_TYPE&& insertedValue);
		void Insert(const size_type insertedIndex, const TArray& arr);
		void Insert(const size_type insertedIndex, TArray&& arr);
		void Remove(const size_type index);
		void SwapPopBack(const size_type removedIndex);
		typename size_type Find(const_reference_type cmpValue) const;

		inline typename reference_type FirstElement();
		inline typename const_reference_type FirstElement() const;
		inline typename reference_type LastElement();
		inline typename const_reference_type LastElement() const;

		bool Contain(const_reference_type cmpValue) const;

	};

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::Destroy()
	{
		if (mBufferBegin != nullptr)
		{
			const size_type elementCount = Count();
			for (size_type elementIndex = 0; elementIndex < elementCount; elementIndex++)
			{
				mBufferBegin[elementIndex].~ELEMENT_TYPE();
			}

			DeAllocate(mBufferBegin);
		}
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::NullifyBufferPtr()
	{
		mBufferBegin = nullptr;
		mBufferEnd = nullptr;
		mBufferCapacityEnd = nullptr;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::CapacityResizeGrow(const size_type reAllocElementCount)
	{
		JINSTL_ASSERT(reAllocElementCount > Count());

		const size_type currentElementCount = Count();
		ELEMENT_TYPE* const newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(reAllocElementCount * sizeof(ELEMENT_TYPE)));

		for (size_type elementIndex = 0; elementIndex < currentElementCount; elementIndex++)
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
	void TArray<ELEMENT_TYPE>::CapacityResizeGrowForInsert(const size_type insertedIndex, const size_type insertedElementCount)
	{
		JINSTL_ASSERT(insertedElementCount != 0);
		JINSTL_ASSERT(insertedIndex <= Count());
		JINSTL_ASSERT(Count() + insertedElementCount > Capacity());

		const size_type currentCapacity = Capacity();
		if (currentCapacity == 0 && insertedElementCount == 1)
		{
			CapacityResizeGrow(1);
		}
		else
		{
			const size_t targetCapacity = Count() + insertedElementCount;

			const size_type currentElementCount = Count();
			ELEMENT_TYPE* const newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(targetCapacity * sizeof(ELEMENT_TYPE)));

			for (size_type elementIndex = 0; elementIndex < insertedIndex; elementIndex++)
			{
				// Move elements before insertedIndex
				new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(std::move(mBufferBegin[elementIndex]));
			}

			for (size_type elementIndex = insertedIndex + insertedElementCount; elementIndex < insertedElementCount + currentElementCount; elementIndex++)
			{
				// Move elementes after insertedIndex
				new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(std::move(mBufferBegin[elementIndex - insertedElementCount]));
			}

			if (mBufferBegin != nullptr)
			{
				DeAllocate(mBufferBegin);
			}

			mBufferBegin = newlyAllocatedBufferBegin;
			mBufferEnd = newlyAllocatedBufferBegin + currentElementCount;
			mBufferCapacityEnd = newlyAllocatedBufferBegin + targetCapacity;
		}
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::CapacityResizeShrink(const size_type reAllocElementCount)
	{
		JINSTL_ASSERT(reAllocElementCount < Count());

		ELEMENT_TYPE* newlyAllocatedBufferBegin = nullptr;

		const size_type currentElementCount = Count();

		if (reAllocElementCount > 0)
		{
			newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(reAllocElementCount * sizeof(ELEMENT_TYPE)));

			for (size_type elementIndex = 0; elementIndex < reAllocElementCount; elementIndex++)
			{
				new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(std::move(mBufferBegin[elementIndex]));
			}
		}


		for (size_type elementIndex = reAllocElementCount; elementIndex < currentElementCount; elementIndex++)
		{
			(mBufferBegin + elementIndex)->~ELEMENT_TYPE();
		}

		DeAllocate(mBufferBegin);

		mBufferBegin = newlyAllocatedBufferBegin;
		mBufferEnd = newlyAllocatedBufferBegin + reAllocElementCount;
		mBufferCapacityEnd = newlyAllocatedBufferBegin + reAllocElementCount;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::Expand()
	{
		const size_type currentCapacity = Capacity();
		CapacityResizeGrow(currentCapacity == 0 ? (1) : (currentCapacity * 2));
	}

	template <typename ELEMENT_TYPE>
	TArray<ELEMENT_TYPE>::TArray()
	{
		NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE>
	TArray<ELEMENT_TYPE>::TArray(allocator::Allocator* const allocator)
		: AllocBase(allocator)
	{
		NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE>
	TArray<ELEMENT_TYPE>::~TArray()
	{
		Destroy();
		NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE>
	TArray<ELEMENT_TYPE>::TArray(const TArray& arr)
	{
		const size_type passedArrayElementSize = arr.Count();
		if (passedArrayElementSize > 0)
		{
			mBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(Allocate(passedArrayElementSize * sizeof(ELEMENT_TYPE)));
			mBufferEnd = mBufferBegin + passedArrayElementSize;
			mBufferCapacityEnd = mBufferEnd;

			for (size_type elementIndex = 0; elementIndex < passedArrayElementSize; elementIndex++)
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
	TArray<ELEMENT_TYPE>::TArray(TArray&& arr) noexcept
	{
		mBufferBegin = arr.mBufferBegin;
		mBufferEnd = arr.mBufferEnd;
		mBufferCapacityEnd = arr.mBufferCapacityEnd;

		arr.NullifyBufferPtr();
	}

	template <typename ELEMENT_TYPE>
	TArray<ELEMENT_TYPE>& TArray<ELEMENT_TYPE>::operator=(const TArray<ELEMENT_TYPE>& arr)
	{
		const size_type currentArrayElementCount = Count();
		const size_type passedArrayElementCount = arr.Count();
		if (currentArrayElementCount >= passedArrayElementCount)
		{
			for (size_type elementIndex = 0; elementIndex < passedArrayElementCount; elementIndex++)
			{
				mBufferBegin[elementIndex] = arr.mBufferBegin[elementIndex];
			}

			for (size_type elementIndex = passedArrayElementCount; elementIndex < currentArrayElementCount; elementIndex++)
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

			for (size_type elementIndex = 0; elementIndex < passedArrayElementCount; elementIndex++)
			{
				new (mBufferBegin + elementIndex) ELEMENT_TYPE(arr.mBufferBegin[elementIndex]);
			}
		}

		return *this;
	}

	template <typename ELEMENT_TYPE>
	TArray<ELEMENT_TYPE>& TArray<ELEMENT_TYPE>::operator=(TArray<ELEMENT_TYPE>&& arr) noexcept
	{
		Destroy();

		mBufferBegin = arr.mBufferBegin;
		mBufferEnd = arr.mBufferEnd;
		mBufferCapacityEnd = arr.mBufferCapacityEnd;

		arr.NullifyBufferPtr();

		return *this;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::ReserveCapacity(const size_type reservationCount)
	{
		if (reservationCount > Count())
		{
			CapacityResizeGrow(reservationCount);
		}
	}



	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::PushBack(const ELEMENT_TYPE& element)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		*mBufferEnd = element;
		mBufferEnd++;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::PushBack(ELEMENT_TYPE&& element)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		*mBufferEnd = std::move(element);
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::PushBackUnInitialized()
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::PopBack()
	{
		JINSTL_ASSERT(Empty() == false);
		(mBufferEnd - 1)->~ELEMENT_TYPE();
		--mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	template <typename... ARGS>
	void TArray<ELEMENT_TYPE>::EmplaceBack(ARGS&&... args)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		new (mBufferEnd) ELEMENT_TYPE(std::forward<ARGS>(args)...);
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	inline bool TArray<ELEMENT_TYPE>::Empty() const
	{
		return (mBufferBegin == mBufferEnd);
	}

	template <typename ELEMENT_TYPE>
	inline typename TArray<ELEMENT_TYPE>::size_type TArray<ELEMENT_TYPE>::Count() const
	{
		return mBufferEnd - mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	inline typename TArray<ELEMENT_TYPE>::size_type TArray<ELEMENT_TYPE>::Capacity() const
	{
		return mBufferCapacityEnd - mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	inline typename TArray<ELEMENT_TYPE>::reference_type TArray<ELEMENT_TYPE>::operator[](const size_type index)
	{
		JINSTL_ASSERT(Count() > index);
		return mBufferBegin[index];
	}

	template <typename ELEMENT_TYPE>
	inline typename TArray<ELEMENT_TYPE>::const_reference_type TArray<ELEMENT_TYPE>::operator[](const size_type index) const
	{
		JINSTL_ASSERT(Count() > index);
		return mBufferBegin[index];
	}

	template <typename ELEMENT_TYPE>
	inline typename TArray<ELEMENT_TYPE>::pointer_type TArray<ELEMENT_TYPE>::RawPointer()
	{
		return mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	inline typename TArray<ELEMENT_TYPE>::const_pointer_type TArray<ELEMENT_TYPE>::RawPointer() const
	{
		return mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::ResizeCount(const size_type targetCount)
	{
		const size_type curretCount = Count();
		if (targetCount > curretCount)
		{
			CapacityResizeGrow(targetCount);
			for (size_type elementIndex = curretCount; elementIndex < targetCount; elementIndex++)
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
	void TArray<ELEMENT_TYPE>::Clear()
	{
		const size_type elementCount = mBufferEnd - mBufferBegin;
		for (size_type elementIndex = 0; elementIndex < elementCount; elementIndex++)
		{
			mBufferBegin[elementIndex].~ELEMENT_TYPE();
		}

		mBufferEnd = mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::ClearNoDestructor()
	{
		mBufferEnd = mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::Insert(const size_type insertedIndex, const ELEMENT_TYPE& insertedValue)
	{
		if (Count() == Capacity())
		{
			CapacityResizeGrowForInsert(insertedIndex, 1);
		}
		
		mBufferBegin[insertedIndex] = insertedValue;
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::Insert(const size_type insertedIndex, ELEMENT_TYPE&& insertedValue)
	{
		if (Count() == Capacity())
		{
			CapacityResizeGrowForInsert(insertedIndex, 1);
		}

		mBufferBegin[insertedIndex] = std::move(insertedValue);
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::Insert(const size_type insertedIndex, const TArray& arr)
	{
		JINSTL_ASSERT(arr.Empty() == false);

		const size_type copyedTArrayCount = arr.Count();
		if (Count() + copyedTArrayCount > Capacity())
		{
			CapacityResizeGrowForInsert(insertedIndex, copyedTArrayCount);
		}

		for (size_type elementIndex = 0; elementIndex < copyedTArrayCount; elementIndex++)
		{
			new (mBufferBegin + insertedIndex + elementIndex) ELEMENT_TYPE(arr.mBufferBegin[elementIndex]);
		}

		mBufferEnd += copyedTArrayCount;
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::Insert(const size_type insertedIndex, TArray&& arr)
	{
		JINSTL_ASSERT(arr.Empty() == false);

		const size_type movedTArrayCount = arr.Count();
		if (Count() + movedTArrayCount > Capacity())
		{
			CapacityResizeGrowForInsert(insertedIndex, movedTArrayCount);
		}

		for (size_type elementIndex = 0; elementIndex < movedTArrayCount; elementIndex++)
		{
			new (mBufferBegin + insertedIndex + elementIndex) ELEMENT_TYPE(std::move(arr.mBufferBegin[elementIndex]));
		}

		mBufferEnd += movedTArrayCount;

		arr.ClearNoDestructor();
		arr.~TArray();
	}

	template <typename ELEMENT_TYPE>
	void TArray<ELEMENT_TYPE>::Remove(const size_type removedIndex)
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
	void TArray<ELEMENT_TYPE>::SwapPopBack(const size_type removedIndex)
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
	typename TArray<ELEMENT_TYPE>::size_type TArray<ELEMENT_TYPE>::Find(const_reference_type cmpValue) const
	{
		TArray<ELEMENT_TYPE>::size_type targetIndex = Count();

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
	inline typename TArray<ELEMENT_TYPE>::reference_type TArray<ELEMENT_TYPE>::FirstElement()
	{
		JINSTL_ASSERT(Count() > 0);
		return *mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	inline typename TArray<ELEMENT_TYPE>::const_reference_type TArray<ELEMENT_TYPE>::FirstElement() const
	{
		JINSTL_ASSERT(Count() > 0);
		return *mBufferBegin;
	}

	template <typename ELEMENT_TYPE>
	inline typename TArray<ELEMENT_TYPE>::reference_type TArray<ELEMENT_TYPE>::LastElement()
	{
		JINSTL_ASSERT(Count() > 0);
		return *(mBufferEnd - 1);
	}

	template <typename ELEMENT_TYPE>
	inline typename TArray<ELEMENT_TYPE>::const_reference_type TArray<ELEMENT_TYPE>::LastElement() const
	{
		JINSTL_ASSERT(Count() > 0);
		return *(mBufferEnd - 1);
	}

	template <typename ELEMENT_TYPE>
	bool TArray<ELEMENT_TYPE>::Contain(const_reference_type cmpValue) const
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

