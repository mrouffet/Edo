# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

file(GLOB_RECURSE EDO_DEMO_SAMPLE_SOURCES "*.cpp")


# ===== Target =====
add_executable(EdoDemo ${EDO_DEMO_SAMPLE_SOURCES})

target_link_libraries(EdoDemo PUBLIC
	EdoBase
	d3d12.lib dxgi.lib dxguid.lib dxcompiler.lib
)

EDO_LinkTestWindowAPI(EdoDemo)

EDO_CopyTestsResources(EdoDemo)
