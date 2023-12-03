#pragma once

namespace RoseCommon::Math
{
	// Constant for Pi.
	template <typename T> constexpr T Pi				= static_cast<T>(3.1415926535897932384626433832795028841971693993751);

	// Constant for half of Pi.
	template <typename T> constexpr T HalfPi			= Pi<T> / static_cast<T>(2);

	// Constant for quarter of Pi.
	template <typename T> constexpr T QuarterPi			= Pi<T> / static_cast<T>(4);

	// Constant for 2*Pi.
	template <typename T> constexpr T TwoPi				= Pi<T> * static_cast<T>(2);

	// Constant for one divided by Pi.
	template <typename T> constexpr T ReciprocalPi		= static_cast<T>(1) / Pi<T>;

	// Constant for one divided by 2*Pi.
	template <typename T> constexpr T ReciprocalTwoPi	= static_cast<T>(1) / TwoPi<T>;

	// Constant for Euler's number.
	template <typename T> constexpr T E = static_cast<T>(2.71828182845904523536028747135266249775724709369995);

	// Constant for log base 10 of E.
	template <typename T> constexpr T Log10E = static_cast<T>(0.43429448190325182);

	// Constant for log base 2 of E.
	template <typename T> constexpr T Log2E = static_cast<T>(1.4426950408889634);
}