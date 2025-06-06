#pragma once

#include "RoseCommon_Namespace.hpp"

#include <string>

namespace ROSECOMMON_NAMESPACE
{
	template <typename Char>
	void StringReplace(std::basic_string<Char>& aString, const std::basic_string<Char>& anOld, const std::basic_string<Char>& aNew) {
		if (anOld.empty())
			return;

		size_t start_pos = 0;
		while ((start_pos = aString.find(anOld, start_pos)) != std::string::npos) {
			aString.replace(start_pos, anOld.length(), aNew);
			start_pos += aNew.length();
		}
	}
}