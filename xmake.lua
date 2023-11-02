set_project("HyperionEngine")
set_defaultarchs("x64")
set_defaultmode("debug")
set_policy("check.auto_ignore_flags", false)

-- Set build, run, object directories
set_config("buildir", "binaries")
set_targetdir("$(projectdir)/binaries/target/$(host)/$(arch)/$(mode)")
set_objectdir("$(projectdir)/binaries/obj/$(host)/$(arch)/$(mode)")
set_dependir("$(projectdir)/binaries/deps/$(host)/$(arch)/$(mode)")

option("engine-version")
    set_default("0.0.0")
    set_showmenu(true)
    add_defines("VERSION=\"$(engine-version)\"")

-- Include third-party libraries
includes("Thirdparty/spdlog/xmake.lua")
includes("Thirdparty/glm/xmake.lua")
includes("Thirdparty/Glad/xmake.lua")
includes("Thirdparty/GLFW/xmake.lua")
includes("Thirdparty/ImGui/xmake.lua")
includes("Thirdparty/stb_image/xmake.lua")
includes("Thirdparty/tracy/xmake.lua")

-- Include internal libraries
includes("Engine/Source/Runtime/xmake.lua")
includes("Engine/Source/Editor/xmake.lua")