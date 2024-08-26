#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

#include <optional>

namespace RoseCommon::Math
{
	/**
	 * @brief An x- and y-coordinate pair in two-dimensional space.
	 * @tparam T A type for each component.
	 */
	template <typename T>
	class Point
	{
	public:

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize to the specified coordinates.
		 * @param anX An initial x-coordinate.
		 * @param aY An initial y-coordinate.
		 */
		constexpr Point(T anX, T aY) noexcept;

		/**
		 * @brief Initialize to the coordinates described by a vector.
		 * @param aVector A vector whose coordinaates to use for the point.
		 */
		constexpr Point(const Vector2<T>& aVector) noexcept;

		#pragma endregion

		//--------------------------------------------------
		// * Properties
		//--------------------------------------------------
		#pragma region Properties

		/**
		 * @brief The X-coordinate of the point.
		 */
		T X;

		/**
		 * @brief The Y-coordinate of the point.
		 */
		T Y;
		
		#pragma endregion

		//--------------------------------------------------
		// * Methods
		//--------------------------------------------------
		#pragma region Methods

		/**
		 * @brief Offset the point's coordinates by the specified amount.
		 * @param anXOffset The amount to offset the point's X-coordinate.
		 * @param aYOffset The amount to offset the point's Y-coordinate.
		 */
		void Offset(T anXOffset, T aYOffset);

		/**
		 * @brief Offset the point's coordinates by the specified vector.
		 * @param anOffset A vector describing the offset change.
		 */
		void Offset(const Vector2<T>& anOffset);

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		explicit constexpr operator Vector2<T>() const;

		constexpr Point operator+(const Vector2<T>& aVector) const;
		constexpr Vector2<T> operator-(const Point& aPoint) const;
		constexpr Point operator-(const Vector2<T>& aVector) const;
		constexpr Point operator*(const Matrix<3, 3, T>& aMatrix) const;

		constexpr bool operator==(const Point& aPoint) const;
		constexpr bool operator!=(const Point& aPoint) const;

		#pragma endregion
	};

	/**
	 * @brief Describes the width and height of a two-dimensional object.
	 * @tparam T A type for each component.
	 */
	template <typename T>
	class Size
	{
	public:

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize to the specified size.
		 * @param aWidth An initial width.
		 * @param aHeight An initial height.
		 */
		constexpr Size(T aWidth, T aHeight) noexcept;

		/**
		 * @brief Initialize from a Point.
		 * @param aPoint The point whose coordinates should be used for the size.
		 */
		explicit constexpr Size(const Point<T>& aPoint) noexcept;

		#pragma endregion

		//--------------------------------------------------
		// * Properties
		//--------------------------------------------------
		#pragma region Properties

		/**
		 * @brief The width of the size.
		 */
		T Width;

		/**
		 * @brief The height of the size.
		 */
		T Height;

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		explicit constexpr operator Point<T>() const;
		explicit constexpr operator Vector2<T>() const;

		constexpr bool operator==(const Size& aSize) const;
		constexpr bool operator!=(const Size& aSize) const;

		#pragma endregion
	};

	template <typename T>
	class Rectangle
	{
	public:

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize to exactly contain two points.
		 * @param aPointA A point.
		 * @param aPointB A point.
		 */
		constexpr Rectangle(const Point<T>& aPointA, const Point<T>& aPointB) noexcept;

		/**
		 * @brief Initialize to the specified top-left corner position, width and height.
		 * @param aPoint An initial position of the top left corner.
		 * @param aSize An initial size of the rectangle.
		 */
		constexpr Rectangle(const Point<T>& aPoint, const Math::Size<T>& aSize) noexcept;

		/**
		 * @brief Initialize to contain a point, and the sum of the point and a vector.
		 * @param aPoint A first point the rectangle should contain.
		 * @param aVector The amount to offset the point to get the second point.
		 */
		constexpr Rectangle(const Point<T>& aPoint, const Vector2<T>& aVector) noexcept;

		/**
		 * @brief Initialize to the specified size, located at (0, 0).
		 * @param aSize An initial size of the rectangle.
		 */
		constexpr explicit Rectangle(const Math::Size<T>& aSize) noexcept;

		#pragma endregion

		//--------------------------------------------------
		// * Properties
		//--------------------------------------------------
		#pragma region Properties

		/**
		 * @brief The x-coordinate of the rectangle's left side.
		 */
		T X;

		/**
		 * @brief The y-coordinate of the rectangle's top side.
		 */
		T Y;

		/**
		 * @brief The width of the rectangle.
		 */
		T Width;

		/**
		 * @brief The height of the rectangle.
		 */
		T Height;

		/**
		 * @brief Calculate the area of the rectangle.
		 */
		constexpr T Area() const;

		/**
		 * @brief Get the y-coordinate of the rectangle's bottom side.
		 */
		constexpr T Bottom() const;

		/**
		 * @brief Get the position of the rectangle's bottom-left corner.
		 */
		constexpr Point<T> BottomLeft() const;

		/**
		 * @brief Get the position of the rectangle's bottom-right corner.
		 */
		constexpr Point<T> BottomRight() const;

		/**
		 * @brief Get the position of the rectangle's center.
		 */
		constexpr Point<T> Center() const;

		/**
		 * @brief Get the x-coordinate of the rectangle's left side.
		 */
		constexpr T Left() const;

		/**
		 * @brief Get the x-coordinate of the rectangle's right side.
		 */
		constexpr T Right() const;

		/**
		 * @brief Get the width and height of the rectangle.
		 */
		constexpr Size<T> Size() const;

		/**
		 * @brief Get the y-coordinate of the rectangle's top side.
		 */
		constexpr T Top() const;

		/**
		 * @brief Get the position of the rectangle's top-left corner.
		 */
		constexpr Point<T> TopLeft() const;
		
		/**
		 * @brief Get the position of the rectangle's top-right corner.
		 */
		constexpr Point<T> TopRight() const;

		#pragma endregion

		//--------------------------------------------------
		// * Methods
		//--------------------------------------------------
		#pragma region Methods

		/**
		 * @brief Check whether the rectangle contains a specific point.
		 * @param aPoint A point to check.
		 * @return Whether the given point is contained within.
		 */
		constexpr bool Contains(const Point<T>& aPoint) const;

		/**
		 * @brief Check whether the rectangle contains another rectangle.
		 * @param aRectangle A rectangle to check.
		 * @return Whether the given rectangle is entirely contained within.
		 */
		constexpr bool Contains(const Rectangle<T>& aRectangle) const;

		/**
		 * @brief Expand or shrink the rectangle by the specified width and height, in each direction.
		 * @param aWidth An amount by which to expand the left and right sides of the rectangle.
		 * @param aHeight An amount by which to expand the top and bottom sides of the rectangle.
		 */
		void Inflate(T aWidth, T aHeight);

		/**
		 * @brief Expand or shrink the rectangle by the specified width and height, in each direction.
		 * @param aSize An amount by which to expand the sides of the rectangle.
		 */
		void Inflate(const Math::Size<T>& aSize);

		/**
		 * @brief Find the intersection of two rectangles.
		 * @param aRectangle A rectangle to calculate the intersection with the current rectangle.
		 * @return The intersection area, if any.
		 */
		constexpr std::optional<Rectangle<T>> Intersection(const Rectangle<T>& aRectangle) const;

		/**
		 * @brief Check if the specified rectangle intersects with the current.
		 * @return Whether the rectangles intersect with each other.
		 */
		constexpr bool IntersectsWith(const Rectangle<T>& aRectangle) const;

		/**
		 * @brief Move the rectangle by the specified horizontal and vertical amount.
		 * @param anXOffset An amount to move the rectangle horizontally.
		 * @param aYOffset An amount to move the rectangle vertically.
		 */
		void Offset(T anXOffset, T aYOffset);

		/**
		 * @brief Move the rectangle by a specified vector.
		 * @param anOffset A vector which specifies the horizontal and vertical amount to move the rectangle.
		 */
		void Offset(const Vector2<T>& anOffset);

		/**
		 * @brief Expand the rectangle exactly to contain the specified point.
		 * @param aPoint A point to include.
		 */
		void Union(const Point<T>& aPoint);

		/**
		 * @brief Expand the rectangle exactly enough to contain the specified rectangle.
		 * @param aRectangle A rectangle to include.
		 */
		void Union(const Rectangle<T>& aRectangle);

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		constexpr bool operator==(const RoseCommon::Math::Size<T>& aSize) const;
		constexpr bool operator!=(const RoseCommon::Math::Size<T>& aSize) const;

		#pragma endregion
	};
}

namespace RoseCommon::Math
{
	template <typename T>
	constexpr Point<T>::Point(T anX, T aY) noexcept
		: X(anX)
		, Y(aY)
	{

	}

	template <typename T>
	constexpr Point<T>::Point(const Vector2<T>& aVector) noexcept
		: X(aVector.X)
		, Y(aVector.Y)
	{

	}

	template<typename T>
	void Point<T>::Offset(T anXOffset, T aYOffset)
	{
		X += anXOffset;
		Y += aYOffset;
	}

	template<typename T>
	void Point<T>::Offset(const Vector2<T>& anOffset)
	{
		X += anOffset.X;
		Y += anOffset.Y;
	}

	template<typename T>
	constexpr Point<T>::operator Vector2<T>() const
	{
		return Vector2<T>(X, Y);
	}

	template<typename T>
	constexpr Point<T> Point<T>::operator+(const Vector2<T>& aVector) const
	{
		return Point<T>(X + aVector.X, Y + aVector.Y);
	}

	template<typename T>
	constexpr Vector2<T> Point<T>::operator-(const Point& aPoint) const
	{
		return Vector2<T>(X - aPoint.X, Y - aPoint.Y);
	}

	template<typename T>
	constexpr Point<T> Point<T>::operator-(const Vector2<T>& aVector) const
	{
		return Point<T>(X - aVector.X, Y - aVector.Y);
	}

	template<typename T>
	constexpr Point<T> Point<T>::operator*(const Matrix<3, 3, T>& aMatrix) const
	{
		Matrix<3, 1, T> point({ X, Y, 1 });
		point = point * aMatrix;
		return Point<T>(point.GetCell(0, 0), point.GetCell(1, 0));
	}

	template<typename T>
	constexpr bool Point<T>::operator==(const Point& aPoint) const
	{
		return X == aPoint.X && Y == aPoint.Y;
	}

	template<typename T>
	constexpr bool Point<T>::operator!=(const Point& aPoint) const
	{
		return X != aPoint.X || Y != aPoint.Y;
	}

	template <typename T>
	constexpr Size<T>::Size(T aWidth, T aHeight) noexcept
		: Width(aWidth)
		, Height(aHeight)
	{

	}

	template<typename T>
	constexpr Size<T>::Size(const Point<T>& aPoint) noexcept
		: Width(aPoint.X)
		, Height(aPoint.Y)
	{

	}

	template<typename T>
	constexpr Size<T>::operator Point<T>() const
	{
		return Point<T>(Width, Height);
	}

	template<typename T>
	constexpr Size<T>::operator Vector2<T>() const
	{
		return Vector2<T>(Width, Height);
	}

	template<typename T>
	constexpr bool Size<T>::operator==(const Size& aSize) const
	{
		return Width == aSize.Width && Height == aSize.Height;
	}

	template<typename T>
	constexpr bool Size<T>::operator!=(const Size& aSize) const
	{
		return Width != aSize.Width || Height != aSize.Height;
	}

	template <typename T>
	constexpr Rectangle<T>::Rectangle(const Point<T>& aPointA, const Point<T>& aPointB) noexcept
	{
		X = Math::Min<T>(aPointA.X, aPointB.X);
		Y = Math::Min<T>(aPointA.Y, aPointB.Y);
		Width = Math::Max<T>(aPointA.X, aPointB.X) - X;
		Height = Math::Max<T>(aPointA.Y, aPointB.Y) - Y;
	}

	template <typename T>
	constexpr Rectangle<T>::Rectangle(const Point<T>& aPoint, const Math::Size<T>& aSize) noexcept
		: X(aPoint.X)
		, Y(aPoint.Y)
		, Width(aSize.Width)
		, Height(aSize.Height)
	{
		
	}

	template <typename T>
	constexpr Rectangle<T>::Rectangle(const Point<T>& aPoint, const Vector2<T>& aVector) noexcept
		: Rectangle(aPoint, aPoint + aVector)
	{

	}

	template <typename T>
	constexpr Rectangle<T>::Rectangle(const Math::Size<T>& aSize) noexcept
		: X(0)
		, Y(0)
		, Width(aSize.Width)
		, Height(aSize.Height)
	{

	}

	template<typename T>
	constexpr T Rectangle<T>::Area() const
	{
		return Width * Height;
	}

	template<typename T>
	constexpr T Rectangle<T>::Bottom() const
	{
		return Y + Height;
	}

	template<typename T>
	constexpr Point<T> Rectangle<T>::BottomLeft() const
	{
		return Point<T>(Left(), Bottom());
	}

	template<typename T>
	constexpr Point<T> Rectangle<T>::BottomRight() const
	{
		return Point<T>(Right(), Bottom());
	}

	template<typename T>
	constexpr Point<T> Rectangle<T>::Center() const
	{
		return Point<T>(X + (Width / 2), Y + (Height / 2));
	}

	template<typename T>
	constexpr T Rectangle<T>::Left() const
	{
		return X;
	}

	template<typename T>
	constexpr T Rectangle<T>::Right() const
	{
		return X + Width;
	}

	template<typename T>
	constexpr Size<T> Rectangle<T>::Size() const
	{
		return Math::Size<T>(Width, Height);
	}

	template<typename T>
	constexpr T Rectangle<T>::Top() const
	{
		return Y;
	}

	template<typename T>
	constexpr Point<T> Rectangle<T>::TopLeft() const
	{
		return Point<T>(Left(), Top());
	}

	template<typename T>
	constexpr Point<T> Rectangle<T>::TopRight() const
	{
		return Point<T>(Right(), Top());
	}

	template<typename T>
	constexpr bool Rectangle<T>::Contains(const Point<T>& aPoint) const
	{
		return
			Left() <= aPoint.X && aPoint.X <= Right() &&
			Top() <= aPoint.Y && aPoint.Y <= Bottom()
			;
	}

	template<typename T>
	constexpr bool Rectangle<T>::Contains(const Rectangle<T>& aRectangle) const
	{
		return
			Left() <= aRectangle.Left() && aRectangle.Right() <= Right() &&
			Top() <= aRectangle.Top() && aRectangle.Bottom() <= Bottom()
			;
	}

	template <typename T>
	void Rectangle<T>::Inflate(T aWidth, T aHeight)
	{
		X -= aWidth;
		Y -= aHeight;
		Width += aWidth * 2;
		Height += aHeight * 2;
	}

	template <typename T>
	void Rectangle<T>::Inflate(const Math::Size<T>& aSize)
	{
		Inflate(aSize.Width, aSize.Height);
	}

	template <typename T>
	constexpr std::optional<Rectangle<T>> Rectangle<T>::Intersection(const Rectangle<T>& aRectangle) const
	{
		const T top = Math::Max<T>(Top(), aRectangle.Top());
		const T left = Math::Max<T>(Left(), aRectangle.Left());
		const T right = Math::Min<T>(Right(), aRectangle.Right());
		const T bottom = Math::Min<T>(Bottom(), aRectangle.Bottom());

		if (bottom <= top || right <= left)
			return { };

		return Rectangle<T>(Point(left, top), Point(right, bottom));
	}

	template <typename T>
	constexpr bool Rectangle<T>::IntersectsWith(const Rectangle<T>& aRectangle) const
	{
		return
			Left() < aRectangle.Right() && Right() > aRectangle.Left() &&
			Top() < aRectangle.Bottom() && Bottom() > aRectangle.Top()
			;
	}

	template <typename T>
	void Rectangle<T>::Offset(T anXOffset, T aYOffset)
	{
		X += anXOffset;
		Y += aYOffset;
	}

	template <typename T>
	void Rectangle<T>::Offset(const Vector2<T>& anOffset)
	{
		X += anOffset.X;
		Y += anOffset.Y;
	}

	template <typename T>
	void Rectangle<T>::Union(const Point<T>& aPoint)
	{
		X = Math::Min<T>(X, aPoint.X);
		Y = Math::Min<T>(Y, aPoint.Y);
		Width = Math::Max<T>(X + Width, aPoint.X) - X;
		Height = Math::Max<T>(Y + Height, aPoint.Y) - Y;
	}

	template <typename T>
	void Rectangle<T>::Union(const Rectangle<T>& aRectangle)
	{
		X = Math::Min<T>(X, aRectangle.X);
		Y = Math::Min<T>(Y, aRectangle.Y);
		Width = Math::Max<T>(X + Width, aRectangle.X + aRectangle.Width) - X;
		Height = Math::Max<T>(Y + Height, aRectangle.Y + aRectangle.Height) - Y;
	}
}
