#pragma once

#include "Runtime/Renderer/FrameBuffer.hpp"

#include <glm/glm.hpp>

namespace Hyperion {

	class HYPERION_API OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& specification);
		~OpenGLFrameBuffer() override;

		void Invalidate(); // Re-creating frame buffer

		void Bind() override;
		void Unbind() override;
		void Resize(uint32_t width, uint32_t height) override;

		const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
		uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

	private:
		void Delete() const;

		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		FrameBufferSpecification m_Specification;
	};

}