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
	class Vector2T
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
		inline static constexpr Vector2T One() { return { 1, 1 }; }

		/**
		 * @brief Create a unit-vector for the X-axis.
		 */
		inline static constexpr Vector2T UnitX() { return { 1, 0 }; }

		/**
		 * @brief Create a unit vector for the Y-axis.
		 */
		inline static constexpr Vector2T UnitY() { return { 0, 1 }; }

		/**
		 * @brief Create a vector with both of its components set to zero.
		 */
		inline static constexpr Vector2T Zero() { return { 0, 0 }; }

		#pragma endregion

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize both components to be zero.
		 */
		constexpr Vector2T();

		/**
		 * @brief Initialize both components to the specified value.
		 * @param aValue The value both components should have.
		 */
		constexpr Vector2T(const T& aValue);

		/**
		 * @brief Initialize each component to the specified value.
		 * @param anX Value of the X component.
		 * @param aY Value of the Y component.
		 */
		constexpr Vector2T(const T& anX, const T& aY);

		/**
		 * @brief Initialize the components with values from another type of vector.
		 * @tparam U The source vector component type.
		 * @param aVector A vector to convert the values from.
		 */
		template <typename U = T>
		explicit constexpr Vector2T(const Vector2T<U>& aVector);

		/**
		 * @brief Initialize the components with the values from a 1x2 matrix.
		 * @param aColumnMatrix A column matrix to initialize with.
		 */
		explicit constexpr Vector2T(const MatrixT<1, 2, T>& aColumnMatrix);

		/**
		 * @brief Initialize the components with the values from a 2x1 matrix.
		 * @param aRowMatrix A row matrix to initialize with.
		 */
		explicit constexpr Vector2T(const MatrixT<2, 1, T>& aRowMatrix);

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
		static constexpr Vector2T Clamp(const Vector2T& aValue, const Vector2T& aMinimum, const Vector2T& aMaximum);

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
		static constexpr T Distance(const Vector2T& aValue1, const Vector2T& aValue2);

		/**
		 * @brief Calculate the distance between two points squared.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The squared distance between the points.
		 */
		static constexpr T DistanceSquared(const Vector2T& aValue1, const Vector2T& aValue2);

		/**
		 * @brief Calculate the dot product of the two vectors. If the two vectors are unit vectors,
		 * 	      the dot product returns a floating point value between - 1 and 1 that can be used to
		 * 	      determine some properties of the angle between two vectors. For example, it can show
		 * 	      whether the vectors are orthogonal, parallel, or have an acute or obtuse angle between them.
		 * @param aValue1 The first vector.
		 * @param aValue2 The second vector.
		 * @return The dot product of the two vectors.
		 */
		static constexpr T Dot(const Vector2T& aValue1, const Vector2T& aValue2);

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
		static constexpr Vector2T Lerp(const Vector2T& aValue1, const Vector2T& aValue2, const T& anAmount);

		/**
		 * @brief Get the largest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the highest value from each matching pair of components.
		 */
		static constexpr Vector2T Max(const Vector2T& aValue1, const Vector2T& aValue2);

		/**
		 * @brief Get the smallest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the lowest value from each matching pair of components.
		 */
		static constexpr Vector2T Min(const Vector2T& aValue1, const Vector2T& aValue2);

		/**
		 * @brief Create a unit vector from the specified vector with the same direction as the original vector.
		 * @return The unit vector.
		 */
		inline constexpr Vector2T Normalized() const { return (*this) / Length(); }

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
		static constexpr Vector2T Reflect(const Vector2T& aVector, const Vector2T& aNormal);

		/**
		 * @brief Smoothly interpolate two vectors using cubic interpolation.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector in the interpolation.
		 * @return A vector containing the cubic interpolation result.
		 */
		static constexpr Vector2T SmoothStep(const Vector2T& aValue1, const Vector2T& aValue2, const T& anAmount);

		/**
		 * @brief Create a 1x2 column-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		inline constexpr MatrixT<1, 2, T> ToColumnMatrix() const { return MatrixT<1, 2, T>({ X, Y }); }

		/**
		 * @brief Create a 2x1 row-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		inline constexpr MatrixT<2, 1, T> ToRowMatrix() const { return MatrixT<2, 1, T>({ X, Y }); }

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		inline constexpr Vector2T operator-() const { return Vector2T(-X, -Y); }

		inline constexpr Vector2T operator+(const Vector2T& aVector) const { return Vector2T(X + aVector.X, Y + aVector.Y); }
		inline constexpr Vector2T operator-(const Vector2T& aVector) const { return Vector2T(X - aVector.X, Y - aVector.Y); }
		inline constexpr Vector2T operator*(const Vector2T& aVector) const { return Vector2T(X * aVector.X, Y * aVector.Y); }
		inline constexpr Vector2T operator/(const Vector2T& aVector) const { return Vector2T(X / aVector.X, Y / aVector.Y); }

		inline constexpr Vector2T operator*(const MatrixT<2, 2, T>& aMatrix) const { return Vector2T(ToRowMatrix() * aMatrix); }

		inline void operator+=(const Vector2T& aVector) { X += aVector.X; Y += aVector.Y; }
		inline void operator-=(const Vector2T& aVector) { X -= aVector.X; Y -= aVector.Y; }
		inline void operator*=(const Vector2T& aVector) { X *= aVector.X; Y *= aVector.Y; }
		inline void operator/=(const Vector2T& aVector) { X /= aVector.X; Y /= aVector.Y; }

		inline void operator*=(const MatrixT<2, 2, T>& aMatrix) { (*this) = Vector2T(ToRowMatrix() * aMatrix); }

		inline constexpr bool operator==(const Vector2T& aVector) const { return ROSECOMMON_MATH_NAMESPACE::Equals(X, aVector.X) && ROSECOMMON_MATH_NAMESPACE::Equals(Y, aVector.Y); }
		inline constexpr bool operator!=(const Vector2T& aVector) const { return !operator==(aVector); }

		template <typename U = T>
		constexpr std::strong_ordering operator<=>(const Vector2T<U>& aVector) const
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
	class Vector3T
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
		inline static constexpr Vector3T Backward() { return -UnitZ(); }

		/**
		 * @brief Create a unit-vector designating down.
		 */
		inline static constexpr Vector3T Down() { return -UnitY(); }

		/**
		  * @brief Create a unit-vector designating forward in a left-handed coordinate system.
		  */
		inline static constexpr Vector3T Forward() { return UnitZ(); }

		/**
		  * @brief Create a unit-vector designating left in a left-handed coordinate system.
		  */
		inline static constexpr Vector3T Left() { return -UnitX(); }

		/**
		  * @brief Create a vector with all of its components set to one.
		  */
		inline static constexpr Vector3T One() { return { 1, 1, 1 }; }

		/**
		  * @brief Create a unit-vector designating right in a left-handed coordinate system.
		  */
		inline static constexpr Vector3T Right() { return UnitX(); }

		/**
		  * @brief Create a unit-vector for the X-axis.
		  */
		inline static constexpr Vector3T UnitX() { return { 1, 0, 0 }; }

		/**
		  * @brief Create a unit-vector for the Y-axis.
		  */
		inline static constexpr Vector3T UnitY() { return { 0, 1, 0 }; }

		/**
		  * @brief Create a unit-vector for the Z-axis.
		  */
		inline static constexpr Vector3T UnitZ() { return { 0, 0, 1 }; }

		/**
		  * @brief Create a unit-vector designating up.
		  */
		inline static constexpr Vector3T Up() { return UnitY(); }

		/**
		  * @brief Create a vector with all of its components set to zero.
		  */
		inline static constexpr Vector3T Zero() { return { 0, 0, 0 }; }

		#pragma endregion

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize the components to be zero.
		 */
		constexpr Vector3T();

		/**
		 * @brief Initialize the components to the specified value.
		 * @param aValue The value all components should have.
		 */
		constexpr Vector3T(const T& aValue);

		/**
		 * @brief Initialize each component to the specified value.
		 * @param anX Value of the X component.
		 * @param aY Value of the Y component.
		 * @param aZ Value of the Z component.
		 */
		constexpr Vector3T(const T& anX, const T& aY, const T& aZ);

		/**
		 * @brief Initialize the components with values from another type of vector.
		 * @tparam U The source vector component type.
		 * @param aVector A vector to convert the values from.
		 */
		template <typename U = T>
		explicit constexpr Vector3T(const Vector3T<U>& aVector);

		/**
		 * @brief Initialize the components from a Vector2T and a Z value.
		 * @param aVector A vector containing the values for X and Y components.
		 * @param aZ A value for the Z component.
		 */
		explicit constexpr Vector3T(const Vector2T<T>& aVector, const T& aZ = 0);

		/**
		 * @brief Initialize the components with the values from a 1x3 matrix.
		 * @param aColumnMatrix A column matrix to initialize with.
		 */
		explicit constexpr Vector3T(const MatrixT<1, 3, T>& aColumnMatrix);

		/**
		 * @brief Initialize the components with the values from a 3x1 matrix.
		 * @param aRowMatrix A row matrix to initialize with.
		 */
		explicit constexpr Vector3T(const MatrixT<3, 1, T>& aRowMatrix);

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
		static constexpr Vector3T Clamp(const Vector3T& aVector, const Vector3T& aMinimum, const Vector3T& aMaximum);

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
		static constexpr Vector3T Cross(const Vector3T& aValue1, const Vector3T& aValue2);

		/**
		 * @brief Calculate the distance between two points.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The distance between the points.
		 */
		static constexpr T Distance(const Vector3T& aValue1, const Vector3T& aValue2);

		/**
		 * @brief Calculate the distance between two points squared.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The squared distance between the points.
		 */
		static constexpr T DistanceSquared(const Vector3T& aValue1, const Vector3T& aValue2);

		/**
		 * @brief Calculate the dot product of the two vectors. If the two vectors are unit vectors,
		 * 	      the dot product returns a floating point value between - 1 and 1 that can be used to
		 * 	      determine some properties of the angle between two vectors. For example, it can show
		 * 	      whether the vectors are orthogonal, parallel, or have an acute or obtuse angle between them.
		 * @param aValue1 The first vector.
		 * @param aValue2 The second vector.
		 * @return The dot product of the two vectors.
		 */
		static constexpr T Dot(const Vector3T& aValue1, const Vector3T& aValue2);

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
		static constexpr Vector3T Lerp(const Vector3T& aValue1, const Vector3T& aValue2, const T& anAmount);

		/**
		 * @brief Spherically interpolate between two vectors.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector.
		 * @return The spherical interpolation of the two vectors.
		 */
		static constexpr Vector3T Slerp(const Vector3T& aValue1, const Vector3T& aValue2, const T& anAmount);

		/**
		 * @brief Get the largest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the highest value from each matching pair of components.
		 */
		static constexpr Vector3T Max(const Vector3T& aValue1, const Vector3T& aValue2);

		/**
		 * @brief Get the smallest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the lowest value from each matching pair of components.
		 */
		static constexpr Vector3T Min(const Vector3T& aValue1, const Vector3T& aValue2);

		/**
		 * @brief Create a unit vector from the specified vector with the same direction as the original vector.
		 * @return The unit vector.
		 */
		inline constexpr Vector3T Normalized() const { return (*this) / Length(); }

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
		static constexpr Vector3T Reflect(const Vector3T& aVector, const Vector3T& aNormal);

		/**
		 * @brief Smoothly interpolate two vectors using cubic interpolation.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @param anAmount Value between 0 and 1 indicating the weight of the second vector in the interpolation.
		 * @return A vector containing the cubic interpolation result.
		 */
		static constexpr Vector3T SmoothStep(const Vector3T& aValue1, const Vector3T& aValue2, const T& anAmount);

		/**
		 * @brief Create a 1x3 column-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		inline constexpr MatrixT<1, 3, T> ToColumnMatrix() const { return MatrixT<1, 3, T>({ X, Y, Z }); }

		/**
		 * @brief Create a 3x1 row-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		inline constexpr MatrixT<3, 1, T> ToRowMatrix() const { return MatrixT<3, 1, T>({ X, Y, Z }); }

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		inline explicit constexpr operator Vector2T<T>() const { return Vector2T<T>(X, Y); }

		inline constexpr Vector3T operator-() const { return Vector3T(-X, -Y, -Z); }

		inline constexpr Vector3T operator+(const Vector3T& aVector) const { return Vector3T(X + aVector.X, Y + aVector.Y, Z + aVector.Z); }
		inline constexpr Vector3T operator-(const Vector3T& aVector) const { return Vector3T(X - aVector.X, Y - aVector.Y, Z - aVector.Z); }
		inline constexpr Vector3T operator*(const Vector3T& aVector) const { return Vector3T(X * aVector.X, Y * aVector.Y, Z * aVector.Z); }
		inline constexpr Vector3T operator/(const Vector3T& aVector) const { return Vector3T(X / aVector.X, Y / aVector.Y, Z / aVector.Z); }

		inline constexpr Vector3T operator*(const MatrixT<3, 3, T>& aMatrix) const { return Vector3T(ToRowMatrix() * aMatrix); }

		inline void operator+=(const Vector3T& aVector) { X += aVector.X; Y += aVector.Y; Z += aVector.Z; }
		inline void operator-=(const Vector3T& aVector) { X -= aVector.X; Y -= aVector.Y; Z -= aVector.Z; }
		inline void operator*=(const Vector3T& aVector) { X *= aVector.X; Y *= aVector.Y; Z *= aVector.Z; }
		inline void operator/=(const Vector3T& aVector) { X /= aVector.X; Y /= aVector.Y; Z /= aVector.Z; }

		inline void operator*=(const MatrixT<3, 3, T>& aMatrix) { (*this) = Vector3T(ToRowMatrix() * aMatrix); }

		inline constexpr bool operator==(const Vector3T& aVector) const { return ROSECOMMON_MATH_NAMESPACE::Equals(X, aVector.X) && ROSECOMMON_MATH_NAMESPACE::Equals(Y, aVector.Y) && ROSECOMMON_MATH_NAMESPACE::Equals(Z, aVector.Z); }
		inline constexpr bool operator!=(const Vector3T& aVector) const { return !operator==(aVector); }

		constexpr std::strong_ordering operator<=>(const Vector3T& aVector) const
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
	class Vector4T
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
		static constexpr Vector4T One() { return { 1, 1, 1, 1 }; }

		/**
		  * @brief Create a unit-vector for the X-axis.
		  */
		static constexpr Vector4T UnitX() { return { 1, 0, 0, 0 }; }

		/**
		  * @brief Create a unit-vector for the Y-axis.
		  */
		static constexpr Vector4T UnitY() { return { 0, 1, 0, 0 }; }

		/**
		  * @brief Create a unit-vector for the Z-axis.
		  */
		static constexpr Vector4T UnitZ() { return { 0, 0, 1, 0 }; }

		/**
		  * @brief Create a unit-vector for the W-axis.
		  */
		static constexpr Vector4T UnitW() { return { 0, 0, 0, 1 }; }

		/**
		  * @brief Create a vector with all of its components set to zero.
		  */
		static constexpr Vector4T Zero() { return { 0, 0, 0, 0 }; }

		#pragma endregion

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize the components to be zero.
		 */
		constexpr Vector4T();

		/**
		 * @brief Initialize the components to the specified value.
		 * @param aValue The value all components should have.
		 */
		constexpr Vector4T(const T& aValue);

		/**
		 * @brief Initialize each component to the specified value.
		 * @param anX Value of the X component.
		 * @param aY Value of the Y component.
		 * @param aZ Value of the Z component.
		 * @param aW Value of the W component.
		 */
		constexpr Vector4T(const T& anX, const T& aY, const T& aZ, const T& aW);

		/**
		 * @brief Initialize the components with values from another type of vector.
		 * @tparam U The source vector component type.
		 * @param aVector A vector to convert the values from.
		 */
		template <typename U = T>
		explicit constexpr Vector4T(const Vector4T<U>& aVector);

		/**
		 * @brief Initialize the components from a Vector2T, a Z value and a W value.
		 * @param aVector A vector containing the values for X and Y components.
		 * @param aZ A value for the Z component.
		 * @param aW A value for the W component.
		 */
		explicit constexpr Vector4T(const Vector2T<T>& aVector, const T& aZ = 0, const T& aW = 1);

		/**
		 * @brief Initialize the components from a Vector3T, and a W value.
		 * @param aVector A vector containing the values for X, Y and Z components.
		 * @param aW A value for the W component.
		 */
		explicit constexpr Vector4T(const Vector3T<T>& aVector, const T& aW = 1);

		/**
		 * @brief Initialize the components with the values from a 1x4 matrix.
		 * @param aColumnMatrix A column matrix to initialize with.
		 */
		explicit constexpr Vector4T(const MatrixT<1, 4, T>& aColumnMatrix);

		/**
		 * @brief Initialize the components with the values from a 4x1 matrix.
		 * @param aRowMatrix A row matrix to initialize with.
		 */
		explicit constexpr Vector4T(const MatrixT<4, 1, T>& aRowMatrix);

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
		static constexpr Vector4T Clamp(const Vector4T& aVector, const Vector4T& aMinimum, const Vector4T& aMaximum);

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
		static constexpr T Distance(const Vector4T& aValue1, const Vector4T& aValue2);

		/**
		 * @brief Calculate the distance between two points squared.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return The squared distance between the points.
		 */
		static constexpr T DistanceSquared(const Vector4T& aValue1, const Vector4T& aValue2);

		/**
		 * @brief Calculate the dot product of the two vectors. If the two vectors are unit vectors,
		 * 	      the dot product returns a floating point value between - 1 and 1 that can be used to
		 * 	      determine some properties of the angle between two vectors. For example, it can show
		 * 	      whether the vectors are orthogonal, parallel, or have an acute or obtuse angle between them.
		 * @param aValue1 The first vector.
		 * @param aValue2 The second vector.
		 * @return The dot product of the two vectors.
		 */
		static constexpr T Dot(const Vector4T& aValue1, const Vector4T& aValue2);

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
		static constexpr Vector4T Lerp(const Vector4T& aValue1, const Vector4T& aValue2, const T& anAmount);

		/**
		 * @brief Get the largest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the highest value from each matching pair of components.
		 */
		static constexpr Vector4T Max(const Vector4T& aValue1, const Vector4T& aValue2);

		/**
		 * @brief Get the smallest values for each component.
		 * @param aValue1 Source vector.
		 * @param aValue2 Source vector.
		 * @return A vector that contains the lowest value from each matching pair of components.
		 */
		static constexpr Vector4T Min(const Vector4T& aValue1, const Vector4T& aValue2);

		/**
		 * @brief Create a unit vector from the specified vector with the same direction as the original vector.
		 * @return The unit vector.
		 */
		inline constexpr Vector4T Normalized() const { return (*this) / Length(); }

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
		static constexpr Vector4T SmoothStep(const Vector4T& aValue1, const Vector4T& aValue2, const T& anAmount);

		/**
		 * @brief Create a 1x4 column-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		constexpr MatrixT<1, 4, T> ToColumnMatrix() const { return MatrixT<1, 4, T>({ X, Y, Z, W }); }

		/**
		 * @brief Create a 4x1 row-matrix from the vector.
		 * @return A matrix with the same component values as the vector.
		 */
		constexpr MatrixT<4, 1, T> ToRowMatrix() const { return MatrixT<4, 1, T>({ X, Y, Z, W }); }

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		inline explicit constexpr operator Vector2T<T>() const { return Vector2T<T>(X, Y); }
		inline explicit constexpr operator Vector3T<T>() const { return Vector3T<T>(X, Y, Z); }

		inline constexpr Vector4T operator-() const { return Vector4T(-X, -Y, -Z, -W); }

		inline constexpr Vector4T operator+(const Vector4T& aVector) const { return Vector4T(X + aVector.X, Y + aVector.Y, Z + aVector.Z, W + aVector.W); }
		inline constexpr Vector4T operator-(const Vector4T& aVector) const { return Vector4T(X - aVector.X, Y - aVector.Y, Z - aVector.Z, W - aVector.W); }
		inline constexpr Vector4T operator*(const Vector4T& aVector) const { return Vector4T(X * aVector.X, Y * aVector.Y, Z * aVector.Z, W * aVector.W); }
		inline constexpr Vector4T operator/(const Vector4T& aVector) const { return Vector4T(X / aVector.X, Y / aVector.Y, Z / aVector.Z, W / aVector.W); }

		inline constexpr Vector4T operator*(const MatrixT<4, 4, T>& aMatrix) const { return Vector4T(ToRowMatrix() * aMatrix); }

		inline void operator+=(const Vector4T& aVector) { X += aVector.X; Y += aVector.Y; Z += aVector.Z; W += aVector.W; }
		inline void operator-=(const Vector4T& aVector) { X -= aVector.X; Y -= aVector.Y; Z -= aVector.Z; W -= aVector.W; }
		inline void operator*=(const Vector4T& aVector) { X *= aVector.X; Y *= aVector.Y; Z *= aVector.Z; W *= aVector.W; }
		inline void operator/=(const Vector4T& aVector) { X /= aVector.X; Y /= aVector.Y; Z /= aVector.Z; W /= aVector.W; }

		inline void operator*=(const MatrixT<4, 4, T>& aMatrix) { (*this) = Vector4T(ToRowMatrix() * aMatrix); }

		inline constexpr bool operator==(const Vector4T& aVector) const { return ROSECOMMON_MATH_NAMESPACE::Equals(X, aVector.X) && ROSECOMMON_MATH_NAMESPACE::Equals(Y, aVector.Y) && ROSECOMMON_MATH_NAMESPACE::Equals(Z, aVector.Z) && ROSECOMMON_MATH_NAMESPACE::Equals(W, aVector.W); }
		inline constexpr bool operator!=(const Vector4T& aVector) const { return !operator==(aVector); }

		constexpr std::strong_ordering operator<=>(const Vector4T& aVector) const
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
	#pragma region Vector2T implementation

	template <typename T>
	constexpr Vector2T<T>::Vector2T()
		: Vector2T(0, 0)
	{

	}

	template <typename T>
	constexpr Vector2T<T>::Vector2T(const T& aValue)
		: Vector2T(aValue, aValue)
	{

	}

	template <typename T>
	constexpr Vector2T<T>::Vector2T(const T& anX, const T& aY)
		: X(anX)
		, Y(aY)
	{

	}

	template <typename T>
	template <typename U>
	constexpr Vector2T<T>::Vector2T(const Vector2T<U>& aVector)
		: X(static_cast<T>(aVector.X))
		, Y(static_cast<T>(aVector.Y))
	{

	}

	template <typename T>
	constexpr Vector2T<T>::Vector2T(const MatrixT<1, 2, T>& aColumnMatrix)
		: X(aColumnMatrix.GetCell(0, 0))
		, Y(aColumnMatrix.GetCell(0, 1))
	{

	}

	template <typename T>
	constexpr Vector2T<T>::Vector2T(const MatrixT<2, 1, T>& aRowMatrix)
		: X(aRowMatrix.GetCell(0, 0))
		, Y(aRowMatrix.GetCell(1, 0))
	{

	}

	template <typename T>
	constexpr Vector2T<T> Vector2T<T>::Clamp(const Vector2T& aValue, const Vector2T& aMinimum, const Vector2T& aMaximum)
	{
		return Vector2T(
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aValue.X, aMinimum.X, aMaximum.X),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aValue.Y, aMinimum.Y, aMaximum.Y)
		);
	}

	template <typename T>
	constexpr T Vector2T<T>::Content() const
	{
		return X * Y;
	}

	template <typename T>
	constexpr T Vector2T<T>::Distance(const Vector2T& aValue1, const Vector2T& aValue2)
	{
		return (aValue1 - aValue2).Length();
	}

	template <typename T>
	constexpr T Vector2T<T>::DistanceSquared(const Vector2T& aValue1, const Vector2T& aValue2)
	{
		return (aValue1 - aValue2).LengthSquared();
	}

	template <typename T>
	constexpr T Vector2T<T>::Dot(const Vector2T& aValue1, const Vector2T& aValue2)
	{
		return (aValue1.X * aValue2.X) + (aValue1.Y * aValue2.Y);
	}

	template <typename T>
	constexpr T Vector2T<T>::Length() const
	{
		return ROSECOMMON_MATH_NAMESPACE::Squareroot(LengthSquared());
	}

	template <typename T>
	constexpr T Vector2T<T>::LengthSquared() const
	{
		return (X * X) + (Y * Y);
	}

	template <typename T>
	constexpr Vector2T<T> Vector2T<T>::Lerp(const Vector2T& aValue1, const Vector2T& aValue2, const T& anAmount)
	{
		return (aValue1 + ((aValue2 - aValue1) * anAmount));
	}

	template <typename T>
	constexpr Vector2T<T> Vector2T<T>::Max(const Vector2T& aValue1, const Vector2T& aValue2)
	{
		return Vector2T(
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Y, aValue2.Y)
		);
	}

	template <typename T>
	constexpr Vector2T<T> Vector2T<T>::Min(const Vector2T& aValue1, const Vector2T& aValue2)
	{
		return Vector2T(
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Y, aValue2.Y)
		);
	}

	template <typename T>
	constexpr Vector2T<T> Vector2T<T>::Reflect(const Vector2T& aVector, const Vector2T& aNormal)
	{
		const T dotProduct = Dot(aVector, aNormal);

		return Vector2T(
			aVector.X - (2.0f * aNormal.X) * dotProduct,
			aVector.Y - (2.0f * aNormal.Y) * dotProduct
		);
	}

	template <typename T>
	constexpr Vector2T<T> Vector2T<T>::SmoothStep(const Vector2T& aValue1, const Vector2T& aValue2, const T& anAmount)
	{
		return Vector2T(
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.X, aValue2.X, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Y, aValue2.Y, anAmount)
		);
	}

	#pragma endregion

	#pragma region Vector3T implementation

	template <typename T>
	constexpr Vector3T<T>::Vector3T()
		: Vector3T(0, 0, 0)
	{

	}

	template <typename T>
	constexpr Vector3T<T>::Vector3T(const T& aValue)
		: Vector3T(aValue, aValue, aValue)
	{

	}

	template <typename T>
	constexpr Vector3T<T>::Vector3T(const T& anX, const T& aY, const T& aZ)
		: X(anX)
		, Y(aY)
		, Z(aZ)
	{

	}

	template <typename T>
	template <typename U>
	constexpr Vector3T<T>::Vector3T(const Vector3T<U>& aVector)
		: X(static_cast<T>(aVector.X))
		, Y(static_cast<T>(aVector.Y))
		, Z(static_cast<T>(aVector.Z))
	{

	}

	template <typename T>
	constexpr Vector3T<T>::Vector3T(const Vector2T<T>& aVector, const T& aZ)
		: Vector3T(aVector.X, aVector.Y, aZ)
	{

	}

	template <typename T>
	constexpr Vector3T<T>::Vector3T(const MatrixT<1, 3, T>& aColumnMatrix)
		: X(aColumnMatrix.GetCell(0, 0))
		, Y(aColumnMatrix.GetCell(0, 1))
		, Z(aColumnMatrix.GetCell(0, 2))
	{

	}

	template <typename T>
	constexpr Vector3T<T>::Vector3T(const MatrixT<3, 1, T>& aRowMatrix)
		: X(aRowMatrix.GetCell(0, 0))
		, Y(aRowMatrix.GetCell(1, 0))
		, Z(aRowMatrix.GetCell(2, 0))
	{

	}

	template <typename T>
	constexpr Vector3T<T> Vector3T<T>::Clamp(const Vector3T& aVector, const Vector3T& aMinimum, const Vector3T& aMaximum)
	{
		return Vector3T(
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.X, aMinimum.X, aMaximum.X),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.Y, aMinimum.Y, aMaximum.Y),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.Z, aMinimum.Z, aMaximum.Z)
		);
	}

	template <typename T>
	inline constexpr T Vector3T<T>::Content() const
	{
		return X * Y * Z;
	}

	template <typename T>
	constexpr Vector3T<T> Vector3T<T>::Cross(const Vector3T& aValue1, const Vector3T& aValue2)
	{
		return Vector3T(
			aValue1.Y * aValue2.Z - aValue1.Z * aValue2.Y,
			aValue1.Z * aValue2.X - aValue1.X * aValue2.Z,
			aValue1.X * aValue2.Y - aValue1.Y * aValue2.X
		);
	}

	template <typename T>
	constexpr T Vector3T<T>::Distance(const Vector3T& aValue1, const Vector3T& aValue2)
	{
		return (aValue1 - aValue2).Length();
	}

	template <typename T>
	constexpr T Vector3T<T>::DistanceSquared(const Vector3T& aValue1, const Vector3T& aValue2)
	{
		return (aValue1 - aValue2).LengthSquared();
	}

	template <typename T>
	constexpr T Vector3T<T>::Dot(const Vector3T& aValue1, const Vector3T& aValue2)
	{
		return
			(aValue1.X * aValue2.X) +
			(aValue1.Y * aValue2.Y) +
			(aValue1.Z * aValue2.Z);
	}

	template <typename T>
	constexpr T Vector3T<T>::Length() const
	{
		return ROSECOMMON_MATH_NAMESPACE::Squareroot(LengthSquared());
	}

	template <typename T>
	constexpr T Vector3T<T>::LengthSquared() const
	{
		return (X * X) + (Y * Y) + (Z * Z);
	}

	template <typename T>
	constexpr Vector3T<T> Vector3T<T>::Lerp(const Vector3T& aValue1, const Vector3T& aValue2, const T& anAmount)
	{
		return (aValue1 + ((aValue2 - aValue1) * anAmount));
	}

	template <typename T>
	constexpr Vector3T<T> Vector3T<T>::Slerp(const Vector3T& aValue1, const Vector3T& aValue2, const T& anAmount)
	{
		if (aValue1 == aValue2)
			return aValue1;

		const T dot = ROSECOMMON_MATH_NAMESPACE::Clamp(Dot(aValue1, aValue2), -1.f, 1.f);
		const T theta = ROSECOMMON_MATH_NAMESPACE::ArcCosine(dot) * anAmount;
		Vector3T relativeVector = aValue2 - (aValue1 * dot);
		relativeVector.Normalize();
		return ((aValue1 * ROSECOMMON_MATH_NAMESPACE::Cosine(theta)) + (relativeVector * ROSECOMMON_MATH_NAMESPACE::Sine(theta)));
	}

	template <typename T>
	constexpr Vector3T<T> Vector3T<T>::Max(const Vector3T& aValue1, const Vector3T& aValue2)
	{
		return Vector3T(
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Y, aValue2.Y),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Z, aValue2.Z)
		);
	}

	template <typename T>
	constexpr Vector3T<T> Vector3T<T>::Min(const Vector3T& aValue1, const Vector3T& aValue2)
	{
		return Vector3T(
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Y, aValue2.Y),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Z, aValue2.Z)
		);
	}

	template <typename T>
	constexpr Vector3T<T> Vector3T<T>::Reflect(const Vector3T& aVector, const Vector3T& aNormal)
	{
		Vector3T result;
		const T dotProduct = Dot(aVector, aNormal);
		result.X = aVector.X - (2.0f * aNormal.X) * dotProduct;
		result.Y = aVector.Y - (2.0f * aNormal.Y) * dotProduct;
		result.Z = aVector.Z - (2.0f * aNormal.Z) * dotProduct;
		return result;
	}

	template <typename T>
	constexpr Vector3T<T> Vector3T<T>::SmoothStep(const Vector3T& aValue1, const Vector3T& aValue2, const T& anAmount)
	{
		return Vector3T(
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.X, aValue2.X, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Y, aValue2.Y, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Z, aValue2.Z, anAmount)
		);
	}

	#pragma endregion

	#pragma region Vector4T implementation

	template <typename T>
	constexpr Vector4T<T>::Vector4T()
		: Vector4T(0, 0, 0)
	{

	}

	template <typename T>
	constexpr Vector4T<T>::Vector4T(const T& aValue)
		: Vector4T(aValue, aValue, aValue, aValue)
	{

	}

	template <typename T>
	constexpr Vector4T<T>::Vector4T(const T& anX, const T& aY, const T& aZ, const T& aW)
		: X(anX)
		, Y(aY)
		, Z(aZ)
		, W(aW)
	{

	}

	template <typename T>
	template <typename U>
	constexpr Vector4T<T>::Vector4T(const Vector4T<U>& aVector)
		: X(static_cast<T>(aVector.X))
		, Y(static_cast<T>(aVector.Y))
		, Z(static_cast<T>(aVector.Z))
		, W(static_cast<T>(aVector.W))
	{

	}

	template <typename T>
	constexpr Vector4T<T>::Vector4T(const Vector2T<T>& aVector, const T& aZ, const T& aW)
		: Vector4T(aVector.X, aVector.Y, aZ, aW)
	{

	}

	template <typename T>
	constexpr Vector4T<T>::Vector4T(const Vector3T<T>& aVector, const T& aW)
		: Vector4T(aVector.X, aVector.Y, aVector.Z, aW)
	{

	}

	template <typename T>
	constexpr Vector4T<T>::Vector4T(const MatrixT<1, 4, T>& aColumnMatrix)
		: X(aColumnMatrix.GetCell(0, 0))
		, Y(aColumnMatrix.GetCell(0, 1))
		, Z(aColumnMatrix.GetCell(0, 2))
		, W(aColumnMatrix.GetCell(0, 3))
	{

	}

	template <typename T>
	constexpr Vector4T<T>::Vector4T(const MatrixT<4, 1, T>& aRowMatrix)
		: X(aRowMatrix.GetCell(0, 0))
		, Y(aRowMatrix.GetCell(1, 0))
		, Z(aRowMatrix.GetCell(2, 0))
		, W(aRowMatrix.GetCell(3, 0))
	{

	}

	template <typename T>
	constexpr Vector4T<T> Vector4T<T>::Clamp(const Vector4T& aVector, const Vector4T& aMinimum, const Vector4T& aMaximum)
	{
		return Vector4T(
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.X, aMinimum.X, aMaximum.X),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.Y, aMinimum.Y, aMaximum.Y),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.Z, aMinimum.Z, aMaximum.Z),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(aVector.W, aMinimum.W, aMaximum.W)
		);
	}

	template <typename T>
	constexpr T Vector4T<T>::Content() const
	{
		return X * Y * Z * W;
	}

	template <typename T>
	constexpr T Vector4T<T>::Distance(const Vector4T& aValue1, const Vector4T& aValue2)
	{
		return (aValue1 - aValue2).Length();
	}

	template <typename T>
	constexpr T Vector4T<T>::DistanceSquared(const Vector4T& aValue1, const Vector4T& aValue2)
	{
		return (aValue1 - aValue2).LengthSquared();
	}

	template <typename T>
	constexpr T Vector4T<T>::Dot(const Vector4T& aValue1, const Vector4T& aValue2)
	{
		return
			(aValue1.X * aValue2.X) +
			(aValue1.Y * aValue2.Y) +
			(aValue1.Z * aValue2.Z) +
			(aValue1.W * aValue2.W);
	}

	template <typename T>
	constexpr T Vector4T<T>::Length() const
	{
		return ROSECOMMON_MATH_NAMESPACE::Squareroot(LengthSquared());
	}

	template <typename T>
	constexpr T Vector4T<T>::LengthSquared() const
	{
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	template <typename T>
	constexpr Vector4T<T> Vector4T<T>::Lerp(const Vector4T& aValue1, const Vector4T& aValue2, const T& anAmount)
	{
		return (aValue1 + ((aValue2 - aValue1) * anAmount));
	}

	template <typename T>
	constexpr Vector4T<T> Vector4T<T>::Max(const Vector4T& aValue1, const Vector4T& aValue2)
	{
		return Vector4T(
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Y, aValue2.Y),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.Z, aValue2.Z),
			ROSECOMMON_MATH_NAMESPACE::Max<T>(aValue1.W, aValue2.W)
		);
	}

	template <typename T>
	constexpr Vector4T<T> Vector4T<T>::Min(const Vector4T& aValue1, const Vector4T& aValue2)
	{
		return Vector4T(
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.X, aValue2.X),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Y, aValue2.Y),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.Z, aValue2.Z),
			ROSECOMMON_MATH_NAMESPACE::Min<T>(aValue1.W, aValue2.W)
		);
	}

	template <typename T>
	constexpr Vector4T<T> Vector4T<T>::SmoothStep(const Vector4T& aValue1, const Vector4T& aValue2, const T& anAmount)
	{
		return Vector4T(
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.X, aValue2.X, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Y, aValue2.Y, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.Z, aValue2.Z, anAmount),
			ROSECOMMON_MATH_NAMESPACE::SmoothStep<T>(aValue1.W, aValue2.W, anAmount)
		);
	}

	#pragma endregion
}
