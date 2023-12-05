#pragma once

#include "..\BasicTypes.h"

#if _DEBUG
#define TRASH_POOLS 1
#else
#define TRASH_POOLS 0
#endif

namespace System
{
	namespace Memory
	{
		/// <summary>
		/// Abstract memory pool interface
		/// </summary>
		class IMemoryPool
		{
		public:
			static const Byte TrashOnCreationSignature = 0xCC;
			static const Byte TrashOnAllocSignature = 0xAB;
			static const Byte TrashOnFreeSignature = 0xFE;
			static const Byte BoundsCheckSize = 16;
			static const Byte StartBound[BoundsCheckSize];
			static const Byte EndBound[BoundsCheckSize];

		public:
			virtual void* Allocate(const uint& aSize) = 0;
			virtual void Free(void* aPtr) = 0;
			virtual const bool IntegrityCheck() const = 0;

			inline const uint GetFreePoolSize() const { return myFreePoolSize; }
			inline const uint GetTotalPoolSize() const { return myTotalPoolSize; }
			inline const bool HasBoundsCheckOn() const { return myBoundsCheckOn == 1; }

		protected:
			IMemoryPool()
				: myTotalPoolSize(0)
				, myFreePoolSize(0)
				, myTrashOnCreation(TRASH_POOLS)
				, myTrashOnAlloc(TRASH_POOLS)
				, myTrashOnFree(TRASH_POOLS)
				, myBoundsCheckOn(0)
			{};

			IMemoryPool(IMemoryPool&& anOther) noexcept
				: myTotalPoolSize(anOther.myTotalPoolSize)
				, myFreePoolSize(anOther.myFreePoolSize)
				, myTrashOnCreation(anOther.myTrashOnCreation)
				, myTrashOnAlloc(anOther.myTrashOnAlloc)
				, myTrashOnFree(anOther.myTrashOnFree)
				, myBoundsCheckOn(anOther.myBoundsCheckOn)
			{
				anOther.myTotalPoolSize = 0;
				anOther.myFreePoolSize = 0;
				anOther.myTrashOnCreation = TRASH_POOLS;
				anOther.myTrashOnAlloc = TRASH_POOLS;
				anOther.myTrashOnFree = TRASH_POOLS;
				anOther.myBoundsCheckOn = 0;
			}

			virtual ~IMemoryPool() {};

			uint myTotalPoolSize;
			uint myFreePoolSize;

			// Bit-field
			unsigned myTrashOnCreation : 1;
			unsigned myTrashOnAlloc : 1;
			unsigned myTrashOnFree : 1;
			unsigned myBoundsCheckOn : 1;
		};
	}
}
