#pragma once
#include "AxisAlignedBox.h"
#include "Vector3.h"
#include "../Collections/List.h"

#include <memory>

namespace System
{
	namespace Math
	{
		class OctTree
		{
		protected:
			class Node;

		public:
			class IEntity
			{
				friend class Node;
				friend class OctTree;
			public:
				IEntity();

			protected:
				void UpdateOctTreeNode();

			private:
				virtual const Math::AxisAlignedBox GetBoundingBox() const = 0;

			private:
				OctTree* myOctTree;
				Node* myOctTreeNode;
			};

		protected:
			class Node
			{
				friend class OctTree;
			public:
				Node(const Math::Vector3& aCenterLocation, const Float32 aHalfSize);
				Node(Node&& aNode) noexcept;
				Node(const Node& aNode) = delete;

				void Insert(IEntity* anEntity);
				void Remove(IEntity* anEntity);

				void GetEntitiesWithin(const Math::AxisAlignedBox& aBoundingBox, Collections::ICollection<IEntity*>& anEntityListOut) const;

			private:
				// Returns True if there are no child nodes.
				bool IsLeafNode() const;
				Math::Vector3 GetChildOctantCenter(const int anOctant) const;
				int GetChildOctantFittingEntity(IEntity* anEntity, Math::Vector3& anOctantCenterOut) const;

				void GetAllEntitiesWithin(Collections::ICollection<IEntity*>& anEntityListOut) const;

			private:
				std::unique_ptr<Node> myChildNodes[8];
				Collections::List<IEntity*> myChildEntities;

				Math::Vector3 myCenter;
				Float32 myHalfSize;
			};

		public:
			OctTree(const Math::Vector3& aCenter, Float32 aHalfSize);

			void Insert(IEntity* anEntity);
			void Remove(IEntity* anEntity);

			void GetEntitiesWithin(const Math::AxisAlignedBox& aBoundingBox, Collections::ICollection<IEntity*>& anEntityListOut) const;

		private:
			std::unique_ptr<Node> myRootNode;
		};
	}
}
