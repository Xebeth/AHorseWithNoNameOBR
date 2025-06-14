#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>
#include <AActor.hpp>

#include <glaze/json/schema.hpp>
#include <string>
#include <map>

#include "Config.h"
#include "PropertyMacro.h"
#include "TESForm.h"
#include "TESActorBase.h"
#include "UCheatManager.h"
#include "PlayerController.h"
#include "UAltarCheatManager.h"
#include "VTESObjectRefComponent.h"
#include "VCharacterStatePairingComponent.h"
#include "VPairedPawn.h"
#include "VPairedCreature.h"
#include "VPairedCharacter.h"
#include "VOblivionPlayerCharacter.h"
#include "VAltarPlayerController.h"
#include "HorseHandler.h"

namespace RC::UserMod::HorseName
{
	HorseHandler::HorseHandler(const fnSetSelectedActor setSelectedActorFunc, Config *pConfig) : m_pConfig(pConfig)
	{
		SetSelectedActorFunc = setSelectedActorFunc;
	}

	HorseHandler::~HorseHandler()
	{
		if (m_pConfig != nullptr)
		{
			delete m_pConfig;
			m_pConfig = nullptr;
		}

		SetSelectedActorFunc = nullptr;
	}

	auto HorseHandler::PreOnActivatePressedEvent(UnrealScriptFunctionCallableContext& context, void *) -> void
	{
		if (const auto pPlayerController = reinterpret_cast<AVAltarPlayerController*>(context.Context); pPlayerController != nullptr)
		{
			if (const auto pPlayer = pPlayerController->GetPlayerCharacter(); pPlayer != nullptr && pPlayer->IsSneaking())
			{
				context.OverrideOriginal = OpenHorseInventory(pPlayerController);
			}
		}
	}

	auto HorseHandler::PostOnStartDockingToHorse(const UnrealScriptFunctionCallableContext& context, void *) -> void
	{
		if (const auto pRider = reinterpret_cast<AVPairedCharacter*>(context.Context); pRider != nullptr)
		{
			pRider->GetHorse();
		}
	}

	auto HorseHandler::PostGetHorse(const UnrealScriptFunctionCallableContext& context, void*) -> void
	{
		const auto ppHorse = static_cast<UObject**>(context.RESULT_DECL);

		if (ppHorse == nullptr)
		{
			Output::send<LogLevel::Warning>(MODSTR("No return value"));

			return;
		}

		const auto pHorse = reinterpret_cast<AVPairedCreature*>(*ppHorse);

		if (pHorse == nullptr)
		{
			Output::send<LogLevel::Warning>(MODSTR("Invalid horse"));

			return;
		}

		Output::send(MODSTR("Found the horse: {}"), pHorse->GetName());

		const auto pRider = reinterpret_cast<AVPairedPawn*>(context.Context);

		if (pRider == nullptr)
		{
			Output::send<LogLevel::Warning>(MODSTR("Invalid rider"));

			return;
		}

		if (pRider->IsPlayerCharacter())
		{
			this->UpdateHorseName(pHorse);
		}
		else
		{
			Output::send<LogLevel::Warning>(MODSTR("{} is not the player"), pRider->GetName());
		}
	}

	auto HorseHandler::OpenHorseInventory(AVAltarPlayerController *pPlayerController) -> bool
	{
		if (pPlayerController == nullptr)
		{
			pPlayerController = PlayerController();
		}

		if (pPlayerController != nullptr)
		{
			if (const auto pCheatManager = pPlayerController->GetAltarCheatManager(); pPlayerController != nullptr && pCheatManager != nullptr)
			{
				const auto castSpell = FString {STR("ahwsOpenSaddlebagsREF.Cast ahwsActivateHorseSpell Player")};
				const auto moveLootBag = FString {STR("ahwsSaddlebagsREF.MoveTo Player 0,0,-1000")};
				const auto moveActivator = FString {STR("ahwsOpenSaddlebagsREF.MoveTo Player")};
				const auto enableActivator = FString {STR("ahwsOpenSaddlebagsREF.Enable")};

				pCheatManager->SendMultipleOblivionCommand({moveActivator, enableActivator, moveLootBag, castSpell});

				return true;
			}
		}

		return false;
	}

	auto HorseHandler::RestoreHorseName(AVAltarPlayerController *pPlayerController, AVPairedCreature *pHorse) -> void
	{
		if (pHorse == nullptr || pPlayerController == nullptr)
			return;

		if (const auto editorID = pHorse->GetEditorID(); HorseNames.contains(editorID))
		{
			const auto horseName = HorseNames[editorID];

			Output::send(MODSTR("Restore horse name {} -> {}"), editorID, horseName);
			RenameHorse(pPlayerController, pHorse, horseName);
		}
		else
		{
			Output::send<LogLevel::Warning>(MODSTR("Horse name not found for ID {} [{}]"), editorID, pHorse->GetName());
		}
	}
	auto HorseHandler::HideHorseName(AVAltarPlayerController *pPlayerController, AVPairedCreature *pHorse) -> void
	{
		if (pHorse != nullptr && pPlayerController != nullptr)
		{
			const auto editorID = pHorse->GetEditorID();
			const StringType horseName = HorseNames[editorID] = m_pConfig->GetHorseName(to_string(editorID));

			Output::send(MODSTR("Hide horse name {} -> {}"), editorID, horseName);
			RenameHorse(pPlayerController, pHorse, STR(" "));
		}
	}

	auto HorseHandler::UpdateHorseName(AVPairedCreature *pHorse) -> void
	{
		const auto pPlayerController = PlayerController();

		if (pPlayerController == nullptr)
		{
			Output::send<LogLevel::Warning>(MODSTR("Invalid player controller"));

			return;
		}

		auto mounted = pPlayerController->IsHorseRiding() && pHorse != nullptr;

		Output::send(MODSTR("UpdateHorseName: {}"), mounted ? STR("Mounted") : STR("Dismounted"));

		if (mounted == false)
		{
			if (LastRiddenHorse != nullptr)
			{
				RestoreHorseName(pPlayerController, LastRiddenHorse);
				LastRiddenHorse = nullptr;
			}
		}
		else if (LastRiddenHorse == nullptr)
		{
			HideHorseName(pPlayerController, pHorse);
			LastRiddenHorse = pHorse;
		}
	}

	auto HorseHandler::RenameHorse(AVAltarPlayerController *pPlayerController, AVPairedCreature* pHorse, const StringType &horseName) const -> void
	{
		if (const auto pCheatManager = pPlayerController->GetAltarCheatManager(); SetSelectedActorFunc != nullptr && pCheatManager != nullptr)
		{
			const auto command = FString {std::format(STR("SetActorFullName \"{}\""), horseName).c_str()};

			SetSelectedActorFunc(pCheatManager, pHorse);
			pCheatManager->SendMultipleOblivionCommand({ command });
		}
	}

	auto HorseHandler::RegisterHooks() -> void
	{
		UnregisterHooks();

		RegisteredHooks.emplace(OnFadeToBlackEvent, RegisterHook(OnFadeToBlackEvent, [&](UnrealScriptFunctionCallableContext&, void*) { LastRiddenHorse = nullptr; }, NoCallback, nullptr));
		//RegisteredHooks.emplace(OnActivatePressedEvent, RegisterHook(OnActivatePressedEvent, &HorseHandler::PreOnActivatePressedEvent, NoCallback, nullptr));
		RegisteredHooks.emplace(OnStartDockingEvent, RegisterHook(OnStartDockingEvent, NoCallback, &HorseHandler::PostOnStartDockingToHorse, nullptr));
		RegisteredHooks.emplace(GetHorseFunc, RegisterHook(GetHorseFunc, NoCallback, bind_front(&HorseHandler::PostGetHorse, this), nullptr));
	}

	auto HorseHandler::UnregisterHooks() -> void
	{
		for (const auto &[functionName, hooks] : RegisteredHooks)
		{
			UnregisterHook(functionName, hooks);
		}

		RegisteredHooks.clear();
	}
}
