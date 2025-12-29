// Main source file, which includes all test-headers.
// The main function is handled by Catch2.

// First we define some extra extensions that aren't available in Catch2.
#define TEMPLATE_SCENARIO(...) TEMPLATE_TEST_CASE("Scenario: " __VA_ARGS__)
#define TEMPLATE_LIST_SCENARIO(...) TEMPLATE_LIST_TEST_CASE("Scenario: " __VA_ARGS__)

#include <Test_Color.hpp>
// #include <Test_CommandLineParser.hpp>
// #include <Test_Debug.hpp>
// #include <Test_Enum.hpp>
#include <Test_EventSlot.hpp>
#include <Test_Graphs.hpp>
// #include <Test_MacroHelpers.hpp>
// #include <Test_Profiling.hpp>
// #include <Test_Range.hpp>
// #include <Test_SemanticVersion.hpp>
#include <Test_StoreReset.hpp>
// #include <Test_StringUtilities.hpp>

// File format
// #include <fileformat/Test_Ini.hpp>

// Math
// #include <math/Test_Common.hpp>
// #include <math/Test_Constants.hpp>
// #include <math/Test_Curve.hpp>
// #include <math/Test_Geometry.hpp>
// #include <math/Test_Matrix.hpp>
// #include <math/Test_Matrix3D.hpp>
// #include <math/Test_Quaternion.hpp>
// #include <math/Test_Trigonometry.hpp>
// #include <math/Test_Vector.hpp>