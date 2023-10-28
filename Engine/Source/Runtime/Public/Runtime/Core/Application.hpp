#pragma once

#include "Runtime/Core/Core.hpp"
#include "Runtime/Core/Window.hpp"
#include "Runtime/Core/LayerStack.hpp"

#include "Runtime/Events/ApplicationEvent.hpp"
#include "Runtime/Events/Event.hpp"

#include "Runtime/UI/ImGuiLayer.hpp"

namespace Hyperion {

	class HYPERION_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
};

