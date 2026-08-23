# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# ===== Target =====

file(GLOB_RECURSE EDO_UT_MATHS_SOURCES "*.cpp")

add_executable(Edo_UT_Maths "../main.cpp" ${EDO_UT_MATHS_SOURCES})

target_link_libraries(Edo_UT_Maths
	PRIVATE EdoBase GTest::gtest_main
)

gtest_discover_tests(Edo_UT_Maths)
