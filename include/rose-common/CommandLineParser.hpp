#pragma once

#include <algorithm>
#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace RoseCommon
{
	/// <summary>
	/// Provides a simple interface for parsing and getting values of command line-style flags.
	/// 
	/// Line format:
	/// Flag names must start with either a minus('-') or plus('+') sign and are part of the flag name.
	/// Values has no prefix and is automatically attributed to the previous flag. Only one value per flag is allowed.
	/// -FlagWithoutValue -StringFlag1 StringWithoutSpaces -StringFlag2 "String Value with spaces" +NumberFlag 0.55 -BoolFlag false
	/// </summary>
	template <typename StringType = std::string>
	class CommandLineParser
	{
		using stringviewtype = std::basic_string_view<typename StringType::value_type>;

	public:
		CommandLineParser(StringType::const_pointer* aCommandLineArray, const std::size_t anArrayCount)
		{
			std::vector<stringviewtype> tokens;
			tokens.reserve(anArrayCount);

			for (int i = 1; i < anArrayCount; ++i)
				tokens.emplace_back(aCommandLineArray[i]);

			InternalParse(tokens);
		}

		CommandLineParser(const StringType& aString)
		{
			if (aString.empty())
				return;

			std::vector<stringviewtype> tokens;

			typename StringType::const_iterator argumentStart = aString.begin();
			typename StringType::const_iterator argumentEnd = argumentStart;
			while (argumentEnd <= aString.end())
			{
				const bool isArgumentEnd = (argumentEnd == aString.end() || std::isspace(*argumentEnd));
				if (isArgumentEnd)
				{
					if ((argumentEnd - argumentStart) > 0)
						tokens.push_back(stringviewtype(argumentStart, argumentEnd));

					if (argumentEnd == aString.end())
						break;

					argumentStart = (argumentEnd + 1);
				}

argumentEnd++;
			}

			InternalParse(tokens);
		}

		inline std::size_t GetArgumentCount() const { return myArguments.size(); }

		std::optional<bool> GetBooleanArgument(const std::size_t anIndex) const
		{
			if (anIndex < myArguments.size())
				return { };

			return StringToBool(myArguments[anIndex]);
		}

		std::optional<double> GetNumberArgument(const std::size_t anIndex) const
		{
			if (anIndex < myArguments.size())
				return { };

			const StringType& stringValue = myArguments[anIndex];
			return std::stod(stringValue);
		}

		std::optional<StringType> GetStringArgument(const std::size_t anIndex) const
		{
			if (anIndex < myArguments.size())
				return { };

			return myArguments[anIndex];
		}

		inline bool HasFlag(const StringType& aFlagName) const
		{
			return myFlagValues.contains(aFlagName);
		}

		std::optional<bool> GetBooleanFlag(const StringType& aFlagName) const
		{
			const auto iterator = myFlagValues.find(aFlagName);
			if (iterator == myFlagValues.end())
				return { };

			return StringToBool(iterator->second);
		}

		std::optional<double> GetNumberFlag(const StringType& aFlagName) const
		{
			const auto iterator = myFlagValues.find(aFlagName);
			if (iterator == myFlagValues.end())
				return { };

			try
			{
				return std::stod(iterator->second);
			}
			catch (...)
			{
				return { };
			}
		}

		std::optional<typename StringType> GetStringFlag(const StringType& aFlagName) const
		{
			const auto iterator = myFlagValues.find(aFlagName);
			if (iterator == myFlagValues.end())
				return { };
			else
				return iterator->second;
		}

	private:
		void InternalParse(const std::vector<stringviewtype>& anArgumentList)
		{
			StringType* lastFlagValue = nullptr;
			for (std::size_t i = 0; i < anArgumentList.size(); ++i)
			{
				const stringviewtype& currentValue = anArgumentList[i];
				const bool isFlagName = currentValue[0] == '-' || currentValue[0] == '+';

				if (isFlagName)
				{
					lastFlagValue = &myFlagValues[StringType(currentValue)];
				}
				else
				{
					if (lastFlagValue == nullptr)
						lastFlagValue = &myArguments.emplace_back();

					stringviewtype fullValue = currentValue;

					if (fullValue.front() == '"')
					{
						while (i < anArgumentList.size() && fullValue.back() != '"')
						{
							i++;
							fullValue = stringviewtype(&fullValue.front(), &anArgumentList[i].back() + 1);
						}

						(*lastFlagValue) = fullValue.substr(1, fullValue.length() - 2); // Trim quotation marks.
					}
					else
					{
						(*lastFlagValue) = fullValue;
					}

					lastFlagValue = nullptr;
				}
			}
		}

	private:
		struct FlagCompare
		{
			struct CaseInsensitive
			{
				bool operator() (StringType::const_reference aLHV, StringType::const_reference aRHV) const {
					return std::tolower(aLHV) < std::tolower(aRHV);
				}
			};

			bool operator() (const StringType& aLHV, const StringType& aRHV) const {
				return std::lexicographical_compare(
					aLHV.begin(), aLHV.end(),
					aRHV.begin(), aRHV.end(),
					CaseInsensitive()
				);
			}
		};

		bool StringToBool(StringType aString) const
		{
			std::transform(
				aString.begin(),
				aString.end(),
				aString.begin(),
				[](const StringType::value_type c) -> StringType::value_type { return static_cast<StringType::value_type>(std::tolower(c)); });

			if constexpr (std::is_same_v<StringType::value_type, char>)
				return aString != "0" && aString != "false";
			else if constexpr (std::is_same_v<StringType::value_type, wchar_t>)
				return aString != L"0" && aString != L"false";
			else
				throw new std::exception();
		}

	private:
		std::vector<StringType> myArguments;
		std::map<typename StringType, typename StringType, FlagCompare> myFlagValues;
	};
}
