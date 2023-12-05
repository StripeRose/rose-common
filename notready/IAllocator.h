#pragma once

#include "..\BasicTypes.h"

namespace System
{
	namespace Memory
	{
		/// <summary>
		/// Defines the basic interface for all system allocators.
		/// </summary>
		template <typename T>
		class IAllocator
		{
		public:
			virtual ~IAllocator() = default;

			/// <summary>
			/// Allocates a block of memory large enough to store at least the specified number of elements.
			/// </summary>
			/// <param name="aCount">The number of elements for which sufficient storage is to be allocated.</param>
			/// <returns>A pointer to the allocated object or null if memory was not allocated.</returns>
			virtual T* Allocate(const uint& aCount) = 0;

			/// <summary>
			/// Frees the specified number of objects from storage beginning at a specified position.
			/// </summary>
			/// <param name="aMemoryPtr">A pointer to the first object to be deallocated from storage.</param>
			/// <param name="aCount">The number of objects to be deallocated from storage.</param>
			virtual void Deallocate(T* aMemoryPtr, const uint& aCount) = 0;

			/// <summary>
			/// Returns the number of elements of the Type that could be allocated before the free memory is used up.
			/// </summary>
			/// <returns>The number of elements that could be allocated.</returns>
			virtual uint GetMaxSize() const = 0;
		};
	}
}