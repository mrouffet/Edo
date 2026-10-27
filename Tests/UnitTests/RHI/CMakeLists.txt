# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

file(GLOB_RECURSE EDO_UT_RHI_SOURCES "*.cpp")


# ===== Target DX12 =====
if(WIN32)

	add_executable(Edo_UT_RHI_DX12 "../main.cpp" ${EDO_UT_RHI_SOURCES})

	target_compile_definitions(Edo_UT_RHI_DX12 PRIVATE EDO_UT_RHI_DX12=1)

	target_link_libraries(Edo_UT_RHI_DX12
		PRIVATE EdoBase GTest::gtest_main
		PUBLIC d3d12.lib dxgi.lib dxguid.lib dxcompiler.lib
	)

	EDO_LinkTestWindowAPI(Edo_UT_RHI_DX12)
	EDO_CopyDXCRuntimeBinaries(Edo_UT_RHI_DX12)
	EDO_CopyTestsResources(Edo_UT_RHI_DX12)

	gtest_discover_tests(Edo_UT_RHI_DX12)

endif()


# ===== Target VK =====
if(UNIX OR WIN32)

	find_package(Vulkan)

	if(${Vulkan_FOUND})

		add_executable(Edo_UT_RHI_VK "../main.cpp" ${EDO_UT_RHI_SOURCES})

		target_compile_definitions(Edo_UT_RHI_VK PRIVATE EDO_UT_RHI_VK=1)

		target_link_libraries(Edo_UT_RHI_VK
			PRIVATE EdoBase GTest::gtest_main
			PUBLIC Vulkan::Vulkan
		)

		EDO_LinkTestWindowAPI(Edo_UT_RHI_VK)
		EDO_CopyTestsResources(Edo_UT_RHI_VK)

		gtest_discover_tests(Edo_UT_RHI_VK)

	else()

		message(AUTHOR_WARNING "Vulkan package not found on expected target. Vulkan SDK installation required.")

	endif()

endif()


# ===== Target GL =====
if(false)

	add_executable(Edo_UT_RHI_GL "../main.cpp" ${EDO_UT_RHI_SOURCES})

	target_compile_definitions(Edo_UT_RHI_GL PRIVATE EDO_UT_RHI_GL=1)

	target_link_libraries(Edo_UT_RHI_GL
		PRIVATE EdoBase GTest::gtest_main
	)

	EDO_LinkTestWindowAPI(Edo_UT_RHI_GL)
	EDO_CopyTestsResources(Edo_UT_RHI_GL)

	gtest_discover_tests(Edo_UT_RHI_GL)

endif()


# ===== Target CPU =====
if(false)

	add_executable(Edo_UT_RHI_CPU "../main.cpp" ${EDO_UT_RHI_SOURCES})

	target_compile_definitions(Edo_UT_RHI_CPU PRIVATE EDO_UT_RHI_CPU=1)

	target_link_libraries(Edo_UT_RHI_CPU
		PRIVATE EdoBase GTest::gtest_main
	)

	EDO_LinkTestWindowAPI(Edo_UT_RHI_CPU)
	EDO_CopyTestsResources(Edo_UT_RHI_CPU)

	gtest_discover_tests(Edo_UT_RHI_CPU)

endif()
