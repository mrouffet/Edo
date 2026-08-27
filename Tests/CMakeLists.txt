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

add_subdirectory(Samples)
add_subdirectory(UnitTests)
