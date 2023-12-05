#pragma once

#include "IMemoryPool.h"
#include "..\BasicTypes.h"

#include "MemoryUtilities.h"

namespace System
{
	namespace Memory
	{
		class StandardMemoryPool
			: public IMemoryPool
		{
		public:
			StandardMemoryPool(const uint& aPoolSizeInBytes, const bool isBoundsCheckOn = true)
				: myPoolMemory(nullptr)
			{
				Initialize(aPoolSizeInBytes, isBoundsCheckOn);
			}

			StandardMemoryPool(StandardMemoryPool&& anOther) noexcept
				: IMemoryPool(std::move(anOther))
				, myPoolMemory(anOther.myPoolMemory)
			{
				anOther.myPoolMemory = nullptr;
				anOther.Initialize(myTotalPoolSize, myBoundsCheckOn);
			}

			~StandardMemoryPool()
			{
				Debug::Assert(myFreePoolSize == myTotalPoolSize - sizeof(ChunkHeader) - (BoundsCheckSize * 2), "Not all memory has been freed and any remaining reference to this memory is invalid.");
				free(myPoolMemory);
			}

			void* Allocate(const uint& aSize) override
			{
				uint requiredSize = aSize + sizeof(ChunkHeader);
				if (myBoundsCheckOn == 1)
					requiredSize += BoundsCheckSize * 2;

				ChunkHeader* block = (ChunkHeader*)(myBoundsCheckOn == 1 ? myPoolMemory + BoundsCheckSize : myPoolMemory);
				while (block != nullptr)
				{
					if (block->myIsFree == true && block->myUserDataSize >= requiredSize)
						break;
					block = block->myNext;
				}

				Byte* blockData = reinterpret_cast<Byte*>(block);
				if (block == nullptr)
					return nullptr;

				uint freeUserDataSize = block->myUserDataSize - requiredSize;
				const uint minimumFreeBlockSize = 16;
				if (freeUserDataSize > minimumFreeBlockSize)
				{
					ChunkHeader freeBlock(freeUserDataSize);
					freeBlock.myNext = block->myNext;
					freeBlock.myPrevious = block;
					freeBlock.Write(blockData + requiredSize);
					if (freeBlock.myNext != nullptr)
						freeBlock.myNext->myPrevious = reinterpret_cast<ChunkHeader*>(blockData + requiredSize);
					if (myBoundsCheckOn == 1)
						CopyMemory(blockData + requiredSize - BoundsCheckSize, StartBound, BoundsCheckSize);
					block->myNext = reinterpret_cast<ChunkHeader*>(blockData + requiredSize);
					block->myUserDataSize = aSize;
				}

				myFreePoolSize -= block->myUserDataSize;
				block->myIsFree = false;

				if (myBoundsCheckOn == 1)
				{
					CopyMemory(blockData - BoundsCheckSize, StartBound, BoundsCheckSize);
					CopyMemory(blockData + sizeof(ChunkHeader) + block->myUserDataSize, EndBound, BoundsCheckSize);
				}

				if (myTrashOnAlloc == 1)
					SetMemory(blockData + sizeof(ChunkHeader), TrashOnAllocSignature, block->myUserDataSize);

				return (blockData + sizeof(ChunkHeader));
			}

			void Free(void* aPtr) override
			{
				if (aPtr == nullptr)
					return;

				ChunkHeader* block = (ChunkHeader*)((Byte*)aPtr - sizeof(ChunkHeader));
				Debug::Assert(block->myIsFree == false, "This block is already free");
				if (block->myIsFree)
					return;

				uint fullBlockSize = block->myUserDataSize + sizeof(ChunkHeader) + (myBoundsCheckOn == 1 ? BoundsCheckSize * 2 : 0);
				myFreePoolSize += block->myUserDataSize;

				ChunkHeader* headBlock = block;
				ChunkHeader* prev = block->myPrevious;
				ChunkHeader* next = block->myNext;

				// If the node before is free I merge it with this one
				if (block->myPrevious != nullptr && block->myPrevious->myIsFree == true)
				{
					headBlock = block->myPrevious;
					prev = block->myPrevious->myPrevious;
					next = block->myNext;

					fullBlockSize += myBoundsCheckOn == 1 ? block->myPrevious->myUserDataSize + sizeof(ChunkHeader) + BoundsCheckSize * 2 : block->myPrevious->myUserDataSize + sizeof(ChunkHeader);
					if (block->myNext)
					{
						block->myNext->myPrevious = headBlock;

						if (block->myNext->myIsFree)
						{
							next = block->myNext->myNext;
							if (block->myNext->myNext)
								block->myNext->myNext->myPrevious = headBlock;

							fullBlockSize += myBoundsCheckOn == 1 ? block->myNext->myUserDataSize + sizeof(ChunkHeader) + BoundsCheckSize * 2 : block->myNext->myUserDataSize + sizeof(ChunkHeader);
						}
					}
				}
				else
				{
					// If next node is free lets merge it to the current one
					if (block->myNext && block->myNext->myIsFree)
					{
						headBlock = block;
						prev = block->myPrevious;
						next = block->myNext->myNext;

						// Include the next node in the block size so we trash it as well
						fullBlockSize += myBoundsCheckOn == 1 ? block->myNext->myUserDataSize + sizeof(ChunkHeader) + BoundsCheckSize * 2 : block->myNext->myUserDataSize + sizeof(ChunkHeader);
					}
				}

				// Create the free block
				Byte* freeBlockStart = (Byte*)headBlock;
				if (myTrashOnFree == 1)
					SetMemory(myBoundsCheckOn == 1 ? freeBlockStart - BoundsCheckSize : freeBlockStart, TrashOnFreeSignature, fullBlockSize);

				uint freeUserDataSize = fullBlockSize - sizeof(ChunkHeader);
				freeUserDataSize = (myBoundsCheckOn == 1) ? freeUserDataSize - BoundsCheckSize * 2 : freeUserDataSize;

				ChunkHeader freeBlock(freeUserDataSize);
				freeBlock.myPrevious = prev;
				freeBlock.myNext = next;
				freeBlock.Write(freeBlockStart);

				// Move the memory around if guards are needed
				if (myBoundsCheckOn == 1)
				{
					CopyMemory(freeBlockStart - BoundsCheckSize, StartBound, BoundsCheckSize);
					CopyMemory(freeBlockStart + sizeof(ChunkHeader) + freeUserDataSize, EndBound, BoundsCheckSize);
				}
			}

			const bool IntegrityCheck() const override
			{
				if (myBoundsCheckOn == 1)
				{
					ChunkHeader* temp = (ChunkHeader*)(myPoolMemory + BoundsCheckSize);
					while (temp != nullptr)
					{
						if (CompareMemory(((Byte*)temp) - BoundsCheckSize, StartBound, BoundsCheckSize) != 0)
							return false;
						if (CompareMemory(((Byte*)temp) + sizeof(ChunkHeader) + temp->myUserDataSize, EndBound, BoundsCheckSize) != 0)
							return false;

						temp = temp->myNext;
					}
				}

				return true;
			}

		private:
			void Initialize(const uint& aPoolSizeInBytes, const bool isBoundsCheckOn)
			{
				myBoundsCheckOn = isBoundsCheckOn ? 1 : 0;
				myPoolMemory = static_cast<Byte*>(malloc(aPoolSizeInBytes));

				myFreePoolSize = aPoolSizeInBytes - sizeof(ChunkHeader);
				myTotalPoolSize = aPoolSizeInBytes;

				if (myTrashOnCreation == 1)
					SetMemory(myPoolMemory, TrashOnCreationSignature, aPoolSizeInBytes);

				if (myBoundsCheckOn == 1)
				{
					myFreePoolSize -= BoundsCheckSize * 2;

					ChunkHeader freeChunk(aPoolSizeInBytes - sizeof(ChunkHeader) - 2 * BoundsCheckSize);
					freeChunk.Write(myPoolMemory + BoundsCheckSize);
					CopyMemory(myPoolMemory, StartBound, BoundsCheckSize);
					CopyMemory(myPoolMemory + aPoolSizeInBytes - BoundsCheckSize, EndBound, BoundsCheckSize);
				}
				else
				{
					ChunkHeader freeChunk(aPoolSizeInBytes - sizeof(ChunkHeader));
					freeChunk.Write(myPoolMemory);
				}
			}

			class ChunkHeader
			{
			public:
				ChunkHeader(uint aUserDataSize) : myNext(nullptr), myPrevious(nullptr), myUserDataSize(aUserDataSize), myIsFree(true) { }
				void Write(void* aDestination) { CopyMemory(aDestination, this, sizeof(ChunkHeader)); }
				void Read(void* aSource) { CopyMemory(this, aSource, sizeof(ChunkHeader)); }

				ChunkHeader* myNext;
				ChunkHeader* myPrevious;
				uint myUserDataSize;
				bool myIsFree;
			};

		private:
			Byte* myPoolMemory;
		};
	}
}