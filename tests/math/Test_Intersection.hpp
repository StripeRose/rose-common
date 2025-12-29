#pragma once

#include <rose-common/math/geometry/Intersection.hpp>

#include "catch2/catch_template_test_macros.hpp"
#include "catch2/generators/catch_generators_all.hpp"

#define ANY_COMPONENT_SIG(Name, Tags) TEMPLATE_TEST_CASE_SIG(Name, Tags, ((typename T, int N), T, N),

#define ANY_COMPONENT_TYPE(Name, Tags, ComponentCount)      ANY_COMPONENT_SIG(Name, Tags) (double, ComponentCount), (float, ComponentCount), (int, ComponentCount))
#define ANY_COMPONENT_FLOATTYPE(Name, Tags, ComponentCount) ANY_COMPONENT_SIG(Name, Tags) (double, ComponentCount), (float, ComponentCount))
#define ANY_COMPONENT_COUNT(Name, Tags, ComponentType)      ANY_COMPONENT_SIG(Name, Tags) (ComponentType, 2), (ComponentType, 3), (ComponentType, 4))
#define ANY_COMPONENT_COUNT_TYPE(Name, Tags)                ANY_COMPONENT_SIG(Name, Tags) (double, 2), (double, 3), (double, 4), (float, 2), (float, 3), (float, 4), (int, 2), (int, 3), (int, 4))
#define ANY_COMPONENT_COUNT_FLOATTYPE(Name, Tags)           ANY_COMPONENT_SIG(Name, Tags) (double, 2), (double, 3), (double, 4), (float, 2), (float, 3), (float, 4))

namespace Test_Intersection
{
	#include "Test_Intersection_Box.inl"
	#include "Test_Intersection_Capsule.inl"
	#include "Test_Intersection_Cone.inl"
	#include "Test_Intersection_Disc.inl"
	#include "Test_Intersection_Ellipsoid.inl"
	#include "Test_Intersection_Frustrum.inl"
	#include "Test_Intersection_Line.inl"
	#include "Test_Intersection_Plane.inl"
	#include "Test_Intersection_Point.inl"
	#include "Test_Intersection_Ray.inl"
	#include "Test_Intersection_Sphere.inl"
	#include "Test_Intersection_Tetrahedron.inl"
	#include "Test_Intersection_Triangle.inl"
}

#undef ANY_COMPONENT_SIG
#undef ANY_COMPONENT_TYPE
#undef ANY_COMPONENT_FLOATTYPE
#undef ANY_COMPONENT_COUNT
#undef ANY_COMPONEN_COUNT_TYPE
#undef ANY_COMPONEN_COUNT_FLOATTYPE
