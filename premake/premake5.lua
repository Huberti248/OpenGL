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
		"../vendor/IMGUI",
		"../vendor/IMGUI/backends/",
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
		"../vendor/IMGUI/imgui.cpp",
		"../vendor/IMGUI/imgui_demo.cpp",
		"../vendor/IMGUI/imgui_draw.cpp",
		"../vendor/IMGUI/imgui_tables.cpp",
		"../vendor/IMGUI/imgui_widgets.cpp",
		"../vendor/IMGUI/backends/imgui_impl_glfw.cpp",
		"../vendor/IMGUI/backends/imgui_impl_opengl3.cpp",
	}

	defines "GLEW_STATIC"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"
			