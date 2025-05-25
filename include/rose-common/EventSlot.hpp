#pragma once

#include <functional>
#include <map>

namespace RoseCommon
{
	/**
	 * @brief An interface for defining events which other objects can listen for the invokation of.
	 * @tparam ...CallbackArguments A list of argument types the event must use.
	 */
	template <typename ... CallbackArguments>
	class EventSlot
	{
	public:
		/**
		 * @brief Invoke all currently connected functions.
		 * @param ...someArguments A list of arguments to call the connected functions with.
		 */
		void Invoke(CallbackArguments... someArguments) const
		{
			for (const auto& callback : myCallbacks)
			{
				if (callback.second)
					callback.second(someArguments...);
			}
		}

		/**
		 * @brief Register new function to be called when the EventSlot is invoked.
		 * @param aRegistrar A pointer to attribute the connection to.
		 * @param aFunction A function to connect.
		 * @return Whether the operation was successful.
		 */
		bool Connect(void* aRegistrar, std::function<void(CallbackArguments...)> aFunction)
		{
			if (myCallbacks.contains(aRegistrar))
				return false;

			myCallbacks[aRegistrar] = aFunction;
			return true;
		}

		/**
		 * @brief Unregister a function from the specified registrar.
		 * @param aRegistrar A registrar to disconnect the function from.
		 */
		void Disconnect(void* aRegistrar)
		{
			if (myCallbacks.contains(aRegistrar))
				myCallbacks.at(aRegistrar) = nullptr;
		}

		void operator()(CallbackArguments... someArguments) const
		{
			Invoke(someArguments...);
		}

	private:
		std::map<void*, std::function<void(CallbackArguments...)>> myCallbacks;
	};

	/**
	 * @brief An interface for defining events which other objects can listen for the invokation of.
	 */
	template <>
	class EventSlot<>
	{
	public:
		/**
		 * @brief Invoke all currently connected functions.
		 */
		void Invoke() const
		{
			for (const auto& callback : myCallbacks)
			{
				if (callback.second)
					callback.second();
			}
		}

		/**
		 * @brief Register new function to be called when the EventSlot is invoked.
		 * @param aRegistrar A pointer to attribute the connection to.
		 * @param aFunction A function to connect.
		 * @return Whether the operation was successful.
		 */
		bool Connect(void* aRegistrar, std::function<void()> aFunction)
		{
			if (myCallbacks.contains(aRegistrar))
				return false;

			myCallbacks[aRegistrar] = aFunction;
			return true;
		}

		/**
		 * @brief Unregister a function from the specified registrar.
		 * @param aRegistrar A registrar to disconnect the function from.
		 */
		void Disconnect(void* aRegistrar)
		{
			if (myCallbacks.contains(aRegistrar))
				myCallbacks.at(aRegistrar) = nullptr;
		}

	private:
		std::map<void*, std::function<void()>> myCallbacks;
	};
}