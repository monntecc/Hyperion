#pragma once

#include "Hyperion.hpp"

namespace Hyperion {

	class ViewportWidget
	{
	public:
		ViewportWidget();

		void Init();
		void Draw();
		void Update();

		void BindFrameBuffer();
		void UnbindFrameBuffer();

		void Resize(const glm::vec2& size) { m_ViewportSize = size; }
		const glm::vec2& GetSize() const { return m_ViewportSize; }

		bool IsFocused() const { return m_ViewportFocused; }
		bool IsHovered() const { return m_ViewportHovered; }
	private:
		Ref<FrameBuffer> m_FrameBuffer;

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	};

}