#pragma once

#include "Array.h"

namespace jinstl
{
	/**
	 * \brief Templated Dynamic Array is composed of dynamic array chunk. Chunk has max capacity. This is for reducing reallocation overhead when capacity is full.
	 * \tparam ELEMENT_TYPE Element Type
	 */
	template <typename ELEMENT_TYPE>
	class ChunkArray
	{

	public:

		using sizeType = size_t;
		using valueType = ELEMENT_TYPE;
		using reference = ELEMENT_TYPE&;
		using const_reference = const ELEMENT_TYPE&;
		using pointer = ELEMENT_TYPE*;
		using const_pointer = const ELEMENT_TYPE*;

		//inline static const sizeType CapacityCountOfChunk;

	private:

		jinstl::Array<jinstl::Array<ELEMENT_TYPE>> mArrays;

	private:

		void Destroy();
		void ResizeGrow(const sizeType size);
		void ResizeShrink(const sizeType size);
		void Expand();

	public:

		ChunkArray();
		~ChunkArray();
		ChunkArray(const ChunkArray& arr);
		ChunkArray(ChunkArray&& arr) noexcept;
		ChunkArray& operator=(const ChunkArray& arr);
		ChunkArray& operator=(ChunkArray&& arr) noexcept;
		void Reserve(const sizeType size);
		void Push_Back(const ELEMENT_TYPE& element);
		void Push_Back(ELEMENT_TYPE&& element);
		template<typename... ARGS>
		void Emplace_Back(ARGS&&... args);
		bool Empty() const;
		sizeType Count() const;
		sizeType Capacity() const;
		reference operator[](const sizeType index);
		const_reference operator[](const sizeType index) const;
		void Resize(const sizeType targetCount);
		void Clear();

	};

	template <typename ELEMENT_TYPE>
	void ChunkArray<ELEMENT_TYPE>::Destroy()
	{
		mArrays.~Array();
	}

	template <typename ELEMENT_TYPE>
	void ChunkArray<ELEMENT_TYPE>::ResizeGrow(const sizeType reAllocChunkCount)
	{
		JINSTL_ASSERT(reAllocChunkCount > Count());

		ELEMENT_TYPE* const newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(malloc(reAllocChunkCount * sizeof(ELEMENT_TYPE)));

		const sizeType currentElementCount = Count();

		for (sizeType elementIndex = 0; elementIndex < currentElementCount; elementIndex++)
		{
			new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(move(mBufferBegin[elementIndex]));
		}

		if (mBufferBegin != nullptr)
		{
			free(mBufferBegin);
		}

		mBufferBegin = newlyAllocatedBufferBegin;
		mBufferEnd = newlyAllocatedBufferBegin + currentElementCount;
		mBufferCapacityEnd = newlyAllocatedBufferBegin + reAllocChunkCount;
	}

	template <typename ELEMENT_TYPE>
	void ChunkArray<ELEMENT_TYPE>::ResizeShrink(const sizeType reAllocChunkCount)
	{
		JINSTL_ASSERT(reAllocChunkCount < Count());

		ELEMENT_TYPE* const newlyAllocatedBufferBegin = nullptr;

		if (reAllocChunkCount > 0)
		{
			newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(malloc(reAllocChunkCount * sizeof(ELEMENT_TYPE)));

			const sizeType currentElementCount = Count();

			for (sizeType elementIndex = 0; elementIndex < reAllocChunkCount; elementIndex++)
			{
				new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(move(mBufferBegin[elementIndex]));
			}
		}


		for (sizeType elementIndex = reAllocChunkCount; elementIndex < currentElementCount; elementIndex++)
		{
			(mBufferBegin + elementIndex)->~ELEMENT_TYPE();
		}

		free(mBufferBegin);

		mBufferBegin = newlyAllocatedBufferBegin;
		mBufferEnd = newlyAllocatedBufferBegin + currentElementCount;
		mBufferCapacityEnd = newlyAllocatedBufferBegin + reAllocChunkCount;
	}

	template <typename ELEMENT_TYPE>
	void ChunkArray<ELEMENT_TYPE>::Expand()
	{
		const sizeType currentCapacity = Capacity();
		ResizeGrow(currentCapacity == 0 ? (1) : (currentCapacity * 2));
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>::ChunkArray()
		:
		mArrays()
	{
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>::~ChunkArray()
	{
		Destroy();
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>::ChunkArray(const ChunkArray& arr)
		: mArrays(arr.mArrays)
	{
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>::ChunkArray(ChunkArray&& arr) noexcept
		: mArrays(std::move(arr.mArrays))
	{
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>& ChunkArray<ELEMENT_TYPE>::operator=(const ChunkArray<ELEMENT_TYPE>& arr)
	{
		Destroy();

		mArrays = arr.mArrays;

		return *this;
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>& ChunkArray<ELEMENT_TYPE>::operator=(ChunkArray<ELEMENT_TYPE>&& arr) noexcept
	{
		Destroy();

		mArrays = std::move(arr.mArrays);

		return *this;
	}

	template <typename ELEMENT_TYPE>
	void ChunkArray<ELEMENT_TYPE>::Reserve(const sizeType reservationCount)
	{
		if (reservationCount > Count())
		{
			ResizeGrow(reservationCount);
		}
	}



	template <typename ELEMENT_TYPE>
	void ChunkArray<ELEMENT_TYPE>::Push_Back(const ELEMENT_TYPE& element)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		*mBufferEnd = element;
		mBufferEnd++;
	}

	template <typename ELEMENT_TYPE>
	void ChunkArray<ELEMENT_TYPE>::Push_Back(ELEMENT_TYPE&& element)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		*mBufferEnd = move(element);
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	template <typename... ARGS>
	void ChunkArray<ELEMENT_TYPE>::Emplace_Back(ARGS&&... args)
	{
		if (Count() == Capacity())
		{
			Expand();
		}

		new (mBufferEnd) ELEMENT_TYPE(move(args)...);
		++mBufferEnd;
	}

	template <typename ELEMENT_TYPE>
	bool ChunkArray<ELEMENT_TYPE>::Empty() const
	{
		return mArrays.Empty();
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>::sizeType ChunkArray<ELEMENT_TYPE>::Count() const
	{
		return mArrays.Count();
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>::sizeType ChunkArray<ELEMENT_TYPE>::Capacity() const
	{
		return mArrays.Capacity();
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>::reference ChunkArray<ELEMENT_TYPE>::operator[](const sizeType index)
	{
		JINSTL_ASSERT(Count() > index);
		return mArrays[index];
	}

	template <typename ELEMENT_TYPE>
	ChunkArray<ELEMENT_TYPE>::const_reference ChunkArray<ELEMENT_TYPE>::operator[](const sizeType index) const
	{
		JINSTL_ASSERT(Count() > index);
		return mArrays[index];
	}

	template <typename ELEMENT_TYPE>
	void ChunkArray<ELEMENT_TYPE>::Resize(const sizeType targetCount)
	{
		const sizeType curretCount = Count();
		JINSTL_ASSERT(curretCount != targetCount);
		if (targetCount > curretCount)
		{
			ResizeGrow(targetCount);
		}
		else if (targetCount < curretCount)
		{
			ResizeShrink(targetCount);
		}
	}

	template <typename ELEMENT_TYPE>
	void ChunkArray<ELEMENT_TYPE>::Clear()
	{
		mArrays.Clear();
	}
}

