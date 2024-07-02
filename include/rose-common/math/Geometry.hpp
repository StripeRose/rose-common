#pragma once

#include <optional>

namespace RoseCommon::Math
{
	template <typename VectorT>
	class Box
	{
	public:
		static constexpr Box FromExtents(const VectorT& aMinExtents, const VectorT& aMaxExtents)
		{
			Box extentsBox;
			extentsBox.Size = aMaxExtents - aMinExtents;
			extentsBox.Center = aMinExtents + (extentsBox.Size / 2);
			return extentsBox;
		}

	public:
		constexpr Box()
			: Box(VectorT::Zero(), VectorT::Zero())
		{ }

		constexpr Box(VectorT aCenterPoint, VectorT aSize)
			: Center(aCenterPoint)
			, Size(aSize)
		{ }

	public:
		constexpr bool Contains(const VectorT& aPoint) const
		{
			VectorT minExtents, maxExtents;
			ToExtents(minExtents, maxExtents);
			return !(maxExtents < aPoint) && !(aPoint < minExtents);
		}

		constexpr bool Contains(const Box& aBox) const
		{
			VectorT thisMin, thisMax, otherMin, otherMax;
			ToExtents(thisMin, thisMax);
			aBox.ToExtents(otherMin, otherMax);

			return
				otherMin >= thisMin &&
				thisMax >= otherMax;
		}

		constexpr typename VectorT::ComponentType Content() const
		{
			return Size.Content();
		}

		constexpr bool Intersects(const Box& aBox) const
		{
			VectorT thisMin, thisMax, otherMin, otherMax;
			ToExtents(thisMin, thisMax);
			aBox.ToExtents(otherMin, otherMax);

			return thisMin < otherMax && thisMax > otherMin;
		}

		constexpr std::optional<Box> Intersection(const Box& aBox) const
		{
			if (Intersects(aBox) == false)
				return { };

			VectorT thisMin, thisMax, otherMin, otherMax;
			ToExtents(thisMin, thisMax);
			aBox.ToExtents(otherMin, otherMax);

			return Box::FromExtents(
				VectorT::Max(thisMin, otherMin),
				VectorT::Min(thisMax, otherMax)
			);
		}

		/*bool Intersection(const Rectangle& aRect, Rectangle& aResultRect, Rectangle& aUVResult) const
		{
			if (IntersectingRect(aRect, aResultRect) == false)
			{
				return false;
			}

			const T aPoint1X = X;
			const T aPoint1Y = Y;
			const T aPoint2X = X + Width;
			const T aPoint2Y = Y + Height;
			const T bPoint1X = aRect.X;
			const T bPoint1Y = aRect.Y;
			const T bPoint2X = aRect.X + aRect.Width;
			const T bPoint2Y = aRect.Y + aRect.Height;

			T uv1X;
			T uv1Y;
			T uv2X;
			T uv2Y;

			uv1X = (aPoint1X - bPoint1X) / (bPoint2X - bPoint1X);
			uv1Y = (aPoint1Y - bPoint1Y) / (bPoint2Y - bPoint1Y);

			uv2X = (aPoint2X - bPoint1X) / (bPoint2X - bPoint1X);
			uv2Y = (aPoint2Y - bPoint1Y) / (bPoint2Y - bPoint1Y);

			aUVResult.X = uv1X;
			aUVResult.Y = uv1Y;
			aUVResult.Width = uv2X - uv1X;
			aUVResult.Height = uv2Y - uv1Y;

			return true;

		}*/

		constexpr void ToExtents(VectorT& outMinExtents, VectorT& outMaxExtents) const
		{
			outMinExtents = Center - (Size / 2);
			outMaxExtents = outMinExtents + Size;
		}

	public:
		VectorT Center;
		VectorT Size;
	};

	template <typename VectorT>
	class Sphere
	{
	public:
		constexpr Sphere()
			: Sphere(VectorT::Zero(), 1.f)
		{ }

		constexpr Sphere(const VectorT& aCenter, const typename VectorT::ComponentType& aRadius)
			: Center(aCenter)
			, Radius(aRadius)
		{ }

		constexpr bool Contains(const VectorT& aPoint) const
		{
			return VectorT::DistanceSquared(Center, aPoint) < (Radius * Radius);
		}

		// Todo: float GetContent() - length/area/volume

	public:
		VectorT Center;
		typename VectorT::ComponentType Radius;
	};
}