// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "RenderTestBase.hpp"

namespace edo::UT::RHI
{
	class HelloCubeTest : public RenderTestBase
	{
	public:
		void InitRender_Impl() override final
		{
		}

		void LoopRender_Impl() override final
		{
		}

		void ShutdownRender_Impl() override final
		{
		}
	};

	EDO_RENDER_TEST(HelloCubeTest, 2_HelloCube)
}
