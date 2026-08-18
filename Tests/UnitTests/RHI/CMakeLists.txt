# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# ===== Target =====

file(GLOB_RECURSE EDO_RHI_UT_SOURCES "*.cpp")

add_executable(Edo_RHIUT "../main.cpp" ${EDO_RHI_UT_SOURCES})

target_link_libraries(Edo_RHIUT PRIVATE Edo GTest::gtest_main)

target_link_libraries(Edo_RHIUT PUBLIC d3d12.lib dxgi.lib dxguid.lib)

find_package(Vulkan)
target_link_libraries(Edo_RHIUT PUBLIC Vulkan::Vulkan)


gtest_discover_tests(Edo_RHIUT)
