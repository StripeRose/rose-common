
ANY_COMPONENT_COUNT_TYPE("Point intersection", "[geometry]")
{
	using Vector = ROSECOMMON_MATH_NAMESPACE::VectorNT<N, T>;

	// Point vs Box in Test_Intersection_Box.inl

	// Todo: Move to a proper Vector test suite.
	SECTION("Point vs Point")
	{
		SECTION("Same")
		{
			auto values = GENERATE(
				take(100,
					chunk(2,
						random(T(-1000), T(1000)))));
			const Vector point = (Vector::UnitX() * values[0]) + (Vector::UnitY() * values[1]);
			INFO("Test point: " << point.X << ", " << point.Y);
			CHECK(Intersects<T, N>(point, point));
		}

		SECTION("Separate")
		{
			// Generate a bunch of random points and filter away the ones inside the boundary.
			auto values = GENERATE(
				take(100,
					chunk(4,
						random(T(-1000), T(1000)))));

			if (values[0] != values[2] || values[1] != values[3])
			{
				const Vector pointA = (Vector::UnitX() * values[0]) + (Vector::UnitY() * values[1]);
				const Vector pointB = (Vector::UnitX() * values[2]) + (Vector::UnitY() * values[3]);
				INFO("Test point A: " << pointA.X << ", " << pointA.Y);
				INFO("Test point B: " << pointB.X << ", " << pointB.Y);
				CHECK(!Intersects<T, N>(pointA, pointB));
			}
		}
	}

	// Point vs Radius in Test_Intersection_Box.inl
}