project "ImGui"
	kind "StaticLib"
	language "C++"

	files
	{
		"imgui.cpp",
		"imgui_demo.cpp",
		"imgui_draw.cpp",
		"imgui_widgets.cpp",
		"imgui_tables.cpp",
		"imgui_internal.h",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
        "imconfig.h",
		"imgui.h"
	}

	targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "off"
        defines { "IMGUI_API=__declspec(dllexport)" }
        -- postbuildcommands
        -- {
        --	("IF NOT EXIST %{wks.location}/Binaries/" .. OutputDir .. "/Hyperion-Core mkdir %{wks.location}/Binaries/" .. OutputDir .. "/Hyperion-Core"),
        --	("{COPY} %{cfg.buildtarget.relpath} \"%{wks.location}/Binaries/" .. OutputDir .. "/Hyperion-Core/\"")
        -- }

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "off"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
