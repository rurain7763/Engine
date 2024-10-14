workspace "Engine"
    architecture "x64"
    configurations { 
        "Debug", 
        "Release"
    }

project "engine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}/sandbox"
    objdir "bin_obj/%{cfg.buildcfg}/%{cfg.architecture}/engine"

    pchheader "./engine/src/core/pch.h"

    includedirs {
        "./vendor/spdlog/include"
    }

    files {
        "./engine/src/*.h",
        "./engine/src/*.cpp",
        "./engine/src/core/*.cpp"
    }
    
    filter "system:macosx"
        defines  {
            "PLATFORM_MAC",
            "BUILD_DLL"
        }

    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        symbols "On"

    filter "configurations:Release"
        optimize "On"

project "sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}/sandbox"
    objdir "bin_obj/%{cfg.buildcfg}/%{cfg.architecture}/sandbox"
    links "engine"

    includedirs {
        "./engine/src",
        "./vendor/spdlog/include"
    }

    files {
        "./sandbox/src/*.h",
        "./sandbox/src/*.cpp"
    }

    filter "system:macosx"
        defines  {
            "PLATFORM_MAC"
        }

    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        symbols "On"

    filter "configurations:Release"
        optimize "On"


