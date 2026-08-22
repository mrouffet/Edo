// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "CommonTest.hpp"

namespace edo::UT::RHI
{
	edo::rhi::Device device;

	TEST(RHITests, ForwardRenderer)
	{
		// Init
		{
			edo::Debug::logger->EnableLevel(edo::LogLevel::Verbose);

			edo::rhi::Initialize();

			device.Create();
		}


		// Loop
		{
		}


		// Shutdown
		{
			device.Destroy();

			edo::rhi::Shutdown();
		}
	}
}
