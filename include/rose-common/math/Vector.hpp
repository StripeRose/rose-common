#pragma once

#include "Common.hpp"
#include "Curve.hpp"
#include "Matrix.hpp"

namespace RoseCommon::Math
{
	/// <summary>
	/// Represents a mathematical vector with any amount of components.
	/// </summary>
	/*template <std::size_t N, typename T>
	class Vector
	{
	public:
		constexpr Vector()
		{
			for (std::size_t i = 0; i < N; ++i)
				Component[i] = static_cast<T>(0);
		}

		constexpr operator Matrix<N, 1, T>() const
		{
			Matrix<N, 1, T> m;

			for (std::size_t i = 0; i < N; ++i)
				m.GetCell(i, 0) = Component[i];

			return m;
		}

	public:
		T Component[N];
	};*/

	/// <summary>
	/// Represents a mathematical vector with two components.
	/// </summary>
	template <typename T>
	class Vector2
	{
	public:
		/// <summary>A Vector2 with both of its components set to one.</summary>
		static constexpr Vector2 One() { return { 1, 1 }; }

		/// <summary>A Vector2 unit vector for the X-axis.</summary>
		static constexpr Vector2 UnitX() { return { 1, 0 }; }

		/// <summary>A Vector2 unit vector for the Y-axis.</summary>
		static constexpr Vector2 UnitY() { return { 0, 1 }; }

		/// <summary>A Vector2 with both of its components set to zero.</summary>
		static constexpr Vector2 Zero() { return { 0, 0 }; }

	public:
		/// <summary>
		/// Restricts a value to be within the specified range.
		/// </summary>
		/// <param name="aValue">The vector to clamp.</param>
		/// <param name="aMinimum">The minimum clamp value.</param>
		/// <param name="aMaximum">The maximum clamp value.</param>
		/// <returns>The clamped vector.</returns>
		static constexpr Vector2 Clamp(const Vector2& aValue, const Vector2& aMinimum, const Vector2& aMaximum)
		{
			return Vector2(
				Math::Clamp<T>(aValue.X, aMinimum.X, aMaximum.X),
				Math::Clamp<T>(aValue.Y, aMinimum.Y, aMaximum.Y)
			);
		}

		/// <summary>
		/// Calculates the distance between two points.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <returns>The distance between the points.</returns>
		static constexpr T Distance(const Vector2& aValue1, const Vector2& aValue2)
		{
			return (aValue1 - aValue2).Length();
		}

		/// <summary>
		/// Calculates the distance between two points squared.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <returns>The squared distance between the points.</returns>
		static constexpr T DistanceSquared(const Vector2& aValue1, const Vector2& aValue2)
		{
			return (aValue1 - aValue2).LengthSquared();
		}

		/// <summary>
		/// Calculates the dot product of the two vectors. If the two vectors are unit vectors,
		/// the dot product returns a floating point value between - 1 and 1 that can be used to
		/// determine some properties of the angle between two vectors.For example, it can show
		/// whether the vectors are orthogonal, parallel, or have an acute or obtuse angle between them.
		/// </summary>
		/// <param name="aValue1">The first vector.</param>
		/// <param name="aValue2">The second vector.</param>
		/// <returns>The dot product of the two vectors.</returns>
		static constexpr T Dot(const Vector2& aValue1, const Vector2& aValue2)
		{
			return
				(aValue1.X * aValue2.X) +
				(aValue1.Y * aValue2.Y);
		}

		/// <summary>
		/// Performs a linear interpolation between two vectors.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <param name="anAmount">Value between 0 and 1 indicating the weight of the second vector.</param>
		/// <returns>The linear interpolation of the two vectors.</returns>
		static constexpr Vector2 Lerp(const Vector2& aValue1, const Vector2& aValue2, const T& anAmount)
		{
			return (aValue1 + ((aValue2 - aValue1) * anAmount));
		}

		/// <summary>
		/// Returns a vector that contains the highest value from each matching pair of components.
		/// </summary>
		static constexpr Vector2 Max(const Vector2& aValue1, const Vector2& aValue2)
		{
			return Vector2(
				Math::Max<T>(aValue1.X, aValue2.X),
				Math::Max<T>(aValue1.Y, aValue2.Y)
			);
		}

		/// <summary>
		/// Returns a vector that contains the lowest value from each matching pair of components.
		/// </summary>
		static constexpr Vector2 Min(const Vector2& aValue1, const Vector2& aValue2)
		{
			return Vector2(
				Math::Min<T>(aValue1.X, aValue2.X),
				Math::Min<T>(aValue1.Y, aValue2.Y)
			);
		}

		/// <summary>
		/// Returns a vector that contains reflect vector of the given vector and normal.
		/// </summary>
		static constexpr Vector2 Reflect(const Vector2& aVector, const Vector2& aNormal)
		{
			const T dotProduct = Dot(aVector, aNormal);

			return Vector2(
				aVector.X - (2.0f * aNormal.X) * dotProduct,
				aVector.Y - (2.0f * aNormal.Y) * dotProduct
			);
		}

		/// <summary>
		/// Returns a vector that contains cubic interpolation of the specified vectors.
		/// </summary>
		static constexpr Vector2 SmoothStep(const Vector2& aValue1, const Vector2& aValue2, const T& anAmount)
		{
			return Vector2(
				Math::SmoothStep<T>(aValue1.X, aValue2.X, anAmount),
				Math::SmoothStep<T>(aValue1.Y, aValue2.Y, anAmount)
			);
		}

	public:
		/// <summary>
		/// Creates a Vector2 object whose components are zero.
		/// </summary>
		constexpr Vector2()
			: Vector2(0, 0)
		{ }

		/// <summary>
		/// Creates a Vector2 object whose components have the value specified.
		/// </summary>
		/// <param name="aValue">The value both components should have.</param>
		constexpr Vector2(const T& aValue)
			: Vector2(aValue, aValue)
		{ }

		/// <summary>
		/// Creates a Vector2 object whose components have the values specified.
		/// </summary>
		/// <param name="anX">Value of the X component.</param>
		/// <param name="aY">Value of the Y component.</param>
		constexpr Vector2(const T& anX, const T& aY)
			: X(anX)
			, Y(aY)
		{ }

		template <typename U = T>
		constexpr Vector2(const Vector2<U>& aVector)
			: X(static_cast<T>(aVector.X))
			, Y(static_cast<T>(aVector.Y))
		{ }

	public:
		/// <summary>
		/// Calculates the vector length.
		/// </summary>
		/// <returns>The length of the vector.</returns>
		constexpr T Length() const
		{
			return Math::Squareroot(LengthSquared());
		}

		/// <summary>
		/// Calculates the vector squared length.
		/// </summary>
		/// <returns>The squared length of the vector.</returns>
		constexpr T LengthSquared() const
		{
			return (X * X) + (Y * Y);
		}

		/// <summary>
		/// Creates a unit vector from the specified vector with the same direction as the original vector.
		/// </summary>
		/// <returns>The unit vector.</returns>
		constexpr Vector2 Normalized() const
		{
			return (*this) / Length();
		}

		/// <summary>
		/// Modifies the vector into a unit vector with the same direction as the original vector.
		/// </summary>
		void Normalize()
		{
			(*this) /= Length();
		}

	public:
		constexpr Vector2 operator-() const
		{
			return Vector2(-X, -Y);
		}

		constexpr Vector2 operator+(const Vector2& aVector) const
		{
			return Vector2(
				X + aVector.X,
				Y + aVector.Y
			);
		}

		constexpr Vector2 operator-(const Vector2& aVector) const
		{
			return Vector2(
				X - aVector.X,
				Y - aVector.Y
			);
		}

		constexpr Vector2 operator*(const Vector2& aVector) const
		{
			return Vector2(
				X * aVector.X,
				Y * aVector.Y
			);
		}

		constexpr Vector2 operator/(const Vector2& aVector) const
		{
			return Vector2(
				X / aVector.X,
				Y / aVector.Y
			);
		}

		void operator+=(const Vector2& aVector)
		{
			X += aVector.X;
			Y += aVector.Y;
		}

		void operator-=(const Vector2& aVector)
		{
			X -= aVector.X;
			Y -= aVector.Y;
		}

		void operator*=(const Vector2& aVector)
		{
			X *= aVector.X;
			Y *= aVector.Y;
		}

		void operator/=(const Vector2& aVector)
		{
			X /= aVector.X;
			Y /= aVector.Y;
		}

		constexpr bool operator==(const Vector2& aVector) const
		{
			return Math::Equals(X, aVector.X)
				&& Math::Equals(Y, aVector.Y);
		}

		constexpr bool operator!=(const Vector2& aVector) const
		{
			return !operator==(aVector);
		}

		constexpr std::strong_ordering operator<=>(const Vector2& aVector) const
		{
			std::strong_ordering order = std::strong_order(X, aVector.X);
			if (order != std::strong_ordering::equal)
				return order;
			return std::strong_order(Y, aVector.Y);
		}

		/// <summary>The X-component of the vector.</summary>
		T X;

		/// <summary>The Y-component of the vector.</summary>
		T Y;
	};

	/// <summary>
	/// Represents a mathematical vector with three components.
	/// </summary>
	template <typename T>
	class Vector3
	{
	public:
		/// <summary>A unit Vector3 designating backward in a right-handed coordinate system (0, 0, -1).</summary>
		static constexpr Vector3 Backward() { return -UnitZ(); }

		/// <summary>A unit Vector3 designating down (0, -1, 0).</summary>
		static constexpr Vector3 Down() { return -UnitY(); }

		/// <summary>A unit Vector3 designating forward in a right-handed coordinate system (0, 0, 1).</summary>
		static constexpr Vector3 Forward() { return UnitZ(); }

		/// <summary>A unit Vector3 designating left in a right-handed coordinate system (-1, 0, 0).</summary>
		static constexpr Vector3 Left() { return -UnitX(); }

		/// <summary>A Vector3 with all of its components set to one.</summary>
		static constexpr Vector3 One() { return { 0, 0, 0 }; }

		/// <summary>A unit Vector3 designating right in a right-handed coordinate system (1, 0, 0).</summary>
		static constexpr Vector3 Right() { return UnitX(); }

		/// <summary>A Vector3 unit vector for the X-axis.</summary>
		static constexpr Vector3 UnitX() { return { 1, 0, 0 }; }

		/// <summary>A Vector3 unit vector for the Y-axis.</summary>
		static constexpr Vector3 UnitY() { return { 0, 1, 0 }; }

		/// <summary>A Vector3 unit vector for the Z-axis.</summary>
		static constexpr Vector3 UnitZ() { return { 0, 0, 1 }; }

		/// <summary>A unit Vector3 designating up (0, 1, 0).</summary>
		static constexpr Vector3 Up() { return UnitY(); }

		/// <summary>A Vector3 with all of its components set to zero.</summary>
		static constexpr Vector3 Zero() { return { 0, 0, 0 }; }

	public:
		/// <summary>
		/// Restricts a value to be within the specified range.
		/// </summary>
		/// <param name="aVector">The vector to clamp.</param>
		/// <param name="aMinimum">The minimum clamp value.</param>
		/// <param name="aMaximum">The maximum clamp value.</param>
		/// <returns>The clamped vector.</returns>
		static constexpr Vector3 Clamp(const Vector3& aVector, const Vector3& aMinimum, const Vector3& aMaximum)
		{
			return Vector3(
				Math::Clamp<T>(aVector.X, aMinimum.X, aMaximum.X),
				Math::Clamp<T>(aVector.Y, aMinimum.Y, aMaximum.Y),
				Math::Clamp<T>(aVector.Z, aMinimum.Z, aMaximum.Z)
			);
		}

		/// <summary>
		/// Calculates the cross product of two vectors.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <returns>Cross product of the source vectors.</returns>
		static constexpr Vector3 Cross(const Vector3& aValue1, const Vector3& aValue2)
		{
			return Vector3(
				aValue1.Y * aValue2.Z - aValue1.Z * aValue2.Y,
				aValue1.Z * aValue2.X - aValue1.X * aValue2.Z,
				aValue1.X * aValue2.Y - aValue1.Y * aValue2.X
			);
		}

		/// <summary>
		/// Calculates the distance between two points.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <returns>The distance between the points.</returns>
		static constexpr T Distance(const Vector3& aValue1, const Vector3& aValue2)
		{
			return (aValue1 - aValue2).Length();
		}

		/// <summary>
		/// Calculates the distance between two points squared.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <returns>The squared distance between the points.</returns>
		static constexpr T DistanceSquared(const Vector3& aValue1, const Vector3& aValue2)
		{
			return (aValue1 - aValue2).LengthSquared();
		}

		/// <summary>
		/// Calculates the dot product of the two vectors. If the two vectors are unit vectors,
		/// the dot product returns a floating point value between - 1 and 1 that can be used to
		/// determine some properties of the angle between two vectors.For example, it can show
		/// whether the vectors are orthogonal, parallel, or have an acute or obtuse angle between them.
		/// </summary>
		/// <param name="aValue1">The first vector.</param>
		/// <param name="aValue2">The second vector.</param>
		/// <returns>The dot product of the two vectors.</returns>
		static constexpr T Dot(const Vector3& aValue1, const Vector3& aValue2)
		{
			return
				(aValue1.X * aValue2.X) +
				(aValue1.Y * aValue2.Y) +
				(aValue1.Z * aValue2.Z);
		}

		/// <summary>
		/// Performs a linear interpolation between two vectors.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <param name="anAmount">Value between 0 and 1 indicating the weight of the second vector.</param>
		/// <returns>The linear interpolation of the two vectors.</returns>
		static constexpr Vector3 Lerp(const Vector3& aValue1, const Vector3& aValue2, const T& anAmount)
		{
			return (aValue1 + ((aValue2 - aValue1) * anAmount));
		}

		/// <summary>
		/// Performs a spherical interpolation between two vectors.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <param name="anAmount">Value between 0 and 1 indicating the weight of the second vector.</param>
		/// <returns>The spherical interpolation of the two vectors.</returns>
		/*static constexpr Vector3 Slerp(const Vector3& aValue1, const Vector3& aValue2, const T& anAmount)
		{
			if (aValue1 == aValue2)
				return aValue1;

			const T dot = Math::Clamp(Dot(aValue1, aValue2), -1.f, 1.f);
			const T theta = Math::ArcCosine(dot) * anAmount;
			Vector3 relativeVector = aValue2 - (aValue1 * dot);
			relativeVector.Normalize();
			return ((aValue1 * Math::Cosine(theta)) + (relativeVector * Math::Sine(theta)));
		}*/

		/// <summary>
		/// Returns a vector that contains the highest value from each matching pair of components.
		/// </summary>
		static constexpr Vector3 Max(const Vector3& aValue1, const Vector3& aValue2)
		{
			return Vector3(
				Math::Max<T>(aValue1.X, aValue2.X),
				Math::Max<T>(aValue1.Y, aValue2.Y),
				Math::Max<T>(aValue1.Z, aValue2.Z)
			);
		}

		/// <summary>
		/// Returns a vector that contains the lowest value from each matching pair of components.
		/// </summary>
		static constexpr Vector3 Min(const Vector3& aValue1, const Vector3& aValue2)
		{
			return Vector3(
				Math::Min<T>(aValue1.X, aValue2.X),
				Math::Min<T>(aValue1.Y, aValue2.Y),
				Math::Min<T>(aValue1.Z, aValue2.Z)
			);
		}

		/// <summary>
		/// Returns a vector that contains reflect vector of the given vector and normal.
		/// </summary>
		static constexpr Vector3 Reflect(const Vector3& aVector, const Vector3& aNormal)
		{
			Vector3 result;
			const T dotProduct = Dot(aVector, aNormal);
			result.X = aVector.X - (2.0f * aNormal.X) * dotProduct;
			result.Y = aVector.Y - (2.0f * aNormal.Y) * dotProduct;
			result.Z = aVector.Z - (2.0f * aNormal.Z) * dotProduct;
			return result;
		}

		/// <summary>
		/// Returns a vector that contains cubic interpolation of the specified vectors.
		/// </summary>
		static constexpr Vector3 SmoothStep(const Vector3& aValue1, const Vector3& aValue2, const T& anAmount)
		{
			return Vector3(
				Math::SmoothStep<T>(aValue1.X, aValue2.X, anAmount),
				Math::SmoothStep<T>(aValue1.Y, aValue2.Y, anAmount),
				Math::SmoothStep<T>(aValue1.Z, aValue2.Z, anAmount)
			);
		}

	public:
		/// <summary>
		/// Creates a Vector3 object whose components are zero.
		/// </summary>
		constexpr Vector3()
			: Vector3(0, 0, 0)
		{ }

		/// <summary>
		/// Creates a Vector3 object whose components have the value specified.
		/// </summary>
		/// <param name="aValue">The value both components should have.</param>
		constexpr Vector3(const T& aValue)
			: Vector3(aValue, aValue, aValue)
		{ }

		/// <summary>
		/// Creates a Vector3 object whose components have the values specified.
		/// </summary>
		/// <param name="anX">Value of the X component.</param>
		/// <param name="aY">Value of the Y component.</param>
		/// <param name="aZ">Value of the Z component.</param>
		constexpr Vector3(const T& anX, const T& aY, const T& aZ)
			: X(anX)
			, Y(aY)
			, Z(aZ)
		{ }

		template <typename U = T>
		constexpr Vector3(const Vector3<U>& aVector)
			: X(static_cast<T>(aVector.X))
			, Y(static_cast<T>(aVector.Y))
			, Z(static_cast<T>(aVector.Z))
		{ }

		/// <summary>
		/// Creates a Vector3 object from a Vector2 and a Z value.
		/// </summary>
		/// <param name="aVector">Value of the X and Y components.</param>
		/// <param name="aZ">Value of the Z component.</param>
		explicit constexpr Vector3(const Vector2<T>& aVector, const T& aZ = 0)
			: Vector3(aVector.X, aVector.Y, aZ)
		{ }

	public:
		/// <summary>
		/// Calculates the vector length.
		/// </summary>
		/// <returns>The length of the vector.</returns>
		constexpr T Length() const
		{
			return Math::Squareroot(LengthSquared());
		}

		/// <summary>
		/// Calculates the vector squared length.
		/// </summary>
		/// <returns>The squared length of the vector.</returns>
		constexpr T LengthSquared() const
		{
			return (X * X) + (Y * Y) + (Z * Z);
		}

		/// <summary>
		/// Creates a unit vector from the specified vector with the same direction as the original vector.
		/// </summary>
		/// <returns>The unit vector.</returns>
		constexpr Vector3 Normalized() const
		{
			return (*this) / Length();
		}

		/// <summary>
		/// Modifies the vector into a unit vector with the same direction as the original vector.
		/// </summary>
		void Normalize()
		{
			(*this) /= Length();
		}

	public:
		explicit constexpr operator Vector2<T>() const
		{
			return Vector2<T>(X, Y);
		}

		constexpr Vector3 operator-() const
		{
			return Vector3(-X, -Y, -Z);
		}

		constexpr Vector3 operator+(const Vector3& aVector) const
		{
			return Vector3(
				X + aVector.X,
				Y + aVector.Y,
				Z + aVector.Z
			);
		}

		constexpr Vector3 operator-(const Vector3& aVector) const
		{
			return Vector3(
				X - aVector.X,
				Y - aVector.Y,
				Z - aVector.Z
			);
		}

		constexpr Vector3 operator*(const Vector3& aVector) const
		{
			return Vector3(
				X * aVector.X,
				Y * aVector.Y,
				Z * aVector.Z
			);
		}

		constexpr Vector3 operator/(const Vector3& aVector) const
		{
			return Vector3(
				X / aVector.X,
				Y / aVector.Y,
				Z / aVector.Z
			);
		}

		void operator+=(const Vector3& aVector)
		{
			X += aVector.X;
			Y += aVector.Y;
			Z += aVector.Z;
		}

		void operator-=(const Vector3& aVector)
		{
			X -= aVector.X;
			Y -= aVector.Y;
			Z -= aVector.Z;
		}

		void operator*=(const Vector3& aVector)
		{
			X *= aVector.X;
			Y *= aVector.Y;
			Z *= aVector.Z;
		}

		void operator/=(const Vector3& aVector)
		{
			X /= aVector.X;
			Y /= aVector.Y;
			Z /= aVector.Z;
		}

		constexpr bool operator==(const Vector3& aVector) const
		{
			return Math::Equals(X, aVector.X)
				&& Math::Equals(Y, aVector.Y)
				&& Math::Equals(Z, aVector.Z);
		}

		constexpr bool operator!=(const Vector3& aVector) const
		{
			return !operator==(aVector);
		}

		constexpr std::strong_ordering operator<=>(const Vector3& aVector) const
		{
			std::strong_ordering order = std::strong_order(X, aVector.X);
			if (order != std::strong_ordering::equal)
				return order;
			order = std::strong_order(Y, aVector.Y);
			if (order != std::strong_ordering::equal)
				return order;
			return std::strong_order(Z, aVector.Z);
		}

		/// <summary>The X-component of the vector.</summary>
		T X;

		/// <summary>The Y-component of the vector.</summary>
		T Y;

		/// <summary>The Z-component of the vector.</summary>
		T Z;
	};

	/// <summary>
	/// Represents a mathematical vector with four components.
	/// </summary>
	template <typename T>
	class Vector4
	{
	public:
		/// <summary>A Vector4 with all of its components set to one.</summary>
		static constexpr Vector4 One() { return { 1, 1, 1, 1 }; }

		/// <summary>A Vector4 unit vector for the X-axis.</summary>
		static constexpr Vector4 UnitX() { return { 1, 0, 0, 0 }; }

		/// <summary>A Vector4 unit vector for the Y-axis.</summary>
		static constexpr Vector4 UnitY() { return { 0, 1, 0, 0 }; }

		/// <summary>A Vector4 unit vector for the Z-axis.</summary>
		static constexpr Vector4 UnitZ() { return { 0, 0, 1, 0 }; }

		/// <summary>A Vector4 unit vector for the W-axis.</summary>
		static constexpr Vector4 UnitW() { return { 0, 0, 0, 1 }; }

		/// <summary>A Vector4 with all of its components set to zero.</summary>
		static constexpr Vector4 Zero() { return { 0, 0, 0, 0 }; }

	public:
		/// <summary>
		/// Restricts a value to be within the specified range.
		/// </summary>
		/// <param name="aVector">The vector to clamp.</param>
		/// <param name="aMinimum">The minimum clamp value.</param>
		/// <param name="aMaximum">The maximum clamp value.</param>
		/// <returns>The clamped vector.</returns>
		static constexpr Vector4 Clamp(const Vector4& aVector, const Vector4& aMinimum, const Vector4& aMaximum)
		{
			return Vector3(
				Math::Clamp<T>(aVector.X, aMinimum.X, aMaximum.X),
				Math::Clamp<T>(aVector.Y, aMinimum.Y, aMaximum.Y),
				Math::Clamp<T>(aVector.Z, aMinimum.Z, aMaximum.Z),
				Math::Clamp<T>(aVector.W, aMinimum.W, aMaximum.W)
			);
		}

		/// <summary>
		/// Calculates the distance between two points.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <returns>The distance between the points.</returns>
		static constexpr T Distance(const Vector4& aValue1, const Vector4& aValue2)
		{
			return (aValue1 - aValue2).Length();
		}

		/// <summary>
		/// Calculates the distance between two points squared.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <returns>The squared distance between the points.</returns>
		static constexpr T DistanceSquared(const Vector4& aValue1, const Vector4& aValue2)
		{
			return (aValue1 - aValue2).LengthSquared();
		}

		/// <summary>
		/// Calculates the dot product of the two vectors. If the two vectors are unit vectors,
		/// the dot product returns a floating point value between - 1 and 1 that can be used to
		/// determine some properties of the angle between two vectors.For example, it can show
		/// whether the vectors are orthogonal, parallel, or have an acute or obtuse angle between them.
		/// </summary>
		/// <param name="aValue1">The first vector.</param>
		/// <param name="aValue2">The second vector.</param>
		/// <returns>The dot product of the two vectors.</returns>
		static constexpr T Dot(const Vector4& aValue1, const Vector4& aValue2)
		{
			return
				(aValue1.X * aValue2.X) +
				(aValue1.Y * aValue2.Y) +
				(aValue1.Z * aValue2.Z) +
				(aValue1.W * aValue2.W);
		}

		/// <summary>
		/// Performs a linear interpolation between two vectors.
		/// </summary>
		/// <param name="aValue1">Source vector.</param>
		/// <param name="aValue2">Source vector.</param>
		/// <param name="anAmount">Value between 0 and 1 indicating the weight of the second vector.</param>
		/// <returns>The linear interpolation of the two vectors.</returns>
		static constexpr Vector4 Lerp(const Vector4& aValue1, const Vector4& aValue2, const T& anAmount)
		{
			return (aValue1 + ((aValue2 - aValue1) * anAmount));
		}

		/// <summary>
		/// Returns a vector that contains the highest value from each matching pair of components.
		/// </summary>
		static constexpr Vector4 Max(const Vector4& aValue1, const Vector4& aValue2)
		{
			return Vector4(
				Math::Max<T>(aValue1.X, aValue2.X),
				Math::Max<T>(aValue1.Y, aValue2.Y),
				Math::Max<T>(aValue1.Z, aValue2.Z),
				Math::Max<T>(aValue1.W, aValue2.W)
			);
		}

		/// <summary>
		/// Returns a vector that contains the lowest value from each matching pair of components.
		/// </summary>
		static constexpr Vector4 Min(const Vector4& aValue1, const Vector4& aValue2)
		{
			return Vector4(
				Math::Min<T>(aValue1.X, aValue2.X),
				Math::Min<T>(aValue1.Y, aValue2.Y),
				Math::Min<T>(aValue1.Z, aValue2.Z),
				Math::Min<T>(aValue1.W, aValue2.W)
			);
		}

		/// <summary>
		/// Returns a vector that contains cubic interpolation of the specified vectors.
		/// </summary>
		static constexpr Vector4 SmoothStep(const Vector4& aValue1, const Vector4& aValue2, const T& anAmount)
		{
			return Vector4(
				Math::SmoothStep<T>(aValue1.X, aValue2.X, anAmount),
				Math::SmoothStep<T>(aValue1.Y, aValue2.Y, anAmount),
				Math::SmoothStep<T>(aValue1.Z, aValue2.Z, anAmount),
				Math::SmoothStep<T>(aValue1.W, aValue2.W, anAmount)
			);
		}

	public:
		/// <summary>
		/// Creates a Vector4 object whose components are zero.
		/// </summary>
		constexpr Vector4()
			: Vector4(0, 0, 0)
		{ }

		/// <summary>
		/// Creates a Vector4 object whose components have the value specified.
		/// </summary>
		/// <param name="aValue">The value both components should have.</param>
		constexpr Vector4(const T& aValue)
			: Vector4(aValue, aValue, aValue, aValue)
		{ }

		/// <summary>
		/// Creates a Vector4 object whose components have the values specified.
		/// </summary>
		/// <param name="anX">Value of the X component.</param>
		/// <param name="aY">Value of the Y component.</param>
		/// <param name="aZ">Value of the Z component.</param>
		/// <param name="aW">Value of the W component.</param>
		constexpr Vector4(const T& anX, const T& aY, const T& aZ, const T& aW)
			: X(anX)
			, Y(aY)
			, Z(aZ)
			, W(aW)
		{ }

		template <typename U = T>
		constexpr Vector4(const Vector4<U>& aVector)
			: X(static_cast<T>(aVector.X))
			, Y(static_cast<T>(aVector.Y))
			, Z(static_cast<T>(aVector.Z))
			, W(static_cast<T>(aVector.W))
		{ }

		/// <summary>
		/// Creates a Vector4 object from a Vector2, a Z value and a W value.
		/// </summary>
		/// <param name="aVector">Value of the X and Y components.</param>
		/// <param name="aZ">Value of the Z component.</param>
		/// <param name="aW">Value of the W component.</param>
		explicit constexpr Vector4(const Vector2<T>& aVector, const T& aZ = 0, const T& aW = 1)
			: Vector4(aVector.X, aVector.Y, aZ, aW)
		{ }

		/// <summary>
		/// Creates a Vector4 object from a Vector3 and a W value.
		/// </summary>
		/// <param name="aVector">Value of the X and Y, and Z components.</param>
		/// <param name="aW">Value of the W component.</param>
		explicit constexpr Vector4(const Vector3<T>& aVector, const T& aW = 1)
			: Vector4(aVector.X, aVector.Y, aVector.Z, aW)
		{ }

	public:
		/// <summary>
		/// Calculates the vector length.
		/// </summary>
		/// <returns>The length of the vector.</returns>
		constexpr T Length() const
		{
			return Math::Squareroot(LengthSquared());
		}

		/// <summary>
		/// Calculates the vector squared length.
		/// </summary>
		/// <returns>The squared length of the vector.</returns>
		constexpr T LengthSquared() const
		{
			return (X * X) + (Y * Y) + (Z * Z) + (W * W);
		}

		/// <summary>
		/// Creates a unit vector from the specified vector with the same direction as the original vector.
		/// </summary>
		/// <returns>The unit vector.</returns>
		constexpr Vector4 Normalized() const
		{
			return (*this) / Length();
		}

		/// <summary>
		/// Modifies the vector into a unit vector with the same direction as the original vector.
		/// </summary>
		void Normalize()
		{
			(*this) /= Length();
		}

	public:
		explicit constexpr operator Vector2<T>() const
		{
			return Vector2<T>(X, Y);
		}

		explicit constexpr operator Vector3<T>() const
		{
			return Vector3<T>(X, Y, Z);
		}

		constexpr Vector4 operator-() const
		{
			return Vector4(-X, -Y, -Z, -W);
		}

		constexpr Vector4 operator+(const Vector4& aVector) const
		{
			return Vector4(
				X + aVector.X,
				Y + aVector.Y,
				Z + aVector.Z,
				W + aVector.W
			);
		}

		constexpr Vector4 operator-(const Vector4& aVector) const
		{
			return Vector4(
				X - aVector.X,
				Y - aVector.Y,
				Z - aVector.Z,
				W - aVector.W
			);
		}

		constexpr Vector4 operator*(const Vector4& aVector) const
		{
			return Vector4(
				X * aVector.X,
				Y * aVector.Y,
				Z * aVector.Z,
				W * aVector.W
			);
		}

		constexpr Vector4 operator/(const Vector4& aVector) const
		{
			return Vector4(
				X / aVector.X,
				Y / aVector.Y,
				Z / aVector.Z,
				W / aVector.W
			);
		}

		void operator+=(const Vector4& aVector)
		{
			X += aVector.X;
			Y += aVector.Y;
			Z += aVector.Z;
			W += aVector.W;
		}

		void operator-=(const Vector4& aVector)
		{
			X -= aVector.X;
			Y -= aVector.Y;
			Z -= aVector.Z;
			W -= aVector.W;
		}

		void operator*=(const Vector4& aVector)
		{
			X *= aVector.X;
			Y *= aVector.Y;
			Z *= aVector.Z;
			W *= aVector.W;
		}

		void operator/=(const Vector4& aVector)
		{
			X /= aVector.X;
			Y /= aVector.Y;
			Z /= aVector.Z;
			W /= aVector.W;
		}

		constexpr bool operator==(const Vector4& aVector) const
		{
			return Math::Equals(X, aVector.X)
				&& Math::Equals(Y, aVector.Y)
				&& Math::Equals(Z, aVector.Z)
				&& Math::Equals(W, aVector.W);
		}

		constexpr bool operator!=(const Vector4& aVector) const
		{
			return !operator==(aVector);
		}

		constexpr std::strong_ordering operator<=>(const Vector4& aVector) const
		{
			std::strong_ordering order = std::strong_order(X, aVector.X);
			if (order != std::strong_ordering::equal)
				return order;
			order = std::strong_order(Y, aVector.Y);
			if (order != std::strong_ordering::equal)
				return order;
			order = std::strong_order(Z, aVector.Z);
			if (order != std::strong_ordering::equal)
				return order;
			return std::strong_order(W, aVector.W);
		}

		/// <summary>The X-component of the vector.</summary>
		T X;

		/// <summary>The Y-component of the vector.</summary>
		T Y;

		/// <summary>The Z-component of the vector.</summary>
		T Z;

		/// <summary>The W-component of the vector.</summary>
		T W;
	};
}