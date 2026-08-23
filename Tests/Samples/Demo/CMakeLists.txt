# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

file(GLOB_RECURSE EDO_DEMO_SAMPLE_SOURCES "*.cpp")


# ===== Target =====
add_executable(Edo_Demo ${EDO_DEMO_SAMPLE_SOURCES})

target_link_libraries(Edo_Demo PUBLIC
	Edo glfw
	d3d12.lib dxgi.lib dxguid.lib
)
