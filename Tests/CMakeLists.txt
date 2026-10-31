# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

set(EDO_TESTS_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)

function(EDO_CopyTestsResources _target)
	add_custom_command(
		TARGET ${_target}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${EDO_TESTS_RESOURCE_DIR}
		$<TARGET_FILE_DIR:${_target}>/Resources
	)
endfunction()


# ===== Window Modules =====
## SDL
option(EDO_TEST_SDL_OPT "Should fetch SDL for tests" OFF)
if(EDO_TEST_SDL_OPT)
	EDO_FFIPackage(
		CMAKE_TARGET		SDL
		GIT_REPOSITORY		https://github.com/libsdl-org/SDL
		GIT_TAG				main
		PACKAGE_NAME		SDL
		REPO_FULL_NAME		"SDL"
	)
endif()

## GLFW
option(EDO_TEST_GLFW_OPT "Should fetch GLFW for tests" OFF)
if(EDO_TEST_GLFW_OPT)
	EDO_FFIPackage(
		CMAKE_TARGET		glfw
		GIT_REPOSITORY		https://github.com/glfw/glfw
		GIT_TAG				master
		PACKAGE_NAME		glfw3
		PACKAGE_VERSION		3.5
		REPO_FULL_NAME		"GLFW3"
	)
endif()

## SFML
option(EDO_TEST_SFML_OPT "Should fetch SFML for tests" OFF)
if(EDO_TEST_SFML_OPT)
	EDO_FFIPackage(
		CMAKE_TARGET		sfml
		GIT_REPOSITORY		https://github.com/SFML/SFML
		GIT_TAG				master
		PACKAGE_NAME		sfml
		REPO_FULL_NAME		"SFML"
	)
endif()

## Link helper
function(EDO_LinkTestWindowAPI _target)
	if(EDO_TEST_GLFW_OPT)
		target_link_libraries(${_target} PRIVATE glfw)
	endif()
	if(EDO_TEST_SFML_OPT)
		target_link_libraries(${_target} PRIVATE SFML::Window)
	endif()
	if(EDO_TEST_SDL_OPT)
		target_link_libraries(${_target} PRIVATE SDL3::SDL3)
	endif()
endfunction()



# ===== Entrypoints =====
add_subdirectory(Samples)
add_subdirectory(UnitTests)
