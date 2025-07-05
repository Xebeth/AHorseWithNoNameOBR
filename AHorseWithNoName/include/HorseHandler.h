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
     	const CharType* OnActivatePressedEvent = STR("/Script/Altar.VEnhancedAltarPlayerController:ActivateInput_Pressed");
		const CharType* OnBlockReleasedEvent = STR("/Script/Altar.VEnhancedAltarPlayerController:BlockInput_Released");
		const CharType* OnBlockPressedEvent = STR("/Script/Altar.VEnhancedAltarPlayerController:BlockInput_Pressed");
        const CharType* OnFadeToBlackEvent = STR("/Script/Altar.VLevelChangeData:OnFadeToBlackBeginEventReceived");
        const CharType* OnStartDockingEvent = STR("/Script/Altar.VPairedCharacter:OnStartDockingToHorse");
        const CharType* GetHorseFunc = STR("/Script/Altar.VPairedCharacter:GetHorse");

		inline static UnrealScriptFunctionCallable NoCallback = [](UnrealScriptFunctionCallableContext&, void*) {};
		std::map<StringType, std::pair<int, int>> RegisteredHooks;
		fnSetSelectedActor SetSelectedActorFunc = nullptr;
        std::map<StringType, StringType> HorseNames;
        AVPairedCreature* LastRiddenHorse = nullptr;
		bool m_BlockPressed = false;
		Config* m_pConfig = nullptr;

		static auto PostOnStartDockingToHorse(const UnrealScriptFunctionCallableContext& context, void* customData) -> void;

        auto RenameHorse(AVAltarPlayerController *pPlayerController, AVPairedCreature *pHorse, const StringType &horseName) const -> void;
		auto PostOnBlockReleasedEvent(const UnrealScriptFunctionCallableContext &context, void* customData) -> void;
		auto PostOnBlockPressedEvent(const UnrealScriptFunctionCallableContext &context, void* customData) -> void;
		auto PreOnActivatePressedEvent(UnrealScriptFunctionCallableContext &context, void* customData) const -> void;
		auto RestoreHorseName(AVAltarPlayerController* pPlayerController, AVPairedCreature *pHorse) -> void;
		auto HideHorseName(AVAltarPlayerController* pPlayerController, AVPairedCreature * pHorse) -> void;
        auto PostGetHorse(const UnrealScriptFunctionCallableContext& context, void* customData) -> void;
        auto UpdateHorseName(AVPairedCreature* pHorse) -> void;

    public:
		HorseHandler(fnSetSelectedActor setSelectedActorFunc, Config *pConfig);
		~HorseHandler();

		static auto OpenHorseInventory(AVAltarPlayerController *pPlayerController = nullptr) -> bool;
		static auto PlayerController() -> AVAltarPlayerController*
		{
			return reinterpret_cast<AVAltarPlayerController*>(FindFirstOf(STR("BP_AltarPlayerController_C")));
		}

        [[nodiscard]] auto GetLastRiddenHorse() const -> AVPairedCreature* { return LastRiddenHorse; }
        auto UnregisterHooks() -> void;
		auto RegisterHooks() -> void;
	};
}
