#include "Editor/Layer/ExampleLayer.hpp"

class Editor final : public Hyperion::Application
{
public:
	Editor()
	{
		PushLayer(new ExampleLayer());
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
	HR_CORE_WARN("Initialized Log!");
	HR_INFO("Hello from Hyperion!");

	const auto app = Hyperion::CreateApplication();
	app->Run();
	delete app;

	return FALSE;
}
