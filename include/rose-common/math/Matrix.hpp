#pragma once

#include "Trigonometry.hpp"

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
		constexpr Matrix<Height, Width, T> Transpose() const
		{
			Matrix<Height, Width, T> transposedMatrix;

			for (std::size_t rowIndex = 0; rowIndex < Height; ++rowIndex)
			{
				for (std::size_t columnIndex = 0; columnIndex < Width; ++columnIndex)
				{
					transposedMatrix.GetCell(rowIndex, columnIndex) = GetCell(columnIndex, rowIndex);
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
}