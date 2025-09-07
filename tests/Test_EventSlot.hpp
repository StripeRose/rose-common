#pragma once

#include <rose-common/EventSlot.hpp>

#include <catch2/generators/catch_generators_random.hpp>

#include <array>

namespace
{
	SCENARIO("An event slot with no arguments can be defined empty or as void")
	{
		GIVEN("One event slot of each type")
		{
			RoseCommon::EventSlot<> emptySlot;
			RoseCommon::EventSlot<void> voidSlot;

			THEN("Invoking the slots is done with no arguments")
			{
				emptySlot.Invoke();
				voidSlot.Invoke();
			}
		}
	}

	SCENARIO("Connecting to and invoking an event slot")
	{
		// Todo: Can this be rewritten to be generalized no matter the amount of arguments?

		GIVEN("An event slot with no arguments and one connection") // Should equal case with void argument
		{
			RoseCommon::EventSlot<> slot;
			bool wasInvoked = false;
			slot.Connect(nullptr, [&wasInvoked]() { wasInvoked = true; });

			WHEN("Invoking it will run the connected functions")
			{
				CHECK(!wasInvoked);
				slot.Invoke();
				CHECK(wasInvoked);
			}
		}

		GIVEN("An event slot with void argument and one connection") // Should equal case with no arguments
		{
			RoseCommon::EventSlot<void> slot;
			bool wasInvoked = false;
			slot.Connect(nullptr, [&wasInvoked]() { wasInvoked = true; });

			WHEN("Invoking it will run the connected functions")
			{
				CHECK(!wasInvoked);
				slot.Invoke();
				CHECK(wasInvoked);
			}
		}

		GIVEN("An event slot with one reference argument and one connection")
		{
			RoseCommon::EventSlot<int&> slot;
			int invokeCount = 0;
			slot.Connect(nullptr, [](int& anInvokeCount) { anInvokeCount += 1; });

			WHEN("Invoking it will run the connected functions")
			{
				CHECK(invokeCount == 0);
				slot.Invoke(invokeCount);
				CHECK(invokeCount == 1);
			}
		}

		GIVEN("An event slot with two arguments and one connection")
		{
			static constexpr const char* TestString = "A testing string";

			RoseCommon::EventSlot<int&, const char*> slot;
			int invokeCount = 0;
			slot.Connect(nullptr, [](int& anInvokeCount, const char* aString) {
				CHECK(std::strcmp(aString, TestString) == 0);
				anInvokeCount += 1;
				});

			WHEN("Invoking it will run the connected functions")
			{
				CHECK(invokeCount == 0);
				slot.Invoke(invokeCount, TestString);
				CHECK(invokeCount == 1);
			}
		}
	}

	SCENARIO("Connecting and disconnecting with multiple registrars for the same slot")
	{
		GIVEN("An event slot with connections from multiple registrars")
		{
			RoseCommon::EventSlot<> slot;

			// The invoke count addresses are also used as fake registrars for this test.
			std::array<int, 5> invokeCounts;
			invokeCounts.fill(0);

			slot.Connect(&invokeCounts[0], [&invokeCounts]() { invokeCounts[0] += 1; });
			slot.Connect(&invokeCounts[1], [&invokeCounts]() { invokeCounts[1] += 1; });
			slot.Connect(&invokeCounts[2], [&invokeCounts]() { invokeCounts[2] += 1; });
			// invokeCounts[3] does not have a connection and thus should stay at zero.
			slot.Connect(&invokeCounts[4], [&invokeCounts]() { invokeCounts[4] += 1; });

			WHEN("Invoking the slot")
			{
				slot.Invoke();

				THEN("Each connected callback was run sequentially (in any order)")
				{
					CHECK(invokeCounts[0] == 1);
					CHECK(invokeCounts[1] == 1);
					CHECK(invokeCounts[2] == 1);
					CHECK(invokeCounts[3] == 0);
					CHECK(invokeCounts[4] == 1);
				}
			}

			WHEN("Disconnecting a specific registrar and then invoking the slot")
			{
				slot.Disconnect(&invokeCounts[1]);
				slot.Invoke();

				THEN("No callback registered by the registrar has been run")
				{
					CHECK(invokeCounts[0] == 1);
					CHECK(invokeCounts[1] == 0);
					CHECK(invokeCounts[2] == 1);
					CHECK(invokeCounts[3] == 0);
					CHECK(invokeCounts[4] == 1);
				}
			}
		}
	}

	SCENARIO("Connecting multiple callbacks from the same registrar to a single slot")
	{
		GIVEN("An event slot with no arguments and one connection")
		{
			RoseCommon::EventSlot<> slot;
			bool wasInvoked = false;
			CHECK(slot.Connect(nullptr, [&wasInvoked]() { wasInvoked = true; }));

			WHEN("Connecting a second callback")
			{
				const bool wasSucceessful = slot.Connect(nullptr, []() {});
				THEN("The connection fails")
				{
					CHECK(!wasSucceessful);
				}
			}
		}
	}

	SCENARIO("Invoking a slot via named method or operator")
	{
		GIVEN("An event slot with no arguments and one connection")
		{
			RoseCommon::EventSlot<> slot;
			bool wasInvoked = false;
			slot.Connect(nullptr, [&wasInvoked]() { wasInvoked = true; });

			WHEN("Invoking it with the named method")
			{
				THEN("The function is run")
				{
					CHECK(!wasInvoked);
					slot.Invoke();
					CHECK(wasInvoked);
				}
			}

			WHEN("Invoking it with the operator")
			{
				THEN("The function is run")
				{
					CHECK(!wasInvoked);
					slot();
					CHECK(wasInvoked);
				}
			}
		}
	}
}