// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include <gtest/gtest.h>

#define EDO_DEBUG_IMPLEMENTATION 1
#include <edo_debug.hpp>

int main(int argc, char** argv)
{
	edo::Debug::InitDefaultLogger();
	edo::Debug::logger->EnableLevel(edo::LogLevel::Verbose);

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
