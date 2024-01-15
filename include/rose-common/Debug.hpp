#pragma once

#include <assert.h>
#include <string>

#undef assert
#define assert(x) System::Debug::Assert(!!(x), #x);

namespace std { class thread; }

namespace RoseCommon
{
	class Debug
	{
	public:
		class Impl;

		static Impl* ourDebugImplementation;

	public:
		// Assert that a condition is true, otherwise logging a fatal message.
		static void Assert(bool aCondition, const char* anErrorMessage, ...);
		static void Assert(bool aCondition, const wchar_t* anErrorMessage, ...);

		// Log a message for debugging information only.
		static void Log(const char* aMessage, ...);
		static void Log(const wchar_t* aMessage, ...);

		// Log a warning message to indicate a potential problem.
		static void LogWarning(const char* aMessage, ...);
		static void LogWarning(const wchar_t* aMessage, ...);

		// Log an error message to indicate an issue that needs to be fixed.
		static void LogError(const char* aMessage, ...);
		static void LogError(const wchar_t* aMessage, ...);

		// Log a fatal error message which usually terminates the application with a callstack.
		static void LogFatal(const char* aMessage, ...);
		static void LogFatal(const wchar_t* aMessage, ...);

		/// <summary>
		/// Tries to set the current thread's name to the specified value.
		/// If not implemented on the target system, will simply not do anything.
		/// </summary>
		/// <param name="aThreadName">The thread name to be used.</param>
		static void SetThreadName(const char* aThreadName);

		/// <summary>
		/// Tries to set the thread name to the specified value.
		/// If not implemented on the target system, will simply not do anything.
		/// </summary>
		/// <param name="aThread">The thread to be changed.</param>
		/// <param name="aThreadName">The thread name to be used.</param>
		static void SetThreadName(std::thread& aThread, const char* aThreadName);

		// Verify a condition to be true, otherwise logging it as an error.
		static bool Verify(bool aCondition, const char* anErrorMessage, ...);
		static bool Verify(bool aCondition, const wchar_t* anErrorMessage, ...);
	};

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
