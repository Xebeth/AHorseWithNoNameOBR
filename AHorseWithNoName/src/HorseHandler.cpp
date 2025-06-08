#include <String/StringType.hpp>
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

	auto HorseHandler::PostOnStartDockingToHorse(const UnrealScriptFunctionCallableContext& context, void *) -> void
	{
		if (const auto pPlayer = reinterpret_cast<AVPairedCharacter*>(context.Context); pPlayer != nullptr)
		{
			pPlayer->GetHorse();
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
			Output::send<LogLevel::Warning>(MODSTR("{} is not the player"), pRider->GetFullName());
		}
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
			const auto actorName = pHorse->GetActorName();
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

		if (ForceUnmount || mounted == false)
		{
			ForceUnmount = false;

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

	auto HorseHandler::RenameHorse(AVAltarPlayerController *pPlayerController, AActor* pHorse, const StringType &horseName) const -> void
	{
		if (auto pCheatManager = pPlayerController->GetAltarCheatManager(); SetSelectedActorFunc != nullptr && pCheatManager != nullptr)
		{
			const StringType command = std::format(STR("setactorfullname \"{}\""), horseName);

			SetSelectedActorFunc(pCheatManager, pHorse);
			pCheatManager->SendMultipleOblivionCommand({ FString(command.c_str()) });
		}
	}

	void HorseHandler::ResetLastRiddenHorse(UnrealScriptFunctionCallableContext&, void*)
	{
		this->LastRiddenHorse = nullptr;
	}

	auto HorseHandler::RegisterHooks() -> void
	{
		UnregisterHooks();

		RegisteredHooks.emplace(OnFadeToBlackEvent, RegisterHook(OnFadeToBlackEvent, bind_front(&HorseHandler::ResetLastRiddenHorse, this), NoCallback, nullptr));
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
