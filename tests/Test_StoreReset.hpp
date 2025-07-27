#pragma once

#include <catch2/catch_test_macros.hpp>

#include <rose-common/StoreReset.hpp>

#include <string>

namespace
{
	SCENARIO("StoreReset<T> can set and reset a value")
	{
		// Todo: Expand to use a random generator, and multiple types.
		GIVEN("An std::string")
		{
			std::string text = "Original";

			WHEN("A StoreReset<std::string> is created with a new value")
			{
				{
					RoseCommon::StoreReset<std::string> reset(text, "NewValue");

					THEN("The variable is updated with the new value")
					{
						CHECK(text == "NewValue");
					}
				}

				AND_WHEN("The StoreReset goes out of scope")
				{
					THEN("The variable is restored with the previous value")
					{
						CHECK(text == "Original");
					}
				}
			}
		}
	}
}