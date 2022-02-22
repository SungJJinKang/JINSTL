#pragma once

#include "JINSTLCore.h"
#include "AllocBase.h"

namespace jinstl
{
	namespace details
	{
		template <typename KEY_TYPE>
		struct Hasher
		{
			unsigned long int operator()(const KEY_TYPE& keyType) const;
		};

		template <typename KEY_TYPE>
		class HashTableNode
		{

		public:

			using key_type = KEY_TYPE;
			using this_type = HashTableNode<KEY_TYPE>;

		private:

			this_type* mNextNode;

		public:

			HashTableNode()
				: mNextNode(nullptr)
			{
				
			}

			HashTableNode(this_type* const nextNode)
				: mNextNode(nextNode)
			{
			}

			this_type* NextNode()
			{
				return mNextNode;
			}

			const this_type* NextNode() const
			{
				return mNextNode;
			}

			void SetNextNode(this_type* const nextNode)
			{
				mNextNode = nextNode;
			}
		};

		template <typename KEY_TYPE>
		class HashTableBucket
		{

		public:

			using node_type = HashTableNode<KEY_TYPE>;

		private:

			node_type* mNextNode;

		public:

			HashTableBucket()
				: mNextNode(nullptr)
			{
				
			}

			node_type* FirstNode()
			{
				return mNextNode;
			}

			const node_type* FirstNode() const
			{
				return mNextNode;
			}

			void SetNextNode(node_type* const nodeType)
			{
				mNextNode = nodeType;
			}
		};
	}

	template <typename KEY_TYPE>
	class HashTable : public AllocBase
	{
	public:

		using bucket_type = details::HashTableBucket<KEY_TYPE>;
		using node_type = details::HashTableNode<KEY_TYPE>;

	private:

	public:
	};
}