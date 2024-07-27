#pragma once

#include "Matrix.hpp"
#include "Trigonometry.hpp"
#include "Vector.hpp"

namespace RoseCommon::Math
{
	// A note on Create-function chirality:
	// 
	// Some functions throw an error 100% of the time, due to not having been checked for chirality(handedness).
	// 
	// They have been copied from the reference at: https://github.com/microsoft/referencesource/blob/master/System.Numerics/System/Numerics/Matrix4x4.cs
	// But some functions have not been as easy to test for chirality¨.
	// 
	// When hit, that likely means there is a test-case with an expected outcome,
	// making it possible to confirm that the code is correct or fix it if not.
	//
	// Matrix3D should be a row-major, left handed matrix.
	//

	template <typename T>
	/// <summary>
	/// Specialized row-major Matrix used for 3D transformations, with functions useful for this purpose.
	/// </summary>
	class Matrix3D
	{
	public:
		static constexpr Matrix3D Identity() { return Matrix3D(Matrix<4, 4, T>::Identity()); }

		/// <summary>
		/// Creates a Matrix3D for spherical billboarding that rotates around specified object position.
		/// </summary>
		/// <param name="anObjectPosition">Position of billboard object. It will rotate around that position.</param>
		/// <param name="aTargetPosition">The position to rotate towards.</param>
		/// <param name="anUpVector">The world, camera, or billboard object up-vector.</param>
		/// <param name="aDefaultDirection">The optional default direction, used when the object is too close to the target position.</param>
		static constexpr Matrix3D CreateBillboard(
			const Vector3<T>& anObjectPosition,
			const Vector3<T>& aTargetPosition,
			const Vector3<T>& anUpVector,
			const std::optional<Vector3<T>>& aDefaultDirection) requires(std::is_floating_point_v<T>)
		{
			constexpr T epsilon = static_cast<T>(1e-4);

			Vector3<T> zAxis(aTargetPosition - anObjectPosition);
			const T norm = zAxis.LengthSquared();
			if (norm < epsilon)
				zAxis = aDefaultDirection.has_value() ? aDefaultDirection.value() : Vector3<T>::Forward();
			else
				zAxis = zAxis * Math::ReciprocalSquareroot<T>(norm);

			const Vector3<T> xAxis(Vector3<T>::Cross(anUpVector, zAxis).Normalized());
			const Vector3<T> yAxis(Vector3<T>::Cross(zAxis, xAxis));

			Matrix3D<T> result;

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

		/// <summary>
		/// Creates a Matrix3D that rotates around an arbitrary axis.
		/// </summary>
		/// <param name="anAxis">A normalized vector Matrix specifying the axis.</param>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		static constexpr Matrix3D CreateFromAxisAngle(const Vector3<T>& anAxis, const T& anAngle) requires(std::is_floating_point_v<T>)
		{
			T c = Math::Cosine<T>(-anAngle);
			T s = Math::Sine<T>(-anAngle);
			T t = static_cast<T>(1) - c;

			Matrix3D result = Matrix3D::Identity();

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

		/// <summary>
		/// Creates a view Matrix3D, turned towards a specific position.
		/// </summary>
		/// <param name="aPosition">The position of the camera.</param>
		/// <param name="aTarget">The target towards which the camera is pointing.</param>
		/// <param name="anUpVector">The direction that is "up" from the camera's point of view.</param>
		static constexpr Matrix3D CreateLookAt(const Vector3<T>& aPosition, const Vector3<T>& aTarget, const Vector3<T>& anUpVector) requires(std::is_floating_point_v<T>)
		{
			const Vector3<T> zAxis = (aTarget - aPosition).Normalized();
			const Vector3<T> xAxis = Vector3<T>::Cross(anUpVector, zAxis).Normalized();
			const Vector3<T> yAxis = Vector3<T>::Cross(zAxis, xAxis).Normalized();

			Matrix3D result;

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
			result.GetCell(0, 3) = -Vector3<T>::Dot(xAxis, aPosition);
			result.GetCell(1, 3) = -Vector3<T>::Dot(yAxis, aPosition);
			result.GetCell(2, 3) = -Vector3<T>::Dot(zAxis, aPosition);
			result.GetCell(3, 3) = T(1);

			return result;
		}

		/// <summary>
		/// Creates a new projection Matrix3D for orthographic view.
		/// </summary>
		/// <param name="aWidth">Width of the viewing volume.</param>
		/// <param name="aHeight">Height of the viewing volume.</param>
		/// <param name="aNearPlaneDistance">Distance to the near view plane.</param>
		/// <param name="aFarPlaneDistance">Distance to the far view plane.</param>
		static constexpr Matrix3D CreateOrthographic(T aWidth, T aHeight, T aNearZPlaneDistance, T aFarZPlaneDistance) requires(std::is_floating_point_v<T>)
		{
			Matrix3D result;

			result.GetCell(0, 0) = T(2) / aWidth;
			result.GetCell(1, 1) = T(2) / aHeight;
			result.GetCell(2, 2) = T(1) / (aFarZPlaneDistance - aNearZPlaneDistance);
			result.GetCell(3, 3) = T(1);

			return result;
		}

		/// <summary>
		/// Creates a customized projection Matrix3D for orthographic view.
		/// </summary>
		/// <param name="aLeft">Minimum X-value of the viewing volume.</param>
		/// <param name="aRight">Maximum X-value of the viewing volume.</param>
		/// <param name="aBottom">Minimum Y-value of the viewing volume.</param>
		/// <param name="aTop">Maximum Y-value of the viewing volume.</param>
		/// <param name="aNearPlaneDistance">Distance to the near view plane.</param>
		/// <param name="aFarPlaneDistance">Distance to the far view plane.</param>
		static constexpr Matrix3D CreateOrthographicOffCenter(T aLeft, T aRight, T aBottom, T aTop, T aNearZPlaneDistance, T aFarZPlaneDistance) requires(std::is_floating_point_v<T>)
		{
			throw std::exception("Needs chirality confirmation."); // See top of file for details.

			Matrix3D result;

			result.GetCell(0, 0) = T(2) / (aRight - aLeft);
			result.GetCell(1, 1) = T(2) / (aTop - aBottom);
			result.GetCell(2, 2) = T(1) / (aFarZPlaneDistance - aNearZPlaneDistance);

			result.GetCell(0, 3) = (aLeft + aRight) / (aLeft - aRight);
			result.GetCell(1, 3) = (aTop + aBottom) / (aBottom - aTop);
			result.GetCell(2, 3) = aNearZPlaneDistance / (aFarZPlaneDistance - aNearZPlaneDistance);
			result.GetCell(3, 3) = T(1);

			return result;
		}

		/// <summary>
		/// Creates a perspective projection Matrix3D from a given field-of-view and aspect-ratio.
		/// </summary>
		/// <param name="aFieldOfView">Field of view in the Y direction, in radians.</param>
		/// <param name="anAspectRatio">Aspect ratio, defined as view space width divided by height.</param>
		/// <param name="aNearPlaneDistance">Distance to the near view plane.</param>
		/// <param name="aFarPlaneDistance">Distance to the far view plane.</param>
		static constexpr Matrix3D CreatePerspectiveFieldOfView(const T& aFieldOfView, const T& anAspectRatio, const T& aNearPlaneDistance, const T& aFarPlaneDistance) requires(std::is_floating_point_v<T>)
		{
			if (aFieldOfView <= T(0) || aFieldOfView >= Math::PiT<T>)
				throw std::out_of_range("aFieldOfView");

			if (aNearPlaneDistance <= T(0))
				throw std::out_of_range("aNearPlaneDistance");

			if (aFarPlaneDistance <= T(0))
				throw std::out_of_range("aFarPlaneDistance");

			if (aNearPlaneDistance >= aFarPlaneDistance)
				throw std::out_of_range("aNearPlaneDistance");

			const T yScale = Math::Cotangent(aFieldOfView / T(2));
			const T xScale = yScale / anAspectRatio;
			const T scaling = aFarPlaneDistance / (aFarPlaneDistance - aNearPlaneDistance);

			Matrix3D result;

			result.GetCell(0, 0) = xScale;
			result.GetCell(1, 1) = yScale;
			result.GetCell(2, 2) = scaling;
			result.GetCell(3, 2) = 1;
			result.GetCell(2, 3) = -scaling * aNearPlaneDistance;
			result.GetCell(3, 3) = 0;

			return result;
		}

		// Todo: Potentially implement CreatePerspectiveOffCenter().

		/// <summary>
		/// Creates a Matrix3D that reflects the coordinate system about the specified plane normal.
		/// </summary>
		/// <param name="aPlaneNormal">The Plane normal about which to create a reflection.</param>
		/// <param name="aDistance">The distance of the Plane along its normal from its origin.</param>
		static constexpr Matrix3D CreateReflection(const Vector3<T> aPlaneNormal, const T aDistance = T(0)) requires(std::is_floating_point_v<T>)
		{
			throw std::exception("Needs chirality confirmation."); // See top of file for details.

			const T a = aPlaneNormal.X;
			const T b = aPlaneNormal.Y;
			const T c = aPlaneNormal.Z;

			const T fa = -T(2) * a;
			const T fb = -T(2) * b;
			const T fc = -T(2) * c;

			Matrix3D result;
			
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

		/// <summary>
		/// Creates a Matrix3D that can be used to rotate a set of points around the x-axis.
		/// </summary>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		static constexpr Matrix3D CreateRotationX(const T& anAngle) requires(std::is_floating_point_v<T>)
		{
			T c = Math::Cosine<T>(anAngle);
			T s = Math::Sine<T>(anAngle);

			Matrix3D result = Matrix3D::Identity();

			result.GetCell(1, 1) = c;
			result.GetCell(2, 1) = s;
			result.GetCell(1, 2) = -s;
			result.GetCell(2, 2) = c;

			return result;
		}

		/// <summary>
		/// Creates a Matrix3D that can be used to rotate a set of points around the y-axis.
		/// </summary>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		static constexpr Matrix3D CreateRotationY(const T& anAngle) requires(std::is_floating_point_v<T>)
		{
			T c = Math::Cosine<T>(anAngle);
			T s = Math::Sine<T>(anAngle);

			Matrix3D result = Matrix3D::Identity();

			result.GetCell(0, 0) = c;
			result.GetCell(2, 0) = -s;
			result.GetCell(0, 2) = s;
			result.GetCell(2, 2) = c;

			return result;
		}

		/// <summary>
		/// Creates a Matrix3D that can be used to rotate a set of points around the z-axis.
		/// </summary>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		static constexpr Matrix3D CreateRotationZ(const T& anAngle) requires(std::is_floating_point_v<T>)
		{
			T c = Math::Cosine<T>(anAngle);
			T s = Math::Sine<T>(anAngle);

			Matrix3D result = Matrix3D::Identity();

			result.GetCell(0, 0) = c;
			result.GetCell(1, 0) = s;
			result.GetCell(0, 1) = -s;
			result.GetCell(1, 1) = c;

			return result;
		}

		/// <summary>
		/// Creates a scaling Matrix3D.
		/// </summary>
		/// <param name="anXScale">The X scaling value.</param>
		/// <param name="aYScale">The Y scaling value.</param>
		/// <param name="aZScale">The Z scaling value.</param>
		static constexpr Matrix3D CreateScale(const T& anXScale, const T& aYScale, const T& aZScale) requires(std::is_floating_point_v<T>)
		{
			Matrix3D result = Matrix3D::Identity();

			result.GetCell(0, 0) = anXScale;
			result.GetCell(1, 1) = aYScale;
			result.GetCell(2, 2) = aZScale;

			return result;
		}

		/// <summary>
		/// Creates a scaling Matrix3D with a center point.
		/// </summary>
		/// <param name="anXScale">The X scaling value.</param>
		/// <param name="aYScale">The Y scaling value.</param>
		/// <param name="aZScale">The Z scaling value.</param>
		/// <param name="aCenterPoint">The center point.</param>
		static constexpr Matrix3D CreateScale(const T& anXScale, const T& aYScale, const T& aZScale, const Vector3<T>& aCenterPoint) requires(std::is_floating_point_v<T>)
		{
			Matrix3D result = Matrix3D::Identity();

			result.GetCell(0, 0) = anXScale;
			result.GetCell(1, 1) = aYScale;
			result.GetCell(2, 2) = aZScale;
			
			result.GetCell(0, 3) = aCenterPoint.X * (T(1) - anXScale);
			result.GetCell(1, 3) = aCenterPoint.Y * (T(1) - aYScale);
			result.GetCell(2, 3) = aCenterPoint.Z * (T(1) - aZScale);

			return result;
		}

		/// <summary>
		/// Creates a scaling Matrix3D.
		/// </summary>
		/// <param name="aScale">The Vector3 containing the amount to scale by on each axis.</param>
		static constexpr Matrix3D CreateScale(const Vector3<T>& aScale) requires(std::is_floating_point_v<T>)
		{
			return CreateScale(aScale.X, aScale.Y, aScale.Z);
		}

		/// <summary>
		/// Creates a scaling Matrix3D with a center point.
		/// </summary>
		/// <param name="aScale">The Vector3 containing the amount to scale by on each axis.</param>
		/// <param name="aCenterPoint">The center point.</param>
		static constexpr Matrix3D CreateScale(const Vector3<T>& aScale, const Vector3<T>& aCenterPoint) requires(std::is_floating_point_v<T>)
		{
			return CreateScale(aScale.X, aScale.Y, aScale.Z, aCenterPoint);
		}

		/// <summary>
		/// Creates a scaling Matrix3D.
		/// </summary>
		/// <param name="aScale">The scaling value.</param>
		static constexpr Matrix3D CreateScale(const T& aScale) requires(std::is_floating_point_v<T>)
		{
			return CreateScale(aScale, aScale, aScale);
		}

		/// <summary>
		/// Creates a scaling Matrix3D with a center point.
		/// </summary>
		/// <param name="aScale">The scaling value.</param>
		/// <param name="aCenterPoint">The center point.</param>
		static constexpr Matrix3D CreateScale(const T& aScale, const Vector3<T>& aCenterPoint) requires(std::is_floating_point_v<T>)
		{
			return CreateScale(aScale, aScale, aScale, aCenterPoint);
		}
		
		/// <summary>
		/// Creates a Matrix3D that flattens geometry into a specified Plane as if casting a shadow from a specified light source.
		/// </summary>
		/// <param name="aLightDirection">The direction from which the light that will cast the shadow is coming.</param>
		/// <param name="aPlaneNormal">The normal of the Plane onto which the new matrix should flatten geometry.</param>
		/// <param name="aPlaneDistance">The distance of the Plane onto which the new matrix should flatten geometry.</param>
		static constexpr Matrix3D CreateShadow(const Vector3<T>& aLightDirection, const Vector3<T>& aPlaneNormal, T aPlaneDistance) requires(std::is_floating_point_v<T>)
		{
			throw std::exception("Needs chirality confirmation."); // See top of file for details.

			const T dot = Vector3<T>::Dot(aPlaneNormal, aLightDirection);
			const T a = -aPlaneNormal.X;
			const T b = -aPlaneNormal.Y;
			const T c = -aPlaneNormal.Z;
			const T d = -aPlaneDistance;

			Matrix3D result;

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

		/// <summary>
		/// Creates a translation Matrix3D.
		/// </summary>
		/// <param name="anX">Value to translate on the x-axis.</param>
		/// <param name="aY">Value to translate on the y-axis.</param>
		/// <param name="aZ">Value to translate on the z-axis.</param>
		static constexpr Matrix3D CreateTranslation(const T& anX, const T& aY, const T& aZ) requires(std::is_floating_point_v<T>)
		{
			Matrix3D matrix = Matrix3D::Identity();

			matrix.GetCell(0, 3) = anX;
			matrix.GetCell(1, 3) = aY;
			matrix.GetCell(2, 3) = aZ;

			return matrix;
		}

		/// <summary>
		/// Creates a translation Matrix3D.
		/// </summary>
		/// <param name="aPosition">The amount to translate in each axis.</param>
		static constexpr Matrix3D CreateTranslation(const Vector3<T>& aPosition) requires(std::is_floating_point_v<T>)
		{
			return CreateTranslation(aPosition.X, aPosition.Y, aPosition.Z);
		}

		static constexpr Matrix3D CreateWorld(const Vector3<T>& aPosition, const Vector3<T>& aForward, const Vector3<T>& anUp)
		{
			const Vector3<T> zAxis = aForward.Normalized();
			const Vector3<T> xAxis = Vector3<T>::Cross(anUp, zAxis).Normalized();
			const Vector3<T> yAxis = Vector3<T>::Cross(zAxis, xAxis);

			Matrix3D result;

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

	public:
		constexpr Matrix3D()
		{

		}

		constexpr Matrix3D(const Matrix<4, 4, T>& aMatrix)
			: myMatrix(aMatrix)
		{ }

		constexpr Matrix3D(const Matrix3D& aMatrix)
			: myMatrix(aMatrix.myMatrix)
		{

		}

		/// <summary>
		/// Gets the backwards vector of the matrix.
		/// </summary>
		/// <returns>The backward matrix.</returns>
		constexpr Vector3<T> Backward() const
		{
			return Vector3<T>({
				-myMatrix.GetCell(0, 2),
				-myMatrix.GetCell(1, 2),
				-myMatrix.GetCell(2, 2)
				});
		}

		/// <summary>
		/// Extracts the scalar, translation, and rotation components from a 3D scale/rotate/translate (SRT) Matrix.
		/// </summary>
		/// <param name="outScale">The scalar component of the transform matrix, expressed as a Vector3.</param>
		/// <param name="outRotation">The rotation component of the transform matrix, expressed as a Quaternion.</param>
		/// <param name="outTranslation">The translation component of the transform matrix, expressed as a Vector3.</param>
		/*void Decompose(Vector3& outScale, Quaternion& outRotation, Vector3& outTranslation)
		{
			outTranslation = GetTranslation();

			outScale.X = Math::Squareroot((M11 * M11) + (M12 * M12) + (M13 * M13));
			outScale.Y = Math::Squareroot((M21 * M21) + (M22 * M22) + (M23 * M23));
			outScale.Z = Math::Squareroot((M31 * M31) + (M32 * M32) + (M33 * M33));

			Matrix rotationMatrix = (*this) * Matrix::InvertCorrect(Matrix::CreateScale(outScale) * Matrix::CreateTranslation(outTranslation));

			outRotation.X = rotationMatrix.GetCell(0, 3);
			outRotation.Y = rotationMatrix.GetCell(1, 3);
			outRotation.Z = rotationMatrix.GetCell(2, 3);
			outRotation.W = rotationMatrix.GetCell(3, 3);
		}*/

		/// <summary>
		/// Calculates the determinant of a Matrix.
		/// </summary>
		/// <remarks>This uses the Laplace expansion method currently.</remarks>
		/// <returns>The Matrix determinant.</returns>
		constexpr T Determinant() const
		{
			return myMatrix.Determinant();
		}

		/// <summary>
		/// Gets the down vector of the matrix.
		/// </summary>
		/// <returns>The down matrix.</returns>
		constexpr Vector3<T> Down() const
		{
			return Vector3<T>({
				-myMatrix.GetCell(0, 1),
				-myMatrix.GetCell(1, 1),
				-myMatrix.GetCell(2, 1)
				});
		}

		/// <summary>
		/// Gets the forward vector of the matrix.
		/// </summary>
		/// <returns>The forward matrix.</returns>
		constexpr Vector3<T> Forward() const
		{
			return Vector3<T>({
				myMatrix.GetCell(0, 2),
				myMatrix.GetCell(1, 2),
				myMatrix.GetCell(2, 2)
				});
		}

		/// <summary>
		/// Get a specific cell value.
		/// </summary>
		/// <param name="aColumn">The zero-based column index.</param>
		/// <param name="aRow">The zero-based row index.</param>
		/// <returns>A reference to the cell value.</returns>
		constexpr T& GetCell(std::size_t aColumn, std::size_t aRow)
		{
			return myMatrix.GetCell(aColumn, aRow);
		}

		/// <summary>
		/// Get a specific cell value.
		/// </summary>
		/// <param name="aColumn">The zero-based column index.</param>
		/// <param name="aRow">The zero-based row index.</param>
		/// <returns>A constant reference to the cell value.</returns>
		constexpr T GetCell(std::size_t aColumn, std::size_t aRow) const
		{
			return myMatrix.GetCell(aColumn, aRow);
		}

		/// <summary>
		/// Gets the matrix translation.
		/// </summary>
		/// <returns>The translation as a Vector3.</returns>
		constexpr Vector3<T> GetTranslation() const
		{
			return Vector3<T>({
				myMatrix.GetCell(0, 3),
				myMatrix.GetCell(1, 3),
				myMatrix.GetCell(2, 3)
				}) / myMatrix.GetCell(3, 3);
		}

		/// <summary>
		/// Calculates the inverse of a Matrix. A slow method, so use it responsibly.
		/// </summary>
		/// <param name="aMatrix">The source matrix.</param>
		/// <returns>The inverse of the Matrix.</returns>
		constexpr Matrix3D Inverse() const
		{
			const std::optional<Matrix<4, 4, T>> inverted = myMatrix.Inverse();
			if (inverted.has_value())
				return Matrix3D(inverted.value());
			else
				return Matrix3D();
		}

		/// <summary>
		/// Calculates the inverse of a Matrix quickly, but not very accurately.
		/// </summary>
		/// <param name="aMatrix">The source matrix.</param>
		/// <returns>The inverse of the Matrix.</returns>
		/*constexpr Matrix InvertFast(const Matrix& aMatrix)
		{
			Matrix invertedMatrix(aMatrix);

			Vector4 translation = invertedMatrix.GetTranslation4();
			invertedMatrix.SetTranslation4(Vector4(0, 0, 0, 1));

			translation *= -1.f;
			translation.W = 1.f;
			invertedMatrix = invertedMatrix.Transpose();
			translation *= invertedMatrix;
			invertedMatrix.SetTranslation4(translation);

			return invertedMatrix;
		}*/

		/// <summary>
		/// Gets the left vector of the matrix.
		/// </summary>
		/// <returns>The left matrix.</returns>
		constexpr Vector3<T> Left() const
		{
			return Vector3<T>({
				-myMatrix.GetCell(0, 0),
				-myMatrix.GetCell(1, 0),
				-myMatrix.GetCell(2, 0)
				});
		}

		/// <summary>
		/// Gets the right vector of the matrix.
		/// </summary>
		/// <returns>The right matrix.</returns>
		constexpr Vector3<T> Right() const
		{
			return Vector3<T>({
				myMatrix.GetCell(0, 0),
				myMatrix.GetCell(1, 0),
				myMatrix.GetCell(2, 0)
				});
		}

		/// <summary>
		/// Sets the matrix translation.
		/// </summary>
		/// <param name="aVector">The value to set the translation to.</param>
		void SetTranslation(const Vector3<T>& aVector)
		{
			myMatrix.GetCell(0, 3) = aVector.X * myMatrix.GetCell(4, 3);
			myMatrix.GetCell(1, 3) = aVector.Y * myMatrix.GetCell(4, 3);
			myMatrix.GetCell(2, 3) = aVector.Z * myMatrix.GetCell(4, 3);
		}

		/// <summary>
		/// Sets the matrix translation.
		/// </summary>
		/// <param name="aVector">The value to set the translation to.</param>
		void SetTranslation4(const Vector4<T>& aVector)
		{
			myMatrix.GetCell(0, 3) = aVector.X;
			myMatrix.GetCell(1, 3) = aVector.Y;
			myMatrix.GetCell(2, 3) = aVector.Z;
			myMatrix.GetCell(3, 3) = aVector.W;
		}

		/// <summary>
		/// Transposes the NRows and NColumns of the matrix.
		/// </summary>
		/// <param name="aMatrix">The source matrix.</param>
		/// <returns>The transposed matrix.</returns>
		constexpr Matrix3D Transposed() const
		{
			return Matrix3D(myMatrix.Transposed());
		}

		/// <summary>
		/// Gets the up vector of the matrix.
		/// </summary>
		/// <returns>The up matrix.</returns>
		constexpr Vector3<T> Up() const
		{
			return Vector3<T>({
				myMatrix.GetCell(0, 1),
				myMatrix.GetCell(1, 1),
				myMatrix.GetCell(2, 1)
				});
		}

	public:
		constexpr operator Matrix<4, 4, T>() const { return myMatrix; }

		constexpr Matrix3D operator*(const Matrix3D& aMatrix) const
		{
			return Matrix3D(myMatrix * aMatrix.myMatrix);
		}

		constexpr friend Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3D<T>& aMatrix)
		{
			return Vector3<T>(Vector4<T>(aVector, T(1)) * aMatrix.myMatrix);
		}

		constexpr friend Vector4<T> operator*(const Vector4<T>& aVector, const Matrix3D<T>& aMatrix)
		{
			return aVector * aMatrix.myMatrix;
		}

		constexpr bool operator==(const Matrix3D& aMatrix) const
		{
			return myMatrix == aMatrix.myMatrix;
		}

		constexpr bool operator!=(const Matrix3D& aMatrix) const
		{
			return myMatrix != aMatrix.myMatrix;
		}

	private:
		Matrix<4, 4, T> myMatrix;
	};
}
