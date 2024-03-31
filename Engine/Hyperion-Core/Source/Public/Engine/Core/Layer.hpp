#pragma once

#include "Engine/Core/Base.hpp"
#include "Engine/Core/Timestep.hpp"

#include "Engine/Events/Event.hpp"

namespace Hyperion
{
	class HYPERION_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}