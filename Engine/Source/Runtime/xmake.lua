target("Runtime")
    set_kind("static")
    set_languages("cxx20")
    set_arch("x64")
    set_warnings("all")
    set_group("Source")
    
    -- Set running directory
    set_rundir("$(projectdir)/Engine/Source/Runtime")

    -- Add mode rules
    add_rules("mode.release", "mode.debug")

    -- Set Pre-compiled header
    set_pcxxheader("./pch.hpp")

    -- Add files
    add_files("./Private/**/**.cpp")
    add_files("./pch.cpp")

    -- Add header files
    add_headerfiles("./Public/**/**.hpp")
    add_headerfiles("./Hyperion.hpp")
    add_headerfiles("./pch.hpp")

    -- Add include directories
    add_includedirs("./")
    add_includedirs("./Public")

    -- Add defines
    add_defines("_CRT_SECURE_NO_WARNINGS")
    add_defines("HR_PLATFORM_WINDOWS")
    add_defines("HR_BUILD_DLL")
    add_defines("GLFW_INCLUDE_NONE")

    -- Link libraries
    add_linkdirs("$(projectdir)/binaries/target/$(host)/$(arch)/$(mode)")
    add_deps("ImGui", "GLFW", "Glad", "stb_image", "glm", "spdlog")
    add_syslinks("opengl32")

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

    -- Set system version on Windows
    if is_plat("windows") then
        add_defines("HR_PLATFORM_WINDOWS")
    end
