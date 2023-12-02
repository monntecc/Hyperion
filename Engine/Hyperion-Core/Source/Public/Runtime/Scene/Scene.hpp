#pragma once

#include <entt/entt.hpp>

#include "Runtime/Core/Timestep.hpp"

namespace Hyperion {

	class HYPERION_API Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// TEMP
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep timestep);

	private:
		entt::registry m_Registry;
	};

}
