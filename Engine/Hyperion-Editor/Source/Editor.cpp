// #include "Editor/Layer/ExampleLayer.hpp"
#include "Editor/Layer/Sandbox2DLayer.hpp"

#include <Tracy.hpp>

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

	ZoneScoped;

	const auto app = Hyperion::CreateApplication();
	app->Run();
	delete app;

	return FALSE;
}
