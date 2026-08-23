# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.



# ===== GLFW Module =====
EDO_FFIPackage(
	CMAKE_TARGET		glfw
	GIT_REPOSITORY		https://github.com/glfw/glfw
	GIT_TAG				master
	PACKAGE_NAME		glfw3
	PACKAGE_VERSION		3.5
	REPO_FULL_NAME		"GLFW3"
)



# ===== Entrypoints =====
add_subdirectory(Demo)
