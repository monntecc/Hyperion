#pragma once

#include "Runtime/Core/Base.hpp"

namespace Hyperion {

	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		// FrameBuffer format
		uint32_t Samples = 1;

		// Is this frame buffer need to be rendered to the swapchain ?
		bool SwapChainTarget = false; // false - glBindFramebuffer(0)
	};

	class HYPERION_API FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& specification);

		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

}
