workspace "Engine"
    architecture "x64"
    configurations { 
        "Debug", 
        "Release"
    }

    includedirs {
        "./engine/src/core",
        "./vendor"
    }

    startproject "sandbox"

project "engine"
    location "engine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}/sandbox"
    objdir "bin_obj/%{cfg.buildcfg}/%{cfg.architecture}/engine"

    includedirs {
        "./engine/vendors/GLFW/include",
        "./engine/vendors/glm/glm/**.hpp",
        "./engine/vendors/imgui",
        "./engine/vendors/imgui/backends",
        "./engine/vendors/spdlog/include"
    }

    files {
        "./engine/src/**.h",
        "./engine/src/**.cpp",
        "./engine/vendors/imgui/*.h",
        "./engine/vendors/imgui/*.cpp",
        "./engine/vendors/imgui/backends/imgui_impl_glfw.*",
        "./engine/vendors/imgui/backends/imgui_impl_opengl3.*"
    }
    
    filter "system:macosx"
        defines  {
            "PLATFORM_MAC",
            "BUILD_DLL"
        }

        libdirs {
            "./engine/vendors/GLFW/lib-arm64"
        }    

        links {
            "glfw3",
            "OpenGL.framework",
            "Cocoa.framework",
            "IOkit.framework"
        }

    filter "system:windows"
        systemversion "latest"
        defines  {
            "PLATFORM_WINDOWS",
            "BUILD_DLL"
        }

        libdirs {
            "./engine/vendors/GLFW/lib-vc2022"
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
        defines {
            "RELEASE"
        }
        optimize "On"

project "sandbox"
    location "sandbox"
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
        systemversion "latest"

        defines  {
            "PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        symbols "On"

    filter "configurations:Release"
        defines {
            "RELEASE"
        }
        optimize "On"



