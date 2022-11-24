project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir(dir)
    objdir(obj)

    files
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs
    {
        "%{IncludeList.Engine}",
        "%{IncludeList.VULKAN}",
        "%{IncludeList.GLFW}",
        "%{IncludeList.GLM}"
    }

    links
    {
        "GLM",
        "GLFW",
        "%{LibraryList.VULKAN}"
    }
    
    filter "configurations:Debug"
        defines { "ENGINE_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "ENGINE_RELEASE" }
        runtime "Release"
        optimize "Full"

    linkoptions { "-IGNORE:LNK4006" }