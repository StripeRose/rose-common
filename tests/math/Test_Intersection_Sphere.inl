ANY_COMPONENT_COUNT_TYPE("Sphere intersection", "[geometry]")
{
	using Geometry = ROSECOMMON_MATH_NAMESPACE::Radius<N, T>;
	using Vector = ROSECOMMON_MATH_NAMESPACE::VectorN<N, T>;

	static constexpr T Range = std::is_floating_point_v<T> ? 1 : 1000;

	static constexpr Geometry sphere
	{
		.Center = Vector::Zero(),
		.Radius = Range
	};

	CHECK(Intersects(sphere, sphere));

	SECTION("Sphere vs Sphere")
	{
		SECTION("Touching")
		{
			static constexpr Geometry touching
			{
				.Center = Vector::UnitX() * Range * 2,
				.Radius = Range
			};

			CHECK(Intersects(sphere, touching));
			CHECK(Intersects(touching, sphere));
		}

		SECTION("Overlapping")
		{
			static constexpr Geometry overlapping
			{
				.Center = Vector::UnitX() * Range,
				.Radius = Range
			};

			CHECK(Intersects(sphere, overlapping));
			CHECK(Intersects(overlapping, sphere));
		}

		SECTION("Separate")
		{
			static constexpr Geometry separate
			{
				.Center = Vector::UnitX() * Range * 3,
				.Radius = Range
			};

			CHECK(!Intersects(sphere, separate));
			CHECK(!Intersects(separate, sphere));
		}
	}

	SECTION("Sphere vs Point")
	{
		// Todo: Write generator that uniformly generate points in a ring.

		SECTION("On the boundary")
		{
			static constexpr Vector onBoundaryA = Vector::UnitX() * Range;
			INFO("Test point: " << onBoundaryA.X << ", " << onBoundaryA.Y);
			CHECK(Intersects(sphere, onBoundaryA));
			CHECK(Intersects(onBoundaryA, sphere));

			static constexpr Vector onBoundaryB = Vector::UnitY() * Range;
			INFO("Test point: " << onBoundaryB.X << ", " << onBoundaryB.Y);
			CHECK(Intersects(sphere, onBoundaryB));
			CHECK(Intersects(onBoundaryB, sphere));
		}

		SECTION("Inside")
		{
			static constexpr Vector insideA = Vector::UnitX() * -(Range / 2);
			INFO("Test point: " << insideA.X << ", " << insideA.Y);
			CHECK(Intersects(sphere, insideA));
			CHECK(Intersects(insideA, sphere));

			static constexpr Vector insideB = (Vector::UnitX() * -(Range / 2)) + (Vector::UnitY() * -(Range / 4));
			INFO("Test point: " << insideB.X << ", " << insideB.Y);
			CHECK(Intersects(sphere, insideB));
			CHECK(Intersects(insideB, sphere));
		}

		SECTION("Outside")
		{
			static constexpr Vector outsideA = Vector::UnitX() * (Range + (Range / 2));
			INFO("Test point: " << outsideA.X << ", " << outsideA.Y);
			CHECK(!Intersects(sphere, outsideA));
			CHECK(!Intersects(outsideA, sphere));

			static constexpr Vector outsideB = Vector::UnitY() * -(Range + (Range / 2));
			INFO("Test point: " << outsideB.X << ", " << outsideB.Y);
			CHECK(!Intersects(sphere, outsideB));
			CHECK(!Intersects(outsideB, sphere));
		}
	}
}