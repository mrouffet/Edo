# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

cmake_minimum_required(VERSION 3.24)

# Edo's CMake tools.
add_subdirectory(CMake)



# Project

project(Edo)


# ===== Output Directory =====
set(EDO_BIN_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/Build/bin/${CMAKE_CXX_COMPILER_ID}_$<CONFIG>")

# Log directory at configuration-time
message("[${CMAKE_PROJECT_NAME}]: Output directory: ${EDO_BIN_OUTPUT_DIR}")

# Set output directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${EDO_BIN_OUTPUT_DIR}/libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${EDO_BIN_OUTPUT_DIR}/libs")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EDO_BIN_OUTPUT_DIR}")

# Organize targets (and nesting targets) in IDE.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)



# ===== Target Edo =====
file(GLOB_RECURSE EDO_SOURCES_CPP "Source/*.cpp")
file(GLOB_RECURSE EDO_SOURCES_HLSL "Source/*.hlsl")

add_library(Edo STATIC ${EDO_SOURCES_CPP})

# Standard
target_compile_features(Edo PUBLIC c_std_11 cxx_std_20)

# Include Dirs
target_include_directories(Edo PUBLIC Include Include/SingleHeaders)

# Libs
#target_link_libraries(Edo PUBLIC )

# Compile options
if(MSVC)
	target_compile_options(Edo PUBLIC /W4 /WX)

	### Advanced MSVC preprocessor required for edo_debug.hpp
	### https://docs.microsoft.com/en-us/cpp/preprocessor/preprocessor-experimental-overview
	target_compile_options(Edo PUBLIC /Zc:preprocessor)
else()
	target_compile_options(Edo PUBLIC -Wall Wextra -Werror)
endif()



# ===== CMake Modules =====
include(FetchContent)



# ===== Entrypoints =====
add_subdirectory(ThirdParty)

if(SA_EDO_BUILD_TESTS_OPT)

	# Enable testing for this directory and below.
	enable_testing()

	add_subdirectory(Tests)
endif()
