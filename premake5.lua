workspace "2DGame"
	  location "prj"
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


outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.platform}"

	  project "App"
	  	  kind "ConsoleApp"
		  language "C++"
		  cppdialect "C++17"

		  targetdir("%{wks.location}/build/bin" .. outputdir .. "/%{prj.name}")
		  objdir ("%{wks.location}/build/bin-int" .. outputdir .. "/%{prj.name}")

		  files
		  {
		  	"src/**.h",
			"src/**.cpp"
		  }

		  filter "system:windows"
		  systemversion "latest"

		  filter "configurations:Debug"
		  	 defines "DEBUG"
			 runtime "Debug"
			 symbols "on"
        		 optimize "on"

		  filter "configurations:Release"
			 defines "RELEASE"
			 runtime "Release"
			 optimize "on"

		  filter "configurations:Dist"
		  	 defines "DIST"
			 runtime "Release"
			 optimize "on" 