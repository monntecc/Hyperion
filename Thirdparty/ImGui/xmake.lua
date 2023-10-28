target("ImGui")
    set_kind("static")
    set_languages("cxx17")
    set_group("Dependecies")

    -- Include dirs
    add_includedirs(".", {public = true})

    -- Header files
    add_headerfiles(
        "imconfig.h",
        "imgui.h",
        "imgui_internal.h",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h"
    )

    -- Source files
    add_files(
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_tables.cpp",
        "imgui_widgets.cpp",
        "imgui_demo.cpp"
    )

    -- Windows specific settings
    if is_plat("windows") then
        add_defines("_CRT_SECURE_NO_WARNINGS")
    end

    -- Linux specific settings
    if is_plat("linux") then
        add_cxxflags("-fPIC")
    end

    -- Debug configuration
    if is_config("debug") then
        set_symbols("debug")
        set_runtime("debug")
    end

    -- Release configuration
    if is_config("release") then
        set_optimize("fastest")
        set_runtime("release")
    end

    -- Distribution configuration
    if is_config("dist") then
        set_optimize("fastest")
        set_runtime("release")
        set_symbols("off")
    end
