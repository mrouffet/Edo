// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "RenderTestBase.hpp"

namespace edo::UT::RHI
{
	class HelloTriangleTest : public RenderTestBase
	{
		rhi::Shader vertexSH;
		rhi::Shader pixelSH;

	public:
		void InitRender_Impl() override final
		{
			vertexSH = rhi::Shader::CompileFromSource(device, { L"Resources/Shaders/Passes/HelloTriangle.hlsl", L"mainVS", L"vs_6_5" });
			pixelSH = rhi::Shader::CompileFromSource(device, { L"Resources/Shaders/Passes/HelloTriangle.hlsl", L"mainPS", L"ps_6_5" });
		}

		void LoopRender_Impl() override final
		{
		}

		void ShutdownRender_Impl() override final
		{
			pixelSH.Destroy(device);
			vertexSH.Destroy(device);
		}
	};

	EDO_RENDER_TEST(HelloTriangleTest, 1_HelloTriangle)
}
