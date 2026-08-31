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
	#if EDO_RHI_GLFW
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
	#elif EDO_RHI_SDL3
		SDL_Window* window = nullptr;
		bool bIsSDLWindowOpen = true;
		void InitSDL3(const Vec2ui& _windowSize);
		void ShutdownSDL3();
		bool IsOpenSDL3();
		void ProcessEventsSDL3();
	#endif

		void InitWindow(const Vec2ui& _windowSize);
		void ShutdownWindow();
		bool IsOpen();
		void ProcessEvents();
	};
}

#if EDO_RHI_GLFW
	#define EDO_RHI_UT_Init_Window_Name Init_GLFW
	#define EDO_RHI_UT_Shutdown_Window_Name Shutdown_GLFW
#elif EDO_RHI_SFML
	#define EDO_RHI_UT_Init_Window_Name Init_SFML
	#define EDO_RHI_UT_Shutdown_Window_Name Shutdown_SFML
#elif EDO_RHI_SDL3
	#define EDO_RHI_UT_Init_Window_Name Init_SDL3
	#define EDO_RHI_UT_Shutdown_Window_Name Shutdown_SDL3
#endif

#endif // EDO_RHI_WINDOW_TEST_HELPER_GUARD
