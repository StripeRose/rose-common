#pragma once

#include "MacroHelpers.hpp"

#include <chrono>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace RoseCommon::Profiling
{
	/**
	 * @brief A profiling stack-frame.
	 */
	struct ProfilingFrame
	{
		size_t UID = 0;
		unsigned int Level = 0;
		const char* FileAndLine = nullptr;
		const char* Function = nullptr;
		std::chrono::high_resolution_clock::time_point StartTime;
		std::chrono::high_resolution_clock::time_point EndTime;
		std::chrono::microseconds AverageDuration = std::chrono::microseconds(0);

		std::string Label;

		template <typename T>
		T GetDuration() const
		{
			return std::chrono::duration_cast<T>(EndTime - StartTime);
		}
	};

	/**
	 * @brief A profiler marker.
	 */
	struct ProfilingMarker
	{
		const char* FileAndLine = nullptr;
		const char* Function = nullptr;
		std::chrono::high_resolution_clock::time_point Time;

		std::string Label;
	};

	struct ProfilingData
	{
		std::chrono::high_resolution_clock::time_point StartTime;
		std::chrono::high_resolution_clock::time_point EndTime;
		std::vector<ProfilingFrame> Frames;
		std::vector<ProfilingMarker> Markers;

		template <typename T>
		T GetDuration() const
		{
			return std::chrono::duration_cast<T>(EndTime - StartTime);
		}
	};

	/**
	 * @brief A profiler that measures and reports back the data of marked up code.
	 * 
	 * @todo Expand to allow multi-threaded profiling.
	 */
	class Profiler
	{
	public:
		~Profiler();

		/**
		 * @brief Begin profiling the following code with a specific data target.
		 * @param aProfileTarget The target to use for the collected data.
		 */
		void BeginProfile(ProfilingData& aProfileTarget);

		/**
		 * @brief Begin profiling the following code.
		 */
		void BeginProfile();

		/**
		 * @brief Stop profiling the code and finalize the data.
		 */
		void EndProfile();

		/**
		 * @brief Get the collected profiling data, if a specific data target was not provided.
		 * @return A pointer to the collected data.
		 */
		std::shared_ptr<ProfilingData> GetResultData() const;

	public:
		/**
		 * @brief A class which collects data from the function that creates it, and upon destruction, reports the data to the running profiler.
		 */
		struct FrameSubmitScope
		{
			FrameSubmitScope(size_t aUID, const char* aFileAndLine, const char* aFunctionName, const std::optional<std::string>& aLabel = { });
			~FrameSubmitScope();

		private:
			ProfilingFrame myFrame;
		};

		/**
		 * @brief Submit a named marker to the profiling data. Should be used by the PROFILE_MARKER() macro.
		 * @param aFileAndLine The source file and line which submits the marker.
		 * @param aFunctionName The source function where the marker is submitted from.
		 * @param aLabel A name for the marker.
		 */
		static void SubmitMarker(const char* aFileAndLine, const char* aFunctionName, const std::string& aLabel);

	private:
		void BeginProfileInternal();

		void Submit(const ProfilingFrame& aFrame);
		void Submit(const ProfilingMarker& aMarker);

	private:
		std::atomic_bool myIsProfiling;

		std::shared_ptr<ProfilingData> myProfilingData;
		ProfilingData* myProfilingDataTarget;

		std::map<size_t, std::chrono::microseconds> myAverages;
	};
}

#define PROFILE_SCOPE_NAMED(ScopeName) RoseCommon::Profiling::Profiler::FrameSubmitScope CONCATENATE(profilerScope, __COUNTER__)(__COUNTER__, __FILE__ "(" STRINGIZE(__LINE__) ")", __func__, ScopeName)
#define PROFILE_SCOPE() PROFILE_SCOPE_NAMED({})

#define PROFILE_MARKER(MarkerName) RoseCommon::Profiling::Profiler::SubmitMarker(__FILE__ "(" STRINGIZE(__LINE__) ")", __func__, MarkerName)