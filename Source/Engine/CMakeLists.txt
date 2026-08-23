# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# ===== Target Edo Engine =====
file(GLOB_RECURSE EDO_ENGINE_SOURCES_CPP "*.cpp")

add_library(EdoEngine STATIC ${EDO_ENGINE_SOURCES_CPP})

target_link_libraries(EdoEngine
	PRIVATE EdoBase
	PUBLIC
)
