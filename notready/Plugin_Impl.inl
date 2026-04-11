namespace ROSECOMMON_NAMESPACE
{
	template <typename PluginCapabilitiesT>
	PluginLibrary<PluginCapabilitiesT>::PluginLibrary(const std::string_view aPluginInfoFunction, const std::filesystem::path& aPluginDirectory)
		: myPluginInfoFunction(aPluginInfoFunction)
	{
		if (std::filesystem::is_directory(aPluginDirectory))
			myPluginDirectory = aPluginDirectory;
		else
			throw std::invalid_argument("Given plugin path was not a directory.");
	}

	template <typename PluginCapabilitiesT>
	std::shared_ptr<const PluginCapabilitiesT> PluginLibrary<PluginCapabilitiesT>::GetPlugin(const std::wstring_view aPluginName) const
	{
		#if _DEBUG

		const std::string debugLibraryFileName = std::format(L"{}.d.dll", aPluginName);
		if (myLoadedPlugins.contains(debugLibraryFileName))
			return myLoadedPlugins[debugLibraryFileName].lock();

		#endif

		const std::string libraryFileName = std::format(L"{}.dll", aPluginName);
		if (myLoadedPlugins.contains(libraryFileName))
			return myLoadedPlugins[libraryFileName].lock();

		std::shared_ptr<PluginInstance> newPluginInstance;

		#if _DEBUG
		newPluginInstance = LoadPluginLibrary(FindFileInDirectory(myPluginDirectory, debugLibraryFileName));
		#endif

		if (newPluginInstance)
			newPluginInstance = LoadPluginLibrary(FindFileInDirectory(myPluginDirectory, libraryFileName));

		myLoadedPlugins[aPluginName] = newPluginInstance;
		return std::static_pointer_cast<PluginCapabilitiesT>(newPluginInstance);
	}

	template <typename PluginCapabilitiesT>
	std::shared_ptr<typename PluginLibrary<PluginCapabilitiesT>::PluginInstance> PluginLibrary<PluginCapabilitiesT>::LoadPluginLibrary(const std::filesystem::path& aLibraryPath) const
	{
		#ifdef _WIN32
		if (!std::filesystem::is_regular_file(aLibraryPath))
			return nullptr;

		HMODULE hModule = LoadLibraryW(aLibraryPath.c_str());

		if (!hModule)
		{
			// Err: Not a valid library.
			return nullptr;
		}

		using PluginInfoFunction = void(*)(PluginCapabilitiesT&);

		PluginInfoFunction(*getPluginInfoFunction)() = reinterpret_cast<PluginInfoFunction(*)()>(
			GetProcAddress(hModule, myPluginInfoFunction.c_str())
			);

		if (!getPluginInfoFunction)
		{
			// Err: Failed to find plugin info function.
			return nullptr;
		}

		std::shared_ptr<PluginInstance> newInstance = std::make_shared<PluginInstance>();
		if (newInstance)
		{
			getPluginInfoFunction(*newInstance);
			newInstance->SourceLibraryHandle = hModule;
		}
		else
		{
			// Err: Couldn't create instance, free the library again.
			FreeLibrary(hModule);
		}

		return newInstance;
		#endif
	}

	template <typename PluginCapabilitiesT>
	std::filesystem::path PluginLibrary<PluginCapabilitiesT>::FindFileInDirectory(const std::filesystem::path& aDirectory, std::wstring_view& aFileName)
	{
		for (const auto& entry : std::filesystem::directory_iterator(aDirectory))
		{
			if (entry.is_directory())
			{
				const std::filesystem::path path = FindFileInDirectory(entry, aFileName);
				if (!path.empty())
					return path;
			}
			else if (entry.path().filename() == aFileName)
			{
				return entry.path();
			}
		}

		return std::filesystem::path();
	}

	template <typename PluginCapabilitiesT>
	PluginLibrary<PluginCapabilitiesT>::PluginInstance::~PluginInstance()
	{
		#if defined(_WIN32) || defined(__CYGWIN__)
		HMODULE handle = std::any_cast<HMODULE>(SourceLibraryHandle);
		if (handle)
			FreeLibrary(handle);
		#else
		#error "Plugin instance missing destructor on this platform."
		#endif
	}
}