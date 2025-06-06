#pragma once

#include "../RoseCommon_Namespace.hpp"

#include <algorithm>
#include <cwctype>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// Based off https://github.com/SSARCandy/ini-cpp/

namespace ROSECOMMON_NAMESPACE
{
	/**
	 * @brief A structure of an Initialization (*.ini) file.
	 *        https://en.wikipedia.org/wiki/INI_file
	 */
	class Ini
	{
	public:
		class Section;

		/**
		 * @brief Valid characters at the start of lines that define valid comments.
		 */
		static constexpr const char* StartCommentPrefixes = ";#";

		/**
		 * @brief Valid characters in the middle of a line which defines the start of a comment.
		 */
		static constexpr const char* InlineCommentPrefixes = ";";

	public:
		/**
		 * @brief Create a named data-section which may contain its own list of key-value data pairs.
		 *        If a section with the same name already existed, it will be erased and a new one will take its place.
		 * @param aSectionName The name given to the new section, which it is identified by when getting.
		 * @return A reference to the newly created data-section
		 */
		Section& CreateSection(const std::string_view& aSectionName);

		/**
		 * @brief Get a reference to a data-section by name.
		 *        Throws std::out_of_range if the section does not exist. Use HasSection() to check before accessing.
		 * @param aSectionName The name of the section to get.
		 * @return A reference to the relevant section.
		 */
		[[nodiscard]]
		Section& GetSection(const std::string_view& aSectionName);

		/**
		 * @brief Get a constant reference to a data-section by name.
		 *        Throws std::out_of_range if the section does not exist. Use HasSection() to check before accessing.
		 * @param aSectionName The name of the section to get.
		 * @return A constant reference to the relevant section.
		 */
		[[nodiscard]]
		const Section& GetSection(const std::string_view& aSectionName) const;

		/**
		 * @brief Check if a particular named section exists in the structure.
		 * @param aSectionName The name of the section to check for.
		 * @return Whether the specified section exists.
		 */
		[[nodiscard]]
		bool HasSection(const std::string_view& aSectionName) const;

		/**
		 * @brief Read all contents from an Ini-formatted file into the structure.
		 * @param aPath The relative or absolute path of the file to read.
		 */
		void ReadFromFile(const std::filesystem::path& aPath);

		/**
		 * @brief Read all contents from an Ini-formatted data-stream into the structure.
		 * @param aStream The stream to read in data from.
		 */
		void ReadFromStream(std::istream& aStream);

		/**
		 * @brief Write the contents of the structure out into an Ini-formatted file.
		 * @param aPath The relative or absolute path of the file to write.
		 * @param anOpenMode Optional open mode. By default will overwrite any existing files at the destination.
		 * @return Whether the file write was successful.
		 */
		bool WriteToFile(const std::filesystem::path& aPath, std::ios_base::openmode anOpenMode = std::ios_base::trunc) const;

		/**
		 * @brief Write the contents of the structure out to the specified stream with an Ini-file format.
		 * @param aStream The out-stream to write to.
		 */
		void WriteToStream(std::ostream& aStream) const;

	private:
		std::map<std::string, Section> mySections;
	};

	/**
	 * @brief An individual section of an Ini structure.
	 */
	class Ini::Section
	{
		friend class Ini;

	public:
		/**
		 * @brief Get the value from a property of a given name.
		 * @tparam T
		 * @param aProperty
		 * @return The value it fetched by converting it from a text-string using operator&gt;&gt;().
		 */
		template <typename T = std::string>
		[[nodiscard]]
		T Get(const std::string_view& aProperty) const;

		/**
		 * @brief Get the list of values from a property of a given name.
		 *        The individual items in the list are set by converting them from a text-string using operator&gt;&gt;().
		 * @tparam T The type of the individual items in the list.
		 * @param aProperty The name of the property to get the list from.
		 * @return The resulting list of items.
		 */
		template <typename T = std::string>
		[[nodiscard]]
		std::vector<T> GetList(const std::string_view& aProperty) const;

		/**
		 * @brief Check if the section contains a property of a given name.
		 * @param aProperty The name of the property to check for.
		 * @return Whether the named property exists and can be read.
		 */
		[[nodiscard]]
		bool Has(const std::string_view& aProperty) const
		{
			return myProperties.contains(aProperty.data());
		}

		/**
		 * @brief Set a property of a given name to a specified value.
		 *        The value is set by converting it to a text-string using operator&lt;&lt;().
		 * @tparam T The type of the value to set.
		 * @param aProperty The name of the property to set the value to.
		 * @param aValue The value to set the property to.
		 */
		template <typename T = std::string>
		void Set(const std::string_view& aProperty, const T& aValue);

		/**
		 * @brief Set a property of a given name to a specified list of values.
		 *        The individual items in the list are set by converting them to a text-string using operator&lt;&lt;().
		 * @tparam T The type of the individual items in the list.
		 * @param aProperty The name of the property to set the list to.
		 * @param aList The list to set the property to.
		 */
		template <typename T = std::string>
		void SetList(const std::string_view& aProperty, const std::vector<T>& aList);

	private:
		template <typename T>
		static T StringToValue(const std::string& aString);

		template <typename T>
		static std::string ValueToString(const T& aValue);

		template <typename T>
		static std::string ValueToString(const std::vector<T>& aValue);

		std::map<std::string, std::string> myProperties;
	};

	inline Ini::Section& Ini::CreateSection(const std::string_view& aSectionName)
	{
		return mySections[aSectionName.data()] = Ini::Section();
	}

	inline Ini::Section& Ini::GetSection(const std::string_view& aSectionName)
	{
		return mySections.at(aSectionName.data());
	}

	inline const Ini::Section& Ini::GetSection(const std::string_view& aSectionName) const
	{
		return mySections.at(aSectionName.data());
	}

	inline bool Ini::HasSection(const std::string_view& aSectionName) const
	{
		return mySections.contains(aSectionName.data());
	}

	inline void Ini::ReadFromFile(const std::filesystem::path& aPath)
	{
		std::ifstream fileStream;
		fileStream.open(aPath);

		if (!fileStream.is_open())
			return;

		ReadFromStream(fileStream);
		fileStream.close();
	}

	inline void Ini::ReadFromStream(std::istream& aStream)
	{
		auto skipUntilCharacterOrComment =
			[](std::string::const_iterator& anIt, const std::string::const_iterator& anEndIterator, const char* someCharacters)
			{
				bool wasSpace = false;
				while (anIt != anEndIterator && (!someCharacters || !strchr(someCharacters, *anIt)) && !(wasSpace && strchr(Ini::InlineCommentPrefixes, *anIt)))
				{
					wasSpace = std::iswspace(*anIt);
					++anIt;
				}
			};

		auto skipWhitespace = [](std::string::const_iterator& anIt, const std::string::const_iterator& anEndIterator)
			{
				while (anIt != anEndIterator && std::iswspace(*anIt))
					++anIt;
			};

		auto trimEndWhitespace = [](const std::string::const_iterator& aStartIterator, std::string::const_iterator& anIt)
			{
				while (anIt != aStartIterator && std::iswspace(*(anIt - 1)))
					--anIt;
			};

		std::string line;
		Section* currentSection = nullptr;
		while (!aStream.eof())
		{
			std::getline(aStream, line);

			auto lineCurrent = line.cbegin();
			skipWhitespace(lineCurrent, line.cend());

			while (lineCurrent != line.cend())
			{
				if (strchr(Ini::StartCommentPrefixes, *lineCurrent))
				{
					break;
				}
				else if (*lineCurrent == '[')
				{
					lineCurrent++;
					auto sectionNameEnd = lineCurrent;
					skipUntilCharacterOrComment(sectionNameEnd, line.cend(), "]");
					if (*sectionNameEnd != ']')
						throw std::runtime_error("Section name missing an end.");

					currentSection = &CreateSection(std::string(lineCurrent, sectionNameEnd));

					break;
				}
				else
				{
					auto keyStart = lineCurrent;
					skipWhitespace(keyStart, line.cend());

					auto keyEnd = keyStart;
					skipUntilCharacterOrComment(keyEnd, line.cend(), "=:");
					if (*keyEnd == '=' || *keyEnd == ':')
					{
						auto valueStart = keyEnd + 1;

						trimEndWhitespace(line.cbegin(), keyEnd);

						skipWhitespace(valueStart, line.cend());

						auto valueEnd = valueStart;
						skipUntilCharacterOrComment(valueEnd, line.cend(), nullptr);
						if (valueEnd == valueStart)
							break;

						trimEndWhitespace(line.cbegin(), valueEnd);

						currentSection->Set(
							std::string(keyStart, keyEnd),
							std::string(valueStart, valueEnd)
						);

						break;
					}
					else
					{
						throw std::runtime_error("Property missing value.");
					}
				}
			}
		}
	}

	inline bool Ini::WriteToFile(const std::filesystem::path& aPath, std::ios_base::openmode anOpenMode) const
	{
		std::ofstream fileStream;
		fileStream.open(aPath, anOpenMode | std::ios_base::out);

		if (!fileStream.is_open())
			return false;

		WriteToStream(fileStream);
		fileStream.close();

		return true;
	}

	inline void Ini::WriteToStream(std::ostream& aStream) const
	{
		for (const auto& section : mySections)
		{
			aStream << "[" << section.first << "]\n";

			for (const auto& property : section.second.myProperties)
			{
				aStream << property.first << "=" << property.second << "\n";
			}
		}
	}

	template <typename T>
	inline void Ini::Section::Set(const std::string_view& aProperty, const T& aValue)
	{
		myProperties[aProperty.data()] = ValueToString(aValue);
	}

	template <typename T>
	inline T Ini::Section::Get(const std::string_view& aProperty) const
	{
		const std::string& valueString = myProperties.at(aProperty.data());
		return StringToValue<T>(valueString);
	}

	template <typename T>
	inline void Ini::Section::SetList(const std::string_view& aProperty, const std::vector<T>& aList)
	{
		myProperties[aProperty.data()] = ValueToString(aList);
	}

	template <typename T>
	inline std::vector<T> Ini::Section::GetList(const std::string_view& aProperty) const
	{
		std::istringstream ss(myProperties.at(aProperty.data()));
		const std::vector<std::string> strs{ std::istream_iterator<std::string> {ss}, std::istream_iterator<std::string>() };

		std::vector<T> list;
		for (const std::string& s : strs)
		{
			list.emplace_back(StringToValue<T>(s));
		}
		return list;
	}

	template <>
	inline bool Ini::Section::StringToValue<bool>(const std::string& aString)
	{
		std::string s(aString);

		for (auto& c : s)
			c = static_cast<char>(std::tolower(c));

		static const std::unordered_map<std::string, bool> s2b{
			{"1", true},  {"true", true},   {"yes", true}, {"on", true},
			{"0", false}, {"false", false}, {"no", false}, {"off", false},
		};

		auto const value = s2b.find(s);
		if (value == s2b.end())
		{
			throw std::runtime_error("\"" + s + "\" is not a valid boolean value.");
		}

		return value->second;
	}

	template <>
	inline std::string Ini::Section::StringToValue<std::string>(const std::string& aString)
	{
		return aString;
	}

	template <typename T>
	inline T Ini::Section::StringToValue(const std::string& aString)
	{
		T value;
		std::istringstream ss(aString);
		ss.exceptions(std::ios::failbit);
		ss >> value;
		return value;
	}

	template <typename T>
	inline std::string Ini::Section::ValueToString(const T& aValue)
	{
		std::stringstream ss;
		ss << aValue;
		return ss.str();
	}

	template <typename T>
	inline std::string Ini::Section::ValueToString(const std::vector<T>& aValue)
	{
		if (aValue.empty())
		{
			return "";
		}

		std::ostringstream oss;
		std::copy(aValue.begin(), aValue.end() - 1, std::ostream_iterator<T>(oss, " "));
		oss << aValue.back();

		return oss.str();
	}
}
