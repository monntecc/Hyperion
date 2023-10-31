// #include "Editor/Layer/ExampleLayer.hpp"
#include "Editor/Layer/Sandbox2DLayer.hpp"

class Editor final : public Hyperion::Application
{
public:
	Editor()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2DLayer());
	}

	~Editor() override = default;

};

Hyperion::Application* Hyperion::CreateApplication()
{
	return new Editor();
}

int main(int argc, char** argv)
{
	Hyperion::Log::Init();

	HR_PROFILE_BEGIN_SESSION("Startup", "HyperionProfile-Startup.json");
	const auto app = Hyperion::CreateApplication();
	HR_PROFILE_END_SESSION();
	
	HR_PROFILE_BEGIN_SESSION("Runtime", "HyperionProfile-Runtime.json");
	app->Run();
	HR_PROFILE_END_SESSION();
	
	HR_PROFILE_BEGIN_SESSION("Shutdown", "HyperionProfile-Shutdown.json");
	delete app;
	HR_PROFILE_END_SESSION();
	
	return FALSE;
}
