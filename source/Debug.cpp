#include "../include/rose-common/Debug.hpp"

#include "../include/rose-common/StringUtilities.hpp"

#include <cstdio>
#include <sstream>
#include <thread>

#if defined(_WIN32)
#include <Windows.h>
#endif

namespace RoseCommon
{
	namespace Debug_cpp
	{
		void FormatLogMessage(const char* aMessage, const va_list& someArguments, std::stringstream& aStream)
		{
			va_list argumentsCopy;
			va_copy(argumentsCopy, someArguments);
			const std::size_t stringLength = vsnprintf(nullptr, 0, aMessage, argumentsCopy);

			std::unique_ptr<char> formattedBuffer(new char[stringLength + 1]);
			vsnprintf(formattedBuffer.get(), stringLength + 1, aMessage, someArguments);
			aStream << formattedBuffer;
		}

		void FormatLogMessage(const wchar_t* aMessage, const va_list& someArguments, std::wstringstream& aStream)
		{
			va_list argumentsCopy;
			va_copy(argumentsCopy, someArguments);
			const std::size_t stringLength = vswprintf(nullptr, 0, aMessage, argumentsCopy);

			std::unique_ptr<wchar_t> formattedBuffer(new wchar_t[stringLength + 1]);
			vswprintf(formattedBuffer.get(), stringLength + 1, aMessage, someArguments);
			aStream << formattedBuffer;
		}
	}

	void Debug::Assert(bool aCondition, const char* anErrorMessage, ...)
	{
		if (ourDebugImplementation && !aCondition)
		{
			std::stringstream ss;
			ss << "Assertion failed:\n\n";

			va_list args;
			va_start(args, anErrorMessage);
			Debug_cpp::FormatLogMessage(anErrorMessage, args, ss);
			va_end(args);

			ourDebugImplementation->Log(Impl::LogType::Fatal, ss.str());
			ourDebugImplementation->TriggerCrash(ss.str());
		}
	}

	void Debug::Assert(bool aCondition, const wchar_t* anErrorMessage, ...)
	{
		if (ourDebugImplementation && !aCondition)
		{
			std::wstringstream ss;
			ss << "Assertion failed:\n\n";

			va_list args;
			va_start(args, anErrorMessage);
			Debug_cpp::FormatLogMessage(anErrorMessage, args, ss);
			va_end(args);

			ourDebugImplementation->Log(Impl::LogType::Fatal, ss.str());
			ourDebugImplementation->TriggerCrash(ss.str());
		}
	}

	void Debug::Log(const char* aMessage, ...)
	{
		if (ourDebugImplementation)
		{
			std::stringstream ss;
			va_list args;
			va_start(args, aMessage);
			Debug_cpp::FormatLogMessage(aMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Information, ss.str());
		}
	}

	void Debug::Log(const wchar_t* aMessage, ...)
	{
		if (ourDebugImplementation)
		{
			std::wstringstream ss;
			va_list args;
			va_start(args, aMessage);
			Debug_cpp::FormatLogMessage(aMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Information, ss.str());
		}
	}

	void Debug::LogWarning(const char* aMessage, ...)
	{
		if (ourDebugImplementation)
		{
			std::stringstream ss;
			va_list args;
			va_start(args, aMessage);
			Debug_cpp::FormatLogMessage(aMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Warning, ss.str());
		}
	}

	void Debug::LogWarning(const wchar_t* aMessage, ...)
	{
		if (ourDebugImplementation)
		{
			std::wstringstream ss;
			va_list args;
			va_start(args, aMessage);
			Debug_cpp::FormatLogMessage(aMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Warning, ss.str());
		}
	}

	void Debug::LogError(const char* aMessage, ...)
	{
		if (ourDebugImplementation)
		{
			std::stringstream ss;
			va_list args;
			va_start(args, aMessage);
			Debug_cpp::FormatLogMessage(aMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Error, ss.str());
		}
	}

	void Debug::LogError(const wchar_t* aMessage, ...)
	{
		if (ourDebugImplementation)
		{
			std::wstringstream ss;
			va_list args;
			va_start(args, aMessage);
			Debug_cpp::FormatLogMessage(aMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Error, ss.str());
		}
	}

	void Debug::LogFatal(const char* aMessage, ...)
	{
		if (ourDebugImplementation)
		{
			va_list args;
			std::stringstream ss;
			va_start(args, aMessage);
			Debug_cpp::FormatLogMessage(aMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Fatal, ss.str());
			ourDebugImplementation->TriggerCrash(ss.str());
		}
	}

	void Debug::LogFatal(const wchar_t* aMessage, ...)
	{
		if (ourDebugImplementation)
		{
			va_list args;
			std::wstringstream ss;
			va_start(args, aMessage);
			Debug_cpp::FormatLogMessage(aMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Fatal, ss.str());
			ourDebugImplementation->TriggerCrash(ss.str());
		}
	}

	void Debug::SetThreadName(const char* aThreadName)
	{
		if (ourDebugImplementation)
			ourDebugImplementation->SetThreadName(aThreadName);
	}

	void Debug::SetThreadName(std::thread& aThread, const char* aThreadName)
	{
		if (ourDebugImplementation)
			ourDebugImplementation->SetThreadName(aThread, aThreadName);
	}

	bool Debug::Verify(bool aCondition, const char* anErrorMessage, ...)
	{
		if (ourDebugImplementation && !aCondition)
		{
			std::stringstream ss;
			va_list args;
			va_start(args, anErrorMessage);
			Debug_cpp::FormatLogMessage(anErrorMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Error, ss.str());
		}

		return aCondition;
	}

	bool Debug::Verify(bool aCondition, const wchar_t* anErrorMessage, ...)
	{
		if (ourDebugImplementation && !aCondition)
		{
			std::wstringstream ss;
			va_list args;
			va_start(args, anErrorMessage);
			Debug_cpp::FormatLogMessage(anErrorMessage, args, ss);
			va_end(args);
			ourDebugImplementation->Log(Impl::LogType::Error, ss.str());
		}

		return aCondition;
	}

#if defined(_WIN32)
	class DebugWin32Impl final : public Debug::Impl
	{
	public:
		void Log(LogType aType, const std::string& aMessage)
		{
			std::stringstream ss;
			Output(aType, ss);
			ss << aMessage;
			Print(ss.str());
		}

		void Log(LogType aType, const std::wstring& aMessage)
		{
			std::wstringstream ss;
			Output(aType, ss);
			ss << aMessage;
			Print(ss.str());
		}

		void SetThreadName(const std::string& aThreadName)
		{
#if defined(_WIN32)
			SetThreadName(GetCurrentThreadId(), aThreadName.c_str());
#elif defined(_LINUX)
			prctl(PR_SET_NAME, aThreadName, 0, 0, 0);
#endif
		}

		void SetThreadName(std::thread& aThread, const std::string& aThreadName)
		{
#if defined(_WIN32)
			DWORD threadId = ::GetThreadId(static_cast<HANDLE>(aThread.native_handle()));
			SetThreadName(threadId, aThreadName.c_str());
#elif defined(_LINUX)
			auto handle = aThread->native_handle();
			pthread_setname_np(handle, aThreadName);
#endif
		}

		void TriggerCrash(const std::string& aMessage)
		{
			std::stringstream ss;
			ss << "Fatal error!\n\n";
			ss << aMessage;

			if (IsDebuggerPresent() != FALSE)
			{
				ss << "\n\nPress OK to break.";

				MessageBoxA(NULL, ss.str().c_str(),
					"Program crash",
					MB_OK | MB_ICONERROR | MB_APPLMODAL);
				__debugbreak();
			}
			else
			{
				ss << "\n\nDo you wish to quit the program?";

				if (MessageBoxA(NULL, ss.str().c_str(),
					"Program crash",
					MB_YESNO | MB_ICONERROR | MB_APPLMODAL) == IDYES)
				{
					ExitProcess(1);
				}
			}
		}

		void TriggerCrash(const std::wstring& aMessage)
		{
			std::wstringstream ss;
			ss << L"Fatal error!\n\n";
			ss << aMessage;

			if (IsDebuggerPresent() != FALSE)
			{
				ss << L"\n\nPress OK to break.";

				MessageBoxW(NULL, ss.str().c_str(),
					L"Program crash",
					MB_OK | MB_ICONERROR | MB_APPLMODAL);
				__debugbreak();
			}
			else
			{
				ss << L"\n\nDo you wish to quit the program?";

				if (MessageBoxW(NULL, ss.str().c_str(),
					L"Program crash",
					MB_YESNO | MB_ICONERROR | MB_APPLMODAL) == IDYES)
				{
					ExitProcess(1);
				}
			}
		}

	private:
		void Output(LogType aLogType, std::stringstream& aStream)
		{
			switch (aLogType)
			{
			case LogType::Information:
				aStream << "[ Information ] ";
				break;
			case LogType::Warning:
				aStream << "[   Warning   ] ";
				break;
			case LogType::Error:
				aStream << "[    Error    ] ";
				break;
			case LogType::Fatal:
				aStream << "[    Fatal    ] ";
				break;
			}
		}

		void Output(LogType aLogType, std::wstringstream& aStream)
		{
			switch (aLogType)
			{
			case LogType::Information:
				aStream << L"[ Information ] ";
				break;
			case LogType::Warning:
				aStream << L"[   Warning   ] ";
				break;
			case LogType::Error:
				aStream << L"[    Error    ] ";
				break;
			case LogType::Fatal:
				aStream << L"[    Fatal    ] ";
				break;
			}
		}

		void Print(std::string aMessage)
		{
			if (aMessage.empty())
				return;

			RoseCommon::StringUtilities::Replace<char>(aMessage, "\n", "\n                ");
			aMessage.append("\n");

			printf(aMessage.c_str());
#ifdef _MSC_BUILD
			OutputDebugStringA(aMessage.c_str());
#endif
		}

		void Print(std::wstring aMessage)
		{
			if (aMessage.empty())
				return;

			RoseCommon::StringUtilities::Replace<wchar_t>(aMessage, L"\n", L"\n                ");
			aMessage.append(L"\n");

			wprintf(aMessage.c_str());
#ifdef _MSC_BUILD
			OutputDebugStringW(aMessage.c_str());
#endif
		}

	private:
#pragma pack(push,8)
		struct THREADNAME_INFO
		{
			DWORD dwType; // Must be 0x1000.
			LPCSTR szName; // Pointer to name (in user addr space).
			DWORD dwThreadID; // Thread ID (-1=caller thread).
			DWORD dwFlags; // Reserved for future use, must be zero.
		};
#pragma pack(pop)

		void SetThreadName(DWORD dwThreadID, const char* aThreadName)
		{
			THREADNAME_INFO info;
			info.dwType = 0x1000;
			info.szName = aThreadName;
			info.dwThreadID = dwThreadID;
			info.dwFlags = 0;

			__try
			{
				constexpr DWORD MS_VC_EXCEPTION = 0x406D1388;
				RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
			}
		}
	};

	DebugWin32Impl win32Impl;
	Debug::Impl* Debug::ourDebugImplementation(&win32Impl);
#else
	Debug::Impl* Debug::ourDebugImplementation(nullptr);
#endif
}