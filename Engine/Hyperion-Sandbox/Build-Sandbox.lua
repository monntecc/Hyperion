project "Hyperion-Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	files { "Source/HyperionSandbox.cpp", "Source/Private/**.cpp", "Source/Public/**.hpp" }

	includedirs
	{
        -- Internal headers
        "Source/Public",

        -- External libraries and core headers
		"%{wks.location}/Engine/Hyperion-Core/Source",
		"%{wks.location}/Engine/Hyperion-Core/Source/Public",
		"%{wks.location}/Engine/Hyperion-Core/External",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Tracy}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}"
	}

	defines { "HR_DYNAMIC_LINK" }

	links { "Hyperion-Core" }

	targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "HR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HR_RELEASE"
		runtime "Release"
		optimize "on"