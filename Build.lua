-- premake5.lua
include "Dependecies.lua"

workspace "Hyperion-Engine"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Hyperion-Editor"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Engine/Hyperion-Core/Build-Core.lua"
group ""

group "Dependecies"
	include "Engine/Hyperion-Core/External/GLFW/Build.lua"
	include "Engine/Hyperion-Core/External/ImGui/Build.lua"
	include "Engine/Hyperion-Core/External/Glad/Build.lua"
	include "Engine/Hyperion-Core/External/Tracy/Build.lua"
group ""

include "Engine/Hyperion-Editor/Build-Editor.lua"
include "Engine/Hyperion-Sandbox/Build-Sandbox.lua"