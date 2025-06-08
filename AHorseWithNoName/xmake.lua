local projectName = "AHorseWithNoName"

target(projectName)
	add_rules("ue4ss.mod")

	add_includedirs("include", "include/Altar", "include/Engine", "include/Config")
	add_headerfiles("include/**.h", "include/Altar/**.h", "include/Engine/**.h")

	add_files("src/**.cpp", "src/Altar/**.cpp", "src/Engine/**.cpp", "src/Config/**.cpp")
