// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include <gtest/gtest.h>

#include <edo_debug.hpp>

namespace EDO::UT::Assert
{
	bool SuccessFunction() { return true; }
	bool FailureFunction() { return false; }

	TEST(AssertTests, Success)
	{
		EXPECT_NO_THROW(EDO_ASSERT(SuccessFunction(), Edo.UT.Assert));
		EXPECT_NO_THROW(EDO_ASSERT(SuccessFunction(), Edo.UT.Assert, ("Details about Function %1", "SuccessFunction")));

		const char* ptr = "Hello, world!";
		EXPECT_NO_THROW(EDO_ASSERT(ptr, Edo.UT.Assert));
		EXPECT_THROW(EDO_ASSERT(!ptr, Edo.UT.Assert), edo::Log);

		edo::Debug::logger->EnableLevel(edo::LogLevel::AssertSuccess);

		EXPECT_NO_THROW(EDO_ASSERT(SuccessFunction(), Edo.UT.Assert, ("Details about Function %1", "SuccessFunction")));

		edo::Debug::logger->DisableLevel(edo::LogLevel::AssertSuccess);
	}

	TEST(AssertTests, Failure)
	{
		EXPECT_THROW(EDO_ASSERT(FailureFunction(), Edo.UT.Assert), edo::Log);
		EXPECT_THROW(EDO_ASSERT(FailureFunction(), Edo.UT.Assert, ("Details about Function %1", "FailureFunction")), edo::Log);

		const char* ptr = nullptr;
		EXPECT_THROW(EDO_ASSERT(ptr, Edo.UT.Assert), edo::Log);
		EXPECT_NO_THROW(EDO_ASSERT(!ptr, Edo.UT.Assert));
	}
}
