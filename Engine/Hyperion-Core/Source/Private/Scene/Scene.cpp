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
		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			const auto group = m_Registry.view<TransformComponent, CameraComponent>();
			for (const auto entity : group)
			{
				auto& transform = group.get<TransformComponent>(entity);
				auto& camera = group.get<CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			const auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (const auto entity : group)
			{
				auto& transform = group.get<TransformComponent>(entity);
				auto& sprite = group.get<SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform.Transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}

	}
}
