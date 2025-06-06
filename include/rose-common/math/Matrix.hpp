#pragma once

#include "../RoseCommon_Namespace.hpp"

#include <array>
#include <optional>
#include <stdexcept>
#include <type_traits>

namespace ROSECOMMON_MATH_NAMESPACE
{
	template <std::size_t Width, std::size_t Height, typename T>
	class MatrixT
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
		 * @brief Create an identity matrix for the chosen type and dimension.
		 * @return The identity matrix.
		 */
		static constexpr MatrixT Identity() requires(Width == Height);

		#pragma endregion

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize an all-zero matrix.
		 */
		constexpr MatrixT();

		/**
		 * @brief Initialize with an array of cell-data.
		 * @param someCells A row-major array of cell-data to initialize with.
		 */
		constexpr MatrixT(const std::array<T, Width* Height>& someCells);

		#pragma endregion

		//--------------------------------------------------
		// * Properties
		//--------------------------------------------------
		#pragma region Properties

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
		constexpr const T& GetCell(std::size_t aColumn, std::size_t aRow) const;

		#pragma endregion

		//--------------------------------------------------
		// * Methods
		//--------------------------------------------------
		#pragma region Methods

		/**
		 * @brief Calculate the matrix cofactor, a square matrix consisting of the determinants of its submatrices, alternatingly inverted.
		 *        Requires the matrix to be square.
		 * @return The matrix cofactor.
		 */
		constexpr MatrixT Cofactor() const requires(Width == Height && Width > 0);

		/**
		 * @brief Calculate the matrix's determinant.
		 *        Requires the matrix to be square.
		 *        The determinant is currently calculated using the Laplace expansion method.
		 * @return The matrix determinant.
		 */
		constexpr T Determinant() const requires(Width == Height && Width > 0);

		/**
		 * @brief Calculate the matrix inverse.
		 * @return The inverse of the matrix.
		 */
		constexpr std::optional<MatrixT> Inverse() const requires(std::is_floating_point_v<T>&& Width == Height && Width > 0);

		/**
		 * @brief Calculate the matrix's minor. The square matrix consisting of the determinants of its submatrices.
		 *        https://en.wikipedia.org/wiki/Minor_(linear_algebra)
		 *        Requires the matrix to be square.
		 * @return The minor matrix.
		 */
		constexpr MatrixT Minor() const requires(std::is_floating_point_v<T>&& Width == Height && Width > 0);

		/**
		 * @brief Transpose the rows and columns of the matrix.
		 * @return The transposed matrix.
		 */
		constexpr MatrixT<Height, Width, T> Transposed() const;

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		/**
		 * @brief Multiply a matrix with another.
		          The number of columns in the first matrix must be equal to the number of rows in the second.
		 * @tparam _Width The number of columns in the second matrix.
		 * @param aMatrix The matrix to multiply with.
		 * @return The product of the matrix multiplication.
		 */
		template <std::size_t _Width>
		constexpr MatrixT<_Width, Height, T> operator*(const MatrixT<_Width, Width, T>& aMatrix) const;

		constexpr bool operator==(const MatrixT& aMatrix) const;
		constexpr bool operator!=(const MatrixT& aMatrix) const;

		#pragma endregion

	private:
		constexpr MatrixT<Width - 1, Height - 1, T> SubMatrix(std::size_t aColumn, std::size_t aRow) const;

	private:
		T myCells[Width * Height];
	};

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr MatrixT<Width, Height, T> MatrixT<Width, Height, T>::Identity() requires(Width == Height)
	{
		MatrixT identityMatrix;

		for (std::size_t i = 0; i < Width; ++i)
			identityMatrix.GetCell(i, i) = static_cast<T>(1.f);

		return identityMatrix;
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr MatrixT<Width, Height, T>::MatrixT()
	{
		for (std::size_t i = 0; i < (Width * Height); ++i)
			myCells[i] = static_cast<T>(0);
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr MatrixT<Width, Height, T>::MatrixT(const std::array<T, Width * Height>& someCells)
	{
		for (std::size_t i = 0; i < (Width * Height); ++i)
			myCells[i] = someCells[i];
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr T& MatrixT<Width, Height, T>::GetCell(std::size_t aColumn, std::size_t aRow)
	{
		if (aColumn >= Width || aRow >= Height)
			throw std::out_of_range("Row or column indices out of range.");

		return myCells[(aRow * Width) + aColumn];
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr const T& MatrixT<Width, Height, T>::GetCell(std::size_t aColumn, std::size_t aRow) const
	{
		if (aColumn >= Width || aRow >= Height)
			throw std::out_of_range("Row or column indices out of range.");

		return myCells[(aRow * Width) + aColumn];
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr MatrixT<Width, Height, T> MatrixT<Width, Height, T>::Cofactor() const requires(Width == Height && Width > 0)
	{
		MatrixT solution;

		for (std::size_t rowIndex = 0; rowIndex < Height; ++rowIndex)
		{
			for (std::size_t columnIndex = 0; columnIndex < Width; ++columnIndex)
			{
				const auto subMatrix = SubMatrix(columnIndex, rowIndex);

				const bool isPositive = ((columnIndex ^ rowIndex) % 2) == 0;
				solution.GetCell(columnIndex, rowIndex) =
					static_cast<T>(isPositive ? 1 : -1) *
					subMatrix.Determinant()
					;
			}
		}

		return solution;
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr T MatrixT<Width, Height, T>::Determinant() const requires(Width == Height && Width > 0)
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
				const MatrixT<Width - 1, Height - 1, T> subMatrix = SubMatrix(i, 0);

				determinant +=
					static_cast<T>((i % 2 == 0) ? 1 : -1) *
					(factor * subMatrix.Determinant())
					;
			}

			return determinant;
		}
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr std::optional<MatrixT<Width, Height, T>> MatrixT<Width, Height, T>::Inverse() const requires(std::is_floating_point_v<T>&& Width == Height && Width > 0)
	{
		const T determinant = Determinant();
		if (determinant == static_cast<T>(0))
			return std::optional<MatrixT>();

		const T reciprocalDeterminant = static_cast<T>(1) / determinant;

		if constexpr (Width == 2)
		{
			return MatrixT({
				reciprocalDeterminant * GetCell(1, 1),
				reciprocalDeterminant * -GetCell(1, 0),
				reciprocalDeterminant * -GetCell(0, 1),
				reciprocalDeterminant * GetCell(0, 0)
				});
		}
		else
		{
			MatrixT inverse = Cofactor().Transposed();
			for (std::size_t i = 0; i < Width * Height; ++i)
				inverse.myCells[i] *= reciprocalDeterminant;
			return inverse;
		}
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr MatrixT<Width, Height, T> MatrixT<Width, Height, T>::Minor() const requires(std::is_floating_point_v<T>&& Width == Height && Width > 0)
	{
		MatrixT solution;

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

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr MatrixT<Height, Width, T> MatrixT<Width, Height, T>::Transposed() const
	{
		MatrixT<Height, Width, T> transposedMatrix;

		for (std::size_t rowIndex = 0; rowIndex < Height; ++rowIndex)
		{
			for (std::size_t columnIndex = 0; columnIndex < Width; ++columnIndex)
			{
				transposedMatrix.GetCell(rowIndex, columnIndex) = GetCell(columnIndex, rowIndex);
			}
		}

		return transposedMatrix;
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr MatrixT<Width - 1, Height - 1, T> MatrixT<Width, Height, T>::SubMatrix(std::size_t aColumn, std::size_t aRow) const
	{
		MatrixT<Width - 1, Height - 1, T> subMatrix;
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

	template <std::size_t Width, std::size_t Height, typename T>
	template <std::size_t _Width>
	constexpr MatrixT<_Width, Height, T> MatrixT<Width, Height, T>::operator*(const MatrixT<_Width, Width, T>& aMatrix) const
	{
		MatrixT<_Width, Height, T> result;

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

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr bool MatrixT<Width, Height, T>::operator==(const MatrixT& aMatrix) const
	{
		for (std::size_t i = 0; i < (Width * Height); ++i)
		{
			if (myCells[i] != aMatrix.myCells[i])
				return false;
		}

		return true;
	}

	template <std::size_t Width, std::size_t Height, typename T>
	constexpr bool MatrixT<Width, Height, T>::operator!=(const MatrixT& aMatrix) const
	{
		return !operator==(aMatrix);
	}
}