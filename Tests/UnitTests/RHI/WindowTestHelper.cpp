// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "WindowTestHelper.hpp"

namespace edo::UT::RHI
{
#if EDO_RHI_GLFW

	void WindowHelper::InitGLFW(const Vec2ui& _windowSize)
	{
		auto GLFWErrorCallback = [](int32_t error, const char* description) {
			EDO_LOG((L"GLFW Error [%1]: %2", error, description), Error, Edo.GLFW.API);
		};

		glfwSetErrorCallback(GLFWErrorCallback);
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(_windowSize.x, _windowSize.y, "Edo_RHI_Window_GLFW", nullptr, nullptr);

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

	void WindowHelper::ShutdownGLFW()
	{
		glfwDestroyWindow(window);
		EDO_LOG(L"Destroy Window success", Verbose, GLFW, window);
		window = nullptr;

		glfwTerminate();
	}

	bool WindowHelper::IsOpenGLFW()
	{
		return !glfwWindowShouldClose(window);
	}

	void WindowHelper::ProcessEventsGLFW()
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

#elif EDO_RHI_SFML

	void WindowHelper::InitSFML(const Vec2ui& _windowSize)
	{
		window = sf::Window(sf::VideoMode({ _windowSize.x, _windowSize.y }), "Edo_RHI_Window_SFML");
	}

	void WindowHelper::ShutdownSFML()
	{
		window.~Window();
	}

	bool WindowHelper::IsOpenSFML()
	{
		return window.isOpen();
	}

	void WindowHelper::ProcessEventsSFML()
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				window.close();
		}
	}

#elif EDO_RHI_SDL3

	void WindowHelper::InitSDL3(const Vec2ui& _windowSize)
	{
		bool bInit = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
		EDO_ASSERT(bInit, Edo.SDL3, L"SDL3 API init failed!");

		window = SDL_CreateWindow("Edo_RHI_Window_SDL3", _windowSize.x, _windowSize.y, 0 /* | SDL_WINDOW_VULKAN */);
	}

	void WindowHelper::ShutdownSDL3()
	{
		SDL_DestroyWindow(window);
		window = nullptr;

		SDL_Quit();
	}

	bool WindowHelper::IsOpenSDL3()
	{
		return bIsSDLWindowOpen;
	}

	void WindowHelper::ProcessEventsSDL3()
	{
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_EVENT_QUIT || (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE))
			{
				bIsSDLWindowOpen = false;
			}
		}
	}

#endif


	void WindowHelper::InitWindow(const Vec2ui& _windowSize)
	{
	#if EDO_RHI_GLFW
		InitGLFW(_windowSize);
	#elif EDO_RHI_SFML
		InitSFML(_windowSize);
	#elif EDO_RHI_SDL3
		InitSDL3(_windowSize);
	#endif
	}

	void WindowHelper::ShutdownWindow()
	{
	#if EDO_RHI_GLFW
		ShutdownGLFW();
	#elif EDO_RHI_SFML
		ShutdownSFML();
	#elif EDO_RHI_SDL3
		ShutdownSDL3();
	#endif
	}

	bool WindowHelper::IsOpen()
	{
	#if EDO_RHI_GLFW
		return IsOpenGLFW();
	#elif EDO_RHI_SFML
		return IsOpenSFML();
	#elif EDO_RHI_SDL3
		return IsOpenSDL3();
	#endif
	}

	void WindowHelper::ProcessEvents()
	{
	#if EDO_RHI_GLFW
		ProcessEventsGLFW();
	#elif EDO_RHI_SFML
		ProcessEventsSFML();
	#elif EDO_RHI_SDL3
		ProcessEventsSDL3();
	#endif
	}
}
