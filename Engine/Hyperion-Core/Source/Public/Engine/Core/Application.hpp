#pragma once

#include "Engine/Core/Base.hpp"
#include "Engine/Core/Window.hpp"
#include "Engine/Core/LayerStack.hpp"

#include "Engine/Events/ApplicationEvent.hpp"
#include "Engine/Events/Event.hpp"

#include "Engine/UI/ImGuiLayer.hpp"

int main(int argc, char** argv);

namespace Hyperion {

	class HYPERION_API Application
	{
	public:
		Application(const std::string& name = "Hyperion Application");
		virtual ~Application();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }

		void Shutdown();
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		void Run();
		
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	
		static Application* s_Instance;

		friend int ::main(int argc, char** argv);
	};

	// To be defined in client
	Application* CreateApplication();
};

