# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# ===== Target =====

file(GLOB_RECURSE EDO_UT_EVENT_SOURCES "*.cpp")

add_executable(Edo_UT_Event "../main.cpp" ${EDO_UT_EVENT_SOURCES})

target_link_libraries(Edo_UT_Event
	PRIVATE EdoBase GTest::gtest_main
)

gtest_discover_tests(Edo_UT_Event)
