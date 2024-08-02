#pragma once

#include <assert.h>
#include <string>

#undef assert
#define assert(x) System::Debug::Assert(!!(x), #x);

namespace std { class thread; }

namespace RoseCommon
{
	/**
	 * @brief Provides an interface to debug logging.
	 */
	class Debug
	{
	public:
		class Impl;

		static Impl* ourDebugImplementation;

	public:
		/**
		 * @brief Assert that a condition is true, otherwise logging a fatal message.
		 * @param aCondition A condition to assert being true.
		 * @param anErrorMessage A message to log if the assert fails.
		 */
		static void Assert(bool aCondition, const char* anErrorMessage, ...);
		static void Assert(bool aCondition, const wchar_t* anErrorMessage, ...);

		/**
		 * @brief Log a message for debugging information only.
		 * @param aMessage A message to log.
		 */
		static void Log(const char* aMessage, ...);
		static void Log(const wchar_t* aMessage, ...);

		/**
		 * @brief Log a warning message to indicate a potential problem or mistake.
		 * @param aMessage A message to log.
		 */
		static void LogWarning(const char* aMessage, ...);
		static void LogWarning(const wchar_t* aMessage, ...);

		/**
		 * @brief Log an error message to indicate an issue that needs to be fixed.
		 * @param aMessage A message to log.
		 */
		static void LogError(const char* aMessage, ...);
		static void LogError(const wchar_t* aMessage, ...);

		/**
		 * @brief Log a fatal error message which usually terminates the application with a callstack.
		 * @param aMessage A message to log.
		 */
		static void LogFatal(const char* aMessage, ...);
		static void LogFatal(const wchar_t* aMessage, ...);
		
		/**
		 * @brief Attempt to set the current thread's name to the specified value.
		 *        If not implemented on the target system, will simply not do anything.
		 * @param aThreadName A new name for the thread.
		 */
		static void SetThreadName(const char* aThreadName);

		/**
		 * @brief Attempt to set the current thread's name to the specified value.
		 *        If not implemented on the target system, will simply not do anything.
		 * @param aThread A thread to rename.
		 * @param aThreadName A new name for the thread.
		 */
		static void SetThreadName(std::thread& aThread, const char* aThreadName);

		/**
		 * @brief Verify a condition to be true, otherwise logging it as an error.
		 * @param aCondition A condition to verify as true.
		 * @param anErrorMessage An error-message to log if the condition was false.
		 * @return The condition, to allow the function to be part of an if-statement.
		 */
		static bool Verify(bool aCondition, const char* anErrorMessage, ...);
		static bool Verify(bool aCondition, const wchar_t* anErrorMessage, ...);
	};

	/**
	 * @brief Details the interface for debug logger implementations.
	 */
	class Debug::Impl
	{
	public:
		enum class LogType { Information, Warning, Error, Fatal };

		virtual void Log(LogType aType, const std::string& aMessage) = 0;
		virtual void Log(LogType aType, const std::wstring& aMessage) = 0;

		virtual void SetThreadName(const std::string& aThreadName) = 0;
		virtual void SetThreadName(std::thread& aThread, const std::string& aThreadName) = 0;

		virtual void TriggerCrash(const std::string& aMessage) = 0;
		virtual void TriggerCrash(const std::wstring& aMessage) = 0;
	};
}
