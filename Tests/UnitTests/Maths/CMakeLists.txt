# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# ===== Target =====

file(GLOB_RECURSE EDO_MATHS_UT_SOURCES "*.cpp")

add_executable(Edo_MathsUT "../main.cpp" ${EDO_MATHS_UT_SOURCES})

target_link_libraries(Edo_MathsUT PRIVATE Edo GTest::gtest_main)

gtest_discover_tests(Edo_MathsUT)
