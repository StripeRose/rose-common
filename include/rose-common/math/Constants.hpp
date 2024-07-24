#pragma once

namespace RoseCommon::Math
{
	// Templated constant for Pi.
	template <typename T> constexpr T PiT = static_cast<T>(3.1415926535897932384626433832795028841971693993751);

	// Templated constant for half of Pi.
	template <typename T> constexpr T HalfPiT = PiT<T> / static_cast<T>(2);

	// Templated constant for quarter of Pi.
	template <typename T> constexpr T QuarterPiT = PiT<T> / static_cast<T>(4);

	// Templated constant for 2*Pi.
	template <typename T> constexpr T TwoPiT = PiT<T> *static_cast<T>(2);

	// Templated constant for one divided by Pi.
	template <typename T> constexpr T ReciprocalPiT = static_cast<T>(1) / PiT<T>;

	// Templated constant for one divided by 2*Pi.
	template <typename T> constexpr T ReciprocalTwoPiT = static_cast<T>(1) / TwoPiT<T>;

	// Templated constant for Euler's number.
	template <typename T> constexpr T ET = static_cast<T>(2.71828182845904523536028747135266249775724709369995);

	// Templated constant for log base 10 of E.
	template <typename T> constexpr T Log10ET = static_cast<T>(0.43429448190325182);

	// Templated constant for log base 2 of E.
	template <typename T> constexpr T Log2ET = static_cast<T>(1.4426950408889634);

	// Constant for Pi.
	constexpr float Pi = PiT<float>;

	// Constant for half of Pi.
	constexpr float HalfPi = HalfPiT<float>;

	// Constant for quarter of Pi.
	constexpr float QuarterPi = QuarterPiT<float>;

	// Constant for 2*Pi.
	constexpr float TwoPi = TwoPiT<float>;

	// Constant for one divided by Pi.
	constexpr float ReciprocalPi = ReciprocalPiT<float>;

	// Constant for one divided by 2*Pi.
	constexpr float ReciprocalTwoPi = ReciprocalTwoPiT<float>;

	// Constant for Euler's number.
	constexpr float E = ET<float>;

	// Constant for log base 10 of E.
	constexpr float Log10E = Log10ET<float>;

	// Constant for log base 2 of E.
	constexpr float Log2E = Log2ET<float>;

	// 64-bit constant for Pi.
	constexpr double Pi64 = PiT<double>;

	// 64-bit constant for half of Pi.
	constexpr double HalfPi64 = HalfPiT<double>;

	// 64-bit constant for quarter of Pi.
	constexpr double QuarterPi64 = QuarterPiT<double>;

	// 64-bit constant for 2*Pi.
	constexpr double TwoPi64 = TwoPiT<double>;

	// 64-bit constant for one divided by Pi.
	constexpr double ReciprocalPi64 = ReciprocalPiT<double>;

	// 64-bit constant for one divided by 2*Pi.
	constexpr double ReciprocalTwoPi64 = ReciprocalTwoPiT<double>;

	// 64-bit constant for Euler's number.
	constexpr double E64 = ET<double>;

	// 64-bit constant for log base 10 of E.
	constexpr double Log10E64 = Log10ET<double>;

	// 64-bit constant for log base 2 of E.
	constexpr double Log2E64 = Log2ET<double>;
}