#include "../include/rose-common/Profiling.h"
#include "../include/rose-common/Profiling_Formatting.h"

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

namespace RoseCommon::Profiling
{
	namespace ProfilerInternal
	{
		struct ActiveProfiler
		{
			std::function<void(const ProfilingFrame&)> SubmitFrame;
			std::function<void(const ProfilingMarker&)> SubmitMarker;
		};

		static std::map<Profiler*, ActiveProfiler> ourActiveProfilers;
		static unsigned int ourProfilerLevel = 0;

		void Submit(const ProfilingFrame& aFrame)
		{
			for (auto& activeProfiler : ourActiveProfilers)
				activeProfiler.second.SubmitFrame(aFrame);
		}

		void Submit(const ProfilingMarker& aMarker)
		{
			for (auto& activeProfiler : ourActiveProfilers)
				activeProfiler.second.SubmitMarker(aMarker);
		}
	}

	Profiler::FrameSubmitScope::FrameSubmitScope(size_t aUID, const char* aFileAndLine, const char* aFunctionName, const std::optional<std::string>& aLabel)
	{
		myFrame.StartTime = std::chrono::high_resolution_clock::now();

		myFrame.UID = aUID;
		myFrame.FileAndLine = aFileAndLine;
		myFrame.Function = aFunctionName;
		myFrame.Label = aLabel.value_or("");
		myFrame.Level = ProfilerInternal::ourProfilerLevel;

		ProfilerInternal::ourProfilerLevel += 1;
	}

	Profiler::FrameSubmitScope::~FrameSubmitScope()
	{
		ProfilerInternal::ourProfilerLevel -= 1;

		myFrame.EndTime = std::chrono::high_resolution_clock::now();

		ProfilerInternal::Submit(myFrame);
	}

	void Profiler::SubmitMarker(const char* aFileAndLine, const char* aFunctionName, const std::string& aLabel)
	{
		ProfilingMarker marker;
		marker.Time = std::chrono::high_resolution_clock::now();

		marker.FileAndLine = aFileAndLine;
		marker.Function = aFunctionName;
		marker.Label = aLabel;

		ProfilerInternal::Submit(marker);
	}

	Profiler::~Profiler()
	{
		if (myIsProfiling)
			EndProfile();
	}

	void Profiler::BeginProfile(ProfilingData& aProfileTarget)
	{
		aProfileTarget.Frames.clear();
		aProfileTarget.Markers.clear();

		myProfilingData.reset();
		myProfilingDataTarget = &aProfileTarget;

		BeginProfileInternal();
	}

	void Profiler::BeginProfile()
	{
		myProfilingData = std::make_shared<ProfilingData>();
		myProfilingDataTarget = myProfilingData.get();
		BeginProfileInternal();
	}

	void Profiler::EndProfile()
	{
		myIsProfiling = false;
		ProfilerInternal::ourActiveProfilers.erase(this);
		myProfilingDataTarget->EndTime = std::chrono::high_resolution_clock::now();
	}

	std::shared_ptr<ProfilingData> Profiler::GetResultData() const
	{
		if (myIsProfiling)
			return nullptr;
		else
			return myProfilingData;
	}

	void Profiler::BeginProfileInternal()
	{
		myProfilingDataTarget->StartTime = std::chrono::high_resolution_clock::now();

		ProfilerInternal::ActiveProfiler& activeProfiler = ProfilerInternal::ourActiveProfilers[this];
		activeProfiler.SubmitFrame = [this](const ProfilingFrame& aFrame) {this->Submit(aFrame); };
		activeProfiler.SubmitMarker = [this](const ProfilingMarker& aMarker) {this->Submit(aMarker); };

		myIsProfiling = true;
	}

	void Profiler::Submit(const ProfilingFrame& aFrame)
	{
		if (!myAverages.contains(aFrame.UID))
		{
			myAverages[aFrame.UID] = aFrame.GetDuration<std::chrono::microseconds>();
		}
		else
		{
			std::chrono::microseconds& average = myAverages[aFrame.UID];
			average += aFrame.GetDuration<std::chrono::microseconds>();
			average /= 2;
		}

		ProfilingFrame& frame = myProfilingDataTarget->Frames.emplace_back(aFrame);
		frame.AverageDuration = myAverages[frame.UID];
	}

	void Profiler::Submit(const ProfilingMarker& aMarker)
	{
		myProfilingDataTarget->Markers.push_back(aMarker);
	}
}

namespace RoseCommon::Profiling
{
	class ProfilingDataTreeFormatter
	{
	public:
		void Resolve(const ProfilingData& someData)
		{
			myProfilingData = someData;

			for (ProfilingFrame& frame : myProfilingData.Frames)
				myData.emplace_back().Frame = &frame;

			for (ProfilingMarker& marker : myProfilingData.Markers)
				myData.emplace_back().Marker = &marker;

			std::sort(myData.begin(), myData.end());
		}

		void ToStream(std::ostream& aStream) const
		{
			aStream << "Total: " << myProfilingData.GetDuration<std::chrono::milliseconds>().count() << " ms\n";

			for (const ProfilingEntry& data : myData)
				data.ToStream(aStream);
		}

	private:
		struct ProfilingEntry
		{
			void ToStream(std::ostream& aStream) const
			{
				if (Marker)
				{
					aStream << "---[ " << Marker->Label.c_str() << " ]-------------------------------------------------\n";
				}
				else
				{
					const std::string indentationString(Frame->Level, '\t');
					const char* indentation = indentationString.c_str();

					if (Frame->Label.empty())
						aStream << indentation << Frame->Function;
					else
						aStream << indentation << Frame->Label.c_str() << " (" << Frame->Function << ")";

					const std::chrono::microseconds duration = Frame->GetDuration<std::chrono::microseconds>();
					aStream << " " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " ms.";
					aStream << " Avg. " << std::chrono::duration_cast<std::chrono::milliseconds>(Frame->AverageDuration).count() << " ms.\n";

					aStream << indentation << "\t\t" << Frame->FileAndLine << "\n";
				}
			}

			bool operator<(const ProfilingEntry& aRHV) const
			{
				std::chrono::high_resolution_clock::time_point lhvTimePoint;
				std::chrono::high_resolution_clock::time_point rhvTimePoint;

				if (Marker)
					lhvTimePoint = Marker->Time;
				else
					lhvTimePoint = Frame->StartTime;

				if (aRHV.Marker)
					rhvTimePoint = aRHV.Marker->Time;
				else
					rhvTimePoint = aRHV.Frame->StartTime;

				return lhvTimePoint < rhvTimePoint;
			}

			ProfilingMarker* Marker = nullptr;
			ProfilingFrame* Frame = nullptr;
		};

	private:
		ProfilingData myProfilingData;
		std::vector<ProfilingEntry> myData;
	};
}

std::ostream& operator<<(std::ostream& os, const RoseCommon::Profiling::ProfilingData& data)
{
	RoseCommon::Profiling::ProfilingDataTreeFormatter formatter;
	formatter.Resolve(data);
	formatter.ToStream(os);
	return os;
}
