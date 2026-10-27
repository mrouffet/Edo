# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# EDO_CopyDXCRuntimeBinaries: Find and post-build copy DirectXShaderCompiler (DXC) runtime binaries to target output directory.
#
# PLATFORM:
#	WIN32:
#		Search for `dxcompiler.dll` and `dxil.dll` (contained either in Windows SDK or VulkanSDK).
#
#	UNIX:
#		Search for `libdxcompiler.so` and `libdxil.so `.
#
# USAGE:
#	EDO_CopyDXCRuntimeBinaries(
#		_target
#	)
#
# ARGUMENTS:
#	_target
#		CMake Target to register the copy command
#
function(EDO_CopyDXCRuntimeBinaries _target)

	if(WIN32)
		find_file(EDO_DXCOMPILER_DLL dxcompiler.dll REQUIRED)
		find_file(EDO_DXIL_DLL dxil.dll REQUIRED)
	else()
		find_file(EDO_DXCOMPILER_DLL libdxcompiler.so REQUIRED)
		find_file(EDO_DXIL_DLL libdxil.so REQUIRED)
	endif()

	add_custom_command(
		TARGET ${_target} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EDO_DXCOMPILER_DLL} $<TARGET_FILE_DIR:${_target}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EDO_DXIL_DLL} $<TARGET_FILE_DIR:${_target}>
		COMMENT "Copy DXC runtime DLLs to target output directory"
	)
endfunction()
