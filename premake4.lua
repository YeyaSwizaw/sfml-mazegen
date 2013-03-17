solution "MazeViewer"
	configurations { "debug", "release" }

project "mazeview"
	kind "ConsoleApp"
	language "C++"
	files { "src/**" }
	links { "sfml-system", "sfml-window", "sfml-graphics" }
	objdir "build/obj"
	buildoptions { "-std=c++11" }

	configuration "debug"
		flags { "Symbols", "ExtraWarnings" }

	configuration "release"
		flags { "Optimize" }

