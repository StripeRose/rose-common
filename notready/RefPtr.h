#pragma once

#include "..\TypeTraits.h"
#include "RefCounted.h"

namespace System
{
	namespace Memory
	{
		template <typename T>
		class RefPtr
		{
			template <typename>
			friend class RefPtr;

		public:
			RefPtr()
				: myObjectPtr(nullptr)
			{
				static_assert(System::IsBaseOf<RefCounted, T>::Value, "Only classes derived from System::Memory::RefCounted can be managed by a RefPtr.");
			}

			RefPtr(T* aNativePointer)
				: myObjectPtr(aNativePointer)
			{
				if (myObjectPtr)
					myObjectPtr->IncreaseRef();
			}

			RefPtr(const RefPtr<T>& aPointer)
				: myObjectPtr(aPointer.myObjectPtr)
			{
				if (myObjectPtr)
					myObjectPtr->IncreaseRef();
			}

			RefPtr(nullptr_t) : RefPtr() { }

			~RefPtr()
			{
				if (myObjectPtr)
					myObjectPtr->DecreaseRef();

				myObjectPtr = nullptr;
			}

			RefPtr<T>& operator=(const RefPtr<T>& aPointer)
			{
				if (myObjectPtr == aPointer.myObjectPtr)
					return *this;

				if (myObjectPtr)
					myObjectPtr->DecreaseRef();

				myObjectPtr = aPointer.myObjectPtr;

				if (myObjectPtr)
					myObjectPtr->IncreaseRef();

				return *this;
			}

			const bool operator==(const RefPtr& aPtr)		const { return myObjectPtr == aPtr.myObjectPtr; }
			const bool operator==(const T* aPtr)			const { return myObjectPtr == aPtr; }
			const bool operator==(nullptr_t)				const { return myObjectPtr == nullptr; }

			const bool operator!=(const RefPtr& aPtr)		const { return myObjectPtr != aPtr.myObjectPtr; }
			const bool operator!=(const T* aPtr)			const { return myObjectPtr != aPtr; }
			const bool operator!=(nullptr_t)				const { return myObjectPtr != nullptr; }

			template <typename U = T>
			const bool operator<(const RefPtr<U>& aPtr) const { return *myObjectPtr < *aPtr.myObjectPtr; }
			template <typename U = T>
			const bool operator<(const U& aPtr) const { return *myObjectPtr < aPtr; }

			T& operator*() { assert(myObjectPtr != nullptr); return *myObjectPtr; }
			T* operator->() { assert(myObjectPtr != nullptr); return myObjectPtr; }

			const T& operator*() const { assert(myObjectPtr != nullptr); return *myObjectPtr; }
			const T* operator->() const { assert(myObjectPtr != nullptr); return myObjectPtr; }

			template <typename U>
			RefPtr<U> As() { return RefPtr<U>(reinterpret_cast<U*>(myObjectPtr)); }

			template <typename U>
			const RefPtr<U> As() const { return RefPtr<U>(reinterpret_cast<U*>(myObjectPtr)); }

			T* Get() { assert(myObjectPtr != nullptr); return myObjectPtr; }
			const T* Get() const { assert(myObjectPtr != nullptr); return myObjectPtr; }

			explicit operator bool() const { return myObjectPtr != nullptr; }
			bool IsValid() const { return myObjectPtr != nullptr; }

		private:
			T* myObjectPtr;
		};
	}
}

template <typename T1, typename T2> bool operator==(const T1* a, const System::Memory::RefPtr<T2>& b) { return b == a; }
template <typename T1, typename T2> bool operator!=(const T1* a, const System::Memory::RefPtr<T2>& b) { return b != a; }
