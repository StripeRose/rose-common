#pragma once

#include "RoseCommon_Namespace.hpp"

#include <functional>
#include <map>

namespace ROSECOMMON_NAMESPACE
{
	struct EventCallbackID
	{
	private:
		template <typename ... T>
		friend class EventSlot;

		EventCallbackID(const void* aSlot, int aCallbackId)
			: myEventSlot(aSlot), myCallbackId(aCallbackId)
		{ }

		const void* myEventSlot;
		int myCallbackId;
	};

	/**
	 * @brief An interface for defining events which other objects can listen for the invokation of.
	 * @tparam ...CallbackArguments A list of argument types the event must use.
	 */
	template <typename ... CallbackArguments>
	class EventSlot
	{
	public:
		EventSlot() = default;
		~EventSlot() = default;

		// Shouldn't copy callbacks.
		EventSlot(const EventSlot&) = delete;
		EventSlot& operator=(const EventSlot&) = delete;

		// Can't move callbacks and maintain callback IDs.
		EventSlot(EventSlot&&) = delete;
		EventSlot& operator=(EventSlot&&) = delete;

		/**
		 * @brief Invoke all currently connected functions.
		 * @param ...someArguments A list of arguments to call the connected functions with.
		 */
		void Invoke(CallbackArguments... someArguments) const
		{
			for (auto it : myCallbacks)
			{
				if (it.second)
					it.second(someArguments...);
			}
		}

		/**
		 * @brief Register new function to be called when the EventSlot is invoked.
		 * @param aFunction A function to connect.
		 * @return A callback id to use when unregistering.
		 */
		EventCallbackID Connect(std::function<void(CallbackArguments...)> aFunction)
		{
			myCallbacks.emplace(myRollingId, aFunction);
			return EventCallbackID{ this, myRollingId++ };
		}

		/**
		 * @brief Register new function to be called when the EventSlot is invoked.
		 * @param aRegistrar A pointer to attribute the connection to.
		 * @param aFunction A function to connect.
		 * @return A callback id to use when unregistering.
		 */
		EventCallbackID Connect(const void* aRegistrar, std::function<void(CallbackArguments...)> aFunction)
		{
			myCallbacks.emplace(myRollingId, aFunction);
			myRegistrarCallbacks[aRegistrar].push_back(myRollingId);
			return EventCallbackID{ this, myRollingId++ };
		}

		/**
		 * @brief Unregister a specific callback.
		 * @param aCallbackId A callback id given when registering.
		 */
		void Disconnect(const EventCallbackID& aCallbackId)
		{
			if (aCallbackId.myEventSlot == this)
				myCallbacks.erase(aCallbackId.myCallbackId);
		}

		/**
		 * @brief Unregister all functions from a specified registrar.
		 * @param aRegistrar A registrar whose functions should be disconnected.
		 */
		void Disconnect(const void* aRegistrar)
		{
			if (!myRegistrarCallbacks.contains(aRegistrar))
				return;

			const std::vector<int>& callbacks = myRegistrarCallbacks[aRegistrar];
			for (int id : callbacks)
				myCallbacks.erase(id);

			myRegistrarCallbacks.erase(aRegistrar);
		}

		void operator()(CallbackArguments... someArguments) const
		{
			Invoke(someArguments...);
		}

	private:
		int myRollingId = 0;
		std::map<int, std::function<void(CallbackArguments...)>> myCallbacks;
		std::map<const void*, std::vector<int>> myRegistrarCallbacks;
	};

	/**
	 * @brief An interface for defining events which other objects can listen for the invokation of.
	 */
	template <>
	class EventSlot<void>
	{
	public:
		EventSlot() = default;
		~EventSlot() = default;

		// Shouldn't copy callbacks.
		EventSlot(const EventSlot&) = delete;
		EventSlot& operator=(const EventSlot&) = delete;

		// Can't move callbacks and maintain callback IDs.
		EventSlot(EventSlot&&) = delete;
		EventSlot& operator=(EventSlot&&) = delete;

		/**
		 * @brief Invoke all currently connected functions.
		 */
		void Invoke() const
		{
			for (auto it : myCallbacks)
			{
				if (it.second)
					it.second();
			}
		}

		/**
		 * @brief Register new function to be called when the EventSlot is invoked.
		 * @param aFunction A function to connect.
		 * @return A callback id to use when unregistering.
		 */
		EventCallbackID Connect(std::function<void()> aFunction)
		{
			myCallbacks.emplace(myRollingId, aFunction);
			return EventCallbackID{ this, myRollingId++ };
		}

		/**
		 * @brief Register new function to be called when the EventSlot is invoked.
		 * @param aRegistrar A pointer to attribute the connection to.
		 * @param aFunction A function to connect.
		 * @return A callback id to use when unregistering.
		 */
		EventCallbackID Connect(const void* aRegistrar, std::function<void()> aFunction)
		{
			myCallbacks.emplace(myRollingId, aFunction);
			myRegistrarCallbacks[aRegistrar].push_back(myRollingId);
			return EventCallbackID{ this, myRollingId++ };
		}

		/**
		 * @brief Unregister a specific callback.
		 * @param aCallbackId A callback id given when registering.
		 */
		void Disconnect(const EventCallbackID& aCallbackId)
		{
			if (aCallbackId.myEventSlot == this)
				myCallbacks.erase(aCallbackId.myCallbackId);
		}

		/**
		 * @brief Unregister all functions from a specified registrar.
		 * @param aRegistrar A registrar whose functions should be disconnected.
		 */
		void Disconnect(const void* aRegistrar)
		{
			if (!myRegistrarCallbacks.contains(aRegistrar))
				return;

			const std::vector<int>& callbacks = myRegistrarCallbacks[aRegistrar];
			for (int id : callbacks)
				myCallbacks.erase(id);

			myRegistrarCallbacks.erase(aRegistrar);
		}

		void operator()() const
		{
			Invoke();
		}

	private:
		int myRollingId = 0;
		std::map<int, std::function<void()>> myCallbacks;
		std::map<const void*, std::vector<int>> myRegistrarCallbacks;
	};
}