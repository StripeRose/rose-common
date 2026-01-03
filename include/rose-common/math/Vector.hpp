#pragma once

#include "../RoseCommon_Namespace.hpp"

#include "Common.hpp"
#include "Curve.hpp"
#include "Matrix.hpp"
#include "Trigonometry.hpp"

namespace ROSECOMMON_MATH_NAMESPACE
{
	/**
	 * @brief A mathematical vector with two components.
	 * @tparam T A type used for each component.
	 */
	template <typename T>
	class Vector2
	{
	public:

		//--------------------------------------------------
		// * Types
		//--------------------------------------------------
		#pragma region Types

		using ComponentType = T;

		#pragma endregion

		//--------------------------------------------------
		// * Static constants
		//--------------------------------------------------
		#pragma region Static constants

		/**
		 * @brief Create a vector with both of its components set to one.
		 */
		inline static constexpr Vector2 One() { return { 1, 1 }; }

		/**
		 * @brief Create a unit-vector for the X-axis.
		 */
		inline static constexpr Vector2 UnitX() { return { 1, 0 }; }

		/**
		 * @brief Create a unit vector for the Y-axis.
		 */
		inline static constexpr Vector2 UnitY() { return { 0, 1 }; }

		/**
		 * @brief Create a vector with both of its components set to zero.
		 */
		inline static constexpr Vector2 Zero() { return { 0, 0 }; }

		#pragma endregion

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize both components to be zero.
		 */
		constexpr Vector2();

		/**
		 * @brief Initialize both components to the specified value.
		 * @param aValue The value both components should have.
		 */
		explicit constexpr Vector2(const T& aValue);

		/**
		 * @brief Initialize each component to the specified value.
		 * @param anX Value of the X component.
		 * @param aY Value of the Y component.
		 */
		constexpr Vector2(const T& anX, const T& aY);

		/**
		 * @brief Initialize the components with values from another type of vector.
		 * @tparam U The source vector component type.
		 * @param aVector A vector to convert the values from.
		 */
		template <typename U = T>
		explicit constexpr Vector2(const Vector2<U>& aVector);

		/**
		 * @brief Initialize the components with the values from a 1x2 matrix.
		 * @param aColumnMatrix A column matrix to initialize with.
		 */
		explicit constexpr Vector2(const Matrix<1, 2, T>& aColumnMatrix);

		/**
		 * @brief Initialize the components with the values from a 2x1 matrix.
		 * @param aRowMatrix A row matrix to initialize with.
		 */
		explicit constexpr Vector2(const Matrix<2, 1, T>& aRowMatrix);

		#pragma endregion

		//--------------------------------------------------
		// * Properties
		//--------------------------------------------------
		#pragma region Properties

		/**
		 * @brief The X-component of the vector.
		 */
		T X;

		/**
		 * @brief The Y-component of the vector.
		 */
		T Y;

		#pragma endregion

		//--------------------------------------------------
		// * Methods
		//--------------------------------------------------
		#pragma region Methods

		/**
		 * @brief Restrict a value to be within the specified range.
		 * @param aValue The vector to clamp.
		 * @param aMinimum The minimum clamp value.
		 * @param aMaximum The maximum clamp value.
		 * @return The clamped vector.
		 */
		static constexpr Vector2 Clamp(const Vector2& aValue, const Vector2& aMinimum, const Vector2& aMaximum);

		/**
		 * @brief Assuming the vector defines the size of a box, calculate its area.
		 * @return The area of the box.
		 */
		inline constexpr T Content() const;

		/**
		 * @brief Calculate the distance between two points.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The distance between the points.
		 */
		static constexpr T Distance(const Vector2& aValue1, const Vector2& aValue2);

		/**
		 * @brief Calculate the distance between two points squared.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The squared distance between the points.
		 */
		static constexpr T DistanceSquared(const Vector2& aValue1, const Vector2& aValue2);

		/**
		 * @brief Calculate the dot product of the two vectors. If the two vectors are unit vectors,
		 * 	      the dot product returns a floating point value between - 1 and 1 that can be used to
		 * 	      determine some properties of the angle between two vectors. For example, it can show
		 * 	      whether the vectors are orthogonal, parallel, or have an acute or obtuse angle between them.
		 * @param aValue1 The first vector.
		 * @param aValue2 The second vector.
		 * @return The dot product of the two vectors.
		 */
		static constexpr T Dot(const Vector2& aValue1, const Vector2& aValue2);

		/**
		 * @brief Calculate the vector length.
		 * @return The length of the vector.
		 */
		constexpr T Length() const;

		/**
		 * @brief Calculate the vector squared length.
		 * @return The squared length of the vector.
		 */
		constexpr T LengthSquared() const;

		/**
		 * @brief Linearly interpolate between two vectors.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector.
		 * @return A vector containing the linear interpolation result.
		 */
		static constexpr Vector2 Lerp(const Vector2& aValue1, const Vector2& aValue2, const T& anAmount);

		/**
		 * @brief Get the largest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the highest value from each matching pair of components.
		 */
		static constexpr Vector2 Max(const Vector2& aValue1, const Vector2& aValue2);

		/**
		 * @brief Get the smallest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the lowest value from each matching pair of components.
		 */
		static constexpr Vector2 Min(const Vector2& aValue1, const Vector2& aValue2);

		/**
		 * @brief Create a unit vector from the specified vector with the same direction as the original vector.
		 * @return The unit vector.
		 */
		inline constexpr Vector2 Normalized() const { return (*this) / Length(); }

		/**
		 * @brief Modify the vector into a unit vector with the same direction as the original vector.
		 */
		inline void Normalize() { (*this) /= Length(); }

		/**
		 * @brief Calculate the reflection vector, given an incoming direction and normal.
		 * @param aVector A normalized incoming direction.
		 * @param aNormal A normal about which the vector should be reflected.
		 * @return A vector containing the reflected direction.
		 */
		static constexpr Vector2 Reflect(const Vector2& aVector, const Vector2& aNormal);

		/**
		 * @brief Smoothly interpolate two vectors using cubic interpolation.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector in the interpolation.
		 * @return A vector containing the cubic interpolation result.
		 */
		static constexpr Vector2 SmoothStep(const Vector2& aValue1, const Vector2& aValue2, const T& anAmount);

		/**
		 * @brief Create a 1x2 column-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		inline constexpr Matrix<1, 2, T> ToColumnMatrix() const { return Matrix<1, 2, T>({ X, Y }); }

		/**
		 * @brief Create a 2x1 row-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		inline constexpr Matrix<2, 1, T> ToRowMatrix() const { return Matrix<2, 1, T>({ X, Y }); }

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		inline constexpr Vector2 operator-() const { return Vector2(-X, -Y); }

		inline constexpr Vector2 operator+(const Vector2& aVector) const { return Vector2(X + aVector.X, Y + aVector.Y); }
		inline constexpr Vector2 operator-(const Vector2& aVector) const { return Vector2(X - aVector.X, Y - aVector.Y); }
		inline constexpr Vector2 operator*(const Vector2& aVector) const { return Vector2(X * aVector.X, Y * aVector.Y); }
		inline constexpr Vector2 operator/(const Vector2& aVector) const { return Vector2(X / aVector.X, Y / aVector.Y); }

		inline constexpr Vector2 operator*(const Matrix<2, 2, T>& aMatrix) const { return Vector2(ToRowMatrix() * aMatrix); }

		inline void operator+=(const Vector2& aVector) { X += aVector.X; Y += aVector.Y; }
		inline void operator-=(const Vector2& aVector) { X -= aVector.X; Y -= aVector.Y; }
		inline void operator*=(const Vector2& aVector) { X *= aVector.X; Y *= aVector.Y; }
		inline void operator/=(const Vector2& aVector) { X /= aVector.X; Y /= aVector.Y; }

		inline void operator*=(const Matrix<2, 2, T>& aMatrix) { (*this) = Vector2(ToRowMatrix() * aMatrix); }

		inline constexpr Vector2 operator*(const T& aScalar) const { return Vector2(X * aScalar, Y * aScalar); }
		inline constexpr Vector2 operator/(const T& aScalar) const { return Vector2(X / aScalar, Y / aScalar); }
		inline void operator*=(const T& aScalar) { X *= aScalar; Y *= aScalar; }
		inline void operator/=(const T& aScalar) { X /= aScalar; Y /= aScalar; }

		inline constexpr bool operator==(const Vector2& aVector) const { return ROSECOMMON_MATH_NAMESPACE::Equals(X, aVector.X) && ROSECOMMON_MATH_NAMESPACE::Equals(Y, aVector.Y); }
		inline constexpr bool operator!=(const Vector2& aVector) const { return !operator==(aVector); }

		template <typename U = T>
		constexpr std::strong_ordering operator<=>(const Vector2<U>& aVector) const
		{
			std::strong_ordering order = std::strong_order(X, aVector.X);
			if (order != std::strong_ordering::equal)
				return order;
			return std::strong_order(Y, aVector.Y);
		}

		#pragma endregion
	};

	/**
	 * @brief A mathematical vector with three components.
	 * @tparam T A type used for each component.
	 */
	template <typename T>
	class Vector3
	{
	public:

		//--------------------------------------------------
		// * Types
		//--------------------------------------------------
		#pragma region Types

		using ComponentType = T;

		#pragma endregion

		//--------------------------------------------------
		// * Static constants
		//--------------------------------------------------
		#pragma region Static constants

		/**
		 * @brief Create a unit-vector designating backward in a left-handed coordinate system.
		 */
		inline static constexpr Vector3 Backward() { return -UnitZ(); }

		/**
		 * @brief Create a unit-vector designating down.
		 */
		inline static constexpr Vector3 Down() { return -UnitY(); }

		/**
		  * @brief Create a unit-vector designating forward in a left-handed coordinate system.
		  */
		inline static constexpr Vector3 Forward() { return UnitZ(); }

		/**
		  * @brief Create a unit-vector designating left in a left-handed coordinate system.
		  */
		inline static constexpr Vector3 Left() { return -UnitX(); }

		/**
		  * @brief Create a vector with all of its components set to one.
		  */
		inline static constexpr Vector3 One() { return { 1, 1, 1 }; }

		/**
		  * @brief Create a unit-vector designating right in a left-handed coordinate system.
		  */
		inline static constexpr Vector3 Right() { return UnitX(); }

		/**
		  * @brief Create a unit-vector for the X-axis.
		  */
		inline static constexpr Vector3 UnitX() { return { 1, 0, 0 }; }

		/**
		  * @brief Create a unit-vector for the Y-axis.
		  */
		inline static constexpr Vector3 UnitY() { return { 0, 1, 0 }; }

		/**
		  * @brief Create a unit-vector for the Z-axis.
		  */
		inline static constexpr Vector3 UnitZ() { return { 0, 0, 1 }; }

		/**
		  * @brief Create a unit-vector designating up.
		  */
		inline static constexpr Vector3 Up() { return UnitY(); }

		/**
		  * @brief Create a vector with all of its components set to zero.
		  */
		inline static constexpr Vector3 Zero() { return { 0, 0, 0 }; }

		#pragma endregion

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize the components to be zero.
		 */
		constexpr Vector3();

		/**
		 * @brief Initialize the components to the specified value.
		 * @param aValue The value all components should have.
		 */
		explicit constexpr Vector3(const T& aValue);

		/**
		 * @brief Initialize each component to the specified value.
		 * @param anX Value of the X component.
		 * @param aY Value of the Y component.
		 * @param aZ Value of the Z component.
		 */
		constexpr Vector3(const T& anX, const T& aY, const T& aZ);

		/**
		 * @brief Initialize the components with values from another type of vector.
		 * @tparam U The source vector component type.
		 * @param aVector A vector to convert the values from.
		 */
		template <typename U = T>
		explicit constexpr Vector3(const Vector3<U>& aVector);

		/**
		 * @brief Initialize the components from a Vector2 and a Z value.
		 * @param aVector A vector containing the values for X and Y components.
		 * @param aZ A value for the Z component.
		 */
		explicit constexpr Vector3(const Vector2<T>& aVector, const T& aZ = 0);

		/**
		 * @brief Initialize the components with the values from a 1x3 matrix.
		 * @param aColumnMatrix A column matrix to initialize with.
		 */
		explicit constexpr Vector3(const Matrix<1, 3, T>& aColumnMatrix);

		/**
		 * @brief Initialize the components with the values from a 3x1 matrix.
		 * @param aRowMatrix A row matrix to initialize with.
		 */
		explicit constexpr Vector3(const Matrix<3, 1, T>& aRowMatrix);

		#pragma endregion

		//--------------------------------------------------
		// * Properties
		//--------------------------------------------------
		#pragma region Properties

		/**
		 * @brief The X-component of the vector.
		 */
		T X;

		/**
		 * @brief The Y-component of the vector.
		 */
		T Y;

		/**
		 * @brief The Z-component of the vector.
		 */
		T Z;

		#pragma endregion

		//--------------------------------------------------
		// * Methods
		//--------------------------------------------------
		#pragma region Methods

		/**
		 * @brief Restrict a value to be within the specified range.
		 * @param aValue The vector to clamp.
		 * @param aMinimum The minimum clamp value.
		 * @param aMaximum The maximum clamp value.
		 * @return The clamped vector.
		 */
		static constexpr Vector3 Clamp(const Vector3& aVector, const Vector3& aMinimum, const Vector3& aMaximum);

		/**
		 * @brief Assuming the vector defines the size of a box, calculate the volume.
		 * @return The volume of the box.
		 */
		inline constexpr T Content() const;

		/**
		 * @brief Calculate the cross-product of two unit-vectors.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The cross-product of the two vectors.
		 */
		static constexpr Vector3 Cross(const Vector3& aValue1, const Vector3& aValue2);

		/**
		 * @brief Calculate the distance between two points.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The distance between the points.
		 */
		static constexpr T Distance(const Vector3& aValue1, const Vector3& aValue2);

		/**
		 * @brief Calculate the distance between two points squared.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The squared distance between the points.
		 */
		static constexpr T DistanceSquared(const Vector3& aValue1, const Vector3& aValue2);

		/**
		 * @brief Calculate the dot product of the two vectors. If the two vectors are unit vectors,
		 * 	      the dot product returns a floating point value between - 1 and 1 that can be used to
		 * 	      determine some properties of the angle between two vectors. For example, it can show
		 * 	      whether the vectors are orthogonal, parallel, or have an acute or obtuse angle between them.
		 * @param aValue1 The first vector.
		 * @param aValue2 The second vector.
		 * @return The dot product of the two vectors.
		 */
		static constexpr T Dot(const Vector3& aValue1, const Vector3& aValue2);

		/**
		 * @brief Calculate the vector length.
		 * @return The length of the vector.
		 */
		constexpr T Length() const;

		/**
		 * @brief Calculate the vector squared length.
		 * @return The squared length of the vector.
		 */
		constexpr T LengthSquared() const;

		/**
		 * @brief Linearly interpolate between two vectors.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector.
		 * @return A vector containing the linear interpolation result.
		 */
		static constexpr Vector3 Lerp(const Vector3& aValue1, const Vector3& aValue2, const T& anAmount);

		/**
		 * @brief Spherically interpolate between two vectors.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector.
		 * @return The spherical interpolation of the two vectors.
		 */
		static constexpr Vector3 Slerp(const Vector3& aValue1, const Vector3& aValue2, const T& anAmount);

		/**
		 * @brief Get the largest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the highest value from each matching pair of components.
		 */
		static constexpr Vector3 Max(const Vector3& aValue1, const Vector3& aValue2);

		/**
		 * @brief Get the smallest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the lowest value from each matching pair of components.
		 */
		static constexpr Vector3 Min(const Vector3& aValue1, const Vector3& aValue2);

		/**
		 * @brief Create a unit vector from the specified vector with the same direction as the original vector.
		 * @return The unit vector.
		 */
		inline constexpr Vector3 Normalized() const { return (*this) / Length(); }

		/**
		 * @brief Modify the vector into a unit vector with the same direction as the original vector.
		 */
		inline void Normalize() { (*this) /= Length(); }

		/**
		 * @brief Calculate the reflection vector, given an incoming direction and normal.
		 * @param aVector A normalized incoming direction.
		 * @param aNormal A normal about which the vector should be reflected.
		 * @return A vector containing the reflected direction.
		 */
		static constexpr Vector3 Reflect(const Vector3& aVector, const Vector3& aNormal);

		/**
		 * @brief Smoothly interpolate two vectors using cubic interpolation.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector in the interpolation.
		 * @return A vector containing the cubic interpolation result.
		 */
		static constexpr Vector3 SmoothStep(const Vector3& aValue1, const Vector3& aValue2, const T& anAmount);

		/**
		 * @brief Create a 1x3 column-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		inline constexpr Matrix<1, 3, T> ToColumnMatrix() const { return Matrix<1, 3, T>({ X, Y, Z }); }

		/**
		 * @brief Create a 3x1 row-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		inline constexpr Matrix<3, 1, T> ToRowMatrix() const { return Matrix<3, 1, T>({ X, Y, Z }); }

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		inline explicit constexpr operator Vector2<T>() const { return Vector2<T>(X, Y); }

		inline constexpr Vector3 operator-() const { return Vector3(-X, -Y, -Z); }

		inline constexpr Vector3 operator+(const Vector3& aVector) const { return Vector3(X + aVector.X, Y + aVector.Y, Z + aVector.Z); }
		inline constexpr Vector3 operator-(const Vector3& aVector) const { return Vector3(X - aVector.X, Y - aVector.Y, Z - aVector.Z); }
		inline constexpr Vector3 operator*(const Vector3& aVector) const { return Vector3(X * aVector.X, Y * aVector.Y, Z * aVector.Z); }
		inline constexpr Vector3 operator/(const Vector3& aVector) const { return Vector3(X / aVector.X, Y / aVector.Y, Z / aVector.Z); }

		inline constexpr Vector3 operator*(const Matrix<3, 3, T>& aMatrix) const { return Vector3(ToRowMatrix() * aMatrix); }

		inline void operator+=(const Vector3& aVector) { X += aVector.X; Y += aVector.Y; Z += aVector.Z; }
		inline void operator-=(const Vector3& aVector) { X -= aVector.X; Y -= aVector.Y; Z -= aVector.Z; }
		inline void operator*=(const Vector3& aVector) { X *= aVector.X; Y *= aVector.Y; Z *= aVector.Z; }
		inline void operator/=(const Vector3& aVector) { X /= aVector.X; Y /= aVector.Y; Z /= aVector.Z; }

		inline void operator*=(const Matrix<3, 3, T>& aMatrix) { (*this) = Vector3(ToRowMatrix() * aMatrix); }

		inline constexpr Vector3 operator*(const T& aScalar) const { return Vector3(X * aScalar, Y * aScalar, Z * aScalar); }
		inline constexpr Vector3 operator/(const T& aScalar) const { return Vector3(X / aScalar, Y / aScalar, Z / aScalar); }
		inline void operator*=(const T& aScalar) { X *= aScalar; Y *= aScalar; Z *= aScalar; }
		inline void operator/=(const T& aScalar) { X /= aScalar; Y /= aScalar; Z /= aScalar; }

		inline constexpr bool operator==(const Vector3& aVector) const { return ROSECOMMON_MATH_NAMESPACE::Equals(X, aVector.X) && ROSECOMMON_MATH_NAMESPACE::Equals(Y, aVector.Y) && ROSECOMMON_MATH_NAMESPACE::Equals(Z, aVector.Z); }
		inline constexpr bool operator!=(const Vector3& aVector) const { return !operator==(aVector); }

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

		#pragma endregion
	};

	/**
	 * @brief A mathematical vector with four components.
	 * @tparam T A type used for each component.
	 */
	template <typename T>
	class Vector4
	{
	public:

		//--------------------------------------------------
		// * Types
		//--------------------------------------------------
		#pragma region Types

		using ComponentType = T;

		#pragma endregion

		//--------------------------------------------------
		// * Static constants
		//--------------------------------------------------
		#pragma region Static constants

		/**
		  * @brief Create a vector with all of its components set to one.
		  */
		static constexpr Vector4 One() { return { 1, 1, 1, 1 }; }

		/**
		  * @brief Create a unit-vector for the X-axis.
		  */
		static constexpr Vector4 UnitX() { return { 1, 0, 0, 0 }; }

		/**
		  * @brief Create a unit-vector for the Y-axis.
		  */
		static constexpr Vector4 UnitY() { return { 0, 1, 0, 0 }; }

		/**
		  * @brief Create a unit-vector for the Z-axis.
		  */
		static constexpr Vector4 UnitZ() { return { 0, 0, 1, 0 }; }

		/**
		  * @brief Create a unit-vector for the W-axis.
		  */
		static constexpr Vector4 UnitW() { return { 0, 0, 0, 1 }; }

		/**
		  * @brief Create a vector with all of its components set to zero.
		  */
		static constexpr Vector4 Zero() { return { 0, 0, 0, 0 }; }

		#pragma endregion

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize the components to be zero.
		 */
		constexpr Vector4();

		/**
		 * @brief Initialize the components to the specified value.
		 * @param aValue The value all components should have.
		 */
		explicit constexpr Vector4(const T& aValue);

		/**
		 * @brief Initialize each component to the specified value.
		 * @param anX Value of the X component.
		 * @param aY Value of the Y component.
		 * @param aZ Value of the Z component.
		 * @param aW Value of the W component.
		 */
		constexpr Vector4(const T& anX, const T& aY, const T& aZ, const T& aW);

		/**
		 * @brief Initialize the components with values from another type of vector.
		 * @tparam U The source vector component type.
		 * @param aVector A vector to convert the values from.
		 */
		template <typename U = T>
		explicit constexpr Vector4(const Vector4<U>& aVector);

		/**
		 * @brief Initialize the components from a Vector2, a Z value and a W value.
		 * @param aVector A vector containing the values for X and Y components.
		 * @param aZ A value for the Z component.
		 * @param aW A value for the W component.
		 */
		explicit constexpr Vector4(const Vector2<T>& aVector, const T& aZ = 0, const T& aW = 1);

		/**
		 * @brief Initialize the components from a Vector3, and a W value.
		 * @param aVector A vector containing the values for X, Y and Z components.
		 * @param aW A value for the W component.
		 */
		explicit constexpr Vector4(const Vector3<T>& aVector, const T& aW = 1);

		/**
		 * @brief Initialize the components with the values from a 1x4 matrix.
		 * @param aColumnMatrix A column matrix to initialize with.
		 */
		explicit constexpr Vector4(const Matrix<1, 4, T>& aColumnMatrix);

		/**
		 * @brief Initialize the components with the values from a 4x1 matrix.
		 * @param aRowMatrix A row matrix to initialize with.
		 */
		explicit constexpr Vector4(const Matrix<4, 1, T>& aRowMatrix);

		#pragma endregion

		//--------------------------------------------------
		// * Properties
		//--------------------------------------------------
		#pragma region Properties

		/**
		 * @brief The X-component of the vector.
		 */
		T X;

		/**
		 * @brief The Y-component of the vector.
		 */
		T Y;

		/**
		 * @brief The Z-component of the vector.
		 */
		T Z;

		/**
		 * @brief The W-component of the vector.
		 */
		T W;

		#pragma endregion

		//--------------------------------------------------
		// * Methods
		//--------------------------------------------------
		#pragma region Methods

		/**
		 * @brief Restrict a value to be within the specified range.
		 * @param aValue The vector to clamp.
		 * @param aMinimum The minimum clamp value.
		 * @param aMaximum The maximum clamp value.
		 * @return The clamped vector.
		 */
		static constexpr Vector4 Clamp(const Vector4& aVector, const Vector4& aMinimum, const Vector4& aMaximum);

		/**
		 * @brief Assuming the vector defines the size of a fourth-dimensional box, calculate its volume.
		 * @return The volume of the box.
		 */
		inline constexpr T Content() const;

		/**
		 * @brief Calculate the distance between two points.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The distance between the points.
		 */
		static constexpr T Distance(const Vector4& aValue1, const Vector4& aValue2);

		/**
		 * @brief Calculate the distance between two points squared.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The squared distance between the points.
		 */
		static constexpr T DistanceSquared(const Vector4& aValue1, const Vector4& aValue2);

		/**
		 * @brief Calculate the dot product of the two vectors. If the two vectors are unit vectors,
		 * 	      the dot product returns a floating point value between - 1 and 1 that can be used to
		 * 	      determine some properties of the angle between two vectors. For example, it can show
		 * 	      whether the vectors are orthogonal, parallel, or have an acute or obtuse angle between them.
		 * @param aValue1 The first vector.
		 * @param aValue2 The second vector.
		 * @return The dot product of the two vectors.
		 */
		static constexpr T Dot(const Vector4& aValue1, const Vector4& aValue2);

		/**
		 * @brief Calculate the vector length.
		 * @return The length of the vector.
		 */
		constexpr T Length() const;

		/**
		 * @brief Calculate the vector squared length.
		 * @return The squared length of the vector.
		 */
		constexpr T LengthSquared() const;

		/**
		 * @brief Linearly interpolate between two vectors.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector.
		 * @return A vector containing the linear interpolation result.
		 */
		static constexpr Vector4 Lerp(const Vector4& aValue1, const Vector4& aValue2, const T& anAmount);

		/**
		 * @brief Get the largest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the highest value from each matching pair of components.
		 */
		static constexpr Vector4 Max(const Vector4& aValue1, const Vector4& aValue2);

		/**
		 * @brief Get the smallest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the lowest value from each matching pair of components.
		 */
		static constexpr Vector4 Min(const Vector4& aValue1, const Vector4& aValue2);

		/**
		 * @brief Create a unit vector from the specified vector with the same direction as the original vector.
		 * @return The unit vector.
		 */
		inline constexpr Vector4 Normalized() const { return (*this) / Length(); }

		/**
		 * @brief Modify the vector into a unit vector with the same direction as the original vector.
		 */
		inline void Normalize() { (*this) /= Length(); }

		/**
		 * @brief Smoothly interpolate two vectors using cubic interpolation.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector in the interpolation.
		 * @return A vector containing the cubic interpolation result.
		 */
		static constexpr Vector4 SmoothStep(const Vector4& aValue1, const Vector4& aValue2, const T& anAmount);

		/**
		 * @brief Create a 1x4 column-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		constexpr Matrix<1, 4, T> ToColumnMatrix() const { return Matrix<1, 4, T>({ X, Y, Z, W }); }

		/**
		 * @brief Create a 4x1 row-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		constexpr Matrix<4, 1, T> ToRowMatrix() const { return Matrix<4, 1, T>({ X, Y, Z, W }); }

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		inline explicit constexpr operator Vector2<T>() const { return Vector2<T>(X, Y); }
		inline explicit constexpr operator Vector3<T>() const { return Vector3<T>(X, Y, Z); }

		inline constexpr Vector4 operator-() const { return Vector4(-X, -Y, -Z, -W); }

		inline constexpr Vector4 operator+(const Vector4& aVector) const { return Vector4(X + aVector.X, Y + aVector.Y, Z + aVector.Z, W + aVector.W); }
		inline constexpr Vector4 operator-(const Vector4& aVector) const { return Vector4(X - aVector.X, Y - aVector.Y, Z - aVector.Z, W - aVector.W); }
		inline constexpr Vector4 operator*(const Vector4& aVector) const { return Vector4(X * aVector.X, Y * aVector.Y, Z * aVector.Z, W * aVector.W); }
		inline constexpr Vector4 operator/(const Vector4& aVector) const { return Vector4(X / aVector.X, Y / aVector.Y, Z / aVector.Z, W / aVector.W); }

		inline constexpr Vector4 operator*(const Matrix<4, 4, T>& aMatrix) const { return Vector4(ToRowMatrix() * aMatrix); }

		inline void operator+=(const Vector4& aVector) { X += aVector.X; Y += aVector.Y; Z += aVector.Z; W += aVector.W; }
		inline void operator-=(const Vector4& aVector) { X -= aVector.X; Y -= aVector.Y; Z -= aVector.Z; W -= aVector.W; }
		inline void operator*=(const Vector4& aVector) { X *= aVector.X; Y *= aVector.Y; Z *= aVector.Z; W *= aVector.W; }
		inline void operator/=(const Vector4& aVector) { X /= aVector.X; Y /= aVector.Y; Z /= aVector.Z; W /= aVector.W; }

		inline void operator*=(const Matrix<4, 4, T>& aMatrix) { (*this) = Vector4(ToRowMatrix() * aMatrix); }

		inline constexpr Vector4 operator*(const T& aScalar) const { return Vector4(X * aScalar, Y * aScalar, Z * aScalar, W * aScalar); }
		inline constexpr Vector4 operator/(const T& aScalar) const { return Vector4(X / aScalar, Y / aScalar, Z / aScalar, W / aScalar); }
		inline void operator*=(const T& aScalar) { X *= aScalar; Y *= aScalar; Z *= aScalar; W *= aScalar; }
		inline void operator/=(const T& aScalar) { X /= aScalar; Y /= aScalar; Z /= aScalar; W /= aScalar; }

		inline constexpr bool operator==(const Vector4& aVector) const { return ROSECOMMON_MATH_NAMESPACE::Equals(X, aVector.X) && ROSECOMMON_MATH_NAMESPACE::Equals(Y, aVector.Y) && ROSECOMMON_MATH_NAMESPACE::Equals(Z, aVector.Z) && ROSECOMMON_MATH_NAMESPACE::Equals(W, aVector.W); }
		inline constexpr bool operator!=(const Vector4& aVector) const { return !operator==(aVector); }

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

		#pragma endregion
	};
}

namespace ROSECOMMON_MATH_NAMESPACE
{
	#pragma region Vector2 implementation

	template <typename T>
	constexpr Vector2<T>::Vector2()
		: Vector2(0, 0)
	{

	}

	template <typename T>
	constexpr Vector2<T>::Vector2(const T& aValue)
		: Vector2(aValue, aValue)
	{

	}

	template <typename T>
	constexpr Vector2<T>::Vector2(const T& anX, const T& aY)
		: X(anX)
		, Y(aY)
	{

	}

	template <typename T>
	template <typename U>
	constexpr Vector2<T>::Vector2(const Vector2<U>& aVector)
		: X(static_cast<T>(aVector.X))
		, Y(static_cast<T>(aVector.Y))
	{

	}

	template <typename T>
	constexpr Vector2<T>::Vector2(const Matrix<1, 2, T>& aColumnMatrix)
		: X(aColumnMatrix.GetCell(0, 0))
		, Y(aColumnMatrix.GetCell(0, 1))
	{

	}

	template <typename T>
	constexpr Vector2<T>::Vector2(const Matrix<2, 1, T>& aRowMatrix)
		: X(aRowMatrix.GetCell(0, 0))
		, Y(aRowMatrix.GetCell(1, 0))
	{

	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Clamp(const Vector2& aValue, const Vector2& aMinimum, const Vector2& aMaximum)
	{
		return Vector2(
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aValue.X, aMinimum.X, aMaximum.X),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aValue.Y, aMinimum.Y, aMaximum.Y)
		);
	}

	template <typename T>
	constexpr T Vector2<T>::Content() const
	{
		return X * Y;
	}

	template <typename T>
	constexpr T Vector2<T>::Distance(const Vector2& aValue1, const Vector2& aValue2)
	{
		return (aValue1 - aValue2).Length();
	}

	template <typename T>
	constexpr T Vector2<T>::DistanceSquared(const Vector2& aValue1, const Vector2& aValue2)
	{
		return (aValue1 - aValue2).LengthSquared();
	}

	template <typename T>
	constexpr T Vector2<T>::Dot(const Vector2& aValue1, const Vector2& aValue2)
	{
		return (aValue1.X * aValue2.X) + (aValue1.Y * aValue2.Y);
	}

	template <typename T>
	constexpr T Vector2<T>::Length() const
	{
		return ROSECOMMON_MATH_NAMESPACE::Squareroot(LengthSquared());
	}

	template <typename T>
	constexpr T Vector2<T>::LengthSquared() const
	{
		return (X * X) + (Y * Y);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Lerp(const Vector2& aValue1, const Vector2& aValue2, const T& anAmount)
	{
		return (aValue1 + ((aValue2 - aValue1) * anAmount));
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Max(const Vector2& aValue1, const Vector2& aValue2)
	{
		return Vector2(
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Y, aValue2.Y)
		);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Min(const Vector2& aValue1, const Vector2& aValue2)
	{
		return Vector2(
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Y, aValue2.Y)
		);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Reflect(const Vector2& aVector, const Vector2& aNormal)
	{
		const T dotProduct = Dot(aVector, aNormal);

		return Vector2(
			aVector.X - (2.0f * aNormal.X) * dotProduct,
			aVector.Y - (2.0f * aNormal.Y) * dotProduct
		);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::SmoothStep(const Vector2& aValue1, const Vector2& aValue2, const T& anAmount)
	{
		return Vector2(
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.X, aValue2.X, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Y, aValue2.Y, anAmount)
		);
	}

	#pragma endregion

	#pragma region Vector3 implementation

	template <typename T>
	constexpr Vector3<T>::Vector3()
		: Vector3(0, 0, 0)
	{

	}

	template <typename T>
	constexpr Vector3<T>::Vector3(const T& aValue)
		: Vector3(aValue, aValue, aValue)
	{

	}

	template <typename T>
	constexpr Vector3<T>::Vector3(const T& anX, const T& aY, const T& aZ)
		: X(anX)
		, Y(aY)
		, Z(aZ)
	{

	}

	template <typename T>
	template <typename U>
	constexpr Vector3<T>::Vector3(const Vector3<U>& aVector)
		: X(static_cast<T>(aVector.X))
		, Y(static_cast<T>(aVector.Y))
		, Z(static_cast<T>(aVector.Z))
	{

	}

	template <typename T>
	constexpr Vector3<T>::Vector3(const Vector2<T>& aVector, const T& aZ)
		: Vector3(aVector.X, aVector.Y, aZ)
	{

	}

	template <typename T>
	constexpr Vector3<T>::Vector3(const Matrix<1, 3, T>& aColumnMatrix)
		: X(aColumnMatrix.GetCell(0, 0))
		, Y(aColumnMatrix.GetCell(0, 1))
		, Z(aColumnMatrix.GetCell(0, 2))
	{

	}

	template <typename T>
	constexpr Vector3<T>::Vector3(const Matrix<3, 1, T>& aRowMatrix)
		: X(aRowMatrix.GetCell(0, 0))
		, Y(aRowMatrix.GetCell(1, 0))
		, Z(aRowMatrix.GetCell(2, 0))
	{

	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Clamp(const Vector3& aVector, const Vector3& aMinimum, const Vector3& aMaximum)
	{
		return Vector3(
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.X, aMinimum.X, aMaximum.X),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.Y, aMinimum.Y, aMaximum.Y),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.Z, aMinimum.Z, aMaximum.Z)
		);
	}

	template <typename T>
	inline constexpr T Vector3<T>::Content() const
	{
		return X * Y * Z;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Cross(const Vector3& aValue1, const Vector3& aValue2)
	{
		return Vector3(
			aValue1.Y * aValue2.Z - aValue1.Z * aValue2.Y,
			aValue1.Z * aValue2.X - aValue1.X * aValue2.Z,
			aValue1.X * aValue2.Y - aValue1.Y * aValue2.X
		);
	}

	template <typename T>
	constexpr T Vector3<T>::Distance(const Vector3& aValue1, const Vector3& aValue2)
	{
		return (aValue1 - aValue2).Length();
	}

	template <typename T>
	constexpr T Vector3<T>::DistanceSquared(const Vector3& aValue1, const Vector3& aValue2)
	{
		return (aValue1 - aValue2).LengthSquared();
	}

	template <typename T>
	constexpr T Vector3<T>::Dot(const Vector3& aValue1, const Vector3& aValue2)
	{
		return
			(aValue1.X * aValue2.X) +
			(aValue1.Y * aValue2.Y) +
			(aValue1.Z * aValue2.Z);
	}

	template <typename T>
	constexpr T Vector3<T>::Length() const
	{
		return ROSECOMMON_MATH_NAMESPACE::Squareroot(LengthSquared());
	}

	template <typename T>
	constexpr T Vector3<T>::LengthSquared() const
	{
		return (X * X) + (Y * Y) + (Z * Z);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Lerp(const Vector3& aValue1, const Vector3& aValue2, const T& anAmount)
	{
		return (aValue1 + ((aValue2 - aValue1) * anAmount));
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Slerp(const Vector3& aValue1, const Vector3& aValue2, const T& anAmount)
	{
		if (aValue1 == aValue2)
			return aValue1;

		const T dot = ROSECOMMON_MATH_NAMESPACE::Clamp(Dot(aValue1, aValue2), -1.f, 1.f);
		const T theta = ROSECOMMON_MATH_NAMESPACE::ArcCosine(dot) * anAmount;
		Vector3 relativeVector = aValue2 - (aValue1 * dot);
		relativeVector.Normalize();
		return ((aValue1 * ROSECOMMON_MATH_NAMESPACE::Cosine(theta)) + (relativeVector * ROSECOMMON_MATH_NAMESPACE::Sine(theta)));
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Max(const Vector3& aValue1, const Vector3& aValue2)
	{
		return Vector3(
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Y, aValue2.Y),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Z, aValue2.Z)
		);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Min(const Vector3& aValue1, const Vector3& aValue2)
	{
		return Vector3(
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Y, aValue2.Y),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Z, aValue2.Z)
		);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Reflect(const Vector3& aVector, const Vector3& aNormal)
	{
		Vector3 result;
		const T dotProduct = Dot(aVector, aNormal);
		result.X = aVector.X - (2.0f * aNormal.X) * dotProduct;
		result.Y = aVector.Y - (2.0f * aNormal.Y) * dotProduct;
		result.Z = aVector.Z - (2.0f * aNormal.Z) * dotProduct;
		return result;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::SmoothStep(const Vector3& aValue1, const Vector3& aValue2, const T& anAmount)
	{
		return Vector3(
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.X, aValue2.X, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Y, aValue2.Y, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Z, aValue2.Z, anAmount)
		);
	}

	#pragma endregion

	#pragma region Vector4 implementation

	template <typename T>
	constexpr Vector4<T>::Vector4()
		: Vector4(0, 0, 0, 0)
	{

	}

	template <typename T>
	constexpr Vector4<T>::Vector4(const T& aValue)
		: Vector4(aValue, aValue, aValue, aValue)
	{

	}

	template <typename T>
	constexpr Vector4<T>::Vector4(const T& anX, const T& aY, const T& aZ, const T& aW)
		: X(anX)
		, Y(aY)
		, Z(aZ)
		, W(aW)
	{

	}

	template <typename T>
	template <typename U>
	constexpr Vector4<T>::Vector4(const Vector4<U>& aVector)
		: X(static_cast<T>(aVector.X))
		, Y(static_cast<T>(aVector.Y))
		, Z(static_cast<T>(aVector.Z))
		, W(static_cast<T>(aVector.W))
	{

	}

	template <typename T>
	constexpr Vector4<T>::Vector4(const Vector2<T>& aVector, const T& aZ, const T& aW)
		: Vector4(aVector.X, aVector.Y, aZ, aW)
	{

	}

	template <typename T>
	constexpr Vector4<T>::Vector4(const Vector3<T>& aVector, const T& aW)
		: Vector4(aVector.X, aVector.Y, aVector.Z, aW)
	{

	}

	template <typename T>
	constexpr Vector4<T>::Vector4(const Matrix<1, 4, T>& aColumnMatrix)
		: X(aColumnMatrix.GetCell(0, 0))
		, Y(aColumnMatrix.GetCell(0, 1))
		, Z(aColumnMatrix.GetCell(0, 2))
		, W(aColumnMatrix.GetCell(0, 3))
	{

	}

	template <typename T>
	constexpr Vector4<T>::Vector4(const Matrix<4, 1, T>& aRowMatrix)
		: X(aRowMatrix.GetCell(0, 0))
		, Y(aRowMatrix.GetCell(1, 0))
		, Z(aRowMatrix.GetCell(2, 0))
		, W(aRowMatrix.GetCell(3, 0))
	{

	}

	template <typename T>
	constexpr Vector4<T> Vector4<T>::Clamp(const Vector4& aVector, const Vector4& aMinimum, const Vector4& aMaximum)
	{
		return Vector4(
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.X, aMinimum.X, aMaximum.X),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.Y, aMinimum.Y, aMaximum.Y),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.Z, aMinimum.Z, aMaximum.Z),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.W, aMinimum.W, aMaximum.W)
		);
	}

	template <typename T>
	constexpr T Vector4<T>::Content() const
	{
		return X * Y * Z * W;
	}

	template <typename T>
	constexpr T Vector4<T>::Distance(const Vector4& aValue1, const Vector4& aValue2)
	{
		return (aValue1 - aValue2).Length();
	}

	template <typename T>
	constexpr T Vector4<T>::DistanceSquared(const Vector4& aValue1, const Vector4& aValue2)
	{
		return (aValue1 - aValue2).LengthSquared();
	}

	template <typename T>
	constexpr T Vector4<T>::Dot(const Vector4& aValue1, const Vector4& aValue2)
	{
		return
			(aValue1.X * aValue2.X) +
			(aValue1.Y * aValue2.Y) +
			(aValue1.Z * aValue2.Z) +
			(aValue1.W * aValue2.W);
	}

	template <typename T>
	constexpr T Vector4<T>::Length() const
	{
		return ROSECOMMON_MATH_NAMESPACE::Squareroot(LengthSquared());
	}

	template <typename T>
	constexpr T Vector4<T>::LengthSquared() const
	{
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	template <typename T>
	constexpr Vector4<T> Vector4<T>::Lerp(const Vector4& aValue1, const Vector4& aValue2, const T& anAmount)
	{
		return (aValue1 + ((aValue2 - aValue1) * anAmount));
	}

	template <typename T>
	constexpr Vector4<T> Vector4<T>::Max(const Vector4& aValue1, const Vector4& aValue2)
	{
		return Vector4(
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Y, aValue2.Y),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Z, aValue2.Z),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.W, aValue2.W)
		);
	}

	template <typename T>
	constexpr Vector4<T> Vector4<T>::Min(const Vector4& aValue1, const Vector4& aValue2)
	{
		return Vector4(
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Y, aValue2.Y),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Z, aValue2.Z),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.W, aValue2.W)
		);
	}

	template <typename T>
	constexpr Vector4<T> Vector4<T>::SmoothStep(const Vector4& aValue1, const Vector4& aValue2, const T& anAmount)
	{
		return Vector4(
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.X, aValue2.X, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Y, aValue2.Y, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Z, aValue2.Z, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.W, aValue2.W, anAmount)
		);
	}

	#pragma endregion

	template <int N, typename T> struct Vector_T;
	template <typename T> struct Vector_T<2, T> { using type = Vector2<T>; };
	template <typename T> struct Vector_T<3, T> { using type = Vector3<T>; };
	template <typename T> struct Vector_T<4, T> { using type = Vector4<T>; };

	template <int N, typename T>
	using VectorN = typename Vector_T<N, T>::type;
}
