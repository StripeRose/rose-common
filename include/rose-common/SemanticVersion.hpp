#pragma once

#include "RoseCommon_Namespace.hpp"

#include <sstream>
#include <string>
#include <vector>

namespace ROSECOMMON_NAMESPACE
{
	/**
	 * @brief A version identifier, following the http://semver.org/ standard.
	 */
	struct SemanticVersion
	{
		struct Identifier;

		/**
		 * @brief Initialize with version 0.0.0.
		 */
		SemanticVersion();

		/**
		 * @brief Initialize a specified version.
		 * @param aMajor A major version.
		 * @param aMinor A minor version.
		 * @param aPatch A patch version.
		 */
		SemanticVersion(std::uint64_t aMajor, std::uint64_t aMinor, std::uint64_t aPatch);

		/**
		 * @brief Initialize a specified prerelease version. 
		 * @param aMajor A major version.
		 * @param aMinor A minor version.
		 * @param aPatch A patch version.
		 * @param aPrerelease A prerelease version.
		 */
		SemanticVersion(std::uint64_t aMajor, std::uint64_t aMinor, std::uint64_t aPatch, const std::string& aPrerelease);

		/**
		 * @brief Initialize a version from a string.
		 * @param aSemanticVersion A valid SemVer string.
		 */
		SemanticVersion(std::string aSemanticVersion);

		/**
		 * @brief Add prerelease versions.
		 * @param aString A dot-separated string of versions to add.
		 * @return This object, to allow chained function calls.
		 */
		SemanticVersion& AddPrerelease(const std::string& aString);

		/**
		 * @brief Add metadata to the version.
		 * @param aString A dot-separated metadata string to add.
		 * @return This object, to allow chained function calls.
		 */
		SemanticVersion& AddMetadata(const std::string& aString);

		/**
		 * @brief Check if the version is stable, meaning it has a non-zero major version, and is not a prerelease version.
		 * @return Whether the version is stable.
		 */
		bool IsStable() const;

		/**
		 * @brief Create a SemVer string from the current state.
		 * @return The version string.
		 */
		std::string ToString() const;

		bool operator==(const SemanticVersion& b) const;

		std::partial_ordering operator<=>(const SemanticVersion& b) const;

		std::uint64_t Major;
		std::uint64_t Minor;
		std::uint64_t Patch;
		std::vector<Identifier> Prerelease;
		std::vector<Identifier> Metadata;

	private:
		static std::strong_ordering CompareIdentifierLists(const std::vector<Identifier>& a, const std::vector<Identifier>& b);
	};

	struct SemanticVersion::Identifier
	{
		/**
		 * @brief Construct a list of identifiers from a dot-separated string.
		 * @param aString A dot-separated string containing identifier information.
		 * @param aTargetList An identifier list to add the identifiers to.
		 */
		static void FromString(const std::string& aString, std::vector<Identifier>& aTargetList);

		/**
		 * @brief Initialize a version identifier with a specified string.
		 * @param aString An identifier string.
		 */
		Identifier(const std::string& aString);

		/**
		 * @brief Creates a string from the version identifier.
		 * @return The resulting identifier string.
		 */
		std::string ToString() const;

		bool operator==(const Identifier& b) const;

		std::strong_ordering operator<=>(const Identifier& b) const;

		bool IsAlphanumeric = false;
		std::string Alphanumeric;
		std::uint64_t Numeric = 0;
	};

	inline SemanticVersion::SemanticVersion()
		: Major(0)
		, Minor(0)
		, Patch(0)
	{ }

	inline SemanticVersion::SemanticVersion(std::uint64_t aMajor, std::uint64_t aMinor, std::uint64_t aPatch)
		: Major(aMajor)
		, Minor(aMinor)
		, Patch(aPatch)
	{ }

	inline SemanticVersion::SemanticVersion(std::uint64_t aMajor, std::uint64_t aMinor, std::uint64_t aPatch, const std::string& aPrerelease)
		: Major(aMajor)
		, Minor(aMinor)
		, Patch(aPatch)
	{
		Identifier::FromString(aPrerelease, Prerelease);
	}

	inline SemanticVersion::SemanticVersion(std::string aSemanticVersion)
		: Major(0)
		, Minor(0)
		, Patch(0)
	{
		std::string preReleaseString;
		std::string metadataString;

		const size_t metadataIndex = aSemanticVersion.find('+');
		if (metadataIndex != std::string::npos)
		{
			metadataString = aSemanticVersion.substr(metadataIndex + 1);
			aSemanticVersion.erase(metadataIndex);
		}

		const size_t preReleaseIndex = aSemanticVersion.find('-');
		if (preReleaseIndex != std::string::npos)
		{
			preReleaseString = aSemanticVersion.substr(preReleaseIndex + 1);
			aSemanticVersion.erase(preReleaseIndex);
		}

		std::vector<Identifier> mainVersionIdentifiers;
		Identifier::FromString(aSemanticVersion, mainVersionIdentifiers);

		// Semantic version does not follow the pattern 'MAJOR.MINOR.PATCH'.
		if (mainVersionIdentifiers.size() != 3)
			return;

		// Main version identifiers cannot be alphanumeric.
		if (mainVersionIdentifiers[0].IsAlphanumeric || mainVersionIdentifiers[1].IsAlphanumeric || mainVersionIdentifiers[2].IsAlphanumeric)
			return;

		Major = mainVersionIdentifiers[0].Numeric;
		Minor = mainVersionIdentifiers[1].Numeric;
		Patch = mainVersionIdentifiers[2].Numeric;

		Identifier::FromString(preReleaseString, Prerelease);
		Identifier::FromString(metadataString, Metadata);
	}

	inline SemanticVersion& SemanticVersion::AddPrerelease(const std::string& aString)
	{
		Identifier::FromString(aString, Prerelease);
		return *this;
	}

	inline SemanticVersion& SemanticVersion::AddMetadata(const std::string& aString)
	{
		Identifier::FromString(aString, Metadata);
		return *this;
	}

	inline bool SemanticVersion::IsStable() const
	{
		return Major > 0 && Prerelease.size() == 0;
	}

	inline std::string SemanticVersion::ToString() const
	{
		std::ostringstream ss;
		ss << Major << '.' << Minor << '.' << Patch;

		for (std::size_t i = 0; i < Prerelease.size(); ++i)
		{
			if (i == 0)
				ss << '-';
			else
				ss << '.';
			ss << Prerelease[i].ToString();
		}

		for (std::size_t i = 0; i < Metadata.size(); ++i)
		{
			if (i == 0)
				ss << '+';
			else
				ss << '.';
			ss << Metadata[i].ToString();
		}

		return ss.str();
	}

	inline bool SemanticVersion::operator==(const SemanticVersion& b) const
	{
		return Major == b.Major
			&& Minor == b.Minor
			&& Patch == b.Patch
			&& Prerelease == b.Prerelease;
	}

	inline std::partial_ordering SemanticVersion::operator<=>(const SemanticVersion& b) const
	{
		if (Major != b.Major) return std::partial_order(Major, b.Major);
		if (Minor != b.Minor) return std::partial_order(Minor, b.Minor);
		if (Patch != b.Patch) return std::partial_order(Patch, b.Patch);

		{
			const bool isAPrerelease = !Prerelease.empty();
			const bool isBPrerelease = !b.Prerelease.empty();
			if (isAPrerelease != isBPrerelease)
			{
				if (isAPrerelease)
					return std::partial_ordering::less;
				else
					return std::partial_ordering::greater;
			}
		}

		{
			std::strong_ordering prereleaseOrder = CompareIdentifierLists(Prerelease, b.Prerelease);
			if (prereleaseOrder != std::strong_ordering::equivalent)
				return prereleaseOrder;
		}

		if (Metadata == b.Metadata)
			return std::strong_ordering::equal;
		else
			return std::strong_ordering::equivalent;
	}

	inline std::strong_ordering SemanticVersion::CompareIdentifierLists(const std::vector<Identifier>& a, const std::vector<Identifier>& b)
	{
		const std::size_t identifiersToCheck = std::min(a.size(), b.size());
		for (std::size_t i = 0; i < identifiersToCheck; ++i)
		{
			const std::strong_ordering order = a.at(i).operator<=>(b.at(i));
			if (order != std::strong_ordering::equivalent)
				return order;
		}

		// All were equal, check which list is larger.
		return std::strong_order(a.size(), b.size());
	}

	inline void SemanticVersion::Identifier::FromString(const std::string& aString, std::vector<Identifier>& outIdentifiers)
	{
		std::istringstream ss(aString);
		std::string subString;
		while (std::getline(ss, subString, '.'))
			outIdentifiers.push_back(Identifier(subString));
	}

	inline SemanticVersion::Identifier::Identifier(const std::string& aString)
		: Alphanumeric(aString)
		, IsAlphanumeric(true)
	{
		try
		{
			Numeric = std::stoull(aString);
			IsAlphanumeric = false;
		}
		catch (...)
		{
		}
	}

	inline std::string SemanticVersion::Identifier::ToString() const
	{
		return Alphanumeric;
	}

	inline bool SemanticVersion::Identifier::operator==(const Identifier& b) const
	{
		if (IsAlphanumeric != b.IsAlphanumeric)
			return false;

		if (IsAlphanumeric)
			return Alphanumeric == b.Alphanumeric;
		else
			return Numeric == b.Numeric;
	}

	inline std::strong_ordering SemanticVersion::Identifier::operator<=>(const Identifier& b) const
	{
		if (IsAlphanumeric != b.IsAlphanumeric)
			return std::strong_order(IsAlphanumeric, b.IsAlphanumeric);

		if (IsAlphanumeric)
			return std::strong_order(std::strcmp(Alphanumeric.c_str(), b.Alphanumeric.c_str()), 0);
		else if (Numeric != b.Numeric)
			return std::strong_order(Numeric, b.Numeric);

		return std::strong_ordering::equivalent;
	}
}