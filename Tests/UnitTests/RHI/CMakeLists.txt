# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

file(GLOB_RECURSE EDO_RHI_UT_SOURCES "*.cpp")


# ===== Target DX12 =====
if(WIN32)

	add_executable(Edo_RHI_DX12_UT "../main.cpp" ${EDO_RHI_UT_SOURCES})

	target_compile_definitions(Edo_RHI_DX12_UT PRIVATE EDO_UT_RHI_DX12=1)

	target_link_libraries(Edo_RHI_DX12_UT PRIVATE Edo GTest::gtest_main)

	target_link_libraries(Edo_RHI_DX12_UT PUBLIC d3d12.lib dxgi.lib dxguid.lib)

	gtest_discover_tests(Edo_RHI_DX12_UT)

endif()


# ===== Target VK =====
if(UNIX OR WIN32)

	add_executable(Edo_RHI_VK_UT "../main.cpp" ${EDO_RHI_UT_SOURCES})

	target_compile_definitions(Edo_RHI_VK_UT PRIVATE EDO_UT_RHI_VK=1)

	target_link_libraries(Edo_RHI_VK_UT PRIVATE Edo GTest::gtest_main)

	find_package(Vulkan)
	target_link_libraries(Edo_RHI_VK_UT PUBLIC Vulkan::Vulkan)

	gtest_discover_tests(Edo_RHI_VK_UT)

endif()
