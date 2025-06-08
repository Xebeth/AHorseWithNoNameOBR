#pragma once

namespace RC::UserMod::HorseName
{
	using namespace RC::Unreal::UObjectGlobals;
    using namespace RC::Unreal;
    using namespace std;
    using namespace RC;

	class Config;

	typedef void(WINAPI* fnSetSelectedActor)(UAltarCheatManager* pThis, AActor* pTarget);

	class HorseHandler
	{
        const CharType* OnFadeToBlackEvent = STR("/Script/Altar.VLevelChangeData:OnFadeToBlackBeginEventReceived"); // NOLINT(clang-diagnostic-unused-private-field)
        const CharType* OnStartDockingEvent = STR("/Script/Altar.VPairedCharacter:OnStartDockingToHorse");          // NOLINT(clang-diagnostic-unused-private-field)
        const CharType* GetHorseFunc = STR("/Script/Altar.VPairedCharacter:GetHorse");                              // NOLINT(clang-diagnostic-unused-private-field)
        inline static UnrealScriptFunctionCallable NoCallback = [](UnrealScriptFunctionCallableContext&, void*) {};
		std::map<StringType, std::pair<int, int>> RegisteredHooks;
		fnSetSelectedActor SetSelectedActorFunc = nullptr;
        std::map<StringType, StringType> HorseNames;
        AVPairedCreature* LastRiddenHorse = nullptr;
		bool ForceUnmount = false;

		Config* m_pConfig = nullptr;

        static auto PostOnStartDockingToHorse(const UnrealScriptFunctionCallableContext& context, void* customData) -> void;
        auto RenameHorse(AVAltarPlayerController *pPlayerController, AActor *pHorse, const StringType &horseName) const -> void;
		auto ResetLastRiddenHorse(UnrealScriptFunctionCallableContext& context, void* customData) -> void;
        auto PostGetHorse(const UnrealScriptFunctionCallableContext& context, void* customData) -> void;
        auto UpdateHorseName(AVPairedCreature* pHorse) -> void;

    public:
		HorseHandler(fnSetSelectedActor setSelectedActorFunc, Config *pConfig);
		~HorseHandler();

		static auto PlayerController() -> AVAltarPlayerController*
		{
			return reinterpret_cast<AVAltarPlayerController*>(FindFirstOf(STR("BP_AltarPlayerController_C")));
		}

		auto RestoreHorseName(AVAltarPlayerController* pPlayerController, AVPairedCreature *pHorse) -> void;
		auto HideHorseName(AVAltarPlayerController* pPlayerController, AVPairedCreature * pHorse) -> void;
		auto SetForceUnmount(const bool force) -> HorseHandler* { ForceUnmount = force; return this; }
        [[nodiscard]] auto GetLastRiddenHorse() const -> AVPairedCreature* { return LastRiddenHorse; }

        auto UnregisterHooks() -> void;
		auto RegisterHooks() -> void;
	};
}
