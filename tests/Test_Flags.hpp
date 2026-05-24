#include <catch2/catch_test_macros.hpp>

#include <rose-common/Flags.hpp>

namespace
{
	using namespace RoseCommon;

	enum class Enumeration { First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth };
	using FlagsType = Flags<Enumeration>;

#pragma region Construction

	TEST_CASE("Flags<> is empty if default-constructed")
	{
		constexpr FlagsType defaultConstructed;
		STATIC_CHECK(defaultConstructed.IsEmpty());
		STATIC_CHECK(!defaultConstructed);
	}

	TEST_CASE("Flags<> has only one bit set if constructed with an enum value")
	{
		constexpr FlagsType flags(Enumeration::Third);

		// Only the specified bit is set.
		STATIC_CHECK(static_cast<int>(flags) == 0b100);

		// The specified flag is set.
		STATIC_CHECK(flags.IsSet(Enumeration::Third));

		// No other flag is set.
		constexpr FlagsType flagsWithoutOriginal(flags & ~FlagsType(Enumeration::Third));
		STATIC_CHECK(flagsWithoutOriginal.IsEmpty());
	}

	TEST_CASE("Flags<> can construct a combination of bits at compile time.")
	{
		constexpr FlagsType flags = FlagsType(Enumeration::First) | Enumeration::Second | Enumeration::Fifth;

		// Only the specified bits are set
		STATIC_CHECK(static_cast<int>(flags) == 0b10011);
	}

#pragma endregion

#pragma region Methods

	TEST_CASE("Flags<> can clear a bit after construction")
	{
		FlagsType flags = FlagsType(Enumeration::First) | Enumeration::Second | Enumeration::Fifth;
		flags.Clear(Enumeration::Second);
		CHECK(flags.IsSet(Enumeration::First));
		CHECK(!flags.IsSet(Enumeration::Second));
		CHECK(flags.IsSet(Enumeration::Fifth));
		CHECK(static_cast<int>(flags) == 0b10001);
	}

	TEST_CASE("Flags<> can set a bit after construction")
	{
		FlagsType flags = FlagsType(Enumeration::First) | Enumeration::Fifth;
		flags.Set(Enumeration::Eighth);
		CHECK(flags.IsSet(Enumeration::First));
		CHECK(flags.IsSet(Enumeration::Fifth));
		CHECK(flags.IsSet(Enumeration::Eighth));
		CHECK(static_cast<int>(flags) == 0b010010001);
	}

#pragma endregion

#pragma region Operators

	

#pragma endregion
}