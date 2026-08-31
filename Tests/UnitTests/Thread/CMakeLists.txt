# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# ===== Target =====

file(GLOB_RECURSE EDO_UT_THREAD_SOURCES "*.cpp")

add_executable(Edo_UT_Thread "../main.cpp" ${EDO_UT_THREAD_SOURCES})

target_link_libraries(Edo_UT_Thread
	PRIVATE EdoBase GTest::gtest_main
)

gtest_discover_tests(Edo_UT_Thread)
