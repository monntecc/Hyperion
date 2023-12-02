project "Hyperion-Core"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	pchheader "hrpch.hpp"
	pchsource "Source/hrpch.cpp"

	files
	{
        -- Internal source and header filse
        "Source/Hyperion.hpp",
        "Source/hrpch.hpp",
        "Source/hrpch.cpp",

		"Source/Public/**.hpp",
		"Source/Private/**.cpp",

        -- External libraries
		"External/stb_image/**.h",
		"External/stb_image/**.cpp",
		"External/glm/glm/**.hpp",
		"External/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"HR_DYNAMIC_LINK",
		"HR_BUILD_DLL"
	}

	includedirs
	{
        "Source",
		"Source/Public",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.Tracy}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
        "Tracy",
		"opengl32.lib",
	}

	postbuildcommands
	{
		-- Copy dll to editor project
		("IF NOT EXIST %{wks.location}/Binaries/" .. OutputDir .. "/Hyperion-Editor mkdir %{wks.location}/Binaries/" .. OutputDir .. "/Hyperion-Editor"),
		("{COPY} %{cfg.buildtarget.relpath} \"%{wks.location}/Binaries/" .. OutputDir .. "/Hyperion-Editor/\""),

		-- Copy dll to sandbox project
		("IF NOT EXIST %{wks.location}/Binaries/" .. OutputDir .. "/Hyperion-Sandbox mkdir %{wks.location}/Binaries/" .. OutputDir .. "/Hyperion-Sandbox"),
		("{COPY} %{cfg.buildtarget.relpath} \"%{wks.location}/Binaries/" .. OutputDir .. "/Hyperion-Sandbox/\"")
	}

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