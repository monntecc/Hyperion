#include "Sandbox/Layer/Sandbox2DLayer.hpp"

#include <Tracy.hpp>

class HyperionSandbox final : public Hyperion::Application
{
public:
	HyperionSandbox()
	{
		PushLayer(new Sandbox2DLayer());
	}

	~HyperionSandbox() override = default;

};

Hyperion::Application* Hyperion::CreateApplication()
{
	return new HyperionSandbox();
}

int main(int argc, char** argv)
{
	Hyperion::Log::Init();

	ZoneScoped;

	const auto app = Hyperion::CreateApplication();
	app->Run();
	delete app;

#ifdef HR_PLATFORM_WINDOWS
    return FALSE;
#else
    return 0;
#endif
}
