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
	struct BoxNT
	{
		VectorNT<N, T> Min;
		VectorNT<N, T> Max;
	};

	template <int N, typename T>
	struct CapsuleNT
	{
		VectorNT<N, T> A;
		VectorNT<N, T> B;
		T Radius;
	};

	template <typename T>
	struct Cone3T
	{
		Vector3T<T> Origin;
		Vector3T<T> Direction;
		T Height;
		T RadianAngle;
	};

	template <typename T>
	struct Disc3T
	{
		Vector3T<T> Center;
		Vector3T<T> Normal;
		T Radius;
	};

	template <int N, typename T>
	struct EllipsoidNT
	{
		VectorNT<N, T> Center;
		VectorNT<N, T> Radii;
	};

	template <typename T>
	struct Frustrum
	{
		Vector3T<T> Apex;
		Vector3T<T> Up;
		Vector3T<T> Direction;

		T Left;
		T Right;
		T Bottom;
		T Top;
		T Near;
		T Far;
	};

	template <int N, typename T>
	struct LineSegmentNT
	{
		VectorNT<N, T> A;
		VectorNT<N, T> B;
	};

	template <typename T>
	struct Plane3T
	{
		Vector3T<T> Normal;
		T Distance;
	};

	template <int N, typename T>
	struct RadiusNT
	{
		VectorNT<N, T> Center;
		T Radius;
	};

	template <int N, typename T>
	struct RayNT
	{
		VectorNT<N, T> Origin;
		VectorNT<N, T> Direction;
	};

	template <int N, typename T>
	struct TriangleNT
	{
		VectorNT<N, T> A;
		VectorNT<N, T> B;
		VectorNT<N, T> C;
	};
}
