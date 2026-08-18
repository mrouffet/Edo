// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_SH_RHI_GUARD
#define EDO_SH_RHI_GUARD


#if !defined(EDO_RHI_DX12) && !defined(EDO_RHI_VK) && !defined(EDO_RHI_CPU)

	#if WIN32
	
		#define EDO_RHI_DX12 1

	#else

		#define EDO_RHI_VK 1

	#endif

#endif

#ifndef EDO_DEBUG
	#if !defined(NDEBUG) || defined(_DEBUG)

		#define EDO_DEBUG 1

	#else

		#define EDO_DEBUG 0

	#endif
#endif


#include <cstdint>
#include <string>
#include <type_traits>

#if EDO_RHI_DX12

#include <d3d12.h>		// Requires `d3d12.lib`
#include <DXGIDebug.h>	// Requires `dxguid.lib`
#include <dxgi1_6.h>	// Requires `dxgi.lib`

//#include <dxc/dxcapi.h>

#include <wrl.h>

namespace edo::rhi
{
	template <typename T>
	using MComPtr = Microsoft::WRL::ComPtr<T>;
}

#endif

#if EDO_RHI_VK

#include <vulkan/vulkan.h>

#endif

namespace edo::rhi
{
// ##############################################################
// #					TYPES									#
// ##############################################################

	class Device;

	class Swapchain;

	class Shader;

	struct GfxPipelineDesc;
	struct CompPipelineDesc;
	class Pipeline;

	struct BufferDesc;
	class Buffer;

	struct TextureDesc;
	class Texture;

// ##############################################################


// ##############################################################
// #					Format									#
// ##############################################################

	enum class Format
	{
		Unknown = 0,

		R8_UNORM,
		R8_UINT,
		RG8_UNORM,
		RG8_UINT,
		RGBA8_UNORM,
		RGBA8_sRGB,
		RGBA8_UINT,

		R16_UNORM,
		R16_UINT,
		R16_FLOAT,
		RG16_UNORM,
		RG16_UINT,
		RG16_FLOAT,
		RGBA16_UNORM,
		RGBA16_UINT,
		RGBA16_FLOAT,

		R32_UINT,
		R32_FLOAT,
		RG32_UINT,
		RG32_FLOAT,
		RGB32_UINT,
		RGB32_FLOAT,
		RGBA32_UINT,
		RGBA32_FLOAT,

		D16,
		D24S8,
		D32,
		D32S8,
	};

#if EDO_RHI_IMPLEMENTATION

	namespace intl
	{
#if EDO_RHI_DX12

		DXGI_FORMAT MapFormatToDX(Format _format)
		{
			switch (_format)
			{
				case Format::Unknown:
					return DXGI_FORMAT_UNKNOWN;

				case Format::R8_UNORM:
					return DXGI_FORMAT_R8_UNORM;
				case Format::R8_UINT:
					return DXGI_FORMAT_R8_UINT;
				case Format::RG8_UNORM:
					return DXGI_FORMAT_R8G8_UNORM;
				case Format::RG8_UINT:
					return DXGI_FORMAT_R8G8_UINT;
				case Format::RGBA8_UNORM:
					return DXGI_FORMAT_R8G8B8A8_UNORM;
				case Format::RGBA8_sRGB:
					return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
				case Format::RGBA8_UINT:
					return DXGI_FORMAT_R8G8B8A8_UINT;

				case Format::R16_UNORM:
					return DXGI_FORMAT_R16_UNORM;
				case Format::R16_UINT:
					return DXGI_FORMAT_R16_UINT;
				case Format::R16_FLOAT:
					return DXGI_FORMAT_R16_FLOAT;
				case Format::RG16_UNORM:
					return DXGI_FORMAT_R16G16_UNORM;
				case Format::RG16_UINT:
					return DXGI_FORMAT_R16G16_UINT;
				case Format::RG16_FLOAT:
					return DXGI_FORMAT_R16G16_FLOAT;
				case Format::RGBA16_UNORM:
					return DXGI_FORMAT_R16G16B16A16_UNORM;
				case Format::RGBA16_UINT:
					return DXGI_FORMAT_R16G16B16A16_UINT;
				case Format::RGBA16_FLOAT:
					return DXGI_FORMAT_R16G16B16A16_FLOAT;

				case Format::R32_UINT:
					return DXGI_FORMAT_R32_UINT;
				case Format::R32_FLOAT:
					return DXGI_FORMAT_R32_FLOAT;
				case Format::RG32_UINT:
					return DXGI_FORMAT_R32G32_UINT;
				case Format::RG32_FLOAT:
					return DXGI_FORMAT_R32G32_FLOAT;
				case Format::RGB32_UINT:
					return DXGI_FORMAT_R32G32B32_UINT;
				case Format::RGB32_FLOAT:
					return DXGI_FORMAT_R32G32B32_FLOAT;
				case Format::RGBA32_UINT:
					return DXGI_FORMAT_R32G32B32A32_UINT;
				case Format::RGBA32_FLOAT:
					return DXGI_FORMAT_R32G32B32A32_FLOAT;

				case Format::D16:
					return DXGI_FORMAT_D16_UNORM;
				case Format::D24S8:
					return DXGI_FORMAT_D24_UNORM_S8_UINT;
				case Format::D32:
					return DXGI_FORMAT_D32_FLOAT;
				case Format::D32S8:
					return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;

				default:
				{
					// SA_LOG(Error)
					return DXGI_FORMAT_UNKNOWN;
				}
			}
		}

		Format MapFormatFromDX(DXGI_FORMAT _format)
		{
			switch (_format)
			{
				case DXGI_FORMAT_UNKNOWN:
					return Format::Unknown;

				case DXGI_FORMAT_R8_UNORM:
					return Format::R8_UNORM;
				case DXGI_FORMAT_R8_UINT:
					return Format::R8_UINT;
				case DXGI_FORMAT_R8G8_UNORM:
					return Format::RG8_UNORM;
				case DXGI_FORMAT_R8G8_UINT:
					return Format::RG8_UINT;
				case DXGI_FORMAT_R8G8B8A8_UNORM:
					return Format::RGBA8_UNORM;
				case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
					return Format::RGBA8_sRGB;
				case DXGI_FORMAT_R8G8B8A8_UINT:
					return Format::RGBA8_UINT;

				case DXGI_FORMAT_R16_UNORM:
					return Format::R16_UNORM;
				case DXGI_FORMAT_R16_UINT:
					return Format::R16_UINT;
				case DXGI_FORMAT_R16_FLOAT:
					return Format::R16_FLOAT;
				case DXGI_FORMAT_R16G16_UNORM:
					return Format::RG16_UNORM;
				case DXGI_FORMAT_R16G16_UINT:
					return Format::RG16_UINT;
				case DXGI_FORMAT_R16G16_FLOAT:
					return Format::RG16_FLOAT;
				case DXGI_FORMAT_R16G16B16A16_UNORM:
					return Format::RGBA16_UNORM;
				case DXGI_FORMAT_R16G16B16A16_UINT:
					return Format::RGBA16_UINT;
				case DXGI_FORMAT_R16G16B16A16_FLOAT:
					return Format::RGBA16_FLOAT;

				case DXGI_FORMAT_R32_UINT:
					return Format::R32_UINT;
				case DXGI_FORMAT_R32_FLOAT:
					return Format::R32_FLOAT;
				case DXGI_FORMAT_R32G32_UINT:
					return Format::RG32_UINT;
				case DXGI_FORMAT_R32G32_FLOAT:
					return Format::RG32_FLOAT;
				case DXGI_FORMAT_R32G32B32_UINT:
					return Format::RGB32_UINT;
				case DXGI_FORMAT_R32G32B32_FLOAT:
					return Format::RGB32_FLOAT;
				case DXGI_FORMAT_R32G32B32A32_UINT:
					return Format::RGBA32_UINT;
				case DXGI_FORMAT_R32G32B32A32_FLOAT:
					return Format::RGBA32_FLOAT;

				case DXGI_FORMAT_D16_UNORM:
					return Format::D16;
				case DXGI_FORMAT_D24_UNORM_S8_UINT:
					return Format::D24S8;
				case DXGI_FORMAT_D32_FLOAT:
					return Format::D32;
				case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
					return Format::D32S8;

				default:
				{
					// SA_LOG(Error)
					return Format::Unknown;
				}
			}
		}

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		VkFormat MapFormatToVK(Format _format)
		{
			switch (_format)
			{
				case Format::Unknown:
					return VK_FORMAT_UNDEFINED;

				case Format::R8_UNORM:
					return VK_FORMAT_R8_UNORM;
				case Format::R8_UINT:
					return VK_FORMAT_R8_UINT;
				case Format::RG8_UNORM:
					return VK_FORMAT_R8G8_UNORM;
				case Format::RG8_UINT:
					return VK_FORMAT_R8G8_UINT;
				case Format::RGBA8_UNORM:
					return VK_FORMAT_R8G8B8A8_UNORM;
				case Format::RGBA8_sRGB:
					return VK_FORMAT_R8G8B8A8_SRGB;
				case Format::RGBA8_UINT:
					return VK_FORMAT_R8G8B8A8_UINT;

				case Format::R16_UNORM:
					return VK_FORMAT_R16_UNORM;
				case Format::R16_UINT:
					return VK_FORMAT_R16_UINT;
				case Format::R16_FLOAT:
					return VK_FORMAT_R16_SFLOAT;
				case Format::RG16_UNORM:
					return VK_FORMAT_R16G16_UNORM;
				case Format::RG16_UINT:
					return VK_FORMAT_R16G16_UINT;
				case Format::RG16_FLOAT:
					return VK_FORMAT_R16G16_SFLOAT;
				case Format::RGBA16_UNORM:
					return VK_FORMAT_R16G16B16A16_UNORM;
				case Format::RGBA16_UINT:
					return VK_FORMAT_R16G16B16A16_UINT;
				case Format::RGBA16_FLOAT:
					return VK_FORMAT_R16G16B16A16_SFLOAT;

				case Format::R32_UINT:
					return VK_FORMAT_R32_UINT;
				case Format::R32_FLOAT:
					return VK_FORMAT_R32_SFLOAT;
				case Format::RG32_UINT:
					return VK_FORMAT_R32G32_UINT;
				case Format::RG32_FLOAT:
					return VK_FORMAT_R32G32_SFLOAT;
				case Format::RGB32_UINT:
					return VK_FORMAT_R32G32B32_UINT;
				case Format::RGB32_FLOAT:
					return VK_FORMAT_R32G32B32_SFLOAT;
				case Format::RGBA32_UINT:
					return VK_FORMAT_R32G32B32A32_UINT;
				case Format::RGBA32_FLOAT:
					return VK_FORMAT_R32G32B32A32_SFLOAT;

				case Format::D16:
					return VK_FORMAT_D16_UNORM;
				case Format::D24S8:
					return VK_FORMAT_D24_UNORM_S8_UINT;
				case Format::D32:
					return VK_FORMAT_D32_SFLOAT;
				case Format::D32S8:
					return VK_FORMAT_D32_SFLOAT_S8_UINT;

				default:
				{
					// SA_LOG(Error)
					return VK_FORMAT_UNDEFINED;
				}
			}
		}

		Format MapFormatFromVK(VkFormat _format)
		{
			switch (_format)
			{
				case VK_FORMAT_UNDEFINED:
					return Format::Unknown;

				case VK_FORMAT_R8_UNORM:
					return Format::R8_UNORM;
				case VK_FORMAT_R8_UINT:
					return Format::R8_UINT;
				case VK_FORMAT_R8G8_UNORM:
					return Format::RG8_UNORM;
				case VK_FORMAT_R8G8_UINT:
					return Format::RG8_UINT;
				case VK_FORMAT_R8G8B8A8_UNORM:
					return Format::RGBA8_UNORM;
				case VK_FORMAT_R8G8B8A8_SRGB:
					return Format::RGBA8_sRGB;
				case VK_FORMAT_R8G8B8A8_UINT:
					return Format::RGBA8_UINT;

				case VK_FORMAT_R16_UNORM:
					return Format::R16_UNORM;
				case VK_FORMAT_R16_UINT:
					return Format::R16_UINT;
				case VK_FORMAT_R16_SFLOAT:
					return Format::R16_FLOAT;
				case VK_FORMAT_R16G16_UNORM:
					return Format::RG16_UNORM;
				case VK_FORMAT_R16G16_UINT:
					return Format::RG16_UINT;
				case VK_FORMAT_R16G16_SFLOAT:
					return Format::RG16_FLOAT;
				case VK_FORMAT_R16G16B16A16_UNORM:
					return Format::RGBA16_UNORM;
				case VK_FORMAT_R16G16B16A16_UINT:
					return Format::RGBA16_UINT;
				case VK_FORMAT_R16G16B16A16_SFLOAT:
					return Format::RGBA16_FLOAT;

				case VK_FORMAT_R32_UINT:
					return Format::R32_UINT;
				case VK_FORMAT_R32_SFLOAT:
					return Format::R32_FLOAT;
				case VK_FORMAT_R32G32_UINT:
					return Format::RG32_UINT;
				case VK_FORMAT_R32G32_SFLOAT:
					return Format::RG32_FLOAT;
				case VK_FORMAT_R32G32B32_UINT:
					return Format::RGB32_UINT;
				case VK_FORMAT_R32G32B32_SFLOAT:
					return Format::RGB32_FLOAT;
				case VK_FORMAT_R32G32B32A32_UINT:
					return Format::RGBA32_UINT;
				case VK_FORMAT_R32G32B32A32_SFLOAT:
					return Format::RGBA32_FLOAT;

				case VK_FORMAT_D16_UNORM:
					return Format::D16;
				case VK_FORMAT_D24_UNORM_S8_UINT:
					return Format::D24S8;
				case VK_FORMAT_D32_SFLOAT:
					return Format::D32;
				case VK_FORMAT_D32_SFLOAT_S8_UINT:
					return Format::D32S8;

				default:
				{
					// SA_LOG(Error)
					return Format::Unknown;
				}
			}
		}

#endif // EDO_RHI_VK
	}

#endif // EDO_RHI_IMPLEMENTATION

// ##############################################################

// ##############################################################
// #					DEVICE									#
// ##############################################################

	class Device
	{
#if EDO_RHI_DX12

	private:
		/// Physical Device
		MComPtr<IDXGIAdapter3> mAdapter = nullptr;

		/// Logical Device
		MComPtr<ID3D12Device> mHandle = nullptr;

	#if EDO_DEBUG
		DWORD mVLayerCallbackCookie = 0;
	#endif

	public:
		ID3D12Device* operator->() const { return mHandle.Get(); }

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

	private:
		VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;

		/// Logical Device
		VkDevice mHandle = VK_NULL_HANDLE;

	public:
		VkDevice Get() const { return mHandle; }

#endif // EDO_RHI_VK

	private:
	public:
		void Create();
		void Destroy();

		Pipeline CreatePipeline(const GfxPipelineDesc& _desc);
		Pipeline CreatePipeline(const CompPipelineDesc& _desc);
		void DestroyPipeline(Pipeline& _pip);

		Buffer CreateBuffer(const BufferDesc& _desc);
		void DestroyBuffer(Buffer& _buff);

		Texture CreateTexture(const TextureDesc& _desc);
		void DestroyTexture(Texture& _tex);
	};

#if EDO_RHI_IMPLEMENTATION
	
	void Device::Create()
	{
#if EDO_RHI_DX12
		//SA_ERROR(!mAdapter, "Try create non-null device");
		//SA_ERROR(!mHandle, "Try create non-null device");

		const HRESULT hrQueryGPU = factory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&mAdapter));
		if (FAILED(hrQueryGPU))
		{
			//SA_LOG(L"Adapter not found!", Error, DX12, (L"Error Code: %1", hrQueryGPU));
			return EXIT_FAILURE;
		}

		const HRESULT hrDeviceCreated = D3D12CreateDevice(mAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mHandle));
		if (FAILED(hrDeviceCreated))
		{
			//SA_LOG(L"Create Device failed!", Error, DX12, (L"Error Code: %1", hrDeviceCreated));
			return EXIT_FAILURE;
		}
		else
		{
			const LPCWSTR name = L"Edo Main Device";
			mHandle->SetName(name);

			//SA_LOG(L"Create Device success.", Info, DX12, (L"\"%1\" [%2]", name, device.Get()));
		}

	#if EDO_DEBUG
		// Validation Layers
		{
			MComPtr<ID3D12InfoQueue1> infoQueue = nullptr;

			const HRESULT hrQueryInfoQueue = mHandle->QueryInterface(IID_PPV_ARGS(&infoQueue));
			if (SUCCEEDED(hrQueryInfoQueue))
			{
				infoQueue->RegisterMessageCallback(ValidationLayersDebugCallback,
					D3D12_MESSAGE_CALLBACK_IGNORE_FILTERS, nullptr, &mVLayerCallbackCookie);

				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
			}
			else
			{
				//SA_LOG(L"Device query info queue to enable validation layers failed.", Error, DX12, (L"Error Code: %1", hrQueryInfoQueue));
			}
		}
	#endif

#endif // EDO_RHI_DX12
	}

	void Device::Destroy()
	{
#if EDO_RHI_DX12

	#if EDO_DEBUG
		if (mVLayerCallbackCookie)
		{
			MComPtr<ID3D12InfoQueue1> infoQueue = nullptr;

			const HRESULT hrQueryInfoQueue = mHandle->QueryInterface(IID_PPV_ARGS(&infoQueue));
			if (SUCCEEDED(hrQueryInfoQueue))
			{
				infoQueue->UnregisterMessageCallback(mVLayerCallbackCookie);
				mVLayerCallbackCookie = 0;
			}
		}
	#endif

		//SA_WARN(mHandle, "Try destroy null device");
		//SA_WARN(mAdapter, "Try destroy null device");

		//SA_LOG(L"Destroying Device...", Info, Edo.RHI.DX12, mDevice.Get());
		mHandle = nullptr;
		mAdapter = nullptr;

#endif // EDO_RHI_DX12
	}


	Pipeline Device::CreatePipeline(const GfxPipelineDesc& _desc)
	{
		Pipeline pip;

		pip.Create(*this, _desc);

		return pip;
	}

	Pipeline Device::CreatePipeline(const CompPipelineDesc& _desc)
	{
		Pipeline pip;

		pip.Create(*this, _desc);

		return pip;
	}

	void Device::DestroyPipeline(Pipeline& _pip)
	{
		_pip.Destroy(*this);
	}


	Buffer Device::CreateBuffer(const BufferDesc& _desc)
	{
		Buffer buff;

		buff.Create(*this, _desc);

		return buff;
	}

	void Device::DestroyBuffer(Buffer& _buff)
	{
		_buff.Destroy(*this);
	}


	Texture Device::CreateTexture(const TextureDesc& _desc)
	{
		Texture tex;

		tex.Create(*this, _desc);

		return tex;
	}

	void Device::DestroyTexture(Texture& _tex)
	{
		_tex.Destroy(*this);
	}

#endif // EDO_RHI_IMPLEMENTATION

// ##############################################################


// ##############################################################
// #					SWAPCHAIN								#
// ##############################################################

	class Swapchain
	{
#if EDO_RHI_DX12

		MComPtr<IDXGISwapChain3> mSwapchain = nullptr;

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		VkSwapchainKHR mSwapchain = VK_NULL_HANDLE;

#endif // EDO_RHI_VK

	public:
		void Create();
		void Destroy();
	};

// ##############################################################


// ##############################################################
// #					SHADER									#
// ##############################################################

	class Shader
	{
#if EDO_RHI_DX12

		MComPtr<ID3DBlob> mShader = nullptr;

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		VkShaderModule mShader = VK_NULL_HANDLE;

#endif // EDO_RHI_VK
	};

// ##############################################################


// ##############################################################
// #					PIPELINE								#
// ##############################################################

	enum class PolygonMode : uint8_t
	{
		// Draw fill triangle.
		Fill,

		// Draw line only.
		Line,

		// Draw point only.
		Point,
	};

	enum class CullingMode : uint8_t
	{
		// No culling.
		None,

		// Front-face culling.
		Front,

		// Back-face culling.
		Back,
	};

	enum class FrontFaceMode : uint8_t
	{
		// Clockwise polygon are front-face.
		Clockwise,

		// Counter clockwise polygon are front-face.
		CounterClockwise,
	};

	enum class DepthTestingMethod
	{
		Default = 0,

		Inverse = 1,
	};


	struct GfxPipShaderStageDesc
	{
		/// Vertex Shader.
		Shader* vs = nullptr;

		/// Geometry Shader.
		Shader* gs = nullptr;

		/// Pixel Shader.
		Shader* ps = nullptr;
	};

	struct GfxPipRasterizationDesc
	{
		/// Whether to use conservative rasterization.
		bool bConservative = false;

		/// Polygon mode.
		PolygonMode polygon = PolygonMode::Fill;

		/// Culling mode.
		CullingMode cullingMode = CullingMode::Back;

		/// Rasterization front face mode.
		FrontFaceMode frontFace = FrontFaceMode::Clockwise;
	};

	struct GfxPipDepthStencilDesc
	{
		/// Enable depth testing.
		bool bDepthTest = true;

		/// Enable write into depth buffer.
		bool bDepthWrite = true;

		/// Enable stencil testing.
		bool bStencilTest = false;

		DepthTestingMethod method = DepthTestingMethod::Default;
	};

	struct GfxPipelineDesc
	{
		GfxPipShaderStageDesc shaders{};

		GfxPipRasterizationDesc raster{};

		GfxPipDepthStencilDesc depthStencil{};
	};


	struct CompPipelineDesc
	{
	};


	class Pipeline
	{
#if EDO_RHI_DX12

		MComPtr<ID3D12PipelineState> mHandle = nullptr;

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		VkPipeline mHandle = VK_NULL_HANDLE;

#endif // EDO_RHI_VK

	private:
	public:
		void Create(const Device& _device, const GfxPipelineDesc& _desc);
		void Create(const Device& _device, const CompPipelineDesc& _desc);
		void Destroy(const Device& _device);
	};

#if EDO_RHI_IMPLEMENTATION

	namespace intl
	{
#if EDO_RHI_DX12

		D3D12_FILL_MODE MapPolygonModeToDX(PolygonMode _mode)
		{
			switch (_mode)
			{
				case PolygonMode::Fill:
					return D3D12_FILL_MODE_SOLID;
				case PolygonMode::Line:
				case PolygonMode::Point:
					return D3D12_FILL_MODE_WIREFRAME;
				default:
				{
					// SA_LOG(Error)
					return D3D12_FILL_MODE_SOLID;
				}
			}
		}

		D3D12_CULL_MODE MapCullingModeToDX(CullingMode _mode)
		{
			switch (_mode)
			{
				case CullingMode::None:
					return D3D12_CULL_MODE_NONE;
				case CullingMode::Front:
					return D3D12_CULL_MODE_FRONT;
				case CullingMode::Back:
					return D3D12_CULL_MODE_BACK;
				default:
				{
					// SA_LOG(Error)
					return D3D12_CULL_MODE_NONE;
				}
			}
		}

		BOOL MapFrontFaceModeToDX(FrontFaceMode _mode)
		{
			switch (_mode)
			{
				case FrontFaceMode::Clockwise:
					return TRUE;
				case FrontFaceMode::CounterClockwise:
					return FALSE;
				default:
				{
					// SA_LOG()
					return TRUE;
				}
			}
		}

#endif // EDO_RHI_DX12
	}

	void Pipeline::Create(const Device& _device, const GfxPipelineDesc& _desc)
	{
#if EDO_RHI_DX12

		// PipelineState
		{
			const D3D12_RENDER_TARGET_BLEND_DESC rtBlend{
				.BlendEnable = false,
				.LogicOpEnable = false,

				.SrcBlend = D3D12_BLEND_ONE,
				.DestBlend = D3D12_BLEND_ZERO,
				.BlendOp = D3D12_BLEND_OP_ADD,

				.SrcBlendAlpha = D3D12_BLEND_ONE,
				.DestBlendAlpha = D3D12_BLEND_ZERO,
				.BlendOpAlpha = D3D12_BLEND_OP_ADD,

				.LogicOp = D3D12_LOGIC_OP_NOOP,

				.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL,
			};

			const D3D12_BLEND_DESC blendState{
				.AlphaToCoverageEnable = false,
				.IndependentBlendEnable = false,

				.RenderTarget
				{
					rtBlend,
					rtBlend,
					rtBlend,
					rtBlend,
					rtBlend,
					rtBlend,
					rtBlend,
					rtBlend
				}
			};

			const D3D12_RASTERIZER_DESC raster{
				.FillMode = intl::MapPolygonModeToDX(_desc.raster.polygon),
				.CullMode = intl::MapCullingModeToDX(_desc.raster.cullingMode),
				.FrontCounterClockwise = intl::MapFrontFaceModeToDX(_desc.raster.frontFace),
				.DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
				.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
				.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
				.DepthClipEnable = TRUE,
				.MultisampleEnable = FALSE,
				.AntialiasedLineEnable = FALSE,
				.ForcedSampleCount = 0,
				.ConservativeRaster = _desc.raster.bConservative ? D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON : D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF,
			};

			const D3D12_DEPTH_STENCIL_DESC depthStencilState{
				.DepthEnable = _desc.depthStencil.bDepthTest ? TRUE : FALSE,
				.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
				.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL,
				.StencilEnable = _desc.depthStencil.bStencilTest ? TRUE : FALSE,
				.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK,
				.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK,
				.FrontFace
				{
					.StencilFailOp = D3D12_STENCIL_OP_KEEP,
					.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
					.StencilPassOp = D3D12_STENCIL_OP_KEEP,
					.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS,
				},
				.BackFace
				{
					.StencilFailOp = D3D12_STENCIL_OP_KEEP,
					.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
					.StencilPassOp = D3D12_STENCIL_OP_KEEP,
					.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS,
				}
			};

			D3D12_INPUT_ELEMENT_DESC inputElems[]{
				//{
				//	.SemanticName = "POSITION",
				//	.SemanticIndex = 0,
				//	.Format = DXGI_FORMAT_R32G32B32_FLOAT,
				//		.InputSlot = 0,
				//		.AlignedByteOffset = 0,
				//		.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				//		.InstanceDataStepRate = 0
				//},
				//{
				//	.SemanticName = "NORMAL",
				//	.SemanticIndex = 0,
				//	.Format = DXGI_FORMAT_R32G32B32_FLOAT,
				//	.InputSlot = 1,
				//	.AlignedByteOffset = 0,
				//	.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				//	.InstanceDataStepRate = 0
				//},
				//{
				//	.SemanticName = "TANGENT",
				//	.SemanticIndex = 0,
				//	.Format = DXGI_FORMAT_R32G32B32_FLOAT,
				//	.InputSlot = 2,
				//	.AlignedByteOffset = 0,
				//	.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				//	.InstanceDataStepRate = 0
				//},
				//{
				//	.SemanticName = "TEXCOORD",
				//	.SemanticIndex = 0,
				//	.Format = DXGI_FORMAT_R32G32_FLOAT,
				//	.InputSlot = 3,
				//	.AlignedByteOffset = 0,
				//	.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				//	.InstanceDataStepRate = 0
				//}
			};
			const D3D12_INPUT_LAYOUT_DESC inputLayout{
				.pInputElementDescs = inputElems,
				.NumElements = _countof(inputElems)
			};


			const D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{
				.pRootSignature = litRootSign.Get(),

				.VS{
					.pShaderBytecode = litVertexShader->GetBufferPointer(),
					.BytecodeLength = litVertexShader->GetBufferSize()
				},
				.PS{
					.pShaderBytecode = litPixelShader->GetBufferPointer(),
					.BytecodeLength = litPixelShader->GetBufferSize()
				},

				.StreamOutput = {},
				.BlendState = blendState,
				.SampleMask = UINT_MAX,

				.RasterizerState = raster,
				.InputLayout = inputLayout,

				.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,

				.NumRenderTargets = 1,
				.RTVFormats{
					sceneColorFormat
				},
				.DSVFormat = sceneDepthFormat,

				.SampleDesc
				{
					.Count = 1,
					.Quality = 0,
				},

				.NodeMask = 0,

				.CachedPSO
				{
					.pCachedBlob = nullptr,
					.CachedBlobSizeInBytes = 0,
				},

				.Flags = D3D12_PIPELINE_STATE_FLAG_NONE,
			};

			const HRESULT hrCreatePipeline = _device->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&mHandle));
			if (FAILED(hrCreatePipeline))
			{
				//SA_LOG(L"Create Lit PipelineState failed!", Error, DX12, (L"Error Code: %1", hrCreatePipeline));
				return EXIT_FAILURE;
			}
			
			//SA_LOG(L"Create Lit PipelineState success.", Info, DX12, litPipelineState.Get());
		}

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		// Pipeline
		{
			const std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages{
				VkPipelineShaderStageCreateInfo{
					.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.stage = VK_SHADER_STAGE_VERTEX_BIT,
					.module = litVertexShader,
					.pName = "main",
					.pSpecializationInfo = nullptr,
				},
				VkPipelineShaderStageCreateInfo{
					.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
					.module = litFragmentShader,
					.pName = "main",
					.pSpecializationInfo = nullptr,
				},
			};

			const std::array<VkVertexInputBindingDescription, 4> vertexInputBindings{
				VkVertexInputBindingDescription{ // Position buffer
					.binding = 0,
					.stride = sizeof(SA::Vec3f),
					.inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
				},
				VkVertexInputBindingDescription{ // Normal buffer
					.binding = 1,
					.stride = sizeof(SA::Vec3f),
					.inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
				},
				VkVertexInputBindingDescription{ // Tangent buffer
					.binding = 2,
					.stride = sizeof(SA::Vec3f),
					.inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
				},
				VkVertexInputBindingDescription{ // UV buffer
					.binding = 3,
					.stride = sizeof(SA::Vec2f),
					.inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
				},
			};

			const std::array<VkVertexInputAttributeDescription, 4> vertexInputAttribs{
				VkVertexInputAttributeDescription{ // Position Input
					.location = 0u,
					.binding = 0u,
					.format = VK_FORMAT_R32G32B32_SFLOAT,
					.offset = 0u,
				},
				VkVertexInputAttributeDescription{ // Normal Input
					.location = 1u,
					.binding = 1u,
					.format = VK_FORMAT_R32G32B32_SFLOAT,
					.offset = 0u,
				},
				VkVertexInputAttributeDescription{ // Tangent Input
					.location = 2u,
					.binding = 2u,
					.format = VK_FORMAT_R32G32B32_SFLOAT,
					.offset = 0u,
				},
				VkVertexInputAttributeDescription{ // UV Input
					.location = 3u,
					.binding = 3u,
					.format = VK_FORMAT_R32G32_SFLOAT,
					.offset = 0u,
				},
			};

			const VkPipelineInputAssemblyStateCreateInfo inputAssemblyState{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
				.primitiveRestartEnable = VK_FALSE,
			};

			const VkPipelineVertexInputStateCreateInfo vertexInputInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputBindings.size()),
				.pVertexBindingDescriptions = vertexInputBindings.data(),
				.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttribs.size()),
				.pVertexAttributeDescriptions = vertexInputAttribs.data(),
			};

			const VkPipelineViewportStateCreateInfo viewportInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.viewportCount = 1,
				.pViewports = &viewport,
				.scissorCount = 1,
				.pScissors = &scissorRect,
			};

			const VkPipelineRasterizationStateCreateInfo rasterInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.depthClampEnable = VK_FALSE,
				.rasterizerDiscardEnable = VK_FALSE,
				.polygonMode = VK_POLYGON_MODE_FILL,
				.cullMode = VK_CULL_MODE_BACK_BIT,
				.frontFace = VK_FRONT_FACE_CLOCKWISE,
				.depthBiasEnable = VK_FALSE,
				.depthBiasConstantFactor = 0.0f,
				.depthBiasClamp = 0.0f,
				.depthBiasSlopeFactor = 0.0f,
				.lineWidth = 1.0f,
			};

			const VkPipelineMultisampleStateCreateInfo multisampleInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
				.sampleShadingEnable = VK_FALSE,
				.minSampleShading = 1.0f,
				.pSampleMask = nullptr,
				.alphaToCoverageEnable = VK_FALSE,
				.alphaToOneEnable = VK_FALSE,
			};

			const VkPipelineDepthStencilStateCreateInfo depthStencilState{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.depthTestEnable = VK_TRUE,
				.depthWriteEnable = VK_TRUE,
				.depthCompareOp = VK_COMPARE_OP_LESS,
				.depthBoundsTestEnable = VK_FALSE,
				.stencilTestEnable = VK_FALSE,
				.front = {},
				.back = {},
				.minDepthBounds = 0.0f,
				.maxDepthBounds = 1.0f,
			};

			const std::array<VkPipelineColorBlendAttachmentState, 1> colorBlendAttachs{
				VkPipelineColorBlendAttachmentState{
					.blendEnable = VK_FALSE,
					.srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
					.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
					.colorBlendOp = VK_BLEND_OP_ADD,
					.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
					.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
					.alphaBlendOp = VK_BLEND_OP_ADD,
					.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
										VK_COLOR_COMPONENT_G_BIT |
										VK_COLOR_COMPONENT_B_BIT |
										VK_COLOR_COMPONENT_A_BIT,
				},
			};

			const VkPipelineColorBlendStateCreateInfo colorBlendState{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.logicOpEnable = VK_FALSE,
				.logicOp = VK_LOGIC_OP_COPY,
				.attachmentCount = static_cast<uint32_t>(colorBlendAttachs.size()),
				.pAttachments = colorBlendAttachs.data(),
				.blendConstants = { 0.0f },
			};

			const std::array<VkDynamicState, 2> dynamicStates{
				VK_DYNAMIC_STATE_VIEWPORT,
				VK_DYNAMIC_STATE_SCISSOR
			};

			const VkPipelineDynamicStateCreateInfo dynamicStateInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size()),
				.pDynamicStates = dynamicStates.data(),
			};


			const VkGraphicsPipelineCreateInfo pipelineInfo{
				.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.stageCount = static_cast<uint32_t>(shaderStages.size()),
				.pStages = shaderStages.data(),
				.pVertexInputState = &vertexInputInfo,
				.pInputAssemblyState = &inputAssemblyState,
				.pTessellationState = nullptr,
				.pViewportState = &viewportInfo,
				.pRasterizationState = &rasterInfo,
				.pMultisampleState = &multisampleInfo,
				.pDepthStencilState = &depthStencilState,
				.pColorBlendState = &colorBlendState,
				.pDynamicState = &dynamicStateInfo,
				.layout = litPipelineLayout,
				.renderPass = renderPass,
				.subpass = 0u,
				.basePipelineHandle = VK_NULL_HANDLE,
				.basePipelineIndex = -1,
			};

			const VkResult vrCreatePipeline = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1u, &pipelineInfo, nullptr, &litPipeline);
			if (vrCreatePipeline != VK_SUCCESS)
			{
				SA_LOG(L"Create Lit Pipeline failed!", Error, VK, (L"Error Code: %1", vrCreatePipeline));
				return EXIT_FAILURE;
			}
			else
			{
				SA_LOG(L"Create Lit Pipeline success", Info, VK, litPipeline);
			}
		}

#endif // EDO_RHI_VK
	}

	void Pipeline::Create(const Device& _device, const CompPipelineDesc& _desc)
	{
#if EDO_RHI_DX12

		// Pipeline State
		{
			const D3D12_COMPUTE_PIPELINE_STATE_DESC desc{
			};

			const HRESULT hrCreatePipeline = _device->CreateComputePipelineState(&desc, IID_PPV_ARGS(&mHandle));
			if (FAILED(hrCreatePipeline))
			{
				//SA_LOG(L"Create Lit PipelineState failed!", Error, DX12, (L"Error Code: %1", hrCreatePipeline));
				return EXIT_FAILURE;
			}

			//SA_LOG(L"Create Lit PipelineState success.", Info, DX12, mHandle.Get());
		}

#endif // EDO_RHI_DX12

#if EDO_RHI_VK
#endif // EDO_RHI_VK
	}

	void Pipeline::Destroy(const Device& _device)
	{
#if EDO_RHI_DX12

		//SA_WARN(mHandle, "Try destroy null pipeline");

		// PipelineState
		{
			//SA_LOG(L"Destroying Lit PipelineState...", Info, DX12, mHandle.Get());

			mHandle = nullptr;
		}

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		//SA_WARN(mHandle, "Try destroy null pipeline");

		// Pipeline
		if (mHandle != VK_NULL_HANDLE)
		{
			vkDestroyPipeline(device, mHandle, nullptr);

			SA_LOG(L"Destroy Lit Pipeline success.", Info, VK, mHandle);

			mHandle = VK_NULL_HANDLE;
		}

#endif // EDO_RHI_VK
	}

#endif // EDO_RHI_IMPLEMENTATION

// ##############################################################


// ##############################################################
// #					BUFFER									#
// ##############################################################

	enum class BufferType
	{
		GPU,

		Upload,

		Readbak,
	};

	struct BufferDesc
	{
		/// Size in bytes.
		uint64_t size = 0;

		BufferType type = BufferType::GPU;

		std::wstring name = L"unknown buffer";
	};

	class Buffer
	{
#if EDO_RHI_DX12

	private:
		MComPtr<ID3D12Resource> mHandle = nullptr;

	public:

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

	private:
		VkBuffer mHandle = VK_NULL_HANDLE;
		VkDeviceMemory mMemory = VK_NULL_HANDLE;

	public:

#endif // EDO_RHI_VK

	private:
	public:
		void Create(const Device& _device, const BufferDesc& _desc);
		void Destroy(const Device& _device);
	};

#if EDO_RHI_IMPLEMENTATION

	namespace intl
	{
#if EDO_RHI_DX12
		D3D12_HEAP_TYPE MapBufferTypeToDX(BufferType _type)
		{
			switch (_type)
			{
				case BufferType::GPU:
					return D3D12_HEAP_TYPE_DEFAULT;
				case BufferType::Upload:
					return D3D12_HEAP_TYPE_UPLOAD;
				case BufferType::Readbak:
					return D3D12_HEAP_TYPE_READBACK;
				default:
				{
					// SA_LOG(Error);
					return D3D12_HEAP_TYPE_DEFAULT;
				}
			}
		}
#endif
	}

	void Buffer::Create(const Device& _device, const BufferDesc& _desc)
	{
#if EDO_RHI_DX12

		//SA_ERROR(!mHandle, "Try create non-null Buffer");

		const D3D12_HEAP_PROPERTIES heap{
			.Type = intl::MapBufferTypeToDX(_desc.type),
		};

		const D3D12_RESOURCE_DESC desc{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = 0,
			.Width = _desc.size,
			.Height = 1,
			.DepthOrArraySize = 1,
			.MipLevels = 1,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = {.Count = 1, .Quality = 0 },
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
		};

		const HRESULT hrBufferCreated = _device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&mHandle));
		if (FAILED(hrBufferCreated))
		{
			//SA_LOG(L"Create PointLights Buffer failed!", Error, DX12, (L"Error code: %1", hrBufferCreated));
			return EXIT_FAILURE;
		}

		mHandle->SetName(_desc.name.c_str());

		//SA_LOG(L"Create PointLights Buffer success", Info, DX12, (L"\"%1\" [%2]", name, pointLightBuffer.Get()));

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		//SA_ERROR(!mHandle, "Try create non-null Buffer");
		//SA_ERROR(!mMemory, "Try create non-null Buffer");

		// Buffer
		{
			const VkBufferCreateInfo bufferInfo{
				.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.size = _desc.size,
				.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT,
				.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
				.queueFamilyIndexCount = 0u,
				.pQueueFamilyIndices = nullptr,
			};

			const VkResult vrBufferCreated = vkCreateBuffer(_device.Get(), &bufferInfo, nullptr, &mHandle);
			if (vrBufferCreated != VK_SUCCESS)
			{
				//SA_LOG(L"Create PointLights Buffer failed!", Error, VK, (L"Error code: %1", vrBufferCreated));
				return EXIT_FAILURE;
			}

			//SA_LOG(L"Create PointLights Buffer success", Info, VK, pointLightBuffer);
		}

		// Memory
		{
			VkMemoryRequirements memRequirements;
			//vkGetBufferMemoryRequirements(device, pointLightBuffer, &memRequirements);

			const VkMemoryAllocateInfo allocInfo{
				.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
				.pNext = nullptr,
				.allocationSize = memRequirements.size,
				//.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
			};

			const VkResult vrBufferAlloc = vkAllocateMemory(_device.Get(), &allocInfo, nullptr, &mMemory);
			if (vrBufferAlloc != VK_SUCCESS)
			{
				//SA_LOG(L"Create PointLights Buffer Memory failed!", Error, VK, (L"Error code: %1", vrBufferAlloc));
				return EXIT_FAILURE;
			}

			//SA_LOG(L"Create PointLights Buffer Memory success", Info, VK, pointLightBufferMemory);
		}

		// Bind
		{
			const VkResult vrBindBufferMem = vkBindBufferMemory(_device.Get(), mHandle, mMemory, 0);
			if (vrBindBufferMem != VK_SUCCESS)
			{
				//SA_LOG(L"Bind PointLights Buffer Memory failed!", Error, VK, (L"Error code: %1", vrBindBufferMem));
				return EXIT_FAILURE;
			}

			//SA_LOG(L"Bind PointLights Buffer Memory success", Info, VK);
		}

#endif // EDO_RHI_VK
	}

	void Buffer::Destroy(const Device& _device)
	{
#if EDO_RHI_DX12

		(void)_device;

		// SA_WARN(mHandle, "try destroy null Buffer);

		//SA_LOG(L"Destroying Buffer...", Info, DX12, mHandle.Get());
		mHandle = nullptr;

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		// SA_WARN(mHandle, "try destroy null Buffer);
		// SA_WARN(mMemory, "try destroy null Buffer);

		// Buffer
		if (mHandle != VK_NULL_HANDLE)
		{
			vkDestroyBuffer(_device.Get(), mHandle, nullptr);

			//SA_LOG(L"Destroy Buffer success.", Info, VK, mHandle);

			mHandle = VK_NULL_HANDLE;
		}

		// Memory
		if(mMemory != VK_NULL_HANDLE)
		{
			vkFreeMemory(_device.Get(), mMemory, nullptr);

			//SA_LOG(L"Destroy Buffer Memory success.", Info, VK, mMemory);

			mMemory = VK_NULL_HANDLE;
		}

#endif // EDO_RHI_VK
	}

#endif // EDO_RHI_IMPLEMENTATION

// ##############################################################


// ##############################################################
// #					TEXTURE									#
// ##############################################################

	struct TextureDesc
	{
		uint32_t width = 0u;
		uint32_t height = 0u;
		
		uint16_t mipLevels = 1u;

		Format format = Format::Unknown;

		std::wstring name = L"unknown texture";
	};

	class Texture
	{
#if EDO_RHI_DX12

	private:
		MComPtr<ID3D12Resource> mHandle = nullptr;

	public:

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

	private:
		VkImage mHandle = VK_NULL_HANDLE;
		VkDeviceMemory mMemory = VK_NULL_HANDLE;

	public:

#endif // EDO_RHI_VK

	private:
	public:
		void Create(const Device& _device, const TextureDesc& _desc);
		void Destroy(const Device& _device);
	};

#if EDO_RHI_IMPLEMENTATION

	void Texture::Create(const Device& _device, const TextureDesc& _desc)
	{
#if EDO_RHI_DX12

		//SA_ERROR(!mHandle, "Try create non-null Texture");

		const D3D12_HEAP_PROPERTIES heap{
			.Type = D3D12_HEAP_TYPE_DEFAULT,
		};

		const D3D12_RESOURCE_DESC desc{
			.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			.Alignment = 0,
			.Width = _desc.width,
			.Height = _desc.height,
			.DepthOrArraySize = 1,
			.MipLevels = _desc.mipLevels,
			.Format = intl::MapFormatToDX(_desc.format),
			.SampleDesc = {.Count = 1, .Quality = 0 },
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = D3D12_RESOURCE_FLAG_NONE,
		};

		const HRESULT hrBufferCreated = _device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&mHandle));
		if (FAILED(hrBufferCreated))
		{
			//SA_LOG(L"Create RustedIron2 Albedo Texture failed!", Error, DX12, (L"Error code: %1", hrBufferCreated));
			return EXIT_FAILURE;
		}

		mHandle->SetName(_desc.name.c_str());

		//SA_LOG(L"Create Texture success.", Info, DX12, (L"\"%1\" [%2]", name, mHandle.Get()));

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		//SA_ERROR(!mHandle, "Try create non-null Texture");
		//SA_ERROR(!mMemory, "Try create non-null Texture");

		// Image
		{
			const VkImageCreateInfo imageInfo{
				.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.imageType = VK_IMAGE_TYPE_2D,
				.format = intl::MapFormatToVK(_desc.format),
				.extent{
					.width = _desc.width,
					.height = _desc.height,
					.depth = 1u,
				},
				.mipLevels = _desc.mipLevels,
				.arrayLayers = 1u,
				.samples = VK_SAMPLE_COUNT_1_BIT,
				.tiling = VK_IMAGE_TILING_OPTIMAL,
				.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
				.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
				.queueFamilyIndexCount = 0u,
				.pQueueFamilyIndices = nullptr,
				.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			};

			const VkResult vrImageCreated = vkCreateImage(_device.Get(), &imageInfo, nullptr, &mHandle);
			if (vrImageCreated != VK_SUCCESS)
			{
				//SA_LOG(L"Create RustedIron2 Albedo Texture failed!", Error, VK, (L"Error code: %1", vrImageCreated));
				return EXIT_FAILURE;
			}
				
			//SA_LOG(L"Create RustedIron2 Albedo Texture success", Info, VK, rustedIron2AlbedoImage);
		}

		// ImageMemory
		{
			VkMemoryRequirements memRequirements;
			//vkGetImageMemoryRequirements(device, rustedIron2AlbedoImage, &memRequirements);

			const VkMemoryAllocateInfo allocInfo{
				.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
				.pNext = nullptr,
				.allocationSize = memRequirements.size,
				//.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
			};

			const VkResult vrImageAlloc = vkAllocateMemory(_device.Get(), &allocInfo, nullptr, &mMemory);
			if (vrImageAlloc != VK_SUCCESS)
			{
				//SA_LOG(L"Create RustedIron2 Albedo Texture Alloc failed!", Error, VK, (L"Error code: %1", vrImageAlloc));
				return EXIT_FAILURE;
			}
				
			//SA_LOG(L"Create RustedIron2 Albedo Texture Alloc success", Info, VK, rustedIron2AlbedoImageMemory);
		}

		// Bind
		{
			const VkResult vrImageBindMem = vkBindImageMemory(_device.Get(), mHandle, mMemory), 0);
			if (vrImageBindMem != VK_SUCCESS)
			{
				//SA_LOG(L"Create RustedIron2 Albedo Texture Memory bind failed!", Error, VK, (L"Error code: %1", vrImageBindMem));
				return EXIT_FAILURE;
			}
				
			//SA_LOG(L"Create RustedIron2 Albedo Texture Memory bind success", Info, VK);
		}

#endif // EDO_RHI_VK
	}

	void Texture::Destroy(const Device& _device)
	{
#if EDO_RHI_DX12

		(void)_device;

		// SA_WARN(mHandle, "try destroy null Buffer);

		//SA_LOG(L"Destroying Texture...", Info, DX12, mHandle.Get());
		
		mHandle = nullptr;

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		// SA_WARN(mHandle, "try destroy null Buffer);
		// SA_WARN(mMemory, "try destroy null Buffer);

		// Image
		if(mHandle != VK_NULL_HANDLE)
		{
			vkDestroyImage(_device.Get(), mHandle, nullptr);

			//SA_LOG(L"Destroy RustedIron2 Roughness Image success.", Info, VK, mHandle);

			mHandle = VK_NULL_HANDLE;
		}

		// Memory
		if(mMemory != VK_NULL_HANDLE)
		{
			vkFreeMemory(_device.Get(), mMemory, nullptr);

			//SA_LOG(L"Destroy RustedIron2 Roughness Image Memory success.", Info, VK, mMemory);

			mMemory = VK_NULL_HANDLE;
		}

#endif // EDO_RHI_VK
	}

#endif // EDO_RHI_IMPLEMENTATION

// ##############################################################
}

#endif // EDO_SH_RHI_GUARD
