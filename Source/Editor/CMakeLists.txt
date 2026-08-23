# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

# ===== Target Edo Editor =====
file(GLOB_RECURSE EDO_EDITOR_SOURCES_CPP "*.cpp")

add_executable(EdoEditor ${EDO_EDITOR_SOURCES_CPP})

target_link_libraries(EdoEditor
	PRIVATE EdoBase
	PUBLIC EdoEngine
)
