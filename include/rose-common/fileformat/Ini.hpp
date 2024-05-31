#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// Based off https://github.com/SSARCandy/ini-cpp/

namespace RoseCommon
{
	class Ini
	{
	public:
		class Section;

		static constexpr const char* StartCommentPrefixes = ";#";
		static constexpr const char* InlineCommentPrefixes = ";";

	public:
		Section& CreateSection(const std::string_view& aSectionName);

		Section& GetSection(const std::string_view& aSectionName);

		const Section& GetSection(const std::string_view& aSectionName) const;

		bool HasSection(const std::string_view& aSectionName) const;

		void ReadFromFile(const std::filesystem::path& aPath);

		void ReadFromStream(std::ifstream& aStream);

		void WriteToFile(const std::filesystem::path& aPath) const;

		void WriteToStream(std::ofstream& aStream) const;

	private:
		std::map<std::string, Section> mySections;
	};

	class Ini::Section
	{
	public:
		bool IsEmpty() const { return myProperties.empty(); }

		bool Has(const std::string& aProperty) const { return myProperties.contains(aProperty); }

		template <typename T = std::string>
		void Set(const std::string_view& aProperty, const T& aValue);

		template <typename T = std::string>
		T Get(const std::string_view& aProperty) const;

		template <typename T = std::string>
		void SetList(const std::string_view& aProperty, const std::vector<T>& aList);

		template <typename T = std::string>
		std::vector<T> GetList(const std::string_view& aProperty) const;

		void WriteToStream(std::ofstream& aStream) const;

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
		return mySections[aSectionName.data()];
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
		ReadFromStream(fileStream);
		fileStream.close();
	}

	inline void Ini::ReadFromStream(std::ifstream& aStream)
	{
		auto skipUntilCharacterOrComment = [](std::string::const_iterator& anIt, const std::string::const_iterator& anEndIterator, const char* someCharacters)
			{
				bool wasSpace = false;
				while (anIt != anEndIterator && (!someCharacters || !strchr(someCharacters, *anIt)) && !(wasSpace && strchr(Ini::InlineCommentPrefixes, *anIt)))
				{
					wasSpace = std::isspace(*anIt);
					++anIt;
				}
			};

		auto skipWhitespace = [](std::string::const_iterator& anIt, const std::string::const_iterator& anEndIterator)
			{
				while (anIt != anEndIterator && std::isspace(*anIt))
					++anIt;
			};

		auto trimEndWhitespace = [](const std::string::const_iterator& aStartIterator, std::string::const_iterator& anIt)
			{
				while (anIt != aStartIterator && std::isspace(*(anIt - 1)))
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

	inline void Ini::WriteToFile(const std::filesystem::path& aPath) const
	{
		std::ofstream fileStream;
		fileStream.open(aPath);
		WriteToStream(fileStream);
		fileStream.close();
	}

	inline void Ini::WriteToStream(std::ofstream& aStream) const
	{
		if (!aStream.is_open())
			return;

		for (const auto& section : mySections)
		{
			aStream << "[" << section.first << "]\n";
			section.second.WriteToStream(aStream);
		}
	}

	template<typename T>
	inline void Ini::Section::Set(const std::string_view& aProperty, const T& aValue)
	{
		myProperties[aProperty.data()] = ValueToString(aValue);
	}

	template<typename T>
	inline T Ini::Section::Get(const std::string_view& aProperty) const
	{
		const std::string& valueString = myProperties.at(aProperty.data());
		return StringToValue<T>(valueString);
	}

	template<typename T>
	inline void Ini::Section::SetList(const std::string_view& aProperty, const std::vector<T>& aList)
	{
		myProperties[aProperty.data()] = ValueToString(aList);
	}

	template<typename T>
	inline std::vector<T> Ini::Section::GetList(const std::string_view& aProperty) const
	{
		std::istringstream ss(myProperties.at(aProperty.data()));
		const std::vector<std::string> strs{ std::istream_iterator<std::string>{ss},
											std::istream_iterator<std::string>() };

		std::vector<T> list;
		for (const std::string& s : strs) {
			list.emplace_back(StringToValue<T>(s));
		}
		return list;
	}

	inline void Ini::Section::WriteToStream(std::ofstream& aStream) const
	{
		for (const auto& property : myProperties)
			aStream << property.first << "=" << property.second << "\n";
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
		if (value == s2b.end()) {
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

	template<typename T>
	inline std::string Ini::Section::ValueToString(const std::vector<T>& aValue)
	{
		if (aValue.empty()) {
			return "";
		}
		std::ostringstream oss;
		std::copy(aValue.begin(), aValue.end() - 1, std::ostream_iterator<T>(oss, " "));
		oss << aValue.back();

		return oss.str();
	}
}
