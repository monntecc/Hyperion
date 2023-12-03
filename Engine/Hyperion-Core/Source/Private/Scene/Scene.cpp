#include "hrpch.hpp"

#include "Runtime/Scene/Scene.hpp"
#include "Runtime/Scene/Entity.hpp"
#include "Runtime/Scene/Components.hpp"

#include "Runtime/Renderer/Renderer2D.hpp"

namespace Hyperion {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Unnamed entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		const auto group = m_Registry.group<TransformComponent, SpriteRendererComponent>();
		for (const auto entity : group)
		{
			auto& transform = group.get<TransformComponent>(entity);
			auto& sprite = group.get<SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(static_cast<glm::mat4&>(transform), sprite.Color);
		}
	}
}
