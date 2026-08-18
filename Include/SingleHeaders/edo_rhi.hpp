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

	struct PipelineDesc;
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

		Buffer CreateBuffer(const BufferDesc& _desc);
		void DestroyBuffer(Buffer& _buff);

		Texture CreateTexture(const TextureDesc& _desc);
		void DestroyTexture(Texture& _tex);
	};

#if EDO_RHI_IMPLEMENTATION
	
	void Device::Create()
	{
#if EDO_RHI_DX12
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

			const HRESULT hrQueryInfoQueue = mDevice->QueryInterface(IID_PPV_ARGS(&infoQueue));
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

		//SA_LOG(L"Destroying Device...", Info, Edo.RHI.DX12, mDevice.Get());
		mHandle = nullptr;
		mAdapter = nullptr;
#endif // EDO_RHI_DX12
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

	struct PipelineDesc
	{
	};

	class Pipeline
	{
#if EDO_RHI_DX12

		MComPtr<ID3D12PipelineState> mPipelineState = nullptr;

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		VkPipeline mPipeline = VK_NULL_HANDLE;

#endif // EDO_RHI_VK
	};

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

		//SA_LOG(L"Destroying Buffer...", Info, DX12, mHandle.Get());
		mHandle = nullptr;

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		// Buffer
		{
			vkDestroyBuffer(_device.Get(), mHandle, nullptr);

			//SA_LOG(L"Destroy Buffer success.", Info, VK, mHandle);

			mHandle = VK_NULL_HANDLE;
		}

		// Memory
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

		//SA_LOG(L"Destroying Texture...", Info, DX12, mHandle.Get());
		
		mHandle = nullptr;

#endif // EDO_RHI_DX12

#if EDO_RHI_VK

		// Image
		{
			vkDestroyImage(_device.Get(), mHandle, nullptr);

			//SA_LOG(L"Destroy RustedIron2 Roughness Image success.", Info, VK, mHandle);

			mHandle = VK_NULL_HANDLE;
		}

		// Memory
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
