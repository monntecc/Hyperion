#pragma once

#include "Runtime/Core/Base.hpp"
#include "Runtime/Core/Window.hpp"
#include "Runtime/Core/LayerStack.hpp"

#include "Runtime/Events/ApplicationEvent.hpp"
#include "Runtime/Events/Event.hpp"

#include "Runtime/UI/ImGuiLayer.hpp"

int main(int argc, char** argv);

namespace Hyperion {

	class HYPERION_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }
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

