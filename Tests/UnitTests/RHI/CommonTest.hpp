// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_RHI_COMMON_TEST_GUARD
#define EDO_RHI_COMMON_TEST_GUARD

#include <gtest/gtest.h>

#include <edo_debug.hpp>
#include <edo_maths.hpp>
using namespace edo;

/**
* Select Graphics API based on CMake Target
*/
#if EDO_UT_RHI_DX12
	#define EDO_RHI_DX12 1
#endif
#if EDO_UT_RHI_VK
	#define EDO_RHI_VK 1
#endif
#if EDO_UT_RHI_GL
	#define EDO_RHI_GL 1
#endif
#if EDO_UT_RHI_CPU
	#define EDO_RHI_CPU 1
#endif


/**
* Force define Window API to be used.
* Required API added to CMake project build tree
* CMake option can be also used instead
*/
//#define EDO_RHI_SDL3 0
//#define EDO_RHI_GLFW 0
//#define EDO_RHI_SFML 0

#include <edo_rhi.hpp>


/**
* Select the one test only to be compiled and run for easier development.
*/
#ifndef EDO_RHI_UT_SELECT_TEST
	#define EDO_RHI_UT_SELECT_TEST -1
#endif

#endif // EDO_RHI_COMMON_TEST_GUARD
