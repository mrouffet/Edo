# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.



# Project

project(Edo_UnitTests)


# ===== GoogleTest Module =====
if(NOT TARGET googletest) # Check CMAKE target already present
	if(EXISTS "${CMAKE_SOURCE_DIR}/ThirdParty/googletest/CMakeLists.txt")

		# Content already cloned
		message("Including Google Test...")

		add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/googletest ${CMAKE_BINARY_DIR}/ThirdParty/googletest)

	else()

		# Fetch
		message("Fetching Google Test...")

		FetchContent_Declare(
			googletest
			GIT_REPOSITORY	https://github.com/google/googletest
			GIT_TAG			v1.18.0
			SOURCE_DIR		../../ThirdParty/googletest
		)
	
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
		FetchContent_MakeAvailable(googletest)

	endif()
endif()

include(GoogleTest)



# ===== Entrypoints =====
add_subdirectory(Debug)
add_subdirectory(Maths)
add_subdirectory(Event)
