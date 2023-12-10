#pragma once

#include <string>

namespace RoseCommon
{
	namespace StringUtilities
	{
		template <typename Char>
		void Replace(std::basic_string<Char>& aString, const std::basic_string<Char>& anOld, const std::basic_string<Char>& aNew) {
			if (anOld.empty())
				return;

			size_t start_pos = 0;
			while ((start_pos = aString.find(anOld, start_pos)) != std::string::npos) {
				aString.replace(start_pos, anOld.length(), aNew);
				start_pos += aNew.length();
			}
		}
	}
}