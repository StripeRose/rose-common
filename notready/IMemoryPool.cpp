#include "IMemoryPool.h"

namespace System
{
	namespace Memory
	{
		const Byte IMemoryPool::StartBound[16]
			= { '[', 'B', 'l', 'o', 'c', 'k', '.', '.', '.', '.', 'S', 't', 'a', 'r', 't', ']' };

		const Byte IMemoryPool::EndBound[16]
			= { '[', 'B', 'l', 'o', 'c', 'k', '.', '.', '.', '.', '.', '.', 'E', 'n', 'd', ']' };
	}
}