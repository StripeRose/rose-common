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
	/**
	 * @brief An interface for parsing and getting values off command line-style flags.
	 *
	 *        Flag names must start with either a minus('-') or plus('+') sign, which are part of the flag name.
	 *        Values has no prefix and is automatically attributed to the previous flag. Only one value per flag is allowed.
	 *        -FlagWithoutValue -StringFlag1 StringWithoutSpaces -StringFlag2 "String Value with spaces" +NumberFlag 0.55 -BoolFlag false
	 * 
	 * @tparam StringType The string type used for parsing and returning data.
	 */
	template <typename StringType = std::string>
	class CommandLineParser
	{
		using stringviewtype = std::basic_string_view<typename StringType::value_type>;

	public:
		/**
		 * @brief Initialize the parser with a C-style character array.
		 * @param aCommandLineArray Pointer to the character to start parsing from.
		 * @param anArrayCount The length of the character array to parse.
		 */
		CommandLineParser(StringType::const_pointer* aCommandLineArray, const std::size_t anArrayCount)
		{
			std::vector<stringviewtype> tokens;
			tokens.reserve(anArrayCount);

			for (int i = 1; i < anArrayCount; ++i)
				tokens.emplace_back(aCommandLineArray[i]);

			InternalParse(tokens);
		}

		/**
		 * @brief Initialize the parser with a string.
		 * @param aString A string to parse.
		 */
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

		/**
		 * @brief Get the amount of non-flag arguments that were parsed.
		 * @return The amount of parsed arguments.
		 */
		[[nodiscard]]
		inline std::size_t GetArgumentCount() const { return myArguments.size(); }

		/**
		 * @brief Get a commandline argument by index as a boolean.
		 * @param anIndex Index of the argument to get.
		 * @return The set value if the argument exists, otherwise an unset optional.
		 */
		[[nodiscard]]
		std::optional<bool> GetBooleanArgument(const std::size_t anIndex) const
		{
			if (anIndex < myArguments.size())
				return { };

			return StringToBool(myArguments[anIndex]);
		}

		/**
		 * @brief Get a commandline argument by index as a number.
		 * @param anIndex Index of the argument to get.
		 * @return The set value if the argument exists, otherwise an unset optional.
		 */
		[[nodiscard]]
		std::optional<double> GetNumberArgument(const std::size_t anIndex) const
		{
			if (anIndex < myArguments.size())
				return { };

			const StringType& stringValue = myArguments[anIndex];
			return std::stod(stringValue);
		}

		/**
		 * @brief Get a commandline argument by index as a string.
		 * @param anIndex Index of the argument to get.
		 * @return The set value if the argument exists, otherwise an unset optional.
		 */
		[[nodiscard]]
		std::optional<StringType> GetStringArgument(const std::size_t anIndex) const
		{
			if (anIndex < myArguments.size())
				return { };

			return myArguments[anIndex];
		}

		/**
		 * @brief Check if a specific flag exists in the commandline.
		 * @param aFlagName The flag name to check for.
		 * @return Whether the flag exists.
		 */
		[[nodiscard]]
		inline bool HasFlag(const StringType& aFlagName) const
		{
			return myFlagValues.contains(aFlagName);
		}

		/**
		 * @brief Get the value of a commandline flag by the flag name, as a boolean.
		 * @param aFlagName The name of the flag to get the value from.
		 * @return The set value if the flag exists, otherwise an unset optional.
		 */
		[[nodiscard]]
		std::optional<bool> GetBooleanFlag(const StringType& aFlagName) const
		{
			const auto iterator = myFlagValues.find(aFlagName);
			if (iterator == myFlagValues.end())
				return { };

			return StringToBool(iterator->second);
		}

		/**
		 * @brief Get the value of a commandline flag by the flag name, as a number.
		 * @param aFlagName The name of the flag to get the value from.
		 * @return The set value if the flag exists, otherwise an unset optional.
		 */
		[[nodiscard]]
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

		/**
		 * @brief Get the value of a commandline flag by the flag name, as a string.
		 * @param aFlagName The name of the flag to get the value from.
		 * @return The set value if the flag exists, otherwise an unset optional.
		 */
		[[nodiscard]]
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
