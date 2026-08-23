# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.



# Project

project(Edo_Samples)


# ===== GLFW Module =====
# Try locating GLFW3, local clone otherwise.
find_package(glfw3 3.5)

if(NOT ${glfw3_FOUND})
	EDO_FetchOrInclude(
		CMAKE_TARGET		glfw
		GIT_REPOSITORY		https://github.com/glfw/glfw
		GIT_TAG				master
		REPO_FULL_NAME		"GLFW3"
	)
endif()



# ===== Entrypoints =====
add_subdirectory(Demo)
