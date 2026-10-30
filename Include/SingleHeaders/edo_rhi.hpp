// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_SH_RHI_GUARD
#define EDO_SH_RHI_GUARD

#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include <type_traits>

// Edo Debug Module
#if __has_include(<edo_debug.hpp>)
	#include <edo_debug.hpp>
#else
	#if !defined(NDEBUG) || defined(_DEBUG)
		/// Edo Debug preprocessor.
		#define EDO_CONFIG_DEBUG 1
	#else
		#define EDO_CONFIG_DEBUG 0
	#endif

	#define EDO_LOG(...) {}
	#define EDO_WARN(...) {}
	#define EDO_ERROR(...) {}
	#define EDO_ASSERT(...) {}
	#define EDO_THROW(...) {}
#endif

/**
*	Graphics API Selector.
*	User-defined preprocessor to select API.
*	Define API per-platform by default.
*/
#if !defined(EDO_RHI_DX12) && !defined(EDO_RHI_VK) && !defined(EDO_RHI_GL) && !defined(EDO_RHI_CPU)
	#if WIN32
		#define EDO_RHI_DX12 1
	#else
		#define EDO_RHI_VK 1
	#endif
#endif

#if EDO_RHI_DX12

#include <d3d12.h>		// `d3d12.lib`
#include <DXGIDebug.h>	// `dxguid.lib`
#include <dxgi1_6.h>	// `dxgi.lib`
#include <dxcapi.h>		// `dxcompiler.lib`

#define EDO_DX12_ASSERT(_hres, _msg)\
	EDO_ASSERT(SUCCEEDED(_hres), Edo.RHI.DX12, (edo::StringFormat(_msg) + edo::StringFormat(L"\tError Code: %1", _hres)));

#include <wrl.h>

namespace edo::rhi
{
	template <typename T>
	using MComPtr = Microsoft::WRL::ComPtr<T>;
}

#if !defined(EDO_RHI_GLFW)
	#if __has_include(<GLFW/glfw3.h>) && __has_include(<GLFW/glfw3native.h>)
		#define EDO_RHI_GLFW 1

		#if (defined(_glfw3_h_) || defined(_glfw3_native_h_)) && !defined(GLFW_EXPOSE_NATIVE_WIN32)
			#error "<edo_rhi.hpp> must be included after `glfw3.h` and `glfw3native.h` with `GLFW_EXPOSE_NATIVE_WIN32` defined. You can either:\
			1. Change the include order.\
			2. Remove the glfw includes and let <edo_rhi.hpp> handling them.\
			3. Force define `EDO_RHI_GLFW` to `1` before including <edo_rhi.hpp> to force-enable GLFW implementation without the internal includes.\
			4. Force define `EDO_RHI_GLFW` to `0` before including <edo_rhi.hpp> to force-disable the use of GLFW in <edo_rhi.hpp>"
		#endif

		#define GLFW_EXPOSE_NATIVE_WIN32
		#include <GLFW/glfw3.h>
		#include <GLFW/glfw3native.h>
	#else
		#define EDO_RHI_GLFW 0
	#endif
#endif // GLFW

#endif

#if EDO_RHI_VK

#include <vulkan/vulkan.h>

#define EDO_VK_ASSERT(_vres, _msg)\
	EDO_ASSERT(_vres == VK_SUCCESS, Edo.RHI.VK, (edo::StringFormat(_msg) + edo::StringFormat(L"\tError Code: %1", _vres)));

#if !defined(EDO_RHI_GLFW)
	#if __has_include(<GLFW/glfw3.h>) && __has_include(<GLFW/glfw3native.h>)
		#define EDO_RHI_GLFW 1

		#if defined(_glfw3_h_) && !defined(GLFW_INCLUDE_VULKAN)
			#error "<edo_rhi.hpp> must be included after `glfw3.h` with `GLFW_INCLUDE_VULKAN` defined. You can either:\
			1. Change the include order.\
			2. Remove the glfw includes and let <edo_rhi.hpp> handling them.\
			3. Force define `EDO_RHI_GLFW` to `1` before including <edo_rhi.hpp> to force-enable GLFW implementation without the internal includes.\
			4. Force define `EDO_RHI_GLFW` to `0` before including <edo_rhi.hpp> to force-disable the use of GLFW in <edo_rhi.hpp>"
		#endif

		#define GLFW_INCLUDE_VULKAN 1
		#include <GLFW/glfw3.h>
	#else
		#define EDO_RHI_GLFW 0
	#endif
#endif // GLFW

#endif

#if !defined(EDO_RHI_SFML)
	#if __has_include(<SFML/Window.hpp>)
		#define EDO_RHI_SFML 1
		#include <SFML/Window.hpp>
	#else
		#define EDO_RHI_SFML 0
	#endif
#endif // SFML

#if !defined(EDO_RHI_SDL3)
	#if __has_include(<SDL3/SDL.h>)
		#define EDO_RHI_SDL3 1
		#include <SDL3/SDL.h>
	#else
		#define EDO_RHI_SDL3 0
	#endif
#endif // SDL

namespace edo::rhi
{
// ##############################################################
// #						TYPES								#
// ##############################################################

	class Device;
	class Queue;

	class Swapchain;

	class CommandList;

	class Shader;

	struct GfxPipelineDesc;
	struct CmpPipelineDesc;
	class Pipeline;

	struct BufferDesc;
	class Buffer;

	struct TextureDesc;
	class Texture;


// ##############################################################
// #						FORMAT								#
// ##############################################################

	enum class Format : uint8_t
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

	bool IsDepthStencilFormat(Format _format) noexcept;


// ##############################################################
// #						INSTANCE							#
// ##############################################################

	void Initialize();
	void Shutdown();


// ##############################################################
// #						QUEUE								#
// ##############################################################

	class Queue
	{
#if EDO_RHI_DX12
	private:
		friend Device;

		MComPtr<ID3D12CommandQueue> mHandle = nullptr;

		HANDLE mFenceEvent = nullptr;
		MComPtr<ID3D12Fence> mFence = nullptr;
		uint32_t mFenceValue = 1u;
	public:
		ID3D12CommandQueue* Get() const { return mHandle.Get(); }
		ID3D12CommandQueue* operator->() const { return mHandle.Get(); }
#endif // EDO_RHI_DX12

#if EDO_RHI_VK
#endif // EDO_RHI_VK

	private:
	public:
		void Create(const Device& _device, const std::wstring& _name = L"");
		void Destroy(const Device& _device);

		void WaitForComplete();
	};


// ##############################################################
// #						DEVICE								#
// ##############################################################

	class Device
	{
#if EDO_RHI_DX12
	private:
		/// Physical Device
		MComPtr<IDXGIAdapter3> mAdapter = nullptr;

		/// Logical Device
		MComPtr<ID3D12Device4> mHandle = nullptr;

	#if EDO_CONFIG_DEBUG
		DWORD mVLayerCallbackCookie = 0;
	#endif

	public:
		ID3D12Device4* operator->() const { return mHandle.Get(); }
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
		Queue gfxQueue;
		Queue cmpQueue;

		void Create();
		void Destroy();

		void WaitIdle();

		CommandList CreateCommandList();
		void DestroyCommandList(CommandList& _cmd);

		Pipeline CreatePipeline(const GfxPipelineDesc& _desc);
		Pipeline CreatePipeline(const CmpPipelineDesc& _desc);
		void DestroyPipeline(Pipeline& _pip);

		Buffer CreateBuffer(const BufferDesc& _desc, const void* _data = nullptr);
		void DestroyBuffer(Buffer& _buff);

		Texture CreateTexture(const TextureDesc& _desc, const void* _data = nullptr);
		void DestroyTexture(Texture& _tex);
	};


// ##############################################################
// #						SURFACE								#
// ##############################################################

	/**
	* Interface to be implemented by the user to provide
	* windowing/surface to the render.
	*/
	class ISurfaceHandle
	{
	public:
		/**
		* Checks current handle valid state
		*/
		virtual inline bool IsValid() { return false; }

		/**
		* Get surface (width;height) size available for render.
		* Required if no (width;height) is provided into `SwapchainDesc`
		*/
		virtual inline void GetRenderSize(uint32_t& _width, uint32_t& _height) { _width = 0u; _height = 0u; }

#if EDO_RHI_DX12
		/**
		* Retreive Windows native HWND from Window API
		*/
		virtual HWND GetHWND() = 0;
#endif // EDO_RHI_DX12

#if EDO_RHI_VK
		/**
		* \brief Create a `VkSurfaceKHR` from window API surface.
		* /!\ \b Ownership of the created VkSurfaceKHR belongs to the \b Swapchain, not the SurfaceHandle /!\ 
		*/
		virtual VkSurfaceKHR CreateVkSurfaceKHR() = 0;
#endif // EDO_RHI_VK
	};


// ##################################
// #			GLFW				#
// ##################################

#if EDO_RHI_GLFW
	/**
	* Provided base implementation for GLFW Window interface.
	*/
	class GLFWSurfaceHandle : public ISurfaceHandle
	{
	protected:
		GLFWwindow* mHandle = nullptr;

	public:
		inline GLFWSurfaceHandle(GLFWwindow* _window) noexcept :
			mHandle{ _window }
		{
		}

		inline bool IsValid() override final { return mHandle != nullptr; }

		inline void GetRenderSize(uint32_t& _width, uint32_t& _height) override final
		{
			int width, height;
			glfwGetWindowSize(mHandle, &width, &height);

			_width = static_cast<uint32_t>(width);
			_height = static_cast<uint32_t>(height);
		}

#if EDO_RHI_DX12
		HWND GetHWND() override final;
#endif // EDO_RHI_DX12

#if EDO_RHI_VK
		VkSurfaceKHR CreateVkSurfaceKHR() override final;
#endif // EDO_RHI_VK
	};
#endif // EDO_RHI_GLFW


// ##################################
// #			SFML				#
// ##################################

#if EDO_RHI_SFML
	/**
	* Provided base implementation for SFML Window interface.
	*/
	class SFMLSurfaceHandle : public ISurfaceHandle
	{
	protected:
		const sf::Window& mHandle;

	public:
		inline SFMLSurfaceHandle(const sf::Window& _window) noexcept :
			mHandle{ _window }
		{
		}

		inline bool IsValid() override final { return mHandle.isOpen(); }

		inline void GetRenderSize(uint32_t& _width, uint32_t& _height) override final
		{
			const sf::Vector2u size = mHandle.getSize();

			_width = size.x;
			_height = size.y;
		}

#if EDO_RHI_DX12
		HWND GetHWND() override final;
#endif // EDO_RHI_DX12

#if EDO_RHI_VK
		VkSurfaceKHR CreateVkSurfaceKHR() override final;
#endif // EDO_RHI_VK
	};
#endif // EDO_RHI_SFML


// ##################################
// #			SDL3				#
// ##################################

#if EDO_RHI_SDL3
	/**
	* Provided base implementation for SDL3 Window interface.
	*/
	class SDL3SurfaceHandle : public ISurfaceHandle
	{
	protected:
		SDL_Window* mHandle = nullptr;

	public:
		inline SDL3SurfaceHandle(SDL_Window* _window) noexcept :
			mHandle{ _window }
		{
		}

		inline bool IsValid() override final { return mHandle != nullptr; }

		inline void GetRenderSize(uint32_t& _width, uint32_t& _height) override final
		{
			int width, height;
			const bool bRes = SDL_GetWindowSizeInPixels(nullptr, &width, &height);

			if (bRes)
			{
				_width = static_cast<uint32_t>(width);
				_height = static_cast<uint32_t>(height);
			}
			else
			{
				const char* error = SDL_GetError();

				EDO_LOG("SDL_GetWindowSizeInPixels failed!", Error, Edo.RHI.Surface.SDL3, error);

				_width = 0u;
				_height = 0u;
			}
		}

#if EDO_RHI_DX12
		HWND GetHWND() override final;
#endif // EDO_RHI_DX12

#if EDO_RHI_VK
		VkSurfaceKHR CreateVkSurfaceKHR() override final;
#endif // EDO_RHI_VK
	};
#endif // EDO_RHI_GLFW


// ##############################################################
// #						SWAPCHAIN							#
// ##############################################################

	struct SwapchainDesc
	{
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t bufferingCount = 3;
		Format format = Format::RGBA8_sRGB;
		ISurfaceHandle&& surface;
	};

	class Swapchain
	{
#if EDO_RHI_DX12
		MComPtr<IDXGISwapChain3> mHandle = nullptr;
		std::vector<MComPtr<ID3D12Resource>> mBackBuffers{ nullptr };

		HANDLE mFenceEvent = nullptr;
		MComPtr<ID3D12Fence> mFence = nullptr;
		std::vector<uint64_t> mFenceValues{ 0u };
#endif // EDO_RHI_DX12

#if EDO_RHI_VK
		VkSwapchainKHR mHandle = VK_NULL_HANDLE;
#endif // EDO_RHI_VK

	public:
		void Create(const Device& _device, const SwapchainDesc& _desc);
		void Destroy(const Device& _device);
		
		void Present(const Device& _device);
	};


// ##############################################################
// #						COMMAND								#
// ##############################################################

	class CommandList
	{
#if EDO_RHI_DX12
		MComPtr<ID3D12GraphicsCommandList6> mHandle = nullptr;
		MComPtr<ID3D12CommandAllocator> mAlloc = nullptr;
#endif // EDO_RHI_DX12

#if EDO_RHI_VULKAN
#endif // EDO_RHI_VULKAN

	public:
		void Create(const Device& _device);
		void Destroy(const Device& _device);
	};


// ##############################################################
// #						SHADER								#
// ##############################################################

	struct ShaderDesc
	{
		std::wstring path;
		std::wstring entry;
		std::wstring target;
		std::vector<std::wstring> defines;
	};

	class Shader
	{
#if EDO_RHI_DX12
		MComPtr<ID3DBlob> mHandle = nullptr;
#endif // EDO_RHI_DX12

#if EDO_RHI_VK
		VkShaderModule mHandle = VK_NULL_HANDLE;
#endif // EDO_RHI_VK

	public:
		void Create(const Device& _device);
		void Destroy(const Device& _device);

		static Shader CompileFromSource(const Device& _device, const ShaderDesc& _desc);
	};


// ##############################################################
// #						PIPELINE							#
// ##############################################################

// ##################################
// #			GFX					#
// ##################################

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


// ##################################
// #			CMP					#
// ##################################

	struct CmpPipelineDesc
	{
	};

// ##################################

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
		void Create(const Device& _device, const CmpPipelineDesc& _desc);
		void Destroy(const Device& _device);
	};


// ##############################################################
// #						BUFFER								#
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

		std::wstring name;
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
		void Create(const Device& _device, const BufferDesc& _desc, const void* _data = nullptr);
		void Destroy(const Device& _device);
	};


// ##############################################################
// #						TEXTURE								#
// ##############################################################

	enum TextureUsage : uint8_t
	{
		None = 0,

		SRV,

		UAV,

		RT,

		All = SRV | UAV | RT
	};

	struct TextureDesc
	{
		uint32_t width = 0u;
		uint32_t height = 0u;

		uint16_t mipLevels = 1u;

		Format format = Format::Unknown;

		uint8_t usage = TextureUsage::SRV;

		std::wstring name;
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
		void Create(const Device& _device, const TextureDesc& _desc, const void* _data = nullptr);
		void Destroy(const Device& _device);
	};

// ##############################################################


#if EDO_RHI_IMPLEMENTATION
// ##############################################################################################################################
// #														COMMON																#
// ##############################################################################################################################

	bool IsDepthStencilFormat(Format _format) noexcept
	{
		return static_cast<uint8_t>(_format) >= static_cast<uint8_t>(Format::D16) &&
			static_cast<uint8_t>(_format) <= static_cast<uint8_t>(Format::D32S8);
	}

// ##############################################################
// #						DEVICE								#
// ##############################################################

	CommandList Device::CreateCommandList()
	{
		CommandList cmd;

		cmd.Create(*this);

		return cmd;
	}

	void Device::DestroyCommandList(CommandList& _cmd)
	{
		_cmd.Destroy(*this);
	}


	Pipeline Device::CreatePipeline(const GfxPipelineDesc& _desc)
	{
		Pipeline pip;

		pip.Create(*this, _desc);

		return pip;
	}

	Pipeline Device::CreatePipeline(const CmpPipelineDesc& _desc)
	{
		Pipeline pip;

		pip.Create(*this, _desc);

		return pip;
	}

	void Device::DestroyPipeline(Pipeline& _pip)
	{
		_pip.Destroy(*this);
	}


	Buffer Device::CreateBuffer(const BufferDesc& _desc, const void* _data)
	{
		Buffer buff;

		buff.Create(*this, _desc, _data);

		return buff;
	}

	void Device::DestroyBuffer(Buffer& _buff)
	{
		_buff.Destroy(*this);
	}


	Texture Device::CreateTexture(const TextureDesc& _desc, const void* _data)
	{
		Texture tex;

		tex.Create(*this, _desc, _data);

		return tex;
	}

	void Device::DestroyTexture(Texture& _tex)
	{
		_tex.Destroy(*this);
	}


// ##############################################################################################################################
// #														DX12																#
// ##############################################################################################################################
#if EDO_RHI_DX12

	namespace intl
	{
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
				EDO_LOG((L"Format {%1} not supported", static_cast<uint32_t>(_format)), Error, Edo.RHI.DX12.Format);
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
				EDO_LOG((L"DX12 Format {%1} not supported", static_cast<uint32_t>(_format)), Error, Edo.RHI.DX12.Format);
				return Format::Unknown;
			}
			}
		}
	}

// ##############################################################
// #						INSTANCE							#
// ##############################################################

	namespace intl
	{
		static MComPtr<IDXGIFactory6> gFactory = nullptr;

		static MComPtr<IDxcUtils> gShaderCompilerUtils = nullptr;
		static MComPtr<IDxcCompiler3> gShaderCompiler = nullptr;
	}

	void Initialize()
	{
		// Instance
		{

			EDO_ERROR(!intl::gFactory, Edo.RHI.DX12.Instance, L"Try initializing already initialized API!");

			UINT dxgiFactoryFlags = 0;

		#if EDO_CONFIG_DEBUG
			// Validation Layers
			{
				// Debug controller
				{
					MComPtr<ID3D12Debug1> debugController = nullptr;

					const HRESULT hrDebugInterface = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
					if (SUCCEEDED(hrDebugInterface))
					{
						debugController->EnableDebugLayer();
						debugController->SetEnableGPUBasedValidation(true);
					}
					else
					{
						EDO_LOG(L"Validation layer DebugController initialization failed.", Error, Edo.RHI.DX12.Instance,
							(L"Error Code: %1", hrDebugInterface));
					}
				}

				// Report live objects
				{
					MComPtr<IDXGIInfoQueue> dxgiInfoQueue = nullptr;

					const HRESULT hrDebugInterface = DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiInfoQueue));
					if (SUCCEEDED(hrDebugInterface))
					{
						/**
						* Enable this to trigger breakpoints on ReportLiveObjects() and have errors in VisualStudio's output window.
						* WARNING: ReportLiveObjects() will ONLY output in VisualStudio's output window and not exe CONSOLE.
						*/
						dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);
						dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
						dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING, true);
					}
					else
					{
						EDO_LOG(L"Validation layer DebugInfoQueue uninitialized failed.", Error, Edo.RHI.DX12.Instance,
							(L"Error Code: %1", hrDebugInterface));
					}
				}
			}

			// Enable additional debug layers.
			dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		#endif // EDO_CONFIG_DEBUG

			const HRESULT hrFactoryCreated = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&intl::gFactory));
			EDO_DX12_ASSERT(hrFactoryCreated, L"Create Factory failed!");

			EDO_LOG(L"Create Factory success.", Verbose, Edo.RHI.DX12.Instance, intl::gFactory.Get());
		}


		// Shader Compiler
		{
			EDO_ERROR(!intl::gShaderCompilerUtils, Edo.RHI.DX12.DXC, L"Try initializing already initialized DXC Shader Compiler!");

			const HRESULT hCreateUtils = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&intl::gShaderCompilerUtils));
			EDO_DX12_ASSERT(hCreateUtils, L"Create DXC Shader Compiler Utils failed!");

			EDO_LOG(L"Create DXC Shader Compiler Utils success.", Verbose, Edo.RHI.DX12.DXC, intl::gShaderCompilerUtils.Get());


			EDO_ERROR(!intl::gShaderCompiler, Edo.RHI.DX12.DXC, L"Try initializing already initialized DXC Shader Compiler Instance!");

			const HRESULT hCreateInstance = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&intl::gShaderCompiler));
			EDO_DX12_ASSERT(hCreateInstance, L"Create DXC Shader Compiler Instance failed!");

			EDO_LOG(L"Create DXC Shader Compiler success.", Verbose, Edo.RHI.DX12.DXC, intl::gShaderCompiler.Get());
		}
	}

	void Shutdown()
	{
		// Shader Compiler
		{
			EDO_LOG(L"Destroying Shader Compiler...", Verbose, Edo.RHI.DX12.DXC, intl::gShaderCompiler.Get());
			intl::gShaderCompiler.Reset();

			EDO_LOG(L"Destroying Shader Compiler Utils...", Verbose, Edo.RHI.DX12.DXC, intl::gShaderCompilerUtils.Get());
			intl::gShaderCompilerUtils.Reset();
		}


		// Instance
		{
			EDO_ERROR(intl::gFactory, Edo.RHI.DX12.Instance, L"Try shutting down already null API!", return;);

			EDO_LOG(L"Destroying Factory...", Verbose, Edo.RHI.DX12.Instance, intl::gFactory.Get());
			intl::gFactory.Reset();

		#if EDO_CONFIG_DEBUG
			// Report live objects
			MComPtr<IDXGIDebug1> dxgiDebug = nullptr;

			const HRESULT hrDebugInterface = DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug));
			if (SUCCEEDED(hrDebugInterface))
			{
				dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
			}
			else
			{
				EDO_LOG(L"Validation layer uninitialized failed.", Error, Edo.RHI.DX12.Instance);
			}
		#endif // EDO_CONFIG_DEBUG
		}
	}


// ##############################################################
// #						QUEUE								#
// ##############################################################

	void Queue::Create(const Device& _device, const std::wstring& _name)
	{
		// Queue
		{
			const D3D12_COMMAND_QUEUE_DESC descDX{
				.Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
				.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			};

			const HRESULT hrQueueCreated = _device->CreateCommandQueue(&descDX, IID_PPV_ARGS(&mHandle));
			EDO_DX12_ASSERT(hrQueueCreated, (L"Create %1 Queue failed!", _name));

			std::wstring queueName;
		#ifdef EDO_SH_DEBUG_GUARD
			queueName = edo::StringFormat(L"Edo_%1_Queue", _name);
			mHandle->SetName(queueName.c_str());
		#endif // EDO_SH_DEBUG_GUARD

			EDO_LOG((L"Create %1 Queue success.", _name), Verbose, Edo.RHI.DX12.Queue, (L"\"%1\" [%2]", queueName, mHandle.Get()));
		}

		// Sync
		{
			mFenceEvent = CreateEvent(nullptr, false, false, nullptr);
			EDO_ASSERT(mFenceEvent, Edo.RHI.DX12.Queue, (L"Create %1 Queue Fence Event failed!", _name));

			const HRESULT hrSwapChainFenceCreated = _device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));
			EDO_DX12_ASSERT(hrSwapChainFenceCreated, (L"Create %1 Queue Fence failed!", _name));

			std::wstring fenceName;
		#ifdef EDO_SH_DEBUG_GUARD
			fenceName = edo::StringFormat(L"Edo_%1_Queue_Fence", _name);
			mFence->SetName(fenceName.c_str());
		#endif // EDO_SH_DEBUG_GUARD

			EDO_LOG((L"Create %1 Queue Fence success.", _name), Verbose, Edo.RHI.DX12.Queue, (L"\"%1\" [%2]", fenceName, mFence.Get()));
		}
	}

	void Queue::Destroy(const Device& _device)
	{
		(void)_device;

		// Sync
		{
			CloseHandle(mFenceEvent);
			EDO_LOG(L"Destroy Queue Fence Event success", Verbose, Edo.RHI.DX12.Queue, mFenceEvent);
			mFenceEvent = nullptr;

			EDO_LOG(L"Destroying Queue Fence...", Verbose, Edo.RHI.DX12.Queue, mFence.Get());
			mFence.Reset();
		}

		// Queue
		{
			EDO_LOG(L"Destroying Queue...", Verbose, Edo.RHI.DX12.Queue, mHandle.Get());
			mHandle.Reset();
		}
	}

	void Queue::WaitForComplete()
	{
		// Schedule a Signal command in the queue.
		mHandle->Signal(mFence.Get(), mFenceValue);

		// Wait until the fence has been processed.
		mFence->SetEventOnCompletion(mFenceValue, mFenceEvent);
		WaitForSingleObjectEx(mFenceEvent, INFINITE, false);

		// Increment for next use.
		++mFenceValue;
	}

// ##############################################################
// #						DEVICE								#
// ##############################################################

	namespace intl
	{
		void ValidationLayersDebugCallback(D3D12_MESSAGE_CATEGORY _category,
			D3D12_MESSAGE_SEVERITY _severity,
			D3D12_MESSAGE_ID _ID,
			LPCSTR _description,
			void* _context)
		{
			(void)_context;

			std::wstring categoryStr;

			switch (_category)
			{
				case D3D12_MESSAGE_CATEGORY_APPLICATION_DEFINED:
					categoryStr = L"Application Defined";
					break;
				case D3D12_MESSAGE_CATEGORY_MISCELLANEOUS:
					categoryStr = L"Miscellaneous";
					break;
				case D3D12_MESSAGE_CATEGORY_INITIALIZATION:
					categoryStr = L"Initialization";
					break;
				case D3D12_MESSAGE_CATEGORY_CLEANUP:
					categoryStr = L"Cleanup";
					break;
				case D3D12_MESSAGE_CATEGORY_COMPILATION:
					categoryStr = L"Compilation";
					break;
				case D3D12_MESSAGE_CATEGORY_STATE_CREATION:
					categoryStr = L"State Creation";
					break;
				case D3D12_MESSAGE_CATEGORY_STATE_SETTING:
					categoryStr = L"State Setting";
					break;
				case D3D12_MESSAGE_CATEGORY_STATE_GETTING:
					categoryStr = L"State Getting";
					break;
				case D3D12_MESSAGE_CATEGORY_RESOURCE_MANIPULATION:
					categoryStr = L"Resource Manipulation";
					break;
				case D3D12_MESSAGE_CATEGORY_EXECUTION:
					categoryStr = L"Execution";
					break;
				case D3D12_MESSAGE_CATEGORY_SHADER:
					categoryStr = L"Shader";
					break;
				default:
					categoryStr = L"Unknown";
					break;
			}

			std::wstring dets = edo::StringFormat(L"ID [%1]\tCategory [%2]", static_cast<int>(_ID), categoryStr);

			switch (_severity)
			{
				case D3D12_MESSAGE_SEVERITY_CORRUPTION:
				{
					EDO_LOG(_description, AssertFailure, Edo.RHI.DX12.ValidationLayers, std::move(dets));
					break;
				}
				case D3D12_MESSAGE_SEVERITY_ERROR:
				{
					EDO_LOG(_description, Error, Edo.RHI.DX12.ValidationLayers, std::move(dets));
					break;
				}
				case D3D12_MESSAGE_SEVERITY_WARNING:
				{
					EDO_LOG(_description, Warning, Edo.RHI.DX12.ValidationLayers, std::move(dets));
					break;
				}
				case D3D12_MESSAGE_SEVERITY_INFO:
				{
					/**
					* Filter: too much logging on Resource create/destroy and Swapchain Present.
					* EDO logging already tracking.
					*/
					//EDO_LOG(_description, Verbose, Edo.RHI.DX12.ValidationLayers, std::move(dets));
					break;
				}
				case D3D12_MESSAGE_SEVERITY_MESSAGE:
				default:
				{
					EDO_LOG(_description, Normal, Edo.RHI.DX12.ValidationLayers, std::move(dets));
					break;
				}
			}
		}
	}

	void Device::Create()
	{
		// Device
		{
			EDO_ASSERT(intl::gFactory, Edo.RHI.DX12.Device, L"API not initialized. Call edo::rhi::Initialize() first!");
			EDO_ERROR(!mAdapter, Edo.RHI.DX12.Device, L"Try create an already created device!");
			EDO_ERROR(!mHandle, Edo.RHI.DX12.Device, L"Try create an already created device!");

			const HRESULT hrQueryGPU = intl::gFactory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&mAdapter));
			EDO_DX12_ASSERT(hrQueryGPU, L"Adapter not found!");

			const HRESULT hrDeviceCreated = D3D12CreateDevice(mAdapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&mHandle));
			EDO_DX12_ASSERT(hrDeviceCreated, L"Create Device failed!");

			const LPCWSTR name = L"Edo_Device";
			mHandle->SetName(name);

			EDO_LOG(L"Create Device success.", Verbose, Edo.RHI.DX12.Device, (L"\"%1\" [%2]", name, mHandle.Get()));
		}

	#if EDO_CONFIG_DEBUG
		// Validation Layers
		{
			MComPtr<ID3D12InfoQueue1> infoQueue = nullptr;

			const HRESULT hrQueryInfoQueue = mHandle->QueryInterface(IID_PPV_ARGS(&infoQueue));
			if (SUCCEEDED(hrQueryInfoQueue))
			{
				infoQueue->RegisterMessageCallback(intl::ValidationLayersDebugCallback,
					D3D12_MESSAGE_CALLBACK_IGNORE_FILTERS, nullptr, &mVLayerCallbackCookie);

				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
			}
			else
			{
				EDO_LOG(L"Device query info queue to enable validation layers failed.",
					Error, Edo.RHI.DX12.Device, (L"Error Code: %1", hrQueryInfoQueue));
			}
		}
	#endif
		
		// Queues
		{
			gfxQueue.Create(*this, L"GFX");
			cmpQueue.Create(*this, L"CMP");
		}
	}

	void Device::Destroy()
	{
		EDO_ERROR(mHandle && mAdapter, Edo.RHI.DX12.Device, L"Try destroying already null device!", return;);

		// Queue
		{
			gfxQueue.Destroy(*this);
			cmpQueue.Destroy(*this);
		}

	#if EDO_CONFIG_DEBUG
		if (mVLayerCallbackCookie)
		{
			MComPtr<ID3D12InfoQueue1> infoQueue = nullptr;

			const HRESULT hrQueryInfoQueue = mHandle->QueryInterface(IID_PPV_ARGS(&infoQueue));
			if (SUCCEEDED(hrQueryInfoQueue))
			{
				infoQueue->UnregisterMessageCallback(mVLayerCallbackCookie);
				mVLayerCallbackCookie = 0;
			}
			else
			{
				EDO_LOG(L"Device query info queue to clear validation layers failed.",
					Error, Edo.RHI.DX12.Device, (L"Error Code: %1", hrQueryInfoQueue));
			}
		}
	#endif

		EDO_LOG(L"Destroying Device...", Verbose, Edo.RHI.DX12.Device, mHandle.Get());

		mHandle.Reset();
		mAdapter.Reset();
	}

	void Device::WaitIdle()
	{
		// Schedule a Signal command in queues.
		gfxQueue.mHandle->Signal(gfxQueue.mFence.Get(), gfxQueue.mFenceValue);
		cmpQueue.mHandle->Signal(cmpQueue.mFence.Get(), cmpQueue.mFenceValue);


		// Wait until the fence has been processed.
		gfxQueue.mFence->SetEventOnCompletion(gfxQueue.mFenceValue, gfxQueue.mFenceEvent);
		cmpQueue.mFence->SetEventOnCompletion(cmpQueue.mFenceValue, cmpQueue.mFenceEvent);

		HANDLE fenceEvents[] = { gfxQueue.mFenceEvent, cmpQueue.mFenceEvent };
		WaitForMultipleObjectsEx(_countof(fenceEvents), fenceEvents, TRUE, INFINITE, false);


		// Increment for next use.
		++gfxQueue.mFenceValue;
		++cmpQueue.mFenceValue;
	}


// ##############################################################
// #						SURFACE								#
// ##############################################################

// ##################################
// #			GLFW				#
// ##################################

#if EDO_RHI_GLFW
	HWND GLFWSurfaceHandle::GetHWND()
	{
		EDO_ASSERT(mHandle, Edo.RHI.Surface.GLFW, L"Try creating Surface from null window!");

		return glfwGetWin32Window(mHandle);
	}
#endif // EDO_RHI_GLFW

// ##################################
// #			SFML				#
// ##################################

#if EDO_RHI_SFML
	HWND SFMLSurfaceHandle::GetHWND()
	{
		return mHandle.getNativeHandle();
	}
#endif // EDO_RHI_SFML

// ##################################
// #			SDL3				#
// ##################################

#if EDO_RHI_SDL3
	HWND SDL3SurfaceHandle::GetHWND()
	{
		SDL_PropertiesID props = SDL_GetWindowProperties(mHandle);
		HWND hwnd = (HWND)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);

		return hwnd;
	}
#endif // EDO_RHI_SDL3


// ##############################################################
// #						SWAPCHAIN							#
// ##############################################################

	void Swapchain::Create(const Device& _device, const SwapchainDesc& _desc)
	{
		EDO_ASSERT(_desc.surface.IsValid(), Edo.RHI.DX12.Swapchain, L"Valid Surface handle must be provided for Swapchain creation!");

		// Swapchain
		{
			uint32_t width = 0u;
			uint32_t height = 0u;
			_desc.surface.GetRenderSize(width, height);

			width = _desc.width != 0u ? _desc.width : width;
			height = _desc.height != 0u ? _desc.height : height;

			EDO_ASSERT(width != 0u, Edo.RHI.DX12.Swapchain, L"Swapchain width must be greater than 0!");
			EDO_ASSERT(height != 0u, Edo.RHI.DX12.Swapchain, L"Swapchain height must be greater than 0!");

			const DXGI_SWAP_CHAIN_DESC1 descDX{
				.Width = width,
				.Height = height,
				.Format = intl::MapFormatToDX(_desc.format == Format::RGBA8_sRGB ? Format::RGBA8_UNORM : _desc.format),
				.Stereo = false,
				.SampleDesc = {.Count = 1, .Quality = 0 },
				.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
				.BufferCount = _desc.bufferingCount,
				.Scaling = DXGI_SCALING_STRETCH,
				.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
				.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED,
				.Flags = 0,
			};

			MComPtr<IDXGISwapChain1> swapchain1;
			const HRESULT hrSwapChainCreated = intl::gFactory->CreateSwapChainForHwnd(_device.gfxQueue.Get(), _desc.surface.GetHWND(), &descDX, nullptr, nullptr, &swapchain1);
			EDO_DX12_ASSERT(hrSwapChainCreated, L"Create Swapchain failed!");

			EDO_LOG(L"Create Swapchain success.", Verbose, Edo.RHI.DX12.Swapchain, swapchain1.Get());

			const HRESULT hrSwapChainCast = swapchain1.As(&mHandle);
			EDO_DX12_ASSERT(hrSwapChainCast, L"Swapchain cast failed!");
		}


		// Query back buffers
		{
			mBackBuffers.resize(_desc.bufferingCount);

			for (uint32_t i = 0; i < _desc.bufferingCount; ++i)
			{
				const HRESULT hrSwapChainGetBuffer = mHandle->GetBuffer(i, IID_PPV_ARGS(&mBackBuffers[i]));
				EDO_DX12_ASSERT(hrSwapChainGetBuffer, (L"Get Swapchain Buffer [%1] failed!", i));

				const std::wstring name = L"Edo_Swapchain_BackBuffer [" + std::to_wstring(i) + L"]";
				mBackBuffers[i]->SetName(name.data());

				EDO_LOG((L"Query Swapchain Buffer [%1] success.", i), Verbose, Edo.RHI.DX12.Swapchain, (L"\"%1\" [%2]", name, mBackBuffers[i].Get()));
			}
		}

		
		// Sync
		{
			mFenceValues.resize(_desc.bufferingCount);

			mFenceEvent = CreateEvent(nullptr, false, false, nullptr);
			EDO_ASSERT(mFenceEvent, Edo.RHI.DX12.Swapchain, L"Create Swapchain Fence Event failed!");

			const HRESULT hrSwapChainFenceCreated = _device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));
			EDO_DX12_ASSERT(hrSwapChainFenceCreated, L"Create Swapchain Fence failed!");

			const LPCWSTR name = L"Edo_Swapchain_Fence";
			mFence->SetName(name);

			EDO_LOG(L"Create Swapchain Fence success.", Verbose, Edo.RHI.DX12.Swapchain, (L"\"%1\" [%2]", name, mFence.Get()));
		}
	}

	void Swapchain::Destroy(const Device& _device)
	{
		(void)_device;

		// Sync
		{
			CloseHandle(mFenceEvent);
			EDO_LOG(L"Destroy Swapchain Fence Event success", Verbose, Edo.RHI.DX12.Swapchain, mFenceEvent);
			mFenceEvent = nullptr;

			EDO_LOG(L"Destroying Swapchain Fence...", Verbose, Edo.RHI.DX12.Swapchain, mFence.Get());
			mFence.Reset();
		}

		for (size_t i = 0; i < mBackBuffers.size(); ++i)
		{
			EDO_LOG((L"Destroying Swapchain image [%1]...", i), Verbose, Edo.RHI.DX12.Swapchain, mBackBuffers[i].Get());
			mBackBuffers[i].Reset();
		}

		EDO_LOG(L"Destroying Swapchain...", Verbose, Edo.RHI.DX12.Swapchain, mHandle.Get());
		mHandle.Reset();
	}

	void Swapchain::Present(const Device& _device)
	{
		const UINT frameIndex = mHandle->GetCurrentBackBufferIndex();

		const HRESULT hrPresent = mHandle->Present(1, 0);
		EDO_DX12_ASSERT(hrPresent, L"Swapchain Present failed");

		// Move to next frame
		{
			// Schedule a Signal command in the queue.
			const UINT64 fenceValue = mFenceValues[frameIndex];
			const HRESULT hrFenceSignal = _device.gfxQueue->Signal(mFence.Get(), fenceValue);
			EDO_DX12_ASSERT(hrFenceSignal, L"Swapchain Fence Signal failed");

			const UINT newFrameIndex = mHandle->GetCurrentBackBufferIndex();
			const UINT64 newFenceValue = mFenceValues[newFrameIndex];

			// If the next frame is not ready to be rendered yet, wait until it is ready.
			if (mFence->GetCompletedValue() < newFenceValue)
			{
				const HRESULT hrSetEvent = mFence->SetEventOnCompletion(newFenceValue, mFenceEvent);
				EDO_DX12_ASSERT(hrSetEvent, L"Fence SetEventOnCompletion failed.");

				WaitForSingleObjectEx(mFenceEvent, INFINITE, FALSE);
			}

			// Set the fence value for the next frame.
			mFenceValues[newFrameIndex] = fenceValue + 1;
		}
	}


// ##############################################################
// #						COMMAND								#
// ##############################################################

	void CommandList::Create(const Device& _device)
	{
		// Allocator
		{
			const HRESULT hrCmdAllocCreated = _device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mAlloc));
			EDO_DX12_ASSERT(hrCmdAllocCreated, L"Create Command Allocator failed!");

			const std::wstring name = L"Edo_CommandAlloc";
			mAlloc->SetName(name.c_str());

			EDO_LOG(L"Create Command Allocator success", Verbose, Edo.RHI.DX12.Command, (L"\"%1\" [%2]", name, mAlloc.Get()));
		}

		// Command List
		{
			const HRESULT hrCmdListCreated = _device->CreateCommandList1(0,
				D3D12_COMMAND_LIST_TYPE_DIRECT,
				D3D12_COMMAND_LIST_FLAG_NONE,
				IID_PPV_ARGS(&mHandle));
			EDO_DX12_ASSERT(hrCmdListCreated, "Create Command List failed!");

			const LPCWSTR name = L"Edo_CommandList";
			mHandle->SetName(name);

			EDO_LOG(L"Create Command List success.", Verbose, Edo.RHI.DX12.Command, (L"\"%1\" [%2]", name, mHandle.Get()));
		}
	}

	void CommandList::Destroy(const Device& _device)
	{
		(void)_device;

		EDO_LOG(L"Destroying Command List...", Verbose, Edo.RHI.DX12.Command, mHandle.Get());
		mHandle.Reset();

		EDO_LOG(L"Destroying Command Allocator...", Verbose, Edo.RHI.DX12.Command, mAlloc.Get());
		mAlloc.Reset();
	}


// ##############################################################
// #						SHADER								#
// ##############################################################

	namespace intl
	{
		// TODO: shader includer?
	}

	void Shader::Create(const Device& _device)
	{
		(void)_device;

		EDO_LOG(L"Create Shader success", Verbose, Edo.RHI.DX12.Shader, (L"[%1]", mHandle.Get()));
	}

	void Shader::Destroy(const Device& _device)
	{
		(void)_device;

		if (mHandle)
		{
			EDO_LOG(L"Destroying Shader...", Verbose, Edo.RHI.DX12.Shader, mHandle.Get());
			mHandle.Reset();
		}
		else
		{
			EDO_LOG("Try destroy null Shader", Warning, Edo.RHI.DX12.Shader);
		}
	}

	Shader Shader::CompileFromSource(const Device& _device, const ShaderDesc& _desc)
	{
		Shader result;

		MComPtr<IDxcBlobEncoding> blob;
		DxcBuffer dx;

		const HRESULT hrLoadFile = intl::gShaderCompilerUtils->LoadFile(_desc.path.c_str(), nullptr, &blob);
		if (FAILED(hrLoadFile))
		{
			EDO_LOG((L"Load Shader `%1` failed!", _desc.path), Error, Edo.RHI.DXC, (L"Error Code: %1", hrLoadFile));
			return result;
		}

		dx.Ptr = blob->GetBufferPointer();
		dx.Size = blob->GetBufferSize();
		dx.Encoding = 0;

		std::vector<LPCWSTR> cArgs
		{
			L"-E",
			_desc.entry.c_str(),
			L"-T",
			_desc.target.c_str(),
			L"-HV",
			L"2021",
			DXC_ARG_PACK_MATRIX_ROW_MAJOR,
			DXC_ARG_ALL_RESOURCES_BOUND,
			/* TODO: Add include path for shader includer (Warning: must work both from VS and standalone .exe) */
			//L"-I",
			//L"/Resources/Shaders"
		};


#if EDO_CONFIG_DEBUG
		cArgs.push_back(DXC_ARG_DEBUG);
		cArgs.push_back(DXC_ARG_WARNINGS_ARE_ERRORS);
		cArgs.push_back(DXC_ARG_SKIP_OPTIMIZATIONS);
#else
		cArgs.push_back(DXC_ARG_OPTIMIZATION_LEVEL3);
#endif

		for (auto& define : _desc.defines)
		{
			cArgs.push_back(L"-D");
			cArgs.push_back(define.c_str());
		}


		MComPtr<IDxcResult> compiled;
		const HRESULT hrCompile = intl::gShaderCompiler->Compile(&dx, cArgs.data(), static_cast<uint32_t>(cArgs.size()), nullptr /*&includer*/, IID_PPV_ARGS(&compiled));

		if (FAILED(hrCompile))
		{
			MComPtr<IDxcBlobUtf8> errors;
			compiled->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&errors), nullptr);

			if (errors && errors->GetStringLength() > 0)
			{
				EDO_LOG((L"Shader `%1:%2` Compilation failed!", _desc.path, _desc.entry), Error, Edo.RHI.DXC, errors->GetStringPointer());
			}

			return result;
		}

		compiled->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&result.mHandle), nullptr);

		EDO_LOG(L"Compile Shader success.", Verbose, Edo.RHI.DXC, (L"\"%1\" [%2]", _desc.path, result.mHandle.Get()));

		result.Create(_device);

		return result;
	}


// ##############################################################
// #						PIPELINE							#
// ##############################################################

	namespace intl
	{
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
					EDO_LOG((L"Polygon Mode {%1} not supported", static_cast<uint32_t>(_mode)), Error, Edo.RHI.DX12.Pipeline);
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
					EDO_LOG((L"Culling Mode {%1} not supported", static_cast<uint32_t>(_mode)), Error, Edo.RHI.DX12.Pipeline);
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
					EDO_LOG((L"FrontFace Mode {%1} not supported", static_cast<uint32_t>(_mode)), Error, Edo.RHI.DX12.Pipeline);
					return TRUE;
				}
			}
		}
	}

	void Pipeline::Create(const Device& _device, const GfxPipelineDesc& _desc)
	{
		(void)_device;
		(void)_desc;
#if 0

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

#endif
	}

	void Pipeline::Create(const Device& _device, const CmpPipelineDesc& _desc)
	{
		(void)_device;
		(void)_desc;
#if 0

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

#endif
	}

	void Pipeline::Destroy(const Device& _device)
	{
		(void)_device;

		// PipelineState
		if (mHandle)
		{
			EDO_LOG(L"Destroying PipelineState...", Verbose, Edo.RHI.DX12.Pipeline, mHandle.Get());

			mHandle.Reset();
		}
		else
		{
			EDO_LOG("Try destroy null PipelineState", Warning, Edo.RHI.DX12.Pipeline);
		}
	}


// ##############################################################
// #						BUFFER								#
// ##############################################################

	namespace intl
	{
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
				EDO_LOG((L"Buffer Type {%1} not supported", static_cast<uint32_t>(_type)), Error, Edo.RHI.DX12.Buffer);
				return D3D12_HEAP_TYPE_DEFAULT;
			}
			}
		}
	}

	void Buffer::Create(const Device& _device, const BufferDesc& _desc, const void* _data)
	{
		std::wstring name = _desc.name;

		if (_desc.name.empty())
		{
			static uint32_t uBuffIndex = 0;
			name = L"Edo_UnknownBuffer_" + std::to_wstring(++uBuffIndex);
		}

		EDO_ERROR(!mHandle, Edo.RHI.DX12.Buffer, (L"Try create on non-null Buffer `%1`"), name);

		const D3D12_HEAP_PROPERTIES heap{
			.Type = intl::MapBufferTypeToDX(_desc.type),
		};

		const D3D12_RESOURCE_DESC descDX{
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

		const HRESULT hrBufferCreated = _device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &descDX,
			D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&mHandle));
		EDO_DX12_ASSERT(hrBufferCreated, (L"Create Buffer `%1` Failed!", name));

		mHandle->SetName(name.c_str());

		EDO_LOG(L"Create Buffer success", Verbose, Edo.RHI.DX12.Buffer, (L"\"%1\" [%2]", name, mHandle.Get()));


		// TODO: upload data
		(void)_data;
	}

	void Buffer::Destroy(const Device& _device)
	{
		(void)_device;

		if (mHandle)
		{
			EDO_LOG(L"Destroying Buffer...", Verbose, Edo.RHI.DX12.Buffer, mHandle.Get());
			mHandle.Reset();
		}
		else
		{
			EDO_LOG("Try destroy null Buffer", Warning, Edo.RHI.DX12.Buffer);
		}
	}


// ##############################################################
// #						TEXTURE								#
// ##############################################################

	namespace intl
	{
		D3D12_RESOURCE_FLAGS MapTextureFlagsDX(Format _format, uint8_t _usage)
		{
			D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;

			if (IsDepthStencilFormat(_format))
			{
				flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
			}

			if (!(_usage & TextureUsage::SRV))
			{
				flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
			}

			if (_usage & TextureUsage::UAV)
			{
				flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
			}

			if (_usage & TextureUsage::RT)
			{
				flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
			}

			return flags;
		}

		D3D12_RESOURCE_STATES MapInitialTextureStateDX(const TextureDesc& _desc, const void* _data)
		{
			if (_data || _desc.usage & TextureUsage::SRV)
			{
				return D3D12_RESOURCE_STATE_COPY_DEST;
			}
			
			if (_desc.usage & TextureUsage::RT)
			{
				if (IsDepthStencilFormat(_desc.format))
				{
					return D3D12_RESOURCE_STATE_DEPTH_WRITE;
				}
				else
				{
					return D3D12_RESOURCE_STATE_RENDER_TARGET;
				}
			}

			if (_desc.usage & TextureUsage::UAV)
			{
				return D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
			}

			return D3D12_RESOURCE_STATE_COMMON;
		}
	}

	void Texture::Create(const Device& _device, const TextureDesc& _desc, const void* _data)
	{
		std::wstring name = _desc.name;
		if (_desc.name.empty())
		{
			static uint32_t uTextIndex = 0;
			name = L"Edo_UnknownTexture_" + std::to_wstring(++uTextIndex);
		}

		EDO_ERROR(!mHandle, Edo.RHI.DX12.Texture, (L"Try create on non-null Texture `%1`", name));
		EDO_ERROR(!((_desc.usage & TextureUsage::RT) && _data), Edo.RHI.DX12.Texture,
			(L"Can not provide data to a RenderTarget Texture `%1`", name));

		const D3D12_HEAP_PROPERTIES heap{
			.Type = D3D12_HEAP_TYPE_DEFAULT,
		};

		const D3D12_RESOURCE_DESC descDX{
			.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
			.Alignment = 0,
			.Width = _desc.width,
			.Height = _desc.height,
			.DepthOrArraySize = 1,
			.MipLevels = _desc.mipLevels,
			.Format = intl::MapFormatToDX(_desc.format),
			.SampleDesc = {.Count = 1, .Quality = 0 },
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = intl::MapTextureFlagsDX(_desc.format, _desc.usage),
		};

		const HRESULT hrBufferCreated = _device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &descDX,
			intl::MapInitialTextureStateDX(_desc, _data), nullptr, IID_PPV_ARGS(&mHandle));
		EDO_DX12_ASSERT(hrBufferCreated, (L"Create Texture `%1` failed!", name));

		mHandle->SetName(name.c_str());

		EDO_LOG(L"Create Texture success.", Verbose, Edo.RHI.DX12.Texture, (L"\"%1\" [%2]", name, mHandle.Get()));


		// TODO: upload data
		(void)_data;
	}

	void Texture::Destroy(const Device& _device)
	{
		(void)_device;

		if (mHandle)
		{
			EDO_LOG(L"Destroying Texture...", Verbose, Edo.RHI.DX12.Texture, mHandle.Get());
			mHandle.Reset();
		}
		else
		{
			EDO_LOG("Try destroy null Texture", Warning, Edo.RHI.DX12.Texture);
		}
	}

// ##############################################################

#endif // EDO_RHI_DX12


// ##############################################################################################################################
// #														VK																	#
// ##############################################################################################################################
#if EDO_RHI_VK

	namespace intl
	{
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
					EDO_LOG((L"Format {%1} not supported", static_cast<uint32_t>(_format)), Error, Edo.RHI.VK.Format);
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
					EDO_LOG((L"VK Format {%1} not supported", static_cast<uint32_t>(_format)), Error, Edo.RHI.VK.Format);
					return Format::Unknown;
				}
			}
		}
	}

// ##############################################################
// #						INSTANCE							#
// ##############################################################

	namespace intl
	{
		static VkInstance gInstance = VK_NULL_HANDLE;
		static VkDebugUtilsMessengerEXT gDebugMessenger = VK_NULL_HANDLE;

	#if EDO_CONFIG_DEBUG
		static std::array<const char*, 1> gValidationLayers{
			"VK_LAYER_KHRONOS_validation"
		};

		VKAPI_ATTR VkBool32 VKAPI_CALL ValidationLayersDebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData)
		{
			(void)pUserData;

			std::wstring msgTypeStr;

			switch (messageType)
			{
				case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
				{
					msgTypeStr = L"[General]";
					break;
				}
				case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
				{
					msgTypeStr = L"[Validation]";
					break;
				}
				case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
				{
					msgTypeStr = L"[Performance]";
					break;
				}
				case VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT:
				{
					msgTypeStr = L"[AddrBind]";
					break;
				}
				default:
				{
					msgTypeStr = L"[Unknown]";
					break;
				}
			}

			switch (messageSeverity)
			{
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
				{
					/**
					* Filter: too much logging.
					* EDO logging already tracking.
					*/
					//EDO_LOG(pCallbackData->pMessage, Verbose, Edo.RHI.VK.ValidationLayers, (L"Vulkan Validation Layers %1", msgTypeStr));
					break;
				}
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
				{
					EDO_LOG(pCallbackData->pMessage, Info, Edo.RHI.VK.ValidationLayers, (L"Vulkan Validation Layers %1", msgTypeStr));
					break;
				}
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
				{
					EDO_LOG(pCallbackData->pMessage, Warning, Edo.RHI.VK.ValidationLayers, (L"Vulkan Validation Layers %1", msgTypeStr));
					break;
				}
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
				{
					EDO_LOG(pCallbackData->pMessage, Error, Edo.RHI.VK.ValidationLayers, (L"Vulkan Validation Layers %1", msgTypeStr));
					break;
				}
				default:
				{
					EDO_LOG(pCallbackData->pMessage, Normal, Edo.RHI.VK.ValidationLayers, (L"Vulkan Validation Layers %1", msgTypeStr));
					break;
				}
			}

			return VK_FALSE;
		}
	#endif // EDO_RHI_DEBUG
	}

	void Initialize()
	{
		EDO_ERROR(!intl::gInstance, Edo.RHI.VK.Instance, L"Try initializing already initialized API!");

		const VkApplicationInfo appInfo{
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.pNext = nullptr,
			.pApplicationName = "EDO_VK-App",
			.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
			.pEngineName = "Edo",
			.engineVersion = VK_MAKE_VERSION(1, 0, 0),
			.apiVersion = VK_API_VERSION_1_4,
		};

		VkInstanceCreateInfo instanceCreateInfo{
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.pApplicationInfo = &appInfo,
			.enabledLayerCount = 0u,
			.ppEnabledLayerNames = nullptr,
			// TODO:
			//.enabledExtensionCount = static_cast<uint32_t>(vkInstanceExts.size()),
			//.ppEnabledExtensionNames = vkInstanceExts.data(),
		};

	#if EDO_CONFIG_DEBUG
		// Validation Layers
		// Check Support
		{
			// Query currently supported layers.
			uint32_t layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			std::vector<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


			// Check each asked supported.
			for (uint32_t i = 0; i < intl::gValidationLayers.size(); ++i)
			{
				bool layerFound = false;

				for (uint32_t j = 0; j < availableLayers.size(); ++j)
				{
					// Layer found.
					if (std::strcmp(intl::gValidationLayers[i], availableLayers[j].layerName) == 0)
					{
						layerFound = true;
						break;
					}
				}

				// Layer not found.
				if (!layerFound)
				{
					EDO_LOG((L"Validation Layers [%1] not supported!", intl::gValidationLayers[i]), Error, Edo.RHI.VK.Instance);
				}
			}
		}

		const VkDebugUtilsMessengerCreateInfoEXT debugUtilsInfo{
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
			.pNext = nullptr,
			.flags = 0u,
			.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT,
			.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_FLAG_BITS_MAX_ENUM_EXT,
			.pfnUserCallback = intl::ValidationLayersDebugCallback,
			.pUserData = nullptr,
		};

		instanceCreateInfo.pNext = &debugUtilsInfo;

		instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(intl::gValidationLayers.size());
		instanceCreateInfo.ppEnabledLayerNames = intl::gValidationLayers.data();
	#endif // EDO_CONFIG_DEBUG

		const VkResult vrInstanceCreated = vkCreateInstance(&instanceCreateInfo, nullptr, &intl::gInstance);
		EDO_VK_ASSERT(vrInstanceCreated, L"Create VkInstance failed!");
		
		EDO_LOG("Create VkInstance success.", Verbose, Edo.RHI.VK.Instance, intl::gInstance);

	#if EDO_CONFIG_DEBUG
		EDO_ERROR(!intl::gDebugMessenger, Edo.RHI.VK.Instance, L"Try initializing already initialized API Debug callback!");

		// Validation Layers
		{
			auto createDebugFunc = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(intl::gInstance, "vkCreateDebugUtilsMessengerEXT");

			if (createDebugFunc)
			{
				const VkResult vrDebugCreated = createDebugFunc(intl::gInstance, &debugUtilsInfo, nullptr, &intl::gDebugMessenger);
				EDO_VK_ASSERT(vrDebugCreated, L"Failed to create vulkan debug messenger!");

				EDO_LOG(L"Debug Messenger created.", Verbose, Edo.RHI.VK.Instance, intl::gDebugMessenger);
			}
			else
			{
				EDO_LOG(L"Extension PFN_vkCreateDebugUtilsMessengerEXT missing!", Warning, Edo.RHI.VK.Instance);
			}
		}
	#endif // EDO_CONFIG_DEBUG
	}

	void Shutdown()
	{
		EDO_ERROR(intl::gInstance, Edo.RHI.DX12.Instance, L"Try shutting down already null API!", return;);

	#if EDO_CONFIG_DEBUG
		if (intl::gDebugMessenger != VK_NULL_HANDLE)
		{
			auto destroyDebugFunc = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(intl::gInstance, "vkDestroyDebugUtilsMessengerEXT");

			if (destroyDebugFunc)
			{
				destroyDebugFunc(intl::gInstance, intl::gDebugMessenger, nullptr);
				EDO_LOG(L"Destroy Debug Messenger success.", Verbose, Edo.RHI.VK.Instance, intl::gDebugMessenger);
				intl::gDebugMessenger = VK_NULL_HANDLE;
			}
			else
			{
				EDO_LOG(L"Extension PFN_vkDestroyDebugUtilsMessengerEXT missing!", Warning, Edo.RHI.VK.Instance);
			}
		}
	#endif

		vkDestroyInstance(intl::gInstance, nullptr);
		EDO_LOG(L"Destroy Instance success", Verbose, Edo.RHI.VK.Instance, intl::gInstance);
		intl::gInstance = VK_NULL_HANDLE;
	}


// ##############################################################
// #						DEVICE								#
// ##############################################################

	void Device::Create()
	{
	}

	void Device::Destroy()
	{
	}

	void Device::WaitIdle()
	{
		vkDeviceWaitIdle(mHandle);
	}

// ##############################################################
// #						SURFACE								#
// ##############################################################

// ##################################
// #			GLFW				#
// ##################################

#if EDO_RHI_GLFW
	VkSurfaceKHR GLFWSurfaceHandle::CreateVkSurfaceKHR()
	{
		EDO_ASSERT(mHandle, Edo.RHI.Surface.GLFW, L"Try creating Surface from null window!");

		VkSurfaceKHR surfaceKHR = VK_NULL_HANDLE;
		const VkResult vrSurfaceCreated = glfwCreateWindowSurface(intl::gInstance, mHandle, nullptr, &surfaceKHR);

		if (vrSurfaceCreated != VkResult::VK_SUCCESS)
		{
			const char* error;
			glfwGetError(&error);

			EDO_LOG((L"Create Window Surface `glfwCreateWindowSurface` failed!" + edo::StringFormat(L"\tError Code: %1", _vres)), AssertFailure, Edo.RHI.Surface.GLFW, error);
		}

		SA_LOG("Create Window Surface success.", Verbose, Edo.RHI.Surface.GLFW, surfaceKHR);

		return surfaceKHR;
	}
#endif // EDO_RHI_GLFW

// ##################################
// #			SFML				#
// ##################################

#if EDO_RHI_SFML
	VkSurfaceKHR SFMLSurfaceHandle::CreateVkSurfaceKHR()
	{
		VkSurfaceKHR surfaceKHR = VK_NULL_HANDLE;

		const bool res = mHandle.createVulkanSurface(intl::gInstance, surfaceKHR);
		EDO_ASSERT(res, Edo.RHI.Surface.SFML, L"Create Window Surface failed!");

		return surfaceKHR;
	}
#endif // EDO_RHI_SFML

// ##################################
// #			SDL3				#
// ##################################

#if EDO_RHI_SDL3
	VkSurfaceKHR SDL3SurfaceHandle::CreateVkSurfaceKHR()
	{
		VkSurfaceKHR surfaceKHR = VK_NULL_HANDLE;

		const bool bRes = SDL_Vulkan_CreateSurface(mHandle, intl::gInstance, nullptr, &surfaceKHR);

		if (bRes)
		{
			const char* error = SDL_GetError();

			EDO_LOG(L"Create Window Surface `SDL_Vulkan_CreateSurface()` failed!", AssertFailure, Edo.RHI.Surface.SDL3, error)
		}

		return surfaceKHR;
	}
#endif // EDO_RHI_SDL3


// ##############################################################
// #						PIPELINE							#
// ##############################################################

	void Pipeline::Create(const Device& _device, const GfxPipelineDesc& _desc)
	{
		(void)_device;
		(void)_desc;
#if 0

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

#endif
	}

	void Pipeline::Create(const Device& _device, const CmpPipelineDesc& _desc)
	{
		(void)_device;
		(void)_desc;
	}

	void Pipeline::Destroy(const Device& _device)
	{
		// Pipeline
		if (mHandle != VK_NULL_HANDLE)
		{
			vkDestroyPipeline(_device.Get(), mHandle, nullptr);

			EDO_LOG(L"Destroy Pipeline success.", Verbose, Edo.RHI.VK.Pipeline, mHandle);

			mHandle = VK_NULL_HANDLE;
		}
		else
		{
			EDO_LOG("Try destroy null pipeline", Warning, Edo.RHI.VK.Pipeline);
		}
	}


// ##############################################################
// #						BUFFER								#
// ##############################################################

	void Buffer::Create(const Device& _device, const BufferDesc& _desc)
	{
		EDO_ERROR(!mHandle, Edo.RHI.VK.Buffer, "Try create on non-null Buffer");
		EDO_ERROR(!mMemory, Edo.RHI.VK.Buffer, "Try create on non-null Buffer");

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
			EDO_VK_ASSERT(vrBufferCreated, L"Create Buffer failed!");

			EDO_LOG(L"Create Buffer success", Verbose, Edo.RHI.VK.Buffer, mHandle);
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
			EDO_VK_ASSERT(vrBufferAlloc, L"Create Buffer Memory failed!");

			EDO_LOG(L"Create Buffer Memory success", Verbose, Edo.RHI.VK.Buffer, mMemory);
		}

		// Bind
		{
			const VkResult vrBindBufferMem = vkBindBufferMemory(_device.Get(), mHandle, mMemory, 0);
			EDO_VK_ASSERT(vrBindBufferMem, L"Bind Buffer Memory failed!");

			EDO_LOG(L"Bind Buffer Memory success", Verbose, Edo.RHI.VK.Buffer, mMemory);
		}
	}

	void Buffer::Destroy(const Device& _device)
	{
		// Buffer
		if (mHandle != VK_NULL_HANDLE)
		{
			vkDestroyBuffer(_device.Get(), mHandle, nullptr);

			EDO_LOG(L"Destroy Buffer success.", Verbose, Edo.RHI.VK.Buffer, mHandle);

			mHandle = VK_NULL_HANDLE;
		}
		else
		{
			EDO_LOG("Try destroy null Buffer", Warning, Edo.RHI.VK.Buffer);
		}

		// Memory
		if(mMemory != VK_NULL_HANDLE)
		{
			vkFreeMemory(_device.Get(), mMemory, nullptr);

			EDO_LOG(L"Destroy Buffer Memory success.", Verbose, Edo.RHI.VK.Buffer, mMemory);

			mMemory = VK_NULL_HANDLE;
		}
		else
		{
			EDO_LOG("Try destroy null Buffer Memory", Warning, Edo.RHI.VK.Buffer);
		}
	}


// ##############################################################
// #						TEXTURE								#
// ##############################################################

	void Texture::Create(const Device& _device, const TextureDesc& _desc)
	{
		EDO_ERROR(!mHandle, Edo.RHI.VK.Texture, "Try create on non-null Texture");
		EDO_ERROR(!mMemory, Edo.RHI.VK.Texture, "Try create on non-null Texture");

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
			EDO_VK_ASSERT(vrImageCreated, L"Create Texture failed!");

			EDO_LOG(L"Create Texture success", Verbose, Edo.RHI.VK.Texture, mHandle);
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
			EDO_VK_ASSERT(vrImageAlloc, L"Create Texture Memory failed!");

			EDO_LOG(L"Create Texture Memory success", Verbose, Edo.RHI.VK.Texture, mMemory);
		}

		// Bind
		{
			const VkResult vrImageBindMem = vkBindImageMemory(_device.Get(), mHandle, mMemory, 0);
			EDO_VK_ASSERT(vrImageBindMem, L"Bind Texture Memory failed!");

			EDO_LOG(L"Bind Texture Memory success", Verbose, Edo.RHI.VK.Texture);
		}
	}

	void Texture::Destroy(const Device& _device)
	{
		// Image
		if(mHandle != VK_NULL_HANDLE)
		{
			vkDestroyImage(_device.Get(), mHandle, nullptr);

			EDO_LOG(L"Destroy Texture success.", Verbose, Edo.RHI.VK.Texture, mHandle);

			mHandle = VK_NULL_HANDLE;
		}
		else
		{
			EDO_LOG("Try destroy null Texture", Warning, Edo.RHI.VK.Texture);
		}

		// Memory
		if(mMemory != VK_NULL_HANDLE)
		{
			vkFreeMemory(_device.Get(), mMemory, nullptr);

			EDO_LOG(L"Destroy Image Memory success.", Verbose, Edo.RHI.VK.Texture, mMemory);

			mMemory = VK_NULL_HANDLE;
		}
		else
		{
			EDO_LOG("Try destroy null Image Memory", Warning, Edo.RHI.VK.Texture);
		}
	}

// ##############################################################

#endif // EDO_RHI_VK


// ##############################################################################################################################
// #														GL																	#
// ##############################################################################################################################
#if EDO_RHI_GL
#endif // EDO_RHI_GL


// ##############################################################################################################################
// #														CPU																	#
// ##############################################################################################################################
#if EDO_RHI_CPU
#endif // EDO_RHI_CPU


// ##############################################################################################################################
#endif // EDO_RHI_IMPLEMENTATION
}

#endif // EDO_SH_RHI_GUARD
