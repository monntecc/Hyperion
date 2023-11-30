#pragma once

#include "Runtime/Renderer/FrameBuffer.hpp"

namespace Hyperion {

	class HYPERION_API OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& specification);
		~OpenGLFrameBuffer() override;

		void Invalidate(); // Re-creating frame buffer

		void Bind() override;
		void Unbind() override;

		const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
		uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FrameBufferSpecification m_Specification;
	};

}