// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include <gtest/gtest.h>

#include <edo_debug.hpp>

void LogCallback(edo::Log _log)
{
	// Filter: discard Info level.
	if (_log.level == edo::LogLevel::Info)
		return;

	std::wcout << edo::ToWString(_log) << std::endl;
}

namespace MyNamespace
{
	class MyClass
	{
	public:
		int i = 0;
	};
}

namespace edo
{
	template <>
	std::string ToString(const MyNamespace::MyClass& _m)
	{
		return "MyNamespace::MyClass: " + std::to_string(_m.i);
	}
}

namespace edo::UT::Logger
{
	TEST(LoggerTests, Various)
	{
		int i = 8614;

		MyNamespace::MyClass m1;
		m1.i = 72;

		EDO_LOG("efsegseg");
		EDO_LOG(i, Error);
		EDO_LOG(m1, Info);
		EDO_LOG("efsegseg", Error, PP.SuperChan);
		EDO_LOG("efsegseg", Error, PP.SuperChan, L"super dets");
		EDO_LOG(L"AAAAAAAAAA", Normal, Edo.TestChan, L"");
		EDO_LOG(("%1 Hello %1 %2", 8, m1), Normal, Edo.TestChan, L"");

		edo::Debug::logger->DisableChannel(L"Edo.SuperDisabledChan");

		EDO_LOG("Discarded message", Info, Edo.SuperDisabledChan);

		int i3 = 3;
		EDO_ERROR(i3 < 1, NewChan, ("Some Details! %1 is > %2", i3, 1))
		EDO_WARN(i3 < 1, NewChan, ("Some Details! %1 is > %2", i3, 1))

//{ Test LogLevel Flags

		EDO_LOG("This log level is enabled in console!", Warning, Edo.TestChan);

		edo::Debug::logger->Flush();

		edo::Debug::logger->DisableLevel(edo::LogLevel::Warning);

		EDO_LOG("This log level is NOT enabled in console!", Warning, Edo.TestChan);

		edo::Debug::logger->Flush();

		edo::Debug::logger->EnableLevel(edo::LogLevel::Warning);

		EDO_LOG("This log level is enabled AGAIN in console!", Warning, Edo.TestChan);

//}

		EDO_LOG("Verbose test ignored!", Verbose);

		edo::Debug::logger->EnableLevel(edo::LogLevel::Verbose);

		EDO_LOG("Verbose test passed!", Verbose);
	}
}
