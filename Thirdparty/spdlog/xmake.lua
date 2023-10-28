target("spdlog")
    set_kind("static")
    set_languages("c17")
    set_group("Dependecies")
    
    -- Add source files
    add_files("./src/**.cpp")
    
    -- Add header files
    add_headerfiles("./include/spdlog/**.h")
    
    -- Include dirs
    add_includedirs("./include", {public = true})
    
    -- Add defines
    add_defines("SPDLOG_COMPILED_LIB")
    
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