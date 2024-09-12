#pragma once

#ifndef DEFINE_ENUM_FLAG_OPERATORS

	#include <type_traits>

	#define DEFINE_ENUM_FLAG_OPERATORS(EnumType) \
	inline constexpr EnumType operator|(EnumType a, EnumType b) noexcept { return (EnumType)((std::underlying_type_t<EnumType>)a | (std::underlying_type_t<EnumType>)b); } \
	inline EnumType& operator|=(EnumType& a, EnumType b) noexcept { return (EnumType&)(((std::underlying_type_t<EnumType>&)a) |= ((std::underlying_type_t<EnumType>)b)); } \
	inline constexpr EnumType operator&(EnumType a, EnumType b) noexcept { return EnumType(((std::underlying_type_t<EnumType>)a) & ((std::underlying_type_t<EnumType>)b)); } \
	inline EnumType& operator&=(EnumType& a, EnumType b) noexcept { return (EnumType&)(((std::underlying_type_t<EnumType>&)a) &= ((std::underlying_type_t<EnumType>)b)); } \
	inline constexpr EnumType operator~(EnumType a) noexcept { return EnumType(~((std::underlying_type_t<EnumType>)a)); } \
	inline constexpr EnumType operator^(EnumType a, EnumType b) noexcept { return EnumType(((std::underlying_type_t<EnumType>)a) ^ ((std::underlying_type_t<EnumType>)b)); } \
	inline EnumType& operator^=(EnumType& a, EnumType b) noexcept { return (EnumType&)(((std::underlying_type_t<EnumType>&)a) ^= ((std::underlying_type_t<EnumType>)b)); } \

#endif
