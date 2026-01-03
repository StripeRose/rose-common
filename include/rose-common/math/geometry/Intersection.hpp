#pragma once

#include "../../RoseCommon_Namespace.hpp"
#include "IntersectionTypes.hpp"

/*
	d: Distance only
	i: Intersection only
	x: Both

				 B C C D E F L P P R R T
				 o a o i l r i l o a a r
				+-+-+-+-+-+-+-+-+-+-+-+-+
	Box         |i| | | | | | | |i|i| | |
	Capsule     | | | | | | | | | | | | |
	Cone        | | | | | | | | | | | | |
	Disc        | | | | | | | | | | | | |
	Ellipsoid   | | | | | | | | | | | | |
	Frustrum    | | | | | | | | | | | | |
	Line        | | | | | | | | | | | | |
	Plane       | | | | | | | | | | | | |
	Point       |i| | | | | | | |i|i| | |
	Radius      |i| | | | | | | |i|i| | |
	Ray         | | | | | | | | | | | | |
	Triangle    | | | | | | | | | | | | |
				+-+-+-+-+-+-+-+-+-+-+-+-+
*/

// Implementation reference:
// https://github.com/Jojendersie/Epsilon-Intersection/

namespace ROSECOMMON_MATH_NAMESPACE
{
	template <typename T, int N> bool Intersects(const Box<N, T>& aBox, const Box<N, T>& aBoxB);
	//template <typename T, int N> bool Intersects(const Box<N, T>& aBox, const Capsule<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const Box<3, T>& aBox, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const Box<3, T>& aBox, const Disc<T>& aDisc);
	//template <typename T, int N> bool Intersects(const Box<N, T>& aBox, const Ellipsoid<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Box<3, T>& aBox, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const Box<N, T>& aBox, const LineSegment<N, T>& aLine);
	//template <typename T>        bool Intersects(const Box<3, T>& aBox, const Plane<T>& aPlane);
	template <typename T, int N> bool Intersects(const Box<N, T>& aBox, const VectorN<N, T>& aPoint);
	template <typename T, int N> bool Intersects(const Box<N, T>& aBox, const Radius<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const Box<N, T>& aBox, const Ray<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const Box<N, T>& aBox, const Triangle<N, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const Capsule<N, T>& aCapsule, const Box<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const Capsule<N, T>& aCapsule, const Capsule<N, T>& aCapsuleB);
	//template <typename T>        bool Intersects(const Capsule<3, T>& aCapsule, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const Capsule<3, T>& aCapsule, const Disc<T>& aDisc);
	//template <typename T, int N> bool Intersects(const Capsule<N, T>& aCapsule, const Ellipsoid<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Capsule<3, T>& aCapsule, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const Capsule<N, T>& aCapsule, const LineSegment<N, T>& aLine);
	//template <typename T>        bool Intersects(const Capsule<3, T>& aCapsule, const Plane<T>& aPlane);
	//template <typename T, int N> bool Intersects(const Capsule<N, T>& aCapsule, const VectorN<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const Capsule<N, T>& aCapsule, const Radius<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const Capsule<N, T>& aCapsule, const Ray<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const Capsule<N, T>& aCapsule, const Triangle<N, T>& aTriangle);

	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Box<3, T>& aBox);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Capsule<3, T>& aCapsule);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Cone<T>& aConeB);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Disc<T>& aDisc);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Ellipsoid<3, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Frustrum<T>& aFrustrum);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const LineSegment<3, T>& aLine);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Plane<T>& aPlane);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const VectorN<3, T>& aPoint);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Radius<3, T>& aRadius);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Ray<3, T>& aRay);
	//template <typename T>        bool Intersects(const Cone<T>& aCone, const Triangle<3, T>& aTriangle);

	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Box<3, T>& aBox);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Capsule<3, T>& aCapsule);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Disc<T>& aDiscB);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Ellipsoid<3, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Frustrum<T>& aFrustrum);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const LineSegment<3, T>& aLine);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Plane<T>& aPlane);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const VectorN<3, T>& aPoint);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Radius<3, T>& aRadius);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Ray<3, T>& aRay);
	//template <typename T>        bool Intersects(const Disc<T>& aDisc, const Triangle<3, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const Ellipsoid<N, T>& anEllipsoid, const Box<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const Ellipsoid<N, T>& anEllipsoid, const Capsule<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const Ellipsoid<3, T>& anEllipsoid, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const Ellipsoid<3, T>& anEllipsoid, const Disc<T>& aDisc);
	//template <typename T, int N> bool Intersects(const Ellipsoid<N, T>& anEllipsoid, const Ellipsoid<N, T>& anEllipsoidB);
	//template <typename T>        bool Intersects(const Ellipsoid<3, T>& anEllipsoid, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const Ellipsoid<N, T>& anEllipsoid, const LineSegment<N, T>& aLine);
	//template <typename T>        bool Intersects(const Ellipsoid<3, T>& anEllipsoid, const Plane<T>& aPlane);
	//template <typename T, int N> bool Intersects(const Ellipsoid<N, T>& anEllipsoid, const VectorN<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const Ellipsoid<N, T>& anEllipsoid, const Radius<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const Ellipsoid<N, T>& anEllipsoid, const Ray<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const Ellipsoid<N, T>& anEllipsoid, const Triangle<N, T>& aTriangle);

	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Box<3, T>& aBox);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Capsule<3, T>& aCapsule);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Disc<T>& aDisc);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Ellipsoid<3, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Frustrum<T>& aFrustrumB);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const LineSegment<3, T>& aLine);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Plane<T>& aPlane);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const VectorN<3, T>& aPoint);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Radius<3, T>& aRadius);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Ray<3, T>& aRay);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Triangle<3, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const LineSegment<N, T>& aLine, const Box<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const LineSegment<N, T>& aLine, const Capsule<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const LineSegment<3, T>& aLine, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const LineSegment<3, T>& aLine, const Disc<T>& aDisc);
	//template <typename T, int N> bool Intersects(const LineSegment<N, T>& aLine, const Ellipsoid<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const LineSegment<3, T>& aLine, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const LineSegment<N, T>& aLine, const LineSegment<N, T>& aLineB);
	//template <typename T>        bool Intersects(const LineSegment<3, T>& aLine, const Plane<T>& aPlane);
	//template <typename T, int N> bool Intersects(const LineSegment<N, T>& aLine, const VectorN<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const LineSegment<N, T>& aLine, const Radius<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const LineSegment<N, T>& aLine, const Ray<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const LineSegment<N, T>& aLine, const Triangle<N, T>& aTriangle);

	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Box<3, T>& aBox);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Capsule<3, T>& aCapsule);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Disc<T>& aDisc);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Ellipsoid<3, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Frustrum<T>& aFrustrum);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const LineSegment<3, T>& aLine);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Plane<T>& aPlaneB);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const VectorN<3, T>& aPoint);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Radius<3, T>& aRadius);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Ray<3, T>& aRay);
	//template <typename T>        bool Intersects(const Plane<T>& aPlane, const Triangle<3, T>& aTriangle);

	template <typename T, int N> bool Intersects(const VectorN<N, T>& aPoint, const Box<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const VectorN<N, T>& aPoint, const Capsule<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const VectorN<3, T>& aPoint, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const VectorN<3, T>& aPoint, const Disc<T>& aDisc);
	//template <typename T, int N> bool Intersects(const VectorN<N, T>& aPoint, const Ellipsoid<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const VectorN<3, T>& aPoint, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const VectorN<N, T>& aPoint, const LineSegment<N, T>& aLine);
	//template <typename T>        bool Intersects(const VectorN<3, T>& aPoint, const Plane<T>& aPlane);
	template <typename T, int N> bool Intersects(const VectorN<N, T>& aPoint, const VectorN<N, T>& aPointB);
	template <typename T, int N> bool Intersects(const VectorN<N, T>& aPoint, const Radius<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const VectorN<N, T>& aPoint, const Ray<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const VectorN<N, T>& aPoint, const Triangle<N, T>& aTriangle);

	template <typename T, int N> bool Intersects(const Radius<N, T>& aRadius, const Box<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const Radius<N, T>& aRadius, const Capsule<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const Radius<3, T>& aRadius, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const Radius<3, T>& aRadius, const Disc<T>& aDisc);
	//template <typename T, int N> bool Intersects(const Radius<N, T>& aRadius, const Ellipsoid<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Radius<3, T>& aRadius, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const Radius<N, T>& aRadius, const LineSegment<N, T>& aLine);
	//template <typename T>        bool Intersects(const Radius<3, T>& aRadius, const Plane<T>& aPlane);
	template <typename T, int N> bool Intersects(const Radius<N, T>& aRadius, const VectorN<N, T>& aPoint);
	template <typename T, int N> bool Intersects(const Radius<N, T>& aRadius, const Radius<N, T>& aRadiusB);
	//template <typename T, int N> bool Intersects(const Radius<N, T>& aRadius, const Ray<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const Radius<N, T>& aRadius, const Triangle<N, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const Ray<N, T>& aRay, const Box<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const Ray<N, T>& aRay, const Capsule<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const Ray<3, T>& aRay, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const Ray<3, T>& aRay, const Disc<T>& aDisc);
	//template <typename T, int N> bool Intersects(const Ray<N, T>& aRay, const Ellipsoid<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Ray<3, T>& aRay, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const Ray<N, T>& aRay, const LineSegment<N, T>& aLine);
	//template <typename T>        bool Intersects(const Ray<3, T>& aRay, const Plane<T>& aPlane);
	//template <typename T, int N> bool Intersects(const Ray<N, T>& aRay, const VectorN<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const Ray<N, T>& aRay, const Radius<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const Ray<N, T>& aRay, const Ray<N, T>& aRayB);
	//template <typename T, int N> bool Intersects(const Ray<N, T>& aRay, const Triangle<N, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const Triangle<N, T>& aTriangle, const Box<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const Triangle<N, T>& aTriangle, const Capsule<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const Triangle<3, T>& aTriangle, const Cone<T>& aCone);
	//template <typename T>        bool Intersects(const Triangle<3, T>& aTriangle, const Disc<T>& aDisc);
	//template <typename T, int N> bool Intersects(const Triangle<N, T>& aTriangle, const Ellipsoid<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Triangle<3, T>& aTriangle, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const Triangle<N, T>& aTriangle, const LineSegment<N, T>& aLine);
	//template <typename T>        bool Intersects(const Triangle<3, T>& aTriangle, const Plane<T>& aPlane);
	//template <typename T, int N> bool Intersects(const Triangle<N, T>& aTriangle, const VectorN<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const Triangle<N, T>& aTriangle, const Radius<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const Triangle<N, T>& aTriangle, const Ray<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const Triangle<N, T>& aTriangle, const Triangle<N, T>& aTriangleB);
}

#include "Intersection_Box.inl"
#include "Intersection_Capsule.inl"
#include "Intersection_Cone.inl"
#include "Intersection_Disc.inl"
#include "Intersection_Ellipsoid.inl"
#include "Intersection_Frustrum.inl"
#include "Intersection_Line.inl"
#include "Intersection_Plane.inl"
#include "Intersection_Point.inl"
#include "Intersection_Radius.inl"
#include "Intersection_Ray.inl"
#include "Intersection_Triangle.inl"
