// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#define EDO_RHI_IMPLEMENTATION 1
#include "CommonTest.hpp"

#include "RenderTestBase.hpp"

namespace edo::UT::RHI
{
	void RenderTestBase::InitLogger()
	{
		edo::Debug::logger->EnableLevel(edo::LogLevel::Verbose);
	}

	void RenderTestBase::InitRenderBase()
	{
	#if EDO_RHI_GLFW
			rhi::GLFWSurfaceHandle surface(winHelper.window);
	#elif EDO_RHI_SFML
			rhi::SFMLSurfaceHandle surface(winHelper.window);
	#elif EDO_RHI_SDL3
			rhi::SDL3SurfaceHandle surface(winHelper.window);
	#endif

		rhi::Initialize(&surface);

		device.Create(&surface);

		rhi::SwapchainDesc scDesc{
			.bufferingCount = bufferingCount,
			.surface = surface

		};
		swapchain.Create(device, scDesc);

		for (uint32_t i = 0; i < bufferingCount; ++i)
		{
			cmdLists[i] = device.CreateCommandList();
		}
	}


	void RenderTestBase::Loop()
	{
		float accumulateTime = 0.0f;
		auto start = std::chrono::steady_clock::now();

	#if !defined(EDO_CI_CD)
		while (winHelper.IsOpen())
	#endif
		{
			auto end = std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - start).count();
			accumulateTime += deltaTime;
			start = end;

	#if defined(EDO_CI_CD)
			accumulateTime = fixedTime;
	#endif

			// Fixed Update
			if (accumulateTime >= fixedTime)
			{
				accumulateTime -= fixedTime;

				winHelper.ProcessEvents();
			}
			
			LoopRender_Impl();

			swapchain.Present(device);
		}
	}


	void RenderTestBase::ShutdownRenderBase()
	{
		device.WaitIdle();

		for (uint32_t i = 0; i < bufferingCount; ++i)
		{
			device.DestroyCommandList(cmdLists[i]);
		}

		swapchain.Destroy(device);
		device.Destroy();

		rhi::Shutdown();
	}
}
