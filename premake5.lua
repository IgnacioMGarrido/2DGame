workspace "2DGame"
	  configurations {"Debug", "Release", "Dist"}
	  architecture "x64"
	  platforms {"x64"}
	  startproject "Game"

	  filter "system:windows"
	  	 buildoptions {"/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}
		 

	  flags
    	  {
		"MultiProcessorCompile"
    	  }

  OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

  group "Core"
 	include "Engine/Engine.lua"
  group ""

  include "Game/Game.lua"
	  