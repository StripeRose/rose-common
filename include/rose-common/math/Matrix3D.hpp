#pragma once

#include "../RoseCommon_Namespace.hpp"

#include "Matrix.hpp"
#include "Trigonometry.hpp"
#include "Vector.hpp"

namespace ROSECOMMON_MATH_NAMESPACE
{
	/*
	 * A note on Create-function chirality:
	 *
	 * Some functions throw an error 100% of the time, due to not having been checked for chirality(handedness).
	 *
	 * They have been copied from the reference at: https://github.com/microsoft/referencesource/blob/master/System.Numerics/System/Numerics/Matrix4x4.cs
	 * But some functions have not been as easy to test for chirality�.
	 *
	 * When hit, that likely means there is a test-case with an expected outcome,
	 * making it possible to confirm that the code is correct or fix it if not.
	 *
	 * Matrix3DT should be a row-major, left handed matrix.
	 */

	 /**
	  * @brief Specialized row-major matrix used for 3D transformations, with functions useful for this purpose.
	  * @tparam T The type to use for each cell in the matrix.
	  */
	template <typename T>
	class Matrix3DT
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
		 * @brief Initialize an identity matrix.
		 * @return The identity matrix.
		 */
		static constexpr Matrix3DT Identity();

		#pragma endregion

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize to all zeroes.
		 */
		constexpr Matrix3DT();

		/**
		 * @brief Initialize to the same value as another matrix.
		 * @param aMatrix The matrix to initialize with.
		 */
		constexpr Matrix3DT(const MatrixT<4, 4, T>& aMatrix);

		/**
		 * @brief Initialize to the same as another matrix.
		 * @param aMatrix The matrix to initialize with.
		 */
		constexpr Matrix3DT(const Matrix3DT& aMatrix);

		/**
		 * @brief Create a matrix for spherical billboarding that rotates around specified object position.
		 * @param anObjectPosition Position of billboard object. It will rotate around that position.
		 * @param aTargetPosition The position to rotate towards.
		 * @param anUpVector The world, camera, or billboard object up-vector.
		 * @param aDefaultDirection The optional default direction, used when the object is too close to the target position.
		 * @return The billboard matrix.
		 */
		static constexpr Matrix3DT CreateBillboard(const Vector3T<T>& anObjectPosition, const Vector3T<T>& aTargetPosition, const Vector3T<T>& anUpVector, const std::optional<Vector3T<T>>& aDefaultDirection) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a matrix that rotates around an arbitrary axis.
		 * @param anAxis A normalized vector Matrix specifying the axis.
		 * @param anAngle The amount, in radians, in which to rotate.
		 * @return The rotation matrix.
		 */
		static constexpr Matrix3DT CreateFromAxisAngle(const Vector3T<T>& anAxis, const T& anAngle) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a view matrix, turned towards a specific position.
		 * @param aPosition The position of the camera.
		 * @param aTarget The target towards which the camera is pointing.
		 * @param anUpVector The direction that is "up" from the camera's point of view.
		 * @return The view matrix.
		 */
		static constexpr Matrix3DT CreateLookAt(const Vector3T<T>& aPosition, const Vector3T<T>& aTarget, const Vector3T<T>& anUpVector) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a projection matrix for orthographic view.
		 * @param aWidth Width of the viewing volume.
		 * @param aHeight Height of the viewing volume.
		 * @param aNearZPlaneDistance Distance to the near view plane.
		 * @param aFarZPlaneDistance Distance to the far view plane.
		 * @return The projection matrix.
		 */
		static constexpr Matrix3DT CreateOrthographic(T aWidth, T aHeight, T aNearZPlaneDistance, T aFarZPlaneDistance) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a customized projection matrix for orthographic view.
		 * @param aLeft Minimum X-value of the viewing volume.
		 * @param aRight Maximum X-value of the viewing volume.
		 * @param aBottom Minimum Y-value of the viewing volume.
		 * @param aTop Maximum Y-value of the viewing volume.
		 * @param aNearZPlaneDistance Distance to the near view plane.
		 * @param aFarZPlaneDistance Distance to the far view plane.
		 * @return The projection matrix.
		 */
		static constexpr Matrix3DT CreateOrthographicOffCenter(T aLeft, T aRight, T aBottom, T aTop, T aNearZPlaneDistance, T aFarZPlaneDistance) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a perspective projection matrix from a given field-of-view and aspect-ratio.
		 * @param aFieldOfView Field of view in the Y direction, in radians.
		 * @param anAspectRatio Aspect ratio, defined as view space width divided by height.
		 * @param aNearZPlaneDistance Distance to the near view plane.
		 * @param aFarZPlaneDistance Distance to the far view plane.
		 * @return The projection matrix.
		 */
		static constexpr Matrix3DT CreatePerspectiveFieldOfView(const T& aFieldOfView, const T& anAspectRatio, const T& aNearPlaneDistance, const T& aFarPlaneDistance) requires(std::is_floating_point_v<T>);

		// Todo: Potentially implement CreatePerspectiveOffCenter().

		/**
		 * @brief Create a matrix that reflects the coordinate system about the specified plane normal.
		 * @param aPlaneNormal The Plane normal about which to create a reflection.
		 * @param aDistance The distance of the Plane along its normal from its origin.
		 * @return The reflection matrix.
		 */
		static constexpr Matrix3DT CreateReflection(const Vector3T<T> aPlaneNormal, const T aDistance = T(0)) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a matrix that can be used to rotate a set of points around the x-axis.
		 * @param anAngle The amount, in radians, in which to rotate.
		 * @return The rotation matrix.
		 */
		static constexpr Matrix3DT CreateRotationX(const T& anAngle) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a matrix that can be used to rotate a set of points around the y-axis.
		 * @param anAngle The amount, in radians, in which to rotate.
		 * @return The rotation matrix.
		 */
		static constexpr Matrix3DT CreateRotationY(const T& anAngle) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a matrix that can be used to rotate a set of points around the z-axis.
		 * @param anAngle The amount, in radians, in which to rotate.
		 * @return The rotation matrix.
		 */
		static constexpr Matrix3DT CreateRotationZ(const T& anAngle) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a scaling matrix.
		 * @param anXScale The X scaling value.
		 * @param aYScale The Y scaling value.
		 * @param aZScale The Z scaling value.
		 * @return The scaling matrix.
		 */
		static constexpr Matrix3DT CreateScale(const T& anXScale, const T& aYScale, const T& aZScale) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a scaling matrix with a center point.
		 * @param anXScale The X scaling value.
		 * @param aYScale The Y scaling value.
		 * @param aZScale The Z scaling value.
		 * @param aCenterPoint The center point.
		 * @return The scaling matrix.
		 */
		static constexpr Matrix3DT CreateScale(const T& anXScale, const T& aYScale, const T& aZScale, const Vector3T<T>& aCenterPoint) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a scaling matrix.
		 * @param aScale The Vector3 containing the amount to scale by on each axis.
		 * @return The scaling matrix.
		 */
		static constexpr Matrix3DT CreateScale(const Vector3T<T>& aScale) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a scaling matrix with a center point.
		 * @param aScale The Vector3 containing the amount to scale by on each axis.
		 * @param aCenterPoint The center point.
		 * @return The scaling matrix.
		 */
		static constexpr Matrix3DT CreateScale(const Vector3T<T>& aScale, const Vector3T<T>& aCenterPoint) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a scaling matrix.
		 * @param aScale The scaling value to use for each axis.
		 * @return The scaling matrix.
		 */
		static constexpr Matrix3DT CreateScale(const T& aScale) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a scaling matrix with a center point.
		 * @param aScale The scaling value to use for each axis.
		 * @param aCenterPoint The center point.
		 * @return The scaling matrix.
		 */
		static constexpr Matrix3DT CreateScale(const T& aScale, const Vector3T<T>& aCenterPoint) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a matrix that flattens geometry into a specified plane as if casting a shadow from a specified light source.
		 * @param aLightDirection The direction from which the light that will cast the shadow is coming.
		 * @param aPlaneNormal The normal of the plane onto which the new matrix should flatten geometry.
		 * @param aPlaneDistance The distance of the plane onto which the new matrix should flatten geometry.
		 * @return The shadow matrix.
		 */
		static constexpr Matrix3DT CreateShadow(const Vector3T<T>& aLightDirection, const Vector3T<T>& aPlaneNormal, T aPlaneDistance) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a translation matrix.
		 * @param anX Value to translate on the x-axis.
		 * @param aY Value to translate on the y-axis.
		 * @param aZ Value to translate on the z-axis.
		 * @return The translation matrix.
		 */
		static constexpr Matrix3DT CreateTranslation(const T& anX, const T& aY, const T& aZ) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a translation matrix.
		 * @param aPosition The Vector3 containing the amount to translate by on each axis.
		 * @return The translation matrix.
		 */
		static constexpr Matrix3DT CreateTranslation(const Vector3T<T>& aPosition) requires(std::is_floating_point_v<T>);

		/**
		 * @brief Create a world matrix with the specified parameters.
		 * @param aPosition The position of the world.
		 * @param aForward The forward direction.
		 * @param anUp The up direction.
		 * @return The world matrix.
		 */
		static constexpr Matrix3DT CreateWorld(const Vector3T<T>& aPosition, const Vector3T<T>& aForward, const Vector3T<T>& anUp);

		#pragma endregion

		//--------------------------------------------------
		// * Properties
		//--------------------------------------------------
		#pragma region Properties

		/**
		 * @brief Get the backwards vector of the matrix.
		 * @return The backwards vector.
		 */
		constexpr Vector3T<T> Backward() const;

		/**
		 * @brief Get the down vector of the matrix.
		 * @return The down vector.
		 */
		constexpr Vector3T<T> Down() const;

		/**
		 * @brief Get the forward vector of the matrix.
		 * @return The forward vector.
		 */
		constexpr Vector3T<T> Forward() const;

		/**
		 * @brief Get the left vector of the matrix.
		 * @return The left vector.
		 */
		constexpr Vector3T<T> Left() const;

		/**
		 * @brief Get the right vector of the matrix.
		 * @return The right vector.
		 */
		constexpr Vector3T<T> Right() const;

		/**
		 * @brief Get the up vector of the matrix.
		 * @return The up vector.
		 */
		constexpr Vector3T<T> Up() const;

		#pragma endregion

		//--------------------------------------------------
		// * Methods
		//--------------------------------------------------
		#pragma region Methods

		/// <summary>
		/// Extracts the scalar, translation, and rotation components from a 3D scale/rotate/translate (SRT) Matrix.
		/// </summary>
		/// <param name="outScale">The scalar component of the transform matrix, expressed as a Vector3.</param>
		/// <param name="outRotation">The rotation component of the transform matrix, expressed as a Quaternion.</param>
		/// <param name="outTranslation">The translation component of the transform matrix, expressed as a Vector3.</param>		
		/*void Decompose(Vector3& outScale, Quaternion& outRotation, Vector3& outTranslation) const*/

		/**
		 * @brief Calculate the determinant of the matrix.
		 * @return The determinant value.
		 */
		constexpr T Determinant() const;

		/**
		 * @brief Get the value of a specific cell.
		 * @param aColumn The zero-based column index.
		 * @param aRow The zero-based row index.
		 * @return A reference to the cell value.
		 */
		constexpr T& GetCell(std::size_t aColumn, std::size_t aRow);

		/**
		 * @brief Get the value of a specific cell.
		 * @param aColumn The zero-based column index.
		 * @param aRow The zero-based row index.
		 * @return A reference to the cell value.
		 */
		constexpr T GetCell(std::size_t aColumn, std::size_t aRow) const;

		/**
		 * @brief Get the matrix translation.
		 * @return The translation as a Vector3.
		 */
		constexpr Vector3T<T> GetTranslation() const;

		/**
		 * @brief Get the matrix translation.
		 * @return The translation as a Vector4.
		 */
		constexpr Vector4T<T> GetTranslation4() const;

		/**
		 * @brief Calculate the matrix inverse.
		 * @return The inverse of the matrix.
		 */
		constexpr Matrix3DT Inverse() const;

		/**
		 * @brief Calculate the inverse of the matrix quickly, but less accurately.
		 * @return The inverse of the matrix.
		 */
		constexpr Matrix3DT Inverse_Fast() const;

		/**
		 * @brief Set the matrix translation.
		 * @param aVector The value to set the translation to.
		 */
		void SetTranslation(const Vector3T<T>& aVector);

		/**
		 * @brief Set the matrix translation.
		 * @param aVector The value to set the translation to.
		 */
		void SetTranslation4(const Vector4T<T>& aVector);

		/**
		 * @brief Transpose the rows and columns of the matrix.
		 * @return The transposed matrix.
		 */
		constexpr Matrix3DT Transposed() const;

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		inline constexpr operator MatrixT<4, 4, T>() const { return myMatrix; }

		inline constexpr Matrix3DT operator*(const Matrix3DT& aMatrix) const { return Matrix3DT(myMatrix * aMatrix.myMatrix); }

		inline constexpr friend Vector3T<T> operator*(const Vector3T<T>& aVector, const Matrix3DT<T>& aMatrix) { return Vector3T<T>(Vector4T<T>(aVector, T(1)) * aMatrix.myMatrix); }
		inline constexpr friend Vector4T<T> operator*(const Vector4T<T>& aVector, const Matrix3DT<T>& aMatrix) { return aVector * aMatrix.myMatrix; }

		inline constexpr bool operator==(const Matrix3DT& aMatrix) const { return myMatrix == aMatrix.myMatrix; }
		inline constexpr bool operator!=(const Matrix3DT& aMatrix) const { return myMatrix != aMatrix.myMatrix; }

		#pragma endregion

	private:
		MatrixT<4, 4, T> myMatrix;
	};
}

namespace ROSECOMMON_MATH_NAMESPACE
{
	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::Identity()
	{
		return Matrix3DT(MatrixT<4, 4, T>::Identity());
	}

	template <typename T>
	constexpr Matrix3DT<T>::Matrix3DT()
	{

	}

	template <typename T>
	constexpr Matrix3DT<T>::Matrix3DT(const MatrixT<4, 4, T>& aMatrix)
		: myMatrix(aMatrix)
	{

	}

	template <typename T>
	constexpr Matrix3DT<T>::Matrix3DT(const Matrix3DT& aMatrix)
		: myMatrix(aMatrix.myMatrix)
	{

	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateBillboard(const Vector3T<T>& anObjectPosition, const Vector3T<T>& aTargetPosition, const Vector3T<T>& anUpVector, const std::optional<Vector3T<T>>& aDefaultDirection) requires(std::is_floating_point_v<T>)
	{
		constexpr T epsilon = static_cast<T>(1e-4);

		Vector3T<T> zAxis(aTargetPosition - anObjectPosition);
		const T norm = zAxis.LengthSquared();
		if (norm < epsilon)
			zAxis = aDefaultDirection.has_value() ? aDefaultDirection.value() : Vector3T<T>::Forward();
		else
			zAxis = zAxis * ROSECOMMON_MATH_NAMESPACE::ReciprocalSquareroot<T>(norm);

		const Vector3T<T> xAxis(Vector3T<T>::Cross(anUpVector, zAxis).Normalized());
		const Vector3T<T> yAxis(Vector3T<T>::Cross(zAxis, xAxis));

		Matrix3DT<T> result;

		result.GetCell(0, 0) = xAxis.X;
		result.GetCell(1, 0) = xAxis.Y;
		result.GetCell(2, 0) = xAxis.Z;
		result.GetCell(3, 0) = 0;

		result.GetCell(0, 1) = yAxis.X;
		result.GetCell(1, 1) = yAxis.Y;
		result.GetCell(2, 1) = yAxis.Z;
		result.GetCell(3, 1) = 0;

		result.GetCell(0, 2) = zAxis.X;
		result.GetCell(1, 2) = zAxis.Y;
		result.GetCell(2, 2) = zAxis.Z;
		result.GetCell(3, 2) = 0;

		result.GetCell(0, 3) = anObjectPosition.X;
		result.GetCell(1, 3) = anObjectPosition.Y;
		result.GetCell(2, 3) = anObjectPosition.Z;
		result.GetCell(3, 3) = 1;

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateFromAxisAngle(const Vector3T<T>& anAxis, const T& anAngle) requires(std::is_floating_point_v<T>)
	{
		T c = ROSECOMMON_MATH_NAMESPACE::Cosine<T>(-anAngle);
		T s = ROSECOMMON_MATH_NAMESPACE::Sine<T>(-anAngle);
		T t = static_cast<T>(1) - c;

		Matrix3DT result = Matrix3DT::Identity();

		result.GetCell(0, 0) = c + anAxis.X * anAxis.X * t;
		result.GetCell(1, 1) = c + anAxis.Y * anAxis.Y * t;
		result.GetCell(2, 2) = c + anAxis.Z * anAxis.Z * t;

		T tmp1 = anAxis.X * anAxis.Y * t;
		T tmp2 = anAxis.Z * s;

		result.GetCell(0, 1) = tmp1 + tmp2;
		result.GetCell(1, 0) = tmp1 - tmp2;

		tmp1 = anAxis.X * anAxis.Z * t;
		tmp2 = anAxis.Y * s;
		result.GetCell(0, 2) = tmp1 - tmp2;
		result.GetCell(2, 0) = tmp1 + tmp2;

		tmp1 = anAxis.Y * anAxis.Z * t;
		tmp2 = anAxis.X * s;
		result.GetCell(1, 2) = tmp1 + tmp2;
		result.GetCell(2, 1) = tmp1 - tmp2;

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateLookAt(const Vector3T<T>& aPosition, const Vector3T<T>& aTarget, const Vector3T<T>& anUpVector) requires(std::is_floating_point_v<T>)
	{
		const Vector3T<T> zAxis = (aTarget - aPosition).Normalized();
		const Vector3T<T> xAxis = Vector3T<T>::Cross(anUpVector, zAxis).Normalized();
		const Vector3T<T> yAxis = Vector3T<T>::Cross(zAxis, xAxis).Normalized();

		Matrix3DT result;

		result.GetCell(0, 0) = xAxis.X;
		result.GetCell(1, 0) = yAxis.X;
		result.GetCell(2, 0) = zAxis.X;
		result.GetCell(3, 0) = T(0);
		result.GetCell(0, 1) = xAxis.Y;
		result.GetCell(1, 1) = yAxis.Y;
		result.GetCell(2, 1) = zAxis.Y;
		result.GetCell(3, 1) = T(0);
		result.GetCell(0, 2) = xAxis.Z;
		result.GetCell(1, 2) = yAxis.Z;
		result.GetCell(2, 2) = zAxis.Z;
		result.GetCell(3, 2) = T(0);
		result.GetCell(0, 3) = -Vector3T<T>::Dot(xAxis, aPosition);
		result.GetCell(1, 3) = -Vector3T<T>::Dot(yAxis, aPosition);
		result.GetCell(2, 3) = -Vector3T<T>::Dot(zAxis, aPosition);
		result.GetCell(3, 3) = T(1);

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateOrthographic(T aWidth, T aHeight, T aNearZPlaneDistance, T aFarZPlaneDistance) requires(std::is_floating_point_v<T>)
	{
		Matrix3DT result;

		result.GetCell(0, 0) = T(2) / aWidth;
		result.GetCell(1, 1) = T(2) / aHeight;
		result.GetCell(2, 2) = T(1) / (aFarZPlaneDistance - aNearZPlaneDistance);
		result.GetCell(3, 3) = T(1);

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateOrthographicOffCenter(T aLeft, T aRight, T aBottom, T aTop, T aNearZPlaneDistance, T aFarZPlaneDistance) requires(std::is_floating_point_v<T>)
	{
		throw std::exception("Needs chirality confirmation."); // See top of file for details.

		Matrix3DT result;

		result.GetCell(0, 0) = T(2) / (aRight - aLeft);
		result.GetCell(1, 1) = T(2) / (aTop - aBottom);
		result.GetCell(2, 2) = T(1) / (aFarZPlaneDistance - aNearZPlaneDistance);

		result.GetCell(0, 3) = (aLeft + aRight) / (aLeft - aRight);
		result.GetCell(1, 3) = (aTop + aBottom) / (aBottom - aTop);
		result.GetCell(2, 3) = aNearZPlaneDistance / (aFarZPlaneDistance - aNearZPlaneDistance);
		result.GetCell(3, 3) = T(1);

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreatePerspectiveFieldOfView(const T& aFieldOfView, const T& anAspectRatio, const T& aNearPlaneDistance, const T& aFarPlaneDistance) requires(std::is_floating_point_v<T>)
	{
		if (aFieldOfView <= T(0) || aFieldOfView >= ROSECOMMON_MATH_NAMESPACE::PiT<T>)
			throw std::out_of_range("aFieldOfView");

		if (aNearPlaneDistance <= T(0))
			throw std::out_of_range("aNearPlaneDistance");

		if (aFarPlaneDistance <= T(0))
			throw std::out_of_range("aFarPlaneDistance");

		if (aNearPlaneDistance >= aFarPlaneDistance)
			throw std::out_of_range("aNearPlaneDistance");

		const T yScale = ROSECOMMON_MATH_NAMESPACE::Cotangent(aFieldOfView / T(2));
		const T xScale = yScale / anAspectRatio;
		const T scaling = aFarPlaneDistance / (aFarPlaneDistance - aNearPlaneDistance);

		Matrix3DT result;

		result.GetCell(0, 0) = xScale;
		result.GetCell(1, 1) = yScale;
		result.GetCell(2, 2) = scaling;
		result.GetCell(3, 2) = 1;
		result.GetCell(2, 3) = -scaling * aNearPlaneDistance;
		result.GetCell(3, 3) = 0;

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateReflection(const Vector3T<T> aPlaneNormal, const T aDistance) requires(std::is_floating_point_v<T>)
	{
		throw std::exception("Needs chirality confirmation."); // See top of file for details.

		const T a = aPlaneNormal.X;
		const T b = aPlaneNormal.Y;
		const T c = aPlaneNormal.Z;

		const T fa = -T(2) * a;
		const T fb = -T(2) * b;
		const T fc = -T(2) * c;

		Matrix3DT result;

		result.GetCell(0, 0) = fa * a + 1.0f;
		result.GetCell(1, 0) = fb * a;
		result.GetCell(2, 0) = fc * a;
		result.GetCell(3, 0) = 0.0f;

		result.GetCell(0, 1) = fa * b;
		result.GetCell(1, 1) = fb * b + 1.0f;
		result.GetCell(2, 1) = fc * b;
		result.GetCell(3, 1) = 0.0f;

		result.GetCell(0, 2) = fa * c;
		result.GetCell(1, 2) = fb * c;
		result.GetCell(2, 2) = fc * c + 1.0f;
		result.GetCell(3, 2) = 0.0f;

		result.GetCell(0, 3) = fa * aDistance;
		result.GetCell(1, 3) = fb * aDistance;
		result.GetCell(2, 3) = fc * aDistance;
		result.GetCell(3, 3) = 1.0f;

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateRotationX(const T& anAngle) requires(std::is_floating_point_v<T>)
	{
		T c = ROSECOMMON_MATH_NAMESPACE::Cosine<T>(anAngle);
		T s = ROSECOMMON_MATH_NAMESPACE::Sine<T>(anAngle);

		Matrix3DT result = Matrix3DT::Identity();

		result.GetCell(1, 1) = c;
		result.GetCell(2, 1) = s;
		result.GetCell(1, 2) = -s;
		result.GetCell(2, 2) = c;

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateRotationY(const T& anAngle) requires(std::is_floating_point_v<T>)
	{
		T c = ROSECOMMON_MATH_NAMESPACE::Cosine<T>(anAngle);
		T s = ROSECOMMON_MATH_NAMESPACE::Sine<T>(anAngle);

		Matrix3DT result = Matrix3DT::Identity();

		result.GetCell(0, 0) = c;
		result.GetCell(2, 0) = -s;
		result.GetCell(0, 2) = s;
		result.GetCell(2, 2) = c;

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateRotationZ(const T& anAngle) requires(std::is_floating_point_v<T>)
	{
		T c = ROSECOMMON_MATH_NAMESPACE::Cosine<T>(anAngle);
		T s = ROSECOMMON_MATH_NAMESPACE::Sine<T>(anAngle);

		Matrix3DT result = Matrix3DT::Identity();

		result.GetCell(0, 0) = c;
		result.GetCell(1, 0) = s;
		result.GetCell(0, 1) = -s;
		result.GetCell(1, 1) = c;

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateScale(const T& anXScale, const T& aYScale, const T& aZScale) requires(std::is_floating_point_v<T>)
	{
		Matrix3DT result = Matrix3DT::Identity();

		result.GetCell(0, 0) = anXScale;
		result.GetCell(1, 1) = aYScale;
		result.GetCell(2, 2) = aZScale;

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateScale(const T& anXScale, const T& aYScale, const T& aZScale, const Vector3T<T>& aCenterPoint) requires(std::is_floating_point_v<T>)
	{
		Matrix3DT result = Matrix3DT::Identity();

		result.GetCell(0, 0) = anXScale;
		result.GetCell(1, 1) = aYScale;
		result.GetCell(2, 2) = aZScale;

		result.GetCell(0, 3) = aCenterPoint.X * (T(1) - anXScale);
		result.GetCell(1, 3) = aCenterPoint.Y * (T(1) - aYScale);
		result.GetCell(2, 3) = aCenterPoint.Z * (T(1) - aZScale);

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateScale(const Vector3T<T>& aScale) requires(std::is_floating_point_v<T>)
	{
		return CreateScale(aScale.X, aScale.Y, aScale.Z);
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateScale(const Vector3T<T>& aScale, const Vector3T<T>& aCenterPoint) requires(std::is_floating_point_v<T>)
	{
		return CreateScale(aScale.X, aScale.Y, aScale.Z, aCenterPoint);
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateScale(const T& aScale) requires(std::is_floating_point_v<T>)
	{
		return CreateScale(aScale, aScale, aScale);
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateScale(const T& aScale, const Vector3T<T>& aCenterPoint) requires(std::is_floating_point_v<T>)
	{
		return CreateScale(aScale, aScale, aScale, aCenterPoint);
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateShadow(const Vector3T<T>& aLightDirection, const Vector3T<T>& aPlaneNormal, T aPlaneDistance) requires(std::is_floating_point_v<T>)
	{
		throw std::exception("Needs chirality confirmation."); // See top of file for details.

		const T dot = Vector3T<T>::Dot(aPlaneNormal, aLightDirection);
		const T a = -aPlaneNormal.X;
		const T b = -aPlaneNormal.Y;
		const T c = -aPlaneNormal.Z;
		const T d = -aPlaneDistance;

		Matrix3DT result;

		result.GetCell(0, 0) = a * aLightDirection.X + dot;
		result.GetCell(0, 1) = b * aLightDirection.X;
		result.GetCell(0, 2) = c * aLightDirection.X;
		result.GetCell(0, 3) = d * aLightDirection.X;

		result.GetCell(1, 0) = a * aLightDirection.Y;
		result.GetCell(1, 1) = b * aLightDirection.Y + dot;
		result.GetCell(1, 2) = c * aLightDirection.Y;
		result.GetCell(1, 3) = d * aLightDirection.Y;

		result.GetCell(2, 0) = a * aLightDirection.Z;
		result.GetCell(2, 1) = b * aLightDirection.Z;
		result.GetCell(2, 2) = c * aLightDirection.Z + dot;
		result.GetCell(2, 3) = d * aLightDirection.Z;

		result.GetCell(3, 0) = 0;
		result.GetCell(3, 1) = 0;
		result.GetCell(3, 2) = 0;
		result.GetCell(3, 3) = dot;

		return result;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateTranslation(const T& anX, const T& aY, const T& aZ) requires(std::is_floating_point_v<T>)
	{
		Matrix3DT matrix = Matrix3DT::Identity();

		matrix.GetCell(0, 3) = anX;
		matrix.GetCell(1, 3) = aY;
		matrix.GetCell(2, 3) = aZ;

		return matrix;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateTranslation(const Vector3T<T>& aPosition) requires(std::is_floating_point_v<T>)
	{
		return CreateTranslation(aPosition.X, aPosition.Y, aPosition.Z);
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::CreateWorld(const Vector3T<T>& aPosition, const Vector3T<T>& aForward, const Vector3T<T>& anUp)
	{
		const Vector3T<T> zAxis = aForward.Normalized();
		const Vector3T<T> xAxis = Vector3T<T>::Cross(anUp, zAxis).Normalized();
		const Vector3T<T> yAxis = Vector3T<T>::Cross(zAxis, xAxis);

		Matrix3DT result;

		result.GetCell(0, 0) = xAxis.X;
		result.GetCell(1, 0) = xAxis.Y;
		result.GetCell(2, 0) = xAxis.Z;
		result.GetCell(3, 0) = 0.0f;
		result.GetCell(0, 1) = yAxis.X;
		result.GetCell(1, 1) = yAxis.Y;
		result.GetCell(2, 1) = yAxis.Z;
		result.GetCell(3, 1) = 0.0f;
		result.GetCell(0, 2) = zAxis.X;
		result.GetCell(1, 2) = zAxis.Y;
		result.GetCell(2, 2) = zAxis.Z;
		result.GetCell(3, 2) = 0.0f;
		result.GetCell(0, 3) = aPosition.X;
		result.GetCell(1, 3) = aPosition.Y;
		result.GetCell(2, 3) = aPosition.Z;
		result.GetCell(3, 3) = 1.0f;

		return result;
	}

	template <typename T>
	constexpr Vector3T<T> Matrix3DT<T>::Backward() const
	{
		return Vector3T<T>({
			-myMatrix.GetCell(0, 2),
			-myMatrix.GetCell(1, 2),
			-myMatrix.GetCell(2, 2)
			});
	}

	template <typename T>
	constexpr Vector3T<T> Matrix3DT<T>::Down() const
	{
		return Vector3T<T>({
			-myMatrix.GetCell(0, 1),
			-myMatrix.GetCell(1, 1),
			-myMatrix.GetCell(2, 1)
			});
	}

	template <typename T>
	constexpr Vector3T<T> Matrix3DT<T>::Forward() const
	{
		return Vector3T<T>({
			myMatrix.GetCell(0, 2),
			myMatrix.GetCell(1, 2),
			myMatrix.GetCell(2, 2)
			});
	}

	template <typename T>
	constexpr Vector3T<T> Matrix3DT<T>::Left() const
	{
		return Vector3T<T>({
			-myMatrix.GetCell(0, 0),
			-myMatrix.GetCell(1, 0),
			-myMatrix.GetCell(2, 0)
			});
	}

	template <typename T>
	constexpr Vector3T<T> Matrix3DT<T>::Right() const
	{
		return Vector3T<T>({
			myMatrix.GetCell(0, 0),
			myMatrix.GetCell(1, 0),
			myMatrix.GetCell(2, 0)
			});
	}

	template <typename T>
	constexpr Vector3T<T> Matrix3DT<T>::Up() const
	{
		return Vector3T<T>({
			myMatrix.GetCell(0, 1),
			myMatrix.GetCell(1, 1),
			myMatrix.GetCell(2, 1)
			});
	}

	/*template <typename T>
	constexpr void Matrix3DT<T>::Decompose(Vector3& outScale, Quaternion& outRotation, Vector3& outTranslation) const
	{
		outTranslation = GetTranslation();

		outScale.X = ROSECOMMON_MATH_NAMESPACE::Squareroot((M11 * M11) + (M12 * M12) + (M13 * M13));
		outScale.Y = ROSECOMMON_MATH_NAMESPACE::Squareroot((M21 * M21) + (M22 * M22) + (M23 * M23));
		outScale.Z = ROSECOMMON_MATH_NAMESPACE::Squareroot((M31 * M31) + (M32 * M32) + (M33 * M33));

		Matrix rotationMatrix = (*this) * Matrix::InvertCorrect(Matrix::CreateScale(outScale) * Matrix::CreateTranslation(outTranslation));

		outRotation.X = rotationMatrix.GetCell(0, 3);
		outRotation.Y = rotationMatrix.GetCell(1, 3);
		outRotation.Z = rotationMatrix.GetCell(2, 3);
		outRotation.W = rotationMatrix.GetCell(3, 3);
	}*/

	template <typename T>
	constexpr T Matrix3DT<T>::Determinant() const
	{
		return myMatrix.Determinant();
	}

	template <typename T>
	constexpr T& Matrix3DT<T>::GetCell(std::size_t aColumn, std::size_t aRow)
	{
		return myMatrix.GetCell(aColumn, aRow);
	}

	template <typename T>
	constexpr T Matrix3DT<T>::GetCell(std::size_t aColumn, std::size_t aRow) const
	{
		return myMatrix.GetCell(aColumn, aRow);
	}

	template <typename T>
	constexpr Vector3T<T> Matrix3DT<T>::GetTranslation() const
	{
		return Vector3T<T>({
			myMatrix.GetCell(0, 3),
			myMatrix.GetCell(1, 3),
			myMatrix.GetCell(2, 3)
			}) / myMatrix.GetCell(3, 3);
	}

	template <typename T>
	constexpr Vector4T<T> Matrix3DT<T>::GetTranslation4() const
	{
		return Vector4T<T>({
			myMatrix.GetCell(0, 3),
			myMatrix.GetCell(1, 3),
			myMatrix.GetCell(2, 3),
			myMatrix.GetCell(3, 3)
			});
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::Inverse() const
	{
		const std::optional<MatrixT<4, 4, T>> inverted = myMatrix.Inverse();

		if (!inverted.has_value())
			throw std::exception("Matrix has no inverse.");

		return Matrix3DT(inverted.value());
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::Inverse_Fast() const
	{
		Matrix3DT invertedMatrix(*this);

		Vector4T translation = invertedMatrix.GetTranslation4();
		invertedMatrix.SetTranslation4(Vector4T(0, 0, 0, 1));

		translation *= -1.f;
		translation.W = 1.f;
		invertedMatrix = invertedMatrix.Transposed();
		translation *= invertedMatrix;
		invertedMatrix.SetTranslation4(translation);

		return invertedMatrix;
	}

	template <typename T>
	void Matrix3DT<T>::SetTranslation(const Vector3T<T>& aVector)
	{
		myMatrix.GetCell(0, 3) = aVector.X * myMatrix.GetCell(4, 3);
		myMatrix.GetCell(1, 3) = aVector.Y * myMatrix.GetCell(4, 3);
		myMatrix.GetCell(2, 3) = aVector.Z * myMatrix.GetCell(4, 3);
	}

	template <typename T>
	void Matrix3DT<T>::SetTranslation4(const Vector4T<T>& aVector)
	{
		myMatrix.GetCell(0, 3) = aVector.X;
		myMatrix.GetCell(1, 3) = aVector.Y;
		myMatrix.GetCell(2, 3) = aVector.Z;
		myMatrix.GetCell(3, 3) = aVector.W;
	}

	template <typename T>
	constexpr Matrix3DT<T> Matrix3DT<T>::Transposed() const
	{
		return Matrix3DT(myMatrix.Transposed());
	}
}
