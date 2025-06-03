#pragma once

namespace RC::Unreal
{
	class UAltarCheatManager;
	class AVPairedPawn;
}

#define MODSTR(_in_mod_str) STR("[AHorseWithNoName] " _in_mod_str "\n")

namespace RC::Mod::HorseName
{
    using namespace RC::Unreal;
    using namespace std;
    using namespace RC;

	class HorseHandler
	{
        const CharType* OnFadeToBlackEvent = STR("/Script/Altar.VLevelChangeData:OnFadeToBlackBeginEventReceived"); // NOLINT(clang-diagnostic-unused-private-field)
        const CharType* OnStartDockingEvent = STR("/Script/Altar.VPairedCharacter:OnStartDockingToHorse");          // NOLINT(clang-diagnostic-unused-private-field)
        const CharType* GetHorseFunc = STR("/Script/Altar.VPairedCharacter:GetHorse");                              // NOLINT(clang-diagnostic-unused-private-field)
        inline static UnrealScriptFunctionCallable NoCallback = [](UnrealScriptFunctionCallableContext&, void*) {};
        std::map<StringType, StringType> HorseNames;
        AVPairedPawn* LastRiddenHorse = nullptr;

        static auto PostOnStartDockingToHorse(const UnrealScriptFunctionCallableContext& context, void* customData) -> void;
        auto RenameHorse(UAltarCheatManager* pCheatManager, const StringType& formID, const StringType& horseName) -> void;
		auto ResetLastCalledHorse(UnrealScriptFunctionCallableContext& context, void* customData) -> void;
        auto PostGetHorse(const UnrealScriptFunctionCallableContext& context, void* customData) -> void;
        auto UpdateHorseName(AVPairedPawn* pHorse) -> void;

    public:
        auto RegisterHooks() -> void;
	};
}
