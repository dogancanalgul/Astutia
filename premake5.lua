workspace "Astutia"    
    architecture "x64"
    configurations { "Debug", "Release" }

-- Include directories relative to root folder (solution directory)
    IncludeDir = {}
    IncludeDir["GLFW"] = "Dependencies/GLFW/include"
    IncludeDir["Glad"] = "Dependencies/Glad/include"
   -- IncludeDir["glm"] = "Dependencies/glm"

    group "Dependencies"
        include "Dependencies/GLFW"
        include "Dependencies/Glad"
    group ""

    project "Astutia"
        location "Astutia"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin-int/%{cfg.buildcfg}"

        files
	    {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
	    }

        includedirs
        {
            "%{prj.name}/src",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
          --  "%{IncludeDir.glm}"
        }

        links 
        { 
            "GLFW",
            "Glad",
            "opengl32.lib"
        }
        filter "system:windows"
		    systemversion "latest"

		defines
		{
		}

        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            runtime "Release"
            optimize "on"
