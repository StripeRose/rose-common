#pragma once

#include "../RoseCommon_Namespace.hpp"

#include "Common.hpp"
#include "Constants.hpp"

namespace ROSECOMMON_MATH_NAMESPACE
{
	// Functions ported from https://github.com/FNA-XNA/FNA/blob/master/src/MathHelper.cs

	/**
	 * @brief Calculate the Cartesian coordinate for one axis of a point that is defined by a
	 *        given triangle and two normalized barycentric (areal) coordinates.
	 * @tparam T The type of all parameters and the returned value.
	 * @param aValue1 The coordinate on one axis of vertex 1 of the defining triangle.
	 * @param aValue2 The coordinate on the same axis of vertex 2 of the defining triangle.
	 * @param aValue3 The coordinate on the same axis of vertex 3 of the defining triangle.
	 * @param anAmount1 The normalized barycentric (areal) coordinate b2, equal to the weighting factor
	 *                  for vertex 2, the coordinate of which is specified in aValue2.
	 * @param anAmount2 The normalized barycentric (areal) coordinate b3, equal to the weighting factor
	 *                  for vertex 3, the coordinate of which is specified in aValue3.
	 * @return Cartesian coordinate of the specified point with respect to the axis being used.
	 */
	template <typename T>
	constexpr T Barycentric(T aValue1, T aValue2, T aValue3, T anAmount1, T anAmount2);

	/**
	 * @brief Performs a Catmull-Rom interpolation using the specified positions.
	 */
	template <typename T>
	constexpr T CatmullRom(T aValue1, T aValue2, T aValue3, T aValue4, T anAmount);

	/**
	 * @brief Performs a Hermite spline interpolation.
	 */
	template <typename T>
	constexpr T Hermite(T aValue1, T aTangent1, T aValue2, T aTangent2, T anAmount);

	/**
	 * @brief Interpolates between two aValues using a cubic equation.
	 */
	template <typename T>
	constexpr T SmoothStep(T aValue1, T aValue2, T anAmount);
}

namespace ROSECOMMON_MATH_NAMESPACE
{
	template <typename T>
	constexpr T Barycentric(T aValue1, T aValue2, T aValue3, T anAmount1, T anAmount2)
	{
		return aValue1 + (aValue2 - aValue1) * anAmount1 + (aValue3 - aValue1) * anAmount2;
	}

	template <typename T>
	constexpr T CatmullRom(T aValue1, T aValue2, T aValue3, T aValue4, T anAmount)
	{
		/* Using formula from http://www.mvps.org/directx/articles/catmull/
		 * Internally using doubles not to lose precision.
		 */
		const double anAmountSquared = anAmount * anAmount;
		const double anAmountCubed = anAmountSquared * anAmount;
		return static_cast<T>(
			0.5 *
			(
				((2.0 * aValue2 + (aValue3 - aValue1) * anAmount) +
					((2.0 * aValue1 - 5.0 * aValue2 + 4.0 * aValue3 - aValue4) * anAmountSquared) +
					(3.0 * aValue2 - aValue1 - 3.0 * aValue3 + aValue4) * anAmountCubed)
				)
			);
	}

	template <typename T>
	constexpr T Hermite(T aValue1, T aTangent1, T aValue2, T aTangent2, T anAmount)
	{
		/* All transformed to double not to lose precision
		 * Otherwise, for high numbers of param:anAmount the result is NaN instead
		 * of Infinity.
		 */
		const double v1 = aValue1, v2 = aValue2, t1 = aTangent1, t2 = aTangent2, s = anAmount;
		const double sCubed = s * s * s;
		const double sSquared = s * s;

		double result;
		if (ROSECOMMON_MATH_NAMESPACE::IsZero(anAmount))
		{
			result = aValue1;
		}
		else if (ROSECOMMON_MATH_NAMESPACE::Equals(anAmount, T(1)))
		{
			result = aValue2;
		}
		else
		{
			result = (
				((2 * v1 - 2 * v2 + t2 + t1) * sCubed) +
				((3 * v2 - 3 * v1 - 2 * t1 - t2) * sSquared) +
				(t1 * s) +
				v1
				);
		}

		return static_cast<T>(result);
	}

	template <typename T>
	constexpr T SmoothStep(T aValue1, T aValue2, T anAmount)
	{
		/* It is expected that 0 < anAmount < 1.
		 * If anAmount < 0, return aValue1.
		 * If anAmount > 1, return aValue2.
		 */
		const T result = ROSECOMMON_MATH_NAMESPACE::Clamp<T>(anAmount, T(0), T(1));
		return Hermite<T>(aValue1, T(0), aValue2, T(0), result);
	}
}
