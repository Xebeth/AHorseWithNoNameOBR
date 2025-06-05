local projectName = "AHorseWithNoName"

target(projectName)
	add_rules("ue4ss.mod")

	add_includedirs("include", "include/Altar", "include/Engine")
	add_headerfiles("include/**.h", "include/Altar/**.h", "include/Engine/**.h")
	add_files("src/dllmain.cpp", "src/HorseHandler.cpp", "src/Altar/VPairedPawn.cpp", "src/Altar/VPairedCharacter.cpp",
			  "src/Altar/VAltarPlayerController.cpp", "src/Altar/TESForm.cpp", "src/Altar/VTESObjectRefComponent.cpp",
			  "src/Altar/UAltarCheatManager.cpp",  "src/Engine/PlayerController.cpp", "src/Engine/UCheatManager.cpp",
			  "src/Altar/TESActorBase.cpp")