#pragma once

namespace RoseCommon::Math
{
	// ---------------------------------------
	// * Forward declarations
	// ---------------------------------------
	template <typename T> constexpr T Truncate(T aValue);

	template <typename T>
	constexpr T Abs(T aValue) { return aValue < 0 ? -aValue : aValue; }

	template <typename T>
	constexpr T Ceil(T aValue)
	{
		if constexpr (!std::is_floating_point_v<T>)
		{
			return aValue;
		}
		else
		{
			if (aValue > static_cast<T>(0))
				return -Math::Truncate<T>(-aValue);
			else
				return Math::Truncate<T>(aValue);
		}
	}

	/// <summary>
	/// Restricts a value to be within a specified range.
	/// </summary>
	/// <param name="aValue">The value to clamp.</param>
	/// <param name="aMin">
	/// The minimum value. If <c>value</c> is less than <c>min</c>, <c>min</c>
	/// will be returned.
	/// </param>
	/// <param name="aMax">
	/// The maximum value. If <c>value</c> is greater than <c>max</c>, <c>max</c>
	/// will be returned.
	/// </param>
	/// <returns>The clamped value.</returns>
	template <typename T>
	constexpr T Clamp(const T& aValue, const T& aMin, const T& aMax)
	{
		return Min<T>(Max<T>(aValue, aMin), aMax);
	}

	/// <summary>
	/// Calculates the absolute value of the difference of two values.
	/// </summary>
	/// <param name="aValue1">Source value.</param>
	/// <param name="aValue2">Source value.</param>
	/// <returns>Distance between the two values.</returns>
	template <typename T>
	constexpr T Distance(const T& aValue1, const T& aValue2)
	{
		return Abs<T>(aValue1 - aValue2);
	}

	template <typename T>
	constexpr bool Equals(T a, T b, T tolerance = std::numeric_limits<T>::epsilon())
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	template <typename T>
	constexpr T Floor(T aValue)
	{
		if constexpr (!std::is_floating_point_v<T>)
		{
			return aValue;
		}
		else
		{
			if (aValue > 0)
				return Math::Truncate<T>(aValue);
			else
				return -Math::Truncate<T>(-aValue);
		}
	}

	template <typename T>
	constexpr bool IsZero(T a, T tolerance = std::numeric_limits<T>::epsilon())
	{
		return Math::Abs<T>(a) <= tolerance;
	}

	/// <summary>
	/// Linearly interpolates between two values.
	/// </summary>
	/// <param name="value1">Source value.</param>
	/// <param name="value2">Source value.</param>
	/// <param name="amount">
	/// Value between 0 and 1 indicating the weight of value2.
	/// </param>
	/// <returns>Interpolated value.</returns>
	/// <remarks>
	/// This method performs the linear interpolation based on the following formula.
	/// <c>value1 + (value2 - value1) * amount</c>
	/// Passing amount a value of 0 will cause value1 to be returned, a value of 1 will
	/// cause value2 to be returned.
	/// </remarks>
	template <typename T>
	constexpr T Lerp(T value1, T value2, T amount)
	{
		return value1 + (value2 - value1) * amount;
	}

	/// <summary>
	/// Returns the greater of two values.
	/// </summary>
	/// <param name="value1">Source value.</param>
	/// <param name="value2">Source value.</param>
	/// <returns>The greater value.</returns>
	template <typename T>
	constexpr T Max(T value1, T value2)
	{
		return value1 > value2 ? value1 : value2;
	}

	/// <summary>
	/// Returns the greater of three values.
	/// </summary>
	/// <param name="value1">Source value.</param>
	/// <param name="value2">Source value.</param>
	/// <param name="value3">Source value.</param>
	/// <returns>The greater value.</returns>
	template <typename T>
	constexpr T Max(T value1, T value2, T value3)
	{
		return Max(Max(value1, value2), value3);
	}

	/// <summary>
	/// Returns the lesser of two values.
	/// </summary>
	/// <param name="value1">Source value.</param>
	/// <param name="value2">Source value.</param>
	/// <returns>The lesser value.</returns>
	template <typename T>
	constexpr T Min(T value1, T value2)
	{
		return value1 < value2 ? value1 : value2;
	}

	/// <summary>
	/// Returns the lesser of three values.
	/// </summary>
	/// <param name="value1">Source value.</param>
	/// <param name="value2">Source value.</param>
	/// <param name="value3">Source value.</param>
	/// <returns>The lesser value.</returns>
	template <typename T>
	constexpr T Min(T value1, T value2, T value3)
	{
		return Min<T>(Min<T>(value1, value2), value3);
	}

	template <typename T>
	constexpr T Modulo(T aDividend, T aDivisor)
	{
		if constexpr (std::is_integral_v<T>)
		{
			return aDividend % aDivisor;
		}
		else
		{
			const T divisionResult = aDividend / aDivisor;
			return (divisionResult - Math::Floor(divisionResult)) * aDivisor;
		}
	}

	namespace _impl
	{
		template <typename T>
		constexpr T sqrt_impl2(T x, T s, T s2)
		{
			if (s >= s2)
				return s2;
			else
				return sqrt_impl2(x, (x / s + s) / 2, s);
		}

		template <typename T>
		constexpr T sqrt_impl1(T x, T s)
		{
			return sqrt_impl2(x, (x / s + s) / 2, s);
		}

		template <typename T>
		constexpr T sqrt_impl(T aValue)
		{
			return sqrt_impl1(aValue, aValue > 1 ? aValue : T(1));
		}
	}

	template <typename T>
	constexpr T Squareroot(T aValue)
	{
		return _impl::sqrt_impl(aValue);
	}

	template <typename T>
	constexpr T ReciprocalSquareroot(T aValue)
	{
		return static_cast<T>(1) / Squareroot<T>(aValue);
	}

	template <typename T>
	constexpr T Reciprocal(T aValue)
	{
		return static_cast<T>(1) / aValue;
	}

	template <typename T>
	constexpr T Truncate(T aValue)
	{
		if constexpr (!std::is_floating_point_v<T>)
		{
			return aValue;
		}
		else
		{
			if (aValue == 0)
				return 0;

			// Todo: Figure out how to handle errors in constexpr.
			/*if (Math::Abs(aValue) >= std::numeric_limits<std::uintmax_t>::max())
				return 0;*/

			if (aValue > 0)
				return static_cast<T>(static_cast<std::uintmax_t>(aValue));
			else
				return -static_cast<T>(static_cast<std::uintmax_t>(-aValue));
		}
	}

	template <typename T>
	T Wrap(const T& value, const T& min, const T& max)
	{
		int range = max - min + 1;

		if (value < min)
			value += range * ((min - value) / range + 1);

		return min + (value - min) % range;
	}
}
