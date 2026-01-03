#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <rose-common/Color.hpp>

#include <cmath>

namespace
{
	using ColorComponentTypes = std::tuple<std::uint8_t, std::uint16_t, float>;
	static constexpr float MaxFloatError = 0.000001f;
	template <typename T>
	static constexpr T Whitepoint = std::is_floating_point_v<T> ? static_cast<T>(1) : std::numeric_limits<T>::max();
	template <typename T>
	static constexpr T PackedRangeRatio = Whitepoint<T> / 0xFF;
	template <typename T>
	static constexpr T MaxSDRToHDRError = std::is_floating_point_v<T> ? static_cast<T>(1.f / 0xFF) : PackedRangeRatio<T>;

	using namespace Catch;
	using namespace Catch::Matchers;
	using namespace Catch::Generators;

	using namespace RoseCommon;

#pragma region Construction

	TEMPLATE_LIST_SCENARIO("ColorARGB<> is zeroed-out when default-constructed", "[color]", ColorComponentTypes)
	{
		GIVEN("A default-constructed ColorARGB<>")
		{
			static constexpr ColorARGB<TestType> Color;

			THEN("Each color component is zeroed out")
			{
				STATIC_CHECK(Color.A == static_cast<TestType>(0));
				STATIC_CHECK(Color.R == static_cast<TestType>(0));
				STATIC_CHECK(Color.G == static_cast<TestType>(0));
				STATIC_CHECK(Color.B == static_cast<TestType>(0));
			}
		}
	}

	TEMPLATE_LIST_SCENARIO("ColorARGB<> can unpack a UInt32 ARGB color value", "[color]", ColorComponentTypes)
	{
		GIVEN("A color with unique values in each component")
		{
			static constexpr ColorARGB<TestType> Color(0x12345678);

			THEN("Each color component is extracted into the correct variable")
			{
				if constexpr (std::is_floating_point_v<TestType>)
				{
					CHECK_THAT(Color.A, WithinAbs(static_cast<TestType>(0x12) / 255.f, MaxSDRToHDRError<TestType>));
					CHECK_THAT(Color.R, WithinAbs(static_cast<TestType>(0x34) / 255.f, MaxSDRToHDRError<TestType>));
					CHECK_THAT(Color.G, WithinAbs(static_cast<TestType>(0x56) / 255.f, MaxSDRToHDRError<TestType>));
					CHECK_THAT(Color.B, WithinAbs(static_cast<TestType>(0x78) / 255.f, MaxSDRToHDRError<TestType>));
				}
				else
				{
					STATIC_CHECK(Color.A == static_cast<TestType>(0x12) * PackedRangeRatio<TestType>);
					STATIC_CHECK(Color.R == static_cast<TestType>(0x34) * PackedRangeRatio<TestType>);
					STATIC_CHECK(Color.G == static_cast<TestType>(0x56) * PackedRangeRatio<TestType>);
					STATIC_CHECK(Color.B == static_cast<TestType>(0x78) * PackedRangeRatio<TestType>);
				}
			}
		}
	}

	TEMPLATE_LIST_SCENARIO("ColorARGB<> can be initialized as a solid color by defining RGB values", "[color]", ColorComponentTypes)
	{
		GIVEN("A color with unique values in each Red, Green, and Blue components")
		{
			static constexpr ColorARGB<TestType> Color(
				static_cast<TestType>(12),
				static_cast<TestType>(34),
				static_cast<TestType>(56));

			THEN("Each color is correctly assigned")
			{
				CHECK_THAT(Color.A, WithinAbs(Whitepoint<TestType>, MaxFloatError));
				STATIC_CHECK(Color.R == static_cast<TestType>(12));
				STATIC_CHECK(Color.G == static_cast<TestType>(34));
				STATIC_CHECK(Color.B == static_cast<TestType>(56));
			}
		}
	}

	TEMPLATE_LIST_SCENARIO("ColorARGB<> can be initialized by defining ARGB values", "[color]", ColorComponentTypes)
	{
		GIVEN("A color with unique values in each Alpha, Red, Green, and Blue components")
		{
			static constexpr ColorARGB<TestType> Color(
				static_cast<TestType>(12),
				static_cast<TestType>(34),
				static_cast<TestType>(56),
				static_cast<TestType>(78));

			THEN("Each color is correctly assigned")
			{
				STATIC_CHECK(Color.A == static_cast<TestType>(12));
				STATIC_CHECK(Color.R == static_cast<TestType>(34));
				STATIC_CHECK(Color.G == static_cast<TestType>(56));
				STATIC_CHECK(Color.B == static_cast<TestType>(78));
			}
		}
	}
#pragma endregion
}