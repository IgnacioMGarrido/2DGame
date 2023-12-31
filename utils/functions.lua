
function AddProject(projName)
	 project (projName)
  	  	  kind "ConsoleApp"
	 	  language "C++"
	  	  cppdialect "C++20"
	  
		targetdir ("%{wks.location}/build/bin/" .. "%{cfg.buildcfg}_%{cfg.system}_%{cfg.platform}" .. "/%{prj.name}")
	  	objdir ("%{wks.location}/build/bin-int/" .. "%{cfg.buildcfg}_%{cfg.system}_%{cfg.platform}" .. "/%{prj.name}")

	  	location("%{wks.location}/" .. projName)
	  	files
	  	{
			"%{prj.location}/include/**.h",
			"%{prj.location}/src/**.cpp"
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

end