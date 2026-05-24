#pragma once

#include "RoseCommon_Namespace.hpp"

#include <compare>
#include <type_traits>

namespace ROSECOMMON_NAMESPACE
{
	/**
	 * @brief Defines a bit-set where each bit index is specified by an enum index.
	 *        Note, bitwise or-ing an enum value prior to constructing will likely cause the wrong bits being set.
	 * @tparam T The enum type to use when defining which bits are set.
	 */
	template <typename T> requires std::is_enum_v<T>
	class Flags
	{
	public:
		using MaskType = std::underlying_type_t<T>;

		//--------------------------------------------------
		// * Construction
		//--------------------------------------------------
	#pragma region Construction

		/**
		 * @brief Construct with no bits set.
		 */
		constexpr Flags() noexcept
			: myMask(0)
		{
		}

		/**
		 * @brief Construct with a single bit set, as defined by the enum.
		 *        If multiple bits are to be set, use the bitwise or-operator after construction.
		 * @param aBitIndex The enum value representing which bit index should be set.
		 */
		constexpr Flags(T aBitIndex) noexcept
			: myMask(1 << static_cast<MaskType>(aBitIndex))
		{
		}

		constexpr Flags(const Flags<T>&) noexcept = default;

		constexpr explicit Flags(MaskType aValue) noexcept
			: myMask(aValue)
		{
		}

		static Flags<T> All() { return Flags(static_cast<MaskType>(~0)); }

	#pragma endregion

		//--------------------------------------------------
		// * Methods
		//--------------------------------------------------
	#pragma region Methods

		inline Flags<T>& Clear(T aFlag) { return operator&=(~Flags<T>(aFlag)); }
		inline constexpr bool IsEmpty() const { return !myMask; }
		inline constexpr bool IsSet(T aFlag) const { return !operator&(Flags<T>(aFlag)).IsEmpty(); }
		inline Flags<T>& Set(T aFlag) { return operator|=(Flags<T>(aFlag)); }

	#pragma endregion

		//--------------------------------------------------
		// * Operators
		//--------------------------------------------------
	#pragma region Operators

		constexpr auto operator<=>(const Flags<T>&) const = default;

		constexpr bool operator!() const noexcept { return !myMask; }

		constexpr Flags<T> operator&(const Flags<T>& anRHV) const noexcept { return Flags<T>(myMask & anRHV.myMask); }
		constexpr Flags<T> operator|(const Flags<T>& anRHV) const noexcept { return Flags<T>(myMask | anRHV.myMask); }
		constexpr Flags<T> operator^(const Flags<T>& anRHV) const noexcept { return Flags<T>(myMask ^ anRHV.myMask); }
		constexpr Flags<T> operator~() const noexcept { return Flags<T>(myMask ^ static_cast<MaskType>(-1)); }

		constexpr Flags<T>& operator=(const Flags<T>& anRHV) noexcept = default;
		constexpr Flags<T>& operator|=(const Flags<T>& anRHV) noexcept
		{
			myMask |= anRHV.myMask;
			return *this;
		}

		constexpr Flags<T>& operator&=(const Flags<T>& anRHV) noexcept
		{
			myMask &= anRHV.myMask;
			return *this;
		}

		constexpr Flags<T>& operator^=(const Flags<T>& anRHV) noexcept
		{
			myMask ^= anRHV.myMask;
			return *this;
		}

		explicit constexpr operator bool() const noexcept { return !!myMask; }
		explicit constexpr operator MaskType() const noexcept { return myMask; }

	#pragma endregion

	private:
		MaskType myMask;
	};

	// bitwise operators
	template <typename T> requires std::is_enum_v<T>
	constexpr Flags<T> operator&(T aBitIndex, const Flags<T>& someFlags) noexcept
	{
		return someFlags.operator&(aBitIndex);
	}

	template <typename T> requires std::is_enum_v<T>
	constexpr Flags<T> operator|(T aBitIndex, const Flags<T>& someFlags) noexcept
	{
		return someFlags.operator|(aBitIndex);
	}

	template <typename T> requires std::is_enum_v<T>
	constexpr Flags<T> operator^(T aBitIndex, const Flags<T>& someFlags) noexcept
	{
		return someFlags.operator^(aBitIndex);
	}

	// bitwise operators on T
	template <typename T> requires std::is_enum_v<T>
	inline constexpr Flags<T> operator&(T aLHV, T anRHV) noexcept
	{
		return Flags<T>(aLHV) & anRHV;
	}

	template <typename T> requires std::is_enum_v<T>
	inline constexpr Flags<T> operator|(T aLHV, T anRHV) noexcept
	{
		return Flags<T>(aLHV) | anRHV;
	}

	template <typename T> requires std::is_enum_v<T>
	inline constexpr Flags<T> operator^(T aLHV, T anRHV) noexcept
	{
		return Flags<T>(aLHV) ^ anRHV;
	}

	template <typename T> requires std::is_enum_v<T>
	inline constexpr Flags<T> operator~(T aBitIndex) noexcept
	{
		return ~(Flags<T>(aBitIndex));
	}
}