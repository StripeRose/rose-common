#include "RefCounted.h"

namespace System
{
	namespace Memory
	{
		static DefaultRefCountedAllocator locDefaultAllocator;

		void IRefCountedPool::SetRefCountedAllocator(RefCounted* aRefCountedObjectPtr, IRefCountedAllocator* anAllocatorPtr)
		{
			aRefCountedObjectPtr->myAllocatorPtr = anAllocatorPtr;
		}

		void DefaultRefCountedAllocator::DestroyObject(RefCounted* anObject)
		{
			delete anObject;
		}

		RefCounted::RefCounted()
			: myReferenceCount(0)
			, myAllocatorPtr(&locDefaultAllocator)
		{ }
	}
}