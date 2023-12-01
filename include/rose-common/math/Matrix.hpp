#pragma once

#include <array>
#include <optional>
#include <type_traits>

namespace RoseCommon::Math
{
	template <std::size_t Width, std::size_t Height, typename T>
	class Matrix
	{
	public:
		static constexpr Matrix Identity() requires(Width == Height)
		{
			Matrix identityMatrix;

			for (std::size_t i = 0; i < Width; ++i)
				identityMatrix.GetCell(i, i) = static_cast<T>(1.f);

			return identityMatrix;
		}

	public:
		constexpr Matrix()
		{
			for (std::size_t i = 0; i < (Width * Height); ++i)
				myCells[i] = static_cast<T>(0);
		}

		constexpr Matrix(const std::array<T, Width * Height>& someCells)
		{
			for (std::size_t i = 0; i < (Width * Height); ++i)
				myCells[i] = someCells[i];
		}

	public:
		/// <summary>
		/// Calculates the matrix cofactor.
		/// </summary>
		/// <returns>A square matrix consisting of the determinants of its submatrices, alternatingly inverted.</returns>
		constexpr Matrix Cofactor() const requires(Width == Height && Width > 0)
		{
			Matrix solution;
			
			bool isPositive = true;
			for (std::size_t rowIndex = 0; rowIndex < Height; ++rowIndex)
			{
				for (std::size_t columnIndex = 0; columnIndex < Width; ++columnIndex)
				{
					const auto subMatrix = SubMatrix(columnIndex, rowIndex);
					
					solution.GetCell(columnIndex, rowIndex) =
						static_cast<T>(isPositive ? 1 : -1) *
						subMatrix.Determinant()
						;
					isPositive = !isPositive;
				}
			}
			
			return solution;
		}

		/// <summary>
		/// Calculates the determinant of a Matrix.
		/// </summary>
		/// <remarks>This uses the Laplace expansion method currently.</remarks>
		/// <returns>The Matrix determinant.</returns>
		constexpr T Determinant() const requires(Width == Height && Width > 0)
		{
			if constexpr (Width == 1)
			{
				return GetCell(0, 0);
			}
			else if constexpr (Width == 2)
			{
				return GetCell(0, 0) * GetCell(1, 1) - GetCell(0, 1) * GetCell(1, 0);
			}
			else if constexpr (Width != 0)
			{
				T determinant = 0;
				for (std::size_t i = 0; i < Width; ++i)
				{
					const T factor = GetCell(i, 0);
					const Matrix<Width - 1, Height - 1, T> subMatrix = SubMatrix(i, 0);

					determinant +=
						static_cast<T>((i % 2 == 0) ? 1 : -1) *
						(factor * subMatrix.Determinant())
						;
				}

				return determinant;
			}
		}

		/// <summary>
		/// Get a specific cell value.
		/// </summary>
		/// <param name="aColumn">The zero-based column index.</param>
		/// <param name="aRow">The zero-based row index.</param>
		/// <returns>A reference to the cell value.</returns>
		constexpr T& GetCell(std::size_t aColumn, std::size_t aRow)
		{
			return myCells[(aRow * Width) + aColumn];
		}

		/// <summary>
		/// Get a specific cell value.
		/// </summary>
		/// <param name="aColumn">The zero-based column index.</param>
		/// <param name="aRow">The zero-based row index.</param>
		/// <returns>A constant reference to the cell value.</returns>
		constexpr T GetCell(std::size_t aColumn, std::size_t aRow) const
		{
			return myCells[(aRow * Width) + aColumn];
		}

		/// <summary>
		/// Calculates the inverse of a Matrix. A slow method, so use it responsibly.
		/// </summary>
		/// <param name="aMatrix">The source matrix.</param>
		/// <returns>The inverse of the Matrix.</returns>
		constexpr std::optional<Matrix> Invert() const requires(std::is_floating_point_v<T> && Width == Height && Width > 0)
		{
			const T determinant = Determinant();
			if (determinant == static_cast<T>(0))
				return std::optional<Matrix>();

			const T reciprocalDeterminant = static_cast<T>(1) / determinant;

			if constexpr (Width == 2)
			{
				return Matrix({
					reciprocalDeterminant * GetCell(1, 1),
					reciprocalDeterminant * -GetCell(1, 0),
					reciprocalDeterminant * -GetCell(0, 1),
					reciprocalDeterminant * GetCell(0, 0)
					});
			}
			else
			{
				return reciprocalDeterminant * Cofactor().Transpose();
			}
		}

		/// <summary>
		/// Calculates the matrix minor.
		/// </summary>
		/// <returns>A square matrix consisting of the determinants of its submatrices.</returns>
		constexpr Matrix Minor() const requires(std::is_floating_point_v<T>&& Width == Height && Width > 0)
		{
			Matrix solution;

			for (std::size_t rowIndex = 0; rowIndex < Height; ++rowIndex)
			{
				for (std::size_t columnIndex = 0; columnIndex < Width; ++columnIndex)
				{
					const auto subMatrix = SubMatrix(columnIndex, rowIndex);
					solution.GetCell(columnIndex, rowIndex) = subMatrix.Determinant();
				}
			}

			return solution;
		}

		/// <summary>
		/// Transposes the NRows and NColumns of the matrix.
		/// </summary>
		/// <param name="aMatrix">The source matrix.</param>
		/// <returns>The transposed matrix.</returns>
		constexpr Matrix Transpose() const requires(Width == Height)
		{
			Matrix transposedMatrix;

			for (std::size_t rowIndex = 0; rowIndex < Height; ++rowIndex)
			{
				for (std::size_t columnIndex = 0; columnIndex < Width; ++columnIndex)
				{
					transposedMatrix.GetCell(columnIndex, rowIndex) = GetCell(rowIndex, columnIndex);
				}
			}

			return transposedMatrix;
		}

	public:
		template <std::size_t _Width>
		constexpr Matrix<Height, _Width, T> operator*(const Matrix<Width, _Width, T>& aMatrix) const
		{
			Matrix<Height, _Width, T> result;

			for (std::size_t rowIndex = 0; rowIndex < Height; ++rowIndex)
			{
				for (std::size_t columnIndex = 0; columnIndex < _Width; ++columnIndex)
				{
					for (std::size_t memberIndex = 0; memberIndex < Width; ++memberIndex)
					{
						T& resultCell = result.GetCell(columnIndex, rowIndex);
						const T& lhvCell = GetCell(memberIndex, rowIndex);
						const T& rhvCell = aMatrix.GetCell(columnIndex, memberIndex);

						resultCell += lhvCell * rhvCell;
					}
				}
			}

			return result;
		}

		constexpr friend Matrix operator*(T aScalar, Matrix aMatrix)
		{
			for (T& cell : aMatrix.myCells)
				cell *= aScalar;
			return aMatrix;
		}

		constexpr bool operator==(const Matrix& aMatrix) const
		{
			for (std::size_t i = 0; i < (Width * Height); ++i)
			{
				if (myCells[i] != aMatrix.myCells[i])
					return false;
			}

			return true;
		}

		constexpr bool operator!=(const Matrix& aMatrix) const
		{
			return !operator==(aMatrix);
		}

	private:
		constexpr Matrix<Width - 1, Height - 1, T> SubMatrix(std::size_t aColumn, std::size_t aRow) const
		{
			Matrix<Width - 1, Height - 1, T> subMatrix;
			for (std::size_t rowIndex = 0; rowIndex < Height - 1; ++rowIndex)
			{
				for (std::size_t columnIndex = 0; columnIndex < Width - 1; ++columnIndex)
				{
					subMatrix.GetCell(columnIndex, rowIndex) =
						GetCell(
							columnIndex >= aColumn ? columnIndex + 1 : columnIndex,
							rowIndex >= aRow ? rowIndex + 1 : rowIndex
						);
				}
			}
			return subMatrix;
		};

	private:
		T myCells[Width * Height];
	};

	template <typename T>
	class Matrix4x4 : public Matrix<4, 4, T>
	{
	public:
		/// <summary>
		/// Creates a Matrix that rotates around an arbitrary axis.
		/// </summary>
		/// <param name="anAxis">A normalized Vector3 specifying the axis.</param>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateFromAxisAngle(const Vector3& anAxis, const Float32& anAngle) requires(NRows == 4 && NColumns == 4)
		{
			Float32 c = static_cast<Float32>(Math::Cosine(anAngle));
			Float32 s = static_cast<Float32>(Math::Sine(anAngle));
			Float32 t = static_cast<Float32>(1.0f) - c;

			Matrix rotation(Matrix::Identity);

			rotation.M11 = c + anAxis.X * anAxis.X * t;
			rotation.M22 = c + anAxis.Y * anAxis.Y * t;
			rotation.M33 = c + anAxis.Z * anAxis.Z * t;

			Float32 tmp1 = anAxis.X * anAxis.Y * t;
			Float32 tmp2 = anAxis.Z * s;

			rotation.M21 = tmp1 + tmp2;
			rotation.M12 = tmp1 - tmp2;

			tmp1 = anAxis.X * anAxis.Z * t;
			tmp2 = anAxis.Y * s;
			rotation.M31 = tmp1 - tmp2;
			rotation.M13 = tmp1 + tmp2;

			tmp1 = anAxis.Y * anAxis.Z * t;
			tmp2 = anAxis.X * s;
			rotation.M32 = tmp1 + tmp2;
			rotation.M23 = tmp1 - tmp2;

			return rotation;
		}*/

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
		/*static Matrix CreateLookAt(const Vector3& aPosition, const Vector3& aTarget, const Vector3& anUpVector) requires(NRows == 4 && NColumns == 4)
		{
			Vector3 usedTarget = aTarget;

			if (aPosition == usedTarget)
				usedTarget = aPosition + Vector3::Forward;

			Vector3 zAxis = (usedTarget - aPosition).Normalized();
			Vector3 xAxis = Vector3::Cross(anUpVector, zAxis).Normalized();
			Vector3 yAxis = Vector3::Cross(zAxis, xAxis);

			return Matrix::Invert(Matrix(
				xAxis.X, yAxis.X, zAxis.X, 0,
				xAxis.Y, yAxis.Y, zAxis.Y, 0,
				xAxis.Z, yAxis.Z, zAxis.Z, 0,
				-Vector3::Dot(xAxis, aPosition), -Vector3::Dot(yAxis, aPosition), -Vector3::Dot(zAxis, aPosition), 1
			));
		}*/

		/// <summary>
		/// Creates a new projection <see cref="Matrix"/> for orthographic view.
		/// </summary>
		/// <param name="width">Width of the viewing volume.</param>
		/// <param name="height">Height of the viewing volume.</param>
		/// <param name="zNearPlane">Depth of the near plane.</param>
		/// <param name="zFarPlane">Depth of the far plane.</param>
		/// <returns>The new projection Matrix for orthographic view.</returns>
		/*static Matrix CreateOrthographic(Float32 aWidth, Float32 aHeight, Float32 aNearZPlane, Float32 aFarZPlane) requires(NRows == 4 && NColumns == 4)
		{
			Matrix matrix;
			matrix.M11 = 2.f / aWidth;
			matrix.M22 = 2.f / aHeight;
			matrix.M33 = 2.f / (aFarZPlane - aNearZPlane);
			matrix.M44 = 1.f;
			return matrix;
		}*/

		/// <summary>
		/// Creates a perspective projection Matrix based on a field of view and returns by value.
		/// </summary>
		/// <param name="aFieldOfView">Field of view in the Y direction, in radians.</param>
		/// <param name="anAspectRatio">Aspect ratio, defined as view space width divided by height.</param>
		/// <param name="aNearPlane">Distance to the near view plane.</param>
		/// <param name="aFarPlane">Distance to the far view plane.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreatePerspectiveFieldOfView(const Float32& aFieldOfView, const Float32& anAspectRatio, const Float32& aNearPlane, const Float32& aFarPlane) requires(NRows == 4 && NColumns == 4)
		{
			Matrix proj;
			Float32 sinFov, cosFov, height, width;

			sinFov = static_cast<Float32>(Math::Sine(0.5 * static_cast<double>(aFieldOfView)));
			cosFov = static_cast<Float32>(Math::Cosine(0.5 * static_cast<double>(aFieldOfView)));

			height = cosFov / sinFov;
			width = height / anAspectRatio;

			Float32 scaling = aFarPlane / (aFarPlane - aNearPlane);

			proj.M11 = width;
			proj.M22 = height;
			proj.M33 = scaling;
			proj.M34 = static_cast<Float32>(1);
			proj.M43 = -scaling * aNearPlane;
			proj.M44 = static_cast<Float32>(0);

			return proj;
		}*/

		/// <summary>
		/// Creates a Matrix that reflects the coordinate system about the specified plane normal.
		/// </summary>
		/// <param name="aPlaneNormal">The normal about which to create a reflection.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateReflectionAroundAxis(const Vector3& aPlaneNormal) requires(NRows == 4 && NColumns == 4)
		{
			Matrix reflMatrix;

			Float32 one = static_cast<Float32>(1);
			Float32 two = static_cast<Float32>(2);

			reflMatrix.M11 = one - two * (aPlaneNormal.X * aPlaneNormal.X);
			reflMatrix.M12 = -two * (aPlaneNormal.X * aPlaneNormal.Y);
			reflMatrix.M13 = -two * (aPlaneNormal.X * aPlaneNormal.Z);

			reflMatrix.M21 = -two * (aPlaneNormal.Y * aPlaneNormal.X);
			reflMatrix.M22 = one - two * (aPlaneNormal.Y * aPlaneNormal.Y);
			reflMatrix.M23 = -one * (aPlaneNormal.Y * aPlaneNormal.Z);

			reflMatrix.M31 = -two * (aPlaneNormal.Z * aPlaneNormal.X);
			reflMatrix.M32 = -two * (aPlaneNormal.Z * aPlaneNormal.Y);
			reflMatrix.M33 = one - two * (aPlaneNormal.Z * aPlaneNormal.Z);

			return reflMatrix;
		}*/

		/// <summary>
		/// Creates a Matrix that can be used to rotate a set of points around the x-axis.
		/// </summary>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateRotationX(const Float32& anAngle) requires(NRows == 4 && NColumns == 4)
		{
			Float32 c = static_cast<Float32>(Math::Cosine(anAngle));
			Float32 s = static_cast<Float32>(Math::Sine(anAngle));

			Matrix rotation(Matrix::Identity);
			rotation.M22 = c;
			rotation.M23 = s;
			rotation.M32 = -s;
			rotation.M33 = c;
			return rotation;
		}*/

		/// <summary>
		/// Creates a Matrix that can be used to rotate a set of points around the y-axis.
		/// </summary>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateRotationY(const Float32& anAngle) requires(NRows == 4 && NColumns == 4)
		{
			Float32 c = static_cast<Float32>(Math::Cosine(anAngle));
			Float32 s = static_cast<Float32>(Math::Sine(anAngle));

			Matrix rotation(Matrix::Identity);
			rotation.M11 = c;
			rotation.M13 = -s;
			rotation.M31 = s;
			rotation.M33 = c;
			return rotation;
		}*/

		/// <summary>
		/// Creates a Matrix that can be used to rotate a set of points around the z-axis.
		/// </summary>
		/// <param name="anAngle">The amount, in radians, in which to rotate.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateRotationZ(const Float32& anAngle) requires(NRows == 4 && NColumns == 4)
		{
			Float32 c = static_cast<Float32>(Math::Cosine(anAngle));
			Float32 s = static_cast<Float32>(Math::Sine(anAngle));

			Matrix rotation(Matrix::Identity);
			rotation.M11 = c;
			rotation.M12 = s;
			rotation.M21 = -s;
			rotation.M22 = c;
			return rotation;
		}*/

		/// <summary>
		/// Creates a scaling Matrix.
		/// </summary>
		/// <param name="aScale">The scaling value.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateScale(const Float32& aScale) requires(NRows == 4 && NColumns == 4)
		{
			return CreateScale(Vector3(aScale, aScale, aScale));
		}*/

		/// <summary>
		/// Creates a scaling Matrix.
		/// </summary>
		/// <param name="anXScale">The X scaling value.</param>
		/// <param name="aYScale">The Y scaling value.</param>
		/// <param name="aZScale">The Z scaling value.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateScale(const Float32& anXScale, const Float32& aYScale, const Float32& aZScale) requires(NRows == 4 && NColumns == 4)
		{
			return CreateScale(Vector3(anXScale, aYScale, aZScale));
		}*/

		/// <summary>
		/// Creates a scaling Matrix.
		/// </summary>
		/// <param name="aScale">A Vector3 containing the X, Y, and Z scaling values.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateScale(const Vector3& aScale) requires(NRows == 4 && NColumns == 4)
		{
			Matrix matrix(Matrix::Identity);

			matrix.M11 = aScale.X;
			matrix.M22 = aScale.Y;
			matrix.M33 = aScale.Z;

			return matrix;
		}*/

		/// <summary>
		/// Creates a translation Matrix.
		/// </summary>
		/// <param name="anX">Value to translate on the x-axis.</param>
		/// <param name="aY">Value to translate on the y-axis.</param>
		/// <param name="aZ">Value to translate on the z-axis.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateTranslation(const Float32& anX, const Float32& aY, const Float32& aZ) requires(NRows == 4 && NColumns == 4)
		{
			return CreateTranslation(Vector3(anX, aY, aZ));
		}*/

		/// <summary>
		/// Creates a translation Matrix.
		/// </summary>
		/// <param name="aTranslation">Amounts to translate on the X, Y, and Z axis.</param>
		/// <returns>The resulting Matrix.</returns>
		/*static Matrix CreateTranslation(const Vector3& aTranslation) requires(NRows == 4 && NColumns == 4)
		{
			Matrix matrix(Matrix::Identity);

			matrix.M41 = aTranslation.X;
			matrix.M42 = aTranslation.Y;
			matrix.M43 = aTranslation.Z;

			return matrix;
		}*/

	public:
		/// <summary>
		/// Gets the backwards vector of the matrix.
		/// </summary>
		/// <returns>The backward matrix.</returns>
		/*Vector3 Backward() const
		{
			return -Forward();
		}*/

		/// <summary>
		/// Extracts the scalar, translation, and rotation components from a 3D scale/rotate/translate (SRT) Matrix.
		/// </summary>
		/// <param name="aScaleOut">The scalar component of the transform matrix, expressed as a Vector3.</param>
		/// <param name="aRotationOut">The rotation component of the transform matrix, expressed as a Quaternion.</param>
		/// <param name="aTranslationOut">The translation component of the transform matrix, expressed as a Vector3.</param>
		/*void Decompose(Vector3& aScaleOut, Quaternion& aRotationOut, Vector3& aTranslationOut) requires(NRows == 4 && NColumns == 4)
		{
			aTranslationOut = GetTranslation();

			aScaleOut.X = Math::Squareroot((M11 * M11) + (M12 * M12) + (M13 * M13));
			aScaleOut.Y = Math::Squareroot((M21 * M21) + (M22 * M22) + (M23 * M23));
			aScaleOut.Z = Math::Squareroot((M31 * M31) + (M32 * M32) + (M33 * M33));

			Matrix rotationMatrix = (*this) * Matrix::InvertCorrect(Matrix::CreateScale(aScaleOut) * Matrix::CreateTranslation(aTranslationOut));

			aRotationOut.X = rotationMatrix.GetCell(0, 3);
			aRotationOut.Y = rotationMatrix.GetCell(1, 3);
			aRotationOut.Z = rotationMatrix.GetCell(2, 3);
			aRotationOut.W = rotationMatrix.GetCell(3, 3);
		}*/

		/// <summary>
		/// Gets the down vector of the matrix.
		/// </summary>
		/// <returns>The down matrix.</returns>
		/*Vector3 Down() const
		{
			return -Up();
		}*/

		/// <summary>
		/// Gets the forward vector of the matrix.
		/// </summary>
		/// <returns>The forward matrix.</returns>
		/*Vector3 Forward() const
		{
			return Vector3(M31, M32, M33);
		}*/

		/// <summary>
		/// Gets the matrix translation.
		/// </summary>
		/// <returns>The translation as a 1x3 Matrix.</returns>
		/*constexpr Matrix<1, 3, T> GetTranslation() const requires(NRows == 4 && NRows == NColumns)
		{
			return Matrix<1, 3, T>({
				GetCell(3, 0),
				GetCell(3, 1),
				GetCell(3, 2)
				});
		}*/

		/// <summary>
		/// Calculates the inverse of a Matrix quickly, but not very accurately.
		/// </summary>
		/// <param name="aMatrix">The source matrix.</param>
		/// <returns>The inverse of the Matrix.</returns>
		/*constexpr Matrix InvertFast(const Matrix& aMatrix) requires(std::is_floating_point_v<T> && NRows == 4 && NColumns == 4)
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
		/*Vector3 Left() const
		{
			return -Right();
		}*/

		/// <summary>
		/// Gets the right vector of the matrix.
		/// </summary>
		/// <returns>The right matrix.</returns>
		/*Vector3 Right() const
		{
			return Vector3(M11, M12, M13);
		}*/

		/// <summary>
		/// Sets the matrix translation.
		/// </summary>
		/// <param name="aVector">The value to set the translation to.</param>
		/*void SetTranslation(const Vector3& aVector)
		{
			M41 = aVector.X;
			M42 = aVector.Y;
			M43 = aVector.Z;
		}*/

		/// <summary>
		/// Sets the matrix translation.
		/// </summary>
		/// <param name="aVector">The value to set the translation to.</param>
		/*void SetTranslation4(const Vector4& aVector)
		{
			M41 = aVector.X;
			M42 = aVector.Y;
			M43 = aVector.Z;
			M44 = aVector.W;
		}*/

		/// <summary>
		/// Gets the up vector of the matrix.
		/// </summary>
		/// <returns>The up matrix.</returns>
		/*Vector3 Up() const
		{
			return Vector3(M21, M22, M23);
		}*/
	};
}