#pragma once

#include "../../RoseCommon_Namespace.hpp"

#include "../Vector.hpp"

#include <optional>

namespace ROSECOMMON_MATH_NAMESPACE
{
	template <typename T>
	class Rectangle
	{
	public:

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize to the specified top-left corner position, width and height.
		 * @param aPoint An initial position of the top left corner.
		 * @param aSize An initial size of the rectangle.
		 */
		constexpr Rectangle(const Vector2<T>& aPoint, const Vector2<T>& aSize) noexcept;

		/**
		 * @brief Create a rectangle to exactly contain two points.
		 * @param aPointA A point.
		 * @param aPointB A point.
		 */
		static constexpr Rectangle FromPoints(const Vector2<T>& aPointA, const Vector2<T>& aPointB) noexcept;

		/**
		 * @brief Create a rectangle to contain a point, and the sum of the point and a vector.
		 * @param aPoint A first point the rectangle should contain.
		 * @param aVector The amount to offset the point to get the second point.
		 */
		static constexpr Rectangle FromPointAndOffset(const Vector2<T>& aPoint, const Vector2<T>& aVector) noexcept;

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
		constexpr Vector2<T> BottomLeft() const;

		/**
		 * @brief Get the position of the rectangle's bottom-right corner.
		 */
		constexpr Vector2<T> BottomRight() const;

		/**
		 * @brief Get the position of the rectangle's center.
		 */
		constexpr Vector2<T> Center() const;

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
		constexpr Vector2<T> Size() const;

		/**
		 * @brief Get the y-coordinate of the rectangle's top side.
		 */
		constexpr T Top() const;

		/**
		 * @brief Get the position of the rectangle's top-left corner.
		 */
		constexpr Vector2<T> TopLeft() const;

		/**
		 * @brief Get the position of the rectangle's top-right corner.
		 */
		constexpr Vector2<T> TopRight() const;

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
		constexpr bool Contains(const Vector2<T>& aPoint) const;

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
		void Inflate(const Vector2<T>& aSize);

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
		void Union(const Vector2<T>& aPoint);

		/**
		 * @brief Expand the rectangle exactly enough to contain the specified rectangle.
		 * @param aRectangle A rectangle to include.
		 */
		void Union(const Rectangle<T>& aRectangle);

		#pragma endregion
	};

	template <typename T>
	constexpr Rectangle<T>::Rectangle(const Vector2<T>& aPoint, const Vector2<T>& aSize) noexcept
		: X(aPoint.X)
		, Y(aPoint.Y)
		, Width(aSize.Width)
		, Height(aSize.Height)
	{

	}

	template <typename T>
	constexpr Rectangle<T> Rectangle<T>::FromPoints(const Vector2<T>& aPointA, const Vector2<T>& aPointB) noexcept
	{
		const T x = ROSECOMMON_MATH_NAMESPACE::Min<T>(aPointA.X, aPointB.X);
		const T y = ROSECOMMON_MATH_NAMESPACE::Min<T>(aPointA.Y, aPointB.Y);
		const T width = ROSECOMMON_MATH_NAMESPACE::Max<T>(aPointA.X, aPointB.X) - X;
		const T height = ROSECOMMON_MATH_NAMESPACE::Max<T>(aPointA.Y, aPointB.Y) - Y;
		return Rectangle<T>({ x, y }, { width, height });
	}

	template <typename T>
	constexpr Rectangle<T> Rectangle<T>::FromPointAndOffset(const Vector2<T>& aPoint, const Vector2<T>& aVector) noexcept
	{
		return FromPoints(aPoint, aPoint + aVector);
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
	constexpr Vector2<T> Rectangle<T>::BottomLeft() const
	{
		return Vector2<T>(Left(), Bottom());
	}

	template<typename T>
	constexpr Vector2<T> Rectangle<T>::BottomRight() const
	{
		return Vector2<T>(Right(), Bottom());
	}

	template<typename T>
	constexpr Vector2<T> Rectangle<T>::Center() const
	{
		return Vector2<T>(X + (Width / 2), Y + (Height / 2));
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
	constexpr Vector2<T> Rectangle<T>::Size() const
	{
		return Vector2<T>(Width, Height);
	}

	template<typename T>
	constexpr T Rectangle<T>::Top() const
	{
		return Y;
	}

	template<typename T>
	constexpr Vector2<T> Rectangle<T>::TopLeft() const
	{
		return Vector2<T>(Left(), Top());
	}

	template<typename T>
	constexpr Vector2<T> Rectangle<T>::TopRight() const
	{
		return Vector2<T>(Right(), Top());
	}

	template<typename T>
	constexpr bool Rectangle<T>::Contains(const Vector2<T>& aPoint) const
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
	void Rectangle<T>::Inflate(const Vector2<T>& aSize)
	{
		Inflate(aSize.Width, aSize.Height);
	}

	template <typename T>
	constexpr std::optional<Rectangle<T>> Rectangle<T>::Intersection(const Rectangle<T>& aRectangle) const
	{
		const T top = ROSECOMMON_MATH_NAMESPACE::Max<T>(Top(), aRectangle.Top());
		const T left = ROSECOMMON_MATH_NAMESPACE::Max<T>(Left(), aRectangle.Left());
		const T right = ROSECOMMON_MATH_NAMESPACE::Min<T>(Right(), aRectangle.Right());
		const T bottom = ROSECOMMON_MATH_NAMESPACE::Min<T>(Bottom(), aRectangle.Bottom());

		if (bottom <= top || right <= left)
			return { };

		return Rectangle<T>(PointT(left, top), PointT(right, bottom));
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
	void Rectangle<T>::Union(const Vector2<T>& aPoint)
	{
		X = ROSECOMMON_MATH_NAMESPACE::Min<T>(X, aPoint.X);
		Y = ROSECOMMON_MATH_NAMESPACE::Min<T>(Y, aPoint.Y);
		Width = ROSECOMMON_MATH_NAMESPACE::Max<T>(X + Width, aPoint.X) - X;
		Height = ROSECOMMON_MATH_NAMESPACE::Max<T>(Y + Height, aPoint.Y) - Y;
	}

	template <typename T>
	void Rectangle<T>::Union(const Rectangle<T>& aRectangle)
	{
		X = ROSECOMMON_MATH_NAMESPACE::Min<T>(X, aRectangle.X);
		Y = ROSECOMMON_MATH_NAMESPACE::Min<T>(Y, aRectangle.Y);
		Width = ROSECOMMON_MATH_NAMESPACE::Max<T>(X + Width, aRectangle.X + aRectangle.Width) - X;
		Height = ROSECOMMON_MATH_NAMESPACE::Max<T>(Y + Height, aRectangle.Y + aRectangle.Height) - Y;
	}
}