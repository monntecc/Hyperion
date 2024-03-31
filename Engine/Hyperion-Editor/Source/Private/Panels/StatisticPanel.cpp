#include "Editor/Panels/StatisticPanel.hpp"

namespace Hyperion {

	StatisticPanel::StatisticPanel()
	{
	}

	void StatisticPanel::Draw()
	{
        ImGui::Begin("Statistics");

        const auto stats = Renderer2D::GetStats();

        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

        ImGui::End();
	}
}
