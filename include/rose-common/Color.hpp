#pragma once

#include "RoseCommon_Namespace.hpp"
#include "math/Common.hpp"

#include <cmath>
#include <compare>
#include <cstdint>
#include <utility>

namespace ROSECOMMON_NAMESPACE
{
	/**
	 * @brief A straight four-component color using red, green, blue, and alpha data.
	 * @tparam T The type used for each color component.
	 */
	template <typename T>
	class ColorARGB
	{
		static constexpr T ourWhitepoint = std::is_floating_point_v<T> ? static_cast<T>(1) : std::numeric_limits<T>::max();
		static constexpr T ourPackedRangeRatio = ourWhitepoint / 0xFF;
	public:

		//--------------------------------------------------
		// * Types
		//--------------------------------------------------
		#pragma region Types

		using ComponentType = T;
		struct Predefined;

		#pragma endregion

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
		#pragma region Construction

		/**
		 * @brief Initialize to be transparent black.
		 */
		constexpr ColorARGB();

		/**
		 * @brief Initialize the color components based on the provided ARGB value.
		 * @param aPackedArgbValue A 32-bit unsigned integer with the format 0xAARRGGBB.
		 */
		constexpr ColorARGB(const std::uint32_t aPackedArgbValue);

		/**
		 * @brief Initialize an opaque color with the provided component values.
		 * @param aRedValue A red component value.
		 * @param aGreenValue A green component value.
		 * @param aBlueValue A blue component value.
		 */
		constexpr ColorARGB(T aRedValue, T aGreenValue, T aBlueValue);

		/**
		 * @brief Initialize a color with the provided color and alpha components.
		 * @param anAlphaValue An alpha component value.
		 * @param aRedValue A red component value.
		 * @param aGreenValue A green component value.
		 * @param aBlueValue A blue component value.
		 */
		constexpr ColorARGB(T anAlphaValue, T aRedValue, T aGreenValue, T aBlueValue);

		#pragma endregion

		//--------------------------------------------------
		// * Properties
		//--------------------------------------------------
		#pragma region Properties

		/**
		 * @brief The Alpha component value.
		 */
		T A;

		/**
		 * @brief The Red component value.
		 */
		T R;

		/**
		 * @brief The Green component value.
		 */
		T G;

		/**
		 * @brief The Blue component value.
		 */
		T B;

		#pragma endregion

		//--------------------------------------------------
		// * Methods
		//--------------------------------------------------
		#pragma region Methods

		/**
		 * @brief Calculate the brightness component of an HSB/HSV color from the RGB components.
		 * @return The brightness component, in range 0 - 1.
		 */
		constexpr float GetBrightness() const;

		/**
		 * @brief Calculate the hue component of an HSB/HSV color from the RGB components.
		 * @return The hue component, as an angle in the hue circle.
		 */
		constexpr float GetHue() const;

		/**
		 * @brief Calculate the saturation component of an HSB/HSV color, from the RGB components.
		 * @return The saturation value, in range 0 - 1.
		 */
		constexpr float GetSaturation() const;

		/**
		 * @brief Limit the color components to their maximum SDR value. 255 for integers, 1 for decimal numbers.
		 * @return The color with all its components limited to be within the 0 - 255 / 0 - 1 range.
		 */
		constexpr ColorARGB<T> Saturated() const;

		/**
		 * @brief Pack the color into a single 32-bit unsigned integer, with 8 bits for each component.
		 *        Requires the color to be in 0 - 255 / 0 - 1 range.
		 * @return A 32-bit unsigned integer with the format 0xAARRGGBB.
		 */
		constexpr std::uint32_t ToARGB() const;

		#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
		#pragma region Operators

		constexpr ColorARGB& operator=(const ColorARGB& aColor);

		constexpr ColorARGB operator+(const ColorARGB& aColor) const;
		constexpr ColorARGB operator-(const ColorARGB& aColor) const;
		constexpr ColorARGB operator*(const ColorARGB& aColor) const;
		constexpr ColorARGB operator*(float aScalar) const;

		constexpr void operator+=(const ColorARGB& aColor);
		constexpr void operator-=(const ColorARGB& aColor);
		constexpr void operator*=(const ColorARGB& aColor);
		constexpr void operator*=(float aScalar);

		constexpr bool operator==(const ColorARGB& aColor) const;
		constexpr bool operator!=(const ColorARGB& aColor) const;

		constexpr std::strong_ordering operator<=>(const ColorARGB& aColor) const;

		#pragma endregion
	};

	template<typename T>
	constexpr ColorARGB<T>::ColorARGB()
		: R(0), G(0), B(0), A(0)
	{
	}

	template<typename T>
	constexpr ColorARGB<T>::ColorARGB(const std::uint32_t aPackedArgbValue)
	{
		const std::uint8_t a = static_cast<std::uint8_t>((aPackedArgbValue >> 24) & 0xFF);
		const std::uint8_t r = static_cast<std::uint8_t>((aPackedArgbValue >> 16) & 0xFF);
		const std::uint8_t g = static_cast<std::uint8_t>((aPackedArgbValue >>  8) & 0xFF);
		const std::uint8_t b = static_cast<std::uint8_t>((aPackedArgbValue >>  0) & 0xFF);

		A = static_cast<T>(a) * ourPackedRangeRatio;
		R = static_cast<T>(r) * ourPackedRangeRatio;
		G = static_cast<T>(g) * ourPackedRangeRatio;
		B = static_cast<T>(b) * ourPackedRangeRatio;
	}

	template <typename T>
	constexpr ColorARGB<T>::ColorARGB(T aRedValue, T aGreenValue, T aBlueValue)
		: A(ourWhitepoint), R(aRedValue), G(aGreenValue), B(aBlueValue)
	{ }

	template<typename T>
	constexpr ColorARGB<T>::ColorARGB(T anAlphaValue, T aRedValue, T aGreenValue, T aBlueValue)
		: A(anAlphaValue)
		, R(aRedValue)
		, G(aGreenValue)
		, B(aBlueValue)
	{ }

	template<typename T>
	constexpr float ColorARGB<T>::GetBrightness() const
	{
		const float r = static_cast<float>(R) / ourWhitepoint;
		const float g = static_cast<float>(G) / ourWhitepoint;
		const float b = static_cast<float>(B) / ourWhitepoint;

		return std::max({ r, g, b });
	}

	template<typename T>
	constexpr float ColorARGB<T>::GetHue() const
	{
		if (R == G && G == B)
			return 0.f;

		const float r = static_cast<float>(R) / ourWhitepoint;
		const float g = static_cast<float>(G) / ourWhitepoint;
		const float b = static_cast<float>(B) / ourWhitepoint;

		const float max = std::max({ r, g, b });
		const float min = std::min({ r, g, b });
		const float delta = max - min;

		float hue = 0.f;
		if (r == max) {
			hue = ROSECOMMON_MATH_NAMESPACE::Modulo<float>((g - b) / delta, 6);
		}
		else if (g == max) {
			hue = 2 + (b - r) / delta;
		}
		else if (b == max) {
			hue = 4 + (r - g) / delta;
		}
		hue *= 60.f;

		return hue;
	}

	template<typename T>
	constexpr float ColorARGB<T>::GetSaturation() const
	{
		const float r = static_cast<float>(R) / ourWhitepoint;
		const float g = static_cast<float>(G) / ourWhitepoint;
		const float b = static_cast<float>(B) / ourWhitepoint;

		const float max = std::max({ r, g, b });
		const float min = std::min({ r, g, b });
		const float delta = max - min;

		if (max == 0)
			return 0;
		else
			return delta / max;
	}

	template<typename T>
	constexpr ColorARGB<T> ColorARGB<T>::Saturated() const
	{
		return ColorARGB<T>(
			A,
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(R, 0, ourWhitepoint),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(G, 0, ourWhitepoint),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(B, 0, ourWhitepoint)
		);
	}

	template <typename T>
	constexpr std::uint32_t ColorARGB<T>::ToARGB() const
	{
		std::uint8_t a, r, g, b;

		if constexpr (std::is_floating_point_v<T>)
		{
			a = static_cast<std::uint8_t>(ROSECOMMON_MATH_NAMESPACE::Clamp<T>(A, 0, ourWhitepoint) * 0xFF);
			r = static_cast<std::uint8_t>(ROSECOMMON_MATH_NAMESPACE::Clamp<T>(R, 0, ourWhitepoint) * 0xFF);
			g = static_cast<std::uint8_t>(ROSECOMMON_MATH_NAMESPACE::Clamp<T>(G, 0, ourWhitepoint) * 0xFF);
			b = static_cast<std::uint8_t>(ROSECOMMON_MATH_NAMESPACE::Clamp<T>(B, 0, ourWhitepoint) * 0xFF);
		}
		else
		{
			a = static_cast<std::uint8_t>(A / ourPackedRangeRatio);
			r = static_cast<std::uint8_t>(R / ourPackedRangeRatio);
			g = static_cast<std::uint8_t>(G / ourPackedRangeRatio);
			b = static_cast<std::uint8_t>(B / ourPackedRangeRatio);
		}

		return (
			a << 24 |
			r << 16 |
			g << 8 |
			b
			);
	}

	template <typename T>
	constexpr ColorARGB<T>& ColorARGB<T>::operator=(const ColorARGB& aColor)
	{
		A = aColor.A;
		R = aColor.R;
		G = aColor.G;
		B = aColor.B;
		return *this;
	}

	template <typename T>
	constexpr ColorARGB<T> ColorARGB<T>::operator+(const ColorARGB& aColor) const
	{
		ColorARGB result(*this);
		result += aColor;
		return result;
	}

	template <typename T>
	constexpr ColorARGB<T> ColorARGB<T>::operator-(const ColorARGB& aColor) const
	{
		ColorARGB result(*this);
		result -= aColor;
		return result;
	}

	template <typename T>
	constexpr ColorARGB<T> ColorARGB<T>::operator*(const ColorARGB& aColor) const
	{
		ColorARGB result(*this);
		result *= aColor;
		return result;
	}

	template <typename T>
	constexpr ColorARGB<T> ColorARGB<T>::operator*(float aScalar) const
	{
		ColorARGB result(*this);
		result *= aScalar;
		return result;
	}

	template <typename T>
	constexpr void ColorARGB<T>::operator+=(const ColorARGB& aColor)
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			A = ROSECOMMON_MATH_NAMESPACE::Clamp<T>(A + aColor.A, 0, 1);
			R += aColor.R;
			G += aColor.G;
			B += aColor.B;
		}
		else
		{
			const int result[] = {
				static_cast<int>(A) + static_cast<int>(aColor.A),
				static_cast<int>(R) + static_cast<int>(aColor.R),
				static_cast<int>(G) + static_cast<int>(aColor.G),
				static_cast<int>(B) + static_cast<int>(aColor.B)
			};

			A = static_cast<std::uint8_t>(std::min(result[0], 0xFF));
			R = static_cast<std::uint8_t>(std::min(result[1], 0xFF));
			G = static_cast<std::uint8_t>(std::min(result[2], 0xFF));
			B = static_cast<std::uint8_t>(std::min(result[3], 0xFF));
		}
	}

	template <typename T>
	constexpr void ColorARGB<T>::operator-=(const ColorARGB& aColor)
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			A = ROSECOMMON_MATH_NAMESPACE::Clamp<T>(A - aColor.A, 0, 1);
			R -= aColor.R;
			G -= aColor.G;
			B -= aColor.B;
		}
		else
		{
			const int result[] = {
				static_cast<int>(A) - static_cast<int>(aColor.A),
				static_cast<int>(R) - static_cast<int>(aColor.R),
				static_cast<int>(G) - static_cast<int>(aColor.G),
				static_cast<int>(B) - static_cast<int>(aColor.B)
			};

			A = static_cast<std::uint8_t>(std::max(result[0], 0));
			R = static_cast<std::uint8_t>(std::max(result[1], 0));
			G = static_cast<std::uint8_t>(std::max(result[2], 0));
			B = static_cast<std::uint8_t>(std::max(result[3], 0));
		}
	}

	template <typename T>
	constexpr void ColorARGB<T>::operator*=(const ColorARGB& aColor)
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			A = ROSECOMMON_MATH_NAMESPACE::Clamp<T>(A * aColor.A, 0, 1);
			R *= aColor.R;
			G *= aColor.G;
			B *= aColor.B;
		}
		else
		{
			A = static_cast<std::uint8_t>(((A / 255.f) * (aColor.A / 255.f)) * 255.f);
			R = static_cast<std::uint8_t>(((R / 255.f) * (aColor.R / 255.f)) * 255.f);
			G = static_cast<std::uint8_t>(((G / 255.f) * (aColor.G / 255.f)) * 255.f);
			B = static_cast<std::uint8_t>(((B / 255.f) * (aColor.B / 255.f)) * 255.f);
		}
	}

	template <typename T>
	constexpr void ColorARGB<T>::operator*=(float aScalar)
	{
		if constexpr (std::is_floating_point_v<T>)
			operator*=(ColorARGB(
				aScalar,
				aScalar,
				aScalar,
				aScalar
			));
		else
			operator*=(ColorARGB(
				static_cast<std::uint8_t>(aScalar * ourWhitepoint),
				static_cast<std::uint8_t>(aScalar * ourWhitepoint),
				static_cast<std::uint8_t>(aScalar * ourWhitepoint),
				static_cast<std::uint8_t>(aScalar * ourWhitepoint)
			));
	}

	template <typename T>
	constexpr bool ColorARGB<T>::operator==(const ColorARGB& aColor) const
	{
		return operator<=>(aColor) == std::weak_ordering::equivalent;
	}

	template <typename T>
	constexpr bool ColorARGB<T>::operator!=(const ColorARGB& aColor) const
	{
		return operator<=>(aColor) != std::weak_ordering::equivalent;
	}

	template <typename T>
	constexpr std::strong_ordering ColorARGB<T>::operator<=>(const ColorARGB& aColor) const
	{
		std::strong_ordering order;
		order = std::strong_order(R, aColor.R);
		if (order != std::strong_ordering::equal)
			return order;
		order = std::strong_order(G, aColor.G);
		if (order != std::strong_ordering::equal)
			return order;
		order = std::strong_order(B, aColor.B);
		if (order != std::strong_ordering::equal)
			return order;
		return std::strong_order(A, aColor.A);
	}

	/**
	 * @brief A list of pre-defined named colors.
	 * @tparam T The type used for each color component.
	 */
	template <typename T>
	struct ColorARGB<T>::Predefined
	{
		static constexpr ColorARGB AliceBlue = 0xFFF0F8FF;
		static constexpr ColorARGB AntiqueWhite = 0xFFFAEBD7;
		static constexpr ColorARGB Aqua = 0xFF00FFFF;
		static constexpr ColorARGB Aquamarine = 0xFF7FFFD4;
		static constexpr ColorARGB Azure = 0xFFF0FFFF;
		static constexpr ColorARGB Beige = 0xFFF5F5DC;
		static constexpr ColorARGB Bisque = 0xFFFFE4C4;
		static constexpr ColorARGB Black = 0xFF000000;
		static constexpr ColorARGB BlanchedAlmond = 0xFFFFEBCD;
		static constexpr ColorARGB Blue = 0xFF0000FF;
		static constexpr ColorARGB BlueViolet = 0xFF8A2BE2;
		static constexpr ColorARGB Brown = 0xFFA52A2A;
		static constexpr ColorARGB BurlyWood = 0xFFDEB887;
		static constexpr ColorARGB CadetBlue = 0xFF5F9EA0;
		static constexpr ColorARGB Chartreuse = 0xFF7FFF00;
		static constexpr ColorARGB Chocolate = 0xFFD2691E;
		static constexpr ColorARGB Coral = 0xFFFF7F50;
		static constexpr ColorARGB CornflowerBlue = 0xFF6495ED;
		static constexpr ColorARGB Cornsilk = 0xFFFFF8DC;
		static constexpr ColorARGB Crimson = 0xFFDC143C;
		static constexpr ColorARGB Cyan = 0xFF00FFFF;
		static constexpr ColorARGB DarkBlue = 0xFF00008B;
		static constexpr ColorARGB DarkCyan = 0xFF008B8B;
		static constexpr ColorARGB DarkGoldenrod = 0xFFB8860B;
		static constexpr ColorARGB DarkGray = 0xFFA9A9A9;
		static constexpr ColorARGB DarkGreen = 0xFF006400;
		static constexpr ColorARGB DarkKhaki = 0xFFBDB76B;
		static constexpr ColorARGB DarkMagenta = 0xFF8B008B;
		static constexpr ColorARGB DarkOliveGreen = 0xFF556B2F;
		static constexpr ColorARGB DarkOrange = 0xFFFF8C00;
		static constexpr ColorARGB DarkOrchid = 0xFF9932CC;
		static constexpr ColorARGB DarkRed = 0xFF8B0000;
		static constexpr ColorARGB DarkSalmon = 0xFFE9967A;
		static constexpr ColorARGB DarkSeaGreen = 0xFF8FBC8B;
		static constexpr ColorARGB DarkSlateBlue = 0xFF483D8B;
		static constexpr ColorARGB DarkSlateGray = 0xFF2F4F4F;
		static constexpr ColorARGB DarkTurquoise = 0xFF9400D3;
		static constexpr ColorARGB DarkViolet = 0xFFFF1493;
		static constexpr ColorARGB DeepPink = 0xFF00BFFF;
		static constexpr ColorARGB DeepSkyBlue = 0xFF00BFFF;
		static constexpr ColorARGB DimGray = 0xFF696969;
		static constexpr ColorARGB DodgerBlue = 0xFF1E90FF;
		static constexpr ColorARGB Firebrick = 0xFFB22222;
		static constexpr ColorARGB FloralWhite = 0xFFFFFAF0;
		static constexpr ColorARGB ForestGreen = 0xFF228B22;
		static constexpr ColorARGB Fuchsia = 0xFFFF00FF;
		static constexpr ColorARGB Gainsboro = 0xFFDCDCDC;
		static constexpr ColorARGB GhostWhite = 0xFFF8F8FF;
		static constexpr ColorARGB Gold = 0xFFFFD700;
		static constexpr ColorARGB Goldenrod = 0xFFDAA520;
		static constexpr ColorARGB Gray = 0xFF808080;
		static constexpr ColorARGB Green = 0xFF008000;
		static constexpr ColorARGB GreenYellow = 0xFFADFF2F;
		static constexpr ColorARGB Honeydew = 0xFFF0FFF0;
		static constexpr ColorARGB HotPink = 0xFFFF69B4;
		static constexpr ColorARGB IndianRed = 0xFFCD5C5C;
		static constexpr ColorARGB Indigo = 0xFF4B0082;
		static constexpr ColorARGB Ivory = 0xFFFFFFF0;
		static constexpr ColorARGB Khaki = 0xFFF0E68C;
		static constexpr ColorARGB Lavender = 0xFFE6E6FA;
		static constexpr ColorARGB LavenderBlush = 0xFFFFF0F5;
		static constexpr ColorARGB LawnGreen = 0xFF7CFC00;
		static constexpr ColorARGB LemonChiffon = 0xFFFFFACD;
		static constexpr ColorARGB LightBlue = 0xFFADD8E6;
		static constexpr ColorARGB LightCoral = 0xFFF08080;
		static constexpr ColorARGB LightCyan = 0xFFE0FFFF;
		static constexpr ColorARGB LightGoldenrodYellow = 0xFFFAFAD2;
		static constexpr ColorARGB LightGray = 0xFFD3D3D3;
		static constexpr ColorARGB LightGreen = 0xFF90EE90;
		static constexpr ColorARGB LightPink = 0xFFFFB6C1;
		static constexpr ColorARGB LightSalmon = 0xFFFFA07A;
		static constexpr ColorARGB LightSeaGreen = 0xFF20B2AA;
		static constexpr ColorARGB LightSkyBlue = 0xFF87CEFA;
		static constexpr ColorARGB LightSlateGray = 0xFF778899;
		static constexpr ColorARGB LightSteelBlue = 0xFFB0C4DE;
		static constexpr ColorARGB LightYellow = 0xFFFFFFE0;
		static constexpr ColorARGB Lime = 0xFF00FF00;
		static constexpr ColorARGB LimeGreen = 0xFF32CD32;
		static constexpr ColorARGB Linen = 0xFFFAF0E6;
		static constexpr ColorARGB Magenta = 0xFFFF00FF;
		static constexpr ColorARGB Maroon = 0xFF800000;
		static constexpr ColorARGB MediumAquamarine = 0xFF66CDAA;
		static constexpr ColorARGB MediumBlue = 0xFF0000CD;
		static constexpr ColorARGB MediumOrchid = 0xFFBA55D3;
		static constexpr ColorARGB MediumPurple = 0xFF9370DB;
		static constexpr ColorARGB MediumSeaGreen = 0xFF3CB371;
		static constexpr ColorARGB MediumSlateBlue = 0xFF7B68EE;
		static constexpr ColorARGB MediumSpringGreen = 0xFF00FA9A;
		static constexpr ColorARGB MediumTurquoise = 0xFF48D1CC;
		static constexpr ColorARGB MediumVioletRed = 0xFFC71585;
		static constexpr ColorARGB MidnightBlue = 0xFF191970;
		static constexpr ColorARGB MintCream = 0xFFF5FFFA;
		static constexpr ColorARGB MistyRose = 0xFFFFE4E1;
		static constexpr ColorARGB Moccasin = 0xFFFFE4B5;
		static constexpr ColorARGB NavajoWhite = 0xFFFFDEAD;
		static constexpr ColorARGB Navy = 0xFF000080;
		static constexpr ColorARGB OldLace = 0xFFFDF5E6;
		static constexpr ColorARGB Olive = 0xFF808000;
		static constexpr ColorARGB OliveDrab = 0xFF6B8E23;
		static constexpr ColorARGB Orange = 0xFFFFA500;
		static constexpr ColorARGB OrangeRed = 0xFFFF4500;
		static constexpr ColorARGB Orchid = 0xFFDA70D6;
		static constexpr ColorARGB PaleGoldenrod = 0xFFEEE8AA;
		static constexpr ColorARGB PaleGreen = 0xFF98FB98;
		static constexpr ColorARGB PaleTurquoise = 0xFFAFEEEE;
		static constexpr ColorARGB PaleVioletRed = 0xFFDB7093;
		static constexpr ColorARGB PapayaWhip = 0xFFFFEFD5;
		static constexpr ColorARGB PeachPuff = 0xFFFFDAB9;
		static constexpr ColorARGB Peru = 0xFFCD853F;
		static constexpr ColorARGB Pink = 0xFFFFC0CB;
		static constexpr ColorARGB Plum = 0xFFDDA0DD;
		static constexpr ColorARGB PowderBlue = 0xFFB0E0E6;
		static constexpr ColorARGB Purple = 0xFF800080;
		static constexpr ColorARGB Red = 0xFFFF0000;
		static constexpr ColorARGB RosyBrown = 0xFFBC8F8F;
		static constexpr ColorARGB RoyalBlue = 0xFF4169E1;
		static constexpr ColorARGB SaddleBrown = 0xFF8B4513;
		static constexpr ColorARGB Salmon = 0xFFFA8072;
		static constexpr ColorARGB SandyBrown = 0xFFF4A460;
		static constexpr ColorARGB SeaGreen = 0xFF2E8B57;
		static constexpr ColorARGB SeaShell = 0xFFFFF5EE;
		static constexpr ColorARGB Sienna = 0xFFA0522D;
		static constexpr ColorARGB Silver = 0xFFC0C0C0;
		static constexpr ColorARGB SkyBlue = 0xFF87CEEB;
		static constexpr ColorARGB SlateBlue = 0xFF6A5ACD;
		static constexpr ColorARGB SlateGray = 0xFF708090;
		static constexpr ColorARGB Snow = 0xFFFFFAFA;
		static constexpr ColorARGB SpringGreen = 0xFF00FF7F;
		static constexpr ColorARGB SteelBlue = 0xFF4682B4;
		static constexpr ColorARGB Tan = 0xFFD2B48C;
		static constexpr ColorARGB Teal = 0xFF008080;
		static constexpr ColorARGB Thistle = 0xFFD8BFD8;
		static constexpr ColorARGB Tomato = 0xFFFF6347;
		static constexpr ColorARGB Transparent = 0x00000000;
		static constexpr ColorARGB Turquoise = 0xFF40E0D0;
		static constexpr ColorARGB Violet = 0xFFEE82EE;
		static constexpr ColorARGB Wheat = 0xFFF5DEB3;
		static constexpr ColorARGB White = 0xFFFFFFFF;
		static constexpr ColorARGB WhiteSmoke = 0xFFF5F5F5;
		static constexpr ColorARGB Yellow = 0xFFFFFF00;
		static constexpr ColorARGB YellowGreen = 0xFF9ACD32;
	};
}