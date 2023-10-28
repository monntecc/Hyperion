target("stb_image")
    set_kind("static")
    set_languages("c17")
    set_group("Dependecies")
    
    -- Include dirs
    add_includedirs("./", {public = true})
    
    -- Header files
    add_headerfiles("./stb_image.h")
    
    -- Add source files
    add_files("./stb_image.cpp")
    
    -- Compiler flags
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