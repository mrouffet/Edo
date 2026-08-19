# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# ===== Target =====

file(GLOB_RECURSE EDO_DEBUG_UT_SOURCES "*.cpp")

add_executable(Edo_DebugUT "../main.cpp" ${EDO_DEBUG_UT_SOURCES})

target_link_libraries(Edo_DebugUT PRIVATE Edo GTest::gtest_main)

gtest_discover_tests(Edo_DebugUT)
