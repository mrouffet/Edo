// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#define EDO_DEBUG_IMPLEMENTATION 1
#include <edo_debug.hpp>
using namespace edo;

#include <edo_maths.hpp>

#define EDO_RHI_IMPLEMENTATION 1
#include <edo_rhi.hpp>

GLFWwindow* window = nullptr;
void GLFWErrorCallback(int32_t error, const char* description)
{
	EDO_LOG((L"GLFW Error [%1]: %2", error, description), Error, Edo.GLFW.API);
}

constexpr Vec2ui windowSize = { 1200, 900 };

rhi::Device device;
rhi::Swapchain swapchain;

int main()
{
	// Init
	{
		Debug::InitDefaultLogger();
		Debug::logger->EnableLevel(LogLevel::Verbose);

		// GLFW
		{
			glfwSetErrorCallback(GLFWErrorCallback);
			glfwInit();

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			window = glfwCreateWindow(windowSize.x, windowSize.y, "FVTDX12_DX12-Window", nullptr, nullptr);

			if (!window)
			{
				EDO_LOG(L"GLFW create window failed!", Error, GLFW);
				return EXIT_FAILURE;
			}
			else
			{
				EDO_LOG("GLFW create window success.", Verbose, GLFW, window);
			}

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		// Render
		{
			rhi::Initialize();

			device.Create();

			rhi::SwapchainDesc scDesc{
				.width = windowSize.x,
				.height = windowSize.y,
				.surface = rhi::GLFWSurfaceHandle(window)
			};
			swapchain.Create(device, scDesc);
		}
	}


	// Loop
	{
		const float fixedTime = 0.0025f;
		float accumulateTime = 0.0f;
		auto start = std::chrono::steady_clock::now();

		while (!glfwWindowShouldClose(window))
		{
			auto end = std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - start).count();
			accumulateTime += deltaTime;
			start = end;

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
			}
		}
	}


	// Shutdown
	{
		// Render
		{

			swapchain.Destroy(device);
			device.Destroy();

			rhi::Shutdown();
		}


		// GLFW
		{
			glfwDestroyWindow(window);
			EDO_LOG(L"Destroy Window success", Verbose, GLFW, window);
			window = nullptr;

			glfwTerminate();
		}
	}

	return EXIT_SUCCESS;
}
