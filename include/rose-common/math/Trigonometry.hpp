#pragma once

#include "Constants.hpp"
#include "Common.hpp"

namespace RoseCommon::Math
{
	/*inline Float32 ArcSine(Float32 x) { return static_cast<Float32>(std::asinf(x)); }
	inline Float64 ArcSine(Float64 x) { return static_cast<Float64>(std::asin(x)); }*/

	/*template <typename T>
	constexpr T ArcCosine(T x)
	{
		return static_cast<T>((-0.69813170079773212 * x * x - 0.87266462599716477) * x + 1.5707963267948966);
	}*/

	// ArcTangent()

	/*inline Float32 ArcTangent2(Float32 y, Float32 x)
	{
		return static_cast<Float32>(std::atan2f(y, x));
	}

	inline Float64 ArcTangent2(Float64 y, Float64 x)
	{
		return static_cast<Float64>(std::atan2(y, x));
	}*/

	template <typename T>
	constexpr T Hill(T x)
	{
		const T a0 = static_cast<T>(1.0f);
		const T a2 = (static_cast<T>(2.0f) / Math::Pi<T>) - (static_cast<T>(12.0f) / (Math::Pi<T> * Math::Pi<T>));
		const T a3 = (static_cast<T>(16.0f) / (Math::Pi<T> * Math::Pi<T> * Math::Pi<T>))
			- (static_cast<T>(4.0f) / (Math::Pi<T> * Math::Pi<T>));
		const T xx = x * x;
		const T xxx = xx * x;

		return a0 + (a2 * xx) + (a3 * xxx);
	}

	template <typename T>
	constexpr T Sine(T x)
	{
		const T a = x * Math::ReciprocalTwoPi<T>;
		x -= static_cast<int>(a) * Math::TwoPi<T>;
		if (x < static_cast<T>(0))
		{
			x += Math::TwoPi<T>;
		}

		if (x < Math::HalfPi<T>)
		{
			return Hill(Math::HalfPi<T> - x);
		}
		else if (x < Math::Pi<T>)
		{
			return Hill(x - Math::HalfPi<T>);
		}
		else if (x < static_cast<T>(3) * Math::HalfPi<T>)
		{
			return -Hill((static_cast<T>(3) * Math::HalfPi<T>) - x);
		}
		else
		{
			return -Hill(x - (static_cast<T>(3) * Math::HalfPi<T>));
		}
	}

	template <typename T>
	constexpr T Cosine(T x) { return Sine(x + Math::HalfPi<T>); }

	// Todo: Tangent

	/// <summary>
	/// Converts radians to degrees.
	/// </summary>
	/// <param name="radians">The angle in radians.</param>
	/// <returns>The angle in degrees.</returns>
	template <typename T>
	constexpr T ToDegrees(T anAngleInRadians) { return (static_cast<T>(180) / Math::Pi<T>) * anAngleInRadians; }

	/// <summary>
	/// Converts degrees to radians.
	/// </summary>
	/// <param name="degrees">The angle in degrees.</param>
	/// <returns>The angle in radians.</returns>
	template <typename T>
	constexpr T ToRadians(T anAngleInDegrees) { return (Math::Pi<T> / static_cast<T>(180)) * anAngleInDegrees; }

	/// <summary>
	/// Reduces a given angle to a value between pi and -pi.
	/// </summary>
	/// <param name="angle">The angle to reduce, in radians.</param>
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
	/// <param name="angle">The angle to reduce, in degrees.</param>
	/// <returns>The new angle, in degrees.</returns>
	template <typename T>
	constexpr T WrapDegrees(const T& anAngleInDegrees)
	{
		return Math::Modulo<T>(anAngleInDegrees, T(360));
	}
}