target("Editor")
    set_kind("binary")
    set_default(true)
    set_languages("cxx20")
    set_arch("x64")
    set_warnings("all")
    set_group("Source")
    
    -- Set running directory
    set_rundir("$(projectdir)/Engine/Source/Editor")

    -- Add mode rules
    add_rules("mode.release", "mode.debug")

    -- Add source files
    add_files("./Private/**/**.cpp")
    add_files("./Editor.cpp")

    -- Add header files
    add_headerfiles("./Public/**/**.hpp")

    -- Add include dirs
    add_includedirs("$(projectdir)/Engine/Source/Runtime/Public")
    add_includedirs("$(projectdir)/Engine/Source/Runtime")
    add_includedirs("./Public")
    
    -- Add extra files
    add_extrafiles("Assets/Textures/*.png")

    -- Add deps
    add_deps("Runtime", "glm", "spdlog") 

    -- Set defines and system specific settings
    if is_plat("windows") then
        add_defines("HR_PLATFORM_WINDOWS")
    end

    -- Set configurations
    if is_mode("debug") then
        add_defines("HR_DEBUG")
        set_symbols("debug")
        set_optimize("none")
    end

    if is_mode("release") then
        add_defines("HR_RELEASE")
        set_symbols("hidden")
        set_optimize("fastest")
    end