target("Tracy")
    set_kind("static")
    set_languages("cxx17")
    set_group("Dependecies")

    -- Include dirs
    add_includedirs(".", {public = true})

    -- Header files
    add_headerfiles(
        "./**.hpp"
    )
    
    -- Source files
    add_files(
        "./TracyClient.cpp"
    )
    
    -- Add defines
    add_defines("TRACY_ENABLE")

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