
ANY_COMPONENT_COUNT_TYPE("Box intersection", "[geometry]")
{
	using Geometry = ROSECOMMON_MATH_NAMESPACE::BoxNT<N, T>;
	using Vector = ROSECOMMON_MATH_NAMESPACE::VectorNT<N, T>;

	static constexpr T Range = std::is_floating_point_v<T> ? 1 : 1000;

	static constexpr Geometry box
	{
		.Min = Vector::One() * -Range,
		.Max = Vector::One() * Range
	};

	CHECK(box.Min.X < box.Max.X);
	CHECK(box.Min.Y < box.Max.Y);
	if constexpr (N >= 3)
		CHECK(box.Min.Z < box.Max.Z);
	if constexpr (N >= 4)
		CHECK(box.Min.W < box.Max.W);

	CHECK(Intersects(box, box));

	SECTION("Box vs Box")
	{
		SECTION("Touching")
		{
			static constexpr Geometry touching
			{
				.Min = (Vector::One() * -Range) + (Vector::UnitX() * Range),
				.Max = (Vector::One() * Range) + (Vector::UnitX() * Range)
			};

			CHECK(touching.Min.X < touching.Max.X);
			CHECK(touching.Min.Y < touching.Max.Y);
			if constexpr (N >= 3)
				CHECK(touching.Min.Z < touching.Max.Z);
			if constexpr (N >= 4)
				CHECK(touching.Min.W < touching.Max.W);

			CHECK(Intersects(box, touching));
			CHECK(Intersects(touching, box));
		}

		SECTION("Overlapping")
		{
			static constexpr Geometry overlapping
			{
				.Min = Vector::Zero(),
				.Max = Vector::One() * Range * 2
			};

			CHECK(overlapping.Min.X < overlapping.Max.X);
			CHECK(overlapping.Min.Y < overlapping.Max.Y);
			if constexpr (N >= 3)
				CHECK(overlapping.Min.Z < overlapping.Max.Z);
			if constexpr (N >= 4)
				CHECK(overlapping.Min.W < overlapping.Max.W);
			CHECK(Intersects(box, overlapping));
			CHECK(Intersects(overlapping, box));
		}

		SECTION("Separate")
		{
			static constexpr Geometry separate
			{
				.Min = Vector::One() * Range * 2,
				.Max = Vector::One() * Range * 3
			};

			CHECK(separate.Min.X < separate.Max.X);
			CHECK(separate.Min.Y < separate.Max.Y);
			if constexpr (N >= 3)
				CHECK(separate.Min.Z < separate.Max.Z);
			if constexpr (N >= 4)
				CHECK(separate.Min.W < separate.Max.W);
			CHECK(!Intersects(box, separate));
			CHECK(!Intersects(separate, box));
		}
	}

	SECTION("Box vs Sphere")
	{
		using OtherGeometry = ROSECOMMON_MATH_NAMESPACE::RadiusNT<N, T>;

		SECTION("Touching")
		{
			static constexpr OtherGeometry touching
			{
				.Center = (Vector::UnitX() * Range * 2),
				.Radius = Range
			};

			CHECK(Intersects(box, touching));
			CHECK(Intersects(touching, box));
		}

		SECTION("Overlapping")
		{
			static constexpr OtherGeometry overlapping
			{
				.Center = (Vector::UnitX() * Range * 2),
				.Radius = Range * 2
			};

			CHECK(Intersects(box, overlapping));
			CHECK(Intersects(overlapping, box));
		}

		SECTION("Separate")
		{
			static constexpr OtherGeometry separate
			{
				.Center = (Vector::UnitX() * Range * 3),
				.Radius = Range
			};

			CHECK(!Intersects(box, separate));
			CHECK(!Intersects(separate, box));
		}
	}

	SECTION("Box vs Point")
	{
		SECTION("On the boundary")
		{
			// Generate a few random points on the box boundary.
			auto side = GENERATE(0, 1, 2, 3);
			auto value = GENERATE(
				take(100,
					random(-Range, Range)));

			Vector onBoundary;

			switch (side)
			{
				case 0:
					onBoundary = (-Vector::UnitX()) + (Vector::UnitY() * value);
					break;
				case 1:
					onBoundary = (Vector::UnitX()) + (Vector::UnitY() * value);
					break;
				case 2:
					onBoundary = (Vector::UnitX() * value) + (-Vector::UnitY());
					break;
				case 3:
					onBoundary = (Vector::UnitX() * value) + (Vector::UnitY());
					break;
			}

			INFO("Test point: " << onBoundary.X << ", " << onBoundary.Y);
			
			CHECK(Intersects(box, onBoundary));
			CHECK(Intersects(onBoundary, box));
		}

		SECTION("Inside")
		{
			// Generate a few random points within the box boundary.
			auto values = GENERATE(
				take(100,
					chunk(2,
						random(-Range, Range))));
			const Vector insideBoundary = (Vector::UnitX() * values[0]) + (Vector::UnitY() * values[1]);
			INFO("Test point: " << insideBoundary.X << ", " << insideBoundary.Y);
			CHECK(Intersects(box, insideBoundary));
			CHECK(Intersects(insideBoundary, box));
		}

		SECTION("Outside")
		{
			// Generate a bunch of random points and filter away the ones inside the boundary.
			auto values = GENERATE(
				take(100,
					chunk(2,
						filter([](auto i) { return i < -Range || i > Range; },
							random(-Range * 100, Range * 100)))));
			const Vector outsideBoundary = (Vector::UnitX() * values[0]) + (Vector::UnitY() * values[1]);
			INFO("Test point: " << outsideBoundary.X << ", " << outsideBoundary.Y);
			CHECK(!Intersects(box, outsideBoundary));
			CHECK(!Intersects(outsideBoundary, box));
		}
	}
}
