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
	template <typename T, int N> bool Intersects(const BoxNT<N, T>& aBox, const BoxNT<N, T>& aBoxB);
	//template <typename T, int N> bool Intersects(const BoxNT<N, T>& aBox, const CapsuleNT<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const BoxNT<3, T>& aBox, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const BoxNT<3, T>& aBox, const Disc3T<T>& aDisc);
	//template <typename T, int N> bool Intersects(const BoxNT<N, T>& aBox, const EllipsoidNT<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const BoxNT<3, T>& aBox, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const BoxNT<N, T>& aBox, const LineSegmentNT<N, T>& aLine);
	//template <typename T>        bool Intersects(const BoxNT<3, T>& aBox, const Plane3T<T>& aPlane);
	template <typename T, int N> bool Intersects(const BoxNT<N, T>& aBox, const VectorNT<N, T>& aPoint);
	template <typename T, int N> bool Intersects(const BoxNT<N, T>& aBox, const RadiusNT<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const BoxNT<N, T>& aBox, const RayNT<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const BoxNT<N, T>& aBox, const TriangleNT<N, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const CapsuleNT<N, T>& aCapsule, const BoxNT<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const CapsuleNT<N, T>& aCapsule, const CapsuleNT<N, T>& aCapsuleB);
	//template <typename T>        bool Intersects(const CapsuleNT<3, T>& aCapsule, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const CapsuleNT<3, T>& aCapsule, const Disc3T<T>& aDisc);
	//template <typename T, int N> bool Intersects(const CapsuleNT<N, T>& aCapsule, const EllipsoidNT<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const CapsuleNT<3, T>& aCapsule, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const CapsuleNT<N, T>& aCapsule, const LineSegmentNT<N, T>& aLine);
	//template <typename T>        bool Intersects(const CapsuleNT<3, T>& aCapsule, const Plane3T<T>& aPlane);
	//template <typename T, int N> bool Intersects(const CapsuleNT<N, T>& aCapsule, const VectorNT<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const CapsuleNT<N, T>& aCapsule, const RadiusNT<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const CapsuleNT<N, T>& aCapsule, const RayNT<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const CapsuleNT<N, T>& aCapsule, const TriangleNT<N, T>& aTriangle);

	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const BoxNT<3, T>& aBox);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const CapsuleNT<3, T>& aCapsule);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const Cone3T<T>& aConeB);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const Disc3T<T>& aDisc);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const EllipsoidNT<3, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const Frustrum<T>& aFrustrum);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const LineSegmentNT<3, T>& aLine);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const Plane3T<T>& aPlane);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const VectorNT<3, T>& aPoint);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const RadiusNT<3, T>& aRadius);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const RayNT<3, T>& aRay);
	//template <typename T>        bool Intersects(const Cone3T<T>& aCone, const TriangleNT<3, T>& aTriangle);

	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const BoxNT<3, T>& aBox);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const CapsuleNT<3, T>& aCapsule);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const Disc3T<T>& aDiscB);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const EllipsoidNT<3, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const Frustrum<T>& aFrustrum);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const LineSegmentNT<3, T>& aLine);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const Plane3T<T>& aPlane);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const VectorNT<3, T>& aPoint);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const RadiusNT<3, T>& aRadius);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const RayNT<3, T>& aRay);
	//template <typename T>        bool Intersects(const Disc3T<T>& aDisc, const TriangleNT<3, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const EllipsoidNT<N, T>& anEllipsoid, const BoxNT<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const EllipsoidNT<N, T>& anEllipsoid, const CapsuleNT<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const EllipsoidNT<3, T>& anEllipsoid, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const EllipsoidNT<3, T>& anEllipsoid, const Disc3T<T>& aDisc);
	//template <typename T, int N> bool Intersects(const EllipsoidNT<N, T>& anEllipsoid, const EllipsoidNT<N, T>& anEllipsoidB);
	//template <typename T>        bool Intersects(const EllipsoidNT<3, T>& anEllipsoid, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const EllipsoidNT<N, T>& anEllipsoid, const LineSegmentNT<N, T>& aLine);
	//template <typename T>        bool Intersects(const EllipsoidNT<3, T>& anEllipsoid, const Plane3T<T>& aPlane);
	//template <typename T, int N> bool Intersects(const EllipsoidNT<N, T>& anEllipsoid, const VectorNT<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const EllipsoidNT<N, T>& anEllipsoid, const RadiusNT<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const EllipsoidNT<N, T>& anEllipsoid, const RayNT<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const EllipsoidNT<N, T>& anEllipsoid, const TriangleNT<N, T>& aTriangle);

	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const BoxNT<3, T>& aBox);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const CapsuleNT<3, T>& aCapsule);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Disc3T<T>& aDisc);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const EllipsoidNT<3, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Frustrum<T>& aFrustrumB);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const LineSegmentNT<3, T>& aLine);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const Plane3T<T>& aPlane);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const VectorNT<3, T>& aPoint);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const RadiusNT<3, T>& aRadius);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const RayNT<3, T>& aRay);
	//template <typename T>        bool Intersects(const Frustrum<T>& aFrustrum, const TriangleNT<3, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const LineSegmentNT<N, T>& aLine, const BoxNT<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const LineSegmentNT<N, T>& aLine, const CapsuleNT<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const LineSegmentNT<3, T>& aLine, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const LineSegmentNT<3, T>& aLine, const Disc3T<T>& aDisc);
	//template <typename T, int N> bool Intersects(const LineSegmentNT<N, T>& aLine, const EllipsoidNT<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const LineSegmentNT<3, T>& aLine, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const LineSegmentNT<N, T>& aLine, const LineSegmentNT<N, T>& aLineB);
	//template <typename T>        bool Intersects(const LineSegmentNT<3, T>& aLine, const Plane3T<T>& aPlane);
	//template <typename T, int N> bool Intersects(const LineSegmentNT<N, T>& aLine, const VectorNT<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const LineSegmentNT<N, T>& aLine, const RadiusNT<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const LineSegmentNT<N, T>& aLine, const RayNT<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const LineSegmentNT<N, T>& aLine, const TriangleNT<N, T>& aTriangle);

	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const BoxNT<3, T>& aBox);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const CapsuleNT<3, T>& aCapsule);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const Disc3T<T>& aDisc);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const EllipsoidNT<3, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const Frustrum<T>& aFrustrum);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const LineSegmentNT<3, T>& aLine);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const Plane3T<T>& aPlaneB);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const VectorNT<3, T>& aPoint);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const RadiusNT<3, T>& aRadius);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const RayNT<3, T>& aRay);
	//template <typename T>        bool Intersects(const Plane3T<T>& aPlane, const TriangleNT<3, T>& aTriangle);

	template <typename T, int N> bool Intersects(const VectorNT<N, T>& aPoint, const BoxNT<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const VectorNT<N, T>& aPoint, const CapsuleNT<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const VectorNT<3, T>& aPoint, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const VectorNT<3, T>& aPoint, const Disc3T<T>& aDisc);
	//template <typename T, int N> bool Intersects(const VectorNT<N, T>& aPoint, const EllipsoidNT<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const VectorNT<3, T>& aPoint, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const VectorNT<N, T>& aPoint, const LineSegmentNT<N, T>& aLine);
	//template <typename T>        bool Intersects(const VectorNT<3, T>& aPoint, const Plane3T<T>& aPlane);
	template <typename T, int N> bool Intersects(const VectorNT<N, T>& aPoint, const VectorNT<N, T>& aPointB);
	template <typename T, int N> bool Intersects(const VectorNT<N, T>& aPoint, const RadiusNT<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const VectorNT<N, T>& aPoint, const RayNT<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const VectorNT<N, T>& aPoint, const TriangleNT<N, T>& aTriangle);

	template <typename T, int N> bool Intersects(const RadiusNT<N, T>& aRadius, const BoxNT<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const RadiusNT<N, T>& aRadius, const CapsuleNT<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const RadiusNT<3, T>& aRadius, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const RadiusNT<3, T>& aRadius, const Disc3T<T>& aDisc);
	//template <typename T, int N> bool Intersects(const RadiusNT<N, T>& aRadius, const EllipsoidNT<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const RadiusNT<3, T>& aRadius, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const RadiusNT<N, T>& aRadius, const LineSegmentNT<N, T>& aLine);
	//template <typename T>        bool Intersects(const RadiusNT<3, T>& aRadius, const Plane3T<T>& aPlane);
	template <typename T, int N> bool Intersects(const RadiusNT<N, T>& aRadius, const VectorNT<N, T>& aPoint);
	template <typename T, int N> bool Intersects(const RadiusNT<N, T>& aRadius, const RadiusNT<N, T>& aRadiusB);
	//template <typename T, int N> bool Intersects(const RadiusNT<N, T>& aRadius, const RayNT<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const RadiusNT<N, T>& aRadius, const TriangleNT<N, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const RayNT<N, T>& aRay, const BoxNT<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const RayNT<N, T>& aRay, const CapsuleNT<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const RayNT<3, T>& aRay, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const RayNT<3, T>& aRay, const Disc3T<T>& aDisc);
	//template <typename T, int N> bool Intersects(const RayNT<N, T>& aRay, const EllipsoidNT<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const RayNT<3, T>& aRay, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const RayNT<N, T>& aRay, const LineSegmentNT<N, T>& aLine);
	//template <typename T>        bool Intersects(const RayNT<3, T>& aRay, const Plane3T<T>& aPlane);
	//template <typename T, int N> bool Intersects(const RayNT<N, T>& aRay, const VectorNT<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const RayNT<N, T>& aRay, const RadiusNT<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const RayNT<N, T>& aRay, const RayNT<N, T>& aRayB);
	//template <typename T, int N> bool Intersects(const RayNT<N, T>& aRay, const TriangleNT<N, T>& aTriangle);

	//template <typename T, int N> bool Intersects(const TriangleNT<N, T>& aTriangle, const BoxNT<N, T>& aBox);
	//template <typename T, int N> bool Intersects(const TriangleNT<N, T>& aTriangle, const CapsuleNT<N, T>& aCapsule);
	//template <typename T>        bool Intersects(const TriangleNT<3, T>& aTriangle, const Cone3T<T>& aCone);
	//template <typename T>        bool Intersects(const TriangleNT<3, T>& aTriangle, const Disc3T<T>& aDisc);
	//template <typename T, int N> bool Intersects(const TriangleNT<N, T>& aTriangle, const EllipsoidNT<N, T>& anEllipsoid);
	//template <typename T>        bool Intersects(const TriangleNT<3, T>& aTriangle, const Frustrum<T>& aFrustrum);
	//template <typename T, int N> bool Intersects(const TriangleNT<N, T>& aTriangle, const LineSegmentNT<N, T>& aLine);
	//template <typename T>        bool Intersects(const TriangleNT<3, T>& aTriangle, const Plane3T<T>& aPlane);
	//template <typename T, int N> bool Intersects(const TriangleNT<N, T>& aTriangle, const VectorNT<N, T>& aPoint);
	//template <typename T, int N> bool Intersects(const TriangleNT<N, T>& aTriangle, const RadiusNT<N, T>& aRadius);
	//template <typename T, int N> bool Intersects(const TriangleNT<N, T>& aTriangle, const RayNT<N, T>& aRay);
	//template <typename T, int N> bool Intersects(const TriangleNT<N, T>& aTriangle, const TriangleNT<N, T>& aTriangleB);
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
