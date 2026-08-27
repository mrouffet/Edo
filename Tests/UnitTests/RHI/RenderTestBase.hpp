// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_RHI_RENDER_TEST_BASE_GUARD
#define EDO_RHI_RENDER_TEST_BASE_GUARD

#include "CommonTest.hpp"

#include <edo_debug.hpp>
#include <edo_maths.hpp>
using namespace edo;

#include <edo_rhi.hpp>

namespace edo::UT::RHI
{
	constexpr float fixedTime = 0.0025f;
	constexpr uint32_t bufferingCount = 3;
	constexpr Vec2ui windowSize = { 1200, 900 };

	class RenderTestBase
	{
	protected:
		GLFWwindow* window = nullptr;

		rhi::Device device;
		rhi::Swapchain swapchain;

		std::array<rhi::CommandList, bufferingCount> cmdLists;
	public:
		void InitLogger();
		void InitGLFW();
		void InitRenderBase();
		virtual void InitRender_Impl() = 0;

		void Loop();
		virtual void LoopRender_Impl() = 0;

		virtual void ShutdownRender_Impl() = 0;
		void ShutdownRenderBase();
		void ShutdownGLFW();
	};
}

#if EDO_UT_RHI_DX12
	#define RHITestSuite(_name) RHITests_ ##_name ##_DX12
#endif
#if EDO_UT_RHI_VK
	#define RHITestSuite(_name) RHITests_ ##_name ##_VK
#endif
#if EDO_UT_RHI_GL
	#define RHITestSuite(_name) RHITests_ ##_name ##_GL
#endif
#if EDO_UT_RHI_CPU
	#define RHITestSuite(_name) RHITests_ ##_name ##_CPU
#endif

#define EDO_RENDER_TEST(_class, _name)\
	_class rtest;\
	TEST(RHITestSuite(_name), Init_Logger) { rtest.InitLogger(); }\
	TEST(RHITestSuite(_name), Init_GLFW) { rtest.InitGLFW(); }\
	TEST(RHITestSuite(_name), Init_Render_Base) { rtest.InitRenderBase(); }\
	TEST(RHITestSuite(_name), Init_Render_Impl) { rtest.InitRender_Impl(); }\
	TEST(RHITestSuite(_name), Loop) { rtest.Loop(); }\
	TEST(RHITestSuite(_name), Shutdown_Render_Impl) { rtest.ShutdownRender_Impl(); }\
	TEST(RHITestSuite(_name), Shutdown_Render_Base) { rtest.ShutdownRenderBase(); }\
	TEST(RHITestSuite(_name), Shutdown_GLFW) { rtest.ShutdownGLFW(); }

#endif // EDO_RHI_RENDER_TEST_BASE_GUARD
