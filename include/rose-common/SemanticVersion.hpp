#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace RoseCommon
{
	// See http://semver.org/ for further details.
	struct SemanticVersion
	{
		struct Identifier
		{
			static void FromString(const std::string& aString, std::vector<Identifier>& outIdentifiers)
			{
				std::istringstream ss(aString);
				std::string subString;
				while (std::getline(ss, subString, '.'))
					outIdentifiers.push_back(Identifier(subString));
			}

			Identifier(const std::string& aString)
				: Alphanumeric(aString)
				, IsAlphanumeric(true)
			{
				try
				{
					Numeric = std::stoull(aString);
					IsAlphanumeric = false;
				}
				catch (...)
				{ }
			}

			std::string ToString() const
			{
				return Alphanumeric;
			}

			bool operator==(const Identifier& b) const
			{
				if (IsAlphanumeric != b.IsAlphanumeric)
					return false;

				if (IsAlphanumeric)
					return Alphanumeric == b.Alphanumeric;
				else
					return Numeric == b.Numeric;
			}

			std::strong_ordering operator<=>(const Identifier& b) const
			{
				if (IsAlphanumeric != b.IsAlphanumeric)
					return std::strong_order(IsAlphanumeric, b.IsAlphanumeric);

				if (IsAlphanumeric)
					return std::strong_order(std::strcmp(Alphanumeric.c_str(), b.Alphanumeric.c_str()), 0);
				else if (Numeric != b.Numeric)
					return std::strong_order(Numeric, b.Numeric);

				return std::strong_ordering::equivalent;
			}

			bool IsAlphanumeric = false;
			std::string Alphanumeric;
			std::uint64_t Numeric = 0;
		};

		SemanticVersion()
			: Major(0)
			, Minor(0)
			, Patch(0)
		{ }

		SemanticVersion(std::uint64_t aMajor, std::uint64_t aMinor, std::uint64_t aPatch)
			: Major(aMajor)
			, Minor(aMinor)
			, Patch(aPatch)
		{ }

		SemanticVersion(std::uint64_t aMajor, std::uint64_t aMinor, std::uint64_t aPatch, const std::string& aPrerelease)
			: Major(aMajor)
			, Minor(aMinor)
			, Patch(aPatch)
		{
			Identifier::FromString(aPrerelease, Prerelease);
		}

		SemanticVersion(std::string aSemanticVersion)
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

		SemanticVersion& AddPrerelease(const std::string& aString)
		{
			Identifier::FromString(aString, Prerelease);
			return *this;
		}

		SemanticVersion& AddMetadata(const std::string& aString)
		{
			Identifier::FromString(aString, Metadata);
			return *this;
		}

		bool IsStable() const { return Major > 0 && Prerelease.size() == 0; }

		std::string ToString() const
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

		bool operator==(const SemanticVersion& b) const
		{
			return Major == b.Major
				&& Minor == b.Minor
				&& Patch == b.Patch
				&& Prerelease == b.Prerelease;
		}

		std::partial_ordering operator<=>(const SemanticVersion& b) const
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

		// Incremented Major determines incompatible API changes.
		std::uint64_t Major;

		// Incremented Minor when functionality is changed in a backwards compatible manner.
		std::uint64_t Minor;

		// Incremented Patch for backwards-compatible bug fixes.
		std::uint64_t Patch;

		/// <summary>
		/// Pre-release version may be denoted by a series of dot-separated identifiers.
		/// Identifiers MUST comprise only ASCII alphanumerics and hyphens.
		/// Numeric identifiers MUST NOT include leading zeroes.
		/// Examples: "alpha", "alpha.1", "0.3.7", "x.7.z.92"
		/// </summary>
		std::vector<Identifier> Prerelease;

		/// <summary>
		/// Build metadata may be denoted by a series of dot-separated identifiers.
		/// Identifiers MUST comprise only ASCII alphanumerics and hyphens.
		/// Identifiers MUST NOT be empty.
		/// Examples: "001", "20130313144700", "exp.sha.5114f85", "21AF26D3----117B344092BD"
		/// </summary>
		std::vector<Identifier> Metadata;

	private:
		static std::strong_ordering CompareIdentifierLists(const std::vector<Identifier>& a, const std::vector<Identifier>& b)
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
	};
}