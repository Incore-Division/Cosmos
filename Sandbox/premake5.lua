project "Sandbox"
    kind "ConsoleApp"
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
        "%{IncludeList.Sandbox}",
        "%{IncludeList.VULKAN}",
        "%{IncludeList.GLFW}",
        "%{IncludeList.GLM}"
    }

    links
    {
        "Engine"
    }

    filter "configurations:Debug"
        defines { "SANDBOX_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "SANDBOX_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "system:windows"
        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
        }

        disablewarnings
        {
            "4251"
        }