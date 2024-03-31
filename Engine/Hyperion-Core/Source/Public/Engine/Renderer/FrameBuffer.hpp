#pragma once

#include "Engine/Core/Base.hpp"

#include <glm/glm.hpp>

namespace Hyperion {

	struct FrameBufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		// FrameBuffer format
		uint32_t Samples = 1;

		// Is this frame buffer need to be rendered to the swapchain ?
		bool SwapChainTarget = false; // false - glBindFramebuffer(0)
	};

	class HYPERION_API FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& specification);

		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;
	};

}
