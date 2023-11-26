#pragma once

#include "MacroHelpers.hpp"

#include <chrono>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace RoseCommon::Profiling
{
	// Represents a single profiling stack-frame.
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

	// Represents a single profiler marker
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

	class Profiler
	{
	public:
		~Profiler();

		void BeginProfile(ProfilingData& aProfileTarget);
		void BeginProfile();
		void EndProfile();

		std::shared_ptr<ProfilingData> GetResultData() const;

	public:
		// Don't use directly. Use the PROFILE_SCOPE*() macros.
		struct FrameSubmitScope
		{
			FrameSubmitScope(size_t aUID, const char* aFileAndLine, const char* aFunctionName, const std::optional<std::string>& aLabel = { });
			~FrameSubmitScope();

		private:
			ProfilingFrame myFrame;
		};

		// Don't use directly. Use the PROFILE_MARKER() macro.
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