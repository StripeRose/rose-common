#pragma once

#include <exception>
#include <limits>
#include <type_traits>

namespace RoseCommon::Math
{
	/**
	 * @brief Get the absolute value of a specified value.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue Any numerical value.
	 * @return The input with a positive sign.
	 */
	template <typename T>
	constexpr T Abs(T aValue);

	/**
	 * @brief Calculate the smallest integral value greater than or equal to the specified value.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue A numerical value.
	 * @return The smallest integral value greater than or equal to the input.
	 */
	template <typename T>
	constexpr T Ceiling(T aValue);

	/**
	 * @brief Calculate the smallest integral value greater than or equal to the specified value, and converts it to a given type.
	 * @tparam R The type of the returned value.
	 * @tparam V The type of the parameter value.
	 * @param aValue A decimal or integer number. No operation is done for an integer number.
	 * @return The smallest integral value greater than or equal to the input.
	 */
	template <typename R, typename V>
	constexpr R CeilingTo(V aValue);

	/**
	 * @brief Restrict a value to be within a specified range.
	 * @tparam T The type of all parameters and the returned value.
	 * @param aValue The value to clamp.
	 * @param aMin The minimum value. If @a aValue is less than @a aMin, @a aMin will be returned.
	 * @param aMax The maximum value. If @a aValue is greater than @a aMax, @a aMax will be returned.
	 * @return The clamped value.
	 */
	template <typename T>
	constexpr T Clamp(const T& aValue, const T& aMin, const T& aMax);
	
	/**
	 * @brief Calculate the distance between two values.
	 *        Requires the type to implement the less-than comparison, uniary and binary subtraction operators.
	 * @tparam T The type of the parameters and the returned value.
	 * @param aFrom The point to calculate the distance from.
	 * @param aTo The point to calculate the distance to.
	 * @return The distance between the two values.
	 */
	template <typename T>
	constexpr T Distance(const T& aFrom, const T& aTo);

	/**
	 * @brief Check if a value equal another, within a known tolerance from each other.
	 * @tparam T The type of the parameters.
	 * @param aValue1 A value to check equality.
	 * @param aValue2 A value to check equality.
	 * @param aTolerance A tolerance to allow, and still be considered equal.
	 * @return Whether the values equal, within the specified tolerance.
	 */
	template <typename T>
	constexpr bool Equals(T aValue1, T aValue2, T aTolerance = std::numeric_limits<T>::epsilon());

	 /**
	  * @brief Calculate the largest integral value less than or equal to the specified value.
	  * @tparam T The type of the parameter and returned value.
	  * @param aValue A numerical value.
	  * @return The largest integral value less than or equal to @a aValue.
	  */
	template <typename T>
	constexpr T Floor(T aValue);

	/**
	  * @brief Calculate the largest integral value less than or equal to the specified value, and converts it to a given type.
	  * @tparam R The type of the returned value.
	  * @tparam V The type of the parameter value.
	  * @param aValue A numerical value.
	  * @return The largest integral value less than or equal to @a aValue.
	  */
	template <typename R, typename V>
	constexpr R FloorTo(V aValue);

	/**
	 * @brief Check if a value equal zero, within a known tolerance from each other.
	 * @tparam T The type of the parameters.
	 * @param aValue The value to check against zero.
	 * @param aTolerance The tolerance to use.
	 * @return Whether the value equal zero.
	 */
	template <typename T>
	constexpr bool IsZero(T aValue, T aTolerance = std::numeric_limits<T>::epsilon());
	
	/**
	 * @brief Linearly interpolate between two values, based on a specified weight.
	 *        Passing amount a value of 0 will cause @a aValue1 to be returned, a value of 1 will
	 *        cause @a aValue2 to be returned.
	 * @tparam T The type of the bound and returned value.
	 * @tparam S Scalar weight value type.
	 * @param aValue1 A value intended to be the lower bound.
	 * @param aValue2 A value intended to be the upper bound.
	 * @param anAmount Value between 0 and 1 indicating the weight of value2.
	 * @return The interpolated value.
	 */
	template <typename T, typename S>
	constexpr T Lerp(T aValue1, T aValue2, S anAmount);

	/**
	 * @brief Get the greater of two values.
	 * @tparam T The type of both parameters and the returned value.
	 * @param aValue1 A first value to compare with.
	 * @param aValue2 A second value to compare with.
	 * @return The largest value of the two inputs.
	 */
	template <typename T>
	constexpr T Max(T aValue1, T aValue2);

	/**
	 * @brief Get the greater of three values.
	 * @tparam T The type of all parameters and the returned value.
	 * @param aValue1 A first value to compare with.
	 * @param aValue2 A second value to compare with.
	 * @param aValue3 A third value to compare with.
	 * @return The largest value of the three inputs.
	 */
	template <typename T>
	constexpr T Max(T aValue1, T aValue2, T aValue3);

	/**
	 * @brief Get the lesser of two values.
	 * @tparam T The type of both parameters and the returned value.
	 * @param aValue1 A first value to compare with.
	 * @param aValue2 A second value to compare with.
	 * @return The smallest value of the two inputs.
	 */
	template <typename T>
	constexpr T Min(T aValue1, T aValue2);

	/**
	 * @brief Get the lesser of three values.
	 * @tparam T The type of both parameters and the returned value.
	 * @param aValue1 A first value to compare with.
	 * @param aValue2 A second value to compare with.
	 * @param aValue3 A third value to compare with.
	 * @return The smallest value of the three inputs.
	 */
	template <typename T>
	constexpr T Min(T aValue1, T aValue2, T aValue3);

	/**
	 * @brief Calculate a division remainder.
	 * @tparam T The type of both parameters and the returned value.
	 * @param aDividend A number to divide up.
	 * @param aDivisor A number to divide by.
	 * @return The remainder value.
	 */
	template <typename T>
	constexpr T Modulo(T aDividend, T aDivisor);

	/**
	 * @brief Round a value to the closest integer value. Half-way values are rounded up.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue The number to round.
	 * @return The rounded value.
	 */
	template <typename T>
	constexpr T Round(T aValue);

	/**
	 * @brief Round a value to the closest integer value, and converts it to a given type. Half-way values are rounded up.
	 * @tparam R The type of the returned value.
	 * @tparam V The type of the parameter value.
	 * @param aValue The number to round.
	 * @return The rounded value.
	 */
	template <typename R, typename V>
	constexpr R RoundTo(V aValue);

	/**
	 * @brief Calculate the square root of a specified value.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue The number whose square root is to be found.
	 * @return The square root of the input value.
	 */
	template <typename T>
	constexpr T Squareroot(T aValue);

	/**
	 * @brief Calculate the reciprocal square root of a specified value.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue The number whose reciprocal square root is to be found.
	 * @return The reciprocal square root of the input value.
	 */
	template <typename T>
	constexpr T ReciprocalSquareroot(T aValue);

	/**
	 * @brief Calculate the multiplicative inverse of a value.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue A number to calculate the reciprocal of.
	 * @return The reciprocal of the input value.
	 */
	template <typename T>
	constexpr T Reciprocal(T aValue);

	/**
	 * @brief Round towards zero by truncating away the decimals of a value.
	 * @tparam T The type of the parameter and returned value.
	 * @param aValue A number to truncate.
	 * @return The truncated value.
	 */
	template <typename T>
	constexpr T Truncate(T aValue);

	/**
	 * @brief Round towards zero by truncating away the decimals of a value.
	 * @tparam R The type of the returned value.
	 * @tparam V The type of the parameter value.
	 * @param aValue A number to truncate.
	 * @return The truncated value.
	 */
	template <typename R, typename V>
	constexpr R TruncateTo(V aValue);

	/**
	 * @brief Wrap a specified value around to make it always be within the specified range.
	 * @tparam T The type of the parameters and returned value.
	 * @param aValue A value to wrap.
	 * @param aMinimum The lower bound of the wrapping range.
	 * @param aMaximum The upper bound of the wrapping range.
	 * @return The wrapped value.
	 */
	template <typename T>
	constexpr T Wrap(T aValue, T aMinimum, T aMaximum);
}

namespace RoseCommon::Math
{
	template <typename T>
	constexpr T Abs(T aValue) { return aValue < static_cast<T>(0) ? -aValue : aValue; }

	template <typename T>
	constexpr T Ceiling(T aValue)
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
	constexpr R CeilingTo(V aValue) { return static_cast<R>(Ceiling<V>(aValue)); }

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

	template <typename T>
	constexpr T Distance(const T& aFrom, const T& aTo)
	{
		return Abs<T>(aFrom - aTo);
	}

	template <typename T>
	constexpr bool Equals(T aValue1, T aValue2, T aTolerance)
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
	constexpr bool IsZero(T aValue, T aTolerance)
	{
		return Math::Abs<T>(aValue) <= aTolerance;
	}

	template <typename T, typename S>
	constexpr T Lerp(T aValue1, T aValue2, S anAmount)
	{
		return aValue1 + (aValue2 - aValue1) * anAmount;
	}

	template <typename T>
	constexpr T Max(T aValue1, T aValue2)
	{
		return aValue1 > aValue2 ? aValue1 : aValue2;
	}

	template <typename T>
	constexpr T Max(T aValue1, T aValue2, T aValue3)
	{
		return Max(Max(aValue1, aValue2), aValue3);
	}

	template <typename T>
	constexpr T Min(T aValue1, T aValue2)
	{
		return aValue1 < aValue2 ? aValue1 : aValue2;
	}

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
