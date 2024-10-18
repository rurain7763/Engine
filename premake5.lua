workspace "Engine"
    architecture "x64"
    configurations { 
        "Debug", 
        "Release"
    }

    startproject "sandbox"

project "engine"
    location "engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}/engine"
    objdir "bin_obj/%{cfg.buildcfg}/%{cfg.architecture}/engine"

    includedirs {
        "./engine/src/core",
        "./engine/vendors/glm",
        "./engine/vendors/GLFW/include",
        "./engine/vendors/glad/include",
        "./engine/vendors/imgui",
        "./engine/vendors/imgui/backends",
        "./engine/vendors/spdlog/include",
        "./engine/vendors/stb_image",
    }

    files {
        "./engine/src/**.h",
        "./engine/src/**.cpp",
        "./engine/vendors/spdlog/include/**.h",
        "./engine/vendors/glad/include/**",
        "./engine/vendors/glad/src/*.c",
        "./engine/vendors/imgui/*.h",
        "./engine/vendors/imgui/*.cpp",
        "./engine/vendors/imgui/backends/imgui_impl_glfw.*",
        "./engine/vendors/imgui/backends/imgui_impl_opengl3.*",
        "./engine/vendors/stb_image/*.h",
        "./engine/vendors/stb_image/*.cpp"
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

    filter "action:xcode4"
        externalincludedirs {
            "./engine/vendors/spdlog/include"
        }

        xcodebuildsettings {
            ["GENERATE_INFOPLIST_FILE"] = "YES"
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
        "./engine/vendors/glm",
        "./engine/vendors"
    }
    
    files {
        "./sandbox/src/**.h",
        "./sandbox/src/**.cpp"
    }

    libdirs {
        "bin/%{cfg.buildcfg}/%{cfg.architecture}/engine"
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



