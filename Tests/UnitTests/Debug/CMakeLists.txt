# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# ===== Target =====

file(GLOB_RECURSE EDO_UT_DEBUG_SOURCES "*.cpp")

add_executable(Edo_UT_Debug "../main.cpp" ${EDO_UT_DEBUG_SOURCES})

target_link_libraries(Edo_UT_Debug
	PRIVATE EdoBase GTest::gtest_main
)

gtest_discover_tests(Edo_UT_Debug)
