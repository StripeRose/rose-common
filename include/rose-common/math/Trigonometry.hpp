#pragma once

#include "Constants.hpp"
#include "Common.hpp"

namespace RoseCommon::Math
{
	/*inline float ArcSine(float aValue) { return static_cast<float>(std::asinf(aValue)); }
	inline double ArcSine(double aValue) { return static_cast<double>(std::asin(aValue)); }*/

	/*template <typename T>
	constexpr T ArcCosine(T aValue)
	{
		return static_cast<T>((-0.69813170079773212 * aValue * aValue - 0.87266462599716477) * aValue + 1.5707963267948966);
	}*/

	// ArcTangent()

	/*inline float ArcTangent2(float aY, float anX)
	{
		return static_cast<float>(std::atan2f(aY, anX));
	}

	inline double ArcTangent2(double aY, double anX)
	{
		return static_cast<double>(std::atan2(aY, anX));
	}*/

	template <typename T>
	constexpr T Hill(T aValue)
	{
		const T a0 = static_cast<T>(1.0f);
		const T a2 = (static_cast<T>(2.0f) / Math::Pi<T>) - (static_cast<T>(12.0f) / (Math::Pi<T> * Math::Pi<T>));
		const T a3 = (static_cast<T>(16.0f) / (Math::Pi<T> * Math::Pi<T> * Math::Pi<T>))
			- (static_cast<T>(4.0f) / (Math::Pi<T> * Math::Pi<T>));
		const T xx = aValue * aValue;
		const T xxx = xx * aValue;

		return a0 + (a2 * xx) + (a3 * xxx);
	}

	template <typename T>
	constexpr T Sine(T aValue)
	{
		const T a = aValue * Math::ReciprocalTwoPi<T>;
		aValue -= static_cast<int>(a) * Math::TwoPi<T>;
		if (aValue < static_cast<T>(0))
		{
			aValue += Math::TwoPi<T>;
		}

		if (aValue < Math::HalfPi<T>)
		{
			return Hill(Math::HalfPi<T> - aValue);
		}
		else if (aValue < Math::Pi<T>)
		{
			return Hill(aValue - Math::HalfPi<T>);
		}
		else if (aValue < static_cast<T>(3) * Math::HalfPi<T>)
		{
			return -Hill((static_cast<T>(3) * Math::HalfPi<T>) - aValue);
		}
		else
		{
			return -Hill(aValue - (static_cast<T>(3) * Math::HalfPi<T>));
		}
	}

	template <typename T>
	constexpr T Cosine(T x) { return Sine(x + Math::HalfPi<T>); }

	// Todo: Tangent

	/// <summary>
	/// Converts radians to degrees.
	/// </summary>
	/// <param name="anAngleInRadians">The angle in radians.</param>
	/// <returns>The angle in degrees.</returns>
	template <typename T>
	constexpr T ToDegrees(T anAngleInRadians) { return (static_cast<T>(180) / Math::Pi<T>) * anAngleInRadians; }

	/// <summary>
	/// Converts degrees to radians.
	/// </summary>
	/// <param name="anAngleInDegrees">The angle in degrees.</param>
	/// <returns>The angle in radians.</returns>
	template <typename T>
	constexpr T ToRadians(T anAngleInDegrees) { return (Math::Pi<T> / static_cast<T>(180)) * anAngleInDegrees; }

	/// <summary>
	/// Reduces a given angle to a value between pi and -pi.
	/// </summary>
	/// <param name="anAngleInRadians">The angle to reduce, in radians.</param>
	/// <returns>The new angle, in radians.</returns>
	template <typename T>
	constexpr T WrapRadians(T anAngleInRadians)
	{
		if ((anAngleInRadians > -Math::Pi<T>) && (anAngleInRadians <= Math::Pi<T>))
			return anAngleInRadians;

		T wrappedAngle = Math::Modulo<T>(anAngleInRadians, Math::TwoPi<T>);
		if (wrappedAngle <= -Math::Pi<T>)
			return wrappedAngle + Math::TwoPi<T>;
		if (wrappedAngle > Math::Pi<T>)
			return wrappedAngle - Math::TwoPi<T>;
		return wrappedAngle;
	}

	/// <summary>
	/// Reduces a given angle to a value between 0 and -360.
	/// </summary>
	/// <param name="anAngleInDegrees">The angle to reduce, in degrees.</param>
	/// <returns>The new angle, in degrees.</returns>
	template <typename T>
	constexpr T WrapDegrees(const T& anAngleInDegrees)
	{
		return Math::Modulo<T>(anAngleInDegrees, T(360));
	}
}