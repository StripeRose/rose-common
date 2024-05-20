#pragma once

#include <functional>
#include <map>

namespace RoseCommon
{
	template <typename ... CallbackArguments>
	class EventSlot
	{
	public:
		void Invoke(CallbackArguments... someArguments) const
		{
			for (const auto& callback : myCallbacks)
			{
				if (callback.second)
					callback.second(someArguments...);
			}
		}

		bool Connect(void* aRegistrar, std::function<void(CallbackArguments...)> aFunction)
		{
			if (myCallbacks.contains(aRegistrar))
				return false;

			myCallbacks[aRegistrar] = aFunction;
			return true;
		}

		void Disconnect(void* aRegistrar)
		{
			if (myCallbacks.contains(aRegistrar))
				myCallbacks.at(aRegistrar) = nullptr;
		}

	private:
		std::map<void*, std::function<void(CallbackArguments...)>> myCallbacks;
	};

	template <>
	class EventSlot<>
	{
	public:
		void Invoke() const
		{
			for (const auto& callback : myCallbacks)
			{
				if (callback.second)
					callback.second();
			}
		}

		bool Connect(void* aRegistrar, std::function<void()> aFunction)
		{
			if (myCallbacks.contains(aRegistrar))
				return false;

			myCallbacks[aRegistrar] = aFunction;
			return true;
		}

		void Disconnect(void* aRegistrar)
		{
			if (myCallbacks.contains(aRegistrar))
				myCallbacks.at(aRegistrar) = nullptr;
		}

	private:
		std::map<void*, std::function<void()>> myCallbacks;
	};
}