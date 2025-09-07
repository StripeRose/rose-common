#pragma once

#include <rose-common/EventSlot.hpp>

#include <catch2/generators/catch_generators_random.hpp>

#include <array>
#include <bitset>

namespace
{
	SCENARIO("An EventSlot with no arguments can be defined empty or as void")
	{
		GIVEN("One EventSlot of each type")
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

	SCENARIO("Connecting to and invoking an EventSlot")
	{
		// Todo: Can this be rewritten to be generalized no matter the amount of arguments?

		GIVEN("An EventSlot with no arguments and one connection") // Should equal case with void argument
		{
			RoseCommon::EventSlot<> slot;
			bool wasInvoked = false;
			slot.Connect([&wasInvoked]() { wasInvoked = true; });

			WHEN("Invoking it will run the connected functions")
			{
				CHECK(!wasInvoked);
				slot.Invoke();
				CHECK(wasInvoked);
			}
		}

		GIVEN("An EventSlot with void argument and one connection") // Should equal case with no arguments
		{
			RoseCommon::EventSlot<void> slot;
			bool wasInvoked = false;
			slot.Connect([&wasInvoked]() { wasInvoked = true; });

			WHEN("Invoking it will run the connected functions")
			{
				CHECK(!wasInvoked);
				slot.Invoke();
				CHECK(wasInvoked);
			}
		}

		GIVEN("An EventSlot with one reference argument and one connection")
		{
			RoseCommon::EventSlot<int&> slot;
			int invokeCount = 0;
			slot.Connect([](int& anInvokeCount) { anInvokeCount += 1; });

			WHEN("Invoking it will run the connected functions")
			{
				CHECK(invokeCount == 0);
				slot.Invoke(invokeCount);
				CHECK(invokeCount == 1);
			}
		}

		GIVEN("An EventSlot with two arguments and one connection")
		{
			static constexpr const char* TestString = "A testing string";

			RoseCommon::EventSlot<int&, const char*> slot;
			int invokeCount = 0;
			slot.Connect([](int& anInvokeCount, const char* aString) {
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

	SCENARIO("Connecting multiple callbacks")
	{
		GIVEN("An EventSlot with callbacks from multiple registrars, where each may have multiple callbacks")
		{
			RoseCommon::EventSlot<> slot;

			// Integers used as stand-ins for registrars.
			int registrarA = 0;
			int registrarB = 0;

			std::bitset<6> invokeBits;
			const RoseCommon::EventCallbackID a = slot.Connect(&registrarA, [&invokeBits]() { invokeBits.set(0); });
			const RoseCommon::EventCallbackID b = slot.Connect(&registrarA, [&invokeBits]() { invokeBits.set(1); });
			const RoseCommon::EventCallbackID c = slot.Connect(&registrarB, [&invokeBits]() { invokeBits.set(2); });
			const RoseCommon::EventCallbackID d = slot.Connect(&registrarB, [&invokeBits]() { invokeBits.set(3); });
			const RoseCommon::EventCallbackID e = slot.Connect([&invokeBits]() { invokeBits.set(4); });
			const RoseCommon::EventCallbackID f = slot.Connect([&invokeBits]() { invokeBits.set(5); });

			WHEN("Invoking the slot")
			{
				slot.Invoke();

				THEN("All callbacks are run")
				{
					CHECK(invokeBits.test(0));
					CHECK(invokeBits.test(1));
					CHECK(invokeBits.test(2));
					CHECK(invokeBits.test(3));
					CHECK(invokeBits.test(4));
					CHECK(invokeBits.test(5));
				}
			}

			WHEN("Disconnecting by registrar")
			{
				slot.Disconnect(&registrarB);

				AND_THEN("Invoking the slot")
				{
					slot.Invoke();

					THEN("Only the remaining connected callbacks are run")
					{
						CHECK(invokeBits.test(0));
						CHECK(invokeBits.test(1));
						CHECK(!invokeBits.test(2));
						CHECK(!invokeBits.test(3));
						CHECK(invokeBits.test(4));
						CHECK(invokeBits.test(5));
					}
				}
			}

			WHEN("Disconnecting by IDs")
			{
				slot.Disconnect(b);
				slot.Disconnect(c);
				slot.Disconnect(e);

				AND_THEN("Invoking the slot")
				{
					slot.Invoke();

					THEN("Only the remaining connected callbacks are run")
					{
						CHECK(invokeBits.test(0));
						CHECK(!invokeBits.test(1));
						CHECK(!invokeBits.test(2));
						CHECK(invokeBits.test(3));
						CHECK(!invokeBits.test(4));
						CHECK(invokeBits.test(5));
					}
				}
			}
		}
	}

	SCENARIO("Moving and copying EventCallbackID structures")
	{
		// Here to make sure common operations don't become unavailable.

		std::vector<RoseCommon::EventCallbackID> callbacks;

		RoseCommon::EventSlot<> slot1;
		RoseCommon::EventSlot<int> slot2;

		callbacks.emplace_back(slot1.Connect([]() {}));
		callbacks.push_back(slot2.Connect([](int) {}));

		const auto id1_2 = slot1.Connect([]() {});
		callbacks.emplace_back(id1_2);
		callbacks.push_back(id1_2);

		RoseCommon::EventCallbackID id2_2 = slot2.Connect([](int) {});
		RoseCommon::EventCallbackID id2_2copy = id2_2;
		callbacks.push_back(std::move(id2_2));

		// Original should remain the same even after the move to prevent creating an invalid ID.
		CHECK(std::memcmp(&id2_2, &id2_2copy, sizeof(id2_2)) == 0);
	}

	SCENARIO("Invoking a slot via named method or operator")
	{
		GIVEN("An EventSlot with no arguments and one connection")
		{
			RoseCommon::EventSlot<> slot;
			bool wasInvoked = false;
			slot.Connect([&wasInvoked]() { wasInvoked = true; });

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