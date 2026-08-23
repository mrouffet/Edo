# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

include(FetchContent)

# EDO_FFIPackage: Find, Fetch, or Include Package.
#
# If the cmake target does not exist:
# 1. Try to find_package and link it
# 2. Include if already cloned and found at ${SOURCE_DIR}
# 3. Clone repository at config time and add it to ${SOURCE_DIR}
#
# Automatically init git submodules.
#
# USAGE:
#	EDO_FFIPackage(
#		CMAKE_TARGET		<cmake_target_name>
#		GIT_REPOSITORY		<repo_url>
#		GIT_TAG				<git_branch_or_tag>
#		PACKAGE_NAME		<package_name>
#		PACKAGE_VERSION		<package_version>
#		REPO_FULL_NAME		<repo_full_name>
#		SOURCE_DIR			<source_dir>
#	)
#
# ARGUMENTS:
#	CMAKE_TARGET
#		CMake target name.
#		Default is repository name from url
#		ex: https://github.com/glfw/glfw => CMAKE_TARGET = 'glfw'
#
#	GIT_REPOSITORY
#		Git repository URL (without '.git' at the end).
#
#	GIT_TAG
#		Git tag or branch to clone
#
#	PACKAGE_NAME
#		Package name to try find using find_package
#		Default is repository name from url
#
#	PACKAGE_VERSION
#		Package version to try find using find_package
#
#	REPO_FULL_NAME
#		Full name used for logging
#
#	SOURCE_DIR
#		Output source directory from ${CMAKE_SOURCE_DIR}/
#		Default is ThirdParty/
#
function(EDO_FFIPackage)

  #{ Args

	cmake_parse_arguments(
		PARGS
		""
		"CMAKE_TARGET;GIT_REPOSITORY;GIT_TAG;PACKAGE_NAME;PACKAGE_VERSION;REPO_FULL_NAME;SOURCE_DIR"
		""
		${ARGN}
	)

	# Repository name from url.
	string(FIND "${PARGS_GIT_REPOSITORY}" "/" lastSlashIndex REVERSE)
	math(EXPR lastSlashIndex "${lastSlashIndex} + 1" OUTPUT_FORMAT DECIMAL)
	string(SUBSTRING "${PARGS_GIT_REPOSITORY}" ${lastSlashIndex} -1 repoName)

	# Default same as repository name.
	if(NOT PARGS_CMAKE_TARGET)
		set(PARGS_CMAKE_TARGET ${repoName})
	endif()
	
	# Default same as repository name.
	if(NOT PARGS_PACKAGE_NAME)
		set(PARGS_PACKAGE_NAME ${repoName})
	endif()

	# Default same as repository name.
	if(NOT PARGS_REPO_FULL_NAME)
		set(PARGS_REPO_FULL_NAME ${repoName})
	endif()

	# Default ThirdParty/.
	if(NOT PARGS_SOURCE_DIR)
		set(PARGS_SOURCE_DIR "ThirdParty")
	endif()

  #}

	message("[EDO] ========== FFI Package ${PARGS_REPO_FULL_NAME} ==========")

	# Check CMAKE target already available
	if(NOT TARGET ${PARGS_CMAKE_TARGET})

		# Try locating installed package
		message("[EDO] Searching for package `${PARGS_PACKAGE_NAME} ${PACKAGE_VERSION}`...")
		find_package(${PARGS_PACKAGE_NAME} ${PACKAGE_VERSION} QUIET)

		if(NOT ${${PARGS_PACKAGE_NAME}_FOUND})

			message("[EDO] Package `${PARGS_PACKAGE_NAME} ${PACKAGE_VERSION}` not found.")

			if(EXISTS "${CMAKE_SOURCE_DIR}/${PARGS_SOURCE_DIR}/${repoName}/CMakeLists.txt")

				# Content already cloned
				message("[EDO] Package Content `${repoName}` already cloned: adding to build-tree.")

				add_subdirectory(${CMAKE_SOURCE_DIR}/${PARGS_SOURCE_DIR}/${repoName} ${CMAKE_BINARY_DIR}/${PARGS_SOURCE_DIR}/${repoName})

			else()

				# Fetch
				message("[EDO] Fetching Package Content `${repoName}`...")

				FetchContent_Declare(
					${PARGS_CMAKE_TARGET}
					GIT_REPOSITORY	${PARGS_GIT_REPOSITORY}
					GIT_TAG			${PARGS_GIT_TAG}
					SOURCE_DIR		${CMAKE_SOURCE_DIR}/${PARGS_SOURCE_DIR}/${repoName}
				)
	
				FetchContent_MakeAvailable(${PARGS_CMAKE_TARGET})
	
			endif()


		else()

			message("[EDO] Package `${PARGS_PACKAGE_NAME} ${PACKAGE_VERSION}` found and added to build-tree.")

		endif()

	else()

		message("[EDO] CMake Target `${PARGS_CMAKE_TARGET}` already in build-tree. Skipping...")

	endif()

	message("[EDO] ====================")

endfunction(EDO_FFIPackage)
