// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_RHI_WINDOW_TEST_HELPER_GUARD
#define EDO_RHI_WINDOW_TEST_HELPER_GUARD

#include "CommonTest.hpp"

namespace edo::UT::RHI
{
	class WindowHelper
	{
	public:
		rhi::ISurfaceHandle* surface = nullptr;

	#if EDO_RHI_SDL3

		SDL_Window* window = nullptr;

		bool bIsSDLWindowOpen = true;
		void InitSDL3(const Vec2ui& _windowSize);
		void ShutdownSDL3();
		bool IsOpenSDL3();
		void ProcessEventsSDL3();

	#elif EDO_RHI_GLFW

		GLFWwindow* window = nullptr;

		void InitGLFW(const Vec2ui& _windowSize);
		void ShutdownGLFW();
		bool IsOpenGLFW();
		void ProcessEventsGLFW();

	#elif EDO_RHI_SFML

		sf::Window window;

		void InitSFML(const Vec2ui& _windowSize);
		void ShutdownSFML();
		bool IsOpenSFML();
		void ProcessEventsSFML();

	#endif

		void InitWindow(const Vec2ui& _windowSize);
		void ShutdownWindow();
		bool IsOpen();
		void ProcessEvents();
	};
}

#endif // EDO_RHI_WINDOW_TEST_HELPER_GUARD
