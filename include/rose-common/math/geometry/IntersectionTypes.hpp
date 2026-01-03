#pragma once

#include "../../RoseCommon_Namespace.hpp"

#include "Rectangle.hpp"
#include "../Constants.hpp"
#include "../Vector.hpp"

namespace ROSECOMMON_MATH_NAMESPACE
{
	// Basic types for use with the intersection functions.
	// If there's a need to create more proper classes of these, they
	// should be removed from here.

	template <int N, typename T>
	struct Box
	{
		VectorN<N, T> Min;
		VectorN<N, T> Max;
	};

	template <int N, typename T>
	struct Capsule
	{
		VectorN<N, T> A;
		VectorN<N, T> B;
		T Radius;
	};

	template <typename T>
	struct Cone
	{
		Vector3<T> Origin;
		Vector3<T> Direction;
		T Height;
		T RadianAngle;
	};

	template <typename T>
	struct Disc
	{
		Vector3<T> Center;
		Vector3<T> Normal;
		T Radius;
	};

	template <int N, typename T>
	struct Ellipsoid
	{
		VectorN<N, T> Center;
		VectorN<N, T> Radii;
	};

	template <typename T>
	struct Frustrum
	{
		Vector3<T> Apex;
		Vector3<T> Up;
		Vector3<T> Direction;

		T Left;
		T Right;
		T Bottom;
		T Top;
		T Near;
		T Far;
	};

	template <int N, typename T>
	struct LineSegment
	{
		VectorN<N, T> A;
		VectorN<N, T> B;
	};

	template <typename T>
	struct Plane
	{
		Vector3<T> Normal;
		T Distance;
	};

	template <int N, typename T>
	struct Radius
	{
		VectorN<N, T> Center;
		T Radius;
	};

	template <int N, typename T>
	struct Ray
	{
		VectorN<N, T> Origin;
		VectorN<N, T> Direction;
	};

	template <int N, typename T>
	struct Triangle
	{
		VectorN<N, T> A;
		VectorN<N, T> B;
		VectorN<N, T> C;
	};
}
