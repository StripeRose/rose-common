#pragma once

//https://github.com/StripeRose/atrium/commit/84d4b06db6ce12513fbc5d34c870abf8b8c9dd5b#diff-64bc600a22f3a5003637ab6fdfe5dd43cf940620ca24f89dd8a035f012af02d6

#include "RoseCommon_Namespace.hpp"

#include <any>
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <string_view>

#if defined(_WIN32) || defined(__CYGWIN__)
#include <Windows.h>
#ifdef _MSC_VER
#define ROSECOMMON_VISIBILITY_EXPORT __declspec(dllexport)
#else
#define ROSECOMMON_VISIBILITY_EXPORT __attribute__ ((dllexport))
#endif
#else
#define ROSECOMMON_VISIBILITY_EXPORT __attribute__ ((visibility("default")))
#endif

#ifdef ROSECOMMON_PLUGIN_DLL
#define ROSECOMMON_PLUGIN_EXPORT ROSECOMMON_VISIBILITY_EXPORT
#else
#define ROSECOMMON_PLUGIN_EXPORT
#endif

// #define ROSECOMMON_DECLARE_PLUGIN(T) \
// extern "C" { \
// 	ROSECOMMON_PLUGIN_EXPORT Atrium::PluginInfoFunction GetPluginInfoFunction() { return &T::GetPluginInfo; } \
// }

namespace ROSECOMMON_NAMESPACE
{
	template <typename PluginCapabilitiesT>
	class PluginLibrary
	{
	public:
		PluginLibrary(const std::string_view aPluginInfoFunction, const std::filesystem::path& aPluginDirectory);

		std::shared_ptr<const PluginCapabilitiesT> GetPlugin(const std::wstring_view aPluginName) const;

	private:
		struct PluginInstance : public PluginCapabilitiesT
		{
			~PluginInstance() override;

			std::any SourceLibraryHandle;
		};

		std::shared_ptr<PluginInstance> LoadPluginLibrary(const std::filesystem::path& aLibraryPath) const;
		std::filesystem::path FindFileInDirectory(const std::filesystem::path& aDirectory, std::wstring_view& aFileName);

		std::map<std::filesystem::path /* stem */, std::weak_ptr<PluginInstance>> myLoadedPlugins;
		std::filesystem::path myPluginDirectory;
		std::string myPluginInfoFunction;
	};
}

#include "Plugin_Impl.inl"
