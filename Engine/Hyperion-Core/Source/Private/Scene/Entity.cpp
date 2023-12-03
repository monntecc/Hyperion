#include "hrpch.hpp"

#include "Runtime/Scene/Entity.hpp"
#include "Runtime/Scene/Scene.hpp"

namespace Hyperion {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}