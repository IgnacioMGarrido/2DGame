include "utils/functions.lua"
workspace "2DGame"
	  location "./"
	  configurations {"Debug", "Release"}
	  architecture "x64"
	  platforms {"x64"}

	  configurations
	  {
		"Debug",
              	"Release",
              	"Dist"
	  }

	  flags
    	  {
		"MultiProcessorCompile"
    	  }

	  AddProject("Game")
	  