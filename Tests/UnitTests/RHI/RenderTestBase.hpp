// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_RHI_RENDER_TEST_BASE_GUARD
#define EDO_RHI_RENDER_TEST_BASE_GUARD

#include "CommonTest.hpp"

#include "WindowTestHelper.hpp"

namespace edo::UT::RHI
{
	constexpr float fixedTime = 0.0025f;
	constexpr uint32_t bufferingCount = 3;
	constexpr Vec2ui windowSize = { 1200, 900 };

	class RenderTestBase
	{
	protected:
		rhi::Device device;
		rhi::Swapchain swapchain;

		std::array<rhi::CommandList, bufferingCount> cmdLists;

		virtual void LoopRender() = 0;

	public:
		WindowHelper winHelper;

		virtual void InitAPI(rhi::ISurfaceHandle* _surface);
		virtual void CreateDevice(rhi::ISurfaceHandle* _surface);
		virtual void CreateSwapchain(rhi::ISurfaceHandle* _surface);

		virtual void InitRender() = 0;
		virtual void ShutdownRender() = 0;

		void LoopMain();

		virtual void DestroySwapchain();
		virtual void DestroyDevice();
		virtual void ShutdownAPI();
	};
}

#define EDO_RHI_UT_CONCAT_I(a, b, c, d, e, f) a##b##c##d##e##f
#define EDO_RHI_UT_CONCAT(a, b, c, d, e, f) EDO_RHI_UT_CONCAT_I(a, b, c, d, e, f)

#if EDO_RHI_DX12
	#define EDO_RHI_UT_TESTSUITE_GRAPHICS_NAME _DX12
#elif EDO_RHI_VK
	#define EDO_RHI_UT_TESTSUITE_GRAPHICS_NAME _VK
#elif EDO_RHI_GL
	#define EDO_RHI_UT_TESTSUITE_GRAPHICS_NAME _GL
#elif EDO_RHI_CPU
	#define EDO_RHI_UT_TESTSUITE_GRAPHICS_NAME _CPU
#else
	#define EDO_RHI_UT_TESTSUITE_GRAPHICS_NAME _NONEG
#endif

#if EDO_RHI_SDL3
	#define EDO_RHI_UT_TESTSUITE_WINDOW_NAME _SDL3
#elif EDO_RHI_GLFW
	#define EDO_RHI_UT_TESTSUITE_WINDOW_NAME _GLFW
#elif EDO_RHI_SFML
	#define EDO_RHI_UT_TESTSUITE_WINDOW_NAME _SFML
#else
	#define EDO_RHI_UT_TESTSUITE_WINDOW_NAME _NONEW
#endif

#define EDO_RHI_UT_TESTSUITE_NAME(_class) EDO_RHI_UT_CONCAT(t, EDO_RHI_UT_TEST_ID, _, _class, EDO_RHI_UT_TESTSUITE_GRAPHICS_NAME, EDO_RHI_UT_TESTSUITE_WINDOW_NAME)

#if !defined(EDO_CI)
	#define TEST_NO_CI(_tSuite, _tName, _tbody) TEST(_tSuite, _tName)_tbody
#else
	#define TEST_NO_CI(_tSuite, _tName, _tbody) TEST(_tSuite, _tName##_Skipped_CI){}
#endif

#define EDO_RENDER_TEST(_class)\
	_class rtest;\
	TEST_NO_CI(EDO_RHI_UT_TESTSUITE_NAME(_class), InitWindow, { rtest.winHelper.InitWindow(windowSize); })\
	TEST(EDO_RHI_UT_TESTSUITE_NAME(_class), InitAPI){ rtest.InitAPI(rtest.winHelper.surface); }\
	TEST(EDO_RHI_UT_TESTSUITE_NAME(_class), CreateDevice){ rtest.CreateDevice(rtest.winHelper.surface); }\
	TEST_NO_CI(EDO_RHI_UT_TESTSUITE_NAME(_class), CreateSwapchain, { rtest.CreateSwapchain(rtest.winHelper.surface); })\
	TEST(EDO_RHI_UT_TESTSUITE_NAME(_class), InitRender){ rtest.InitRender(); }\
	TEST(EDO_RHI_UT_TESTSUITE_NAME(_class), LoopMain){ rtest.LoopMain(); }\
	TEST(EDO_RHI_UT_TESTSUITE_NAME(_class), ShutdownRender){ rtest.ShutdownRender(); }\
	TEST_NO_CI(EDO_RHI_UT_TESTSUITE_NAME(_class), DestroySwapchain, { rtest.DestroySwapchain(); })\
	TEST(EDO_RHI_UT_TESTSUITE_NAME(_class), DestroyDevice){ rtest.DestroyDevice(); }\
	TEST(EDO_RHI_UT_TESTSUITE_NAME(_class), ShutdownAPI){ rtest.ShutdownAPI(); }\
	TEST_NO_CI(EDO_RHI_UT_TESTSUITE_NAME(_class), ShutdownWindow, { rtest.winHelper.ShutdownWindow(); })\

#if defined(EDO_RHI_UT_SELECT_TEST) && EDO_RHI_UT_SELECT_TEST != -1 && EDO_RHI_UT_SELECT_TEST != EDO_RHI_UT_TEST_ID
	#undef EDO_RENDER_TEST
	#define EDO_RENDER_TEST(_class)
#endif

#endif // EDO_RHI_RENDER_TEST_BASE_GUARD
