# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

include(FetchContent)

# Clone repository or include if already cloned at config time and add it to ThirdParty/.
# Automatically init git submodules.
#
# USAGE:
#	EDO_FetchOrInclude(
#		CMAKE_TARGET	<cmake_target_name>
#		GIT_REPOSITORY	<repo_url>
#		GIT_TAG			<git_branch_or_tag>
#		REPO_FULL_NAME	<repo_full_name>
#		SOURCE_DIR		<source_dir>
#	)
#
# ARGUMENTS:
#	CMAKE_TARGET
#		CMake target name. Default is repository name from url
#		ex: https://github.com/glfw/glfw => CMAKE_TARGET = 'glfw'
#
#	GIT_REPOSITORY
#		Git repository URL (without '.git' at the end).
#
#	GIT_TAG
#		Git tag or branch to clone
#
#	REPO_FULL_NAME
#		Full name used for logging
#
#	SOURCE_DIR
#		Output source directory from ${CMAKE_SOURCE_DIR}/
#		Default is ThirdParty/
#
function(EDO_FetchOrInclude)

  #{ Args

	cmake_parse_arguments(
		PARGS
		""
		"CMAKE_TARGET;GIT_REPOSITORY;GIT_TAG;REPO_FULL_NAME;SOURCE_DIR"
		""
		${ARGN}
	)

	# Repository name from url.
	string(FIND "${PARGS_GIT_REPOSITORY}" "/" lastSlashIndex REVERSE)
	math(EXPR lastSlashIndex "${lastSlashIndex} + 1" OUTPUT_FORMAT DECIMAL)
	string(SUBSTRING "${PARGS_GIT_REPOSITORY}" ${lastSlashIndex} -1 repoName)

	# Default same as repository name.
	if(NOT PARGS_REPO_FULL_NAME)
		set(PARGS_REPO_FULL_NAME ${repoName})
	endif()

	# Default same as repository name.
	if(NOT PARGS_CMAKE_TARGET)
		set(PARGS_CMAKE_TARGET ${repoName})
	endif()

	# Default ThirdParty/.
	if(NOT PARGS_SOURCE_DIR)
		set(PARGS_SOURCE_DIR "ThirdParty")
	endif()

  #}


	# Check CMAKE target already present
	if(NOT TARGET ${PARGS_CMAKE_TARGET})
	
		if(EXISTS "${CMAKE_SOURCE_DIR}/${PARGS_SOURCE_DIR}/${repoName}/CMakeLists.txt")

			# Content already cloned
			message("Including ${PARGS_REPO_FULL_NAME}...")

			add_subdirectory(${CMAKE_SOURCE_DIR}/${PARGS_SOURCE_DIR}/${repoName} ${CMAKE_BINARY_DIR}/${PARGS_SOURCE_DIR}/${repoName})

		else()

			# Fetch
			message("Fetching ${PARGS_REPO_FULL_NAME}...")

			FetchContent_Declare(
				${PARGS_CMAKE_TARGET}
				GIT_REPOSITORY	${PARGS_GIT_REPOSITORY}
				GIT_TAG			${PARGS_GIT_TAG}
				SOURCE_DIR		${CMAKE_SOURCE_DIR}/${PARGS_SOURCE_DIR}/${repoName}
			)
	
			FetchContent_MakeAvailable(${PARGS_CMAKE_TARGET})
	
		endif()

	endif()

endfunction(EDO_FetchOrInclude)
