workspace "Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

group "Engine"

project "Engine"
	location "engine"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")
	
	pchheader "engine_pch.h"
	pchsource "engine/precompiled/engine_pch.cpp"
	
	files
	{
		"%{prj.name}/enginecode/**.h",
		"%{prj.name}/enginecode/**.cpp",
		"engine/precompiled/engine_pch.h",
		"engine/precompiled/engine_pch.cpp",
		"vendor/stb_image/stb_image.cpp"
	}

	includedirs
	{
		"%{prj.name}/enginecode/",
		"%{prj.name}/enginecode/include/independent",
		"%{prj.name}/precompiled/",
		"vendor/spdlog/include",
		"vendor/glfw/include",
		"vendor/Glad/include",
		"vendor/glm/",
		"vendor/stb_image",
		"vendor/freetype2/include",
		"vendor/json/single_include/nlohmann",
		"vendor/bullet3-2.89/src",
		"vendor/FMOD/core/inc",
		"vendor/FMOD/fsbank/inc",
		"vendor/FMOD/studio/inc"
	}
	
	libdirs 
	{
		"vendor/bullet3-2.89/bin"
	}
	
	links 
	{
		"GLFW",
		"Glad",
		"Freetype",
		"assimp"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines { "NG_DEBUG", "_DEBUG=1" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/include",
		"engine/enginecode/",
		"engine/enginecode/include/independent",
		"engine/precompiled/",
		"vendor/spdlog/include",
		"vendor/glm/",
		"vendor/json/single_include/nlohmann",
		"vendor/FMOD/core/inc",
		"vendor/FMOD/fsbank/inc",
		"vendor/FMOD/studio/inc"
	}

	libdirs 
	{
		"vendor/bullet3-2.89/bin",
		"vendor/FMOD/core/lib/x64",
		"vendor/FMOD/fsbank/lib/x64",
		"vendor/FMOD/studio/lib/x64"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

		debugenvs
		{
		"PATH=PATH;../vendor/FMOD/core/lib/x64;../vendor/FMOD/studio/lib/x64"
		}

	filter "configurations:Debug"
		defines { "NG_DEBUG", "_DEBUG=1" }
		runtime "Debug"
		symbols "On"

		links
		{
		"Engine",
		"fmodL_vc.lib",
		"fmodstudioL_vc.lib"
		}

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"

		links
		{
		"Engine",
		"fmod_vc.lib",
		"fmodstudio_vc.lib"
		}

project "Game"
	location "game"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/include",
		"engine/enginecode/",
		"engine/enginecode/include/independent",
		"engine/precompiled/",
		"vendor/spdlog/include",
		"vendor/glm/",
		"vendor/json/single_include/nlohmann",
		"vendor/FMOD/core/inc",
		"vendor/FMOD/fsbank/inc",
		"vendor/FMOD/studio/inc"
	}

	libdirs 
	{
		"vendor/bullet3-2.89/bin",
		"vendor/FMOD/core/lib/x64",
		"vendor/FMOD/fsbank/lib/x64",
		"vendor/FMOD/studio/lib/x64"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

		debugenvs
		{
		"PATH=PATH;../vendor/FMOD/core/lib/x64;../vendor/FMOD/studio/lib/x64"
		}

	filter "configurations:Debug"
		defines { "NG_DEBUG", "_DEBUG=1" }
		runtime "Debug"
		symbols "On"

		links
		{
		"Engine",
		"fmodL_vc.lib",
		"fmodstudioL_vc.lib"
		}

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"

		links
		{
		"Engine",
		"fmod_vc.lib",
		"fmodstudio_vc.lib"
		}

 project "EngineTests"
		location "engineTests"
        kind "ConsoleApp"
        language "C++"
		staticruntime "off"
		systemversion "latest"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("build/" .. outputdir .. "/%{prj.name}")

        files 
		{ 
			"%{prj.name}/include/*.h",
			"%{prj.name}/src/*.cpp",
		}

        includedirs
		{ 
			"%{prj.name}/include/",
			"vendor/googletest/googletest/include",
			"engine/enginecode/",
			"engine/enginecode/include/independent",
			"engine/enginecode/include/platform",
			"engine/precompiled/",
			"vendor/spdlog/include",
			"vendor/glfw/include",
			"vendor/Glad/include",
			"vendor/glm/",
			"vendor/stb_image",
			"vendor/freetype2/include"
			
		}

        links 
		{ 
			"googletest"
		}
		
		filter "configurations:Debug"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			runtime "Release"
			optimize "On"

project "Spike"
	location "spike"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/include",
		"vendor/spdlog/include",
		"vendor/stb_image",
		"vendor/freetype2/include",
		"vendor/glm/",
		"vendor/assimp/include",
		"vendor/Glad/include",
		"vendor/bullet3-2.89/src"
	}
	
	libdirs 
	{
		"vendor/bullet3-2.89/bin"
	}
	
	links 
	{
		"Freetype",
		"assimp",
		"Glad",
		"BulletDynamics_vs2010_x64_debug",
		"BulletCollision_vs2010_x64_debug",
		"LinearMath_vs2010_x64_debug"
	}
	

	defines { "BT_THREADSAFE=1", "BT_USE_DOUBLE_PRECISION" }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines { "NG_DEBUG", "_DEBUG=1" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

group "Vendor"

	include "vendor/glfw"
	include "vendor/googletest"
	include "vendor/Glad"
	include "vendor/freetype2"
	include "vendor/zlib"
	include "vendor/IrrXML"
	include "vendor/assimp"