#pragma once

#include <entt/entt.hpp>

#include "Runtime/Core/Timestep.hpp"

namespace Hyperion {

	class Entity;

	class HYPERION_API Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep timestep);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}
