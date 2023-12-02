#include "hrpch.hpp"

#include "Runtime/Scene/Scene.hpp"
#include "Runtime/Scene/Components.hpp"

#include "Runtime/Renderer/Renderer2D.hpp"

namespace Hyperion {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(Timestep timestep)
	{
		const auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (const auto entity : group)
		{
			auto& transform = group.get<TransformComponent>(entity);
			auto& sprite = group.get<SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}
