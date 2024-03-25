#pragma once

#include <glm/glm.hpp>

#include "Runtime/Renderer/Camera.hpp"
#include "Runtime/Scene/SceneCamera.hpp"
#include "Runtime/Scene/ScriptableEntity.hpp"

namespace Hyperion {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		explicit TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		explicit TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		explicit operator glm::mat4& () { return Transform; }
		explicit operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		explicit SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene

		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		std::function<void()> InstantiateFunction;
		std::function<void()> DestroyInstanceFunction;

		std::function<void(ScriptableEntity*)> OnCreateFunction;
		std::function<void(ScriptableEntity*)> OnDestroyFunction;
		std::function<void(ScriptableEntity*, Timestep)> OnUpdateFunction;

		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() { Instance = new T(); };
			DestroyInstanceFunction = [&]() { delete reinterpret_cast<T*>(Instance); Instance = nullptr; };

			OnCreateFunction = [](ScriptableEntity* instance) { (reinterpret_cast<T*>(instance))->OnCreate(); };
			OnDestroyFunction = [](ScriptableEntity* instance) { (reinterpret_cast<T*>(instance))->OnDestroy(); };
			OnUpdateFunction = [](ScriptableEntity* instance, Timestep ts) { (reinterpret_cast<T*>(instance))->OnUpdate(ts); };
		}
	};

}