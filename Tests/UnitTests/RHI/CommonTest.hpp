// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_RHI_COMMON_TEST_GUARD
#define EDO_RHI_COMMON_TEST_GUARD

#include <gtest/gtest.h>

#include <edo_rhi.hpp>

#if EDO_UT_RHI_DX12
	#define RHITests RHITests_DX12
#endif
#if EDO_UT_RHI_VK
	#define RHITests RHITests_VK
#endif

#endif // EDO_RHI_COMMON_TEST_GUARD
