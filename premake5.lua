workspace "Engine"
    architecture "x64"
    configurations { 
        "Debug", 
        "Release"
    }

    includedirs {
        "./engine/src/core"
    }

    startproject "sandbox"

project "engine"
    location "engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}/sandbox"
    objdir "bin_obj/%{cfg.buildcfg}/%{cfg.architecture}/engine"

    includedirs {
        "./engine/vendors/glm",
        "./engine/vendors/GLFW/include",
        "./engine/vendors/glad/include",
        "./engine/vendors/imgui",
        "./engine/vendors/imgui/backends",
        "./engine/vendors/spdlog/include"
    }

    files {
        "./engine/src/**.h",
        "./engine/src/**.cpp",
        "./engine/vendors/glad/src/glad.c",
        "./engine/vendors/imgui/*.h",
        "./engine/vendors/imgui/*.cpp",
        "./engine/vendors/imgui/backends/imgui_impl_glfw.*",
        "./engine/vendors/imgui/backends/imgui_impl_opengl3.*"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }
    
    filter "system:macosx"
        defines  {
            "PLATFORM_MAC"
        }

        libdirs {
            "./engine/vendors/GLFW/lib-arm64"
        }    

        links {
            "glfw3",
            "opengl32",
            "OpenGL.framework",
            "Cocoa.framework",
            "IOkit.framework"
        }

    filter "system:windows"
        systemversion "latest"
        defines  {
            "PLATFORM_WINDOWS"
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
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {
            "RELEASE"
        }
        runtime "Release"
        optimize "On"

project "sandbox"
    location "sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}/sandbox"
    objdir "bin_obj/%{cfg.buildcfg}/%{cfg.architecture}/sandbox"
    
    includedirs {
        "./engine/src",
        "./engine/src/core",
        "./engine/vendors/glm"
    }
    
    files {
        "./sandbox/src/**.h",
        "./sandbox/src/**.cpp"
    }

    links {
        "engine"
    }

    filter "system:macosx"
        defines  {
            "PLATFORM_MAC"
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
            "PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {
            "RELEASE"
        }
        runtime "Release"
        optimize "On"



