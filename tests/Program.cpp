#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <rose-common/Color.hpp>

using namespace Catch;
using namespace Catch::Matchers;

TEST_CASE("ColorT<>/Constructor/Unpacking")
{
	SECTION("8-bit integer")
	{
		constexpr RoseCommon::ColorT<std::uint8_t> staticColor(0x12345678);
		STATIC_REQUIRE(staticColor.A == 0x12);
		STATIC_REQUIRE(staticColor.R == 0x34);
		STATIC_REQUIRE(staticColor.G == 0x56);
		STATIC_REQUIRE(staticColor.B == 0x78);

		RoseCommon::ColorT<std::uint8_t> color(0x12345678);
		REQUIRE(color.A == 0x12);
		REQUIRE(color.R == 0x34);
		REQUIRE(color.G == 0x56);
		REQUIRE(color.B == 0x78);
	}

	SECTION("32-bit floating point")
	{
		constexpr RoseCommon::ColorT<float> staticColor(0x12345678);
		STATIC_REQUIRE(staticColor.A == static_cast<float>(0x12) / 255.f);
		STATIC_REQUIRE(staticColor.R == static_cast<float>(0x34) / 255.f);
		STATIC_REQUIRE(staticColor.G == static_cast<float>(0x56) / 255.f);
		STATIC_REQUIRE(staticColor.B == static_cast<float>(0x78) / 255.f);

		RoseCommon::ColorT<float> color(0x12345678);
		REQUIRE_THAT(color.A, WithinAbs(static_cast<float>(0x12) / 255.f, 0.001f));
		REQUIRE_THAT(color.R, WithinAbs(static_cast<float>(0x34) / 255.f, 0.001f));
		REQUIRE_THAT(color.G, WithinAbs(static_cast<float>(0x56) / 255.f, 0.001f));
		REQUIRE_THAT(color.B, WithinAbs(static_cast<float>(0x78) / 255.f, 0.001f));
	}
}
