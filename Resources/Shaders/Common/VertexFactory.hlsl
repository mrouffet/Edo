// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#ifndef EDO_SHADER_VERTEX_FACTORY_GUARD
#define EDO_SHADER_VERTEX_FACTORY_GUARD

namespace SA
{
	/// Vertex Inputs from vertex buffer
	struct VertexFactory
	{
		float3 position : POSITION;

	#if EDO_VERTEX_NORMAL

		float3 normal : NORMAL;

	#endif

	#if EDO_VERTEX_TANGENT

		float3 tangent : TANGENT;

	#endif

	#if EDO_VERTEX_BITANGENT

		float3 bitangent : BITANGENT;

	#endif

	#if EDO_VERTEX_UV

		float2 uv : TEXCOORD;

	#endif

	#if EDO_VERTEX_COLOR

		float4 color : COLOR;

	#endif
	};
}

#endif // EDO_SHADER_VERTEX_FACTORY_GUARD
