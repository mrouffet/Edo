# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

file(GLOB_RECURSE EDO_DEMO_SAMPLE_SOURCES "*.cpp")


# ===== Target =====
add_executable(EdoDemo ${EDO_DEMO_SAMPLE_SOURCES})

target_link_libraries(EdoDemo PUBLIC
	EdoBase glfw
	d3d12.lib dxgi.lib dxguid.lib dxcompiler.lib
)


add_custom_command(
    TARGET EdoDemo
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources
    $<TARGET_FILE_DIR:EdoDemo>/Resources
)
