#include "hrpch.hpp"

#include "Editor/Layer/EditorLayer.hpp"

#include <Tracy.hpp>

namespace Hyperion {

	class HyperionEditor final : public Application
	{
	public:
		HyperionEditor()
			: Application("Hyperion Editor")
		{
			PushLayer(new EditorLayer());
		}

		~HyperionEditor() override = default;

	};

	Application* CreateApplication()
	{
		return new HyperionEditor();
	}

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
