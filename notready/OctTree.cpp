#include "OctTree.h"
#include "IntersectionUtils.h"

namespace System
{
	namespace Math
	{
		OctTree::IEntity::IEntity()
			: myOctTreeNode(nullptr)
			, myOctTree(nullptr)
		{ }

		void OctTree::IEntity::UpdateOctTreeNode()
		{
			OctTree* octTree = myOctTree;
			myOctTreeNode->Remove(this);
			octTree->Insert(this);
		}

		OctTree::Node::Node(const Math::Vector3& aCenterLocation, const Float32 aHalfSize)
			: myCenter(aCenterLocation)
			, myHalfSize(aHalfSize)
			, myChildEntities(0)
		{
			for (int i = 0; i < 8; ++i)
				myChildNodes[i].reset(nullptr);
		}

		OctTree::Node::Node(Node&& aNode) noexcept
			: myCenter(aNode.myCenter)
			, myHalfSize(aNode.myHalfSize)
			, myChildEntities(std::move(aNode.myChildEntities))
		{
			for (int i = 0; i < 8; ++i)
				myChildNodes[i].swap(aNode.myChildNodes[i]);
		}

		void OctTree::Node::Insert(IEntity* anEntity)
		{
			System::Debug::Assert(anEntity->myOctTree != nullptr, "Oct-tree node has to belong to a tree before inserting entities.");

			Math::Vector3 octantCenter;
			const int containerOctant = GetChildOctantFittingEntity(anEntity, octantCenter);
			if (containerOctant == -1)
			{
				Debug::Assert(anEntity->myOctTreeNode == nullptr, "The entity already belongs to an octtree node, but we're trying to assign it a new one.");
				anEntity->myOctTreeNode = this;
				myChildEntities.Add(anEntity);
			}
			else
			{
				if (myChildNodes[containerOctant] == nullptr)
					myChildNodes[containerOctant].reset(new Node(octantCenter, myHalfSize / 2));

				myChildNodes[containerOctant]->Insert(anEntity);
			}
		}

		void OctTree::Node::Remove(IEntity* anEntity)
		{
			myChildEntities.RemoveCyclic(anEntity);

			anEntity->myOctTree = nullptr;
			anEntity->myOctTreeNode = nullptr;
		}

		void OctTree::Node::GetEntitiesWithin(const Math::AxisAlignedBox& aBoundingBox, Collections::ICollection<IEntity*>& anEntityListOut) const
		{
			for (IEntity* entity : myChildEntities)
			{
				if (aBoundingBox.Intersects(entity->GetBoundingBox()))
					anEntityListOut.Add(entity);
			}

			for (int i = 0; i < 8; ++i)
			{
				if (myChildNodes[i] == nullptr)
					continue;

				Math::AxisAlignedBox childBounds(GetChildOctantCenter(i), Math::Vector3(myHalfSize / 2));
				if (!aBoundingBox.Intersects(childBounds))
					continue;

				if (aBoundingBox.Contains(childBounds))
					myChildNodes[i]->GetAllEntitiesWithin(anEntityListOut);
				else
					myChildNodes[i]->GetAllEntitiesWithin(anEntityListOut);
			}
		}

		bool OctTree::Node::IsLeafNode() const
		{
			return
				myChildNodes[0] == nullptr &&
				myChildNodes[1] == nullptr &&
				myChildNodes[2] == nullptr &&
				myChildNodes[3] == nullptr &&

				myChildNodes[4] == nullptr &&
				myChildNodes[5] == nullptr &&
				myChildNodes[6] == nullptr &&
				myChildNodes[7] == nullptr;
		}

		Math::Vector3 OctTree::Node::GetChildOctantCenter(const int anOctant) const
		{
			const int right = 1;
			const int up = 2;
			const int forward = 4;

			const Math::Vector3 centerOffset(
				(anOctant & right)		!= 0 ? 1.f : -1.f,
				(anOctant & up)			!= 0 ? 1.f : -1.f,
				(anOctant & forward)	!= 0 ? 1.f : -1.f
			);
			return myCenter + (centerOffset * (myHalfSize / 2));
		}

		int OctTree::Node::GetChildOctantFittingEntity(IEntity* anEntity, Math::Vector3& anOctantCenterOut) const
		{
			const Math::AxisAlignedBox& entityBoundingBox = anEntity->GetBoundingBox();
			Debug::Assert(Math::AxisAlignedBox(myCenter, Math::Vector3(myHalfSize * 2)).Contains(entityBoundingBox), "The entity doesn't fit in the current bounding box. It should not have tried to go this deep into the tree.");

			for (int i = 0; i < 8; ++i)
			{
				const Math::Vector3 childOctantCenter = GetChildOctantCenter(i);
				if (Math::AxisAlignedBox(childOctantCenter, Math::Vector3(myHalfSize)).Contains(entityBoundingBox))
				{
					anOctantCenterOut = childOctantCenter;
					return i;
				}
			}

			return -1;
		}

		void OctTree::Node::GetAllEntitiesWithin(Collections::ICollection<IEntity*>& anEntityListOut) const
		{
			for (IEntity* entity : myChildEntities)
				anEntityListOut.Add(entity);

			for (int i = 0; i < 8; ++i)
			{
				if (myChildNodes[i] != nullptr)
					myChildNodes[i]->GetAllEntitiesWithin(anEntityListOut);
			}
		}

		OctTree::OctTree(const Math::Vector3& aCenter, Float32 aHalfSize)
			: myRootNode(new Node(aCenter, aHalfSize))
		{ }

		void OctTree::Insert(IEntity* anEntity)
		{
			const Math::AxisAlignedBox octTreeBounds(myRootNode->myCenter, Math::Vector3(myRootNode->myHalfSize * 2));
			Debug::Assert(octTreeBounds.Contains(anEntity->GetBoundingBox()), "Attempted to insert an object into the octtree that does not fit into the root node.");
			anEntity->myOctTree = this;
			myRootNode->Insert(anEntity);
		}

		void OctTree::Remove(IEntity* anEntity)
		{
			return myRootNode->Remove(anEntity);
		}

		void OctTree::GetEntitiesWithin(const Math::AxisAlignedBox& aBoundingBox, Collections::ICollection<IEntity*>& anEntityListOut) const
		{
			const Math::AxisAlignedBox octTreeBounds(myRootNode->myCenter, Math::Vector3(myRootNode->myHalfSize * 2));
			if (aBoundingBox.Contains(octTreeBounds))
				myRootNode->GetAllEntitiesWithin(anEntityListOut);
			else
				myRootNode->GetEntitiesWithin(aBoundingBox, anEntityListOut);
		}
	}
}
