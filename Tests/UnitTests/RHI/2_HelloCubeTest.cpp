// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#define EDO_RHI_UT_TEST_ID 2

#include "RenderTestBase.hpp"

namespace edo::UT::RHI
{
	class HelloCubeTest : public RenderTestBase
	{
	public:
		void InitRender() override final
		{
		}

		void LoopRender() override final
		{
		}

		void ShutdownRender() override final
		{
		}
	};

	EDO_RENDER_TEST(HelloCubeTest)
}
