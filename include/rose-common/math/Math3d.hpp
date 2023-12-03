#pragma once

#include "Matrix.hpp"

namespace RoseCommon::Math
{
	template <typename T>
	class Matrix4x4 : public Matrix<4, 4, T>
	{
	public:


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
