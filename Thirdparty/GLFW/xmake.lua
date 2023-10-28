target("GLFW")
    set_kind("static")
    set_languages("c17")
    set_group("Dependecies")

    -- Include dirs
    add_includedirs("include", {public = true})

    -- Header files
    add_headerfiles(
        "include/GLFW/glfw3.h",
        "src/internal.h",
        "src/platform.h",
        "src/mappings.h",
        "src/null_platform.h",
        "src/null_joystick.h",
        "include/GLFW/glfw3native.h"
    )

    -- Source files
    add_files(
        "src/context.c",
        "src/init.c",
        "src/input.c",
        "src/monitor.c",
        "src/platform.c",
        "src/vulkan.c",
        "src/window.c",
        "src/egl_context.c",
        "src/osmesa_context.c",
        "src/null_init.c",
        "src/null_monitor.c",
        "src/null_window.c",
        "src/null_joystick.c"
    )

    -- Linux specific files
    if is_plat("linux") then
        add_files(
            "src/x11_init.c",
            "src/x11_monitor.c",
            "src/x11_window.c",
            "src/xkb_unicode.c",
            "src/posix_time.c",
            "src/posix_thread.c",
            "src/glx_context.c",
            "src/linux_joystick.c"
        )
        add_defines("_GLFW_X11")
        if is_mode("debug") then
            add_cflags("-O0", "-g")
        else
            add_cflags("-O2", "-DNDEBUG")
        end
    end

    -- Windows specific files
    if is_plat("windows") then
        add_files(
            "src/win32_init.c",
            "src/win32_module.c",
            "src/win32_joystick.c",
            "src/win32_monitor.c",
            "src/win32_time.c",
            "src/win32_thread.c",
            "src/win32_window.c",
            "src/wgl_context.c"
        )
        add_headerfiles(
            "src/win32_time.h", 
            "src/win32_thread.h")
        add_defines("_GLFW_WIN32", "_CRT_SECURE_NO_WARNINGS")
        add_links("user32", "shell32")
        if is_mode("debug") then
            add_cxflags("-O0", "-g")
        else
            add_cxflags("-O2", "-DNDEBUG")
        end
    end

    -- Compiler flags for both Linux and Windows
    if is_mode("debug") then
        add_cxflags("-D_DEBUG")
    else
        add_cxflags("-DNDEBUG")
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
