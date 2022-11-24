workspace "Solution"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    startproject "Sandbox"

    dir = "%{wks.location}/_Build/Bin"
    obj = "%{wks.location}/_Build/Bin/Temp"
    vulkan = os.getenv("VULKAN_SDK")

    IncludeList = {}
    IncludeList["Engine"] = "%{wks.location}/Engine/Source"
    IncludeList["Sandbox"] = "%{wks.location}/Sandbox/Source"
    --
    IncludeList["VULKAN"] = "%{vulkan}/Include"
    IncludeList["GLFW"] = "%{wks.location}/Thirdparty/glfw/include"
    IncludeList["GLM"] = "%{wks.location}/Thirdparty/glm/glm"

    LibraryList = {}
    LibraryList["VULKAN"] = "%{vulkan}/Lib/vulkan-1.lib"

group "Thirdparty"
    include "Thirdparty/glfw.lua"
    include "Thirdparty/glm.lua"
group ""

include "Engine"
include "Sandbox"