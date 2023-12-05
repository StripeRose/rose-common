#pragma once

#include <atomic>

#include "..\Debug.h"

namespace System
{
	namespace Memory
	{
		class RefCounted;

		class IRefCountedAllocator
		{
		public:
			virtual void DestroyObject(RefCounted* anObject) = 0;
		};

		class IRefCountedPool
		{
		public:
			virtual ~IRefCountedPool() = default;

		protected:
			void SetRefCountedAllocator(RefCounted* aRefCountedObjectPtr, IRefCountedAllocator* anAllocatorPtr);
		};

		class DefaultRefCountedAllocator final
			: public IRefCountedAllocator
		{
		public:
			void DestroyObject(RefCounted* anObject) override;
		};

		/// <summary>
		/// Base class providing fields for all reference-counted objects.
		/// </summary>
		class RefCounted
		{
			template <typename>
			friend class RefPtr;

			friend class IRefCountedPool;

		public:
			RefCounted();
			virtual ~RefCounted() = default;

		private:
			void IncreaseRef()
			{
				myReferenceCount += 1;
			}

			void DecreaseRef()
			{
				Debug::Assert(myReferenceCount > 0, "An object reference remained despite having been destroyed.");

				myReferenceCount -= 1;

				if (myReferenceCount == 0)
				{
					Debug::Assert(myAllocatorPtr, "No allocator specified.");
					myAllocatorPtr->DestroyObject(this);
				}
			}

		private:
			std::atomic<UInt16> myReferenceCount;
			IRefCountedAllocator* myAllocatorPtr;
		};
	}
}
