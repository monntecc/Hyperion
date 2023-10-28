set_project("HyperionEngine")
set_defaultarchs("x64")
set_defaultmode("debug")
set_policy("check.auto_ignore_flags", false)

-- Set build, run, object directories
set_config("buildir", "binaries")
set_rundir("$(projectdir)/binaries/target/$(host)/$(arch)/$(mode)")
set_targetdir("$(projectdir)/binaries/target/$(host)/$(arch)/$(mode)")
set_objectdir("$(projectdir)/binaries/obj/$(host)/$(arch)/$(mode)")
set_dependir("$(projectdir)/binaries/deps/$(host)/$(arch)/$(mode)")

option("engine-version")
    set_default("0.0.0")
    set_showmenu(true)
    add_defines("VERSION=\"$(engine-version)\"")

-- Include thirdparty libraries
includes("Thirdparty/Glad/xmake.lua")
includes("Thirdparty/GLFW/xmake.lua")
includes("Thirdparty/ImGui/xmake.lua")

-- Include internal libraries
includes("Engine/Source/Runtime/xmake.lua")
includes("Engine/Source/Editor/xmake.lua")