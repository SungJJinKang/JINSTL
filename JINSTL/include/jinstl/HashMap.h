#pragma once

#include "HashTable.h"

namespace jinstl
{
	namespace details
	{
		template <typename KEY_TYPE, typename VALUE_TYPE>
		class HashMapNode : public HashTableNode<KEY_TYPE>
		{

		public:

			using value_reference_type = VALUE_TYPE&;
			using value_const_reference_type = const VALUE_TYPE&;

		private:

			VALUE_TYPE mValue;

		public:

			value_reference_type Value()
			{
				return mValue;
			}

			value_const_reference_type Value() const
			{
				return mValue;
			}
		};
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	class HashMap
	{

	public:

	private:

	public:

	};
}