workspace "OpenGL"

architecture "x86"
location "../"
staticruntime "off"

configurations{
	"Debug",
	"Release",
}

platforms{
	"x86",
}

project "OpenGL"
	location "../"
	language "C++"
	cppdialect "C++17"
	kind "ConsoleApp"

	targetdir "../bin/%{cfg.buildcfg}_%{cfg.platform}"
	objdir "../bin/obj/%{cfg.buildcfg}_%{cfg.platform}"

	includedirs{
		"../vendor/GLFW/include",
		"../vendor/GLEW/include",
	}

	libdirs{
		"../vendor/GLFW/lib",
		"../vendor/GLEW/lib",
	}

	links{
		"glfw3.lib",
		"opengl32.lib",
		"glew32s.lib",
	}

	files{
		"../main.cpp",
	}

	defines "GLEW_STATIC"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"
			