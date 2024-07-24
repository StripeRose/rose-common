#pragma once

#include "Constants.hpp"
#include "Common.hpp"

#include <stdexcept>

namespace RoseCommon::Math
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
			return static_cast<T>(Math::HalfPiT<T> +
				Math::Squareroot(T(1) - x)
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
			return Math::HalfPiT<T> - ArcSine(aValue);
	}

	namespace _impl
	{
		template <typename T>
		constexpr T atan_term(T x2, int k)
		{
			return (T(2) * static_cast<T>(k) * x2)
				/ ((T(2) * static_cast<T>(k) + T(1))* (T(1) + x2));
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
			return ArcTangent(aY / anX) + Math::PiT<T>;
		else if (aY < T(0) && anX < T(0))
			return ArcTangent(aY / anX) - Math::PiT<T>;
		else if (aY > T(0) && anX == T(0))
			return Math::PiT<T> / T(2.01);
		else if (aY < T(0) && anX == T(0))
			return -(Math::PiT<T> / T(2.01));
		else
			throw std::exception();
	}

	template <typename T>
	constexpr T Hill(T aValue)
	{
		const T a0 = static_cast<T>(1.0f);
		const T a2 = (static_cast<T>(2.0f) / Math::PiT<T>) - (static_cast<T>(12.0f) / (Math::PiT<T> * Math::PiT<T>));
		const T a3 = (static_cast<T>(16.0f) / (Math::PiT<T> * Math::PiT<T> * Math::PiT<T>))
			- (static_cast<T>(4.0f) / (Math::PiT<T> * Math::PiT<T>));
		const T xx = aValue * aValue;
		const T xxx = xx * aValue;

		return a0 + (a2 * xx) + (a3 * xxx);
	}

	template <typename T>
	constexpr T Sine(T aValue)
	{
		const T a = aValue * Math::ReciprocalTwoPiT<T>;
		aValue -= static_cast<int>(a) * Math::TwoPiT<T>;
		if (aValue < static_cast<T>(0))
		{
			aValue += Math::TwoPiT<T>;
		}

		if (aValue < Math::HalfPiT<T>)
		{
			return Hill(Math::HalfPiT<T> - aValue);
		}
		else if (aValue < Math::PiT<T>)
		{
			return Hill(aValue - Math::HalfPiT<T>);
		}
		else if (aValue < static_cast<T>(3) * Math::HalfPiT<T>)
		{
			return -Hill((static_cast<T>(3) * Math::HalfPiT<T>) - aValue);
		}
		else
		{
			return -Hill(aValue - (static_cast<T>(3) * Math::HalfPiT<T>));
		}
	}

	template <typename T>
	constexpr T Cosine(T x) { return Sine(x + Math::HalfPiT<T>); }

	/// <summary>
	/// Reciprocal of tangent.
	/// </summary>
	template <typename T>
	constexpr T Cotangent(T x) { return Cosine(x) / Sine(x); }

	template <typename T>
	constexpr T Tangent(T x) { return Sine(x) / Cosine(x); }

	/// <summary>
	/// Converts radians to degrees.
	/// </summary>
	/// <param name="anAngleInRadians">The angle in radians.</param>
	/// <returns>The angle in degrees.</returns>
	template <typename T>
	constexpr T ToDegrees(T anAngleInRadians) { return (static_cast<T>(180) / Math::PiT<T>) * anAngleInRadians; }

	/// <summary>
	/// Converts degrees to radians.
	/// </summary>
	/// <param name="anAngleInDegrees">The angle in degrees.</param>
	/// <returns>The angle in radians.</returns>
	template <typename T>
	constexpr T ToRadians(T anAngleInDegrees) { return (Math::PiT<T> / static_cast<T>(180)) * anAngleInDegrees; }

	/// <summary>
	/// Reduces a given angle to a value between pi and -pi.
	/// </summary>
	/// <param name="anAngleInRadians">The angle to reduce, in radians.</param>
	/// <returns>The new angle, in radians.</returns>
	template <typename T>
	constexpr T WrapRadians(T anAngleInRadians)
	{
		return Math::Wrap<T>(anAngleInRadians, -Math::PiT<T>, Math::PiT<T>);
	}

	/// <summary>
	/// Reduces a given angle to a value between 0 and 360.
	/// </summary>
	/// <param name="anAngleInDegrees">The angle to reduce, in degrees.</param>
	/// <returns>The new angle, in degrees.</returns>
	template <typename T>
	constexpr T WrapDegrees(const T& anAngleInDegrees)
	{
		return Math::Modulo<T>(anAngleInDegrees, T(360));
	}
}