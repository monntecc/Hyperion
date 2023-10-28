target("Glad")
    set_kind("static")
    set_languages("c11")
    set_group("Dependecies")

    -- Header files
    add_headerfiles(
        "include/glad/glad.h",
        "include/KHR/khrplatform.h"
    )

    -- Source files
    add_files(
        "src/glad.c"
    )

    -- Include directories
    add_includedirs("include", { public = true })

    -- Windows specific settings
    if is_plat("windows") then
        add_syslinks("user32", "gdi32")
        add_defines("_CRT_SECURE_NO_WARNINGS")
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
