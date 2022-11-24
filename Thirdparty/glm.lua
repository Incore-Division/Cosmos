project "GLM"
    location "glm"
    kind "None"
    language "C++"
    cppdialect "C++11"
    warnings "Off"
    
    targetdir (Bin)
    objdir (Obj)

    files
    {
        "glm/**.hpp",
        "glm/**.h"
    }

    includedirs
    {
        "glm/"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"