#pragma once

#include "Profiling.hpp"

//namespace RoseCommon::Profiling
//{
//    //struct TimelineFormatParameters
//    //{
//    //    // Total width in characters.
//    //    unsigned int Width = 64;
//
//    //    // Maximum frame depth to print.
//    //    std::optional<unsigned int> MaxDepth;
//
//    //    bool PrintMarkers = true;
//    //    bool PrintDuration = true;
//    //};
//
//    void PrintToLog(const ProfilingData& data);
//}

std::ostream& operator<<(std::ostream& os, const RoseCommon::Profiling::ProfilingData& data);
