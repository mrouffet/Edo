# Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.



# ===== GoogleTest Module =====
EDO_FFIPackage(
	CMAKE_TARGET		googletest
	GIT_REPOSITORY		https://github.com/google/googletest
	GIT_TAG				v1.18.0
	REPO_FULL_NAME		"GoogleTest"
)

include(GoogleTest)



# ===== Entrypoints =====
add_subdirectory(Debug)
add_subdirectory(Maths)
add_subdirectory(Event)
add_subdirectory(RHI)
