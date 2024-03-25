#pragma once

#include "Runtime/Core/Base.hpp"
#include "Runtime/Core/Log.hpp"

#include "Runtime/Scene/Scene.hpp"
#include "Runtime/Scene/Entity.hpp"

namespace Hyperion {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}