#pragma once

#include "AllocBase.h"

#include <cstring>
#include <cwchar>

namespace jinstl
{

#define JINSTL_TSTRING_SMALL_SIZE_LOCAL_BUFFER_CHARACTER_COUNT 16

	template <typename CHAR_TYPE>
	class TString : public AllocBase
	{
	public:

		using size_type = size_t;
		using value_type = CHAR_TYPE;
		using const_value_type = const CHAR_TYPE;
		using reference_type = CHAR_TYPE&;
		using const_reference_type = const CHAR_TYPE&;
		using pointer_type = CHAR_TYPE*;
		using const_pointer_type = const CHAR_TYPE*;

	private:

		CHAR_TYPE mSmallSizeLocalBuffer[JINSTL_TSTRING_SMALL_SIZE_LOCAL_BUFFER_CHARACTER_COUNT];

		CHAR_TYPE* mStringBegin;
		CHAR_TYPE* mStringEnd;
		CHAR_TYPE* mStringCapacityEnd;

	private:

		void CopyConstructFromTString(const TString& arr);
		void RangeInitialize(const_pointer_type cStringBegin, const_pointer_type cStringEnd);
		void RangeInitialize(const_pointer_type cString);
		inline void Destroy();
		inline void NullifyBufferPtr();
		void CapacityResizeGrow(const size_type size);
		void CapacityResizeGrowForInsert(const size_type insertedIndex, const size_type insertedElementCount);
		void CapacityResizeShrink(const size_type size);
		inline void MoveBackwardCharacters(const size_type targetIndex, const size_type movedCharacterCount);
		inline void ResizeWithoutCopyOriginalString(const size_type length, const size_type capacity);
		void Expand();

	public:

		TString();
		TString(allocator::Allocator* const allocator);
		TString(const_pointer_type cString);
		TString(const_pointer_type cStringBegin, const_pointer_type cStringEnd);
		~TString();
		TString(const TString& arr);
		TString(TString&& arr) noexcept;
		TString& operator=(const TString& arr);
		TString& operator=(TString&& arr) noexcept;
		TString& operator=(const_pointer_type cString);
		void Reserve(const size_type size);
		void Append(const_value_type element);
		void Append(const TString& tString);
		void Append(TString&& tString) = delete;
		void Append(const_pointer_type cString);
		TString& operator+=(const_value_type element);
		TString& operator+=(const TString& tstring);
		TString& operator+=(TString&& tstring) = delete;
		TString& operator+=(const_pointer_type cString);
		void PopBack();
		inline bool Empty() const;
		inline typename size_type Length() const;
		inline typename size_type Capacity() const;
		inline typename reference_type operator[](const size_type index);
		inline typename const_reference_type operator[](const size_type index) const;
		inline typename pointer_type RawPointer();
		inline typename const_pointer_type RawPointer() const;
		typename pointer_type CString();
		typename const_pointer_type CString() const;
		void ResizeLength(const size_type targetCount);
		void Clear();
		void Insert(const size_type insertedIndex, CHAR_TYPE insertedCharacter);
		void Insert(const size_type insertedIndex, const_pointer_type cString);
		void Insert(const size_type insertedIndex, const TString& string);
		void Remove(const size_type index);
		TString SubString(const size_type index) const;
		typename size_type Find(const_reference_type cmpValue) const;

		inline typename reference_type FirstCharacter();
		inline typename const_reference_type FirstCharacter() const;
		inline typename reference_type LastCharacter();
		inline typename const_reference_type LastCharacter() const;

		bool Contain(const_value_type cmpCharacter) const;
		int Compare(const TString<CHAR_TYPE>& string) const;
		bool EqualWith(const TString<CHAR_TYPE>& string) const;

	};

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::CopyConstructFromTString(const TString& arr)
	{
		const size_type passedTStringElementCount = arr.Length();
		if (passedTStringElementCount > 0)
		{
			ResizeWithoutCopyOriginalString(passedTStringElementCount, passedTStringElementCount + 1);

			std::memcpy(mStringBegin, arr.mStringBegin, sizeof(CHAR_TYPE) * passedTStringElementCount);
		}
		else
		{
			NullifyBufferPtr();
		}
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::RangeInitialize(const_pointer_type cStringBegin, const_pointer_type cStringEnd)
	{
		JINSTL_ASSERT(cStringEnd >= cStringBegin);

		if(cStringEnd > cStringBegin)
		{
			const size_type stringElementCount = cStringEnd - cStringBegin;
			ResizeWithoutCopyOriginalString(stringElementCount, stringElementCount + 1);

			std::memcpy(mStringBegin, cStringBegin, stringElementCount * sizeof(CHAR_TYPE));
		}
		else
		{
			NullifyBufferPtr();
		}

	
	}

	namespace details
	{
		inline size_t CStringLength(const char* const cString)
		{
			return std::strlen(cString);
		}

		inline size_t CStringLength(const wchar_t* const cString)
		{
			return std::wcslen(cString);
		}
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::RangeInitialize(const_pointer_type cString)
	{
		const size_type cStringLength = details::CStringLength(cString);
		RangeInitialize(cString, cString + cStringLength);
	}

	template <typename CHAR_TYPE>
	inline void TString<CHAR_TYPE>::Destroy()
	{
		if (mStringBegin != nullptr && mStringBegin != mSmallSizeLocalBuffer)
		{
			DeAllocate(mStringBegin);
		}
	}

	template <typename CHAR_TYPE>
	inline void TString<CHAR_TYPE>::NullifyBufferPtr()
	{
		mStringBegin = nullptr;
		mStringEnd = nullptr;
		mStringCapacityEnd = nullptr;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::CapacityResizeGrow(const size_type reAllocElementCount)
	{
		JINSTL_ASSERT(reAllocElementCount > Length());

		const size_type currentElementCount = Length();

		CHAR_TYPE* newlyAllocatedBufferBegin;

		if(JINSTL_TSTRING_SMALL_SIZE_LOCAL_BUFFER_CHARACTER_COUNT >= reAllocElementCount)
		{
			newlyAllocatedBufferBegin = mSmallSizeLocalBuffer;
		}
		else
		{
			newlyAllocatedBufferBegin = reinterpret_cast<CHAR_TYPE*>(Allocate(reAllocElementCount * sizeof(CHAR_TYPE)));
		}

		if (mStringBegin != newlyAllocatedBufferBegin)
		{
			std::memcpy(newlyAllocatedBufferBegin, mStringBegin, sizeof(CHAR_TYPE) * currentElementCount);
		}

		Destroy();

		mStringBegin = newlyAllocatedBufferBegin;
		mStringEnd = newlyAllocatedBufferBegin + currentElementCount;
		mStringCapacityEnd = newlyAllocatedBufferBegin + reAllocElementCount;

		
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::CapacityResizeGrowForInsert(const size_type insertedIndex, const size_type insertedElementCount)
	{
		JINSTL_ASSERT(insertedIndex <= Length());

		const size_type currentCapacity = Capacity();
		if (currentCapacity == 0 && insertedElementCount == 1)
		{
			CapacityResizeGrow(1);
		}
		else
		{
			const size_type currentStringLength = Length();
			const size_t targetCapacity = currentStringLength + insertedElementCount;

			CHAR_TYPE* newlyAllocatedStringBegin;
			if (JINSTL_TSTRING_SMALL_SIZE_LOCAL_BUFFER_CHARACTER_COUNT >= targetCapacity)
			{
				newlyAllocatedStringBegin = mSmallSizeLocalBuffer;
			}
			else
			{
				newlyAllocatedStringBegin = reinterpret_cast<CHAR_TYPE*>(Allocate(targetCapacity * sizeof(CHAR_TYPE)));
			}

			if (mStringBegin != newlyAllocatedStringBegin)
			{
				std::memcpy(newlyAllocatedStringBegin, mStringBegin, insertedIndex * sizeof(CHAR_TYPE));
			}

			std::memcpy(newlyAllocatedStringBegin + insertedIndex + insertedElementCount, mStringBegin + insertedIndex, (currentStringLength - insertedIndex) * sizeof(CHAR_TYPE));
			
			Destroy();

			mStringBegin = newlyAllocatedStringBegin;
			mStringEnd = newlyAllocatedStringBegin + currentStringLength;
			mStringCapacityEnd = newlyAllocatedStringBegin + targetCapacity;
		}
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::CapacityResizeShrink(const size_type reAllocElementCount)
	{
		JINSTL_ASSERT(reAllocElementCount < Length());

		CHAR_TYPE* newlyAllocatedBufferBegin = nullptr;

		const size_type currentElementCount = Length();

		if (reAllocElementCount > 0)
		{
			if (JINSTL_TSTRING_SMALL_SIZE_LOCAL_BUFFER_CHARACTER_COUNT >= reAllocElementCount)
			{
				newlyAllocatedBufferBegin = mSmallSizeLocalBuffer;
			}
			else
			{
				newlyAllocatedBufferBegin = reinterpret_cast<CHAR_TYPE*>(Allocate(reAllocElementCount * sizeof(CHAR_TYPE)));
			}

			if(mStringBegin != mSmallSizeLocalBuffer)
			{
				std::memcpy(newlyAllocatedBufferBegin, mStringBegin, sizeof(CHAR_TYPE) * reAllocElementCount);
			}
		}

		Destroy();

		mStringBegin = newlyAllocatedBufferBegin;
		mStringEnd = newlyAllocatedBufferBegin + reAllocElementCount;
		mStringCapacityEnd = newlyAllocatedBufferBegin + reAllocElementCount;
	}

	template <typename CHAR_TYPE>
	inline void TString<CHAR_TYPE>::MoveBackwardCharacters(const size_type targetIndex, const size_type movedCharacterCount)
	{
		const size_type currentLenth = Length();
		std::memmove(mStringBegin + targetIndex + movedCharacterCount, mStringBegin + targetIndex, (currentLenth - targetIndex) * sizeof(CHAR_TYPE));
	}
	
	template <typename CHAR_TYPE>
	inline void TString<CHAR_TYPE>::ResizeWithoutCopyOriginalString(const size_type length, const size_type capacity)
	{
		JINSTL_ASSERT(capacity >= length);

		if(capacity > JINSTL_TSTRING_SMALL_SIZE_LOCAL_BUFFER_CHARACTER_COUNT)
		{
			mStringBegin = reinterpret_cast<CHAR_TYPE*>(Allocate(capacity * sizeof(CHAR_TYPE)));
		}
		else
		{
			mStringBegin = mSmallSizeLocalBuffer;
		}

		mStringEnd = mStringBegin + length;
		mStringCapacityEnd = mStringBegin + capacity;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Expand()
	{
		const size_type currentCapacity = Capacity();
		CapacityResizeGrow(currentCapacity == 0 ? (1) : (currentCapacity * 2));
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>::TString()
	{
		NullifyBufferPtr();
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>::TString(allocator::Allocator* const allocator)
		: AllocBase(allocator)
	{
		NullifyBufferPtr();
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>::TString(const_pointer_type cString)
	{
		RangeInitialize(cString);
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>::TString(const_pointer_type cStringBegin, const_pointer_type cStringEnd)
	{
		JINSTL_ASSERT(cStringBegin <= cStringEnd);
		RangeInitialize(cStringBegin, cStringEnd);
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>::~TString()
	{
		Destroy();
		NullifyBufferPtr();
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>::TString(const TString& arr)
	{
		CopyConstructFromTString(arr);
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>::TString(TString&& arr) noexcept
	{
		if(arr.mStringBegin == arr.mSmallSizeLocalBuffer)
		{
			CopyConstructFromTString(arr);
		}
		else
		{
			mStringBegin = arr.mStringBegin;
			mStringEnd = arr.mStringEnd;
			mStringCapacityEnd = arr.mStringCapacityEnd;
		}
		

		arr.NullifyBufferPtr();
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>& TString<CHAR_TYPE>::operator=(const TString<CHAR_TYPE>& arr)
	{
		const size_type currentTStringElementCount = Length();
		const size_type passedTStringElementCount = arr.Length();
		if (currentTStringElementCount >= passedTStringElementCount)
		{
			std::memcpy(mStringBegin, arr.mStringBegin, sizeof(CHAR_TYPE) * passedTStringElementCount);
			mStringEnd = mStringBegin + passedTStringElementCount;
		}
		else
		{
			Destroy();

			ResizeWithoutCopyOriginalString(passedTStringElementCount, passedTStringElementCount + 1);

			std::memcpy(mStringBegin, arr.mStringBegin, sizeof(CHAR_TYPE) * passedTStringElementCount);
		}

		return *this;
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>& TString<CHAR_TYPE>::operator=(TString<CHAR_TYPE>&& arr) noexcept
	{
		if (arr.mStringBegin == arr.mSmallSizeLocalBuffer)
		{
			*this = arr; // Copy assignment
		}
		else
		{
			Destroy();

			mStringBegin = arr.mStringBegin;
			mStringEnd = arr.mStringEnd;
			mStringCapacityEnd = arr.mStringCapacityEnd;
		}

		arr.NullifyBufferPtr();

		return *this;
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>& TString<CHAR_TYPE>::operator=(const_pointer_type cString)
	{
		Destroy();
		RangeInitialize(cString);
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Reserve(const size_type reservationCount)
	{
		if (reservationCount > Length())
		{
			CapacityResizeGrow(reservationCount);
		}
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Append(const_value_type element)
	{
		if (Length() == Capacity())
		{
			Expand();
		}

		*mStringEnd = element;
		mStringEnd++;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Append(const TString& tString)
	{
		const size_type passedStringLength = tString.Length();
		const size_type targetLength = Length() + passedStringLength;
		if (targetLength > Capacity())
		{
			CapacityResizeGrow(targetLength);
		}

		std::memcpy(mStringEnd, tString.mStringBegin, passedStringLength * sizeof(CHAR_TYPE));
		mStringEnd += passedStringLength;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Append(const_pointer_type cString)
	{
		const size_type cStringLength = details::CStringLength(cString);
		const size_type targetLength = Length() + cStringLength;
		if (targetLength > Capacity())
		{
			CapacityResizeGrow(targetLength);
		}

		std::memcpy(mStringEnd, cString, cStringLength * sizeof(CHAR_TYPE));
		mStringEnd += cStringLength;
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>& TString<CHAR_TYPE>::operator+=(const_value_type element)
	{
		Append(element);
		return *this;
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>& TString<CHAR_TYPE>::operator+=(const TString& tstring)
	{
		Append(tstring);
		return *this;
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE>& TString<CHAR_TYPE>::operator+=(const_pointer_type cString)
	{
		Append(cString);
		return *this;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::PopBack()
	{
		JINSTL_ASSERT(Empty() == false);
		--mStringEnd;
	}
	
	template <typename CHAR_TYPE>
	inline bool TString<CHAR_TYPE>::Empty() const
	{
		return (mStringBegin == mStringEnd);
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::size_type TString<CHAR_TYPE>::Length() const
	{
		return mStringEnd - mStringBegin;
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::size_type TString<CHAR_TYPE>::Capacity() const
	{
		return mStringCapacityEnd - mStringBegin;
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::reference_type TString<CHAR_TYPE>::operator[](const size_type index)
	{
		JINSTL_ASSERT(Length() > index);
		return mStringBegin[index];
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::const_reference_type TString<CHAR_TYPE>::operator[](const size_type index) const
	{
		JINSTL_ASSERT(Length() > index);
		return mStringBegin[index];
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::pointer_type TString<CHAR_TYPE>::RawPointer()
	{
		return mStringBegin;
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::const_pointer_type TString<CHAR_TYPE>::RawPointer() const
	{
		return mStringBegin;
	}

	template <typename CHAR_TYPE>
	typename TString<CHAR_TYPE>::pointer_type TString<CHAR_TYPE>::CString()
	{
		if(Length() == Capacity())
		{
			Expand();
		}

		std::memset(mStringEnd, 0x00, sizeof(CHAR_TYPE)); // Set null-terminated character

		return mStringBegin;
	}

	template <typename CHAR_TYPE>
	typename TString<CHAR_TYPE>::const_pointer_type TString<CHAR_TYPE>::CString() const
	{
		if (Length() == Capacity())
		{
			Expand();
		}

		std::memset(mStringEnd, 0x00, sizeof(CHAR_TYPE)); // Set null-terminated character

		return mStringBegin;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::ResizeLength(const size_type targetCount)
	{
		const size_type curretCount = Length();
		if (targetCount > curretCount)
		{
			CapacityResizeGrow(targetCount);
			mStringEnd = mStringCapacityEnd;
			JINSTL_ASSERT(mStringEnd == mStringBegin + targetCount);
		}
		else if (targetCount < curretCount)
		{
			CapacityResizeShrink(targetCount);
		}
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Clear()
	{
		mStringEnd = mStringBegin;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Insert(const size_type insertedIndex, CHAR_TYPE insertedCharacter)
	{
		JINSTL_ASSERT(insertedIndex <= Length());
		if (Length() == Capacity())
		{
			CapacityResizeGrowForInsert(insertedIndex, 1);
		}
		else
		{
			MoveBackwardCharacters(insertedIndex, 1);
		}

		mStringBegin[insertedIndex] = insertedCharacter;
		++mStringEnd;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Insert(const size_type insertedIndex, const_pointer_type cString)
	{
		JINSTL_ASSERT(insertedIndex <= Length());
		const size_type cStringLength = details::CStringLength(cString);
		if (Length() + cStringLength > Capacity())
		{
			CapacityResizeGrowForInsert(insertedIndex, cStringLength);
		}
		else
		{
			MoveBackwardCharacters(insertedIndex, cStringLength);
		}

		std::memcpy(mStringBegin + insertedIndex, cString, cStringLength * sizeof(CHAR_TYPE));
		mStringEnd += cStringLength;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Insert(const size_type insertedIndex, const TString& string)
	{
		JINSTL_ASSERT(insertedIndex <= Length());
		JINSTL_ASSERT(string.Empty() == false);

		const size_type copyedTStringLength = string.Length();
		if (Length() + copyedTStringLength > Capacity())
		{
			CapacityResizeGrowForInsert(insertedIndex, copyedTStringLength);
		}
		else
		{
			MoveBackwardCharacters(insertedIndex, copyedTStringLength);
		}

		std::memcpy(mStringBegin + insertedIndex, string.mStringBegin, copyedTStringLength * sizeof(CHAR_TYPE));
		mStringEnd += copyedTStringLength;
	}

	template <typename CHAR_TYPE>
	void TString<CHAR_TYPE>::Remove(const size_type removedIndex)
	{
		JINSTL_ASSERT(Length() > removedIndex);

		std::memcpy(mStringBegin + removedIndex, mStringBegin + removedIndex + 1, sizeof(CHAR_TYPE) * (Length() - removedIndex));
		--mStringEnd;
	}

	template <typename CHAR_TYPE>
	TString<CHAR_TYPE> TString<CHAR_TYPE>::SubString(const size_type index) const
	{
		JINSTL_ASSERT(index < Length());
		return TString<CHAR_TYPE>{mStringBegin + index, mStringEnd};
	}

	template <typename CHAR_TYPE>
	typename TString<CHAR_TYPE>::size_type TString<CHAR_TYPE>::Find(const_reference_type cmpValue) const
	{
		// TODO : implement template specialization for element type applicable https://github.com/SungJJinKang/JINSTL
		
		TString<CHAR_TYPE>::size_type targetIndex = Length();

		const size_t count = Length();
		for (size_t index = 0; index < count; ++index)
		{
			if (mStringBegin[index] == cmpValue)
			{
				targetIndex = index;
				break;
			}
		}

		return targetIndex;
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::reference_type TString<CHAR_TYPE>::FirstCharacter()
	{
		JINSTL_ASSERT(Length() > 0);
		return *mStringBegin;
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::const_reference_type TString<CHAR_TYPE>::FirstCharacter() const
	{
		JINSTL_ASSERT(Length() > 0);
		return *mStringBegin;
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::reference_type TString<CHAR_TYPE>::LastCharacter()
	{
		JINSTL_ASSERT(Length() > 0);
		return *(mStringEnd - 1);
	}

	template <typename CHAR_TYPE>
	inline typename TString<CHAR_TYPE>::const_reference_type TString<CHAR_TYPE>::LastCharacter() const
	{
		JINSTL_ASSERT(Length() > 0);
		return *(mStringEnd - 1);
	}

	template <typename CHAR_TYPE>
	bool TString<CHAR_TYPE>::Contain(const_value_type cmpCharacter) const
	{
		// TODO : implement template specialization for element type applicable https://github.com/SungJJinKang/JINSTL

		bool isExist = false;

		const size_t count = Length();
		for (size_t index = 0; index < count; ++index)
		{
			if (mStringBegin[index] == cmpCharacter)
			{
				isExist = true;
				break;
			}
		}

		return isExist;
	}

	namespace details
	{
		inline int StringCompare(const char* const lhs, const char* const rhs, const size_t maxStrLength)
		{
			return std::strncmp(lhs, rhs, maxStrLength);
		}

		inline int StringCompare(const wchar_t* const lhs, const wchar_t* const rhs, const size_t maxStrLength)
		{
			return std::wcsncmp(lhs, rhs, maxStrLength);
		}
	}

	template <typename CHAR_TYPE>
	int TString<CHAR_TYPE>::Compare(const TString<CHAR_TYPE>& string) const
	{
		return details::StringCompare(RawPointer(), string.RawPointer(), JINSTL_MAX(Length(), string.Length()));
	}

	template <typename CHAR_TYPE>
	bool TString<CHAR_TYPE>::EqualWith(const TString<CHAR_TYPE>& string) const
	{
		const size_type thisLength = Length();
		const size_type argumentLength = string.Length();
		if(thisLength != argumentLength)
		{
			return false;
		}
		else if(details::StringCompare(RawPointer(), string.RawPointer(), JINSTL_MAX(thisLength, argumentLength)) != 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	template <typename CHAR_TYPE>
	extern TString<CHAR_TYPE> operator+(const TString<CHAR_TYPE>& lhs, const TString<CHAR_TYPE>& rhs)
	{
		TString<CHAR_TYPE> newString;

		const size_t lhsLength = lhs.Length();
		const size_t rhsLength = rhs.Length();

		newString.ResizeLength(lhsLength + rhsLength/* This protect reallocation when call CString */);

		std::memcpy(newString.RawPointer(), lhs.RawPointer(), lhsLength * sizeof(CHAR_TYPE));
		std::memcpy(newString.RawPointer() + lhsLength, rhs.RawPointer(), rhsLength * sizeof(CHAR_TYPE));

		return newString;
	}

	template <typename CHAR_TYPE>
	extern bool operator==(const TString<CHAR_TYPE>& lhs, const TString<CHAR_TYPE>& rhs)
	{
		return lhs.EqualWith(rhs);
	}

	template <typename CHAR_TYPE>
	extern bool operator!=(const TString<CHAR_TYPE>& lhs, const TString<CHAR_TYPE>& rhs)
	{
		return !(lhs.EqualWith(rhs));
	}

	using String = TString<char>;
	using WideString = TString<wchar_t>;
}