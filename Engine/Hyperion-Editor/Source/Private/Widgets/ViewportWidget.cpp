#include "Editor/Widgets/ViewportWidget.hpp"

namespace Hyperion {

	ViewportWidget::ViewportWidget()
	{
	}

	void ViewportWidget::Init()
	{
		FrameBufferSpecification specification = {};
		specification.Width = 1280;
		specification.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(specification);
	}

	void ViewportWidget::Draw()
	{
		ImGui::Begin("Viewport");
		{
			m_ViewportFocused = ImGui::IsWindowFocused(); // is window focused?
			m_ViewportHovered = ImGui::IsWindowHovered(); // is mouse hovered over active window?
			Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered); // if viewport not focused, block events
		}

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
		ImGui::End();
	}

	void ViewportWidget::Update()
	{

	}

	void ViewportWidget::UnbindFrameBuffer()
	{
		m_FrameBuffer->Unbind();
	}

	void ViewportWidget::BindFrameBuffer()
	{
		m_FrameBuffer->Bind();
	}

}