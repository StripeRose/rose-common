#pragma once

#include <exception>
#include <limits>
#include <type_traits>

namespace RoseCommon::Math
{
	// ---------------------------------------
	// * Forward declarations
	// ---------------------------------------
	template <typename T> constexpr T Truncate(T aValue);

	template <typename T>
	constexpr T Abs(T aValue) { return aValue < static_cast<T>(0) ? -aValue : aValue; }

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
			{
				const T truncated = Math::Truncate<T>(aValue);
				return aValue == truncated ? truncated : truncated + static_cast<T>(1);
			}
			else
			{
				return -Math::Truncate<T>(-aValue);
			}
		}
	}

	template <typename R, typename V>
	constexpr R CeilTo(V aValue) { return static_cast<R>(Ceil<V>(aValue)); }

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
		if (aValue > aMax)
			return aMax;
		else if (aValue < aMin)
			return aMin;
		else
			return aValue;
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
	constexpr bool Equals(T aValue1, T aValue2, T aTolerance = std::numeric_limits<T>::epsilon())
	{
		return (aValue1 + aTolerance >= aValue2) && (aValue1 - aTolerance <= aValue2);
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
			if (aValue > static_cast<T>(0))
			{
				return Math::Truncate<T>(aValue);
			}
			else
			{
				const T truncated = -Math::Truncate<T>(-aValue);
				return aValue == truncated ? truncated : truncated - static_cast<T>(1);
			}
		}
	}

	template <typename R, typename V>
	constexpr R FloorTo(V aValue) { return static_cast<R>(Floor<V>(aValue)); }

	template <typename T>
	constexpr bool IsZero(T aValue, T aTolerance = std::numeric_limits<T>::epsilon())
	{
		return Math::Abs<T>(aValue) <= aTolerance;
	}

	/// <summary>
	/// Linearly interpolates between two values.
	/// </summary>
	/// <param name="aValue1">Source value.</param>
	/// <param name="aValue2">Source value.</param>
	/// <param name="anAmount">
	/// Value between 0 and 1 indicating the weight of value2.
	/// </param>
	/// <returns>Interpolated value.</returns>
	/// <remarks>
	/// This method performs the linear interpolation based on the following formula.
	/// <c>value1 + (value2 - value1) * amount</c>
	/// Passing amount a value of 0 will cause value1 to be returned, a value of 1 will
	/// cause value2 to be returned.
	/// </remarks>
	template <typename T, typename S>
	constexpr T Lerp(T aValue1, T aValue2, S anAmount)
	{
		return aValue1 + (aValue2 - aValue1) * anAmount;
	}

	/// <summary>
	/// Returns the greater of two values.
	/// </summary>
	/// <param name="aValue1">Source value.</param>
	/// <param name="aValue2">Source value.</param>
	/// <returns>The greater value.</returns>
	template <typename T>
	constexpr T Max(T aValue1, T aValue2)
	{
		return aValue1 > aValue2 ? aValue1 : aValue2;
	}

	/// <summary>
	/// Returns the greater of three values.
	/// </summary>
	/// <param name="aValue1">Source value.</param>
	/// <param name="aValue2">Source value.</param>
	/// <param name="aValue3">Source value.</param>
	/// <returns>The greater value.</returns>
	template <typename T>
	constexpr T Max(T aValue1, T aValue2, T aValue3)
	{
		return Max(Max(aValue1, aValue2), aValue3);
	}

	/// <summary>
	/// Returns the lesser of two values.
	/// </summary>
	/// <param name="aValue1">Source value.</param>
	/// <param name="aValue2">Source value.</param>
	/// <returns>The lesser value.</returns>
	template <typename T>
	constexpr T Min(T aValue1, T aValue2)
	{
		return aValue1 < aValue2 ? aValue1 : aValue2;
	}

	/// <summary>
	/// Returns the lesser of three values.
	/// </summary>
	/// <param name="aValue1">Source value.</param>
	/// <param name="aValue2">Source value.</param>
	/// <param name="aValue3">Source value.</param>
	/// <returns>The lesser value.</returns>
	template <typename T>
	constexpr T Min(T aValue1, T aValue2, T aValue3)
	{
		return Min<T>(Min<T>(aValue1, aValue2), aValue3);
	}

	template <typename T>
	constexpr T Modulo(T aDividend, T aDivisor)
	{
		if constexpr (std::is_integral_v<T>)
		{
			return (aDividend % aDivisor + aDivisor) % aDivisor;
		}
		else
		{
			const T divisionResult = aDividend / aDivisor;
			return (divisionResult - Math::Floor(divisionResult)) * aDivisor;
		}
	}

	template <typename T>
	constexpr T Round(T aValue)
	{
		// Rounding half up.
		// If other rounding types are useful, each should split into their own function,
		// and Round() should inline-call RoundUpFromHalf().

		if constexpr (!std::is_floating_point_v<T>)
		{
			return aValue;
		}
		else
		{
			return Floor(aValue) + Floor(Modulo<T>(aValue, 1) + T(0.5));
		}
	}

	template <typename R, typename V>
	constexpr R RoundTo(V aValue) { return static_cast<R>(Round<V>(aValue)); }

	namespace _impl
	{
		// Current implementation from https://github.com/bolero-MURAKAMI/Sprout/blob/master/sprout/math/sqrt.hpp
		// Potential todo for the future: Look into how this works to gain a proper understanding of it.

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
		if (aValue != T(0))
			return _impl::sqrt_impl(aValue);
		else
			return T(0);
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

			if (Math::Abs(aValue) >= std::numeric_limits<std::uintmax_t>::max())
				throw std::exception("Value is too large to be truncated with the current implementation.");

			if (aValue > 0)
				return static_cast<T>(static_cast<std::uintmax_t>(aValue));
			else
				return -static_cast<T>(static_cast<std::uintmax_t>(-aValue));
		}
	}

	template <typename R, typename V>
	constexpr R TruncateTo(V aValue) { return static_cast<R>(Truncate<V>(aValue)); }

	template <typename T>
	constexpr T Wrap(T aValue, T aMinimum, T aMaximum)
	{
		return Modulo<T>(aValue - aMinimum, aMaximum - aMinimum) + aMinimum;
	}
}
