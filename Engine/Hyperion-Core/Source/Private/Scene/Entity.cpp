#include "hrpch.hpp"

#include "Engine/Scene/Entity.hpp"
#include "Engine/Scene/Scene.hpp"

namespace Hyperion {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}