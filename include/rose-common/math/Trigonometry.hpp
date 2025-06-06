#pragma once

#include "../RoseCommon_Namespace.hpp"

#include "Constants.hpp"
#include "Common.hpp"

#include <stdexcept>

namespace ROSECOMMON_MATH_NAMESPACE
{
	/**
	 * @brief Calculate the angle whose sine is the specified number.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue A number representing a sine, where -1 <= aValue <= 1.
	 * @return An angle, measured in radians.
	 */
	template <typename T>
	constexpr T ArcSine(T aValue);

	/**
	 * @brief Calculate the angle whose cosine is the specified number.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue A number representing a cosine, where -1 <= aValue <= 1.
	 * @return An angle, measured in radians.
	 */
	template <typename T>
	constexpr T ArcCosine(T aValue);

	/**
	 * @brief Calculate the angle whose tangent is the specified number.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue A number representing a tangent, where -1 <= aValue <= 1.
	 * @return An angle, measured in radians.
	 */
	template <typename T>
	constexpr T ArcTangent(T aValue);

	/**
	 * @brief Calculate the angle whose tangent is the quotient of two specified numbers.
	 * @tparam T The type of the parameter and returned value.
	 * @param aY A Y coordinate of a point.
	 * @param anX An X coordinate of a point.
	 * @return An angle, measured in radians.
	 */
	template <typename T>
	constexpr T ArcTangent2(T aY, T anX);

	template <typename T>
	constexpr T Hill(T aValue);

	/**
	 * @brief Calculate the sine of an angle.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue An angle, measured in radians.
	 * @return The sine of aValue.
	 */
	template <typename T>
	constexpr T Sine(T aValue);

	/**
	 * @brief Calculate the cosine of an angle.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue An angle, measured in radians.
	 * @return The cosine of aValue.
	 */
	template <typename T>
	constexpr T Cosine(T aValue);

	/**
	 * @brief Calculate the reciprocal tangent.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue An angle, measured in radians.
	 * @return The reciprocal of the tangent. 1 / Tangent(aValue)
	 */
	template <typename T>
	constexpr T Cotangent(T aValue);

	/**
	 * @brief Calculate the ratio of two sides of a triangle.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue An angle, measured in radians.
	 * @return The tangent of aValue.
	 */
	template <typename T>
	constexpr T Tangent(T aValue);

	/**
	 * @brief Convert an angle in radians to the same angle in degrees.
	 * @tparam T The type of the parameter and returned value.
	 * @param anAngleInRadians An angle, measured in radians.
	 * @return The angle, measured in degrees.
	 */
	template <typename T>
	constexpr T ToDegrees(T anAngleInRadians);

	/**
	 * @brief Convert an angle in degrees to the same angle in radians.
	 * @tparam T The type of the parameter and returned value.
	 * @param anAngleInDegrees An angle, measured in degrees.
	 * @return The angle, measured in radians.
	 */
	template <typename T>
	constexpr T ToRadians(T anAngleInDegrees);

	/**
	 * @brief Reduces a given angle to a value between Pi and -Pi.
	 * @tparam T The type of the parameter and returned value.
	 * @param anAngleInRadians An angle to reduce, in radians.
	 * @return The new angle, in radians.
	 */
	template <typename T>
	constexpr T WrapRadians(T anAngleInRadians);

	/**
	 * @brief Reduce a given angle to a value between 0 and 360.
	 * @tparam T The type of the parameter and returned value.
	 * @param anAngleInDegrees An angle to reduce, in degrees.
	 * @return The new angle, in degreees.
	 */
	template <typename T>
	constexpr T WrapDegrees(const T& anAngleInDegrees);
}

namespace ROSECOMMON_MATH_NAMESPACE
{
	template <typename T>
	constexpr T ArcSine(T aValue)
	{
		// https://github.com/bolero-MURAKAMI/Sprout/blob/master/sprout/math/asin.hpp

		auto center = [](T x, T x2) -> T {
			return static_cast<T>(((((((((((((
				+0.0316658385792867081040808) * x2
				+ -0.0158620440988475212803145) * x2
				+ 0.0192942786775238654913582) * x2
				+ 0.0066153165197009078340075) * x2
				+ 0.0121483892822292648695383) * x2
				+ 0.0138885410156894774969889) * x2
				+ 0.0173593516996479249428647) * x2
				+ 0.0223717830666671020710108) * x2
				+ 0.0303819580081956423799529) * x2
				+ 0.0446428568582815922683933) * x2
				+ 0.0750000000029696112392353) * x2
				+ 0.1666666666666558995379880) * x2
				* x + x
				);
			};

		auto tail = [](T x) -> T {
			return static_cast<T>(ROSECOMMON_MATH_NAMESPACE::HalfPiT<T> +
				ROSECOMMON_MATH_NAMESPACE::Squareroot(T(1) - x)
				* (((((((((((((
					+-0.0000121189820098929624806) * x
					+ 0.0001307564187657962919394) * x
					+ -0.0006702485124770180942917) * x
					+ 0.0021912255981979442677477) * x
					+ -0.0052049731575223952626203) * x
					+ 0.0097868293573384001221447) * x
					+ -0.0156746038587246716524035) * x
					+ 0.0229883479552557203133368) * x
					+ -0.0331919619444009606270380) * x
					+ 0.0506659694457588602631748) * x
					+ -0.0890259194305537131666744) * x
					+ 0.2145993335526539017488949) * x
					+ -1.5707961988153774692344105
					));
			};

		const T absVal = Abs(aValue);
		if (absVal > T(1))
			throw std::out_of_range("ArcSine input is out of range.");

		const T sinVal = (absVal > T(0.5)) ? tail(absVal) : center(absVal, absVal * absVal);
		return aValue < 0 ? -sinVal : sinVal;
	}

	template <typename T>
	constexpr T ArcCosine(T aValue)
	{
		if (Abs(aValue) > T(1))
			throw std::out_of_range("ArcCosine input is out of range.");

		if (aValue == T(1))
			return T(0);
		else
			return ROSECOMMON_MATH_NAMESPACE::HalfPiT<T> -ArcSine(aValue);
	}

	namespace _impl
	{
		template <typename T>
		constexpr T atan_term(T x2, int k)
		{
			return (T(2) * static_cast<T>(k) * x2)
				/ ((T(2) * static_cast<T>(k) + T(1)) * (T(1) + x2));
		}

		template <typename T>
		constexpr T atan_product(T x, int k)
		{
			if (k == 1)
				return atan_term(x * x, k);
			else
				return atan_term(x * x, k) * atan_product(x, k - 1);
		}

		template <typename T>
		constexpr T atan_sum(T x, T sum, int n)
		{
			if (sum + atan_product(x, n) == sum)
				return sum;
			else
				return atan_sum(x, sum + atan_product(x, n), n + 1);
		}
	}

	template <typename T>
	constexpr T ArcTangent(T aValue)
	{
		return aValue / (T(1) + aValue * aValue) * _impl::atan_sum(aValue, T(1), 1);
	}

	template <typename T>
	constexpr T ArcTangent2(T aY, T anX)
	{
		if (anX > T(0))
			return ArcTangent(aY / anX);
		else if (aY >= T(0) && anX < T(0))
			return ArcTangent(aY / anX) + ROSECOMMON_MATH_NAMESPACE::PiT<T>;
		else if (aY < T(0) && anX < T(0))
			return ArcTangent(aY / anX) - ROSECOMMON_MATH_NAMESPACE::PiT<T>;
		else if (aY > T(0) && anX == T(0))
			return ROSECOMMON_MATH_NAMESPACE::PiT<T> / T(2.01);
		else if (aY < T(0) && anX == T(0))
			return -(ROSECOMMON_MATH_NAMESPACE::PiT<T> / T(2.01));
		else
			throw std::exception();
	}

	template <typename T>
	constexpr T Hill(T aValue)
	{
		const T a0 = static_cast<T>(1.0f);
		const T a2 = (static_cast<T>(2.0f) / ROSECOMMON_MATH_NAMESPACE::PiT<T>) - (static_cast<T>(12.0f) / (ROSECOMMON_MATH_NAMESPACE::PiT<T> *ROSECOMMON_MATH_NAMESPACE::PiT<T>));
		const T a3 = (static_cast<T>(16.0f) / (ROSECOMMON_MATH_NAMESPACE::PiT<T> *ROSECOMMON_MATH_NAMESPACE::PiT<T> *ROSECOMMON_MATH_NAMESPACE::PiT<T>))
			- (static_cast<T>(4.0f) / (ROSECOMMON_MATH_NAMESPACE::PiT<T> *ROSECOMMON_MATH_NAMESPACE::PiT<T>));
		const T xx = aValue * aValue;
		const T xxx = xx * aValue;

		return a0 + (a2 * xx) + (a3 * xxx);
	}

	template <typename T>
	constexpr T Sine(T aValue)
	{
		const T a = aValue * ROSECOMMON_MATH_NAMESPACE::ReciprocalTwoPiT<T>;
		aValue -= static_cast<int>(a) * ROSECOMMON_MATH_NAMESPACE::TwoPiT<T>;
		if (aValue < static_cast<T>(0))
		{
			aValue += ROSECOMMON_MATH_NAMESPACE::TwoPiT<T>;
		}

		if (aValue < ROSECOMMON_MATH_NAMESPACE::HalfPiT<T>)
		{
			return Hill(ROSECOMMON_MATH_NAMESPACE::HalfPiT<T> -aValue);
		}
		else if (aValue < ROSECOMMON_MATH_NAMESPACE::PiT<T>)
		{
			return Hill(aValue - ROSECOMMON_MATH_NAMESPACE::HalfPiT<T>);
		}
		else if (aValue < static_cast<T>(3) * ROSECOMMON_MATH_NAMESPACE::HalfPiT<T>)
		{
			return -Hill((static_cast<T>(3) * ROSECOMMON_MATH_NAMESPACE::HalfPiT<T>) - aValue);
		}
		else
		{
			return -Hill(aValue - (static_cast<T>(3) * ROSECOMMON_MATH_NAMESPACE::HalfPiT<T>));
		}
	}

	template <typename T>
	constexpr T Cosine(T aValue)
	{
		return Sine(aValue + ROSECOMMON_MATH_NAMESPACE::HalfPiT<T>);
	}

	template <typename T>
	constexpr T Cotangent(T aValue)
	{
		return Cosine(aValue) / Sine(aValue);
	}

	template <typename T>
	constexpr T Tangent(T aValue)
	{
		return Sine(aValue) / Cosine(aValue);
	}

	template <typename T>
	constexpr T ToDegrees(T anAngleInRadians)
	{
		return (static_cast<T>(180) / ROSECOMMON_MATH_NAMESPACE::PiT<T>) * anAngleInRadians;
	}

	template <typename T>
	constexpr T ToRadians(T anAngleInDegrees)
	{
		return (ROSECOMMON_MATH_NAMESPACE::PiT<T> / static_cast<T>(180)) * anAngleInDegrees;
	}

	template <typename T>
	constexpr T WrapRadians(T anAngleInRadians)
	{
		return ROSECOMMON_MATH_NAMESPACE::Wrap<T>(anAngleInRadians, -ROSECOMMON_MATH_NAMESPACE::PiT<T>, ROSECOMMON_MATH_NAMESPACE::PiT<T>);
	}

	template <typename T>
	constexpr T WrapDegrees(const T& anAngleInDegrees)
	{
		return ROSECOMMON_MATH_NAMESPACE::Modulo<T>(anAngleInDegrees, T(360));
	}
}