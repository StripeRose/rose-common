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
	class ColorT
	{
		static constexpr T ourSDRUpperBound = std::is_floating_point_v<T> ? static_cast<T>(1) : static_cast<T>(0xFF);
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
		constexpr ColorT();

		/**
		 * @brief Initialize the color components based on the provided ARGB value.
		 * @param aPackedArgbValue A 32-bit unsigned integer with the format 0xAARRGGBB.
		 */
		constexpr ColorT(const std::uint32_t aPackedArgbValue);

		/**
		 * @brief Initialize an opaque color with the provided component values.
		 * @param aRedValue A red component value.
		 * @param aGreenValue A green component value.
		 * @param aBlueValue A blue component value.
		 */
		constexpr ColorT(T aRedValue, T aGreenValue, T aBlueValue);

		/**
		 * @brief Initialize a color with the provided color and alpha components.
		 * @param anAlphaValue An alpha component value.
		 * @param aRedValue A red component value.
		 * @param aGreenValue A green component value.
		 * @param aBlueValue A blue component value.
		 */
		constexpr ColorT(T anAlphaValue, T aRedValue, T aGreenValue, T aBlueValue);

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
		constexpr ColorT<T> Saturated() const;

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

		constexpr ColorT& operator=(const ColorT& aColor);

		constexpr ColorT operator+(const ColorT& aColor) const;
		constexpr ColorT operator-(const ColorT& aColor) const;
		constexpr ColorT operator*(const ColorT& aColor) const;
		constexpr ColorT operator*(float aScalar) const;

		constexpr void operator+=(const ColorT& aColor);
		constexpr void operator-=(const ColorT& aColor);
		constexpr void operator*=(const ColorT& aColor);
		constexpr void operator*=(float aScalar);

		constexpr bool operator==(const ColorT& aColor) const;
		constexpr bool operator!=(const ColorT& aColor) const;

		constexpr std::strong_ordering operator<=>(const ColorT& aColor) const;

		#pragma endregion
	};

	template<typename T>
	constexpr ColorT<T>::ColorT()
		: R(0), G(0), B(0), A(0)
	{
	}

	template<typename T>
	constexpr ColorT<T>::ColorT(const std::uint32_t aPackedArgbValue)
		: A(static_cast<T>((aPackedArgbValue >> 24) & 0xFF))
		, R(static_cast<T>((aPackedArgbValue >> 16) & 0xFF))
		, G(static_cast<T>((aPackedArgbValue >> 8) & 0xFF))
		, B(static_cast<T>((aPackedArgbValue >> 0) & 0xFF))
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			A /= 0xFF;
			R /= 0xFF;
			G /= 0xFF;
			B /= 0xFF;
		}
	}

	template<typename T>
	constexpr ColorT<T>::ColorT(T aRedValue, T aGreenValue, T aBlueValue)
		: A(ourSDRUpperBound)
		, R(aRedValue)
		, G(aGreenValue)
		, B(aBlueValue)
	{ }

	template<typename T>
	constexpr ColorT<T>::ColorT(T anAlphaValue, T aRedValue, T aGreenValue, T aBlueValue)
		: A(anAlphaValue)
		, R(aRedValue)
		, G(aGreenValue)
		, B(aBlueValue)
	{ }

	template<typename T>
	constexpr float ColorT<T>::GetBrightness() const
	{
		const float r = static_cast<float>(R) / ourSDRUpperBound;
		const float g = static_cast<float>(G) / ourSDRUpperBound;
		const float b = static_cast<float>(B) / ourSDRUpperBound;

		return std::max({ r, g, b });
	}

	template<typename T>
	constexpr float ColorT<T>::GetHue() const
	{
		if (R == G && G == B)
			return 0.f;

		const float r = static_cast<float>(R) / ourSDRUpperBound;
		const float g = static_cast<float>(G) / ourSDRUpperBound;
		const float b = static_cast<float>(B) / ourSDRUpperBound;

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
	constexpr float ColorT<T>::GetSaturation() const
	{
		const float r = static_cast<float>(R) / ourSDRUpperBound;
		const float g = static_cast<float>(G) / ourSDRUpperBound;
		const float b = static_cast<float>(B) / ourSDRUpperBound;

		const float max = std::max({ r, g, b });
		const float min = std::min({ r, g, b });
		const float delta = max - min;

		if (max == 0)
			return 0;
		else
			return delta / max;
	}

	template<typename T>
	constexpr ColorT<T> ColorT<T>::Saturated() const
	{
		return ColorT<T>(
			A,
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(R, 0, ourSDRUpperBound),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(G, 0, ourSDRUpperBound),
			ROSECOMMON_MATH_NAMESPACE::Clamp<T>(B, 0, ourSDRUpperBound)
		);
	}

	template <typename T>
	constexpr std::uint32_t ColorT<T>::ToARGB() const
	{
		std::uint8_t a, r, g, b;

		if constexpr (std::is_floating_point_v<T>)
		{
			a = static_cast<std::uint8_t>(A * 0xFF);
			r = static_cast<std::uint8_t>(R * 0xFF);
			g = static_cast<std::uint8_t>(G * 0xFF);
			b = static_cast<std::uint8_t>(B * 0xFF);
		}
		else
		{
			a = A;
			r = R;
			g = G;
			b = B;
		}

		return (
			a << 24 |
			r << 16 |
			g << 8 |
			b
			);
	}

	template <typename T>
	constexpr ColorT<T>& ColorT<T>::operator=(const ColorT& aColor)
	{
		A = aColor.A;
		R = aColor.R;
		G = aColor.G;
		B = aColor.B;
		return *this;
	}

	template <typename T>
	constexpr ColorT<T> ColorT<T>::operator+(const ColorT& aColor) const
	{
		ColorT result(*this);
		result += aColor;
		return result;
	}

	template <typename T>
	constexpr ColorT<T> ColorT<T>::operator-(const ColorT& aColor) const
	{
		ColorT result(*this);
		result -= aColor;
		return result;
	}

	template <typename T>
	constexpr ColorT<T> ColorT<T>::operator*(const ColorT& aColor) const
	{
		ColorT result(*this);
		result *= aColor;
		return result;
	}

	template <typename T>
	constexpr ColorT<T> ColorT<T>::operator*(float aScalar) const
	{
		ColorT result(*this);
		result *= aScalar;
		return result;
	}

	template <typename T>
	constexpr void ColorT<T>::operator+=(const ColorT& aColor)
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
	constexpr void ColorT<T>::operator-=(const ColorT& aColor)
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
	constexpr void ColorT<T>::operator*=(const ColorT& aColor)
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
	constexpr void ColorT<T>::operator*=(float aScalar)
	{
		if constexpr (std::is_floating_point_v<T>)
			operator*=(ColorT(
				aScalar,
				aScalar,
				aScalar,
				aScalar
			));
		else
			operator*=(ColorT(
				static_cast<std::uint8_t>(aScalar * ourSDRUpperBound),
				static_cast<std::uint8_t>(aScalar * ourSDRUpperBound),
				static_cast<std::uint8_t>(aScalar * ourSDRUpperBound),
				static_cast<std::uint8_t>(aScalar * ourSDRUpperBound)
			));
	}

	template <typename T>
	constexpr bool ColorT<T>::operator==(const ColorT& aColor) const
	{
		return operator<=>(aColor) == std::weak_ordering::equivalent;
	}

	template <typename T>
	constexpr bool ColorT<T>::operator!=(const ColorT& aColor) const
	{
		return operator<=>(aColor) != std::weak_ordering::equivalent;
	}

	template <typename T>
	constexpr std::strong_ordering ColorT<T>::operator<=>(const ColorT& aColor) const
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
	struct ColorT<T>::Predefined
	{
		static constexpr ColorT AliceBlue = 0xFFF0F8FF;
		static constexpr ColorT AntiqueWhite = 0xFFFAEBD7;
		static constexpr ColorT Aqua = 0xFF00FFFF;
		static constexpr ColorT Aquamarine = 0xFF7FFFD4;
		static constexpr ColorT Azure = 0xFFF0FFFF;
		static constexpr ColorT Beige = 0xFFF5F5DC;
		static constexpr ColorT Bisque = 0xFFFFE4C4;
		static constexpr ColorT Black = 0xFF000000;
		static constexpr ColorT BlanchedAlmond = 0xFFFFEBCD;
		static constexpr ColorT Blue = 0xFF0000FF;
		static constexpr ColorT BlueViolet = 0xFF8A2BE2;
		static constexpr ColorT Brown = 0xFFA52A2A;
		static constexpr ColorT BurlyWood = 0xFFDEB887;
		static constexpr ColorT CadetBlue = 0xFF5F9EA0;
		static constexpr ColorT Chartreuse = 0xFF7FFF00;
		static constexpr ColorT Chocolate = 0xFFD2691E;
		static constexpr ColorT Coral = 0xFFFF7F50;
		static constexpr ColorT CornflowerBlue = 0xFF6495ED;
		static constexpr ColorT Cornsilk = 0xFFFFF8DC;
		static constexpr ColorT Crimson = 0xFFDC143C;
		static constexpr ColorT Cyan = 0xFF00FFFF;
		static constexpr ColorT DarkBlue = 0xFF00008B;
		static constexpr ColorT DarkCyan = 0xFF008B8B;
		static constexpr ColorT DarkGoldenrod = 0xFFB8860B;
		static constexpr ColorT DarkGray = 0xFFA9A9A9;
		static constexpr ColorT DarkGreen = 0xFF006400;
		static constexpr ColorT DarkKhaki = 0xFFBDB76B;
		static constexpr ColorT DarkMagenta = 0xFF8B008B;
		static constexpr ColorT DarkOliveGreen = 0xFF556B2F;
		static constexpr ColorT DarkOrange = 0xFFFF8C00;
		static constexpr ColorT DarkOrchid = 0xFF9932CC;
		static constexpr ColorT DarkRed = 0xFF8B0000;
		static constexpr ColorT DarkSalmon = 0xFFE9967A;
		static constexpr ColorT DarkSeaGreen = 0xFF8FBC8B;
		static constexpr ColorT DarkSlateBlue = 0xFF483D8B;
		static constexpr ColorT DarkSlateGray = 0xFF2F4F4F;
		static constexpr ColorT DarkTurquoise = 0xFF9400D3;
		static constexpr ColorT DarkViolet = 0xFFFF1493;
		static constexpr ColorT DeepPink = 0xFF00BFFF;
		static constexpr ColorT DeepSkyBlue = 0xFF00BFFF;
		static constexpr ColorT DimGray = 0xFF696969;
		static constexpr ColorT DodgerBlue = 0xFF1E90FF;
		static constexpr ColorT Firebrick = 0xFFB22222;
		static constexpr ColorT FloralWhite = 0xFFFFFAF0;
		static constexpr ColorT ForestGreen = 0xFF228B22;
		static constexpr ColorT Fuchsia = 0xFFFF00FF;
		static constexpr ColorT Gainsboro = 0xFFDCDCDC;
		static constexpr ColorT GhostWhite = 0xFFF8F8FF;
		static constexpr ColorT Gold = 0xFFFFD700;
		static constexpr ColorT Goldenrod = 0xFFDAA520;
		static constexpr ColorT Gray = 0xFF808080;
		static constexpr ColorT Green = 0xFF008000;
		static constexpr ColorT GreenYellow = 0xFFADFF2F;
		static constexpr ColorT Honeydew = 0xFFF0FFF0;
		static constexpr ColorT HotPink = 0xFFFF69B4;
		static constexpr ColorT IndianRed = 0xFFCD5C5C;
		static constexpr ColorT Indigo = 0xFF4B0082;
		static constexpr ColorT Ivory = 0xFFFFFFF0;
		static constexpr ColorT Khaki = 0xFFF0E68C;
		static constexpr ColorT Lavender = 0xFFE6E6FA;
		static constexpr ColorT LavenderBlush = 0xFFFFF0F5;
		static constexpr ColorT LawnGreen = 0xFF7CFC00;
		static constexpr ColorT LemonChiffon = 0xFFFFFACD;
		static constexpr ColorT LightBlue = 0xFFADD8E6;
		static constexpr ColorT LightCoral = 0xFFF08080;
		static constexpr ColorT LightCyan = 0xFFE0FFFF;
		static constexpr ColorT LightGoldenrodYellow = 0xFFFAFAD2;
		static constexpr ColorT LightGray = 0xFFD3D3D3;
		static constexpr ColorT LightGreen = 0xFF90EE90;
		static constexpr ColorT LightPink = 0xFFFFB6C1;
		static constexpr ColorT LightSalmon = 0xFFFFA07A;
		static constexpr ColorT LightSeaGreen = 0xFF20B2AA;
		static constexpr ColorT LightSkyBlue = 0xFF87CEFA;
		static constexpr ColorT LightSlateGray = 0xFF778899;
		static constexpr ColorT LightSteelBlue = 0xFFB0C4DE;
		static constexpr ColorT LightYellow = 0xFFFFFFE0;
		static constexpr ColorT Lime = 0xFF00FF00;
		static constexpr ColorT LimeGreen = 0xFF32CD32;
		static constexpr ColorT Linen = 0xFFFAF0E6;
		static constexpr ColorT Magenta = 0xFFFF00FF;
		static constexpr ColorT Maroon = 0xFF800000;
		static constexpr ColorT MediumAquamarine = 0xFF66CDAA;
		static constexpr ColorT MediumBlue = 0xFF0000CD;
		static constexpr ColorT MediumOrchid = 0xFFBA55D3;
		static constexpr ColorT MediumPurple = 0xFF9370DB;
		static constexpr ColorT MediumSeaGreen = 0xFF3CB371;
		static constexpr ColorT MediumSlateBlue = 0xFF7B68EE;
		static constexpr ColorT MediumSpringGreen = 0xFF00FA9A;
		static constexpr ColorT MediumTurquoise = 0xFF48D1CC;
		static constexpr ColorT MediumVioletRed = 0xFFC71585;
		static constexpr ColorT MidnightBlue = 0xFF191970;
		static constexpr ColorT MintCream = 0xFFF5FFFA;
		static constexpr ColorT MistyRose = 0xFFFFE4E1;
		static constexpr ColorT Moccasin = 0xFFFFE4B5;
		static constexpr ColorT NavajoWhite = 0xFFFFDEAD;
		static constexpr ColorT Navy = 0xFF000080;
		static constexpr ColorT OldLace = 0xFFFDF5E6;
		static constexpr ColorT Olive = 0xFF808000;
		static constexpr ColorT OliveDrab = 0xFF6B8E23;
		static constexpr ColorT Orange = 0xFFFFA500;
		static constexpr ColorT OrangeRed = 0xFFFF4500;
		static constexpr ColorT Orchid = 0xFFDA70D6;
		static constexpr ColorT PaleGoldenrod = 0xFFEEE8AA;
		static constexpr ColorT PaleGreen = 0xFF98FB98;
		static constexpr ColorT PaleTurquoise = 0xFFAFEEEE;
		static constexpr ColorT PaleVioletRed = 0xFFDB7093;
		static constexpr ColorT PapayaWhip = 0xFFFFEFD5;
		static constexpr ColorT PeachPuff = 0xFFFFDAB9;
		static constexpr ColorT Peru = 0xFFCD853F;
		static constexpr ColorT Pink = 0xFFFFC0CB;
		static constexpr ColorT Plum = 0xFFDDA0DD;
		static constexpr ColorT PowderBlue = 0xFFB0E0E6;
		static constexpr ColorT Purple = 0xFF800080;
		static constexpr ColorT Red = 0xFFFF0000;
		static constexpr ColorT RosyBrown = 0xFFBC8F8F;
		static constexpr ColorT RoyalBlue = 0xFF4169E1;
		static constexpr ColorT SaddleBrown = 0xFF8B4513;
		static constexpr ColorT Salmon = 0xFFFA8072;
		static constexpr ColorT SandyBrown = 0xFFF4A460;
		static constexpr ColorT SeaGreen = 0xFF2E8B57;
		static constexpr ColorT SeaShell = 0xFFFFF5EE;
		static constexpr ColorT Sienna = 0xFFA0522D;
		static constexpr ColorT Silver = 0xFFC0C0C0;
		static constexpr ColorT SkyBlue = 0xFF87CEEB;
		static constexpr ColorT SlateBlue = 0xFF6A5ACD;
		static constexpr ColorT SlateGray = 0xFF708090;
		static constexpr ColorT Snow = 0xFFFFFAFA;
		static constexpr ColorT SpringGreen = 0xFF00FF7F;
		static constexpr ColorT SteelBlue = 0xFF4682B4;
		static constexpr ColorT Tan = 0xFFD2B48C;
		static constexpr ColorT Teal = 0xFF008080;
		static constexpr ColorT Thistle = 0xFFD8BFD8;
		static constexpr ColorT Tomato = 0xFFFF6347;
		static constexpr ColorT Transparent = 0x00000000;
		static constexpr ColorT Turquoise = 0xFF40E0D0;
		static constexpr ColorT Violet = 0xFFEE82EE;
		static constexpr ColorT Wheat = 0xFFF5DEB3;
		static constexpr ColorT White = 0xFFFFFFFF;
		static constexpr ColorT WhiteSmoke = 0xFFF5F5F5;
		static constexpr ColorT Yellow = 0xFFFFFF00;
		static constexpr ColorT YellowGreen = 0xFF9ACD32;
	};
}