#pragma once

#include "Matrix.hpp"
#include "Trigonometry.hpp"
#include "Vector.hpp"

/// <summary>
/// Provides creation functions for left-handed matrices.
/// </summary>
namespace RoseCommon::Math
{
	template <typename T>
	struct MakeMatrix
	{
		/// <summary>
		/// Creates a Matrix that rotates around an arbitrary axis.
		/// </summary>
		/// <param name="anAxis">A normalized Vector3 specifying the axis.</param>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		/// <returns>The resulting Matrix.</returns>
		static constexpr Matrix<4, 4, T> FromAxisAngle(const Vector3<T>& anAxis, const T& anAngle) requires(std::is_floating_point_v<T>)
		{
			T c = Math::Cosine<T>(anAngle);
			T s = Math::Sine<T>(anAngle);
			T t = static_cast<T>(1) - c;

			Matrix<4, 4, T> rotation = Matrix<4, 4, T>::Identity();

			rotation.GetCell(0, 0) = c + anAxis.X * anAxis.X * t;
			rotation.GetCell(1, 1) = c + anAxis.Y * anAxis.Y * t;
			rotation.GetCell(2, 2) = c + anAxis.Z * anAxis.Z * t;

			T tmp1 = anAxis.X * anAxis.Y * t;
			T tmp2 = anAxis.Z * s;

			rotation.GetCell(0, 1) = tmp1 + tmp2;
			rotation.GetCell(1, 0) = tmp1 - tmp2;

			tmp1 = anAxis.X * anAxis.Z * t;
			tmp2 = anAxis.Y * s;
			rotation.GetCell(0, 2) = tmp1 - tmp2;
			rotation.GetCell(2, 0) = tmp1 + tmp2;

			tmp1 = anAxis.Y * anAxis.Z * t;
			tmp2 = anAxis.X * s;
			rotation.GetCell(1, 2) = tmp1 + tmp2;
			rotation.GetCell(2, 1) = tmp1 - tmp2;

			return rotation;
		}

		/// <summary>
		/// Creates a new rotation <see cref="Matrix"/> from a <see cref="Quaternion"/>.
		/// </summary>
		/// <param name="quaternion"><see cref="Quaternion"/> of rotation moment.</param>
		/// <param name="result">The rotation <see cref="Matrix"/> as an output parameter.</param>
		/*static Matrix CreateFromQuaternion(const Quaternion& aQuaternion) requires(NRows == 4 && NColumns == 4)
		{
			Matrix result;

			float num9 = quaternion.X * quaternion.X;
			float num8 = quaternion.Y * quaternion.Y;
			float num7 = quaternion.Z * quaternion.Z;
			float num6 = quaternion.X * quaternion.Y;
			float num5 = quaternion.Z * quaternion.W;
			float num4 = quaternion.Z * quaternion.X;
			float num3 = quaternion.Y * quaternion.W;
			float num2 = quaternion.Y * quaternion.Z;
			float num = quaternion.X * quaternion.W;
			result.M11 = 1.f - (2.f * (num8 + num7));
			result.M12 = 2.f * (num6 + num5);
			result.M13 = 2.f * (num4 - num3);
			result.M14 = 0.f;
			result.M21 = 2.f * (num6 - num5);
			result.M22 = 1.f - (2.f * (num7 + num9));
			result.M23 = 2.f * (num2 + num);
			result.M24 = 0.f;
			result.M31 = 2.f * (num4 + num3);
			result.M32 = 2.f * (num2 - num);
			result.M33 = 1.f - (2.f * (num8 + num9));
			result.M34 = 0.f;
			result.M41 = 0.f;
			result.M42 = 0.f;
			result.M43 = 0.f;
			result.M44 = 1.f;

			return result;
		}*/

		/// <summary>
		/// Creates a view Matrix, turned towards a specific position.
		/// </summary>
		/// <param name="aPosition">The position of the camera.</param>
		/// <param name="aTarget">The target towards which the camera is pointing.</param>
		/// <param name="anUpVector">The direction that is "up" from the camera's point of view.</param>
		/// <returns>The resulting Matrix.</returns>
		static constexpr Matrix<4, 4, T> LookAt(const Vector3<T>& aPosition, const Vector3<T>& aTarget, const Vector3<T>& anUpVector) requires(std::is_floating_point_v<T>)
		{
			const Vector3<T> zAxis = (aTarget - aPosition).Normalized();
			const Vector3<T> xAxis = Vector3<T>::Cross(anUpVector, zAxis).Normalized();
			const Vector3<T> yAxis = Vector3<T>::Cross(zAxis, xAxis).Normalized();

			return Matrix<4, 4, T>({
				xAxis.X, xAxis.Y, xAxis.Z, static_cast<T>(0),
				yAxis.X, yAxis.Y, yAxis.Z, static_cast<T>(0),
				zAxis.X, zAxis.Y, zAxis.Z, static_cast<T>(0),
				aPosition.X, aPosition.Y, aPosition.Z, static_cast<T>(1)
				});
		}

		/// <summary>
		/// Creates a new projection <see cref="Matrix"/> for orthographic view.
		/// </summary>
		/// <param name="width">Width of the viewing volume.</param>
		/// <param name="height">Height of the viewing volume.</param>
		/// <param name="zNearPlane">Depth of the near plane.</param>
		/// <param name="zFarPlane">Depth of the far plane.</param>
		/// <returns>The new projection Matrix for orthographic view.</returns>
		static constexpr Matrix<4, 4, T> Orthographic(T aWidth, T aHeight, T aNearZPlane, T aFarZPlane) requires(std::is_floating_point_v<T>)
		{
			Matrix<4, 4, T> matrix;
			matrix.GetCell(0, 0) = 2 / aWidth;
			matrix.GetCell(1, 1) = 2 / aHeight;
			matrix.GetCell(2, 2) = 2 / (aFarZPlane - aNearZPlane);
			matrix.GetCell(3, 3) = 1;
			return matrix;
		}

		/// <summary>
		/// Creates a perspective projection Matrix based on a field of view and returns by value.
		/// </summary>
		/// <param name="aFieldOfView">Field of view in the Y direction, in radians.</param>
		/// <param name="anAspectRatio">Aspect ratio, defined as view space width divided by height.</param>
		/// <param name="aNearPlane">Distance to the near view plane.</param>
		/// <param name="aFarPlane">Distance to the far view plane.</param>
		/// <returns>The resulting Matrix.</returns>
		static constexpr Matrix<4, 4, T> PerspectiveFieldOfView(const T& aFieldOfView, const T& anAspectRatio, const T& aNearPlane, const T& aFarPlane) requires(std::is_floating_point_v<T>)
		{
			Matrix<4, 4, T> proj;
			T sinFov, cosFov, height, width;

			sinFov = Math::Sine<T>(T(0.5) * aFieldOfView);
			cosFov = Math::Cosine<T>(T(0.5) * aFieldOfView);

			height = cosFov / sinFov;
			width = height / anAspectRatio;

			T scaling = aFarPlane / (aFarPlane - aNearPlane);

			proj.GetCell(0, 0) = width;
			proj.GetCell(1, 1) = height;
			proj.GetCell(2, 2) = scaling;
			proj.GetCell(3, 2) = 1;
			proj.GetCell(2, 3) = -scaling * aNearPlane;
			proj.GetCell(3, 3) = 0;

			return proj;
		}

		/// <summary>
		/// Creates a Matrix that reflects the coordinate system about the specified plane normal.
		/// </summary>
		/// <param name="aPlaneNormal">The normal about which to create a reflection.</param>
		/// <returns>The resulting Matrix.</returns>
		static constexpr Matrix<4, 4, T> ReflectionAroundAxis(T aPlaneNormalX, T aPlaneNormalY, T aPlaneNormalZ) requires(std::is_floating_point_v<T>)
		{
			Matrix<4, 4, T> reflMatrix;

			T one = static_cast<T>(1);
			T two = static_cast<T>(2);

			reflMatrix.GetCell(0, 0) = one - two * (aPlaneNormalX * aPlaneNormalX);
			reflMatrix.GetCell(1, 0) = -two * (aPlaneNormalX * aPlaneNormalY);
			reflMatrix.GetCell(2, 0) = -two * (aPlaneNormalX * aPlaneNormalZ);

			reflMatrix.GetCell(0, 1) = -two * (aPlaneNormalY * aPlaneNormalX);
			reflMatrix.GetCell(1, 1) = one - two * (aPlaneNormalY * aPlaneNormalY);
			reflMatrix.GetCell(2, 1) = -one * (aPlaneNormalY * aPlaneNormalZ);

			reflMatrix.GetCell(0, 2) = -two * (aPlaneNormalZ * aPlaneNormalX);
			reflMatrix.GetCell(1, 2) = -two * (aPlaneNormalZ * aPlaneNormalY);
			reflMatrix.GetCell(2, 2) = one - two * (aPlaneNormalZ * aPlaneNormalZ);

			return reflMatrix;
		}

		/// <summary>
		/// Creates a Matrix that can be used to rotate a set of points around the x-axis.
		/// </summary>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		/// <returns>The resulting Matrix.</returns>
		static constexpr Matrix<4, 4, T> RotationX(const T& anAngle) requires(std::is_floating_point_v<T>)
		{
			T c = Math::Cosine<T>(anAngle);
			T s = Math::Sine<T>(anAngle);

			Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();

			matrix.GetCell(1, 1) = c;
			matrix.GetCell(2, 1) = s;
			matrix.GetCell(1, 2) = -s;
			matrix.GetCell(2, 2) = c;

			return matrix;
		}

		/// <summary>
		/// Creates a Matrix that can be used to rotate a set of points around the y-axis.
		/// </summary>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		/// <returns>The resulting Matrix.</returns>
		static constexpr Matrix<4, 4, T> RotationY(const T& anAngle) requires(std::is_floating_point_v<T>)
		{
			T c = Math::Cosine<T>(anAngle);
			T s = Math::Sine<T>(anAngle);

			Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();

			matrix.GetCell(0, 0) = c;
			matrix.GetCell(2, 0) = -s;
			matrix.GetCell(0, 2) = s;
			matrix.GetCell(2, 2) = c;

			return matrix;
		}

		/// <summary>
		/// Creates a Matrix that can be used to rotate a set of points around the z-axis.
		/// </summary>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		/// <returns>The resulting Matrix.</returns>
		static constexpr Matrix<4, 4, T> RotationZ(const T& anAngle) requires(std::is_floating_point_v<T>)
		{
			T c = Math::Cosine<T>(anAngle);
			T s = Math::Sine<T>(anAngle);

			Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();

			matrix.GetCell(0, 0) = c;
			matrix.GetCell(1, 0) = s;
			matrix.GetCell(0, 1) = -s;
			matrix.GetCell(1, 1) = c;

			return matrix;
		}

		/// <summary>
		/// Creates a scaling Matrix.
		/// </summary>
		/// <param name="aScale">The scaling value.</param>
		/// <returns>The resulting Matrix.</returns>
		static constexpr Matrix<4, 4, T> Scale(const T& aScale) requires(std::is_floating_point_v<T>)
		{
			Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();

			matrix.GetCell(0, 0) = aScale;
			matrix.GetCell(1, 1) = aScale;
			matrix.GetCell(2, 2) = aScale;

			return matrix;
		}

		/// <summary>
		/// Creates a scaling Matrix.
		/// </summary>
		/// <param name="anXScale">The X scaling value.</param>
		/// <param name="aYScale">The Y scaling value.</param>
		/// <param name="aZScale">The Z scaling value.</param>
		/// <returns>The resulting 4x4 matrix.</returns>
		static constexpr Matrix<4, 4, T> Scale(const T& anXScale, const T& aYScale, const T& aZScale) requires(std::is_floating_point_v<T>)
		{
			Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();

			matrix.GetCell(0, 0) = anXScale;
			matrix.GetCell(1, 1) = aYScale;
			matrix.GetCell(2, 2) = aZScale;

			return matrix;
		}

		/// <summary>
		/// Creates a translation Matrix.
		/// </summary>
		/// <param name="anX">Value to translate on the x-axis.</param>
		/// <param name="aY">Value to translate on the y-axis.</param>
		/// <param name="aZ">Value to translate on the z-axis.</param>
		/// <returns>The resulting Matrix.</returns>
		static constexpr Matrix<4, 4, T> Translation(const T& anX, const T& aY, const T& aZ) requires(std::is_floating_point_v<T>)
		{
			Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();

			matrix.GetCell(0, 3) = anX;
			matrix.GetCell(1, 3) = aY;
			matrix.GetCell(2, 3) = aZ;

			return matrix;
		}
	};
}