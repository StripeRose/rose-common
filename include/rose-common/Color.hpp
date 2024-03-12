#pragma once

#include "math/Common.hpp"

#include <cmath>
#include <cstdint>

namespace RoseCommon
{
	/// <summary>
	/// Represents a straight four-component color using red, green, blue, and alpha data.
	/// </summary>
	/// <remarks>Blend modes and alpha compositing not yet implemented.</remarks>
	template <typename T>
	class Color
	{
		static constexpr T ourSDRUpperBound = std::is_floating_point_v<T> ? static_cast<T>(1) : static_cast<T>(0xFF);
	public:
		constexpr Color() : R(0), G(0), B(0), A(0) { }

		constexpr Color(const std::uint32_t aPackedArgbValue)
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

		constexpr Color(T aRedValue, T aGreenValue, T aBlueValue)
			: A(ourSDRUpperBound)
			, R(aRedValue)
			, G(aGreenValue)
			, B(aBlueValue)
		{ }

		constexpr Color(T anAlphaValue, T aRedValue, T aGreenValue, T aBlueValue)
			: A(anAlphaValue)
			, R(aRedValue)
			, G(aGreenValue)
			, B(aBlueValue)
		{ }

		constexpr float GetBrightness() const
		{
			const float r = static_cast<float>(R) / ourSDRUpperBound;
			const float g = static_cast<float>(G) / ourSDRUpperBound;
			const float b = static_cast<float>(B) / ourSDRUpperBound;

			return std::max({ r, g, b });
		}

		constexpr float GetHue() const
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
				hue = Math::Modulo<float>((g - b) / delta, 6);
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

		constexpr float GetSaturation() const
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

		constexpr Color Saturated() const
		{
			return Color<T>(
				A,
				Math::Clamp<T>(R, 0, ourSDRUpperBound),
				Math::Clamp<T>(G, 0, ourSDRUpperBound),
				Math::Clamp<T>(B, 0, ourSDRUpperBound)
			);
		}

		constexpr std::uint32_t ToARGB() const
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

		constexpr Color& operator=(const Color& aColor)
		{
			A = aColor.A;
			R = aColor.R;
			G = aColor.G;
			B = aColor.B;
			return *this;
		}

		constexpr Color operator+(const Color& aColor) const
		{
			Color result(*this);
			result += aColor;
			return result;
		}

		constexpr Color operator-(const Color& aColor) const
		{
			Color result(*this);
			result -= aColor;
			return result;
		}

		constexpr Color operator*(const Color& aColor) const
		{
			Color result(*this);
			result *= aColor;
			return result;
		}

		constexpr Color operator*(float aScalar) const
		{
			Color result(*this);
			result *= aScalar;
			return result;
		}

		constexpr void operator+=(const Color& aColor)
		{
			if constexpr (std::is_floating_point_v<T>)
			{
				A = Math::Clamp<T>(A + aColor.A, 0, 1);
				R += aColor.R;
				G += aColor.G;
				B += aColor.B;
			}
			else
			{
				const int result[] = {
					int(A) + int(aColor.A),
					int(R) + int(aColor.R),
					int(G) + int(aColor.G),
					int(B) + int(aColor.B)
				};

				A = static_cast<std::uint8_t>(std::min(result[0], 0xFF));
				R = static_cast<std::uint8_t>(std::min(result[1], 0xFF));
				G = static_cast<std::uint8_t>(std::min(result[2], 0xFF));
				B = static_cast<std::uint8_t>(std::min(result[3], 0xFF));
			}
		}

		constexpr void operator-=(const Color& aColor)
		{
			if constexpr (std::is_floating_point_v<T>)
			{
				A = Math::Clamp<T>(A - aColor.A, 0, 1);
				R -= aColor.R;
				G -= aColor.G;
				B -= aColor.B;
			}
			else
			{
				const int result[] = {
					int(A) - int(aColor.A),
					int(R) - int(aColor.R),
					int(G) - int(aColor.G),
					int(B) - int(aColor.B)
				};

				A = static_cast<std::uint8_t>(std::max(result[0], 0));
				R = static_cast<std::uint8_t>(std::max(result[1], 0));
				G = static_cast<std::uint8_t>(std::max(result[2], 0));
				B = static_cast<std::uint8_t>(std::max(result[3], 0));
			}
		}

		constexpr void operator*=(const Color& aColor)
		{
			if constexpr (std::is_floating_point_v<T>)
			{
				A = Math::Clamp<T>(A * aColor.A, 0, 1);
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

		constexpr void operator*=(float aScalar)
		{
			if constexpr (std::is_floating_point_v<T>)
				operator*=(Color(
					aScalar,
					aScalar,
					aScalar,
					aScalar
				));
			else
				operator*=(Color(
					static_cast<std::uint8_t>(aScalar * ourSDRUpperBound),
					static_cast<std::uint8_t>(aScalar * ourSDRUpperBound),
					static_cast<std::uint8_t>(aScalar * ourSDRUpperBound),
					static_cast<std::uint8_t>(aScalar * ourSDRUpperBound)
				));
		}

		constexpr bool operator==(const Color& aColor) const { return operator<=>(aColor) == std::weak_ordering::equivalent; }
		constexpr bool operator!=(const Color& aColor) const { return operator<=>(aColor) != std::weak_ordering::equivalent; }

		constexpr std::strong_ordering operator<=>(const Color& aColor) const
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

		// The Alpha component value.
		T A;
		// The Red component value.
		T R;
		// The Green component value.
		T G;
		// The Blue component value.
		T B;

		struct Predefined;
	};

	template <typename T>
	struct Color<T>::Predefined
	{
		static constexpr Color AliceBlue = 0xFFF0F8FF;
		static constexpr Color AntiqueWhite = 0xFFFAEBD7;
		static constexpr Color Aqua = 0xFF00FFFF;
		static constexpr Color Aquamarine = 0xFF7FFFD4;
		static constexpr Color Azure = 0xFFF0FFFF;
		static constexpr Color Beige = 0xFFF5F5DC;
		static constexpr Color Bisque = 0xFFFFE4C4;
		static constexpr Color Black = 0xFF000000;
		static constexpr Color BlanchedAlmond = 0xFFFFEBCD;
		static constexpr Color Blue = 0xFF0000FF;
		static constexpr Color BlueViolet = 0xFF8A2BE2;
		static constexpr Color Brown = 0xFFA52A2A;
		static constexpr Color BurlyWood = 0xFFDEB887;
		static constexpr Color CadetBlue = 0xFF5F9EA0;
		static constexpr Color Chartreuse = 0xFF7FFF00;
		static constexpr Color Chocolate = 0xFFD2691E;
		static constexpr Color Coral = 0xFFFF7F50;
		static constexpr Color CornflowerBlue = 0xFF6495ED;
		static constexpr Color Cornsilk = 0xFFFFF8DC;
		static constexpr Color Crimson = 0xFFDC143C;
		static constexpr Color Cyan = 0xFF00FFFF;
		static constexpr Color DarkBlue = 0xFF00008B;
		static constexpr Color DarkCyan = 0xFF008B8B;
		static constexpr Color DarkGoldenrod = 0xFFB8860B;
		static constexpr Color DarkGray = 0xFFA9A9A9;
		static constexpr Color DarkGreen = 0xFF006400;
		static constexpr Color DarkKhaki = 0xFFBDB76B;
		static constexpr Color DarkMagenta = 0xFF8B008B;
		static constexpr Color DarkOliveGreen = 0xFF556B2F;
		static constexpr Color DarkOrange = 0xFFFF8C00;
		static constexpr Color DarkOrchid = 0xFF9932CC;
		static constexpr Color DarkRed = 0xFF8B0000;
		static constexpr Color DarkSalmon = 0xFFE9967A;
		static constexpr Color DarkSeaGreen = 0xFF8FBC8B;
		static constexpr Color DarkSlateBlue = 0xFF483D8B;
		static constexpr Color DarkSlateGray = 0xFF2F4F4F;
		static constexpr Color DarkTurquoise = 0xFF9400D3;
		static constexpr Color DarkViolet = 0xFFFF1493;
		static constexpr Color DeepPink = 0xFF00BFFF;
		static constexpr Color DeepSkyBlue = 0xFF00BFFF;
		static constexpr Color DimGray = 0xFF696969;
		static constexpr Color DodgerBlue = 0xFF1E90FF;
		static constexpr Color Firebrick = 0xFFB22222;
		static constexpr Color FloralWhite = 0xFFFFFAF0;
		static constexpr Color ForestGreen = 0xFF228B22;
		static constexpr Color Fuchsia = 0xFFFF00FF;
		static constexpr Color Gainsboro = 0xFFDCDCDC;
		static constexpr Color GhostWhite = 0xFFF8F8FF;
		static constexpr Color Gold = 0xFFFFD700;
		static constexpr Color Goldenrod = 0xFFDAA520;
		static constexpr Color Gray = 0xFF808080;
		static constexpr Color Green = 0xFF008000;
		static constexpr Color GreenYellow = 0xFFADFF2F;
		static constexpr Color Honeydew = 0xFFF0FFF0;
		static constexpr Color HotPink = 0xFFFF69B4;
		static constexpr Color IndianRed = 0xFFCD5C5C;
		static constexpr Color Indigo = 0xFF4B0082;
		static constexpr Color Ivory = 0xFFFFFFF0;
		static constexpr Color Khaki = 0xFFF0E68C;
		static constexpr Color Lavender = 0xFFE6E6FA;
		static constexpr Color LavenderBlush = 0xFFFFF0F5;
		static constexpr Color LawnGreen = 0xFF7CFC00;
		static constexpr Color LemonChiffon = 0xFFFFFACD;
		static constexpr Color LightBlue = 0xFFADD8E6;
		static constexpr Color LightCoral = 0xFFF08080;
		static constexpr Color LightCyan = 0xFFE0FFFF;
		static constexpr Color LightGoldenrodYellow = 0xFFFAFAD2;
		static constexpr Color LightGray = 0xFFD3D3D3;
		static constexpr Color LightGreen = 0xFF90EE90;
		static constexpr Color LightPink = 0xFFFFB6C1;
		static constexpr Color LightSalmon = 0xFFFFA07A;
		static constexpr Color LightSeaGreen = 0xFF20B2AA;
		static constexpr Color LightSkyBlue = 0xFF87CEFA;
		static constexpr Color LightSlateGray = 0xFF778899;
		static constexpr Color LightSteelBlue = 0xFFB0C4DE;
		static constexpr Color LightYellow = 0xFFFFFFE0;
		static constexpr Color Lime = 0xFF00FF00;
		static constexpr Color LimeGreen = 0xFF32CD32;
		static constexpr Color Linen = 0xFFFAF0E6;
		static constexpr Color Magenta = 0xFFFF00FF;
		static constexpr Color Maroon = 0xFF800000;
		static constexpr Color MediumAquamarine = 0xFF66CDAA;
		static constexpr Color MediumBlue = 0xFF0000CD;
		static constexpr Color MediumOrchid = 0xFFBA55D3;
		static constexpr Color MediumPurple = 0xFF9370DB;
		static constexpr Color MediumSeaGreen = 0xFF3CB371;
		static constexpr Color MediumSlateBlue = 0xFF7B68EE;
		static constexpr Color MediumSpringGreen = 0xFF00FA9A;
		static constexpr Color MediumTurquoise = 0xFF48D1CC;
		static constexpr Color MediumVioletRed = 0xFFC71585;
		static constexpr Color MidnightBlue = 0xFF191970;
		static constexpr Color MintCream = 0xFFF5FFFA;
		static constexpr Color MistyRose = 0xFFFFE4E1;
		static constexpr Color Moccasin = 0xFFFFE4B5;
		static constexpr Color NavajoWhite = 0xFFFFDEAD;
		static constexpr Color Navy = 0xFF000080;
		static constexpr Color OldLace = 0xFFFDF5E6;
		static constexpr Color Olive = 0xFF808000;
		static constexpr Color OliveDrab = 0xFF6B8E23;
		static constexpr Color Orange = 0xFFFFA500;
		static constexpr Color OrangeRed = 0xFFFF4500;
		static constexpr Color Orchid = 0xFFDA70D6;
		static constexpr Color PaleGoldenrod = 0xFFEEE8AA;
		static constexpr Color PaleGreen = 0xFF98FB98;
		static constexpr Color PaleTurquoise = 0xFFAFEEEE;
		static constexpr Color PaleVioletRed = 0xFFDB7093;
		static constexpr Color PapayaWhip = 0xFFFFEFD5;
		static constexpr Color PeachPuff = 0xFFFFDAB9;
		static constexpr Color Peru = 0xFFCD853F;
		static constexpr Color Pink = 0xFFFFC0CB;
		static constexpr Color Plum = 0xFFDDA0DD;
		static constexpr Color PowderBlue = 0xFFB0E0E6;
		static constexpr Color Purple = 0xFF800080;
		static constexpr Color Red = 0xFFFF0000;
		static constexpr Color RosyBrown = 0xFFBC8F8F;
		static constexpr Color RoyalBlue = 0xFF4169E1;
		static constexpr Color SaddleBrown = 0xFF8B4513;
		static constexpr Color Salmon = 0xFFFA8072;
		static constexpr Color SandyBrown = 0xFFF4A460;
		static constexpr Color SeaGreen = 0xFF2E8B57;
		static constexpr Color SeaShell = 0xFFFFF5EE;
		static constexpr Color Sienna = 0xFFA0522D;
		static constexpr Color Silver = 0xFFC0C0C0;
		static constexpr Color SkyBlue = 0xFF87CEEB;
		static constexpr Color SlateBlue = 0xFF6A5ACD;
		static constexpr Color SlateGray = 0xFF708090;
		static constexpr Color Snow = 0xFFFFFAFA;
		static constexpr Color SpringGreen = 0xFF00FF7F;
		static constexpr Color SteelBlue = 0xFF4682B4;
		static constexpr Color Tan = 0xFFD2B48C;
		static constexpr Color Teal = 0xFF008080;
		static constexpr Color Thistle = 0xFFD8BFD8;
		static constexpr Color Tomato = 0xFFFF6347;
		static constexpr Color Transparent = 0x00000000;
		static constexpr Color Turquoise = 0xFF40E0D0;
		static constexpr Color Violet = 0xFFEE82EE;
		static constexpr Color Wheat = 0xFFF5DEB3;
		static constexpr Color White = 0xFFFFFFFF;
		static constexpr Color WhiteSmoke = 0xFFF5F5F5;
		static constexpr Color Yellow = 0xFFFFFF00;
		static constexpr Color YellowGreen = 0xFF9ACD32;
	};
}