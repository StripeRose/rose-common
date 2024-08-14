#pragma once

namespace RoseCommon::Math
{
	/**
	 * @brief Templated constant for Pi.
	 * @tparam T The type to use for the value.
	 */
	template <typename T> constexpr T PiT = static_cast<T>(3.1415926535897932384626433832795028841971693993751);

	/**
	 * @brief Templated constant for half of Pi.
	 * @tparam T The type to use for the value.
	 */
	template <typename T> constexpr T HalfPiT = PiT<T> / static_cast<T>(2);

	/**
	 * @brief Templated constant for quarter of Pi.
	 * @tparam T The type to use for the value.
	 */
	template <typename T> constexpr T QuarterPiT = PiT<T> / static_cast<T>(4);

	/**
	 * @brief Templated constant for 2*Pi.
	 * @tparam T The type to use for the value.
	 */
	template <typename T> constexpr T TwoPiT = PiT<T> *static_cast<T>(2);

	/**
	 * @brief Templated constant for one divided by Pi.
	 * @tparam T The type to use for the value.
	 */
	template <typename T> constexpr T ReciprocalPiT = static_cast<T>(1) / PiT<T>;

	/**
	 * @brief Templated constant for one divided by 2*Pi.
	 * @tparam T The type to use for the value.
	 */
	template <typename T> constexpr T ReciprocalTwoPiT = static_cast<T>(1) / TwoPiT<T>;

	/**
	 * @brief Templated constant for Euler's number.
	 * @tparam T The type to use for the value.
	 */
	template <typename T> constexpr T ET = static_cast<T>(2.71828182845904523536028747135266249775724709369995);

	/**
	 * @brief Templated constant for log base 10 of E.
	 * @tparam T The type to use for the value.
	 */
	template <typename T> constexpr T Log10ET = static_cast<T>(0.43429448190325182);

	/**
	 * @brief Templated constant for log base 2 of E.
	 * @tparam T The type to use for the value.
	 */
	template <typename T> constexpr T Log2ET = static_cast<T>(1.4426950408889634);

	/**
	 * @brief 32-bit constant for Pi.
	 */
	constexpr float Pi = PiT<float>;

	/**
	 * @brief 32-bit constant for half of Pi.
	 */
	constexpr float HalfPi = HalfPiT<float>;

	/**
	 * @brief 32-bit constant for quarter of Pi.
	 */
	constexpr float QuarterPi = QuarterPiT<float>;

	/**
	 * @brief 32-bit constant for 2 * Pi.
	 */
	constexpr float TwoPi = TwoPiT<float>;

	/**
	 * @brief 32-bit constant for 1 / Pi.
	 */
	constexpr float ReciprocalPi = ReciprocalPiT<float>;

	/**
	 * @brief 32-bit constant for 1 / (2 * Pi).
	 */
	constexpr float ReciprocalTwoPi = ReciprocalTwoPiT<float>;

	/**
	 * @brief 32-bit constant for Euler's number.
	 */
	constexpr float E = ET<float>;

	/**
	 * @brief 32-bit constant for log base 10 of E.
	 */
	constexpr float Log10E = Log10ET<float>;

	/**
	 * @brief 32-bit constant for log base 2 of E.
	 */
	constexpr float Log2E = Log2ET<float>;

	/**
	 * @brief 64-bit constant for Pi.
	 */
	constexpr double Pi64 = PiT<double>;

	/**
	 * @brief 64-bit constant for half of Pi.
	 */
	constexpr double HalfPi64 = HalfPiT<double>;

	/**
	 * @brief 64-bit constant for quarter of Pi.
	 */
	constexpr double QuarterPi64 = QuarterPiT<double>;

	/**
	 * @brief 64-bit constant for 2 * Pi.
	 */
	constexpr double TwoPi64 = TwoPiT<double>;

	/**
	 * @brief 64-bit constant for 1 / Pi.
	 */
	constexpr double ReciprocalPi64 = ReciprocalPiT<double>;

	/**
	 * @brief 64-bit constant for 1 / (2 * Pi).
	 */
	constexpr double ReciprocalTwoPi64 = ReciprocalTwoPiT<double>;

	/**
	 * @brief 64-bit constant for Euler's number.
	 */
	constexpr double E64 = ET<double>;

	/**
	 * @brief 64-bit constant for log base 10 of E.
	 */
	constexpr double Log10E64 = Log10ET<double>;

	/**
	 * @brief 64-bit constant for log base 2 of E.
	 */
	constexpr double Log2E64 = Log2ET<double>;
}