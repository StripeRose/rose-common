#pragma once

#include "Common.hpp"
#include "Constants.hpp"

namespace RoseCommon::Math
{
	/// <summary>
	/// Returns the Cartesian coordinate for one axis of a point that is defined by a
	/// given triangle and two normalized barycentric (areal) coordinates.
	/// </summary>
	/// <param name="value1">
	/// The coordinate on one axis of vertex 1 of the defining triangle.
	/// </param>
	/// <param name="value2">
	/// The coordinate on the same axis of vertex 2 of the defining triangle.
	/// </param>
	/// <param name="value3">
	/// The coordinate on the same axis of vertex 3 of the defining triangle.
	/// </param>
	/// <param name="amount1">
	/// The normalized barycentric (areal) coordinate b2, equal to the weighting factor
	/// for vertex 2, the coordinate of which is specified in value2.
	/// </param>
	/// <param name="amount2">
	/// The normalized barycentric (areal) coordinate b3, equal to the weighting factor
	/// for vertex 3, the coordinate of which is specified in value3.
	/// </param>
	/// <returns>
	/// Cartesian coordinate of the specified point with respect to the axis being used.
	/// </returns>
	template <typename T>
	constexpr T Barycentric(
		T value1,
		T value2,
		T value3,
		T amount1,
		T amount2)
	{
		return value1 + (value2 - value1) * amount1 + (value3 - value1) * amount2;
	}

	/// <summary>
	/// Performs a Catmull-Rom interpolation using the specified positions.
	/// </summary>
	/// <param name="value1">The first position in the interpolation.</param>
	/// <param name="value2">The second position in the interpolation.</param>
	/// <param name="value3">The third position in the interpolation.</param>
	/// <param name="value4">The fourth position in the interpolation.</param>
	/// <param name="amount">Weighting factor.</param>
	/// <returns>A position that is the result of the Catmull-Rom interpolation.</returns>
	template <typename T>
	inline T CatmullRom(
		T value1,
		T value2,
		T value3,
		T value4,
		T amount)
	{
		/* Using formula from http://www.mvps.org/directx/articles/catmull/
		 * Internally using doubles not to lose precision.
		 */
		const double amountSquared = amount * amount;
		const double amountCubed = amountSquared * amount;
		return static_cast<T>(
			0.5 *
			(
				((2.0 * value2 + (value3 - value1) * amount) +
					((2.0 * value1 - 5.0 * value2 + 4.0 * value3 - value4) * amountSquared) +
					(3.0 * value2 - value1 - 3.0 * value3 + value4) * amountCubed)
				)
			);
	}

	/// <summary>
	/// Performs a Hermite spline interpolation.
	/// </summary>
	/// <param name="value1">Source position.</param>
	/// <param name="tangent1">Source tangent.</param>
	/// <param name="value2">Source position.</param>
	/// <param name="tangent2">Source tangent.</param>
	/// <param name="amount">Weighting factor.</param>
	/// <returns>The result of the Hermite spline interpolation.</returns>
	template <typename T>
	constexpr T Hermite(
		T value1,
		T tangent1,
		T value2,
		T tangent2,
		T amount)
	{
		/* All transformed to double not to lose precision
		 * Otherwise, for high numbers of param:amount the result is NaN instead
		 * of Infinity.
		 */
		const double v1 = value1, v2 = value2, t1 = tangent1, t2 = tangent2, s = amount;
		const double sCubed = s * s * s;
		const double sSquared = s * s;

		double result;
		if (Math::IsZero(amount))
		{
			result = value1;
		}
		else if (Math::Equals(amount, T(1)))
		{
			result = value2;
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

	/// <summary>
	/// Interpolates between two values using a cubic equation.
	/// </summary>
	/// <param name="value1">Source value.</param>
	/// <param name="value2">Source value.</param>
	/// <param name="amount">Weighting value.</param>
	/// <returns>Interpolated value.</returns>
	template <typename T>
	constexpr T SmoothStep(T value1, T value2, T amount)
	{
		/* It is expected that 0 < amount < 1.
		 * If amount < 0, return value1.
		 * If amount > 1, return value2.
		 */
		const T result = Math::Clamp<T>(amount, T(0), T(1));
		return Hermite<T>(value1, T(0), value2, T(0), result);
	}
}
