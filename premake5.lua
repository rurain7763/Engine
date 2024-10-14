workspace "Engine"
    architecture "x64"
    configurations { 
        "Debug", 
        "Release"
    }

    includedirs {
        "./engine/src/core",
        "./vendor/spdlog/include",
        "./vendor/GLFW/include"
    }

    startproject "sandbox"

project "engine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}/sandbox"
    objdir "bin_obj/%{cfg.buildcfg}/%{cfg.architecture}/engine"

    files {
        "./engine/src/**.h",
        "./engine/src/**.cpp",
    }
    
    filter "system:macosx"
        pchheader "./engine/src/core/pch.h"

        defines  {
            "PLATFORM_MAC",
            "BUILD_DLL"
        }

        libdirs {
            "./vendor/GLFW/lib-arm64"
        }    

        links {
            "glfw3",
            "OpenGL.framework",
            "Cocoa.framework",
            "IOkit.framework"
        }

    filter "system:windows"
        pchheader "pch.h"
        pchsource "./engine/src/core/pch.cpp"

        defines  {
            "PLATFORM_WINDOWS",
            "BUILD_DLL"
        }

        libdirs {
            "./vendor/GLFW/lib-vc2022"
        }

        links {
            "glfw3",
            "opengl32"
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
        "./engine/src/core"
    }

    files {
        "./sandbox/src/**.h",
        "./sandbox/src/**.cpp"
    }

    filter "system:macosx"
        defines  {
            "PLATFORM_MAC"
        }

    filter "system:windows"
        defines  {
            "PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        symbols "On"

    filter "configurations:Release"
        optimize "On"



