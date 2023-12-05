#pragma once

#include <stdarg.h>

#include "IAllocator.h"
#include "RefPtr.h"
#include "RefCounted.h"
#include "StandardMemoryPool.h"

#define KIB_TO_BYTE(x) (static_cast<uint>((x) * static_cast<double>(1024)))
#define MIB_TO_BYTE(x) (static_cast<uint>((x) * static_cast<double>(1024 * 1024)))

namespace System
{
	namespace Memory
	{
		class SmartRefPool
			: public IRefCountedPool
		{
		private:
			class ObjectAllocator
				: public IRefCountedAllocator
			{
			public:
				ObjectAllocator(SmartRefPool* aPoolPtr) : myPoolPtr(aPoolPtr) { }
				void DestroyObject(RefCounted* aRefCountedObjectPtr) override
				{
					myPoolPtr->Free(aRefCountedObjectPtr);
				}

			private:
				SmartRefPool* myPoolPtr;
			};

		public:
			SmartRefPool(const uint& aMemoryPoolSize)
				: myAllocator(this)
				, myMemoryPool(aMemoryPoolSize)
			{ }

			SmartRefPool(SmartRefPool&& anOther) noexcept
				: myAllocator(this)
				, myMemoryPool(std::move(anOther.myMemoryPool))
			{ }

			template <typename T>
			RefPtr<T> Create() { return CreateArray<T>(1); }

			template <typename T, typename ... Arguments>
			RefPtr<T> Create(Arguments ... someArguments) { return CreateArray<T, Arguments...>(1, std::forward<Arguments>(someArguments)...); }

			template <typename T, typename ... Arguments>
			RefPtr<T> CreateArray(const uint& anArraySize, Arguments ... someArguments)
			{
				static_assert(System::IsBaseOf<RefCounted, T>::Value, "Only objects derived from System::Memory::RefCounted can be instantiated.");

				if (anArraySize == 0)
					return nullptr;

				void* const allocatedMemory = myMemoryPool.Allocate(sizeof(T) * anArraySize);
				if (!Debug::Verify(allocatedMemory != nullptr, "Could not allocate requested memory."))
					return nullptr;

				T* allocatedMemoryType = static_cast<T*>(allocatedMemory);
				for (uint i = 0; i < anArraySize; ++i)
				{
					RefCounted* refCounted = new (allocatedMemoryType + i) T(std::forward<Arguments>(someArguments)...);
					SetRefCountedAllocator(refCounted, &myAllocator);
				}

				return RefPtr<T>(allocatedMemoryType);
			}

		private:
			void Free(void* aMemoryPointer)
			{
				RefCounted* refcountedObj = static_cast<RefCounted*>(aMemoryPointer);
				refcountedObj->~RefCounted();

				myMemoryPool.Free(aMemoryPointer);
			}

		private:
			ObjectAllocator myAllocator;
			StandardMemoryPool myMemoryPool;
		};
	}
}
