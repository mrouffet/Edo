// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "CommonTest.hpp"
// Must be defined before including `RenderTestBase.hpp` here
#define EDO_RHI_IMPLEMENTATION 1
#include <edo_rhi.hpp>

#include "RenderTestBase.hpp"

namespace edo::UT::RHI
{
	void RenderTestBase::InitLogger()
	{
		//edo::Debug::logger->EnableLevel(edo::LogLevel::Verbose);
	}

	void RenderTestBase::InitGLFW()
	{
		auto GLFWErrorCallback = [](int32_t error, const char* description) {
			EDO_LOG((L"GLFW Error [%1]: %2", error, description), Error, Edo.GLFW.API);
		};

		glfwSetErrorCallback(GLFWErrorCallback);
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(windowSize.x, windowSize.y, "Edo_RHI_Window", nullptr, nullptr);

		if (!window)
		{
			EDO_LOG(L"GLFW create window failed!", Error, Edo.GLFW);
			return;
		}
		else
		{
			EDO_LOG("GLFW create window success.", Verbose, Edo.GLFW, window);
		}

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void RenderTestBase::InitRenderBase()
	{
		rhi::Initialize();

		device.Create();

		rhi::SwapchainDesc scDesc{
			.width = windowSize.x,
			.height = windowSize.y,
			.bufferingCount = bufferingCount,
			.surface = rhi::GLFWSurfaceHandle(window)
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
		while (!glfwWindowShouldClose(window))
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

				glfwPollEvents();

				glfwPollEvents();

				// Process input
				{
					if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
						glfwSetWindowShouldClose(window, true);
				}

				LoopRender_Impl();
			}
		}
	}


	void RenderTestBase::ShutdownRenderBase()
	{
		for (uint32_t i = 0; i < bufferingCount; ++i)
		{
			device.DestroyCommandList(cmdLists[i]);
		}

		swapchain.Destroy(device);
		device.Destroy();

		rhi::Shutdown();
	}

	void RenderTestBase::ShutdownGLFW()
	{
		glfwDestroyWindow(window);
		EDO_LOG(L"Destroy Window success", Verbose, GLFW, window);
		window = nullptr;

		glfwTerminate();
	}
}
