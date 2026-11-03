// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#define EDO_RHI_IMPLEMENTATION 1
#include "CommonTest.hpp"

#include "RenderTestBase.hpp"

namespace edo::UT::RHI
{
	void RenderTestBase::InitAPI(rhi::ISurfaceHandle* _surface)
	{
		rhi::Initialize(_surface);
	}

	void RenderTestBase::CreateDevice(rhi::ISurfaceHandle* _surface)
	{
		device.Create(_surface);
	}

	void RenderTestBase::CreateSwapchain(rhi::ISurfaceHandle* _surface)
	{
		rhi::SwapchainDesc scDesc{
			.bufferingCount = bufferingCount,
			.surface = *_surface
		};

		swapchain.Create(device, scDesc);
	}


	void RenderTestBase::LoopMain()
	{
		float accumulateTime = 0.0f;
		auto start = std::chrono::steady_clock::now();

	#if !defined(EDO_CI)
		while (winHelper.IsOpen())
	#endif
		{
			auto end = std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - start).count();
			accumulateTime += deltaTime;
			start = end;

	#if defined(EDO_CI)
			accumulateTime = fixedTime;
	#endif // defined(EDO_CI)

			// Fixed Update
			if (accumulateTime >= fixedTime)
			{
				accumulateTime -= fixedTime;

				winHelper.ProcessEvents();
			}
			
			LoopRender();

	#if !defined(EDO_CI)
			swapchain.Present(device);
	#endif // !defined(EDO_CI)
		}

		device.WaitIdle();
	}


	void RenderTestBase::DestroySwapchain()
	{
		swapchain.Destroy(device);
	}

	void RenderTestBase::DestroyDevice()
	{
		device.Destroy();
	}

	void RenderTestBase::ShutdownAPI()
	{
		rhi::Shutdown();
	}
}
